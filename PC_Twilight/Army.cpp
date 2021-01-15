Army::Army(Player* in_owner, Hex* in_hex, Planet* in_pl){
	_armyHex=in_hex;
	_units.clear();
	_owner=in_owner;
	if (in_pl==0){
		_position=-1;
		_armyPlanet=0;
	}
	else{
		//ernies code
		_position=-2;
		for (int i=0;i<MAX_PLANETS;++i)
			if (in_hex->GetPlanet(i+1) == in_pl)
				_position = i;
		if (_position == -2)
			cout<<"goddamn position is failed";
		//ernies code end
		_armyPlanet=in_pl;
	}
	_retreating = false;
};

//возвращает игрока-владельца армии
Player* Army::GetOwner(){
	return _owner;
};

//возвращает, находитс€ ли арми€ на планете или в космосе
int Army::GetPosition(){
	return _position;
};

//возвращает гекс, в котором находитс€ арми€
Hex* Army::GetHex(){
	return _armyHex;
};


//возвращает список юнитов
vector<Unit*>* Army::GetUnits(){//PowExv<Unit>*
	return &_units;
};


//возвращает планету, на которой находитс€ юнит или NULL если арми€ находитс€ в космосе
Planet* Army::GetPlanet(){
	return _armyPlanet;
};
//добавл€ет в армию юнит указанного типа
Unit* Army::AddUnit(UnitType UT, bool isDamaged){
	UnitStats* stats = _owner->GetUnitStats();
	Unit* un;
	if (!isDamaged)
		un = new Unit(UT,stats->GetParametr(UT,sHP),0,
			stats->GetParametr(UT,sPW),
			stats->GetParametr(UT,sSH),
			stats->GetParametr(UT,sSP),
			stats->GetParametr(UT,sPROD),
			0,
			isDamaged);
	else
		if (UT == DR)
			un = new Unit(UT,1,0,stats->GetParametr(UT,sPW),
				1,stats->GetParametr(UT,sSP),stats->GetParametr(UT,sPROD),0,isDamaged);
		else
			un = new Unit(UT,1,0,stats->GetParametr(UT,sPW),
				stats->GetParametr(UT,sSH),stats->GetParametr(UT,sSP),stats->GetParametr(UT,sPROD),0,isDamaged);
	InitialAbilities(un,0,this);
	_units.push_back(un);
	if ((_position == -1)&&(un->Class == FG))
		_MapGraphics.CreateUnit(this,un,true);// код Ёрни
	else
		_MapGraphics.CreateUnit(this,un);// код Ёрни
	return un;
};

void Army::AddUnits(UnitType UT, int n){
	for (int i=0;i<n;i++)
		this->AddUnit(UT);
};

//убивает юнит
int Army::KillUnit(Unit* unit){
	if (_units.size() == 0){
		Interface().PrintError("Army::KillUnit - Trying to delete unit from empty army");
		return 0;
	}
	vector<Unit*>::iterator titer = _units.begin();
	while ((titer != _units.end()) && (*titer != unit))
		titer++;
	if (titer == _units.end()){
		Interface().PrintError("Army::KillUnit - Trying to delete unit that does not exist in army");
		return 0;
	}
	if ((_position == -1)&&(unit->Class == FG))
		_MapGraphics.KillUnit(this,unit,true);// код Ёрни
	else
		_MapGraphics.KillUnit(this,unit);// код Ёрни
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		if ((*iter)->carrier == unit)
			(*iter)->carrier = 0;
	delete *titer;
	_units.erase(titer);
	return 1;
};

int Army::CheckPasSupport(){
	if (GetPlanet()!=0)
		return 0;
	int FGcap = FighterCapacity();
	int fighterstokill = 0;
	int fighters = 0;
	char str[127];
	int supply = 0;
	Unit* unit = 0;
	bool advFG = _owner->GotTech(ttAdvancedFighters);
	for (int i=1; i<=IsUnitWithAbility(uaFighter); i++)
		if (!GetUnitWithAbility(uaFighter,i)->HasAbility(uaKilled))
			fighters++;
	if (!advFG){
		if (FGcap<=0)
			fighterstokill = fighters;
		else
			if (fighters>FGcap)
				fighterstokill = fighters-FGcap;
	}
	int j=1;
	for (int i=1; i<=fighterstokill; i++){
		while ((GetUnitWithAbility(uaFighter,j)!=0)&&(GetUnitWithAbility(uaFighter,j)->HasAbility(uaKilled)))
			j++;
		if (GetUnitWithAbility(uaFighter,j)!=0)
			GetUnitWithAbility(uaFighter,j)->AddAbility(uaKilled);
		else
			break;
		_Interface.PrintThingAll("Fighter without support was destroyed");
	}
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if (((*iter)->HasAbility(uaNeedSupport,0))&&(((*iter)->carrier==0)||((*iter)->carrier->HasAbility(uaKilled)))){
			if (!(*iter)->HasAbility(uaKilled)){
				(*iter)->AddAbility(uaKilled);
				sprintf(str,"%s was destroyed in its carrier",ShipsFull[(*iter)->Class].c_str());
				_Interface.PrintThingAll(str);
			}
		}
	}
	return 1;
};

