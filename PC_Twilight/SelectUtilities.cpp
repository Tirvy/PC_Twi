bool SelectDialogYesNo(const string str){
	_GrIn.InitChoise(str);
	_GrIn.AddOption(YESNO_IMG[0],"Yes");
	_GrIn.AddOption(YESNO_IMG[1],"No");
	vector<int> tempvec = _GrIn.LaunchChoise();
	int* r = &tempvec[0];
	if (r[0]==1)
		return true;
	else
		return false;
};

int SelectDialogPlanetInSystem(const string str, Hex* hex, Player* curPlayer, bool* mask, int planets){
	bool isPlanet=false;
	int choise = 0;
	int* r;
	int k;
	int result = 0;
	for (int i=0; i<planets; i++){
		if ((hex->GetPlanet(i+1)!=0)&&(mask[i]))
			isPlanet=true;
	}
	if (isPlanet){
		_GrIn.InitChoise(str,true);
		for (int i=0; i<planets; i++){
			if ((hex->GetPlanet(i+1)!=0)&&(mask[i])){
				choise++;
				if (hex->GetPlanet(i+1)->GetOwner()==curPlayer)
					_GrIn.AddOption(PLANET_IMG,hex->GetPlanet(i+1)->GetName().c_str());
				else
					if (hex->GetPlanet(i+1)->GetOwner()==0)
						_GrIn.AddOption(PLANET_IMG,hex->GetPlanet(i+1)->GetName().c_str());
					else
						_GrIn.AddOption(PLANET_IMG,hex->GetPlanet(i+1)->GetName().c_str());
			};
		};
		vector<int> tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() != 0){
			r = &tempvec[0];
			k=-1;
			//if (r!=0)
			for (int i=0; i<planets; i++){
				if (mask[i]){
					k++;
					if (r[k]==1)
						result = i+1;
				};
			};
		}
	};
	return result;
};

int SelectDialogPlanetInSystem(Hex* hex,Player* player,bool own){
	bool isPlanet=false;
	int choise = 0;
	int* r;
	int k;
	int result = 0;
	char buff[64];
	for (int i=0; i<MAX_PLANETS; i++){
		if (hex->GetPlanet(i+1)!=0)
			isPlanet=true;
	}
	if (!isPlanet)
		return -1;
	while (true){
		sprintf(buff,"Choose planet in {%s}",hex->GetId().c_str());
		_GrIn.InitChoise(buff,true);
		for (int i=0; i<MAX_PLANETS; i++){
			if ((hex->GetPlanet(i+1)!=0)&&((player==0)||((hex->GetPlanet(i+1)->GetOwner() == player) == own))){
				choise++;
				_GrIn.AddOption(PLANET_IMG,hex->GetPlanet(i+1)->GetName().c_str());
			}
		}
		vector<int> tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() == 0)
			return 0;
		r = &tempvec[0];
		k=0;
		if (r==0)
			continue;
		for (int i=0; i<MAX_PLANETS; i++){
			if ((hex->GetPlanet(i+1)!=0)&&((player==0)||((hex->GetPlanet(i+1)->GetOwner() == player) == own))){
				if (r[k]==1)
					return i+1;
				++k;
			}
		}
	}
}
Unit* SelectDialogOneUnit(const string str, Army* army, bool pass, UnitAbType UAT, int f1, int f2, int f3){
	int N = army->IsUnitWithAbility(UAT,f1,f2,f3);
	if (N==0)
		return 0;
	char str1[127];
	char str2[127];
	int mask[MAX_UNIT];
	for (int i=0; i<MAX_UNIT; i++)
		mask[i]=0;
	Unit* result = 0;
	int options=0;
	Unit* unit;
	int StackSize = 0;
	_GrIn.InitChoise(str,pass);
	bool FighterButton = false;
	for (int i=1; i<=N; i++){
		unit = army->GetUnitWithAbility(UAT,i,f1,f2,f3);
		if (!unit->HasAbility(uaMultiple)){
			_GrIn.AddOption(SHIPS_IMG[unit->Class],_Info.UnitInfo(unit,army));
			options++;
		}
		else
			mask[unit->Class]+=1;
	}
	for (UnitType UT=GF; UT<MAX_UNIT; UT=(UnitType)((int)UT+1)){
		if (mask[UT]){
			sprintf(str1,ShipsShort[UT].c_str());
			sprintf(str2," x%d",mask[UT]);
			strcat(str1,str2);
			_GrIn.AddOption(SHIPS_IMG[UT],string(str1));
			options++;
		};
	};
	//int* out = new int[options];
	vector<int> tempvec = _GrIn.LaunchChoise();
	int* r = 0;
	if (tempvec.size() != 0)
		r = &tempvec[0];
	/*for (int i=0; i<options;i++){
		out[i]=r[i];
		cout<<"SelectDialogOneUnit debug sayz: out[i]="<<out[i]<<endl;
	};*/
	int k=-1;
	for (int i=0; i<MAX_UNIT; i++)
		mask[i]=0;
	if (r==0)
		result=0;
	else{
		for (int i=1; i<=N; i++){
			unit = army->GetUnitWithAbility(UAT,i,f1,f2,f3);
			if (!unit->HasAbility(uaMultiple)){
				k++;
				if (r[k]==1){
					result=unit;
					break;
				}
			}
			else
				mask[unit->Class]+=1;
		}
		for (UnitType UT=GF; UT<MAX_UNIT; UT=(UnitType)((int)UT+1)){
			if (mask[UT]){
				k++;
				if (r[k]==1){
					for (int j = 1; j <= army->StackSize(UT); j++){
						if (!army->GetUnit(UT,j)->HasAbility(uaKilled)){
							result=army->GetUnit(UT,j);
							break;
						}
					}
				}
			}
		}
	}
	return result;
}; 


