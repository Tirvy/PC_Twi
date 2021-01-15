e_SaarFloatingFactories::e_SaarFloatingFactories(){
	name = "Floating Factories";
	description = "Space Docks may sustain 5 Fighters and have a build limit of 5. Additionally, they get +1 movement";
	cost = 3;
	color = RaceTech;
	race = Saar;
	TT = ttFloatingFactories;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_SaarFloatingFactories::GetQ(GameEffectQs queue){
	return ((queue==eq_BeforeMovement) || (queue==eq_BeforeBuild) || (queue == eq_AfterRefreshAbilities));
}
GameEffectRets e_SaarFloatingFactories::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Unit* unit = EP.unit;
	Army* army = EP.army1;
	int i;
	if (Q == eq_BeforeMovement){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if ((*aiter)->GetOwner() == player)
				for (i = 1; i <= (*aiter)->StackSize(DCK);i++)
					(*aiter)->GetUnit(DCK,i)->ModAbility(uaHyperDrive,+1);
	}
	if (Q == eq_BeforeBuild){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if ((*aiter)->GetOwner() == player)
				for (i = 1; i <= (*aiter)->StackSize(DCK);i++)
					(*aiter)->GetUnit(DCK,i)->ModAbility(uaProduction,+1);
	}
	if (Q == eq_AfterRefreshAbilities){
		if (unit->Class == DCK){
			if (unit->HasAbility(uaCarrier))
				unit->ModAbility(uaCarrier,0,+2);
			else
				unit->AddAbility(uaCarrier,0,5);
		}
	}
	return er_none;
}

GameEffect* e_SaarFloatingFactories::Clone(){
	return new e_SaarFloatingFactories(*this);
}
string e_SaarFloatingFactories::Save(){
	return string();
}
void e_SaarFloatingFactories::Load(std::string str){}
///////////////////////////////////////////////////////
e_SaarChaosMapping::e_SaarChaosMapping(){
	name = "Chaos-Mapping";
	description = "You may activate an Asteroid Field. Your Fleet Supply limit in it is 3 (which cannot be modified)";
	cost = 2;
	color = RaceTech;
	race = Saar;
	TT = ttChaosMapping;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_SaarChaosMapping::GetQ(GameEffectQs queue){
	return ((queue==eq_BeforeMovement) || (queue==eq_AfterFleetSupply));
}
GameEffectRets e_SaarChaosMapping::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Army* army = EP.army1;
	int* supply = EP.FleetSupply;
	if (Q == eq_BeforeMovement)
		player->GetMoveStats()->active[Asteroids] = 1;
	if (Q == eq_AfterFleetSupply)
		if (army->GetHex()->GetDanger() == Asteroids)
			if (*supply > 3)
				*supply = army->GetOwner()->GetCountersFS() + (*supply - 3);
	return er_none;
}

GameEffect* e_SaarChaosMapping::Clone(){
	return new e_SaarChaosMapping(*this);
}
string e_SaarChaosMapping::Save(){
	return string();
}
void e_SaarChaosMapping::Load(std::string str){}
//////////////////////////////////////////////
e_SaarExploration::e_SaarExploration(){
	id = "SaarExploration";
}
bool e_SaarExploration::GetQ(GameEffectQs queue){
	return (queue == eq_OnCapture);
}
GameEffectRets e_SaarExploration::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Planet* planet = EP.planet;
	player->GiveGoods(1);
	char buff[255];
	sprintf(buff,"Player %s receives 1 Trade Good for capturing planet %s",player->GetName().c_str(),planet->GetName().c_str());
	_Interface.PrintThingAll(buff);
	return er_normal;
}
GameEffect* e_SaarExploration::Clone(){
	return new e_SaarExploration(*this);
}
string e_SaarExploration::Save(){
	return string();
}
void e_SaarExploration::Load(std::string str){}
//////////////////////////////////////////////
e_SaarDocks::e_SaarDocks(){
	id = "SaarDocks";
}
bool e_SaarDocks::GetQ(GameEffectQs queue){
	return ((queue==eq_BeforeMovement) || (queue==eq_BeforeBuild) || (queue==eq_Movement) || (queue==eq_DockBuild));
}
GameEffectRets e_SaarDocks::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Army* army = EP.army1;
	Unit* unit = EP.unit;
	Hex* hex = EP.hex;
	Army* fleet;
	Army* tarmy;
	int i;
	if (Q == eq_BeforeMovement){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if ((*aiter)->GetOwner() == player)
				for (i = 1; i <= (*aiter)->StackSize(DCK);i++)
					(*aiter)->GetUnit(DCK,i)->AddAbility(uaHyperDrive,1);
	}
	if (Q == eq_BeforeBuild){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if ((*aiter)->GetOwner() == player)
				for (i = 1; i <= (*aiter)->StackSize(DCK);i++)
					(*aiter)->GetUnit(DCK,i)->ModAbility(uaProduction,4);
	}
	if ((Q == eq_Movement) && (unit->Class == DCK)){
		unit->AssignAbility(uaProduction,FIELD_SKIP,0);
		Log("SaarDock::Execute : block production after movement");
	}
	if (Q == eq_DockBuild){
		Army* fleet = FindAnyArmy(hex);
		Army* army = 0;
		if (fleet == 0)
			fleet = NewArmy(player,hex);
		if (fleet->GetOwner() == player){
			for (int i = 1; i <= MAX_PLANETS; i++){
				if (hex->GetPlanet(i) != 0){
					tarmy = FindArmy(hex,player,false,hex->GetPlanet(i));
					if (tarmy != 0)
						while (tarmy->StackSize(DCK))
							MoveUnit(tarmy,fleet,tarmy->GetUnit(DCK));
				}
			}
		}
		else{
			for (int i = 1; i <= MAX_PLANETS; i++){
				if (hex->GetPlanet(i) != 0){
					tarmy = FindArmy(hex,player,false,hex->GetPlanet(i));
					if (tarmy != 0)
						if (tarmy->GetOwner() == player)
							while (tarmy->StackSize(DCK))
								tarmy->KillUnit(tarmy->GetUnit(DCK));
				}
			}
		}
	}
	return er_normal;
}
GameEffect* e_SaarDocks::Clone(){
	return new e_SaarDocks(*this);
}
string e_SaarDocks::Save(){
	return string();
}
void e_SaarDocks::Load(std::string str){}
//////////////////////////////////////////////
class e_SaarStartUnits:public e_StartUnits{
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
		curPlayer->AddGameEffect(new e_SaarExploration);
		curPlayer->AddGameEffect(new e_SaarDocks);
		curPlayer->AddGameEffect(new e_SaarFloatingFactories);
		curPlayer->RemoveGameEffect("HomeControl");
		curPlayer->RemoveGameEffect("DockBuildLimit");
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[FG] = 2;
		units->unit[CS] = 1;
		units->unit[CR] = 2;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		//подъем доков в космос
		Army* fleet = FindArmy(curPlayer->GetHS(),curPlayer);
		Army* army = 0;
		for (int i = 1; i <= MAX_PLANETS; i++){
			if (curPlayer->GetHS()->GetPlanet(i) != 0){
				army = FindArmy(curPlayer->GetHS(),curPlayer,false,curPlayer->GetHS()->GetPlanet(i));
				if (army != 0){
					while (army->StackSize(DCK))
						MoveUnit(army,fleet,army->GetUnit(DCK));
				}
			}
		}
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_SaarStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};