int Army::AssignDamage(Unit* un){
	int result=0;
	int power,shots;
	if (un->HasAbility(uaSustain,0,FIELD_SKIP,1)){
		result=un->GetAbility(uaSustain).field2;
		un->AssignAbility(uaSustain,1);	
		if ((un->HasAbility(uaDamagedPenalty))&&(un->HasAbility(uaSpaceBattle))){
			power=un->GetAbility(uaDamagedPenalty).field1;
			shots=un->GetAbility(uaDamagedPenalty).field2;
			un->ModAbility(uaSpaceBattle,power,-shots);
		};
	}
	else{
		result=1;
		un->AddAbility(uaKilled);
	};
	return result;
};

//провер€ет наличие боеспособных юнитов в армии
bool Army::isDefeated(){
	if (_armyPlanet == 0)
		return !IsUnitWithAbility(uaSpaceBattle);
	else
		return !IsUnitWithAbility(uaLandBattle);
};
//очищает список юнитов
void Army::KillArmy(){
	while (_units.size() != 0)
		KillUnit(_units.front());
};
//количество юнитов заданного типа
int Army::StackSize(UnitType UT){
	int result=0;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		if ((*iter)->Class == UT)
			result++;
	return result;
};
//перенос юнита из from в to
Unit* MoveUnit(Army* from, Army* to, Unit* un){
// ≈ресь удалена, код направлен на »стинный путь - Ёрни
	if (from == to)
		return un;
	Unit * temp;
	Unit* ret;
	ret = to->AddUnit(un->Class, un->damaged);//создание переносимого юнита в новой армии
	CopyUnitAbility(un,ret);
	for (vector<Unit*>::iterator iter = from->GetUnits()->begin(); iter != from->GetUnits()->end(); iter++){
		if ((*iter)->carrier == un){
			temp = to->AddUnit((*iter)->Class,(*iter)->damaged);
			to->SetPassenger(ret,temp);
		}
	}
	vector<Unit*>::iterator iter = from->GetUnits()->begin();
	while (iter != from->GetUnits()->end()){
		if ((*iter)->carrier == un){//удаление юнитов из from
			from->KillUnit(*iter);
			iter = from->GetUnits()->begin(); // »ћ’ќ, где то тут неоптимальна€ лажа
			//очень может быть, однако при удалении юнита итератор улетает в варп
			//дабы не рисковать начнем просмотр с начала
		}
		else
			iter++;
	}
	from->KillUnit(un);
	return ret;
};

vector<Unit*> Army::GetPassengers(Unit *car){
	vector<Unit*> result;
	result.clear();
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if ((*iter)->carrier == car){
			result.push_back(*iter);
		}
	}
	return result;
}

Unit* Army::GetUnit(int n){
	if (_units.size() < n)
		return 0;
	else
		return _units.at(n-1);
};

Unit* Army::GetUnit(UnitType UT){
	Unit* result=0;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if ((*iter)->Class == UT){
			result = *iter;
			break;
		}
	}
	return result;
};

Unit* Army::GetUnit(UnitType UT, int n){
	Unit* result=0;
	int r=0;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if ((*iter)->Class == UT){
			r++;
			if (r == n){
				result = *iter;
				break;
			}
		}
	}
	return result;
};

