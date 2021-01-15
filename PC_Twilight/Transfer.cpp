

class e_TransferAction:public GameEffect{
	bool CanActivate(Player* player, Hex* hex){
		bool enemyunits = false;
		bool playerunits = false;
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if ((*aiter)->GetHex() == hex){
				if ((*aiter)->GetUnits()->size() > 0)
					if ((*aiter)->GetOwner() == player)
						playerunits = true;
					else
						enemyunits = true;
			}
		}
		return (playerunits && !enemyunits);
	}
	void AssignTransfer(Army* army){
		for (int i=0; i<army->IsUnitWithAbility(uaHyperDrive); i++)
			army->GetUnitWithAbility(uaHyperDrive,i+1)->AddAbility(uaTransfered);
	}
	UnitArmy SelectUnitTransfer(Army* army1, Army* army2){
		int x1,y1,x2,y2;
		army1->GetHex()->GetCoords(&x1,&y1);
		army2->GetHex()->GetCoords(&x2,&y2);
		Unit* unit;
		UnitArmy UA;
		UA.army = 0;
		UA.unit = 0;
		UA.selected = false;
		char str[255];
		if (!army1->IsUnitWithAbility(uaHyperDrive) && !army2->IsUnitWithAbility(uaHyperDrive))
			return UA;
		_GrIn.InitChoise("Select units to move",true,false);
		int s1=0, s2=0;
		for (int i=0; i<army1->IsUnitWithAbility(uaTransfered); i++){
			unit = army1->GetUnitWithAbility(uaTransfered,i+1);
			sprintf(str,"%s(%d,%d)",_Info.UnitInfo(unit,army1).c_str(),x1,y1);
			_GrIn.AddOption(SHIPS_IMG[unit->Class],str);
			s1++;
		}
		s2 = s1;
		for (int i=0; i<army2->IsUnitWithAbility(uaTransfered); i++){
			unit = army2->GetUnitWithAbility(uaTransfered,i+1);
			sprintf(str,"%s(%d,%d)",_Info.UnitInfo(unit,army2).c_str(),x2,y2);
			_GrIn.AddOption(SHIPS_IMG[unit->Class],str);
			s1++;
		}
		vector<int> tempvec = _GrIn.LaunchChoise();
		int* ret = 0;
		if (tempvec.size() != 0)
			ret = &tempvec[0];
		if (ret == 0)
			return UA;
		for (int i=0; i<s1; i++){
			if (ret[i] == 1){
				if (i >= s2){
					UA.army = army2;
					UA.unit = army2->GetUnitWithAbility(uaTransfered,i+1-s2);
				}
				else{
					UA.army = army1;
					UA.unit = army1->GetUnitWithAbility(uaTransfered,i+1);
				}
				UA.selected = true;
			}
		}
		return UA;
	}
	vector<vector<Hex*>> FindRoutes(Hex* hex1, Hex* hex2, int speed, Player* player){
		vector<vector<Hex*>> result;
		vector<Hex*> temp;
		result.clear();
		if (speed >= 1){
			temp.clear();
			temp.push_back(hex1);
			temp.push_back(hex2);
			result.push_back(temp);
			if ((speed > 1) && (player->GetMoveStats()->pass[hex2->GetDanger()]) && 
				(player->GetMoveStats()->pass[hex1->GetDanger()])){
					temp.clear();
					temp.push_back(hex1);
					temp.push_back(hex2);
					temp.push_back(hex1);
					result.push_back(temp);
			}
		}
		return result;
	}
	bool CanProduceInHex(Hex* hex, Player* player){
		bool result = false;
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if (((*aiter)->GetOwner() == player) && ((*aiter)->GetHex() == hex) && ((*aiter)->IsUnitWithAbility(uaProduction,FIELD_SKIP,FIELD_SKIP,1))){
				result = true;
				break;
			}
		}
		return result;
	}
