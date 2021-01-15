int ScuttleUnits(Hex* hex, Player* player){
	vector<int> ret;
	vector<Army*> places;
	vector<UnitArmy> options;
	Army* army;
	int units;
	UnitArmy UA;
	int i,j;
	char buff[255];
	char str[255];
	places.clear();
	army = FindAllyArmy(player,hex);
	if (army != 0)
		places.push_back(army);
	for (i = 1; i <= MAX_PLANETS; i++){
		if (hex->GetPlanet(i) != 0){
			army = FindAllyArmy(player,hex,hex->GetPlanet(i));
			if (army != 0)
				places.push_back(army);
		}
	}
	units = 0;
	for (vector<Army*>::iterator aiter = places.begin(); aiter != places.end(); aiter++)
		units += (*aiter)->IsUnitWithAbility(uaNone);
	if (units == 0){
		_Interface.PrintThingPlayer(player->GetNumber() - 1,"No units to scuttle in this system");
		return 0;
	}
	options.clear();
	_GrIn.InitChoise("Select units to scuttle",true,true,true);
	for (vector<Army*>::iterator aiter = places.begin(); aiter != places.end(); aiter++){
		for (i = GF; i <= DCK; i++){
			if ((*aiter)->StackSize((UnitType)i)){
				if ((*aiter)->GetUnit((UnitType)i,1)->HasAbility(uaMultiple)){
					sprintf(buff,"%s x%d",ShipsShort[i].c_str(),(*aiter)->StackSize((UnitType)i));
					if ((*aiter)->GetPlanet() != 0){
						sprintf(str,"(%s)",(*aiter)->GetPlanet()->GetName().c_str());
						strcat(buff,str);
					}
					_GrIn.AddNumerical(SHIPS_IMG[i],buff);
					UA.army = *aiter;
					UA.unit = (*aiter)->GetUnit((UnitType)i,1);
					UA.selected = false;
					options.push_back(UA);
				}
				else{
					for (j = 1; j <= (*aiter)->StackSize((UnitType)i); j++){
						sprintf(buff,"%s",ShipsShort[i].c_str(),(*aiter)->StackSize((UnitType)i));
						if ((*aiter)->GetUnit((UnitType)i,j)->HasAbility(uaSustain))
							if ((*aiter)->GetUnit((UnitType)i,j)->GetAbility(uaSustain).field2 == 0)
								strcat(buff,"(dmg)");
						if ((*aiter)->GetPlanet() != 0){
							sprintf(str,"(%s)",(*aiter)->GetPlanet()->GetName().c_str());
							strcat(buff,str);
						}
						_GrIn.AddNumerical(SHIPS_IMG[i],buff);
						UA.army = *aiter;
						UA.unit = (*aiter)->GetUnit((UnitType)i,j);
						UA.selected = false;
						options.push_back(UA);
					}
				}
			}
		}
	}
	ret = _GrIn.LaunchChoise();
	if (ret.size() == 0)
		return 0;
	units = 0;
	for (i = 0; i < ret.size(); i++){
		if (ret.at(i) > 0){
			if (options.at(i).unit->HasAbility(uaMultiple)){
				if (options.at(i).army->StackSize(options.at(i).unit->Class) < ret.at(i))
					ret.at(i) = options.at(i).army->StackSize(options.at(i).unit->Class);
				for (j = 1; j <= ret.at(i); j++)
					options.at(i).army->GetUnit(options.at(i).unit->Class,j)->AddAbility(uaKilled);
				if (!options.at(i).unit->HasAbility(uaInfantry) && !options.at(i).unit->HasAbility(uaFighter))
					units += ret.at(i);
			}
			else{
				options.at(i).unit->AddAbility(uaKilled);
				units++;
			}
		}
	}
	for (vector<Army*>::iterator aiter = places.begin(); aiter != places.end(); aiter++)
		if ((*aiter)->IsUnitWithAbility(uaKilled))
			CombatInterface().DestroyUnit(*aiter,(*aiter)->GetUnitWithAbility(uaKilled,1));
	player->CheckFleets();
	return units;
};

e_Politic* ChoosePolitic(Player*player){
	int * result,i;
	e_Politic *  ret;
	std::deque<e_Politic*>::iterator curpol = player->_politics.begin();
	if (player->_politics.size() == 0)
		return 0;
	_GrIn.InitChoise("Choose Politic Card");
	while (curpol < player->_politics.end()){
		_GrIn.AddOption(EMPTY_EVENT_IMG,(*curpol)->GetId().c_str());//Zoldn's ".c_str()"
		++curpol;
	}
	vector<int> tempvec = _GrIn.LaunchChoise();
	if (tempvec.size() != 0)
		result = &tempvec[0];
	curpol = player->_politics.begin();
	i=0;
	while(result[i]!=1){
		++curpol;
		++i;
	}
	ret = (e_Politic*)player->_politics[i]->Clone();
	player->_politics.erase(curpol);
	return ret;
}

/*void CheckTradeStations(Hex* hex, Player* player){
	char str[255];
	Army* army = FindArmy(hex,player);
	for (int i=1; i<=MAX_PLANETS; i++){
		if ((hex->GetPlanet(i) != 0) && (hex->GetPlanet(i)->GetSpecial() == TradeStation)){
			if (hex->GetPlanet(i)->GetOwner()==0)
				sprintf(str,"Planet %s changes owner from neutral to player %s",hex->GetPlanet(i)->GetName().c_str(),player->GetName().c_str());
			else
				if (hex->GetPlanet(i)->GetOwner() != player)
					sprintf(str,"Planet %s changes owner from player %s to player %s",hex->GetPlanet(i)->GetName().c_str(),hex->GetPlanet(i)->GetOwner()->GetName().c_str(),player->GetName().c_str());
			if (hex->GetPlanet(i)->GetOwner() != player)
				_Interface.PrintThingAll(str);
			player->Capture(hex->GetPlanet(i));
		}
	}
}*/

void CheckTradeStations(){
	char str[256];
	int i;
	Army* army;
	Player* player;
	Planet* planet;
	for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++){
		for (i=1; i<=MAX_PLANETS; i++){
			if ((*hiter)->GetPlanet(i) != 0){
				planet = (*hiter)->GetPlanet(i);
				if (planet->GetSpecial() == TradeStation){
					army = FindAnyArmy(*hiter);
					if ((army == 0) || army->isDefeated())
						player = 0;
					else
						player = army->GetOwner();
					if ((planet->GetOwner() != player) && (player != 0)){
						if (planet->GetOwner() != 0){
							sprintf(str,"Trade Station %s changes owner from player %s to player %s",planet->GetName().c_str(),planet->GetOwner()->GetName().c_str(),player->GetName().c_str());
							_Interface.PrintThingAll(str);
							planet->GetOwner()->DeCapture(planet);
							player->Capture(planet);
						}
						else{
							sprintf(str,"Trade Station %s changes owner from neutral to player %s",planet->GetName().c_str(),player->GetName().c_str());
							_Interface.PrintThingAll(str);
							player->Capture(planet);
						}
					}
				}
			}
		}
	}
}