PowDEV<Unit,Army> SelectDialogOneUnit(const string str, int x, int y, UnitAbType UAT, bool pass, bool NotInCarrier, Unit* car){
	int N = 0;// = army->IsUnitWithAbility(UAT);
	//if (N==0)
	//	return 0;
	char str1[127];
	char str2[127];
	int m, j=0;
	int incarrier=0;
	int mask[MAX_UNIT];
	Army *army[MAX_PLANETS+1];
	Army* tarmy;
	tarmy = FindArmy(x,y,0);
	for (int i = 0; i<MAX_PLANETS+1;++i)
		army[i] = 0;
	if (tarmy!=0){
		army[j] = tarmy;
		N += army[j]->IsUnitWithAbility(UAT);
		for (int z=1; z<=N; z++){
			if (NotInCarrier&&(army[j]->GetUnitWithAbility(UAT,z)->carrier==car))
				incarrier++;
		}
		N-=incarrier;
		++j;
	}
	for (int i = 0; (i<MAX_PLANETS)&&(_Map.GetHexh(x,y)->GetPlanet(i+1)!=0);++i){
		tarmy = FindArmy(x,y,0,false,_Map.GetHexh(x,y)->GetPlanet(i+1));
		if (tarmy!=0){
			army[j] = tarmy;
			N += army[j]->IsUnitWithAbility(UAT,1);
			++j;
		}
	}
	if (N==0)
		return PowDEV<Unit,Army> (0,0);
	for (int i=0; i<MAX_UNIT; i++){
		mask[i]=0;
	};
	Unit* result = 0;
	Army* resarmy = 0;
	int options=0;
	Unit* unit;
	int StackSize = 0;
	_GrIn.InitChoise(str,pass);
	bool FighterButton = false;
	for (m = 0;m < j;++m){
		for (int i=1; i<=N; i++){
			unit = army[m]->GetUnitWithAbility(UAT,i);
			if (unit == 0)
				break;
			if (NotInCarrier&&(unit->carrier==car))
				continue;
			if (!unit->HasAbility(uaMultiple)){
				_GrIn.AddOption(SHIPS_IMG[unit->Class],_Info.UnitInfo(unit,army[m]));
				options++;
			}
			else
				mask[unit->Class]+=1;
		}
		for (UnitType UT=GF; UT<MAX_UNIT; UT=(UnitType)((int)UT+1)){
			if (mask[UT]){
				sprintf(str1,ShipsShort[UT].c_str());
				sprintf(str2," x%d",mask[UT]);
				strcat(str1,str2);
				if (army[m]->GetPlanet()!=0)
					sprintf(str2," {%s}",army[m]->GetPlanet()->GetName());
				else
					sprintf(str2," {%s}",_Map.GetHexh(x,y)->GetId());
				strcat(str1,str2);
				_GrIn.AddOption(SHIPS_IMG[UT],str1);
				options++;
			};
		}
		for (int i=0; i<MAX_UNIT; i++){
			mask[i]=0;
		}
	}
	vector<int> tempvec = _GrIn.LaunchChoise();
	int* out = 0;
	if (tempvec.size() != 0)
		out = &tempvec[0];
	if (out == 0)
		return PowDEV<Unit,Army> (0,0);
	int k=-1;
	if (out==0){
		cout<<"SelectDialogOneUnitzZZ: bugget";
		result = 0;
		resarmy = 0;
	}
	else{
		for (m = 0;m < j;++m){
			for (int i=1; i<=N; i++){
				unit = army[m]->GetUnitWithAbility(UAT,i);
				if (unit == 0)
					break;
				if (NotInCarrier&&(unit->carrier==car))
					continue;
				if (!unit->HasAbility(uaMultiple)){
					k++;
					if (out[k]==1){
						resarmy = army[m];
						result=unit;
						break;
					};
				}
				else
					mask[unit->Class]+=1;
			}
			for (UnitType UT=GF; UT<MAX_UNIT; UT=(UnitType)((int)UT+1)){
				if (mask[UT]){
					k++;
					if (out[k]==1){
						resarmy = army[m];
						if (NotInCarrier){
							int z=1;
							while (z<=army[m]->StackSize(UT)){
								if (army[m]->GetUnit(UT,z)->carrier!=car){
									result=army[m]->GetUnit(UT,z);
									break;
								}
								else
									z++;
							};
							if (result==0)
								Interface().PrintError("Can't find unit to pick up");
						}
						else
							result=army[m]->GetUnit(UT);
						break;
					};
				};
			}
			for (int i=0; i<MAX_UNIT; i++){
				mask[i]=0;
			}
		}
	};
	
	return PowDEV<Unit,Army> (result,resarmy);
};
vector<int> SelectDialogOwnedPlanet(const string str, Player* player, bool multiple, int openonly, bool passable, bool goods){
	char buff[64];
	if (multiple){
		_GrIn.InitChoise(str,passable,true,multiple);
	}
	else{
		_GrIn.InitChoise(str,passable);
	}
	cout<<"Select dialog owned planet"<<endl;
	for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
		if ((openonly == 1)&&(!player->IsPlanetOpen(*piter))){
			continue;
		}
		else if ((openonly == 2)&&(player->IsPlanetOpen(*piter))){
			continue;
		}
		sprintf(buff,"{%s} %d/%d",(*piter)->GetName().c_str(),(*piter)->GetRes(),(*piter)->GetInf());
		if (openonly == 0){
			if ((*piter)->HasState(psExhausted))
				strcat(buff," E");
			else
				strcat(buff," +");
		}
		if (multiple)
			_GrIn.AddNumerical(PLANET_IMG,buff);
		else
			_GrIn.AddOption(PLANET_IMG,buff);
	}
	if (goods){
		sprintf(buff,"Trade Goods: %d",player->GetGoods());
		if (multiple)
			_GrIn.AddNumerical(GOODS_IMG,buff);
		else
			_GrIn.AddOption(GOODS_IMG,buff);
	}
	return _GrIn.LaunchChoise();
}

