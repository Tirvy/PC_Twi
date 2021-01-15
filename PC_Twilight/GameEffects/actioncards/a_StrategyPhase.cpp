//Command Sammit
class e_a_CommandSammit:public e_ActionCard{
public:
	e_a_CommandSammit(){
		_name = "Command Sammit";
		_description = "During Strategy Phase. Receive 2 free Command Counters";
		_when = acBeforeBattleRound;
		id = "a_CommandSammit";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StrategyAction);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		char buff[255];
		if (SelectDialogYesNo("Use Command Sammit?")){
			sprintf(buff,"Player %s uses Command Sammit and receive 2 free Command Counters",player->GetName().c_str());
			_Interface.PrintThingAll(buff);
			player->GiveFreeCounters(2);
			return er_delete;
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_a_CommandSammit(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Signal Jamming
class e_a_SignalJamming:public e_ActionCard{
public:
	e_a_SignalJamming(){
		_name = "Signal Jamming";
		_description = "During Strategy Phase. Activate no-Home System of any player by his counter";
		_when = acBeforeBattleRound;
		id = "a_SignalJamming";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StrategyAction);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		Player* target = 0;
		Hex* h = 0;
		vector<int> ret;
		char buff[255];
		if (SelectDialogYesNo("Use Signal Jamming?")){
			while (true){
				target = SelectDialogPlayer("Select player to use Signal Jamming",player);
				if (target == 0)
					return er_none;
				ret = _GrIn.SysChoise("Select System to use Signal Jamming",true);
				if (ret.size() == 0)
					continue;
				h = _Map.GetHexh(ret[0],ret[1]);
				sprintf(buff,"Player %s uses Signal Jamming on player %s in hex %s",player->GetName().c_str(),target->GetName().c_str(),h->GetId().c_str());
				_Interface.PrintThingAll(buff);
				h->SetCC(target->GetNumber());
				return er_delete;
			}
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_a_SignalJamming(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Trade Stop
class e_a_TradeStop:public e_ActionCard{
public:
	e_a_TradeStop(){
		_name = "Trade Stop";
		_description = "During Strategy Phase. Break all Trade Agreements";
		_when = acBeforeBattleRound;
		id = "a_TradeStop";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StrategyAction);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		int i,j;
		if (SelectDialogYesNo("Use Trade Stop?")){
			for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
				for (j = i + 1; j < _GameStats.GetPlayersNumber(); j++)
					BreakRoute(_Players[i],_Players[j]);
			return er_delete;
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_a_TradeStop(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};