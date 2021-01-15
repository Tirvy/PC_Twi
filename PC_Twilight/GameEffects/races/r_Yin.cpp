e_YinFanatic::e_YinFanatic(){
	id = "YinFanatic";
	name = "Fanaticism";
	description = "Use your racial ability twice each ground combat";
	cost = 4;
	color = RaceTech;
	race = Yin;
	TT = ttFanaticism;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_YinFanatic::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_YinFanatic::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_YinFanatic::Clone(){
	return new e_YinFanatic(*this);
}
string e_YinFanatic::Save(){
	return string();
}
void e_YinFanatic::Load(std::string str){}
///////////////////////////////////////////////////////
e_YinSpinner::e_YinSpinner(){
	id = "YinSpinner";
	name = "Yin Spinner";
	description = "Build one free GF each time you build units at your Space Dock. The free GF does not count toward production limit";
	cost = 2;
	color = RaceTech;
	race = Yin;
	TT = ttYinSpinner;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_YinSpinner::GetQ(GameEffectQs queue){
	if (queue == eq_AfterBuild)
		return true;
	return false;
}
GameEffectRets e_YinSpinner::Execute(ExecuteParams EP){
	Player* player = EP.player;
	Hex* hex = EP.hex;
	Army* army;
	for (int i = 1; i <= MAX_PLANETS; i++){
		if ((hex->GetPlanet(i) != 0) && (hex->GetPlanet(i)->GetOwner() == player)){
			army = FindArmy(hex,player,true,hex->GetPlanet(i));
			if (army->StackSize(DCK)){
				_Interface.PrintThingAll("Yin Spinners spawn 1 additional free GF");
				army->AddUnit(GF);
			}
		}
	}
	return er_none;
}

GameEffect* e_YinSpinner::Clone(){
	return new e_YinSpinner(*this);
}
string e_YinSpinner::Save(){
	return string();
}
void e_YinSpinner::Load(std::string str){}
//////////////////////////////////////////////////////
e_YinFanaticism::e_YinFanaticism(){
	id = "YinFanaticism";
}
bool e_YinFanaticism::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeBattle)
		return true;
	return false;
}
GameEffectRets e_YinFanaticism::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	int round = EP.fround;
	int attacker = EP.attacker;
	int roll=0;
	int tries=1;//кол-во попыток перевербовки
	char str[127];
	if (attacker!=1)
		return er_none;
	if (round!=1)
		return er_none;
	if (attArmy->GetPlanet()==0)
		return er_none;
	if (attArmy->GetOwner()->GotTech(ttFanaticism))
		tries=2;
	if ((defArmy!=0)&&(defArmy->StackSize(GF)>0)){
		if (SelectDialogYesNo("Try to recruit enemy GF?")){
			while ((tries>0)&&(defArmy->StackSize(GF))){
				roll=rand()%DICE+1;
				if (roll>=5){
					MoveUnit(defArmy,attArmy,defArmy->GetUnit(GF));
					sprintf(str,"Player %s successful recruit Player %s GF",attArmy->GetOwner()->GetName().c_str(),defArmy->GetOwner()->GetName().c_str());
					_Interface.PrintThingAll(str);
				};
				tries--;
			}
		}
	}
	return er_none;
}
GameEffect* e_YinFanaticism::Clone(){
	return new e_YinFanaticism(*this);
}
string e_YinFanaticism::Save(){
	return string();
}
void e_YinFanaticism::Load(std::string str){}
//////////////////////////////////////////////////////
e_YinKamikaze::e_YinKamikaze(){
	id = "YinKamikaze";
	image = EMPTY_EVENT_IMG;
	active = false;
}
bool e_YinKamikaze::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattleRound)||((queue==eq_BeforeBattleRoundAction) && active))
		return true;
	return false;
}
GameEffectRets e_YinKamikaze::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	int round = EP.fround;
	Unit* unit;
	Unit* target;
	char str[127];
	int d=0;
	/*if (attArmy->GetPlanet()!=0)
		return er_none;
	if (round!=2)
		return er_none;
	if (defArmy==0)
		return er_none;*/
	if ((Q == eq_BeforeBattleRound) && (attArmy->GetPlanet() == 0))
		if (round == 2)
			active = true;
		else
			active = false;
	if (Q == eq_BeforeBattleRoundAction){
	//if ((attArmy!=0)&&(defArmy!=0)&&(!defArmy->isDefeated())){
		if (attArmy->IsUnitWithAbility(uaLightShip)){
			if (defArmy->IsUnitWithAbility(uaCapitalShip)){
				_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
				if (SelectDialogYesNo("Sacrifice destroyer or cruiser to inflict one damage?")){
					unit=SelectDialogOneUnit("Select unit for kamikaze mission",attArmy,true,uaLightShip);
					if (unit!=0){
						//sprintf(str,"Player %s uses kamikaze %s",attArmy->GetOwner()->GetName().c_str(),ShipsShort[unit->Class].c_str());
						//_Interface.PrintThingAll(str);
						//CombatInterface().DestroyUnit(attArmy,unit);
						target=SelectDialogOneUnit("Select target for kamikaze",defArmy,true,uaCapitalShip);
						if (target!=0){
							sprintf(str,"Player %s uses kamikaze %s and inflicts 1 damage to enemy %s",attArmy->GetOwner()->GetName().c_str(),ShipsShort[unit->Class].c_str(), ShipsShort[target->Class].c_str());
							_Interface.PrintThingAll(str);
							CombatInterface().DestroyUnit(attArmy,unit);
							if (target != 0)
								CombatInterface().DamageUnit(defArmy,target);
							active = false;
						}
					}
				}
			}
			else
				_Interface.PrintThingPlayer(attArmy->GetOwner()->GetNumber()-1,"No targets to use this ability");
		}
		else
			_Interface.PrintThingPlayer(attArmy->GetOwner()->GetNumber()-1,"You have no Destroyers or Cruisers to use this ability");
	}
	return er_none;
}
GameEffect* e_YinKamikaze::Clone(){
	return new e_YinKamikaze(*this);
}
string e_YinKamikaze::Save(){
	return string();
}
void e_YinKamikaze::Load(std::string str){}
/////////////////////////////////////////////////////
e_YinReverse::e_YinReverse(){
	id = "YinReverse";
	target = 0;
	launched = false;
}
bool e_YinReverse::GetQ(GameEffectQs queue){
	if ((queue == eq_AAA)||(queue == eq_StatusPhase))//||(queue == eq_LaunchEffect)
		return true;
	return false;
}
GameEffectRets e_YinReverse::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char str[127];
	int res,inf;
	if (Q == eq_AAA){
		if (target != 0){
			sprintf(str,"This ability was already used on %s",target->GetName().c_str());
			_Interface.PrintThingAll(str);
			return er_none;
		}
		else{
			_GrIn.InitChoise("Select planet to reverse res/inf",true,false);
			for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
				sprintf(str,"%s (%d/%d)",(*piter)->GetName().c_str(),(*piter)->GetRes(),(*piter)->GetInf());
				_GrIn.AddOption(PLANET_IMG,str);
			}
			vector<int> tempvec = _GrIn.LaunchChoise();
			if (tempvec.size() == 0)
				return er_none;
			else{
				for (int i = 0; i < tempvec.size(); i++){
					if (tempvec.at(i)){
						target = player->GetPlanetsList()->at(i);
						break;
					}
				}
				if (target){
					sprintf(str,"Using reverse ability on planet %s",target->GetName().c_str());
					_Interface.PrintThingAll(str);
					res = target->GetRes();
					inf = target->GetInf();
					target->SetRes(inf);
					target->SetInf(res);
				}
				else{
					_Interface.PrintThingAll("SUM TING WONG: Yin reverse");
					return er_none;
				}
			}
		}
	}
	if ((Q == eq_StatusPhase) && (target)){
		res = target->GetRes();
		inf = target->GetInf();
		target->SetRes(inf);
		target->SetInf(res);
		target = 0;
	}
	return er_normal;
}
GameEffect* e_YinReverse::Clone(){
	return new e_YinReverse(*this);
}
string e_YinReverse::Save(){
	int x, y, p;
	std::stringstream ss;
	if (target == 0)
		return "0 0 0 0";
	else{
		target->GetSystem()->GetCoords(&x,&y);
		for (int i = 1; i <= MAX_PLANETS; i++){
			if (target->GetSystem()->GetPlanet(i) == target){
				p = i;
				break;
			}
		}
		ss<<"1 "<<x<<" "<<y<<" "<<p;
		return ss.str();
	}
	//return string();
}
void e_YinReverse::Load(std::string str){
	std::istringstream iss(str);
	int d, x, y, p;
	string q;
	iss>>q>>d>>x>>y>>p;
	if (d)
		target = _Map.GetHexh(x,y)->GetPlanet(p);
	else
		target = 0;
}
//////////////////////////////////////////////////////
e_YinFlagship::e_YinFlagship(){
	id = "YinFlagship";
	IsVanHaugeEnabled = false;
	active = false;
}
int e_YinFlagship::VanHaugeEnable(Army* army){
	IsVanHaugeEnabled=false;
	int x,y;
	Unit* unit;
	int planetNUMB=0;
	int t=1;
	int infType=0;
	int planet=0;
	int moved = 0;
	bool selecting = true;
	if (army->StackSize(FM)>0){
		_Interface.SetCurrPlayer(army->GetOwner()->GetId()-1);
		if (SelectDialogYesNo("Use GF as fighters in this space battle?")){
			army->GetHex()->GetCoords(&x,&y);
			while (selecting){
				PowDEV<Unit,Army> selection=SelectDialogOneUnit("Select GF to use in space battle",x,y,uaInfantry,true);
				if ((selection.elem1!=0)&&(selection.elem2!=0)){
					IsVanHaugeEnabled = true;
					moved++;
					unit=selection.elem1;
					if (selection.elem1->Class==GF)
						infType=1;
					if (selection.elem1->Class==ST)
						infType=2;
					planet=0;
					for (int i=1; i<=MAX_PLANETS; i++)
						if ((army->GetHex()->GetPlanet(i)!=0)&&(army->GetHex()->GetPlanet(i)==selection.elem2->GetPlanet()))
							planet=i;
					unit->DeleteAbility(uaInfantry);
					unit->AddAbility(uaYinFighter,infType,planet);
					unit->AddAbility(uaFighter);
					unit->AddAbility(uaSpaceBattle,9,1);
					unit->AssignAbility(uaNeedSupport,1);
					if (selection.elem2!=army)
						MoveUnit(selection.elem2,army,unit);
					else
						unit->carrier=0;
					selection.elem1=0;
					selection.elem2=0;
				}
				else
					selecting=false;
			}
		}
	}
	else
		_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no your Flagship");
	return moved;
};
int e_YinFlagship::VanHaugeDisable(Army* army){
	IsVanHaugeEnabled=false;
	Unit* unit;
	Army* home;
	int infType=0;
	int planet=0;
	while (army->IsUnitWithAbility(uaYinFighter)){//пока есть кого возвращать
		unit=army->GetUnitWithAbility(uaYinFighter,1);
		infType=unit->GetAbility(uaYinFighter).field1;
		planet=unit->GetAbility(uaYinFighter).field2;
		unit->DeleteAbility(uaFighter);
		unit->DeleteAbility(uaSpaceBattle);
		unit->DeleteAbility(uaYinFighter);
		unit->AssignAbility(uaNeedSupport,0);
		unit->AddAbility(uaInfantry);
		if (planet){
			home=FindAllyArmy(army->GetOwner(),army->GetHex(),army->GetHex()->GetPlanet(planet));
			if (home!=0)
				MoveUnit(army,home,unit);
			else
				_Interface.PrintThingAll("Sum Ting Wong, can't land infantry");
		}
	}
	return 1;
};
bool e_YinFlagship::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattle) || ((queue == eq_BeforeBattleAction) && active))
		return true;
	if (queue==eq_AfterBattle)
		return true;
	if (queue==eq_AfterAssignDamage)
		return true;
	return false;
}
GameEffectRets e_YinFlagship::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	GameEffectQs Q = EP.queue;
	if (Q == eq_BeforeBattle)
		active = (attArmy->GetPlanet() == 0);
	if ((Q == eq_BeforeBattleAction) && VanHaugeEnable(attArmy))
		return er_normal;
	if ((Q == eq_AfterAssignDamage)&&IsVanHaugeEnabled&&(attArmy->StackSize(FM)==0))
		VanHaugeDisable(attArmy);
	if ((Q == eq_AfterBattle)&&IsVanHaugeEnabled)
		VanHaugeDisable(attArmy);
	return er_none;
}
GameEffect* e_YinFlagship::Clone(){
	return new e_YinFlagship(*this);
}
string e_YinFlagship::Save(){
	return string();
}
void e_YinFlagship::Load(std::string str){}
////////////////////////////////////////////////////////////////
class e_YinStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttHylar);
		curPlayer->GiveTech(ttADT);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_ADT);
		curPlayer->AddGameEffect(new e_YinKamikaze);
		curPlayer->AddGameEffect(new e_YinFanaticism);
		curPlayer->AddGameEffect(new e_YinFlagship);
		curPlayer->AddGameEffect(new e_YinReverse);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[FG] = 4;
		units->unit[CR] = 2;
		units->unit[DS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_YinStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};