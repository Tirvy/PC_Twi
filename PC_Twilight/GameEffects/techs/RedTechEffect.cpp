//красные технологии

//Hylar V assault laser
e_HylarVAssualtLaser::e_HylarVAssualtLaser(){
	id = "Hylar";
	name = "Hylar V Assualt Laser";
	description = "Cruisers and Destroyers receive +1 on all combat rolls";
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttHylar;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_HylarVAssualtLaser::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_HylarVAssualtLaser::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	int N = attArmy->IsUnitWithAbility(uaLightShip);
	for (int i=1; i<=N; i++)
		attArmy->GetUnitWithAbility(uaLightShip,i)->ModAbility(uaSpaceBattle,-1);
	N = attArmy->StackSize(DS);
	for (int i=1;i<=N;i++)
		attArmy->GetUnit(DS,i)->ModAbility(uaAFB,-1);
	return er_none;
}
GameEffect* e_HylarVAssualtLaser::Clone(){
	return new e_HylarVAssualtLaser(*this);
}
string e_HylarVAssualtLaser::Save(){
	return string();
}
void e_HylarVAssualtLaser::Load(std::string str){}
//Deep Space Cannon
e_DeepSpaceCannon::e_DeepSpaceCannon(){
	id = "DeepSpaceCannon";
	name = "Deep Space Cannon";
	description = "PDS units may fire at adjacent hexes";
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttDeepSpaceCannon;
	prereq1 = ttHylar;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_DeepSpaceCannon::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_DeepSpaceCannon::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Player* curPlayer = EP.player;
	for (int i=1; i<=army->StackSize(PDS); i++)
		army->GetUnit(PDS,i)->AddAbility(uaDeepSpaceCannon,1);
	return er_none;
}
GameEffect* e_DeepSpaceCannon::Clone(){
	return new e_DeepSpaceCannon(*this);
}
string e_DeepSpaceCannon::Save(){
	return string();
}
void e_DeepSpaceCannon::Load(std::string str){}
//war sun
e_WarSun::e_WarSun(){
	id = "WarSun";
	name = "War Sun";
	description = "You may produce War Sun units";
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttWarSun;
	prereq1 = ttDeepSpaceCannon;
	prereq2 = ttSarweenTools;
	isboth = true;
}
bool e_WarSun::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeBuild)
		return true;
	return false;
}
GameEffectRets e_WarSun::Execute(ExecuteParams EP){
	Player* player = EP.player;
	player->GetUnitStats()->SetParametr(WS,sNP,1);
	return er_none;
}
GameEffect* e_WarSun::Clone(){
	return new e_WarSun(*this);
}
string e_WarSun::Save(){
	return string();
}
void e_WarSun::Load(std::string str){}
//Duranium Armor
e_DuraniumArmor::e_DuraniumArmor(){
	id = "DuraniumArmor";
	image = EMPTY_EVENT_IMG;
	name = "Duranium Armor";
	description = "At the end of each round of combat, you may repair 1 of your damaged units in the battle";
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttDuranium;
	prereq1 = ttDeepSpaceCannon;
	prereq2 = MAX_TECH;
	isboth = false;
	active = false;
}
bool e_DuraniumArmor::GetQ(GameEffectQs queue){
	if (((queue==eq_AfterBattleRoundAction) && active) || (queue == eq_BeforeBattleRound))
		return true;
	return false;
}
GameEffectRets e_DuraniumArmor::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Army* army = EP.army1;
	Unit* unit;
	if (Q == eq_AfterBattleRoundAction){
		if (army->IsUnitWithAbility(uaSustain,1)){
			_Interface.SetCurrPlayer(army->GetOwner()->GetId()-1);
			unit = SelectDialogOneUnit("Repair one damaged unit (duranium armor)",army,false,uaSustain,1);
			if (unit!=0){
				unit->AssignAbility(uaSustain,0);
				unit->HP=army->GetOwner()->GetUnitStats()->GetParametr(unit->Class,sHP);
				active = false;
			} 
		}
		else
			_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"No damaged units to repair");
	}
	if (Q == eq_BeforeBattleRound)
		active = true;
	return er_none;
}
GameEffect* e_DuraniumArmor::Clone(){
	return new e_DuraniumArmor(*this);
}
string e_DuraniumArmor::Save(){
	return string();
}
void e_DuraniumArmor::Load(std::string str){}
//Magen Defense Grid
e_MagenDefenseGrid::e_MagenDefenseGrid(){
	id = "MagenDefenseGrid";
	name = "Magen Defense Grid";
	description = "PDS receive +1 on all combat rolls, defenging GF with a PDS receive +1 on all combat rolls";
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttDuranium;
	prereq1 = ttDeepSpaceCannon;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_MagenDefenseGrid::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_MagenDefenseGrid::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* target = EP.army2;
	GameEffectQs Q = EP.queue;
	int attacker = EP.attacker;
	if (Q == eq_Battle){
		if (attacker==1){
			for (int i=1; i<=army->StackSize(PDS);i++)
				army->GetUnit(PDS,i)->ModAbility(uaCannon,-1);
		}
		if ((army->GetPlanet()!=0)&&(attacker==0)&&(army->StackSize(PDS)>0)){
			for (int i=1; i<=army->IsUnitWithAbility(uaInfantry);i++)
				army->GetUnitWithAbility(uaInfantry,i)->ModAbility(uaLandBattle,-1);
		}
	}
	return er_none;
}
GameEffect* e_MagenDefenseGrid::Clone(){
	return new e_MagenDefenseGrid(*this);
}
string e_MagenDefenseGrid::Save(){
	return string();
}
void e_MagenDefenseGrid::Load(std::string str){}
//Automated Defence turrets
e_ADT::e_ADT(){
	id = "ADT";
	name = "Automated Defense Turrets";
	description = "Destroyers receive +2 and roll 1 additional die on all Anti-Fighter Barrage rolls"; 
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttADT;
	prereq1 = ttHylar;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_ADT::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_ADT::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	for (int i=1; i<=army->StackSize(DS);i++)
		army->GetUnit(DS,i)->ModAbility(uaAFB,-2,1);
	return er_none;
}
GameEffect* e_ADT::Clone(){
	return new e_ADT(*this);
}
string e_ADT::Save(){
	return string();
}
void e_ADT::Load(std::string str){}
//Assault Cannon
e_AssaultCannon::e_AssaultCannon(){
	id = "AssaultCannon";
	name = "Assault Cannon";
	description = "Each Dreadnought may fire one free shot before a Space Battle begins, hits are applied immediately"; 
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttAssaultCannon;
	prereq1 = ttADT;
	prereq2 = ttCybernetics;
	isboth = true;
	image = SHIPS_IMG[DR];
	active = false;
}
bool e_AssaultCannon::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattle) || ((queue == eq_BeforeBattleAction) && active))
		return true;
	return false;
}
GameEffectRets e_AssaultCannon::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	GameEffectQs Q = EP.queue;
	if (Q == eq_BeforeBattle)
		if (attArmy->GetPlanet()==0)
			active = true;
		else
			active = false;
	char str[127];
	//if (attArmy->GetPlanet()!=0)
	//	return er_none;
	if (Q == eq_BeforeBattleAction){
		if ((defArmy!=0)&&(!defArmy->isDefeated())&&(!attArmy->isDefeated())&&(attArmy->StackSize(DR)>0)){
			_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
			if (SelectDialogYesNo("Use Assault Cannon vanguard ability?")){
				sprintf(str,"Player %s uses Assualt Cannon",attArmy->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(str);
				CombatInterface().RollingDices(attArmy,defArmy,bt_AssaultCannon,false);
				active = false;
				return er_normal;
			}
		}
	}
	return er_none;
}
GameEffect* e_AssaultCannon::Clone(){
	return new e_AssaultCannon(*this);
}
string e_AssaultCannon::Save(){
	return string();
}
void e_AssaultCannon::Load(std::string str){}
//Gravity Negator
e_GravityNegator::e_GravityNegator(){
	id = "GravitonNegator";
	image = EMPTY_EVENT_IMG;
	name = "Graviton Negator";
	description = "Dreadnoughts may bombard despite PDS, Fighters may join an Invasion Combat but return to space after combat"; 
	cost = 0;
	color = Red;
	race = MAX_RACE;
	TT = ttGravityNegator;
	prereq1 = ttAssaultCannon;
	prereq2 = ttDacxiveAnimators;
	isboth = false;
	active = false;
}
bool e_GravityNegator::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattle)||((queue==eq_BeforeBattleAction) && active)||(queue==eq_BeforeBombardment)||(queue==eq_BeforeBattleRound)||(queue==eq_AfterBattle))
		return true;
	return false;
}
GameEffectRets e_GravityNegator::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* fleet;
	GameEffectQs Q = EP.queue;
	Army* target = EP.army2;
	int round = EP.fround;
	int attacker = EP.attacker;
	Unit* unit = 0;
	int power=0;
	int shots=0;
	bool selecting = true;
	//бревноуты бомбят через PDS
	if ((Q == eq_BeforeBombardment)&&(attacker==1)){
		for (int i=1; i<=army->IsUnitWithAbility(uaDreadnought);i++)
			army->GetUnitWithAbility(uaDreadnought,i)->ModAbility(uaBombard,FIELD_SKIP,1);
	}
	//участие истребов в наземке
	if (Q == eq_BeforeBattle)
		if (army->GetPlanet()!=0)
			active = true;
		else
			active = false;
	if ((Q==eq_BeforeBattleAction)&&(!army->isDefeated())&&(!target->isDefeated())){
		fleet = FindAllyArmy(army->GetOwner(),army->GetHex(),0);
		if (fleet!=0){
			if (SelectDialogYesNo("Use fighters in invasion combat?")){
				while (selecting){
					unit = SelectDialogOneUnit("Select fighters to participate in invasion combat",fleet,true,uaFighter);
					if (unit!=0){
						power=unit->GetAbility(uaSpaceBattle).field1;
						shots=unit->GetAbility(uaSpaceBattle).field2;
						unit->AddAbility(uaLandBattle,power,shots);
						MoveUnit(fleet,army,unit);
					}
					else
						selecting=false;
				}
			}
		}
	}
	if ((Q == eq_BeforeBattleRound)&&(army->GetPlanet()!=0)&&(army->IsUnitWithAbility(uaFighter))){
		for (int i=1; i<=army->IsUnitWithAbility(uaFighter);i++){
			power=unit->GetAbility(uaSpaceBattle).field1;
			shots=unit->GetAbility(uaSpaceBattle).field2;
			unit->AssignAbility(uaLandBattle,power,shots);
		}
	}
	if ((Q == eq_AfterBattle)&&(army->GetPlanet()!=0)&&(army->IsUnitWithAbility(uaFighter))){
		fleet = FindAllyArmy(army->GetOwner(),army->GetHex(),0);
		while (army->IsUnitWithAbility(uaFighter)){
			unit = army->GetUnitWithAbility(uaFighter,1);
			unit->DeleteAbility(uaLandBattle);
			MoveUnit(army,fleet,unit);
		}
	}
	return er_none;
}
GameEffect* e_GravityNegator::Clone(){
	return new e_GravityNegator(*this);
}
string e_GravityNegator::Save(){
	return string();
}
void e_GravityNegator::Load(std::string str){}