Player * SelectDialogPlayer(const string str, Player* exept){
	int * res,j;
	_GrIn.InitChoise(str);
	for (int i=0;i<_GameStats.GetPlayersNumber();++i){
		if (_Players[i]!=exept)
			_GrIn.AddOption(EMPTY_EVENT_IMG,_Players[i]->GetName());
	}
	vector<int> tempvec = _GrIn.LaunchChoise();
	res = &tempvec[0];
	j = 0;
	for (int i=0;i<_GameStats.GetPlayersNumber();++i){
		if (exept == _Players[i])
			continue;
		if (res[j] == 1)
			return _Players[i];
		++j;
	}
	return 0;
}

PowDouble<TradeRoute,Player> SelectDialogTradeRoute(bool free_made, TradeRoute* exclude){
	int total = MAX_TRADES * _GameStats.GetPlayersNumber();
	int i,j,*result;
	TradeRoute * troute;
	char buff[64];
	_GrIn.InitChoise("Choose route",true);
	for (i = 0;i<total;++i){
		troute = _Players[i/MAX_TRADES]->GetTrade(i % MAX_TRADES);
		if ((troute!=0)&&(troute!=exclude)&&((troute->owner == _Players[i/MAX_TRADES]) != free_made)){
			if (free_made)
				sprintf(buff,"%d of {%s} with {%s}",troute->power,troute->owner->GetName().c_str(),_Players[i/MAX_TRADES]->GetName().c_str());
			else
				sprintf(buff,"%d of {%s}",troute->power,troute->owner->GetName().c_str());
			_GrIn.AddOption(EMPTY_EVENT_IMG,buff);
		}
	}
	vector<int> tempvec = _GrIn.LaunchChoise();
	if (tempvec.size() == 0)
		return PowDouble<TradeRoute,Player>(0,0);
	result = &tempvec[0];
	j = 0;
	for (i = 0;i<total;++i){
		troute = _Players[i/MAX_TRADES]->GetTrade(i % MAX_TRADES);
		if ((troute!=0)&&(troute!=exclude)&&((troute->owner == _Players[i/MAX_TRADES]) != free_made)){
			if (result[j] == 1)
				return PowDouble<TradeRoute,Player>(troute,_Players[i/MAX_TRADES]);
			++j;
		}
	}
	Eggog("SelectDialogTradeRoute: no route");
	return PowDouble<TradeRoute,Player>();
}
vector<int> SelectDialogGroupUnits(const string str, Army* army, bool pass, UnitAbType UAT, int f1, int f2, int f3){
	int N = army->IsUnitWithAbility(UAT,f1,f2,f3);
	if (N==0)
		return vector<int>();
	int options=0;
	Unit* unit;
	int StackSize = 0;
	_GrIn.InitChoise(str,pass,true,true);
	for (int i=1; i<=N; i++){
		unit = army->GetUnitWithAbility(UAT,i,f1,f2,f3);
		if (!unit->HasAbility(uaMultiple)){
			_GrIn.AddNumerical(SHIPS_IMG[unit->Class],_Info.UnitInfo(unit,army));
			options++;
		}
	};
	return _GrIn.LaunchChoise();
}

