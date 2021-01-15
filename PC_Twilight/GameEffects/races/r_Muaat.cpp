e_MuaatWarSunSpeed::e_MuaatWarSunSpeed(){
	id = "MuaatWarSunSpeed";
}
bool e_MuaatWarSunSpeed::GetQ(GameEffectQs queue){
	if (queue == eq_BeforeMovement)
		return true;
	return false;
}
GameEffectRets e_MuaatWarSunSpeed::Execute(ExecuteParams EP){
	Player* player = EP.player;
	GameEffectQs Q = EP.queue;
	if ((Q == eq_BeforeMovement) && (!player->GotTech(ttDeepSpaceCannon))){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if ((*aiter)->GetOwner() == player)
				for (int i=1; i<=(*aiter)->StackSize(WS);i++)
					(*aiter)->GetUnit(WS,i)->ModAbility(uaHyperDrive,-1);
		}
	}
	return er_none;
}
GameEffect* e_MuaatWarSunSpeed::Clone(){
	return new e_MuaatWarSunSpeed(*this);
}
string e_MuaatWarSunSpeed::Save(){
	return string();
}
void e_MuaatWarSunSpeed::Load(std::string str){}
////////////////////////////////////////////////////
bool e_MuaatWarSunSpawn::GetQ(GameEffectQs queue){
	if (queue == eq_AAA)
		return true;
	return false;
}
e_MuaatWarSunSpawn::e_MuaatWarSunSpawn(){
	id = "WarSunSpawn";
	image = EMPTY_EVENT_IMG;
}
GameEffectRets e_MuaatWarSunSpawn::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int a,b;
	Army* army;
	int ds = player->CheckUnits().at(DS);
	if (!player->GetCountersSA()){//нет каунтеров
		_Interface.PrintThingAll("There is no SACC for using this ability");
		return er_none;
	}
	vector<int> ret;
	ret.clear();
	while (true){
		ret = _GrIn.SysChoise("Select system with Warsun to place 2 Fighters or 1 Destroyer by spending 1 SACC",true);
		if (ret.size() == 0){
			Log("e_MuaatWarSunSpawn::Execute : pass on hex select");
			return er_none;
		}
		else{
			a = ret.at(0);
			b = ret.at(1);
			if (!_Map.GetHexh(a,b)){
				Eggog("e_MuaatWarSunSpawn::Execute : bad hex selection");
				return er_none;
			}
			else{
				army = 0;
				army = FindAllyArmy(player,_Map.GetHexh(a,b));
				if ((army == 0) || (army->StackSize(WS) == 0)){
					_Interface.PrintThingAll("There is no your Warsun in this hex");
					continue;
				}
				else{
					_GrIn.InitChoise("Select unit to spawn",true);
					_GrIn.AddOption(SHIPS_IMG[FG],"2 Fighters");
					_GrIn.AddOption(SHIPS_IMG[DS],"1 Destroyer");
					ret.clear();
					ret = _GrIn.LaunchChoise();
					if (ret.size() == 0){
						Log("e_MuaatWarSunSpawn::Execute : pass on unit select");
						continue;
					}
					else{
						if (ret.at(0) == 1){
							Log("e_MuaatWarSunSpawn::Execute : spawn fighters");
							army->AddUnits(FG,2);
						}
						if (ret.at(1) == 1){
							if (ds < defUnitNumbers[DS]){
								Log("e_MuaatWarSunSpawn::Execute : spawn destroyer");
								army->AddUnit(DS);
							}
							else{
								_Interface.PrintThingAll("Too many Destroyers, can't spawn");
								continue;
							}
						}
						player->TakeCounter(CC_strat);
						break;
					}
				}
			}
		}
	}
	return er_normal;
}
GameEffect* e_MuaatWarSunSpawn::Clone(){
	return new e_MuaatWarSunSpawn(*this);
}
string e_MuaatWarSunSpawn::Save(){
	return string();
}
void e_MuaatWarSunSpawn::Load(std::string str){}
////////////////////////////////////////////////////////////
bool e_MuaatFlagshipSpawn::GetQ(GameEffectQs queue){
	if (queue == eq_AAA)
		return true;
	return false;
}
e_MuaatFlagshipSpawn::e_MuaatFlagshipSpawn(){
	id = "FlagshipSpawn";
	image = EMPTY_EVENT_IMG;
}
GameEffectRets e_MuaatFlagshipSpawn::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char str[127];
	int cs = player->CheckUnits().at(CS);
	Army* army = 0;
	if (!player->GetCountersSA()){//нет каунтеров
		_Interface.PrintThingAll("There is no SACC for using this ability");
		return er_none;
	}
	if (cs >= defUnitNumbers[CS]){
		_Interface.PrintThingAll("Too many Cruisers, can't spawn");
		return er_none;
	}
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if (((*aiter)->GetOwner() == player) && ((*aiter)->StackSize(FM)))
			army = *aiter;
	if (army == 0){
		_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no your Flagship on the board");
		return er_none;
	}
	sprintf(str,"Spawn 1 Cruiser in %s?",army->GetHex()->GetId().c_str());
	if (SelectDialogYesNo(str)){
		Log("e_MuaatFlagshipSpawn::Execute : spawn");
		army->AddUnit(CS);
	}
	else{
		Log("e_MuaatFlagshipSpawn::Execute : cancel");
		return er_none;
	}
	return er_normal;
}
GameEffect* e_MuaatFlagshipSpawn::Clone(){
	return new e_MuaatFlagshipSpawn(*this);
}
string e_MuaatFlagshipSpawn::Save(){
	return string();
}
void e_MuaatFlagshipSpawn::Load(std::string str){}
////////////////////////////////////////////////////////////
e_MuaatMagmusReactor::e_MuaatMagmusReactor(){
	id = "MagmusReactor";
	name = "Magmus Reactor";
	description = "Warsuns gain +1 Movement and have a base cost of 10";
	cost = 5;
	color = RaceTech;
	race = Muaat;
	TT = ttMagmusReactor;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_MuaatMagmusReactor::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeMovement)||(queue==eq_BeforeBuild))
		return true;
	return false;
}
GameEffectRets e_MuaatMagmusReactor::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_BeforeBuild)
		player->GetUnitStats()->SetModifier(WS,sCOST,-2);
	if (Q == eq_BeforeMovement){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if ((*aiter)->GetOwner()==player)
				for (int i=1; i<=(*aiter)->StackSize(WS);i++)
					(*aiter)->GetUnit(WS,i)->ModAbility(uaHyperDrive,+1);
		}
	}
	return er_none;
}
GameEffect* e_MuaatMagmusReactor::Clone(){
	return new e_MuaatMagmusReactor(*this);
}
string e_MuaatMagmusReactor::Save(){
	return string();
}
void e_MuaatMagmusReactor::Load(std::string str){}
/////////////////////////////////////////////////////////////////
e_MuaatNovaSeed::e_MuaatNovaSeed(){
	id = "NovaSeed";
	image = EMPTY_EVENT_IMG;
	name = "Nova Seed";
	description = "As an action, you may remove this card from the game to replace a system you control with a Supernova system tile. This may not be used on Mecatol Rex, a Home System, or adjacent to a red-bordered system";
	cost = 3;
	color = RaceTech;
	race = Muaat;
	TT = ttNovaSeed;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	isNuked = 0;
}
bool e_MuaatNovaSeed::GetQ(GameEffectQs queue){
	if ((queue==eq_AAA) && !isNuked)
		return true;
	return false;
}
GameEffectRets e_MuaatNovaSeed::Execute(ExecuteParams EP){
	Player* player = EP.player;
	vector<int> ret;
	Hex* nukehex;
	Army* army;
	int i;
	bool cnf;
	char buff[255];
	while (true){
		ret = _GrIn.SysChoise("Select system to destroy",true);
		if (ret.size() == 0)
			return er_none;
		nukehex = _Map.GetHexh(ret.at(0),ret.at(1));
		if (HexController(nukehex) != player){
			_Interface.PrintThingPlayer(player->GetNumber() - 1,"You don't control this system");
			continue;
		}
		if (nukehex->GetPlanet(1) != 0){
			if (nukehex->GetPlanet(1)->GetName().compare(MECATOLREX) == 0){
				_Interface.PrintThingPlayer(player->GetNumber() - 1,"You can't nuke Mecatol");
				continue;
			}
		}
		cnf = false;
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
			if ((_Players[i]->GetHS() == nukehex) || (_Players[i]->GetExtraHS() == nukehex))
				cnf = true;
		if (cnf){
			_Interface.PrintThingPlayer(player->GetNumber() - 1,"You can't nuke Home System");
			continue;
		}
		cnf = false;
		for (i = 0; i < nukehex->GetLinkedHexes()->GetLinkNumber(); i++)
			if (nukehex->GetLinkedHexes()->GetLink(i) == ltBound)
				if (nukehex->GetLinkedHexes()->GetLinkedHex(i)->GetDanger() != DT_NONE)
					cnf = true;
		if (cnf){
			_Interface.PrintThingPlayer(player->GetNumber() - 1,"You can't nuke system near special system");
			continue;
		}
		sprintf(buff,"Nuke system %s?",nukehex->GetId().c_str());
		if (!SelectDialogYesNo(buff))
			continue;
		//прорвались через условия
		for (i = 1; i <= MAX_PLANETS; i++){//убираем планеты
			if (nukehex->GetPlanet(i) != 0){
				player->ExecuteGameEffect(ExecuteParams(eq_PlanetDestroyed,player,nukehex->GetPlanet(i)));
				army = FindArmy(nukehex,player,false,nukehex->GetPlanet(i));
				if (army != 0)
					army->KillArmy();
				player->DeCapture(nukehex->GetPlanet(i));
			}
		}
		sprintf(buff,"Player %s has nuked system %s",player->GetName().c_str(),nukehex->GetId().c_str());
		_Interface.PrintThingAll(buff);
		string str;
		Interface().GetSystemsFile(str, SpecSys);
		SystemDeck* deckspecial;
		SystemTranslator().translate(str,&deckspecial);
		int n = deckspecial->FindById("MuaatSupernova");
		if (n == 0)
			Log("e_MuaatNovaSeed::Execute : can't find MuaatSupernova hex");
		_Map.LaySystemh(nukehex->xc,nukehex->yc,deckspecial->Choose(n)->elem);
		isNuked = 1;
		player->CheckFleets();
		ClearArmies();
		//создает связи между выложенными порталами
		_Map.RemovePortalLinks();
		_Map.CreateHexLinks(false,true);
		break;
	}
	return er_normal;
}

