e_YssarilShuttleLogistics::e_YssarilShuttleLogistics(){
	id = "ShuttleLogistics";
	image = EMPTY_EVENT_IMG;
	name = "Shuttle Logistics";
	description = "During Status Phase you may move your units from one planet you control to another planet you control in the same or an adjacent system; neither may contain enemy ships";
	cost = 3;
	color = RaceTech;
	race = Yssaril;
	TT = ttShuttleLogistics;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	done = false;
}
bool e_YssarilShuttleLogistics::GetQ(GameEffectQs queue){
	if (((queue == eq_StatusEnd) && !done) || (queue == eq_StrategyStart))
		return true;
	return false;
}
GameEffectRets e_YssarilShuttleLogistics::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> ret;
	Hex* hex1;
	Hex* hex2;
	Army* army;
	int p1,p2,i,j;
	Army* from;
	Army* to;
	char buff[255];
	char str[255];
	vector<Unit*> options;
	if ((Q == eq_StatusEnd) && (!done)){
		while (true){
			ClearArmies();
			ret = _GrIn.SysChoise("Select system to use Shuttle Logistic",true);
			if (ret.size() == 0)
				return er_none;
			hex1 = _Map.GetHexh(ret[0],ret[1]);
			army = FindArmy(hex1,0);
			if (army != 0){
				if ((army->GetOwner() != player) && (army->IsUnitWithAbility(uaCapitalShip))){
					_Interface.PrintThingPlayer(player->GetNumber()-1,"This system contain enemy ships");
					continue;
				}
			}
			p1 = SelectDialogPlanetInSystem(hex1,player,true);
			if (p1 <= 0){
				Log("e_YssarilShuttleLogistics::Execute : pass or no planets here");
				continue;
			}
			if (hex1->GetPlanet(p1) == 0){
				Log("e_YssarilShuttleLogistics::Execute : No planet");
				continue;
			}
			from = FindArmy(hex1,player,false,hex1->GetPlanet(p1));
			if (from == 0){
				Log("e_YssarilShuttleLogistics::Execute : No units to transport");
				continue;
			}
			if (!from->IsUnitWithAbility(uaCarried)){
				Log("e_YssarilShuttleLogistics::Execute : No units to transport");
				continue;
			}
			ret = _GrIn.SysChoise("Select system to move",true);
			if (ret.size() == 0)
				continue;
			hex2 = _Map.GetHexh(ret[0],ret[1]);
			army = FindArmy(hex2,0);
			if (army != 0){
				if ((army->GetOwner() != player) && (army->IsUnitWithAbility(uaCapitalShip))){
					_Interface.PrintThingPlayer(player->GetNumber()-1,"This system contain enemy ships");
					continue;
				}
			}
			if (hex1->GetLinkedHexes()->GetLink(hex2) == ltNone){
				Log("e_YssarilShuttleLogistics::Execute : not adjacent");
				continue;
			}
			p2 = SelectDialogPlanetInSystem(hex2,player,true);
			if (p2 <= 0){
				Log("e_YssarilShuttleLogistics::Execute : pass or no planets here");
				continue;
			}
			if (hex2->GetPlanet(p2) == 0){
				Log("e_YssarilShuttleLogistics::Execute : No planet");
				continue;
			}
			if ((hex1 == hex2) && (p1 == p2)){
				Log("e_YssarilShuttleLogistics::Execute : same from and to");
				continue;
			}
			to = FindArmy(hex2,player,true,hex2->GetPlanet(p2));
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
			done = true;
			ClearArmies();
			break;
		}	
	}
	if (Q == eq_StrategyStart)
		done = false;
	return er_none;
}