int Army::SetPassenger(Unit *car, Unit *pas){
	if (pas->carrier==car)
		return 1;
	if ((car==0)&&(pas->carrier != 0)){
		_MapGraphics.KillUnit(this,pas);
		pas->carrier=0;
		if ((_position == -1)&&(pas->Class == FG))
			_MapGraphics.CreateUnit(this,pas,true);// код Ёрни
		else
			_MapGraphics.CreateUnit(this,pas);// код Ёрни
		return 1;
	}
	int result=-1;
	UnitStats* stats = _owner->GetUnitStats();
	UnitType UT=car->Class;	
	if (!car->HasAbility(uaCarrier)){
		Log("Army::SetPassenger : trying to put passenger in unit without uaCarrier");
		return 0;
	}
	int cap=car->GetAbility(uaCarrier).field1;
	int FGcap=car->GetAbility(uaCarrier).field2;
	int GFcap=car->GetAbility(uaCarrier).field3;
	int OTHERnum=0;
	int GFnum=0;
	int FGnum=0;
	int FULLcap=cap+GFcap+FGcap;
	if ((_position == -1)&&(pas->Class == FG))
		_MapGraphics.KillUnit(this,pas,true);// код Ёрни
	else
		_MapGraphics.KillUnit(this,pas);// код Ёрни
	if (pas->carrier != car){
		for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
			if ((*iter)->carrier == car)
				if (((*iter)->Class == GF)||((*iter)->Class == ST))
					GFnum++;
				else
					if ((*iter)->Class == FG)
						FGnum++;
					else
						OTHERnum++;
		}
		int FULLnumb=GFnum+FGnum+OTHERnum;
		if (car->HasAbility(uaUnlimGF)){
			cap=cap-OTHERnum-FGnum;
			if ((pas->Class==GF)||(pas->Class==ST)){
				pas->carrier=car;
				result=0;
			};
			if ((pas->Class==FG)||(pas->Class==MU)||(pas->Class==PDS)){
				if (cap>0){
					pas->carrier=car;
					result=cap-1;
				}
			};
			//_MapGraphics.CreateUnit(this,pas);// ¬ерю, что с новыми нововведени€ми все станет лучше, Ёрни
			return result;
		};
		if ((cap>0)&&(pas->Class<=FG)&&(FULLnumb<cap)){
			result=cap-FULLnumb-1;
			pas->carrier=car;
		};
		if ((GFcap>0)&&((pas->Class==GF)||(pas->Class==ST))&&(GFnum<GFcap)){
			result=cap-GFnum-1;
			pas->carrier=car;
		};
		if ((FGcap>0)&&(pas->Class==FG)&&(FGnum<FGcap)){
			result=cap-FGnum-1;
			pas->carrier=car;
		};
	};
	_MapGraphics.CreateUnit(this,pas);// код Ёрни
	return result;
};

int Army::GetArmyHP(){
	int result=0;
	return result;
};


int Army::GetArmyPower(){
	int result=0;
	return result;
};

int Army::GetUnitNumber(Unit *un){
	int k=1;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if (*iter == un)
			break;
		k++;
	}
	if (k > _units.size())
		return 0;
	else
		return k;
};

void MoveUnit(Army* from, Army* to, int num){
	Unit* un=from->GetUnit(num);
	if (un != 0)
		MoveUnit(from,to,un);
};

void Army::RefreshStats(){
	UnitStats* stats=new UnitStats();
	if (GetOwner()==0)
		stats->SetDefault();
	else
		stats=GetOwner()->GetUnitStats();
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		(*iter)->power = stats->GetParametr((*iter)->Class,sPW);
		(*iter)->shots = stats->GetParametr((*iter)->Class,sSH);
		(*iter)->speed = stats->GetParametr((*iter)->Class,sSP);
		if (!(*iter)->damaged)
			(*iter)->HP = stats->GetParametr((*iter)->Class,sHP);
		else
			(*iter)->HP = 1;
	}
};

int Army::FleetSupply(){
	int supply = 0;
	int fighters = 0;
	int FGcap = FighterCapacity();
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if (((*iter)->HasAbility(uaCapitalShip))&&(!(*iter)->HasAbility(uaKilled)))
			supply++;
		if (((*iter)->HasAbility(uaFighter))&&(!(*iter)->HasAbility(uaKilled)))
			fighters++;
	}
	//if ((fighters > FGcap)&&(_owner->GotTech(ttAdvancedFighters)))
	//	supply += (fighters - FGcap);
	_owner->ExecuteGameEffect(ExecuteParams(eq_FleetSupply,this,&supply));
	_owner->ExecuteGameEffect(ExecuteParams(eq_AfterFleetSupply,this,&supply));
	return supply;
};

void Army::Repair(){
	UnitStats* stats;
	if (_owner!=0)
		stats=_owner->GetUnitStats();
	else{
		stats=new UnitStats();
		stats->SetDefault();
	}
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if ((*iter)->damaged){
			(*iter)->damaged=false;
			(*iter)->HP=stats->GetParametr((*iter)->Class,sHP);
			if ((*iter)->Class==DR)
				(*iter)->shots=2;
		}
	}
};

