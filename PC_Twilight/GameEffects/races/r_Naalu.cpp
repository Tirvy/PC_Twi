e_NaaluTelepathicMindWeapon::e_NaaluTelepathicMindWeapon(){
	id = "TelepathicMindWeapon";
	name = "Telepathic Mind Weapon";
	description = "When your opponent activates a system you control, he loses 1 FSCC";
	cost = 5;
	color = RaceTech;
	race = Naalu;
	TT = ttTelepathicMindWeapon;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_NaaluTelepathicMindWeapon::GetQ(GameEffectQs queue){
	return (queue == eq_ActivateSystem);
}
GameEffectRets e_NaaluTelepathicMindWeapon::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Army* arriving = EP.army1;
	int* check = EP.CommandCounters;
	if ((arriving->GetOwner() != player) && (HexController(arriving->GetHex()) == player)){
		arriving->GetOwner()->TakeCounter(1);
		_Interface.PrintThingPlayer(arriving->GetOwner()->GetNumber()-1,"You lose 1 FSCC due to Telepathic Mind Weapon");
		arriving->GetOwner()->CheckFleets();
	}
	return er_none;
}

GameEffect* e_NaaluTelepathicMindWeapon::Clone(){
	return new e_NaaluTelepathicMindWeapon(*this);
}
string e_NaaluTelepathicMindWeapon::Save(){
	return string();
}
void e_NaaluTelepathicMindWeapon::Load(std::string str){}
///////////////////////////////////////////////////////
e_NaaluHybridCrystalDrives::e_NaaluHybridCrystalDrives(){
	id = "HybridCrystalDrives";
	name = "Hybrid Crystal Drives";
	description = "Your Carriers and unsupported Advanced Fighters each only count 1/2 ship for the Fleet Supply (rounded up)";
	cost = 3;
	color = RaceTech;
	race = Naalu;
	TT = ttHybridCrystalDrives;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_NaaluHybridCrystalDrives::GetQ(GameEffectQs queue){
	return (queue == eq_FleetSupply);
}
GameEffectRets e_NaaluHybridCrystalDrives::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	int* supply = EP.FleetSupply;
	int units = 0;
	for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++){
		if (((*iter)->Class == CR) && (!(*iter)->HasAbility(uaKilled)))
			units++;
		if ((army->GetOwner()->GotTech(ttAdvancedFighters)) && ((*iter)->HasAbility(uaFighter)) && (!(*iter)->HasAbility(uaKilled)))
			units++;
	}
	*supply -= (units/2);
	return er_none;
}

GameEffect* e_NaaluHybridCrystalDrives::Clone(){
	return new e_NaaluHybridCrystalDrives(*this);
}
string e_NaaluHybridCrystalDrives::Save(){
	return string();
}
void e_NaaluHybridCrystalDrives::Load(std::string str){}
//////////////////////////////////////////////
e_NaaluRacialAbilityStats::e_NaaluRacialAbilityStats(){
	id = "NaaluRacialAbilityStats";
}
bool e_NaaluRacialAbilityStats::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
return false;
}
GameEffectRets e_NaaluRacialAbilityStats::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	attArmy->GetOwner()->GetUnitStats()->SetModifier(FG,sPW,-1);
	for (vector<Unit*>::iterator iter = attArmy->GetUnits()->begin(); iter != attArmy->GetUnits()->end(); iter++)
		if ((*iter)->Class==FG)
			(*iter)->ModAbility(uaSpaceBattle,-1);
	return er_none;
}
GameEffect* e_NaaluRacialAbilityStats::Clone(){
	return new e_NaaluRacialAbilityStats(*this);
}
string e_NaaluRacialAbilityStats::Save(){
	return string();
}
void e_NaaluRacialAbilityStats::Load(std::string str){}
//////////////////////////////////////////////
e_NaaluInitiative::e_NaaluInitiative(){
	id = "NaaluInitiative";
}
bool e_NaaluInitiative::GetQ(GameEffectQs queue){
	if (queue==eq_StrategyEnd)
		return true;
return false;
}
GameEffectRets e_NaaluInitiative::Execute(ExecuteParams EP){
	Player* player = EP.player;
	player->SetInitiative(-2);
	return er_none;
}
GameEffect* e_NaaluInitiative::Clone(){
	return new e_NaaluInitiative(*this);
}
string e_NaaluInitiative::Save(){
	return string();
}
void e_NaaluInitiative::Load(std::string str){}
/////////////////////////////////////////////////////
e_NaaluRetreat::e_NaaluRetreat(){
	id = "NaaluRetreat";
	image = EMPTY_EVENT_IMG;
	active = false;
}
bool e_NaaluRetreat::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattle) || ((queue == eq_BeforeBattleAction) && active))
		return true;
	return false;
}
GameEffectRets e_NaaluRetreat::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	int attacker = EP.attacker;
	GameEffectQs Q = EP.queue;
	char str[127];
	if (Q == eq_BeforeBattle)
		if ((attArmy->GetPlanet()==0)&&(attacker==0))
			active = true;
		else
			active = false;
	if (Q == eq_BeforeBattleAction){
		if ((attacker==0)&&(CombatInterface().CanRetreat(attArmy))){
			_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
			if (SelectDialogYesNo("Retreat before battle?")){
				sprintf(str,"Player %s uses Naalu retreat ability",attArmy->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(str);
				CombatInterface().Retreat(attArmy);
				return er_normal;
			}
		}
	}
	return er_none;
}
GameEffect* e_NaaluRetreat::Clone(){
	return new e_NaaluRetreat(*this);
}
string e_NaaluRetreat::Save(){
	return string();
}
void e_NaaluRetreat::Load(std::string str){}
////////////////////////////////////////////////////
e_NaaluFlagship::e_NaaluFlagship(){
	id = "NaaluFlagship";
}
bool e_NaaluFlagship::GetQ(GameEffectQs queue){
	if (queue==eq_FleetSupply)
		return true;
	return false;
}
GameEffectRets e_NaaluFlagship::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	int* supply = EP.FleetSupply;
	if ((army->StackSize(FM))&&(!army->GetUnit(FM)->HasAbility(uaKilled)))
		*supply = *supply - 3;
	return er_none;
}
GameEffect* e_NaaluFlagship::Clone(){
	return new e_NaaluFlagship(*this);
}
string e_NaaluFlagship::Save(){
	return string();
}
void e_NaaluFlagship::Load(std::string str){}
///////////////////////////////////////////////
class e_NaaluStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttEnviroCompensator);
		curPlayer->GiveTech(ttAntimass);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_NaaluRacialAbilityStats);
		curPlayer->AddGameEffect(new e_NaaluRetreat);
		curPlayer->AddGameEffect(new e_NaaluInitiative);
		curPlayer->AddGameEffect(new e_NaaluFlagship);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[CR] = 1;
		units->unit[CS] = 1;
		units->unit[DS] = 1;
		units->unit[FG] = 4;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_NaaluStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};