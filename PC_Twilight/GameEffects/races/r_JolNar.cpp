e_JolNarSpatialConduitNetwork::e_JolNarSpatialConduitNetwork(){
	id = "SpatialConduitNetwork";
	name = "Spatial Conduit Network";
	description = "Once per round you may move from any system you control to any other system you control as if they were adjacent.";
	cost = 6;
	color = RaceTech;
	race = JolNar;
	TT = ttSpatialConduitNetwork;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_JolNarSpatialConduitNetwork::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_JolNarSpatialConduitNetwork::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_JolNarSpatialConduitNetwork::Clone(){
	return new e_JolNarSpatialConduitNetwork(*this);
}
string e_JolNarSpatialConduitNetwork::Save(){
	return string();
}
void e_JolNarSpatialConduitNetwork::Load(std::string str){}
//////////////////////////////////////////////////
e_JolNarElectroResonanceTurbines::e_JolNarElectroResonanceTurbines(){
	id = "ElectroResonanceTurbines";
	name = "Electro-Resonance Turbines";
	description = "When an opponent activate a system you control, gain 3 TG";
	cost = 2;
	color = RaceTech;
	race = JolNar;
	TT = ttElectroResonanceTurbines;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_JolNarElectroResonanceTurbines::GetQ(GameEffectQs queue){
	return (queue == eq_ActivateSystem);
}
GameEffectRets e_JolNarElectroResonanceTurbines::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Army* arriving = EP.army1;
	int* check = EP.CommandCounters;
	char buff[255];
	if ((arriving->GetOwner() != player) && (HexController(arriving->GetHex()) == player)){
		player->GiveGoods(3);
		sprintf(buff,"You receive 3 Trade Goods because player %s has activated your system %s (Electro-resonance Turbines)",arriving->GetOwner()->GetName().c_str(),arriving->GetHex()->GetId().c_str());
		_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
	}
	return er_none;
}

GameEffect* e_JolNarElectroResonanceTurbines::Clone(){
	return new e_JolNarElectroResonanceTurbines(*this);
}
string e_JolNarElectroResonanceTurbines::Save(){
	return string();
}
void e_JolNarElectroResonanceTurbines::Load(std::string str){}
//////////////////////////////////////////////////
e_JolNarRacialAbilityStats::e_JolNarRacialAbilityStats(){
	id = "JolNarRacialAbilityStats";
}
bool e_JolNarRacialAbilityStats::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_JolNarRacialAbilityStats::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	army->ModUnitAbility(uaSpaceBattle,1);
	army->ModUnitAbility(uaLandBattle,1);
	army->ModUnitAbility(uaAFB,1);
	army->ModUnitAbility(uaCannon,1);
	return er_none;
}

GameEffect* e_JolNarRacialAbilityStats::Clone(){
	return new e_JolNarRacialAbilityStats(*this);
}
string e_JolNarRacialAbilityStats::Save(){
	return string();
}
void e_JolNarRacialAbilityStats::Load(std::string str){}
//////////////////////////////////////////////////////////////
e_JolNarTechnology::e_JolNarTechnology(){
	id = "JolNarTechnology";
}
bool e_JolNarTechnology::GetQ(GameEffectQs queue){
	if ((queue==eq_StratSecStart)||(queue==eq_StratSecEnd))
		return true;
	return false;
}
GameEffectRets e_JolNarTechnology::Execute(ExecuteParams EP){
	Player* player = EP.player;
	e_StratCard* SC = EP.stratcard;
	GameEffectQs Q = EP.queue;
	int SACCneed;
	if (SC->GetType()==Technology){
		if (Q == eq_StratSecStart){
			SACCneed = ((e_Technology*)SC)->TECHNOLOGY_SECONDARY_COUNTERS_COST;
			if (player->GetCountersSA()>=SACCneed){
				player->TakeCounter(CC_strat);
				((e_Technology*)SC)->TECHNOLOGY_SECONDARY_COUNTERS_COST = 0;
				SC->UseP = true;
				SC->UseS = true;
			}	
		}
		if (Q == eq_StratSecEnd){
			SC->reset();
		}		
	};
	return er_none;
}

GameEffect* e_JolNarTechnology::Clone(){
	return new e_JolNarTechnology(*this);
}
string e_JolNarTechnology::Save(){
	return string();
}
void e_JolNarTechnology::Load(std::string str){}
////////////////////////////////////////////////////////
e_JolNarReroll::e_JolNarReroll(){
	id = "JolNarReroll";
	image = EMPTY_EVENT_IMG;
}
bool e_JolNarReroll::GetQ(GameEffectQs queue){
	//eq_AfterRollingDicesAction
	if (queue == eq_AfterRollingDicesAction)
		return true;
	return false;
}
GameEffectRets e_JolNarReroll::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	char str[127];
	Roll* r = EP.rolls;
	Roll* selection=0;
	int N = EP.rollNumber;
	int rerolls=0;
	int oldthrow;
	int newthrow;
	if (attArmy->GetOwner()->GetCountersSA()>0){
		//rerolls = attArmy->GetOwner()->GetCountersSA();
		_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
		//while ((rerolls>0) && SelectDialogYesNo("Reroll dice using 1 SACC?")){
		if (SelectDialogYesNo("Reroll one dice using 1 SACC?")){
			selection = SelectDialogRoll(attArmy->GetOwner(),r,N);
			if (selection!=0){
				oldthrow=selection->value;
				newthrow=rand()%DICE+1;
				selection->value=newthrow;
				selection->isRerolled=true;
				sprintf(str,"Player %s rerolls dice: %d -> %d",attArmy->GetOwner()->GetName().c_str(),oldthrow,newthrow);
				_Interface.PrintThingAll(str);
				attArmy->GetOwner()->TakeCounter(CC_strat);
				rerolls=attArmy->GetOwner()->GetCountersSA();
			}
		}
	}
	else
		_Interface.PrintThingPlayer(attArmy->GetOwner()->GetNumber()-1,"You have no SACC to pay this ability");
	return er_none;
}

GameEffect* e_JolNarReroll::Clone(){
	return new e_JolNarReroll(*this);
}
string e_JolNarReroll::Save(){
	return string();
}
void e_JolNarReroll::Load(std::string str){}
//////////////////////////////////////////////////////
class e_JolNarStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttHylar);
		curPlayer->GiveTech(ttAntimass);
		curPlayer->GiveTech(ttEnviroCompensator);
		curPlayer->GiveTech(ttSarweenTools);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_SarweenTools);
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_JolNarRacialAbilityStats);
		curPlayer->AddGameEffect(new e_JolNarTechnology);
		curPlayer->AddGameEffect(new e_JolNarReroll);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 2;
		units->unit[DR] = 1;
		units->unit[CR] = 2;
		units->unit[FG] = 1;
		units->unit[PDS] = 2;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_JolNarStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};