GameEffect* e_YssarilShuttleLogistics::Clone(){
	return new e_YssarilShuttleLogistics(*this);
}
string e_YssarilShuttleLogistics::Save(){
	return string();
}
void e_YssarilShuttleLogistics::Load(std::string str){}
///////////////////////////////////////////////////////
e_YssarilMageonImplants::e_YssarilMageonImplants(){
	id = "MageonImplants";
	name = "Mageon Implants";
	description = "When looking at the hand of your opponentТs AC using your racial ability, you may steal one card of your choice and put it on your hand";
	cost = 4;
	color = RaceTech;
	race = Yssaril;
	TT = ttMageonImplants;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_YssarilMageonImplants::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_YssarilMageonImplants::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_YssarilMageonImplants::Clone(){
	return new e_YssarilMageonImplants(*this);
}
string e_YssarilMageonImplants::Save(){
	return string();
}
void e_YssarilMageonImplants::Load(std::string str){}
//////////////////////////////////////////////
e_YssarilAdditionalAC::e_YssarilAdditionalAC(){
	id = "YssarilAdditionalAC";
}
bool e_YssarilAdditionalAC::GetQ(GameEffectQs queue){
	if (queue==eq_StatusPhase)
		return true;
	return false;
}
GameEffectRets e_YssarilAdditionalAC::Execute(ExecuteParams EP){
	int* ACs = EP.ActionCards;
	*ACs = *ACs + 1;
	return er_none;
}
GameEffect* e_YssarilAdditionalAC::Clone(){
	return new e_YssarilAdditionalAC(*this);
}
string e_YssarilAdditionalAC::Save(){
	return string();
}
void e_YssarilAdditionalAC::Load(std::string str){}
//////////////////////////////////////////////
e_YssarilWait::e_YssarilWait(){
	id = "YssarilWait";
	image = EMPTY_EVENT_IMG;
	cooldown = 0;
}
bool e_YssarilWait::GetQ(GameEffectQs queue){
	if (((queue==eq_AAA) && !cooldown) || (queue == eq_ActionStart) || (queue == eq_StatusStart))
		return true;
	return false;
}
GameEffectRets e_YssarilWait::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char buff[255];
	if ((Q == eq_ActionStart) && (cooldown > 0))
		cooldown--;
	if (Q == eq_StatusStart)
		cooldown = 0;
	if ((Q==eq_AAA) && !cooldown){
		if (SelectDialogYesNo("Skip turn?")){
			cooldown = 2;
			sprintf(buff,"Player %s skips his turn",player->GetName().c_str());
			_Interface.PrintThingAll(buff);
			return er_normal;
		}
	}
	return er_none;
}
GameEffect* e_YssarilWait::Clone(){
	return new e_YssarilWait(*this);
}
string e_YssarilWait::Save(){
	std::stringstream ss;
	ss<<cooldown;
	return ss.str();
}
void e_YssarilWait::Load(std::string str){
	std::istringstream iss(str);
	iss>>cooldown;
}
//////////////////////////////////////////////
e_YssarilSpy::e_YssarilSpy(){
	id = "YssarilSpy";
	image = EMPTY_EVENT_IMG;
	active = false;
}
bool e_YssarilSpy::GetQ(GameEffectQs queue){
	if (((queue == eq_StrategyAction) && active) || (queue == eq_StrategyEnd))
		return true;
	return false;
}
GameEffectRets e_YssarilSpy::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Player* tosteal = 0;
	int k = -1;
	char buff[255];
	string banner;
	if (Q == eq_StrategyEnd)
		active = true;
	if (Q == eq_StrategyAction){
		_Interface.SetCurrPlayer(player->GetNumber() - 1);
		_GrIn.InitChoise("You can watch Action Cards of another player",true);
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			if (_Players[i] != player){
				sprintf(buff,"%s (%d AC)",_Players[i]->GetName().c_str(),_Players[i]->GetActionsNumber());
				_GrIn.AddOption(_Players[i]->GetBanner(),buff);
			}
		}
		vector<int> ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			return er_none;
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			if (_Players[i] != player){
				k++;
				if (ret[k] == 1)
					tosteal = _Players[i];
			}
		}
		if (tosteal == 0)
			return er_none;
		sprintf(buff,"Player %s watches your Action Cards!",player->GetName().c_str());
		_Interface.PrintThingPlayer(tosteal->GetNumber()-1,buff);
		int acs = 0;
		for (list<GameEffect*>::iterator iter = tosteal->_PlayerGameEffect.begin(); iter != tosteal->_PlayerGameEffect.end(); iter++){
			if ((*iter)->GetQ(eq_ActionCard)){
				sprintf(buff,"Player %s has %s Action Card",tosteal->GetName().c_str(),((e_ActionCard*)(*iter))->GetName().c_str());
				_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
				acs++;
			}
		}
		active = false;
		e_ActionCard* AC;
		if ((player->GotTech(ttMageonImplants)) && acs && SelectDialogYesNo("Steal 1 Action Card?")){
			AC = SelectDialogActionCard("Select Action Card to steal",tosteal,true);
			if (AC == 0)
				return er_none;
			sprintf(buff,"You steal %s Action Card from player %s",AC->GetName().c_str(),tosteal->GetName().c_str());
			_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
			sprintf(buff,"Player %s steals Action Card %s from you!",player->GetName().c_str(),AC->GetName().c_str());
			_Interface.PrintThingPlayer(tosteal->GetNumber()-1,buff);
			player->AddGameEffect(AC->Clone());
			tosteal->RemoveGameEffect(AC->GetId());
		}
	}
	return er_none;
}
GameEffect* e_YssarilSpy::Clone(){
	return new e_YssarilSpy(*this);
}
string e_YssarilSpy::Save(){
	return string();
}
void e_YssarilSpy::Load(std::string str){}
////////////////////////////////////////////////////////////
class e_YssarilStartUnits:public GameEffect{
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
		EP.player->AddTrade(1);
		//стартовые техи
		curPlayer->GiveTech(ttAntimass);
		curPlayer->GiveTech(ttXRD);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_XRDtransporters);
		curPlayer->AddGameEffect(new e_YssarilAdditionalAC);
		curPlayer->AddGameEffect(new e_YssarilWait);
		curPlayer->AddGameEffect(new e_YssarilSpy);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 5;
		units->unit[FG] = 2;
		units->unit[CR] = 2;
		units->unit[CS] = 1;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		curPlayer->RemoveGameEffect("ActionCardLimit");
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_YssarilStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};