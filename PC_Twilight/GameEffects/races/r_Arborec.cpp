e_ArborecBioplasmosis::e_ArborecBioplasmosis(){
	id = "Bioplasmosis";
	name = "Bioplasmosis";
	description = "At the beginning of the round, you may move one of your GF from one planet you control to another planet you control in an adjacent system";
	cost = 3;
	color = RaceTech;
	race = Arborec;
	TT = ttBioplasmosis;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_ArborecBioplasmosis::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_ArborecBioplasmosis::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_ArborecBioplasmosis::Clone(){
	return new e_ArborecBioplasmosis(*this);
}
string e_ArborecBioplasmosis::Save(){
	return string();
}
void e_ArborecBioplasmosis::Load(std::string str){}
///////////////////////////////////////////////////////
e_ArborecSporeAcceleration::e_ArborecSporeAcceleration(){
	id = "SporeAcceleration";
	name = "Spore Acceleration";
	description = "Increase the Build Capacity for your GF by one";
	cost = 5;
	color = RaceTech;
	race = Arborec;
	TT = ttSporeAcceleration;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_ArborecSporeAcceleration::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_ArborecSporeAcceleration::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_ArborecSporeAcceleration::Clone(){
	return new e_ArborecSporeAcceleration(*this);
}
string e_ArborecSporeAcceleration::Save(){
	return string();
}
void e_ArborecSporeAcceleration::Load(std::string str){}
//////////////////////////////////////////////
class e_ArborecStartUnits:public e_StartUnits{
public:
	bool GetQ(GameEffectQs queue){
		if (queue==eq_Pregame)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* curPlayer = EP.player;
		// торговые договоры
		EP.player->AddTrade(1);
		EP.player->AddTrade(2);
		spawnarmy* units;
		//стартовые техи
		curPlayer->GiveTech(ttStasis);
		curPlayer->GiveTech(ttAntimass);
		//curPlayer->GetUnitStats()->SetModifier(CS,sGFCP,1);
		//curPlayer->GetUnitStats()->SetModifier(DR,sGFCP,1);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_StasisCapsules);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[CR] = 1;
		units->unit[CS] = 1;
		units->unit[FG] = 2;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		curPlayer->ExecuteGameEffect(ExecuteParams(eq_LaunchEffect,curPlayer));
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_ArborecStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};