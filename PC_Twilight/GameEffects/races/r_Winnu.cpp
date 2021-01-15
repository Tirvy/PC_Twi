e_WinnuBiopticRecyclers::e_WinnuBiopticRecyclers(){
	id = "BiopticRecyclers";
	name = "Bioptic Recyclers";
	description = "Once per round, as an action, discard one AC to get a CC or 2TG";
	cost = 3;
	color = RaceTech;
	race = Winnu;
	TT = ttBiopticRecyclers;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	used = 0;
}
bool e_WinnuBiopticRecyclers::GetQ(GameEffectQs queue){
	if (((queue == eq_AAA) && !used) || (queue == eq_StatusStart))
		return true;
	return false;
}
GameEffectRets e_WinnuBiopticRecyclers::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char buff[255];
	int counters = 0;
	int tgs = 0;
	if (Q == eq_AAA){
		if (!player->GetActionsNumber()){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no Action Cards");
			return er_none;
		}
		while (true){
			e_ActionCard* AC = SelectDialogActionCard("Select Action Card to discard",player,true);
			if (AC == 0)
				return er_none;
			_GrIn.InitChoise("Select bonus for this Action Card",true);
			for (int i = 0; i < CC_MAX; i++)
				_GrIn.AddOption(EMPTY_EVENT_IMG,CC_PoolsFull[i]);
			_GrIn.AddOption(GOODS_IMG,"Trade Goods");
			vector<int> ret = _GrIn.LaunchChoise();
			if (ret.size() == 0)
				continue;
			counters = ret[0]+ret[1]+ret[2];
			tgs = 0;
			player->AddCC(ret[0],ret[1],ret[2]);
			if (ret[3] == 1)
				tgs = 2;
			player->RemoveGameEffect(AC->GetId());
			sprintf(buff,"Player %s receives %d Counters and %d Trade Goods by using Bioptic Recyclers",player->GetName().c_str(),counters,tgs);
			_Interface.PrintThingAll(buff);
			used = 1;
			break;
		}
	}
	if (Q == eq_StatusStart)
		used = 0;
	return er_normal;
}

GameEffect* e_WinnuBiopticRecyclers::Clone(){
	return new e_WinnuBiopticRecyclers(*this);
}
string e_WinnuBiopticRecyclers::Save(){
	std::stringstream ss;
	ss<<used;
	return ss.str();
}
void e_WinnuBiopticRecyclers::Load(std::string str){
	std::istringstream iss(str);
	string s;
	iss>>s>>used;
}
///////////////////////////////////////////////////////
e_WinnuLazaxGateFolding::e_WinnuLazaxGateFolding(){
	id = "LazaxGateFolding";
	name = "Lazax Gate Folding";
	description = "At the start of each Status Phase, you may place 1 GF on Mecatol Rex. You may only do this if the planet is uncontrolled or is under your control (discard any Domain Counter on the planet)";
	cost = 4;
	color = RaceTech;
	race = Winnu;
	TT = ttLazaxGateFolding;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_WinnuLazaxGateFolding::GetQ(GameEffectQs queue){
	if (queue == eq_StatusStart)
		return true;
	return false;
}
GameEffectRets e_WinnuLazaxGateFolding::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Hex* mecatol = 0;
	for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++)
		if ((*iter)->GetId().compare("MecatolRex") == 0)
			mecatol = *iter;
	Army* army = 0;
	char buff[255];
	if (mecatol != 0){
		if ((mecatol->GetPlanet(1)->GetOwner() == 0) || (mecatol->GetPlanet(1)->GetOwner() == player)){
			if (SelectDialogYesNo("Place 1 free Ground Force on Mecatol?")){
				army = FindArmy(mecatol,player,true,mecatol->GetPlanet(1));
				army->AddUnit(GF);
				if (mecatol->GetPlanet(1)->GetOwner() == 0){
					player->Capture(mecatol->GetPlanet(1));
					sprintf(buff,"Player %s captures Mecatol Rex using Lazax Gate Folding",player->GetName().c_str());
					_Interface.PrintThingAll(buff);
				}
			}
		}
	}
	return er_normal;
}

