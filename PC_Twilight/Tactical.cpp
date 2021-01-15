
//backup
class e_TacticalAction:public GameEffect{
public:
	e_TacticalAction(){
		id = "TacticalAction";
		image=TACTICAL_ACTION_IMG;
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){//remember - memory leak
		int a,b,x,y,i,j,z;
		bool done = true;
		Army* arriving;
		Player* player = EP.player;
		Hex* toact;
		Hex* hexpickup;
		char buff[256];
		char buffz[1024];
		if (!player->GetCountersCP()){
			_Interface.PrintThingAll("Not enough counters");
			return er_normal;
		}
		sprintf(buffz,"Player %s uses Tactical Action",player->GetName().c_str());
		_Interface.PrintThingAll(buffz);
		player->GetMoveStats()->Reset();		//обновление мувстатсов
		RefreshArmyAbilities(player,2);			//обновление скоростей юнитов
		player->ExecuteGameEffect(ExecuteParams(eq_BeforeMovement, player));
		// 1) Activating system;
		do{
			vector<int> tempvec = _GrIn.SysChoise("Choose sys to activate");
			if (tempvec.size() > 1){
				a = tempvec[0];
				b = tempvec[1];
				if (_Map.GetHexh(a,b)->GotCC(player->GetNumber()))
					_Interface.PrintThingAll("Already got your CC");
				else if (player->GetMoveStats()->active[_Map.GetHexh(a,b)->GetDanger()] == 0)
					_Interface.PrintThingAll("Can not be activated by you");
				else
					done = false;
			}
			else
				return er_none;
		}while (done);
		arriving = FindArmy(a,b,player,true);
		toact = _Map.GetHexh(a,b);
		sprintf(buffz,"Player %s has activated system %s for Tactical Action",player->GetName().c_str(),toact->GetId().c_str());
		_Interface.PrintThingAll(buffz);
		int check = 0;
		player->TakeCounter(CC_comm);
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->ExecuteGameEffect(ExecuteParams(eq_ActivateSystem,_Players[i],arriving,&check));
		if (check == 1)//возврат к выбору действия без активации системы
			return er_none;
		if (check == 2){//пропуск хода с активацией
			toact->SetCC(player->GetNumber());
			return er_normal;
		}
		if (check == 3)//пропуск хода без активации
			return er_normal;
		
		// 2) Movement into system
		vector<Unit*>* zunit;
		UnitArmy ua;
		vector<UnitArmy> unitlist;
		vector<UnitArmy> options;
		vector<UnitArmy> todelete;
		SpeedMap speedmap;						//создание карты скоростей
		PathFinder PF;	
		//создание поисковика
		speedmap.CalculateMap(player,toact);	//расчет скоростей до toact
		options.clear();
		//формирование списка опций для выбора
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if (((*aiter)->GetOwner() == player)&&((*aiter)->GetPlanet() == 0)&&(!(*aiter)->GetHex()->GotCC(player->GetNumber()))){
				for (i = GF; i < MAX_UNIT; i++){
					if ((*aiter)->StackSize((UnitType)i) > 0){
						if ((*aiter)->GetUnit((UnitType)i)->HasAbility(uaHyperDrive)){
							if ((*aiter)->GetUnit((UnitType)i)->GetAbility(uaHyperDrive).field1 >= speedmap.GetDistance((*aiter)->GetHex())){
								if (!(*aiter)->GetUnit((UnitType)i)->HasAbility(uaMultiple)){
									for (j = 1; j <= (*aiter)->StackSize((UnitType)i); j++){
										ua.unit = (*aiter)->GetUnit((UnitType)i,j);
										ua.army = *aiter;
										ua.selected = 1;
										options.push_back(ua);
									}
								}
								else{
									ua.unit = (*aiter)->GetUnit((UnitType)i,1);
									ua.army = *aiter;
									ua.selected = (*aiter)->StackSize((UnitType)i);
									options.push_back(ua);
								}
							}
						}
					}
				}
			}
		}
		while (options.size()){
			_GrIn.InitChoise("Choose units to move",false,true,true);
			for (vector<UnitArmy>::iterator iter = options.begin(); iter != options.end(); iter++){
				iter->army->GetHex()->GetCoords(&x,&y);
				sprintf(buff,"%s x%d (%d,%d)",_Info.UnitInfo(iter->unit,iter->army).c_str(),iter->selected,x,y);
				_GrIn.AddNumerical(SHIPS_IMG[iter->unit->Class],buff);
			}
			vector<int> ret = _GrIn.LaunchChoise();
			if (ret.size() == 0)
				break;
			for (i = 0; i < ret.size(); i++)//проверка на выбор больше, чем есть
				if (ret[i] > options[i].army->StackSize(options[i].unit->Class))
					ret[i] = options[i].army->StackSize(options[i].unit->Class);
			unitlist.clear();
			ua.selected = 0;
			for (i = 0; i < ret.size(); i++){//формируем юнитлист из выбранных юнитов
				if (options[i].unit->HasAbility(uaMultiple)){
					for (j = 1; j <= ret[i]; j++){
						ua.unit = options[i].army->GetUnit(options[i].unit->Class,j);
						ua.army = options[i].army;
						unitlist.push_back(ua);
					}
				}
				else{
					if (ret[i] > 0){
						ua.unit = options[i].unit;
						ua.army = options[i].army;
						unitlist.push_back(ua);
					}
				}
			}
			for (vector<UnitArmy>::iterator iter = unitlist.begin(); iter != unitlist.end(); iter++)
				player->ExecuteGameEffect(ExecuteParams(eq_Movement,iter->army,iter->unit));
			vector<UnitArmy>::iterator iter = unitlist.begin();
			todelete.clear();
			while (iter != unitlist.end()){
				if (iter->unit->HasAbility(uaKilled)){
					todelete.push_back(*iter);
					unitlist.erase(iter);
					iter = unitlist.begin();
					Log("e_Tactical::Execute : remove destroyed units to %todelete%");
				}
				else
					iter++;
			}
			Log("e_Tactical::Execute : removing destroyed units from %todelete%");
			for (iter = todelete.begin(); iter != todelete.end(); iter++)
				if (iter->army->IsUnitWithAbility(uaKilled,0))
					CombatInterface().DestroyUnit(iter->army,iter->army->GetUnitWithAbility(uaKilled,1));
			Log("e_Tactical::Execute : removed destroyed units from %todelete%");
			for (vector<UnitArmy>::iterator iter = unitlist.begin(); iter != unitlist.end(); iter++){
				PF.set(iter->army->GetHex(),toact,iter->unit->GetAbility(uaHyperDrive).field1,player,&speedmap);
				z = PF.FindRoutes();
				if (!z)
					Log("e_Tactical::Execute : There is NO WAY!");
				while (FreeCapacity(player,iter->army,iter->unit) > 0){
					sprintf(buff,"{%s from %s (%d, %d)}: Specify pick up location?",_Info.UnitInfo(iter->unit,iter->army).c_str(),iter->army->GetHex()->GetId().c_str(),iter->army->GetHex()->xc,iter->army->GetHex()->yc);
					x = a;
					y = b;
					vector<int> tempvec = _GrIn.SysChoise(buff,true);
					if (tempvec.size() == 0)
						break;
					x = tempvec[0];
					y = tempvec[1];
					hexpickup = _Map.GetHexh(x,y);
					if (hexpickup != 0){
						if (PF.IsHexInRoutes(hexpickup)){
							PF.RoutesThroughHex(hexpickup);
							iter->unit = MoveUnit(iter->army,FindArmy(x,y,player,true),iter->unit);
							iter->army = FindArmy(x,y,player);
							ZoldnRelocateCarriable(iter->army,iter->unit);
						}
						else{//если гекс не достигается, то вывести список доступных
							_Interface.PrintThingAll("Can't reach this way");
							vector<Hex*> available = PF.AvailableHexes();
							sprintf(buffz,"Available hexes to pick up: ");
							for (vector<Hex*>::iterator aiter = available.begin(); aiter != available.end(); aiter++){
								sprintf(buff,"%s; ",(*aiter)->GetId().c_str());
								strcat(buffz,buff);
							}
							_Interface.PrintThingAll(buffz);
							continue;
						}
					}
					else
						break;
				}
				cout<<"Tactical1"<<endl;
				MoveUnit(iter->army,arriving,iter->unit);
				cout<<"Tactical2"<<endl;
			}
			player->ExecuteGameEffect(ExecuteParams(eq_AfterMovement,player,arriving));
			break;
		}
		player->CheckFleets();//проверка всех флотов на переполнение
		toact->SetCC(player->GetNumber());
		// FIGHT! 3-6
		CombatInterface().CombatTacticalAction(arriving);
		// Production 7
		player->ExecuteGameEffect(ExecuteParams(eq_Scuttle,player,arriving));
		player->Produce(toact);
		//arriving->CheckFleetSupport();
		player->CheckFleets();//проверка всех флотов на переполнение
		ClearArmies();
		player->ExecuteGameEffect(ExecuteParams(eq_AfterTactical,player));
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_TacticalAction(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};