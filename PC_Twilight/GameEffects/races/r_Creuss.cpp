e_CreussDimensionalSplicers::e_CreussDimensionalSplicers(){
	id = "DimensionalSplicers";
	name = "Dimensional Splicers";
	description = "At the start of a battle containing a Wormhole and at least one of your ships, you may assign 1 hit to an enemy ship of your choice";
	cost = 3;
	color = RaceTech;
	race = Creuss;
	TT = ttDimensionalSplicers;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_CreussDimensionalSplicers::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_CreussDimensionalSplicers::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_CreussDimensionalSplicers::Clone(){
	return new e_CreussDimensionalSplicers(*this);
}
string e_CreussDimensionalSplicers::Save(){
	return string();
}
void e_CreussDimensionalSplicers::Load(std::string str){}
///////////////////////////////////////////////////////
e_CreussSlaveWormholeGenerator::e_CreussSlaveWormholeGenerator(){
	id = "SlaveWormholeGenerator";
	name = "Slave Wormhole Generator";
	description = "At the start of the Status Phase, you may place (or move) your extra 'A' or 'B' wormhole token into an empty or friendly non-Home System";
	cost = 5;
	color = RaceTech;
	race = Creuss;
	TT = ttSlaveWormholeGenerator;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_CreussSlaveWormholeGenerator::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_CreussSlaveWormholeGenerator::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_CreussSlaveWormholeGenerator::Clone(){
	return new e_CreussSlaveWormholeGenerator(*this);
}
string e_CreussSlaveWormholeGenerator::Save(){
	return string();
}
void e_CreussSlaveWormholeGenerator::Load(std::string str){}
///////////////////////////////////////////////////
class e_CreussStartUnits:public e_StartUnits{
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
		curPlayer->GiveTech(ttXRD);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_XRDtransporters);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[DS] = 2;
		units->unit[CR] = 1;
		units->unit[FG] = 2;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetExtraHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_CreussStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};