public:
	e_TransferAction(){
		id = "TransferAction";
		image=TRANSFER_ACTION_IMG;//заменить картинку
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		Hex* hex1;
		Hex* hex2;
		Hex* moveto;
		Hex* hexpickup;
		Hex* produce;
		int a,b;
		int x1,y1,x2,y2;
		char str[255];
		Army* army1;
		Army* army2;
		UnitArmy UA;
		bool done = true;
		int cancel = 1;
		vector<vector<Hex*>> marchroutes;
		int* ret = 0;
		//1.1 - Activating first system, contain at least 1 player's unit and no one enemy (include GF)
		if (!player->GetCountersCP()){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Not enough counters");
			return er_normal;
		}
		sprintf(str,"Player %s uses Transfer Action",player->GetName().c_str());
		_Interface.PrintThingAll(str);
		while (cancel){
			cancel = 1;
			do{
				vector<int> tempvec = _GrIn.SysChoise("Select first system for Transfer Action",true);
				if (tempvec.size() == 0){
					_Interface.PrintThingPlayer(player->GetNumber()-1,"Transfer Action was cancelled");
					return er_none;
					//break;
					//cancel = 0;
				}
				else {//(tempvec.size() > 1)
					a = tempvec[0];
					b = tempvec[1];
					if (_Map.GetHexh(a,b)->GotCC(player->GetNumber()))
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Already got your CC");
					else if (player->GetMoveStats()->active[_Map.GetHexh(a,b)->GetDanger()] == 0)
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Can not be activated by you");
					else if (!CanActivate(player,_Map.GetHexh(a,b)))
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Can't use transfer on this hex");
					else
						done = false;
				}
				//else
				//	return er_none;
			}while (done);
			hex1 = _Map.GetHexh(a,b);
			sprintf(str,"Selected system %s(%d,%d)",hex1->GetId().c_str(),a,b);
			_Interface.PrintThingPlayer(player->GetNumber()-1,str);
			//1.2 - Activating second system, contain at least 1 player's unit and no one enemy (include GF)
			done = true;
			do{
				vector<int> tempvec = _GrIn.SysChoise("Select second system for Transfer Action",true);
				if (tempvec.size() == 0){
					break;
				}
				else{//if (tempvec.size() > 1)
					a = tempvec[0];
					b = tempvec[1];
					if (_Map.GetHexh(a,b)->GotCC(player->GetNumber()))
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Already got your CC");
					else if (player->GetMoveStats()->active[_Map.GetHexh(a,b)->GetDanger()] == 0)
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Can not be activated by you");
					else if (!CanActivate(player,_Map.GetHexh(a,b)))
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Can't use transfer on this hex");
					else if (hex1->GetLinkedHexes()->GetLink(_Map.GetHexh(a,b)) == ltNone)
						_Interface.PrintThingPlayer(player->GetNumber()-1,"This hex isn't adjacent with the first one");
					else{
						done = false;
						cancel = 0;
					}
				}
				//else
				//	return er_none;
			}while (done);
		}
		hex2 = _Map.GetHexh(a,b);
		sprintf(str,"Player %s activates systems %s ans %s for Transfer Action",player->GetName().c_str(),hex1->GetId().c_str(),hex2->GetId().c_str());
		_Interface.PrintThingAll(str);
		//sprintf(str,"Selected system %s(%d,%d)",hex2->GetId().c_str(),a,b);
		//_Interface.PrintThingPlayer(player->GetNumber()-1,str);
		player->TakeCounter(CC_comm);
		//2.0 Movement between hex1 and hex2
		hex1->GetCoords(&x1,&y1);
		hex2->GetCoords(&x2,&y2);
		done = true;
		army1 = FindArmy(hex1,player,true);
		army2 = FindArmy(hex2,player,true);
		AssignTransfer(army1);
		AssignTransfer(army2);
		player->GetMoveStats()->Reset();
		RefreshArmyAbilities(player,2);			//обновление скоростей юнитов
		player->ExecuteGameEffect(ExecuteParams(eq_BeforeMovement, player));
		while (done){
			UA = SelectUnitTransfer(army1,army2);
			if (!UA.selected)
				break;
			sprintf(str,"Selected unit: %s from %s",ShipsFull[UA.unit->Class].c_str(),UA.army->GetHex()->GetId().c_str());
			_Interface.PrintThingPlayer(player->GetNumber()-1,str);
			marchroutes.clear();
			if (UA.army->GetHex() == hex1)
				marchroutes = FindRoutes(hex1,hex2,UA.unit->GetAbility(uaHyperDrive).field1,player);
			else
				marchroutes = FindRoutes(hex2,hex1,UA.unit->GetAbility(uaHyperDrive).field1,player);
			player->ExecuteGameEffect(ExecuteParams(eq_Movement,UA.army,UA.unit));
			if (UA.unit->HasAbility(uaKilled)){
				CombatInterface().DestroyUnit(UA.army,UA.unit);
				continue;
			}
			if (marchroutes.size() == 2){//если скорость выше 1, спросить, куда летим
				_GrIn.InitChoise("Select system to move",true,false);
				sprintf(str,"%s(%d,%d)",hex1->GetId().c_str(),x1,y1);
				_GrIn.AddOption(SYSTEM_IMG,str);
				sprintf(str,"%s(%d,%d)",hex2->GetId().c_str(),x2,y2);
				_GrIn.AddOption(SYSTEM_IMG,str);
				vector<int> tempvec = _GrIn.LaunchChoise();
				if (tempvec.size() != 0)
					ret = &tempvec[0];
				if (ret == 0)
					continue;
				else
					if (ret[0] == 1)
						moveto = hex1;
					else
						moveto = hex2;
			}
			if (marchroutes.size() == 1){//если скорость один или обратно полететь нельзя, то не спрашиваем, куда летим
				if (UA.army->GetHex() == hex1)
					moveto = hex2;
				else
					moveto = hex1;
			}
			while (FreeCapacity(player,UA.army,UA.unit) > 0){//подхват
				//sprintf(buff,"{%s from %s (%d, %d)}: Specify pick up location?",_Info.UnitInfo(iter->unit,iter->army).c_str(),iter->army->GetHex()->GetId().c_str(),iter->army->GetHex()->xc,iter->army->GetHex()->yc);
				sprintf(str,"{%s from %s (%d, %d)}: Specify pick up location?",_Info.UnitInfo(UA.unit,UA.army).c_str(), UA.army->GetHex()->GetId().c_str(),UA.army->GetHex()->xc,UA.army->GetHex()->yc);
				vector<int> tempvec = _GrIn.SysChoise(str,true);
				if (tempvec.size() == 0)
					break;
				a = tempvec[0];
				b = tempvec[1];
				hexpickup = _Map.GetHexh(a,b);
				if (hexpickup != 0){
					if ((hexpickup == hex1)||(hexpickup == hex2)){
						UA.unit = MoveUnit(UA.army,FindArmy(a,b,player,true),UA.unit);
						UA.army = FindArmy(a,b,player);
						ZoldnRelocateCarriable(UA.army,UA.unit);//замена
					}
					else
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Can't pick up units from third hex in transfer");
				}
			}
			UA.unit = MoveUnit(UA.army,FindArmy(moveto,player),UA.unit);
			UA.unit->DeleteAbility(uaTransfered);
		}
		player->CheckFleets();//проверка флотов на переполнение
		army1->DeleteUnitAbility(uaTransfered);
		army2->DeleteUnitAbility(uaTransfered);
		//CheckTradeStations(hex1,player);
		//CheckTradeStations(hex2,player);
		CheckTradeStations();
		hex1->SetCC(player->GetNumber());//ставим каунтеры
		hex2->SetCC(player->GetNumber());
		//3.0 PDS fire to hex1 and hex2
		CombatInterface().GEE(eq_PDSmain,army1,0,0);
		CombatInterface().GEE(eq_PDSmain,army2,0,0);
		//4.0 dropping down to the planets
		CombatInterface().Landing(army1,true);
		CombatInterface().Landing(army2,true);
		//5.0 Production in one system
		bool builds1 = CanProduceInHex(hex1,player);
		bool builds2 = CanProduceInHex(hex1,player);
		if (builds1 || builds2){
			if (builds1 && builds2){//если можно производиться в обеих системах, то выбрать
				_GrIn.InitChoise("Select system to produce",true,false);
				sprintf(str,"%s(%d,%d)",hex1->GetId().c_str(),x1,y1);
				_GrIn.AddOption(SYSTEM_IMG,str);
				sprintf(str,"%s(%d,%d)",hex2->GetId().c_str(),x2,y2);
				_GrIn.AddOption(SYSTEM_IMG,str);
				vector<int> tempvec = _GrIn.LaunchChoise();
				if (tempvec.size() != 0)
					ret = &tempvec[0];
				if (ret != 0)
					if (ret[0] == 1)
						produce = hex1;
					else
						produce = hex2;
			}
			else
				if (builds1)
					produce = hex1;
				else
					produce = hex2;
			if (produce != 0)
				player->Produce(produce);
		}
		else
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Nothing/nowhere to produce");
		player->CheckFleets();
		//hex1->SetCC(player->GetNumber());
		//hex2->SetCC(player->GetNumber());
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_TransferAction(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};