GameEffect* e_MuaatNovaSeed::Clone(){
	return new e_MuaatNovaSeed(*this);
}
string e_MuaatNovaSeed::Save(){
	std::stringstream ss;
	ss<<isNuked;
	return ss.str();
}
void e_MuaatNovaSeed::Load(std::string str){
	std::istringstream iss(str);
	iss>>isNuked;
}
///////////////////////////////////////////////////////////////////
e_MuaatSuperNovaMove::e_MuaatSuperNovaMove(){
	id = "MuaatSuperNovaMove";
}
bool e_MuaatSuperNovaMove::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeMovement)
		return true;
	return false;
}
GameEffectRets e_MuaatSuperNovaMove::Execute(ExecuteParams EP){
	Player* player = EP.player;
	player->GetMoveStats()->pass[Supernova] = 1;
	return er_normal;
}

GameEffect* e_MuaatSuperNovaMove::Clone(){
	return new e_MuaatSuperNovaMove(*this);
}
string e_MuaatSuperNovaMove::Save(){
	return string();
}
void e_MuaatSuperNovaMove::Load(std::string str){}
/////////////////////////////////////////////////////////////////
class e_MuaatStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttSarweenTools);
		curPlayer->GiveTech(ttWarSun);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_SarweenTools);
		curPlayer->AddGameEffect(new e_WarSun);
		curPlayer->AddGameEffect(new e_MuaatWarSunSpeed);
		curPlayer->AddGameEffect(new e_MuaatWarSunSpawn);
		curPlayer->AddGameEffect(new e_MuaatFlagshipSpawn);
		curPlayer->AddGameEffect(new e_MuaatSuperNovaMove);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[WS] = 1;
		units->unit[FG] = 2;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_MuaatStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

