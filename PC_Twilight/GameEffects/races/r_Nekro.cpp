e_NekroFlagship::e_NekroFlagship(){
	id = "NekroFlagship";
}
bool e_NekroFlagship::GetQ(GameEffectQs queue){
	if (queue==eq_AfterAssignDamage)
		return true;
	return false;
}
GameEffectRets e_NekroFlagship::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* opponent = FindOpponentArmy(army);
	Unit* unit = EP.unit;
	int isAttacker = EP.attacker;
	if ((unit->Class==FM)&&(unit->HasAbility(uaKilled,0)&&(!isAttacker))){
		_Interface.PrintThingAll("Alastor was destroyed, all fleets in this system are destroyed");
		for (int i=1; i<=army->IsUnitWithAbility(uaNone);i++){
			if (!army->GetUnitWithAbility(uaNone,i)->HasAbility(uaKilled))
				army->GetUnitWithAbility(uaNone,i)->AddAbility(uaKilled);
		}
		if (opponent!=0)
			for (int i=1; i<=opponent->IsUnitWithAbility(uaNone);i++)
				if (!opponent->GetUnitWithAbility(uaNone,i)->HasAbility(uaKilled))
					opponent->GetUnitWithAbility(uaNone,i)->AddAbility(uaKilled);
	}
	return er_none;
}
GameEffect* e_NekroFlagship::Clone(){
	return new e_NekroFlagship(*this);
}
string e_NekroFlagship::Save(){
	return string();
}
void e_NekroFlagship::Load(std::string str){}
////////////////////////////////////////
e_NekroAbstain::e_NekroAbstain(){
	id = "NekroAbstain";
}
bool e_NekroAbstain::GetQ(GameEffectQs queue){
	if ((queue == eq_Votings) || (queue == eq_PreVotings))
		return true;
	return false;
}
GameEffectRets e_NekroAbstain::Execute(ExecuteParams EP){
	Player* player = EP.player;
	vector<Voting>* votes = EP.votings;
	votes->at(player->GetNumber()-1).votes = 0;
	return er_none;
}
GameEffect* e_NekroAbstain::Clone(){
	return new e_NekroAbstain(*this);
}
string e_NekroAbstain::Save(){
	return string();
}
void e_NekroAbstain::Load(std::string str){}
////////////////////////////////////////
e_NekroTechResearch::e_NekroTechResearch(){
	id = "NekroTechResearch";
}
bool e_NekroTechResearch::GetQ(GameEffectQs queue){
	if (queue == eq_ResearchTech)
		return true;
	return false;
}
GameEffectRets e_NekroTechResearch::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int* ResCost = EP.CommandCounters;
	int* CounterCost = EP.ActionCards;
	int r = 0;
	char buff[255];
	if (player->GetCountersSA() < *CounterCost){
		_Interface.PrintThingPlayer(player->GetNumber()-1,"Not enough SACC to use");
		return er_none;
	}
	int cost = 0;
	if (*ResCost > 0)
		cost = *ResCost;
	sprintf(buff,"Buy 3 Command Counters for %d res and %d SACC?",cost,*CounterCost);
	if (SelectDialogYesNo(buff)){
		if (player->Pay(0,*ResCost) == frr_normal){
			player->TakeCounter(CC_strat,*CounterCost);
			player->GiveFreeCounters(3);
			r = 1;
		}
	}
	*CounterCost = r;
	return er_none;
}
GameEffect* e_NekroTechResearch::Clone(){
	return new e_NekroTechResearch(*this);
}
string e_NekroTechResearch::Save(){
	return string();
}
void e_NekroTechResearch::Load(std::string str){}
////////////////////////////////////////
bool e_NekroValefarAssmilator::GetQ(GameEffectQs queue){
	if ((queue==eq_AfterAssignDamage)||(queue==eq_BeforeBattle)||(queue==eq_AfterBattle))
		return true;
	return false;
};
e_NekroValefarAssmilator::e_NekroValefarAssmilator(){
	id = "NekroValefarAssmilator";
	CopiedRaceTechs = 0;
	IsDestroyedEnemyUnit = false;
};
GameEffectRets e_NekroValefarAssmilator::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* target = EP.army2;
	Player* player = army->GetOwner();
	int attacker = EP.attacker;
	Unit* unit = EP.unit;
	int* r;
	char str[127];
	TechType TT = MAX_TECH;
	GameEffectQs Q = EP.queue;
	if (Q == eq_AfterAssignDamage){
		if ((attacker == 1)||((attacker == 0)&&(army->IsUnitInArmy(unit)))){
			if ((unit!=0)&&(unit->HasAbility(uaKilled))){
				IsDestroyedEnemyUnit = true;
			}
		}
	}
	if (Q == eq_BeforeBattle)
		IsDestroyedEnemyUnit = false;
	if ((Q == eq_AfterBattle)&&IsDestroyedEnemyUnit){
		if (CopiedRaceTechs<=MAX_COPY_RACE_TECHS)
			r = ArrayTechCopy(target->GetOwner(),player,true);
		else
			r = ArrayTechCopy(target->GetOwner(),player,false);
		TT = SelectDialogTech("Select tech to copy from your opponent",player,r);
		if (TT!=MAX_TECH){
			if (TT>ttTransitDiodes)
				CopiedRaceTechs++;
			sprintf(str,"Player %s has copied %s technology from player %s",player->GetName().c_str(),_GameStats.GetTechDeck()->at(TT)->GetName().c_str(),target->GetOwner()->GetName().c_str());//TechFull[TT].c_str()
			_Interface.PrintThingAll(str);
			player->GiveTech(TT);
			AddTechGameEffect(player,TT);
		}
	}
	return er_none;
};
GameEffect* e_NekroValefarAssmilator::Clone(){
	return new e_NekroValefarAssmilator(*this);
}
string e_NekroValefarAssmilator::Save(){
	std::stringstream ss;
	ss<<CopiedRaceTechs;
	return ss.str();
}
void e_NekroValefarAssmilator::Load(std::string str){
	std::istringstream iss(str);
	iss>>CopiedRaceTechs;
}
///////////////////////////////////////////////////
class e_NekroStartUnits:public GameEffect{
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
		EP.player->AddTrade(2);
		//стартовые техи
		curPlayer->GiveTech(ttHylar);
		curPlayer->GiveTech(ttGenSynthesis);
		curPlayer->GiveTech(ttDacxiveAnimators);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_GenSynthesis);
		curPlayer->AddGameEffect(new e_DacxiveAnimators);
		curPlayer->AddGameEffect(new e_NekroValefarAssmilator);
		curPlayer->AddGameEffect(new e_NekroTechResearch);
		curPlayer->AddGameEffect(new e_NekroFlagship);
		curPlayer->AddGameEffect(new e_NekroAbstain);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 2;
		units->unit[MU] = 1;
		units->unit[CS] = 2;
		units->unit[CR] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		curPlayer->RemoveGameEffect("PlanetTechDiscount");
		curPlayer->RemoveGameEffect("ResearchTech");
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_NekroStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};