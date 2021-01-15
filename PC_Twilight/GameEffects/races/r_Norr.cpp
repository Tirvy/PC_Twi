e_NorrRacialAbilityStats::e_NorrRacialAbilityStats(){
	id = "NorrRacialAbilityStats";
}
bool e_NorrRacialAbilityStats::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_NorrRacialAbilityStats::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	army->ModUnitAbility(uaSpaceBattle,-1);
	army->ModUnitAbility(uaLandBattle,-1);
	army->ModUnitAbility(uaAFB,-1);
	army->ModUnitAbility(uaCannon,-1);
	return er_none;
}
GameEffect* e_NorrRacialAbilityStats::Clone(){
	return new e_NorrRacialAbilityStats(*this);
}
string e_NorrRacialAbilityStats::Save(){
	return string();
}
void e_NorrRacialAbilityStats::Load(std::string str){}
///////////////////////////////////////
e_NorrValkyrieArmor::e_NorrValkyrieArmor(){
	id = "ValkyrieArmor";
	name = "Valkyrie Armor";
	description = "At the end of a round of Invasion Combat, roll one die for each casualty you take. For each 10 you roll, your opponent must immediately take one casualty";
	cost = 3;
	color = RaceTech;
	race = Norr;
	TT = ttValkyrieArmor;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	HP = 0;
}
bool e_NorrValkyrieArmor::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattleRound)||(queue==eq_AfterBattleRound))
		return true;
	return false;
}
GameEffectRets e_NorrValkyrieArmor::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* target = EP.army2;
	GameEffectQs Q = EP.queue;
	int dmg=0;
	char str[127];
	if (army->GetPlanet()!=0){
		if (Q == eq_BeforeBattleRound){
			//unit=army->GetUnits();
			HP=0;
			for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++){
				if ((*iter)->HasAbility(uaInfantry))
					HP += 1;
				if ((*iter)->Class==MU)
					if ((*iter)->HasAbility(uaSustain,0))
						HP = HP + (*iter)->GetAbility(uaSustain).field2 + 1;
					else
						HP += 1;
			}
		}
		if (Q == eq_AfterBattleRound){
			//unit=army->GetUnits();
			for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++){
				if ((*iter)->HasAbility(uaInfantry))
					HP -= 1;
				if ((*iter)->Class == MU)
					if ((*iter)->HasAbility(uaSustain,0))
						HP = HP - (*iter)->GetAbility(uaSustain).field2 - 1;
					else
						HP -= 1;
			}
			for (int i=0; i<HP; i++)
				if (rand()%DICE + 1 == DICE)
					dmg++;
			if (dmg > 0){
				sprintf(str,"Player %s do additional damage by Valkyrie Armor",army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(str);
				CombatInterface().SelectCasualties(target,army,dmg,bt_Invasion);
			}
		}
	}
	return er_none;
}
GameEffect* e_NorrValkyrieArmor::Clone(){
	return new e_NorrValkyrieArmor(*this);
}
string e_NorrValkyrieArmor::Save(){
	return string();
}
void e_NorrValkyrieArmor::Load(std::string str){}
/////////////////////////////////////////////
e_NorrFlagship::e_NorrFlagship(){
	id = "NorrFlagship";
}
bool e_NorrFlagship::GetQ(GameEffectQs queue){
	if (queue == eq_Battle)
		return true;
	return false;
}
GameEffectRets e_NorrFlagship::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	int round = EP.fround;
	if ((army->StackSize(FM)) && round)
		army->ModUnitAbility(uaSpaceBattle,-1);
	return er_none;
}
GameEffect* e_NorrFlagship::Clone(){
	return new e_NorrFlagship(*this);
}
string e_NorrFlagship::Save(){
	return string();
}
void e_NorrFlagship::Load(std::string str){}
/////////////////////////////////////////////////////
e_NorrExotrireme::e_NorrExotrireme(){
	id = "Exotrireme";
	name = "Exotrireme";
	description = "At the end of a round of Space Battle, you may destroy one of your Dreadnoughts present to destroy two present enemy ships of your choice";
	cost = 5;
	color = RaceTech;
	race = Norr;
	TT = ttExotrireme;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	active = true;
}
bool e_NorrExotrireme::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattleRoundAction && active)||(queue == eq_BeforeBattleRound))
		return true;
	return false;
}
GameEffectRets e_NorrExotrireme::Execute(ExecuteParams EP){
	char str[127];
	GameEffectQs Q = EP.queue;
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	int round = EP.fround;
	Unit* unit;
	int targets=2;
	/*if (attArmy->GetPlanet()!=0)
		return er_none;
	if (round!=2)
		return er_none;*/
	if (Q == eq_BeforeBattleRound)
		if ((round == 2) && (attArmy->GetPlanet() == 0))
			active = true;
		else
			active = false;
	if (Q == eq_BeforeBattleRoundAction){
	//if ((attArmy!=0)&&(defArmy!=0)&&(!defArmy->isDefeated())){
		if (attArmy->StackSize(DR)>0){
			_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
			if (defArmy->IsUnitWithAbility(uaCapitalShip)){
				if (SelectDialogYesNo("Sacrifice Dreadnought to destroy two enemy ships?")){
					unit=SelectDialogOneUnit("Select unit for kamikaze mission",attArmy,true,uaDreadnought);
					if (unit!=0){
						sprintf(str,"Player %s uses Exotrireme, braves yourself",attArmy->GetOwner()->GetName().c_str());
						_Interface.PrintThingAll(str);
						CombatInterface().DestroyUnit(attArmy,unit);
						//targets = min(2,defArmy->IsUnitWithAbility(uaCapitalShip));
						while ((targets>0)&&(defArmy->IsUnitWithAbility(uaCapitalShip))){
							unit=SelectDialogOneUnit("Select target",defArmy,true,uaCapitalShip);
							if (unit!=0){
								sprintf(str,"Player's %s Exotrireme destroyes %s",attArmy->GetOwner()->GetName().c_str(),ShipsShort[unit->Class].c_str());
								_Interface.PrintThingAll(str);
								unit->DeleteAbility(uaCapitalShip);
								CombatInterface().DestroyUnit(defArmy,unit);
								active = false;
							}
							else
								break;
							targets--;
						}
					}
				}
			}
			else
				_Interface.PrintThingPlayer(attArmy->GetOwner()->GetNumber()-1,"There is no target to use this ability");
		}
		else
			_Interface.PrintThingPlayer(attArmy->GetOwner()->GetNumber()-1,"You have no Dreadnoughts to use this ability");
	}
	return er_none;
}
GameEffect* e_NorrExotrireme::Clone(){
	return new e_NorrExotrireme(*this);
}
string e_NorrExotrireme::Save(){
	return string();
}
void e_NorrExotrireme::Load(std::string str){}
//////////////////////////////////////////////////////
class e_NorrStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttHylar);
		curPlayer->GiveTech(ttDeepSpaceCannon);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_DeepSpaceCannon);
		curPlayer->AddGameEffect(new e_NorrRacialAbilityStats);
		curPlayer->AddGameEffect(new e_NorrFlagship);
		//curPlayer->AddGameEffect(new e_NorrExotrireme);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 5;
		units->unit[CR] = 1;
		units->unit[CS] = 1;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_NorrStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};