Roll* SelectDialogRoll(Player* player, Roll* rolls, int count){
	if ((0==count)||(0==rolls))
		return 0;
	Roll* result = 0;
	char stra[127];
	int power[DICE];
	int options=0;
	int* r;
	int* s;
	int k;
	int powerchoise=-1;
	for (int i=0; i<DICE; i++)
		power[i]=0;
	for (int i=0; i<count; i++){
		if (!rolls[i].isRerolled){
			if ((rolls[i].power>=1)&&(rolls[i].power<=DICE))
				power[rolls[i].power-1]=power[rolls[i].power-1]+1;
			if (rolls[i].power<1)
				power[0]=power[0]+1;
			if (rolls[i].power>DICE)
				power[DICE-1]=power[DICE-1]+1;
		}
	}
	_GrIn.InitChoise("Select power of rerolled dice",true);
	for (int i=0; i<DICE; i++){
		if (power[i]){
			sprintf(stra,"%d+",i+1);
			_GrIn.AddOption(DICE_IMG,stra);
			options++;
		}
	}
	vector<int> tempvec = _GrIn.LaunchChoise();
	if (tempvec.size() != 0)
		r = &tempvec[0];
	if (r!=0){
		k=-1;
		for (int i=0; i<DICE; i++){
			if (power[i]){
				k++;
				if (r[k]==1){
					powerchoise=i+1;
					break;
				}
			}
		}
		_GrIn.InitChoise("Select dice to reroll",true);
		options=0;
		for (int i=0; i<count; i++){
			if ((rolls[i].power==powerchoise)&&(!rolls[i].isRerolled)){
				sprintf(stra,"%s[%d]",ShipsShort[rolls[i].unit->Class].c_str(),rolls[i].value);
				_GrIn.AddOption(SHIPS_IMG[rolls[i].unit->Class],stra);
				options++;
			}
		}
		vector<int> tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() != 0)
			s = &tempvec[0];
		if (s!=0){
			k=-1;
			for (int i=0; i<count; i++){
				if ((rolls[i].power==powerchoise)&&(!rolls[i].isRerolled)){
					k++;
					if (s[k]==1){
						result=(&(rolls[i]));
					}
				}
			}
		}		
	}
	return result;
};

