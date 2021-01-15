//Zoldn: описание класса переехало в Strategy_Card.h,
//чтобы для абилок Ксча, а в дальнейшем и для экшон-карт,
//эти эффекты были видны и имели к ним доступ
/*class e_Diplomacy:public e_StratCard{
public:
	int DIPLOMACY_COUNTERS_COST;
	int DIPLOMACY_INF_COST;*/
void e_Diplomacy::reset(){
	DIPLOMACY_COUNTERS_COST = 1;
	DIPLOMACY_INF_COST = 3;
	UseP = false;
	UseS = false;
}

void e_Diplomacy::special(int n){
}
void e_Diplomacy::sc_S(Player*player){
	Log("e_Diplomacy::sc_S : start");
	int a=0, b=0,i,plans;
	vector<int> ret;
	vector<Planet*> options;
	ret.clear();
	Army* army;
	Planet* planet;
	char buff[255];
	sprintf(buff,"To use this ablility you have to pay %d SA counters",DIPLOMACY_COUNTERS_COST);
	_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
	if (player->GetCountersSA()<DIPLOMACY_COUNTERS_COST){
		_Interface.PrintThingPlayer(player->GetNumber()-1,"Sorry, not enough counters");
		return;
	}
	sprintf(buff,"Player %s uses Diplomacy (secondary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(buff);
	//player->TakeCounter(CC_strat,DIPLOMACY_COUNTERS_COST);
	sprintf(buff,"To use this ablility you have payed %d INF",DIPLOMACY_INF_COST);
	_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
	bool IsHexControl = false;
	for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++){
		if (HexController(*hiter) == player){
			IsHexControl = true;
			break;
		}
	}
	if (!IsHexControl){
		Log("e_Diplomacy::sc_S : No system control, can't use annex");
		return;
	}
	/*if (player->Pay(1,DIPLOMACY_INF_COST) == frr_none){
		_Interface.PrintThingPlayer(player->GetNumber()-1,"Didnt pay for annex");
		return;
	}*/
	sprintf(buff,"Player %s uses Peaceful Annexation",player->GetName().c_str());
	_Interface.PrintThingAll(buff);
	while (true){
		ret.clear();
		Log("e_Diplomacy::sc_S : select hex for diplomating");
		a=0;
		b=0;
		vector<int> tempvec = _GrIn.SysChoise("Choose system, adjacent to a system you control",true);
		if (tempvec.size() == 0)
			break;
		a = tempvec[0];
		b = tempvec[1];
		if (_Map.GetHexh(a,b) == 0)
			Eggog("e_Diplomacy::sc_S : bad hex selected");
		if (_Map.GetHexh(a,b)->GetPlanet(1) == 0){
			_Interface.PrintThingAll("No planets here");
			continue;
		}
		bool isHexControl = false;
		Log("e_Diplomacy::sc_S : check selection");
		for (i=0; i < _Map.GetHexh(a,b)->GetLinkedHexes()->GetLinkNumber(); i++)
			if (_Map.GetHexh(a,b)->GetLinkedHexes()->GetLink(_Map.GetHexh(a,b)->GetLinkedHexes()->GetLinkedHex(i))==ltBound)
				if (HexController(_Map.GetHexh(a,b)->GetLinkedHexes()->GetLinkedHex(i)) == player)
					isHexControl = true;
		if (!isHexControl){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"You have to choose system, adj to controlled by you");
			continue;
		}
		Log("e_Diplomacy::sc_S : go to selection of planet for diplomating");
		plans = 0;
		options.clear();
		for (i = 1; i <= MAX_PLANETS; i++){
			if ((_Map.GetHexh(a,b)->GetPlanet(i) != 0) && (_Map.GetHexh(a,b)->GetPlanet(i)->GetOwner() != player) && (!_Map.GetHexh(a,b)->GetPlanet(i)->HasState(psDiplomated))){
				army = FindArmy(a,b,0,false,_Map.GetHexh(a,b)->GetPlanet(i));
				if ((army == 0) || (army->isDefeated())){
					plans++;
					options.push_back(_Map.GetHexh(a,b)->GetPlanet(i));
				}
			}
		}
		if (!plans){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"No planets to use annexation");
			continue;
		}
		_GrIn.InitChoise("Select planet for annexation",true);
		for (vector<Planet*>::iterator piter = options.begin(); piter != options.end(); piter++)
			_GrIn.AddOption(PLANET_IMG,(*piter)->GetName());
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0){
			Log("e_Diplomacy::sc_S : cancel planet select");
			continue;
		}
		planet = 0;
		for (i = 0; i < ret.size(); i++)
			if (ret.at(i) == 1)
				planet = options.at(i);
		if (planet == 0)
			Eggog("e_Diplomacy::sc_S : selected planet is void");
		if (planet->GetName() == MECATOLREX){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Can't diplomate Mecatol");
			continue;
		}
		sprintf(buff,"Annex planet %s?",planet->GetName().c_str());
		if (SelectDialogYesNo(buff)){
			if (player->Pay(1,DIPLOMACY_INF_COST) == frr_normal){
				if (planet->GetOwner() != 0){
					sprintf(buff,"Your planet %s was annexed by player %s!",planet->GetName().c_str(),player->GetName().c_str());
					_Interface.PrintThingPlayer(planet->GetOwner()->GetNumber()-1,buff);
					planet->GetOwner()->DeCapture(planet);
				}
				sprintf(buff,"Player %s has annexed planet %s",player->GetName().c_str(),planet->GetName().c_str());
				_Interface.PrintThingAll(buff);
				player->Capture(planet);
				planet->AddState(psDiplomated);
				player->TakeCounter(CC_strat,DIPLOMACY_COUNTERS_COST);
				Log("e_Diplomacy::sc_S : diplomated");
				/*for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++)
					for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
						CheckTradeStations(*hiter,_Players[i]);*/
				CheckTradeStations();
				break;
			}
		}
		else{
			Log("e_Diplomacy::sc_S : diplomated cancel");
			continue;
		}
	}
	Log("e_Diplomacy::sc_S : end");
}

