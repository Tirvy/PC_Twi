class e_Production:public e_StratCard{
public:
	int PRODUCTION_ADDITIONAL_RES;
	int PRODUCTION_PROD_LIMIT;
	int PRODUCTION_COUNTERS_COST;
	void reset(){
		PRODUCTION_ADDITIONAL_RES = 2;
		PRODUCTION_PROD_LIMIT = 3;
		PRODUCTION_COUNTERS_COST = 1;
		UseP = false;
		UseS = false;
	}
	void special(int n){}
	void sc_S(Player*player){
		Log("e_Production::sc_S : begin");
		int a=0, b=0;
		char buff[255];
		
		sprintf(buff,"To use this ablility you have to pay %d SA counters",PRODUCTION_COUNTERS_COST);
		_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
		if (player->GetCountersSA() < PRODUCTION_COUNTERS_COST){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Sorry, not enough counters");
			return;
		}
		sprintf(buff,"Player %s uses Production (secondary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		Log("e_Production::sc_S : have counter");
		if (player->CheckUnits()[DCK] == 0){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no Space Docks, can't use Double Efforts");
			return;
		}
		while (true){
			vector<int> tempvec = _GrIn.SysChoise("Choose a system with dock to produce",true);
			if (tempvec.size() == 0)//передумал использовать вторичку производства
				return;
			a = tempvec[0];
			b = tempvec[1];
			if (_Map.GetHexh(a,b))
				Log("e_Production::sc_S : select system");
			else
				Eggog("e_Production::sc_S : no hex");
			if (SystemStackSize(DCK,player,_Map.GetHexh(a,b))){
				sprintf(buff,"Produce in system %s?",_Map.GetHexh(a,b)->GetId().c_str());
				if (SelectDialogYesNo(buff)){
					Log("e_Production::sc_S : go to produce");
					player->Produce(_Map.GetHexh(a,b),PRODUCTION_PROD_LIMIT,0,true);
					Log("e_Production::sc_S : go to check fleets");
					player->CheckFleets();
					player->TakeCounter(CC_strat,PRODUCTION_COUNTERS_COST);
					break;
				}
			}
			else
				_Interface.PrintThingPlayer(player->GetNumber()-1,"No your docks there");
		}
		Log("e_Production::sc_S : end");
	}
	void sc_P(Player*player){
		int a=0, b=0;
		char buff[255];
		sprintf(buff,"Player %s uses Production (primary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		Log("e_Production::sc_P : begin");
		if (player->CheckUnits()[DCK] == 0){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no Space Docks, can't use Tight Deadline");
			return;
		}
		while (true){
			vector<int> tempvec = _GrIn.SysChoise("Choose a system with dock to produce");
			a = tempvec[0];
			b = tempvec[1];
			if (_Map.GetHexh(a,b))
				Log("e_Production::sc_P : select system");
			else
				Eggog("e_Production::sc_P : no hex");
			if (SystemStackSize(DCK,player,_Map.GetHexh(a,b))){
				sprintf(buff,"Produce in system %s?",_Map.GetHexh(a,b)->GetId().c_str());
				if (SelectDialogYesNo(buff)){
					Log("e_Production::sc_P : go to produce");
					player->Produce(_Map.GetHexh(a,b),0,PRODUCTION_ADDITIONAL_RES,true);
					Log("e_Production::sc_P : go to check fleets");
					player->CheckFleets();
					break;
				}
			}
			else
				_Interface.PrintThingPlayer(player->GetNumber()-1,"No your docks there");
		}
		Log("e_Production::sc_P : end");
	}
	e_Production(){
		nt_strload(id,"Production\0");
		type = Production;
		nt_strload(image,STRAT_B_PATH[type]);
		reset();
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffect* Clone(){
		return new e_Production(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};