GameEffect* e_WinnuLazaxGateFolding::Clone(){
	return new e_WinnuLazaxGateFolding(*this);
}
string e_WinnuLazaxGateFolding::Save(){
	return string();
}
void e_WinnuLazaxGateFolding::Load(std::string str){}
//////////////////////////////////////////////
e_WinnuFlagship::e_WinnuFlagship(){
	id = "WinnuFlagship";
}
bool e_WinnuFlagship::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_WinnuFlagship::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	PowExv<Unit>* tUn=0;
	int shots=0;
	if (defArmy==0)
		return er_none;
	if (attArmy->StackSize(FM)>0){
		shots=defArmy->IsUnitWithAbility(uaCapitalShip);
		attArmy->GetUnit(FM)->AssignAbility(uaSpaceBattle,FIELD_SKIP,shots);
	}
	return er_none;
}
GameEffect* e_WinnuFlagship::Clone(){
	return new e_WinnuFlagship(*this);
}
string e_WinnuFlagship::Save(){
	return string();
}
void e_WinnuFlagship::Load(std::string str){}
//////////////////////////////////////////////
e_WinnuPolitic::e_WinnuPolitic(){
	id = "WinnuPolitic";
}
bool e_WinnuPolitic::GetQ(GameEffectQs queue){
	if (queue == eq_PreVotings)
		return true;
	return false;
}
GameEffectRets e_WinnuPolitic::Execute(ExecuteParams EP){
	Player* player = EP.player;
	vector<Voting>* votes = EP.votings;
	int sum = 0;
	for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
		if (!(*piter)->HasState(psExhausted))//Zoldn
			sum += (*piter)->GetInf();
		if ((*piter) == player->GetHS()->GetPlanet(1) && ((*piter)->HasState(psExhausted)))
			sum += (*piter)->GetInf();
	}
	if (sum == 0)
		sum = 1;
	votes->at(player->GetNumber()-1).votes = sum;
	return er_none;
}
GameEffect* e_WinnuPolitic::Clone(){
	return new e_WinnuPolitic(*this);
}
string e_WinnuPolitic::Save(){
	return string();
}
void e_WinnuPolitic::Load(std::string str){}
////////////////////////////////////////
e_WinnuLocalUnrest::e_WinnuLocalUnrest(){
	id = "WinnuLocalUnrest";
}
bool e_WinnuLocalUnrest::GetQ(GameEffectQs queue){
	if (queue == eq_ActionCardBreak)
		return true;
	return false;
}
GameEffectRets e_WinnuLocalUnrest::Execute(ExecuteParams EP){
	Player* player = EP.player;
	e_ActionCard* AC = EP.actioncard;
	int* flag = EP.ActionCards;
	*flag = 1;
	return er_none;
}
GameEffect* e_WinnuLocalUnrest::Clone(){
	return new e_WinnuLocalUnrest(*this);
}
string e_WinnuLocalUnrest::Save(){
	return string();
}
void e_WinnuLocalUnrest::Load(std::string str){}
////////////////////////////////////////
e_WinnuTechnology::e_WinnuTechnology(){
	id = "WinnuTechnology";
}
bool e_WinnuTechnology::GetQ(GameEffectQs queue){
	if ((queue==eq_StratSecStart)||(queue==eq_StratSecEnd))
		return true;
	return false;
}
GameEffectRets e_WinnuTechnology::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	e_StratCard* SC = EP.stratcard;
	if (SC->GetType()==Technology){
		if (Q==eq_StratSecStart)
			((e_Technology*)SC)->TECHNOLOGY_SECONDARY_COUNTERS_COST=0;
		if (Q==eq_StratSecEnd)
			SC->reset();
	};
	return er_none;
}
GameEffect* e_WinnuTechnology::Clone(){
	return new e_WinnuTechnology(*this);
}
string e_WinnuTechnology::Save(){
	return string();
}
void e_WinnuTechnology::Load(std::string str){}
/////////////////////////////////////////////
class e_WinnuStartUnits:public GameEffect{
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
		EP.player->AddTrade(1);
		EP.player->AddTrade(3);
		//стартовые техи
		curPlayer->GiveTech(ttEnviroCompensator);
		curPlayer->GiveTech(ttStasis);
		curPlayer->GiveTech(ttAntimass);
		//curPlayer->GetUnitStats()->SetModifier(CS,sGFCP,1);
		//curPlayer->GetUnitStats()->SetModifier(DR,sGFCP,1);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_StasisCapsules);
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_WinnuFlagship);
		curPlayer->AddGameEffect(new e_WinnuTechnology);
		curPlayer->AddGameEffect(new e_WinnuPolitic);
		curPlayer->AddGameEffect(new e_WinnuLocalUnrest);
		//curPlayer->AddAction(7);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 3;
		units->unit[FG] = 2;
		units->unit[CR] = 1;
		units->unit[CS] = 1;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		curPlayer->ExecuteGameEffect(ExecuteParams(eq_LaunchEffect,curPlayer));
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_WinnuStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};