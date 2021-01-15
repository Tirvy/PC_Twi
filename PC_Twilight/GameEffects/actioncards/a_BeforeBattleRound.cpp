//Morale Boost
class e_a_MoraleBoost:public e_ActionCard{
public:
	e_a_MoraleBoost(){
		_name = "Morale Boost";
		_description = "Before battle round. Receive +1 to all combat rolls in this round";
		_when = acBeforeBattleRound;
		id = "a_MoraleBoost";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_BeforeBattleRoundAction);
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		Army* army = EP.army1;
		char buff[255];
		if (SelectDialogYesNo("Use Morale Boost?")){
			if (army->GetPlanet() == 0)
				army->ModUnitAbility(uaSpaceBattle,-1);
			else
				army->ModUnitAbility(uaLandBattle,-1);
			return er_delete;
		}
		else
			return er_none;
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_MoraleBoost(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Recheck
class e_a_Recheck:public e_ActionCard{
public:
	e_a_Recheck(){
		_name = "Recheck";
		_description = "After rolling dices. Reroll 1 your dice";
		_when = acAAA;
		id = "a_Recheck";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_AfterRollingDicesAction);
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Roll* r = EP.rolls;
		Army* attArmy = EP.army1;
		int N = EP.rollNumber;
		Roll* selection=0;
		int oldthrow;
		int newthrow;
		char str[255];
		_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
		if (SelectDialogYesNo("Use Recheck?")){
			selection = SelectDialogRoll(attArmy->GetOwner(),r,N);
			if (selection!=0){
				oldthrow=selection->value;
				newthrow=rand()%DICE+1;
				selection->value=newthrow;
				selection->isRerolled=true;
				sprintf(str,"Player %s uses Recheck: %d -> %d",attArmy->GetOwner()->GetName().c_str(),oldthrow,newthrow);
				_Interface.PrintThingAll(str);
				return er_delete;
			}		
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_a_Recheck(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Overrun
class e_a_Overrun:public e_ActionCard{
	bool active;
public:
	e_a_Overrun(){
		_name = "Overrun";
		_description = "Before land battle in which your Mechanized Unit participates. Destroy 1 enemy Infantry";
		_when = acBeforeBattleRound;
		id = "a_Overrun";
		image = ACTION_CARD;
		active = false;
	}
	bool GetQ(GameEffectQs queue){
		return (((queue == eq_BeforeBattleAction) && active) || (queue == eq_BeforeBattle));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Army* army = EP.army1;
		Army* opponent = EP.army2;
		char buff[255];
		if ((Q == eq_BeforeBattle) && (army->GetPlanet() != 0))
			active = true;
		if (Q == eq_BeforeBattleAction){
			if (SelectDialogYesNo("Use Overrun?")){
				if (army->StackSize(MU) == 0){
					_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no your Mechanized Unit");
					return er_none;
				}
				if (!opponent->IsUnitWithAbility(uaInfantry)){
					_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no enemy Infantry Units");
					return er_none;
				}
				sprintf(buff,"Player %s uses Overrun and destroyes one Infantry unit of player %s",army->GetOwner()->GetName().c_str(),opponent->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(buff);
				if (opponent->StackSize(GF))
					CombatInterface().DestroyUnit(opponent,opponent->GetUnit(GF));
				else
					CombatInterface().DestroyUnit(opponent,opponent->GetUnit(ST));
				active = false;
				return er_delete;
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_Overrun(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Overrun
class e_a_GeomagneticMines:public e_ActionCard{
	bool active;
public:
	e_a_GeomagneticMines(){
		_name = "Geomagnetic Mines";
		_description = "Before land battle in which enemy Mechanized Unit participates. Destroy 1 enemy Mechanized Unit";
		_when = acAAA;
		id = "a_GeomagneticMines";
		image = ACTION_CARD;
		active = false;
	}
	bool GetQ(GameEffectQs queue){
		return (((queue == eq_BeforeBattleAction) && active) || (queue == eq_BeforeBattle));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Army* army = EP.army1;
		Army* opponent = EP.army2;
		char buff[255];
		if ((Q == eq_BeforeBattle) && (army->GetPlanet() != 0))
			active = true;
		if (Q == eq_BeforeBattleAction){
			if (SelectDialogYesNo("Use Geomagnetic Mines?")){
				if (opponent->StackSize(MU) == 0){
					_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no enemy Mechanized Unit");
					return er_none;
				}
				sprintf(buff,"Player %s uses Geomagnetic Mines and destroyes one Mechanized unit of player %s",army->GetOwner()->GetName().c_str(),opponent->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(buff);
				CombatInterface().DestroyUnit(opponent,opponent->GetUnit(MU));
				active = false;
				return er_delete;
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_GeomagneticMines(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Fighter prototype
class e_a_FighterPrototype:public e_ActionCard{
	bool active;
	bool selectable;
public:
	e_a_FighterPrototype(){
		_name = "Fighter Prototype";
		_description = "Before battle. Your fighters receive +2 to combat rolls in first round of Space Battle";
		_when = acAAA;
		id = "a_FighterPrototype";
		image = ACTION_CARD;
		active = false;
		selectable = false;
	}
	bool GetQ(GameEffectQs queue){
		if (((queue == eq_BeforeBattleAction) && selectable) || (queue == eq_BeforeBattle))
			return true;
		if ((queue == eq_Battle) && active)
			return true;
		if (queue == eq_AfterBattleRound)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Army* army = EP.army1;
		int round = EP.fround;
		char buff[255];
		if ((Q == eq_BeforeBattle) && (army->GetPlanet() == 0))
			selectable = true;
		if (Q == eq_BeforeBattleAction){
			if (SelectDialogYesNo("Use Fighter Prototype?")){
				active = true;
				sprintf(buff,"Player %s uses Fighter Prototype",army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(buff);
			}
			else
				return er_none;
		}
		if ((Q == eq_Battle) && (round == 1) && active){
			for (int i = 1; i <= army->IsUnitWithAbility(uaFighter); i++)
				army->GetUnitWithAbility(uaFighter,i)->ModAbility(uaSpaceBattle,-2);
		}
		if ((Q == eq_AfterBattleRound) && active)
			return er_delete;
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_FighterPrototype(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Into the Breach
class e_a_IntoTheBreach:public e_ActionCard{
	bool active;
	bool selectable;
	Unit* brevno;
public:
	e_a_IntoTheBreach(){
		_name = "Into the Breach";
		_description = "Before Space Battle. Select your Dreadnought, all your units receive +1 to all space combat rolls. All hits from enemy units have be applied to selected Dreadnought if able";
		_when = acAAA;
		id = "a_IntoTheBreach";
		image = ACTION_CARD;
		active = false;
		selectable = false;
		brevno = 0;
	}
	bool GetQ(GameEffectQs queue){
		if (((queue == eq_BeforeBattleAction) && selectable) || (queue == eq_BeforeBattle))
			return true;
		if ((queue == eq_Battle) && active)
			return true;
		if (queue == eq_AfterBattleRound)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Army* army = EP.army1;
		int round = EP.fround;
		Unit* unit = 0;
		char buff[255];
		if ((Q == eq_BeforeBattle) && (army->GetPlanet() == 0))
			selectable = true;
		if (Q == eq_BeforeBattleAction){
			if (army->StackSize(DR) == 0){
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no your Dreadnoughts");
				return er_none;
			}
			if (SelectDialogYesNo("Use Into the Breach?")){
				brevno = SelectDialogOneUnit("Select Dreadnought to use Into the Breach",army,true,uaDreadnought);
				if (brevno == 0)
					return er_none;
				sprintf(buff,"Player %s uses into the Breach",army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(buff);
				brevno->AddAbility(uaFirstTarget,0);
				active = true;
			}
			else
				return er_none;
		}
		if ((Q == eq_Battle) && active){
			for (int i = 1; i <= army->IsUnitWithAbility(uaSpaceBattle); i++)
				army->GetUnitWithAbility(uaSpaceBattle,i)->ModAbility(uaSpaceBattle,-1);
			for (int i = 1; i <= army->IsUnitWithAbility(uaAFB); i++)
				army->GetUnitWithAbility(uaAFB,i)->ModAbility(uaAFB,-1);
		}
		if ((Q == eq_AfterBattle) && active){
			if (brevno != 0)
				brevno->DeleteAbility(uaFirstTarget);
			return er_delete;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_IntoTheBreach(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//beacon of hope
class e_a_BeaconOfHope:public e_ActionCard{
	bool active;
	bool selectable;
public:
	e_a_BeaconOfHope(){
		_name = "A Beacon of Hope";
		_description = "Before Space Battle in which your Flagship participates. All your units inflict 1 additional damage on 10";
		_when = acAAA;
		id = "a_BeaconOfHope";
		image = ACTION_CARD;
		active = false;
		selectable = false;
	}
	bool GetQ(GameEffectQs queue){
		if (((queue == eq_BeforeBattleAction) && selectable) || (queue == eq_BeforeBattle))
			return true;
		if (queue == eq_AfterBattle)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Army* army = EP.army1;
		int round = EP.fround;
		Unit* unit = 0;
		int i;
		char buff[255];
		if ((Q == eq_BeforeBattle) && (army->GetPlanet() == 0))
			selectable = true;
		if (Q == eq_BeforeBattleAction){
			if (army->StackSize(FM) == 0){
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no your Flagship");
				return er_none;
			}
			if (SelectDialogYesNo("Use A Beacon of Hope?")){
				sprintf(buff,"Player %s uses a Beacon of Hope",army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(buff);
				active = true;
				for (i = 1; i <= army->IsUnitWithAbility(uaSpaceBattle); i++){
					unit = army->GetUnitWithAbility(uaSpaceBattle,i);
					if (unit->HasAbility(uaCritical))
						unit->ModAbility(uaCritical,+1);
					else
						unit->AddAbility(uaCritical,2);
				}
			}
			else
				return er_none;
		}
		if ((Q == eq_AfterBattle) && active){
			for (i = army->IsUnitWithAbility(uaCritical); i > 0; i--){
				unit = army->GetUnitWithAbility(uaCritical,i);
				if (unit->GetAbility(uaCritical).field1 <= 2)
					unit->DeleteAbility(uaCritical);
				else
					unit->ModAbility(uaCritical,-1);
			}
			return er_delete;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_BeaconOfHope(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};