int Army::IsUnitWithAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	int result=0;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		if ((*iter)->HasAbility(in_UAT,f1,f2,f3))
			result++;
	return result;
};

Unit* Army::GetUnitWithAbility(UnitAbType in_UAT, int n, int f1, int f2, int f3){
	if (n<=0)
		return 0;
	Unit* result=0;
	int k=0;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if ((*iter)->HasAbility(in_UAT,f1,f2,f3))
			k++;
		if (k == n){
			result = *iter;
			break;
		}
	}
	return result;
};

int Army::ModUnitAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	int N = IsUnitWithAbility(in_UAT);
	for (int i=1;i<=N;i++){
		GetUnitWithAbility(in_UAT,i)->ModAbility(in_UAT,f1,f2,f3);
	};
	return 1;
};

int Army::AssignUnitAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	int N = IsUnitWithAbility(in_UAT);
	for (int i=1;i<=N;i++){
		GetUnitWithAbility(in_UAT,i)->AssignAbility(in_UAT,f1,f2,f3);
	};
	return 1;
};

int Army::AddUnitAbility(UnitType UT, UnitAbType in_UAT,int f1, int f2, int f3){
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		if ((*iter)->Class==UT)
			(*iter)->AddAbility(in_UAT,f1,f2,f3);
	return 1;
};

int Army::DeleteUnitAbility(UnitAbType in_UAT){
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		(*iter)->DeleteAbility(in_UAT);
	return 1;
};

Army* FindAllyArmy(Player* player, Hex* hex, Planet* planet){
	Army* result = 0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetOwner()==player)&&((*aiter)->GetHex()==hex)&&((*aiter)->GetPlanet()==planet)){
			result = *aiter;
			break;
		}
	}
	return result;
};

Army* FindOpponentArmy(Army* army){
	Army* result = 0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetOwner()!=army->GetOwner())&&((*aiter)->GetHex()==army->GetHex())&&((*aiter)->GetPlanet()==army->GetPlanet())){
			result = *aiter;
			break;
		}
	}
	return result;
};

Army* NewArmy(Player* player, Hex* hex, Planet* planet){
	Army* army = new Army(player, hex, planet);
	_Armies.push_back(army);
	return _Armies.back();
};

int Army::IsFreePlace(Unit *car, Unit* pas){
	if (!car->HasAbility(uaCarrier))
		return 0;
	if (!pas->HasAbility(uaCarried))
		return 0;
	if ((car->HasAbility(uaUnlimGF))&&(pas->HasAbility(uaInfantry)))
		return 1;
	int CarryCap=0;
	UnitAbility cartype = car->GetAbility(uaCarrier);
	if (cartype.field1>0)
		CarryCap = cartype.field1;
	if (cartype.field2>0)
		CarryCap = cartype.field2;
	if (cartype.field3>0)
		CarryCap = cartype.field3;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		if ((*iter)->carrier==car)
			CarryCap--;
	return CarryCap;
};

int Army::FighterCapacity(Unit* unit){
	if (GetPlanet()!=0)
		return 0;
	Unit* car;
	Army* tarmy;
	int FGcap=0;
	int GFcap=0;
	int STcap=0;
	int result=0;
	UnitAbility UA;
	int fighters = IsUnitWithAbility(uaFighter);
	for (int i=1; i<=IsUnitWithAbility(uaFighter); i++)
		if (GetUnitWithAbility(uaFighter,i)->HasAbility(uaKilled))
			fighters--;
	if (fighters>0){
		for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
			if (((*iter) != unit)&&(!(*iter)->HasAbility(uaKilled))){
				if ((*iter)->HasAbility(uaCarrier)){
					UA=(*iter)->GetAbility(uaCarrier);
					STcap+=UA.field1;
					FGcap+=UA.field2;
					GFcap+=UA.field3;
				}
				if ((*iter)->HasAbility(uaCarried)){
					if ((*iter)->HasAbility(uaFighter)){
						if ((*iter)->carrier!=0){
							cout<<"Fighter in carrier!";
						}
					}
					else{
						if ((*iter)->HasAbility(uaInfantry)){
							if ((*iter)->carrier!=0){
								car=(*iter)->carrier;
								if ((car->HasAbility(uaCarrier))&&(!car->HasAbility(uaKilled))){
									UA=car->GetAbility(uaCarrier);
									if (UA.field3>0)
										GFcap--;
									if ((UA.field1>0)&&(!car->HasAbility(uaUnlimGF)))
										STcap--;
								}
							}
						}
						else {
							if ((*iter)->carrier!=0){
								car=(*iter)->carrier;
								if (car->HasAbility(uaCarrier)&&(!car->HasAbility(uaKilled))){
									UA=car->GetAbility(uaCarrier);
									if (UA.field1>0)
										STcap--;
								}
							}
						}
					}

				}
			}
		}
		for (int i=1; i<=MAX_PLANETS; i++){
			if (_armyHex->GetPlanet(i)!=0){
				tarmy = FindAllyArmy(_owner,_armyHex,_armyHex->GetPlanet(i));
				if (tarmy != 0){
					for (vector<Unit*>::iterator iter = tarmy->GetUnits()->begin(); iter != tarmy->GetUnits()->end(); iter++){
						if ((*iter)->HasAbility(uaCarrier))
							FGcap+=(*iter)->GetAbility(uaCarrier).field2;
					}
				}
			}
		}
	}
	result=FGcap+STcap;
	return result;
};

