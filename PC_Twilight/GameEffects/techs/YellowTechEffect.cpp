//желтые технологии
//graviton laser system
e_GravitonLaserSystem::e_GravitonLaserSystem(){
	id = "GravitonLaserSystem";
	name = "Graviton Laser System";
	description = "PDS get one re-roll for each missed combat roll";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttGravitonLaserSystem;
	prereq1 = ttDeepSpaceCannon;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_GravitonLaserSystem::GetQ(GameEffectQs queue){
	if (queue==eq_AfterRollingDices)
		return true;
	return false;
}
GameEffectRets e_GravitonLaserSystem::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Roll* rolls = EP.rolls;
	int rollNumber = EP.rollNumber;
	int oldthrow, newthrow;
	char str[127];
	for (int i=0; i<rollNumber; i++){
		if ((rolls[i].unit->Class==PDS)&&(rolls[i].value<rolls[i].power)){
			oldthrow=rolls[i].value;
			newthrow=rand()%10+1;
			_Interface.PrintThingAll("Reroll missed shot of PDS by Graviton Laser System");
			sprintf(str,"%d --> %d",oldthrow,newthrow);
			_Interface.PrintThingAll(str);
			rolls[i].value=newthrow;
		};
	};
	return er_none;
}
GameEffect* e_GravitonLaserSystem::Clone(){
	return new e_GravitonLaserSystem(*this);
}
string e_GravitonLaserSystem::Save(){
	return string();
}
void e_GravitonLaserSystem::Load(std::string str){}
//enviro
e_EnviroCompensator::e_EnviroCompensator(){
	id = "EnviroCompensator";
	name = "Enviro Compensator";
	description = "Space Docks receive +1 to production capacity";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttEnviroCompensator;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_EnviroCompensator::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeBuild)
		return true;
	return false;
}
GameEffectRets e_EnviroCompensator::Execute(ExecuteParams EP){
	Player* player = EP.player;
	int i;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if ((*aiter)->GetOwner() == player)
			for (i = 1; i <= (*aiter)->StackSize(DCK); i++)
				(*aiter)->GetUnit(DCK,i)->ModAbility(uaProduction,+1);
	return er_none;
}
GameEffect* e_EnviroCompensator::Clone(){
	return new e_EnviroCompensator(*this);
}
string e_EnviroCompensator::Save(){
	return string();
}
void e_EnviroCompensator::Load(std::string str){}
//sarween
e_SarweenTools::e_SarweenTools(){
	id = "SarweenTools";
	name = "Sarween Tools";
	description = "When producing units, every Space Dock in system give you +1 free resource to build units";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttSarweenTools;
	prereq1 = ttEnviroCompensator;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_SarweenTools::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeBuild)
		return true;
	return false;
}
GameEffectRets e_SarweenTools::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Hex* hex = EP.hex;
	int* bonus = EP.modificator;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if (((*aiter)->GetHex() == hex) && ((*aiter)->GetOwner() == player))
			*bonus = *bonus + (*aiter)->StackSize(DCK);
	return er_none;
}
GameEffect* e_SarweenTools::Clone(){
	return new e_SarweenTools(*this);
}
string e_SarweenTools::Save(){
	return string();
}
void e_SarweenTools::Load(std::string str){}
//micro
e_Microtechnology::e_Microtechnology(){
	id = "MicroTechnology";
	name = "Micro Technology";
	description = "+1 Trade Good from each Trade Agreement";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttMicroTechnology;
	prereq1 = ttStasis;
	prereq2 = ttSarweenTools;
	isboth = false;
}
bool e_Microtechnology::GetQ(GameEffectQs queue){
	if (queue == eq_TradeModificator)
		return true;
	return false;
}
GameEffectRets e_Microtechnology::Execute(ExecuteParams EP){
	Player* player = EP.player;
	int* sum = EP.CommandCounters;
	for (int i = 0; i < MAX_TRADES; i++)
		if (player->GetTrade(i)->owner != player)
			*sum += 1;
	return er_none;
}
GameEffect* e_Microtechnology::Clone(){
	return new e_Microtechnology(*this);
}
string e_Microtechnology::Save(){
	return string();
}
void e_Microtechnology::Load(std::string str){}
//nano
e_Nanotechnology::e_Nanotechnology(){
	id = "NanoTechnology";
	name = "Nano Technology";
	description = "Dreadnoughts and War Suns cannot be targeted by Action Cards. When you claimed the planet, you gain it refreshed";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttNanoTechnology;
	prereq1 = ttMicroTechnology;
	prereq2 = MAX_TECH;
	isboth = false;
	bool isHostile = false;
}
bool e_Nanotechnology::GetQ(GameEffectQs queue){
	return (queue == eq_OnCapture);
}
GameEffectRets e_Nanotechnology::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Planet* planet = EP.planet;
	GameEffectQs Q = EP.queue;
	if (Q == eq_OnCapture)
		planet->DeleteState(psExhausted);
	return er_normal;
}
GameEffect* e_Nanotechnology::Clone(){
	return new e_Nanotechnology(*this);
}
string e_Nanotechnology::Save(){
	return string();
}
void e_Nanotechnology::Load(std::string str){}
//integrated
e_IntegratedEconomy::e_IntegratedEconomy(){
	id = "IntegratedEconomy";
	name = "Integrated Economy";
	description = "When producing units place them in any activated adjacent system that is friendly or empty. Place ground units on any friendly planet in range";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttIntegratedEconomy;
	prereq1 = ttMicroTechnology;
	prereq2 = ttCybernetics;
	isboth = true;
}
bool e_IntegratedEconomy::GetQ(GameEffectQs queue){
	return (queue==eq_SpawnUnits);
}
GameEffectRets e_IntegratedEconomy::Execute(ExecuteParams EP){
	Player* player = EP.player;
	vector<SpawnUnit> options = EP.spawn;
	Hex* hex = EP.hex;
	int* flag = EP.CommandCounters;
	*flag = 1;
	Hex* e_hex;
	vector<int> e_pool;
	vector<int> e_selected;
	vector<Army*> armies;
	vector<UnitSelection> e_options;
	UnitSelection US;
	US.multiple = false;
	US.n = 0;
	US.army = 0;
	US.selected = 0;
	US.unit = 0;
	US.UT = GF;
	Army* e_army;
	Army* army;
	bool hostile;
	bool lands;
	int e_unitnumber = 0;
	int i;
	Unit* unit;
	char buff[255];
	char str[255];
	vector<int> tempvec;
	for (i = GF; i < MAX_UNIT; i++){
		e_pool.push_back(0);
		e_selected.push_back(0);
	}
	for (i = 0; i < options.size(); i++)
		e_pool[options[i].UT] += options[i].n * player->GetUnitStats()->GetParametr(options[i].UT,sNP);
	e_pool[DCK] = 0;
	for (i = GF; i < DCK; i++)
		e_unitnumber += e_pool[i];
	for (i = 0; i < options.size(); i++){
		if (options[i].UT == DCK){
			unit = options.at(i).iter->army->AddUnit(DCK);
			unit->AssignAbility(uaProduction,FIELD_SKIP,0);
		}
	}
	while (e_unitnumber){
		sprintf(buff,"Select hex to spawn units, left to spawn: ");
		for (i = GF; i < MAX_UNIT; i++){
			if (e_pool[i] == 1){
				sprintf(str,"%s; ",ShipsShort[i].c_str());
				strcat(buff,str);
			}
			if (e_pool[i] > 1){
				sprintf(str,"%s x%d; ",ShipsShort[i].c_str(),e_pool[i]);
				strcat(buff,str);
			}
		}
		tempvec = _GrIn.SysChoise(buff);
		e_hex = _Map.GetHexh(tempvec[0],tempvec[1]);
		if ((e_hex != hex) && (hex->GetLinkedHexes()->GetLink(e_hex) != ltBound)){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Not adjacent hex");
			continue;
		}
		if ((e_hex != hex) && !e_hex->GotCC(player->GetNumber())){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Not activated hex");
			continue;
		}
		hostile = false;
		armies.clear();
		army = FindAnyArmy(e_hex);
		if (army == 0)
			armies.push_back(NewArmy(player,e_hex));
		else
			if (army->GetOwner() == player)
				armies.push_back(army);
			else
				hostile = true;
		lands = false;
		for (i = 1; i <= MAX_PLANETS; i++)
			if (e_hex->GetPlanet(i) != 0)
				if (e_hex->GetPlanet(i)->GetOwner() == player){
					armies.push_back(FindArmy(e_hex,player,true,e_hex->GetPlanet(i)));
					lands = true;
				}
				else
					hostile = true;
		if (hostile){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Not friendly/empty hex");
			continue;
		}
		e_options.clear();
		sprintf(buff,"Select units to spawn in hex %s",e_hex->GetId().c_str());
		_GrIn.InitChoise(buff,true,true,true);
		for (vector<Army*>::iterator aiter = armies.begin(); aiter != armies.end(); aiter++){
			if ((*aiter)->GetPlanet() == 0){
				for (i = FG; i <= FM; i++){
					if (e_pool[i] > 0){
						sprintf(buff,"%s x%d",ShipsShort[i].c_str(),e_pool[i]);
						_GrIn.AddNumerical(SHIPS_IMG[i],buff);
						US.army = *aiter;
						US.UT = (UnitType)i;
						e_options.push_back(US);
					}
				}
			}
			else{
				for (i = GF; i <= PDS; i++){
					if (e_pool[i] > 0){
						sprintf(buff,"%s x%d (%s)",ShipsShort[i].c_str(),e_pool[i],(*aiter)->GetPlanet()->GetName().c_str());
						_GrIn.AddNumerical(SHIPS_IMG[i],buff);
						US.army = *aiter;
						US.UT = (UnitType)i;
						e_options.push_back(US);
					}
				}
			}
		}
		tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() == 0)
			continue;
		for (i = GF; i < MAX_UNIT; i++)
			e_selected[i] = 0;
		for (i = 0; i < tempvec.size(); i++)
			e_selected[e_options[i].UT] += tempvec[i];
		hostile = false;
		for (i = GF; i < MAX_UNIT; i++)
			if (e_selected[i] > e_pool[i])
				hostile = true;
		if (hostile){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Try to place more than was produced");
			continue;
		}
		for (i = 0; i < tempvec.size(); i++)
			e_options[i].army->AddUnits(e_options[i].UT,tempvec[i]);
		for (i = GF; i < MAX_UNIT; i++)
			e_pool[i] -= e_selected[i];
		e_unitnumber = 0;
		for (i = GF; i < MAX_UNIT; i++)
			e_unitnumber += e_pool[i];
	}
	return er_none;
}
GameEffect* e_IntegratedEconomy::Clone(){
	return new e_IntegratedEconomy(*this);
}
string e_IntegratedEconomy::Save(){
	return string();
}
void e_IntegratedEconomy::Load(std::string str){}
//transfabrication
e_Transfabrication::e_Transfabrication(){
	id = "Transfabrication";
	name = "Transfabrication";
	description = "You may scuttle units at the start of Build Units step of your Activation. For each non-fighter and non-GF unit scuttled, gain 1 TG";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttTransfabrication;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_Transfabrication::GetQ(GameEffectQs queue){
	if (queue == eq_Scuttle)
		return true;
	return false;
}
GameEffectRets e_Transfabrication::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Army* army = EP.army1;
	char buff[255];
	if (army == 0)
		return er_none;
	_Interface.SetCurrPlayer(player->GetNumber() - 1);
	int units = ScuttleUnits(army->GetHex(),player);
	if (units){
		sprintf(buff,"Player %s receive %d Trade Goods by scuttling units",player->GetName().c_str(),units);
		_Interface.PrintThingAll(buff);
		player->GiveGoods(units);
	}
	return er_none;
}
GameEffect* e_Transfabrication::Clone(){
	return new e_Transfabrication(*this);
}
string e_Transfabrication::Save(){
	return string();
}
void e_Transfabrication::Load(std::string str){}
//Transit diodes
e_TransitDiodes::e_TransitDiodes(){
	id = "TransitDiodes";
	name = "Transit Diodes";
	description = "As an Action you may spend 1 SACC to move up to 4 GF to a planet your control";
	cost = 0;
	color = Yellow;
	race = MAX_RACE;
	TT = ttTransitDiodes;
	prereq1 = ttLightWaveDeflector;
	prereq2 = ttDacxiveAnimators;
	isboth = false;
}
bool e_TransitDiodes::GetQ(GameEffectQs queue){
	return (queue == eq_AAA);
}
GameEffectRets e_TransitDiodes::Execute(ExecuteParams EP){
	Player* player = EP.player;
	int p1,p2,i,j;
	Planet* pl1;
	Planet* pl2;
	Army* from;
	Army* to;
	Hex* hex1;
	Hex* hex2;
	vector<int> ret;
	vector<Unit*> options;
	char buff[255];
	char str[255];
	int moves = 0;
	if (player->GetCountersSA() <= 0){
		_Interface.PrintThingPlayer(player->GetNumber()-1,"Not enough SACC to use");
		return er_none;
	}
	while (true){
		ClearArmies();
		ret.clear();
		options.clear();
		p1 = 0;
		p2 = 0;
		ret = _GrIn.SysChoise("Select system to move from",true);
		if (ret.size() == 0)
			return er_none;
		hex1 = _Map.GetHexh(ret[0],ret[1]);
		p1 = SelectDialogPlanetInSystem(hex1,player,true);
		if (p1 <= 0)
			continue;
		pl1 = hex1->GetPlanet(p1);
		from = FindArmy(hex1,player,false,pl1);
		if (from == 0){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"No army here");
			continue;
		}
		if (!from->IsUnitWithAbility(uaCarried)){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"No units to move here");
			continue;
		}
		ret = _GrIn.SysChoise("Select system to move to",true);
		if (ret.size() == 0)
			continue;
		hex2 = _Map.GetHexh(ret[0],ret[1]);
		p2 = SelectDialogPlanetInSystem(hex2,player,true);
		if (p2 <= 0)
			continue;
		pl2 = hex2->GetPlanet(p2);
		to = FindArmy(hex2,player,true,pl2);
		options.clear();
		_GrIn.InitChoise("Select units to move",true,true,true);
		for (i = GF; i < FG; i++){
			if (from->StackSize((UnitType)i)){
				if (from->GetUnit((UnitType)i,1)->HasAbility(uaMultiple)){
					sprintf(buff,"%s x%d",ShipsShort[i].c_str(),from->StackSize((UnitType)i));
					if (from->GetPlanet() != 0){
						sprintf(str,"(%s)",from->GetPlanet()->GetName().c_str());
						strcat(buff,str);
					}
					_GrIn.AddNumerical(SHIPS_IMG[i],buff);
					options.push_back(from->GetUnit((UnitType)i,1));
				}
				else{
					for (j = 1; j <= from->StackSize((UnitType)i); j++){
						sprintf(buff,"%s",ShipsShort[i].c_str(),from->StackSize((UnitType)i));
						if (from->GetUnit((UnitType)i,j)->HasAbility(uaSustain))
							if (from->GetUnit((UnitType)i,j)->GetAbility(uaSustain).field2 == 0)
								strcat(buff,"(dmg)");
						if (from->GetPlanet() != 0){
							sprintf(str,"(%s)",from->GetPlanet()->GetName().c_str());
							strcat(buff,str);
						}
						_GrIn.AddNumerical(SHIPS_IMG[i],buff);
						options.push_back(from->GetUnit((UnitType)i,j));
					}
				}
			}
		}
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			continue;
		for (i = 0; i < ret.size(); i++)
			if ((ret[i] > 0) && (options[i]->HasAbility(uaMultiple)))
				if (ret[i] > from->StackSize(options[i]->Class))
					ret[i] = from->StackSize(options[i]->Class);
		moves = 0;
		for (i = 0; i < ret.size(); i++)
			moves += ret[i];
		if (moves > 4){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"More than 4 units to move");
			continue;
		}
		for (i = 0; i < ret.size(); i++){
			if (ret[i] > 0){
				if (options[i]->HasAbility(uaMultiple)){
					for (j = 1; j <= ret[i]; j++)
						if (from->GetUnit(options[i]->Class,j))
							from->GetUnit(options[i]->Class,j)->AddAbility(uaTransfered);
				}
				else
					options[i]->AddAbility(uaTransfered);
			}
		}
		while (from->IsUnitWithAbility(uaTransfered))
			MoveUnit(from,to,from->GetUnitWithAbility(uaTransfered,1));
		to->DeleteUnitAbility(uaTransfered);
		player->TakeCounter(CC_strat);
		ClearArmies();
		break;
	}
	return er_normal;
}
GameEffect* e_TransitDiodes::Clone(){
	return new e_TransitDiodes(*this);
}
string e_TransitDiodes::Save(){
	return string();
}
void e_TransitDiodes::Load(std::string str){}