e_HacanProductionCenters::e_HacanProductionCenters(){
	id = "ProductionCenters";
	name = "Production Centers";
	description = "Once per round, spend a CC from SA to receive 4TG and give 2TG to any other player(s), but only if you have less than 6 TG";
	cost = 3;
	color = RaceTech;
	race = Hacan;
	TT = ttProductionCenters;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
	used = 0;
}
bool e_HacanProductionCenters::GetQ(GameEffectQs queue){
	if (((queue == eq_AAA) && (!used)) || (queue == eq_StatusEnd))
		return true;
	return false;
}
GameEffectRets e_HacanProductionCenters::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char buff[255];
	vector<int> ret;
	int i,k;
	if ((Q == eq_AAA) && (!used)){
		if (player->GetCountersSA() <= 0){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Not enough SACC to use Production Centers");
			return er_none;
		}
		if (player->GetGoods() >= 6){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"You can't use Production Centers (more than 5 Trade Goods)");
			return er_none;
		}
		player->TakeCounter(CC_strat);
		player->GiveGoods(4);
		sprintf(buff,"Player %s receives 4 Trade Goods from Production Centers",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		_GrIn.InitChoise("Select player to give 2 Trade Goods");
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
			if (_Players[i] != player)
				_GrIn.AddOption(_Players[i]->GetBanner(),_Players[i]->GetName());
		ret.clear();
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			Eggog("e_HacanProductionCenters::Execute : ret.size() == 0");
		k = -1;
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
			if (_Players[i] != player){
				k++;
				if (ret[k] == 1){
					_Players[i]->GiveGoods(2);
					sprintf(buff,"Player %s receives 2 Trade Goods from Production Centers",_Players[i]->GetName().c_str());
					_Interface.PrintThingAll(buff);
				}
			}
		}
		used = 1;
		return er_normal;
	}
	if (Q == eq_StatusEnd)
		used = 0;
	return er_none;
}

GameEffect* e_HacanProductionCenters::Clone(){
	return new e_HacanProductionCenters(*this);
}
string e_HacanProductionCenters::Save(){
	std::stringstream ss;
	ss << used;
	return ss.str();
}
void e_HacanProductionCenters::Load(std::string str){
	std::istringstream iss(str);
	string q;
	iss >> q >> used;
}
//////////////////////////////////////////////////
e_HacanQuantumDatahubNode::e_HacanQuantumDatahubNode(){
	id = "QuantumDatahubNode";
	name = "Quantum Datahub Node";
	description = "At the end of your Strategy Phase, you may trade one of your Strategy Cards with a Strategy Card of one of your trading partners. The other player doesnТt need to agree to the trade";
	cost = 5;
	color = RaceTech;
	race = Hacan;
	TT = ttQuantumDatahubNode;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_HacanQuantumDatahubNode::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	//	return true;
	return false;
}
GameEffectRets e_HacanQuantumDatahubNode::Execute(ExecuteParams EP){
	return er_none;
}

GameEffect* e_HacanQuantumDatahubNode::Clone(){
	return new e_HacanQuantumDatahubNode(*this);
}
string e_HacanQuantumDatahubNode::Save(){
	return string();
}
void e_HacanQuantumDatahubNode::Load(std::string str){}
//////////////////////////////////////////////////
e_HacanFlagship::e_HacanFlagship(){
	rerolls = 0;
	id = "HacanFlagship";
	image = GOODS_IMG;
}
bool e_HacanFlagship::GetQ(GameEffectQs queue){
	//if ((queue==eq_AfterRollingDices)||(queue==eq_Battle)||(queue==eq_BeforeBattleRound))
	if (((queue==eq_AfterRollingDicesAction) && rerolls)||(queue==eq_AfterRollingDices))
		return true;
	return false;
}
GameEffectRets e_HacanFlagship::Execute(ExecuteParams EP){
	Army* attArmy = EP.army1;
	GameEffectQs Q = EP.queue;
	char str[127];
	Roll* r = EP.rolls;
	Roll* selection = 0;
	int N = EP.rollNumber;
	int oldthrow;
	int newthrow;
	//if (Q == eq_Battle)
	//	rerolls=0;
	if (Q == eq_AfterRollingDices){
		//rerolls=min(2,attArmy->GetOwner()->GetGoods());
		rerolls = 2;
		if (attArmy->StackSize(FM) == 0)
			rerolls = 0;
	}
	if (Q == eq_AfterRollingDicesAction){
		//if ((attArmy->StackSize(FM)>0)&&(rerolls>0)){
			_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
			sprintf(str,"Reroll dice using 1 trage good? Rerolls left: %d",rerolls);
			while ((rerolls>0) && SelectDialogYesNo(str)){
				selection = SelectDialogRoll(attArmy->GetOwner(),r,N);
				if (selection!=0){
					oldthrow=selection->value;
					newthrow=rand()%DICE+1;
					selection->value=newthrow;
					selection->isRerolled=true;
					sprintf(str,"Player %s rerolls dice: %d -> %d",attArmy->GetOwner()->GetName().c_str(),oldthrow,newthrow);
					_Interface.PrintThingAll(str);
					attArmy->GetOwner()->TakeGoods(1);
					rerolls--;
					sprintf(str,"Reroll dice using 1 trage good? Rerolls left: %d",rerolls);
				}
				else{
					rerolls=0;
					break;
				}
			}
		//}
	}
	return er_none;
}

GameEffect* e_HacanFlagship::Clone(){
	return new e_HacanFlagship(*this);
}
string e_HacanFlagship::Save(){
	return string();
}
void e_HacanFlagship::Load(std::string str){}
//////////////////////////////////////////////////
e_HacanAdditionalTG::e_HacanAdditionalTG(){
	id = "HacanAdditionalTG";
}
bool e_HacanAdditionalTG::GetQ(GameEffectQs queue){
	return (queue == eq_TradeModificator);
}
GameEffectRets e_HacanAdditionalTG::Execute(ExecuteParams EP){
	Player* player = EP.player;
	int* sum = EP.CommandCounters;
	for (int i = 0; i < MAX_TRADES; i++)
		if (player->GetTrade(i)->owner != player)
			*sum += 1;
	return er_none;
}

GameEffect* e_HacanAdditionalTG::Clone(){
	return new e_HacanAdditionalTG(*this);
}
string e_HacanAdditionalTG::Save(){
	return string();
}
void e_HacanAdditionalTG::Load(std::string str){}
///////////////////////////////////////////////////////////
class e_HacanStartUnits:public GameEffect{
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
		EP.player->AddTrade(3);
		EP.player->AddTrade(3);
		//стартовые техи
		curPlayer->GiveTech(ttEnviroCompensator);
		curPlayer->GiveTech(ttSarweenTools);
		//эффекты
		curPlayer->AddGameEffect(new e_EnviroCompensator);
		curPlayer->AddGameEffect(new e_SarweenTools);
		curPlayer->AddGameEffect(new e_HacanFlagship);
		curPlayer->AddGameEffect(new e_HacanAdditionalTG);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 4;
		units->unit[CS] = 1;
		units->unit[CR] = 2;
		units->unit[FG] = 2;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_HacanStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};