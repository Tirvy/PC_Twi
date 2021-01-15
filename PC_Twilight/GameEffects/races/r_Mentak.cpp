e_MentakPreBattle::e_MentakPreBattle(){
	id = "MentakPreBattle";
	image = EMPTY_EVENT_IMG;
	active = false;
}
bool e_MentakPreBattle::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattle) || ((queue == eq_BeforeBattleAction) && active))
		return true;
	return false;
}
GameEffectRets e_MentakPreBattle::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	Army* defArmy=EP.army2;
	GameEffectQs Q = EP.queue;
	int ships=2;
	char str[127];
	Unit* unit;
	if (Q == eq_BeforeBattle)
		if (attArmy->GetPlanet()==0)
			active = true;
		else
			active = false;
	if (Q == eq_BeforeBattleAction){
		if ((attArmy!=0)&&(defArmy!=0)&&(!attArmy->isDefeated())&&(!defArmy->isDefeated())){
			if (attArmy->IsUnitWithAbility(uaLightShip)>0){
				_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
				if (SelectDialogYesNo("Fire up to 2 cruisers or destroyers before battle?")){
					sprintf(str,"Player %s use Mentak ability",attArmy->GetOwner()->GetName().c_str());
					_Interface.PrintThingAll(str);
					while (ships>0){
						unit = SelectDialogOneUnit("Select units for vanguard fire",attArmy,true,uaLightShip,0);
						if (unit!=0){
							unit->AssignAbility(uaLightShip,1);
							unit->AddAbility(uaMentak);
						}
						else
							break;
						ships--;
					}
					CombatInterface().RollingDices(attArmy,defArmy,bt_Mentak,false);
					active = false;
					attArmy->DeleteUnitAbility(uaMentak);
					attArmy->AssignUnitAbility(uaLightShip,0);
					return er_normal;
				}
			}
			else
				_Interface.PrintThingPlayer(attArmy->GetOwner()->GetNumber()-1,"No Cruisers of Destroyers to use ths ability");
		}
	}
	return er_none;
}
GameEffect* e_MentakPreBattle::Clone(){
	return new e_MentakPreBattle(*this);
}
string e_MentakPreBattle::Save(){
	return string();
}
void e_MentakPreBattle::Load(std::string str){}
////////////////////////////////////////////////////////////
e_MentakStealGoods::e_MentakStealGoods(){
	id = "MentakStealGoods";
	active = false;
}
bool e_MentakStealGoods::GetQ(GameEffectQs queue){
	if (((queue==eq_StrategyAction) && active) || (queue == eq_StrategyEnd))
		return true;
	return false;
}
GameEffectRets e_MentakStealGoods::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	bool CanSteal = false;
	char buff[255];
	int i = 0, j = 0;
	int stealed = 0;
	if (Q == eq_StrategyEnd)
		active = true;
	if (Q == eq_StrategyAction){
		for (i = 0; i <_GameStats.GetPlayersNumber(); i++)
			if ((_Players[i] != player) && (_Players[i]->GetGoods() >= MINIMUM_TG_TO_STEAL))
				CanSteal = true;
		if (!CanSteal){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Nothing to steal");
			return er_none;
		}
		_Interface.SetCurrPlayer(player->GetId()-1);
		while (true){
			_GrIn.InitChoise("You can steal up to 2 Trade Goods from two different players",true,true,true);
			for (i = 0; i <_GameStats.GetPlayersNumber(); i++){
				if ((_Players[i] != player) && (_Players[i]->GetGoods() >= MINIMUM_TG_TO_STEAL)){
					sprintf(buff,"%s(%s)",_Players[i]->GetName().c_str(),RacesFull[_Players[i]->GetRace()].c_str());
					_GrIn.AddNumerical(EMPTY_EVENT_IMG,buff);
				}
			}
			vector<int> ret = _GrIn.LaunchChoise();
			if (ret.size() != 0){
				j = -1;
				stealed = 0;
				for (i = 0; i < ret.size(); i++)
					if (ret.at(i))
						stealed++;
				if (stealed > NUMBER_OF_PLAYERS){
					_Interface.PrintThingAll("You can't steal from more than 2 players");
					continue;
				}
				Log("e_MentakStealGoods::Execute : selected players");
				for (i = 0; i <_GameStats.GetPlayersNumber(); i++){
					if ((_Players[i] != player) && (_Players[i]->GetGoods() >= 3)){
						j++;
						if (ret.at(j)){
							player->GiveGoods(1);
							_Players[i]->TakeGoods(1);
							sprintf(buff,"Player %s steal 1 TG from player %s",player->GetName().c_str(),_Players[i]->GetName().c_str());
							_Interface.PrintThingAll(buff);
						}
					}
				}
			}
			else
				Log("e_MentakStealGoods::Execute : pass");
			break;
		}
	}
	return er_none;
}
GameEffect* e_MentakStealGoods::Clone(){
	return new e_MentakStealGoods(*this);
}
string e_MentakStealGoods::Save(){
	return string();
}
void e_MentakStealGoods::Load(std::string str){}
////////////////////////////////////////////////////////////
e_MentakFlagship::e_MentakFlagship(){
	id = "MentakFlagship";
}
bool e_MentakFlagship::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_MentakFlagship::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Army* attArmy = EP.army1;
	Army* defArmy = EP.army2;
	int attacker = EP.attacker;
	if (defArmy!=0){
		if ((Q==eq_Battle)&&(attacker==1))
			if ((attArmy->StackSize(FM))&&(attArmy->GetHex()==defArmy->GetHex()))
				defArmy->AssignUnitAbility(uaSustain,FIELD_SKIP,FIELD_SKIP,0);
			//else
			//	defArmy->AssignUnitAbility(uaSustain,FIELD_SKIP,FIELD_SKIP,1);
	}
	return er_none;
}
GameEffect* e_MentakFlagship::Clone(){
	return new e_MentakFlagship(*this);
}
string e_MentakFlagship::Save(){
	return string();
}
void e_MentakFlagship::Load(std::string str){}
/////////////////////////////////////////////////////////////////
e_MentakSalvageOperations::e_MentakSalvageOperations(){
	id = "SalvageOperations";
	name = "Salvage Operations";
	description = "+2 TG for every Space Battle. If victorious, you rebuild one enemy ship that was destroyed";
	cost = 4;
	color = RaceTech;
	race = Mentak;
	TT = ttSalvageOperations;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_MentakSalvageOperations::GetQ(GameEffectQs queue){
	if ((queue==eq_AfterBattle)||(queue==eq_AfterAssignDamage)||(queue==eq_BeforeBattle))
		return true;
	return false;
}
GameEffectRets e_MentakSalvageOperations::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Army* army = EP.army1;
	Army* target = EP.army2;
	Unit* unit = EP.unit;
	char str[127];
	int isAttacker = EP.attacker;
	bool isRebuild=false;
	int k;
	int* r;
	int options=0;
	UnitType UTrebuild;
	if (Q==eq_AfterBattle){
		army->GetOwner()->GiveGoods(2);//получить 2 товара
		sprintf(str,"Player %s receive 2 trade goods due to Salvage Operations technology",army->GetOwner()->GetName().c_str());
		_Interface.PrintThingAll(str);
		for (UnitType UT=DS; UT<FM; UT=(UnitType)((int)UT+1)){
			if ((UT==WS)&&!army->GetOwner()->GotTech(ttWarSun))
				destrUnits[WS]=false;
			if (destrUnits[UT])
				isRebuild=true;
		}
		if (army->isDefeated())
			isRebuild=false;
		if (isRebuild){
			if (SelectDialogYesNo("Rebuild one of destroyed enemy ships using Salvage Operations?")){
				while (isRebuild){
					_GrIn.InitChoise("Select a unit to rebuild",true);
					for (UnitType UT=DS; UT<FM; UT=(UnitType)((int)UT+1))
						if (destrUnits[UT])
							_GrIn.AddOption(SHIPS_IMG[UT],ShipsShort[UT]);
					vector<int> tempvec = _GrIn.LaunchChoise();
					if (tempvec.size() != 0)
						r = &tempvec[0];
					k=-1;
					if (r!=0){
						for (UnitType UT=DS; UT<FM; UT=(UnitType)((int)UT+1)){
							if (destrUnits[UT]){
								k++;
								if (r[k]==1)
									UTrebuild=UT;
							}
						}
					}
					if (army->GetOwner()->Pay(0,army->GetOwner()->GetUnitStats()->GetParametr(UTrebuild,sCOST))==frr_normal){
						army->AddUnit(UTrebuild);
						sprintf(str,"Player %s rebuild %s using Salvage Operations",army->GetOwner()->GetName().c_str(),ShipsFull[UTrebuild].c_str());
						_Interface.PrintThingAll(str);
						isRebuild=false;
						CombatInterface().FleetSupplyCheck(army);//проверка на переполнение
					}
				}
			}
		}
	}
	if (Q==eq_BeforeBattle)
		for (int i=0; i<MAX_UNIT; i++)
			destrUnits[i]=false;
	if ((Q==eq_AfterAssignDamage)&&(isAttacker==1))
		if (unit->HasAbility(uaKilled))
			destrUnits[(int)unit->Class]=true;
	return er_none;
}
GameEffect* e_MentakSalvageOperations::Clone(){
	return new e_MentakSalvageOperations(*this);
}
string e_MentakSalvageOperations::Save(){
	return string();
}
void e_MentakSalvageOperations::Load(std::string str){}
///////////////////////////////////////////////////////////////
e_MentakMirrorComputing::e_MentakMirrorComputing(){
	id = "MirrorComputing";
	name = "Mirror Computing";
	description = "When you spend Trade Goods, each Trade Good counts as 2 resources instead of one";
	cost = 4;
	color = RaceTech;
	race = Mentak;
	TT = ttMirrorComputing;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_MentakMirrorComputing::GetQ(GameEffectQs queue){
	if (queue == eq_Payment)
		return true;
	return false;
}
GameEffectRets e_MentakMirrorComputing::Execute(ExecuteParams EP){
	int *TradeToResInf = EP.CommandCounters;
	*TradeToResInf = 2;
	return er_none;
}

GameEffect* e_MentakMirrorComputing::Clone(){
	return new e_MentakMirrorComputing(*this);
}
string e_MentakMirrorComputing::Save(){
	return string();
}
void e_MentakMirrorComputing::Load(std::string str){}
///////////////////////////////////////////////////////////////
class e_MentakStartUnits:public GameEffect{
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
		curPlayer->GiveTech(ttEnviroCompensator);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_MentakPreBattle);
		curPlayer->AddGameEffect(new e_MentakFlagship);
		curPlayer->AddGameEffect(new e_MentakStealGoods);
		//curPlayer->AddGameEffect(new e_MentakSalvageOperations);
		//curPlayer->AddGameEffect(new e_MentakMirrorComputing);
		//каунтеры
		curPlayer->AddCC(2,4,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[CR] = 1;
		units->unit[CS] = 3;
		units->unit[PDS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_MentakStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};