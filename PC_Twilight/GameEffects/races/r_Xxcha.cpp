e_XxchaDiplomats::e_XxchaDiplomats(){
	id = "XxchaDiplomats";
	name = "Diplomats";
	description = "You may spend 1 SACC to prevent activation of your system (once per round)";
	cost = 5;
	color = RaceTech;
	race = Xxcha;
	TT = ttDiplomats;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	used = 0;
}
bool e_XxchaDiplomats::GetQ(GameEffectQs queue){
	return ((queue == eq_ActivateSystem) || (queue == eq_StatusEnd));
}
GameEffectRets e_XxchaDiplomats::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Army* arriving = EP.army1;
	int* check = EP.CommandCounters;
	char buff[255];
	if ((Q == eq_ActivateSystem) && !used && player->GetCountersSA()){
		if ((arriving->GetOwner() != player) && (HexController(arriving->GetHex()) == player)){
			_Interface.SetCurrPlayer(player->GetNumber()-1);
			sprintf(buff,"Cancel activation of system %s by player %s?",arriving->GetHex()->GetId().c_str(),arriving->GetOwner()->GetName().c_str());
			if (SelectDialogYesNo(buff)){
				*check = 3;
				used = 1;
				player->TakeCounter(0);
				ClearArmies();
				sprintf(buff,"Player %s cancel activation of system %s",player->GetName().c_str(),arriving->GetHex()->GetId().c_str());
				_Interface.PrintThingPlayer(arriving->GetOwner()->GetNumber()-1,buff);
			}
			_Interface.SetCurrPlayer(arriving->GetOwner()->GetNumber()-1);
		}
	}
	if (Q == eq_StatusEnd)
		used = 0;
	return er_none;
}

GameEffect* e_XxchaDiplomats::Clone(){
	return new e_XxchaDiplomats(*this);
}
string e_XxchaDiplomats::Save(){
	std::stringstream ss;
	ss<<used;
	return ss.str();
}
void e_XxchaDiplomats::Load(std::string str){
	std::istringstream iss(str);
	iss>>used;
}
///////////////////////////////////////////////////////
e_XxchaInstinctTraining::e_XxchaInstinctTraining(){
	id = "InstinctTraining";
	name = "Instinct Training";
	description = "Once per game round, you may spend 1 SACC to cancel an AC just played by your opponent";
	cost = 4;
	color = RaceTech;
	race = Xxcha;
	TT = ttInstinctTraining;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_XxchaInstinctTraining::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_XxchaInstinctTraining::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_XxchaInstinctTraining::Clone(){
	return new e_XxchaInstinctTraining(*this);
}
string e_XxchaInstinctTraining::Save(){
	return string();
}
void e_XxchaInstinctTraining::Load(std::string str){}
//////////////////////////////////////////////
e_XxchaRacialAbilityStats::e_XxchaRacialAbilityStats(){
	id = "XxchaRacialAbilityStats";
}
bool e_XxchaRacialAbilityStats::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeBattleRound)
		return true;
	return false;
}
GameEffectRets e_XxchaRacialAbilityStats::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	int round = EP.fround;
	if ((round==1)&&(defArmy!=0)&&(!defArmy->isDefeated())){
		defArmy->ModUnitAbility(uaSpaceBattle,1);
		defArmy->ModUnitAbility(uaLandBattle,1);
	};
	return er_none;
}
GameEffect* e_XxchaRacialAbilityStats::Clone(){
	return new e_XxchaRacialAbilityStats(*this);
}
string e_XxchaRacialAbilityStats::Save(){
	return string();
}
void e_XxchaRacialAbilityStats::Load(std::string str){}
////////////////////////////////////////////////
e_XxchaDiplomacy::e_XxchaDiplomacy(){
	id = "XxchaDiplomacy";
}
bool e_XxchaDiplomacy::GetQ(GameEffectQs queue){
	if ((queue==eq_StratSecStart)||(queue==eq_StratSecEnd))
		return true;
	return false;
}
GameEffectRets e_XxchaDiplomacy::Execute(ExecuteParams EP){
	Player* player = EP.player;
	e_StratCard* SC = EP.stratcard;
	GameEffectQs Q = EP.queue;
	int* r;
	int SACCneed=0;
	if (SC->GetType()==Diplomacy){
		if (Q == eq_StratSecStart){
			SACCneed = ((e_Diplomacy*)SC)->DIPLOMACY_COUNTERS_COST;
			if (player->GetCountersSA()>=SACCneed){
				player->TakeCounter(CC_strat);
				_GrIn.InitChoise("Play primary or secondary ability of diplomacy SC?");
				_GrIn.AddOption(EMPTY_EVENT_IMG,"Primary");
				_GrIn.AddOption(EMPTY_EVENT_IMG,"Secondary");
				vector<int> tempvec = _GrIn.LaunchChoise();
				if (tempvec.size() != 0)
					r = &tempvec[0];
				if (r!=0){
					SC->UseP = false;
					SC->UseS = false;
					if (r[0]==1)
						SC->UseP = true;
					else
						SC->UseS = true;
				}
			}
		}	
		if (Q == eq_StratSecEnd)
			SC->reset();
	};
	return er_none;
}
GameEffect* e_XxchaDiplomacy::Clone(){
	return new e_XxchaDiplomacy(*this);
}
string e_XxchaDiplomacy::Save(){
	return string();
}
void e_XxchaDiplomacy::Load(std::string str){}
////////////////////////////////////////////////////
e_XxchaVeto::e_XxchaVeto(){
	id = "XxchaVeto";
}
bool e_XxchaVeto::GetQ(GameEffectQs queue){
	if (queue==eq_PreVotings)
		return true;
	return false;
}
GameEffectRets e_XxchaVeto::Execute(ExecuteParams EP){
	ostringstream ss;
	if (EP.player->GetCountersSA() < 1)
		return er_none;
	ss<<"Do you want to discard "<<(**EP.politicalcard).GetId()<<" for "<<1<<" counter?";
	if (SelectDialogYesNo(ss.str())){
		EP.player->TakeCounter(CC_strat,1);
		*(EP.politicalcard) = _GameStats.DrawPolitic();
		ss.str("");
		_Interface.PrintThingAll("Veto has been used. New agenda is:");
		_Interface.PrintThingAll((*EP.politicalcard)->GetEffect());
	}
	return er_none;
}
GameEffect* e_XxchaVeto::Clone(){
	return new e_XxchaVeto(*this);
}
string e_XxchaVeto::Save(){
	return string();
}
void e_XxchaVeto::Load(std::string str){}
////////////////////////////////////////////////////
class e_XxchaStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttEnviroCompensator);
		curPlayer->GiveTech(ttAntimass);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_XxchaRacialAbilityStats);
		curPlayer->AddGameEffect(new e_XxchaDiplomacy);
		curPlayer->AddGameEffect(new e_XxchaVeto);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 2;
		units->unit[FG] = 3;
		units->unit[CR] = 1;
		units->unit[CS] = 2;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_XxchaStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};