bool e_SolMarkIICarrier::GetQ(GameEffectQs queue){
	if ((queue==eq_Battle) || (queue == eq_AfterRefreshAbilities) || (queue == eq_BeforeBuild))
		return true;
	return false;
}
e_SolMarkIICarrier::e_SolMarkIICarrier(){
	id = "SolMarkIICarrier";
	name = "Mark II Advanced Carriers";
	description = "Carriers may carry eight units and gain sustain damage";
	cost = 4;
	color = RaceTech;
	race = Sol;
	TT = ttMarkIIAdvancedCarriers;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
GameEffectRets e_SolMarkIICarrier::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Unit* unit = EP.unit;
	Army* army = EP.army1;
	Player* player = EP.player;
	if (Q == eq_AfterRefreshAbilities){
		if (unit->Class == CR){
			if (unit->HasAbility(uaCarrier))
				unit->ModAbility(uaCarrier,2);
			else
				unit->AddAbility(uaCarrier,2);
			
		}
	}
	if ((Q == eq_Battle) && (army != 0) && (army->GetOwner() != 0)){
		army->GetOwner()->GetUnitStats()->SetModifier(CR,sHP,+1);
		for (int i = 1; i <= army->StackSize(CR); i++)
			if (!army->GetUnit(CR,i)->HasAbility(uaSustain))
				army->GetUnit(CR,i)->AddAbility(uaSustain,0,1,1);
	}
	if (Q == eq_BeforeBuild)
		player->GetUnitStats()->SetModifier(CR,sHP,+1);
	return er_none;
}
GameEffect* e_SolMarkIICarrier::Clone(){
	return new e_SolMarkIICarrier(*this);
}
string e_SolMarkIICarrier::Save(){
	return string();
}
void e_SolMarkIICarrier::Load(std::string str){
	launched = false;
}
////////////////////////////////////////////////////
bool e_SolRecruit::GetQ(GameEffectQs queue){
	if (queue == eq_AAA)
		return true;
	return false;
}
e_SolRecruit::e_SolRecruit(){
	id = "SolRecruit";
	image=EMPTY_EVENT_IMG;
}
GameEffectRets e_SolRecruit::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Planet* planet = 0;
	char str[255];
	if (!player->GetCountersSA()){//нет каунтеров
		_Interface.PrintThingAll("There is no SACC for using this ability");
		return er_none;
	}
	planet = SelectDialogPlanet("Select planet to place 2 GF",
		"Select system to place 2 GF",
		0,player,true,true,false,false,false,false);
	if (planet){
		FindArmy(planet->GetSystem(),player,true,planet)->AddUnits(GF,2);
		player->TakeCounter(CC_strat);
		sprintf(str,"Player %s use Sol ability and spawn 2 GF on planet %s",player->GetName().c_str(),planet->GetName().c_str());
		_Interface.PrintThingAll(str);
	}
	else
		return er_none;
	/*sprintf(str,"Select planet to place %d GF",SOL_GF_FOR_COUNTER);
	_GrIn.InitChoise(str,true,false);
	for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++)
		if ((*piter)->GetSpecial() != TradeStation)
			_GrIn.AddOption(PLANET_IMG,(*piter)->GetName());
	vector<int> tempvec = _GrIn.LaunchChoise();
	int* ret = 0;
	if (tempvec.size() != 0)
		ret = &tempvec[0];
	if (ret == 0)
		return er_none;
	int k = -1;
	for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
		//if ((*piter)->HasState(psNoSurface))
		if ((*piter)->GetSpecial() == TradeStation)
			continue;
		k++;
		if (ret[k] == 1){
			planet = *piter;
			break;
		}
	}
	if (planet != 0){
		FindArmy(planet->GetSystem(),player,true,planet)->AddUnits(GF,2);
		sprintf(str,"Spawn %d GF on planet %s",SOL_GF_FOR_COUNTER,planet->GetName().c_str());
		player->TakeCounter(CC_strat);
	}
	else{
		_Interface.PrintThingAll("No planet to spawn");
		return er_none;
	}*/
	return er_normal;
}
GameEffect* e_SolRecruit::Clone(){
	return new e_SolRecruit(*this);
}
string e_SolRecruit::Save(){
	return string();
}
void e_SolRecruit::Load(std::string str){}
////////////////////////////////////////////////////
e_SolSpecOpsTraining::e_SolSpecOpsTraining(){
	id = "SolSpecOpsTraining";
	name = "Spec Ops Training";
	description = "Each time you roll a 1 during Invasion Combat, you may reroll the die. You must use the second result";
	cost = 5;
	color = RaceTech;
	race = Sol;
	TT = ttSpecOpsTraining;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_SolSpecOpsTraining::GetQ(GameEffectQs queue){
	if (queue==eq_AfterRoll)
		return true;
	return false;
}
GameEffectRets e_SolSpecOpsTraining::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	int* r = EP.roll;
	Unit* unit = EP.unit;
	char str[127];
	if ((army->GetPlanet()!=0)&&((unit->Class==GF)||(unit->Class==ST))&&(*r==1)){
		*r=rand()%10+1;
		sprintf(str,"Player %s Spec Ops Training reroll 1 --> %d",army->GetOwner()->GetName(),*r);
		_Interface.PrintThingAll(str);
	};
	return er_none;
}
GameEffect* e_SolSpecOpsTraining::Clone(){
	return new e_SolSpecOpsTraining(*this);
}
string e_SolSpecOpsTraining::Save(){
	return string();
}
void e_SolSpecOpsTraining::Load(std::string str){}
////////////////////////////////////////////////////
e_SolCounter::e_SolCounter(){
	id = "SolCounter";
}
bool e_SolCounter::GetQ(GameEffectQs queue){
	if (queue==eq_StatusPhase)
		return true;
	return false;
}
GameEffectRets e_SolCounter::Execute(ExecuteParams EP){
	int* CCs = EP.CommandCounters;
	*CCs = *CCs + 1;
	return er_none;
}
GameEffect* e_SolCounter::Clone(){
	return new e_SolCounter(*this);
}
string e_SolCounter::Save(){
	return string();
}
void e_SolCounter::Load(std::string str){}
////////////////////////////////////////////////////
class e_SolStartUnits:public GameEffect{
public:
	bool GetQ(GameEffectQs queue){
		if (queue==eq_Pregame)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* curPlayer = EP.player;
		spawnarmy* units;
		// торговые договоры
		EP.player->AddTrade(2);
		EP.player->AddTrade(2);
		//стартовые техи
		curPlayer->GiveTech(ttAntimass);
		curPlayer->GiveTech(ttCybernetics);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_Cybernetics);
		curPlayer->AddGameEffect(new e_SolCounter);
		curPlayer->AddGameEffect(new e_SolRecruit);
		//curPlayer->AddGameEffect(new e_XRDtransporters);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 5;
		units->unit[DS] = 1;
		units->unit[CR] = 2;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_SolStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};