TechType SelectDialogTech(const string str, Player* player, int* prices){
	Log("SelectDialogTech : start");
	TechType result = MAX_TECH;
	TechTree color;
	int* r = 0;
	int k=-1;
	char stra[127];
	_GrIn.InitChoise(str,true);
	for (TechType TT=ttHylar; TT<MAX_TECH; TT=(TechType)((int)TT+1)){
		if (prices[TT]>=0){
			sprintf(stra,"%s (%d res)",_GameStats.GetTechDeck()->at(TT)->GetName().c_str(),prices[TT]);
			color = _GameStats.GetTechDeck()->at(TT)->GetColor();
			if (color<RaceTech)
				_GrIn.AddOption(TECHS_IMG[color],stra);
			else
				_GrIn.AddOption(EMPTY_EVENT_IMG,stra);
		}
	}
	vector<int> tempvec = _GrIn.LaunchChoise();
	for (vector<int>::iterator it = tempvec.begin(); it != tempvec.end(); it++)
		cout<<"SelectDialogTech tempvec "<<*it<<endl;
	if (tempvec.size() != 0){
		r = &tempvec[0];
		Log("SelectDialogTech : selected tech");
	}
	else
		Log("SelectDialogTech : selected pass");
	if (r!=0){
		for (TechType TT = ttHylar; TT<MAX_TECH; TT=(TechType)((int)TT+1)){
			if (prices[TT]>=0){
				k++;
				if (r[k]==1)
					result=TT;
			}
		}
	}
	Log("SelectDialogTech : end");
	return result;
};

e_Objective* SelectDialogObjective(const string str, Player* player, bool publ, bool secr){
	e_Objective* result = 0;
	e_Objective* obj = 0;
	//list<e_Objective*>::iterator effects = player->_PlayerObjectives.begin();
	list<e_Objective*>::iterator iter;
	int* r;
	int k;
	bool isObjectivesToFulfill = false;
	//for (iter = player->_PlayerObjectives.begin(); iter != player->_PlayerObjectives.end(); ++iter){
	for (list<GameEffect*>::iterator iter = player->_PlayerGameEffect.begin(); iter != player->_PlayerGameEffect.end(); iter++){
		if (((e_Objective*)(*iter))->GetQ(eq_Objective)){
			if ((((e_Objective*)(*iter))->isFulfill)&&(!((e_Objective*)(*iter))->isDone)&&((((e_Objective*)(*iter))->isSecret&&secr)||(!((e_Objective*)(*iter))->isSecret&&publ))){
				isObjectivesToFulfill = true;
				break;
			}
		}
	}
	if (isObjectivesToFulfill){
		_GrIn.InitChoise(str,true);
		//for (iter = player->_PlayerObjectives.begin(); iter != player->_PlayerObjectives.end(); ++iter){
		for (list<GameEffect*>::iterator iter = player->_PlayerGameEffect.begin(); iter != player->_PlayerGameEffect.end(); iter++){
			if (((e_Objective*)(*iter))->GetQ(eq_Objective)){
				if ((((e_Objective*)(*iter))->isFulfill)&&(!((e_Objective*)(*iter))->isDone)&&((((e_Objective*)(*iter))->isSecret&&secr)||(!((e_Objective*)(*iter))->isSecret&&publ))){
					_GrIn.AddOption(OBJ_IMG[((e_Objective*)(*iter))->GetType()],((e_Objective*)(*iter))->GetShortReqs());
				}
			}
		}
		vector<int> tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() != 0)
			r = &tempvec[0];
		if (r!=0){
			k=-1;
			//for (iter = player->_PlayerObjectives.begin(); iter != player->_PlayerObjectives.end(); ++iter){
			for (list<GameEffect*>::iterator iter = player->_PlayerGameEffect.begin(); iter != player->_PlayerGameEffect.end(); iter++){
				if (((e_Objective*)(*iter))->GetQ(eq_Objective)){
					if ((((e_Objective*)(*iter))->isFulfill)&&(!((e_Objective*)(*iter))->isDone)&&((((e_Objective*)(*iter))->isSecret&&secr)||(!((e_Objective*)(*iter))->isSecret&&publ))){
						k++;
						if (r[k]==1)
							//result = *iter;
							result = (e_Objective*)(*iter);
					}
				}
			}
		}
	}
	return result;
};

