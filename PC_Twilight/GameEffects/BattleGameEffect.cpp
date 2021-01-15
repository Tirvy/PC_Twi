//содержит общие боевые эффекты

//эффекты для добавления всем игрокам
//e_ShockTroopersUpgrade
//e_ShockTroopersCapture
//e_DestroyersMarkI
//e_DestroyersMarkII
//e_Bombardment
//e_PDS
/////////////////////
class e_ShockTroopersUpgrade:public GameEffect{
	int GFupg;
public:
	e_ShockTroopersUpgrade(){
		id = "ShockTroopersUpgrade";
		GFupg = 0;
	}
	bool GetQ(GameEffectQs queue){
		if ((queue==eq_BeforeBattleRound)||(queue==eq_AfterRoll)||(queue==eq_AfterBattleRound))
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		GameEffectQs Q = EP.queue;
		Unit* un = EP.unit;
		int* r = EP.roll;
		if (Q == eq_BeforeBattleRound)
			GFupg=0;
		if (Q == eq_AfterRoll){
			if ((un->Class == GF)&&(*r == 10)&&(army->GetPlanet()!=0))
				GFupg++;
		}
		if (Q == eq_AfterBattleRound){
			while ((GFupg>0)&&(army->StackSize(GF)>0)){
				un = army->GetUnit(GF);
				un->Class = ST;
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"Your Ground Force has promoted to Shock Trooper");
				GFupg--;
			}
			GFupg=0;
		}
		return er_none;
	}
	GameEffect* e_ShockTroopersUpgrade::Clone(){
		return new e_ShockTroopersUpgrade(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_ShockTroopersCapture:public GameEffect{
public:
	e_ShockTroopersCapture(){
		id = "ShockTroopersCapture";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AfterBattle)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Army* target = EP.army2;
		Unit* unit;
		bool capturing = true;
		if ((army->StackSize(ST)>0)&&target->IsUnitWithAbility(uaStructure)){
			_Interface.SetCurrPlayer(army->GetOwner()->GetId()-1);
			_Interface.PrintThingAll("You can capture enemy space dock or PDS by shock troopers");
			while (capturing){
				unit = SelectDialogOneUnit("Select unit to capture",target,true,uaStructure);
				if (unit!=0){
					MoveUnit(target,army,unit);
					_Interface.PrintThingAll("Unit was captured");
				}
				else
					capturing = false;
			};
		};
		return er_none;
	}
	GameEffect* e_ShockTroopersCapture::Clone(){
		return new e_ShockTroopersCapture(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_DestroyersMarkI:public GameEffect{
	bool active;
public:
	e_DestroyersMarkI(){
		id = "DestroyersMarkI";
		image = SHIPS_IMG[DS];
		active = false;
	}
	bool GetQ(GameEffectQs queue){
		if ((queue==eq_BeforeBattle) || ((queue == eq_BeforeBattleAction) && active))
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Army* target = EP.army2;
		GameEffectQs Q = EP.queue;
		char str[127];
		if (Q == eq_BeforeBattle)
			active = (army->GetPlanet() == 0);
		if (Q == eq_BeforeBattleAction){
			if ((army->IsUnitWithAbility(uaAFB)) && (target->StackSize(FG)>0)){
				sprintf(str,"Player's %d{%s} anti-fighter barrage",army->GetOwner()->GetId(),army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(str);
				for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++)
					if ((*iter)->HasAbility(uaAFB))
						(*iter)->AssignAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,1);
				CombatInterface().RollingDices(army,target,bt_AFB,false);
				for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++)
					if ((*iter)->HasAbility(uaAFB))
						(*iter)->AssignAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,0);
				active = false;
				return er_normal;
			}
			else
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"No Destroyers or no enemy fighters to use AFB");
		}
		return er_none;
	}
	GameEffect* e_DestroyersMarkI::Clone(){
		return new e_DestroyersMarkI(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_DestroyersMarkII:public GameEffect{
	/*bool isAFB(Army* army){
		if (army->IsUnitWithAbility(uaAFB))
			return true;
		return false;
	};*/
	bool active;
public:
	e_DestroyersMarkII(){
		id = "DestroyersMarkII";
		image = SHIPS_IMG[DS];
		active = false;
	}
	bool GetQ(GameEffectQs queue){
		if ((queue==eq_BeforeBattleRound)||((queue==eq_BeforeBattleRoundAction) && active)||(queue==eq_AfterBattleRound))
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Army* target = EP.army2;
		GameEffectQs Q = EP.queue;
		int* r;
		int N, M;
		char str[127];
		bool selecting = true;
		//if ((Q == eq_BeforeBattleRound)&&(army->IsUnitWithAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,0))&&(target->IsUnitWithAbility(uaFighter)))
		if ((Q == eq_BeforeBattleRound) && (army->GetPlanet() == 0))
			active = true;
		if ((Q == eq_BeforeBattleRoundAction) && active){
			_Interface.SetCurrPlayer(army->GetOwner()->GetId()-1);
			N = army->IsUnitWithAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,0);
			M = target->IsUnitWithAbility(uaFighter);
			if (N == 0){
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"You have no units to fire Anti-fighter Barrage");
				return er_none;
			}
			if (M == 0){
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"There is no enemy fighters to use Anti-fighter Barrage");
				return er_none;
			}
			if (!active){
				_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"You already has used Anti-fighter Barrage in this round");
				return er_none;
			}
			if (SelectDialogYesNo("Use anti-fighter barrage?")){
				vector<int> tempvec = SelectDialogGroupUnits("Select unit to use AFB",army,true,uaAFB,FIELD_SKIP,FIELD_SKIP,0);
				if (tempvec.size()!=0){
					r = &tempvec[0];
					for (int i=N-1; i>=0; i--)
						if (r[i]==1)
							army->GetUnitWithAbility(uaAFB,i+1,FIELD_SKIP,FIELD_SKIP,0)->AssignAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,1);
					sprintf(str,"Player %s uses anti-fighter barrage",army->GetOwner()->GetName().c_str());
					_Interface.PrintThingAll(str);
					CombatInterface().RollingDices(army,target,bt_AFB,false);
					active = false;
				}
			}
		}
		if (Q == eq_AfterBattleRound){
			army->AssignUnitAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,0);
			active = false;
		}
		return er_none;
	}
	GameEffect* e_DestroyersMarkII::Clone(){
		return new e_DestroyersMarkII(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_Bombardment:public GameEffect{
public:
	e_Bombardment(){
		id = "Bombardment";
	}
	bool GetQ(GameEffectQs queue){
		if ((queue==eq_Bombardment)||(queue==eq_AfterBombardment))
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Army* army = EP.army1;
		Army* target = EP.army2;
		bool isInvasion = EP.isInvasion;
		int N;
		int* r;
		int invasion;
		int shields;
		char str[127];
		if (Q == eq_Bombardment){
			if (target==0)//если никого нет, то и бомбить нечего
				return er_none;
			if (target->isDefeated())//если никого нет, то и бомбить нечего
				return er_none;
			army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BeforeBombardment,army,target,0,1));
			target->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BeforeBombardment,army,target,0,0));
			if (isInvasion)//проверка на вторжение
				invasion = FIELD_SKIP;
			else
				invasion = 1;
			if (target->IsUnitWithAbility(uaPlanetaryShield))//проверка на щиты PDS
				shields=1;
			else
				shields=FIELD_SKIP;
			if (N=army->IsUnitWithAbility(uaBombard,0,shields,invasion)){
				_Interface.SetCurrPlayer(army->GetOwner()->GetId()-1);
				sprintf(str,"Bombard planet %s?",target->GetPlanet()->GetName().c_str());
				if (SelectDialogYesNo(str)){
					vector<int> tempvec = SelectDialogGroupUnits("Select unit for bombardment",army,true,uaBombard,0,shields,invasion);
					if (tempvec.size() != 0){
						r = &tempvec[0];
						for (int i=N-1; i>=0; i--)
							if (r[i]==1)
								army->GetUnitWithAbility(uaBombard,i+1,0,shields,invasion)->AssignAbility(uaBombard,1);
						sprintf(str,"Bombardment planet %s",target->GetPlanet()->GetName().c_str());
						_Interface.PrintThingAll(str);
						CombatInterface().RollingDices(army,target,bt_Bombardment,false);
						while (army->IsUnitWithAbility(uaBombard,1))
							army->GetUnitWithAbility(uaBombard,1,1)->AssignAbility(uaBombard,2);
					};
				}
				else
					_Interface.PrintThingAll("Bombardment was cancelled");
			};
		};
		if (Q == eq_AfterBombardment)//сброс выбора бомбардировщиков
			for (int i=1; i<=army->IsUnitWithAbility(uaBombard,2);i++)
				army->GetUnitWithAbility(uaBombard,i,2)->AssignAbility(uaBombard,0);
		return er_none;
	}
	GameEffect* Clone(){
		return new e_Bombardment(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_PDS:public GameEffect{
public:
	e_PDS(){
		id = "PDS";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_PDSmain)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* active = EP.army1;
		Hex* tHex = active->GetHex();
		Player* tOwner = active->GetOwner();
		for (int i=0; i<_GameStats.GetPlayersNumber(); i++)
			_Players[i]->ExecuteGameEffect(ExecuteParams(eq_PDSfire,_Players[i],active));
		return er_none;
	}
	GameEffect* e_PDS::Clone(){
		return new e_PDS(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_PDScommon:public GameEffect{
public:
	e_PDScommon(){
		id = "PDScommon";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_PDSfire)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* active = EP.army1;
		Player* curPlayer = EP.player;
		Hex* hex = active->GetHex();
		int distance=0;
		Player* tOwner = active->GetOwner();
		Army* target;
		Army* defArmy;
		bool isCannons=false;
		int x,y;
		char str[127];
		if (active->GetPlanet()==0){//цель в космосе
			if (active->GetOwner()==curPlayer)
				target=FindOpponentArmy(active);
			else
				target=active;
			if (target==0)
				return er_none;
			if (target->isDefeated())
				return er_none;
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
				if (((*aiter)->GetOwner()!=target->GetOwner())&&((*aiter)->GetOwner()==curPlayer)){
					RefreshArmyAbilities(*aiter,1);
					(*aiter)->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,*aiter,target,0,1));
					target->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,target,*aiter,0,0));
					distance=isAdjacent((*aiter)->GetHex(),hex);
					if ((distance<=1)&&((*aiter)->GetOwner()==curPlayer)){
						isCannons=false;
						if (distance==1){
							if ((*aiter)->GetPlanet()!=0)
								isCannons=(*aiter)->IsUnitWithAbility(uaDeepSpaceCannon,1);
							else
								isCannons=(*aiter)->IsUnitWithAbility(uaDeepSpaceCannon,0);
						}
						if (distance==0)
							if ((*aiter)->GetPlanet()!=0)
								isCannons=(*aiter)->IsUnitWithAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,1);
							else
								isCannons=(*aiter)->IsUnitWithAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,0);
						if (isCannons){
							_Interface.SetCurrPlayer((*aiter)->GetOwner()->GetId()-1);
							if ((*aiter)->GetPlanet()!=0)
								sprintf(str,"PDS fire from planet %s?",(*aiter)->GetPlanet()->GetName().c_str());
							else{
								(*aiter)->GetHex()->GetCoords(&x,&y);
								sprintf(str,"PDS fire from fleet in hex {%d,%d}?",x,y);
							}
							if (SelectDialogYesNo(str)){
								if (distance==0)
									CombatInterface().RollingDices(*aiter,target,bt_PDS,false);
								else
									CombatInterface().RollingDices(*aiter,target,bt_DSC,false);
							}
							else
								_Interface.PrintThingAll("PDS fire was cancelled");
						}
					}
				}
			}
		}
		else{//при высадке
			defArmy=FindOpponentArmy(active);
			if (defArmy!=0)
				if (defArmy->IsUnitWithAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,1)){
					defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_PDSmod,defArmy->GetOwner(),defArmy));
					_Interface.SetCurrPlayer(defArmy->GetOwner()->GetId()-1);
					sprintf(str,"PDS fire from planet %s against landing party?",defArmy->GetPlanet()->GetName().c_str());
					if (SelectDialogYesNo(str))
						CombatInterface().RollingDices(defArmy,active,bt_PDS,false);
					else
						_Interface.PrintThingAll("PDS fire was cancelled");
				}
		}
		return er_none;
	}
	GameEffect* e_PDScommon::Clone(){
		return new e_PDScommon(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_NebulaBonus:public GameEffect{
public:
	e_NebulaBonus(){
		id = "NebulaBonus";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_Battle)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Army* target = EP.army2;
		GameEffectQs Q = EP.queue;
		int attacker = EP.attacker;
		if (Q == eq_Battle){
			if ((attacker == 0)&&(army->GetHex()->GetDanger() == Nebula) && (army->GetPlanet() == 0)){
				army->ModUnitAbility(uaSpaceBattle,-1);
				army->ModUnitAbility(uaAFB,-1);
				army->ModUnitAbility(uaCannon,-1);
			}
		}
		return er_none;
	}
	GameEffect* e_NebulaBonus::Clone(){
		return new e_NebulaBonus(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_IonStormFighters:public GameEffect{
public:
	e_IonStormFighters(){
		id = "IonStormFighters";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_Battle)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Army* target = EP.army2;
		GameEffectQs Q = EP.queue;
		int attacker = EP.attacker;
		if (Q == eq_Battle)
			if ((army->GetHex()->GetDanger() == IonStorm) && (army->GetPlanet() == 0))
				for (int i = 1; i <=army->IsUnitWithAbility(uaFighter); i++)
					army->GetUnitWithAbility(uaFighter,i)->ModAbility(uaSpaceBattle,FIELD_SKIP,-1);
		return er_none;
	}
	GameEffect* e_IonStormFighters::Clone(){
		return new e_IonStormFighters(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_RetreatWithdraw:public GameEffect{
	bool isSpace;
public:
	e_RetreatWithdraw(){
		id = "RetreatWithdraw";
		image = EMPTY_EVENT_IMG;
		isSpace = true;
	}
	bool GetQ(GameEffectQs queue){
		if (((queue == eq_BeforeBattleRoundAction) && isSpace) || (queue == eq_Retreat) || (queue == eq_BeforeBattle))
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Army* target = EP.army2;
		GameEffectQs Q = EP.queue;
		int attacker = EP.attacker;
		char str[255];
		if (Q == eq_BeforeBattle){//4 строчки паранойи. А вдруг останется флаг отступления?!
			army->_retreating = false;
			target->_retreating = false;
			isSpace = (army->GetPlanet() == 0);
		}
		if (Q == eq_BeforeBattleRoundAction){
			if (!army->_retreating){
				if ((CombatInterface().CanRetreat(army)) && ((attacker == 1) || ((attacker == 0) && !target->_retreating))){
					if (attacker == 1){
						if (SelectDialogYesNo("Do you want to withdraw?")){
							sprintf(str,"Player %s announces a withdraw",army->GetOwner()->GetName().c_str());
							_Interface.PrintThingAll(str);
							army->_retreating = true;
						}
					}
					else{
						if (SelectDialogYesNo("Do you want to retreat?")){
							sprintf(str,"Player %s announces a retreat",army->GetOwner()->GetName().c_str());
							_Interface.PrintThingAll(str);
							army->_retreating = true;
						}
					}
				}
				else{
					if (attacker == 1)
						_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"You can't withdraw");
					else
						_Interface.PrintThingPlayer(army->GetOwner()->GetNumber()-1,"You can't retreat");
				}
			}
			else{
				if (attacker == 1){
					if (SelectDialogYesNo("Cancel withdraw?")){
						sprintf(str,"Player %s cancels a withdraw",army->GetOwner()->GetName().c_str());
						_Interface.PrintThingAll(str);
						army->_retreating = false;
					}
				}
				else{
					if (SelectDialogYesNo("Cancel retreat?")){
						sprintf(str,"Player %s cancels a retreat",army->GetOwner()->GetName().c_str());
						_Interface.PrintThingAll(str);
						army->_retreating = false;
					}
				}
			}
		}
		if ((Q == eq_Retreat) && army->_retreating && !army->isDefeated() && !target->isDefeated())
			CombatInterface().Retreat(army);
		return er_none;
	}
	GameEffect* Clone(){
		return new e_RetreatWithdraw(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};