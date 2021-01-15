e_L1z1xRacialAbilityStats::e_L1z1xRacialAbilityStats(){
	id = "L1z1xRacialAbilityStats";
}
bool e_L1z1xRacialAbilityStats::GetQ(GameEffectQs queue){
	if ((queue==eq_Battle)||(queue==eq_BeforeBuild))
		return true;
	return false;
}
GameEffectRets e_L1z1xRacialAbilityStats::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	if (Q == eq_BeforeBuild){
		Player* player = EP.player;
		player->GetUnitStats()->SetModifier(DR,sCOST,-1);
	}
	if (Q == eq_Battle){
		Army* attArmy = EP.army1;
		Army* defArmy = EP.army2;
		int round = EP.fround;
		int attacker = EP.attacker;
		//attArmy->GetOwner()->GetUnitStats()->SetModifier(DR,sCOST,-1);
		for (int i=1; i<=attArmy->StackSize(DR);i++)
			attArmy->GetUnit(DR,i)->ModAbility(uaSpaceBattle,-1);
		if ((attArmy->GetPlanet()!=0)&&(attacker==1))
			for (int i=1; i<=attArmy->IsUnitWithAbility(uaInfantry);i++)
				attArmy->GetUnitWithAbility(uaInfantry,i)->ModAbility(uaLandBattle,-1);
	}
	return er_none;
}
GameEffect* e_L1z1xRacialAbilityStats::Clone(){
	return new e_L1z1xRacialAbilityStats(*this);
}
string e_L1z1xRacialAbilityStats::Save(){
	return string();
}
void e_L1z1xRacialAbilityStats::Load(std::string str){}
//////////////////////////////////////////////////////////////
e_L1z1xDreadnoughtInvasionPods::e_L1z1xDreadnoughtInvasionPods(){
	id = "DreadnoughtInvasionPod";
	name = "Dreadnought Invasion Pod";
	description = "Your Dreadnoughts may carry one additional GF";
	cost = 2;
	color = RaceTech;
	race = L1z1x;
	TT = ttDreadnoughtInvasionPod;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_L1z1xDreadnoughtInvasionPods::GetQ(GameEffectQs queue){
	if (queue == eq_AfterRefreshAbilities)
		return true;
	return false;
}
GameEffectRets e_L1z1xDreadnoughtInvasionPods::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Unit* unit = EP.unit;
	Army* army = EP.army1;
	if (Q == eq_AfterRefreshAbilities)
		if (unit->Class == DR)
			if (unit->HasAbility(uaCarrier))
				unit->ModAbility(uaCarrier,FIELD_SKIP,FIELD_SKIP,1);
			else
				unit->AddAbility(uaCarrier,0,0,1);
	return er_none;
}
GameEffect* e_L1z1xDreadnoughtInvasionPods::Clone(){
	return new e_L1z1xDreadnoughtInvasionPods(*this);
}
string e_L1z1xDreadnoughtInvasionPods::Save(){
	return string();
}
void e_L1z1xDreadnoughtInvasionPods::Load(std::string str){}
/////////////////////////////////////////////////////////////////
e_L1z1xInheritanceSystems::e_L1z1xInheritanceSystems(){
	id = "InheritanceSystems";
	name = "Inheritance Systems";
	description = "When researching Technology using the Technology Strategy Card, you may spend two additional resources to ignore one of the TechnologyТs prerequisites";
	cost = 5;
	color = RaceTech;
	race = L1z1x;
	TT = ttInheritanceSystems;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_L1z1xInheritanceSystems::GetQ(GameEffectQs queue){
	if (queue==eq_TechnologyBuy)
		return true;
	return false;
}
GameEffectRets e_L1z1xInheritanceSystems::Execute(ExecuteParams EP){
	Player* player = EP.player;
	TechType TT = EP.Tech;
	int* bonus = EP.TechCostBonus;
	if (CanGetTech(player,TT)&&(!_GameStats.GetTechDeck()->at(TT)->HavePrereqs(player))){
		*bonus = *bonus + INHERITANCE_SYSTEMS_RES_COST;
	};
	return er_none;
}

GameEffect* e_L1z1xInheritanceSystems::Clone(){
	return new e_L1z1xInheritanceSystems(*this);
}
string e_L1z1xInheritanceSystems::Save(){
	return string();
}
void e_L1z1xInheritanceSystems::Load(std::string str){}
///////////////////////////////////////////////////////
e_L1z1xFlagship::e_L1z1xFlagship(){
	id = "L1z1xFlagship";
}
bool e_L1z1xFlagship::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattleRound)||(queue==eq_AfterBattleRound))
		return true;
	return false;
}
GameEffectRets e_L1z1xFlagship::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	GameEffectQs Q = EP.queue;
	if (eq_BeforeBattleRound==Q){
		if (army->StackSize(FM)>0){
			army->GetUnit(FM)->AddAbility(uaHeavyDamage);
			if (army->StackSize(DR)>0)
				for (int i=1; i<=army->StackSize(DR); i++)
					army->GetUnit(DR,i)->AddAbility(uaHeavyDamage);
		}
	}
	if (eq_AfterBattleRound==Q)
		army->DeleteUnitAbility(uaHeavyDamage);
	return er_none;
}

GameEffect* e_L1z1xFlagship::Clone(){
	return new e_L1z1xFlagship(*this);
}
string e_L1z1xFlagship::Save(){
	return string();
}
void e_L1z1xFlagship::Load(std::string str){}
//////////////////////////////////////////////////
class e_L1z1xStartUnits:public GameEffect{
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
		EP.player->AddTrade(1);
		//стартовые техи
		curPlayer->GiveTech(ttHylar);
		curPlayer->GiveTech(ttEnviroCompensator);
		curPlayer->GiveTech(ttCybernetics);	
		curPlayer->GiveTech(ttStasis);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_Cybernetics);
		curPlayer->AddGameEffect(new e_StasisCapsules);
		curPlayer->AddGameEffect(new e_L1z1xRacialAbilityStats);
		curPlayer->AddGameEffect(new e_L1z1xFlagship);
		//каунтеры
		curPlayer->AddCC(3,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 5;
		units->unit[DR] = 1;
		units->unit[CR] = 1;
		units->unit[FG] = 3;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_L1z1xStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};