e_ActionCard* SelectDialogActionCard(string str, Player* player, bool pass){
	list<GameEffect*>::iterator iter;
	e_ActionCard* result = 0;
	vector<int> ret;
	int k;
	if (player->GetActionsNumber()){
		_GrIn.InitChoise(str,pass);
		for (iter = player->_PlayerGameEffect.begin(); iter != player->_PlayerGameEffect.end(); iter++)
			if ((*iter)->GetQ(eq_ActionCard))
				_GrIn.AddOption(ACTION_CARD,((e_ActionCard*)(*iter))->GetName());
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			return result;
		k = -1;
		for (iter = player->_PlayerGameEffect.begin(); iter != player->_PlayerGameEffect.end(); iter++){
			if ((*iter)->GetQ(eq_ActionCard)){
				k++;
				if (ret[k] == 1){
					result = (e_ActionCard*)(*iter);
					break;
				}
			}
		}
	}
	return result;
};

Planet* SelectDialogPlanet(const string str, const string strhex, Hex* hex, Player* active, bool passable, bool friendly, bool neutral, bool hostile, bool noHS, bool TradeStations){
	Planet* result = 0;
	int flag = 0;
	int i;
	vector<Planet*> options;
	Hex* h = hex;
	vector<int> ret; 
	bool check;
	while (true){
		options.clear();
		if (hex == 0){
			ret = _GrIn.SysChoise(strhex,passable);
			if (ret.size() == 0)
				return 0;
			h = _Map.GetHexh(ret[0],ret[1]);
		}
		else
			h = hex;
		if (noHS && (hex == 0)){
			check = false;
			for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
				if ((_Players[i]->HS == h) || (_Players[i]->eHS == h))
					check = true;
			if (check){
				_Interface.PrintThingPlayer(active->GetNumber()-1,"You can't select Home System");
				continue;
			}
		}
		for (i = 1; i <= MAX_PLANETS; i++){
			if (h->GetPlanet(i) != 0){
				if ((h->GetPlanet(i)->GetSpecial() == TradeStation) && !TradeStations)
					continue;
				if ((h->GetPlanet(i)->GetOwner() == active) && friendly)
					options.push_back(h->GetPlanet(i));
				if ((h->GetPlanet(i)->GetOwner() == 0) && neutral)
					options.push_back(h->GetPlanet(i));
				if ((h->GetPlanet(i)->GetOwner() != active) && (h->GetPlanet(i)->GetOwner() != 0) && hostile)
					options.push_back(h->GetPlanet(i));
			}
		}
		if (options.size() == 0){
			if (hex == 0){
				_Interface.PrintThingPlayer(active->GetNumber()-1,"No planet can be chosen in this system");
				continue;
			}
			else
				return 0;
		}
		_GrIn.InitChoise(str,passable);
		for (i = 0; i < options.size(); i++)
			_GrIn.AddOption(PLANET_IMG,options[i]->GetName());
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			if (hex == 0)
				continue;
			else
				return 0;
		for (i = 0; i < options.size(); i++)
			if (ret[i] == 1)
				result = options[i];
		break;
	}
	return result;
};