void e_Diplomacy::sc_P(Player*player){
	Log("e_Diplomacy::sc_P : begin");
	int *result,x,y;
	bool able;
	char buff[257];
	if (player->GetPlanetsList()->size() == 0){
		_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no planet! You can't use diplomacy!");
		Log("e_Diplomacy::sc_P : no way");
		return;
	}
	sprintf(buff,"Player %s uses Diplomacy (primary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(buff);
	bool IsHexControl = false;
	for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++){
		if (HexController(*hiter) == player){
			IsHexControl = true;
			break;
		}
	}
	sprintf(buff,"Player %s uses Demilitarized Zone",player->GetName().c_str());
	_Interface.PrintThingAll(buff);
	_GrIn.InitChoise("Choose eather a) or b)");
	_GrIn.AddOption(EMPTY_EVENT_IMG,"a) DMZ");
	if (IsHexControl)
		_GrIn.AddOption(EMPTY_EVENT_IMG,"b) Annex");
	vector<int> tempvec = _GrIn.LaunchChoise();
	if (tempvec.size() == 0)
		Eggog("e_Diplomacy::sc_P : wrong yes/no selection");
	if (tempvec[0] == 1){
		Log("e_Diplomacy::sc_P : selected DMZ");
		able = false;
		while(!able){
			vector<int> tempvec = _GrIn.SysChoise("Choose a system, containing a planet you control");
			x = tempvec[0];
			y = tempvec[1];
			able = false;
			for (int i=0;i<MAX_PLANETS;++i)
				if ((_Map.GetHexh(x,y)->GetPlanet(i+1)!=0)&&(_Map.GetHexh(x,y)->GetPlanet(i+1)->GetOwner() == player))
					able = true;
			if (able){
				sprintf(buff,"Use Demilitarized Zone on system %s?",_Map.GetHexh(x,y)->GetId().c_str());
				if (SelectDialogYesNo(buff)){
					Log("e_Diplomacy::sc_P : dmz assigned");
					for (int i=0;i<_GameStats.GetPlayersNumber();++i){
						if (_Players[i] != player){
							_Map.GetHexh(x,y)->SetCC(i+1);
						}
					}
				}
				else{
					Log("e_Diplomacy::sc_P : dmz assignation cancel");
					continue;
				}
			}
			else
				_Interface.PrintThingAll("There is no your planets in this system");
		}
	}
	else{
		Log("e_Diplomacy::sc_P : selected Annex");
		DIPLOMACY_COUNTERS_COST = 0;
		DIPLOMACY_INF_COST = 0;
		sc_S(player);
		reset();
	}
	Log("e_Diplomacy::sc_P : end");
}

e_Diplomacy::e_Diplomacy(){
	nt_strload(id,"Diplomacy\0");
	type = Diplomacy;
	nt_strload(image,STRAT_B_PATH[type]);
	reset();
}

bool e_Diplomacy::GetQ(GameEffectQs queue){
	if (queue==eq_AAA)
		return true;
	return false;
}
GameEffect* e_Diplomacy::Clone(){
	return new e_Diplomacy(*this);
}
string e_Diplomacy::Save(){
	return string();
}
void e_Diplomacy::Load(std::string str){}