int Army::FreeStackSize(UnitType UT){
	int result=0;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++)
		if (((*iter)->Class == UT)&&((*iter)->carrier == 0))
			result++;
	return result;
};

void Army::RemoveKilledUnits(){
	while (IsUnitWithAbility(uaKilled,1))
		KillUnit(GetUnitWithAbility(uaKilled,1,1));
};

bool Army::IsUnitInArmy(Unit *unit){
	bool result=false;
	for (vector<Unit*>::iterator iter = _units.begin(); iter != _units.end(); iter++){
		if (*iter == unit){
			result=true;
			break;
		}
	}
	return result;
};

int Army::CheckFleetSupport(){
	int supply = FleetSupply();
	char str[127];
	Unit* unit = 0;
	int FSCC = _owner->GetCountersFS();
	bool todestroy = false;
	while (supply > FSCC){
		todestroy = true;
		sprintf(str,"Destroy units exceed your current Fleet Supply (%d), they need %d FS",_owner->GetCountersFS(),supply);
		unit = SelectDialogOneUnit(str,this,false,uaSupply);
		if ((unit!=0)&&(!unit->HasAbility(uaKilled))){
			unit->AddAbility(uaKilled);
			unit->DeleteAbility(uaSupply);
			supply = FleetSupply();
		}
		else
			continue;
	}
	if (todestroy)
		CombatInterface().DestroyUnit(this,GetUnitWithAbility(uaKilled,1,0));
	return 1;
}

int Army::SpaceRedistribute(Unit* unit){
	if (_armyPlanet != 0)
		return 1;
	int capS = 0, capI = 0, capF = 0;
	Unit* car = 0;
	int place = 0;
	int i;
	char buff[255];
	vector<Unit*> options;
	for (i = 1; i <= IsUnitWithAbility(uaCarrier); i++){
		car = GetUnitWithAbility(uaCarrier,i);
		capS = car->GetAbility(uaCarrier).field1;
		capF = car->GetAbility(uaCarrier).field2;
		capI = car->GetAbility(uaCarrier).field3;
		place = capS + capF + capI - GetPassengers(car).size();
		if (unit->HasAbility(uaInfantry)){
			if ((capS>0) || (capI>0) || car->HasAbility(uaUnlimGF)){
				options.push_back(car);
			}
		}
		else
			if (capS>0)
				options.push_back(car);
	}
	if (options.size() == 0){
		Log("Army::SpaceRedistribute : no place for unit");
		KillUnit(unit);
		return 0;
	}
	sprintf(buff,"Select carrier for %s produced in space",ShipsFull[unit->Class].c_str());
	_GrIn.InitChoise(buff,true);
	for (i = 0; i < options.size(); i++)
		_GrIn.AddOption(SHIPS_IMG[options[i]->Class],_Info.UnitInfo(options[i],this));
	vector<int> ret = _GrIn.LaunchChoise();
	if (ret.size() == 0){
		Log("Army::SpaceRedistribute : was selected to kill unit");
		KillUnit(unit);
		return 0;
	}
	for (i = 0; i < ret.size(); i++)
		if (ret[i] == 1)
			SetPassenger(options[i],unit);
	if (unit->carrier == 0){
		Log("Army::SpaceRedistribute : failed to put unit in carrier");
		KillUnit(unit);
		return 0;
	}
	return 1;
}