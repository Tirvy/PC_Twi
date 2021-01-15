// -------- class itself --------
class e_Leadership:public e_StratCard{
public:
	int LEADERSHIP_FREE_COUNTERS;
	int LEADERSHIP_MAX_ADD_COUNTERS;
	int LEADERSHIP_INF_PER_COUNTER;
	void reset(){
		LEADERSHIP_FREE_COUNTERS = 3;
		LEADERSHIP_MAX_ADD_COUNTERS = 3;
		LEADERSHIP_INF_PER_COUNTER = 2;
		UseP = false;
		UseS = false;
	}
	void special(int n){}
	void sc_S(Player*player){
		int * results;
		int toget;
		char buff[256];
		sprintf(buff,"Player %s uses Leadership (secondary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		Log("e_Leadership::sc_S : starts");
		sprintf(buff,"You can buy up to %d counters %d inf each",LEADERSHIP_MAX_ADD_COUNTERS,LEADERSHIP_INF_PER_COUNTER);
		while(true){
			Log("e_Leadership::sc_S : initiate choise");
			_GrIn.InitChoise(buff,false,true,true);
			_GrIn.AddNumerical(EMPTY_EVENT_IMG,"Counters to buy");
			vector<int> tempvec = _GrIn.LaunchChoise();
			if (tempvec.size() != 0){
				Log("e_Leadership::sc_S : selected buying counters");
				results = &tempvec[0];
			}
			if ((results == 0)||(results[0] == 0)){
				Log("e_Leadership::sc_S : selected pass");
				return;
			}
			if (results[0] > LEADERSHIP_MAX_ADD_COUNTERS){
				sprintf(buff,"You want too much(%d). You can buy up to %d counters %d inf each",results[0],LEADERSHIP_MAX_ADD_COUNTERS,LEADERSHIP_INF_PER_COUNTER);
				continue;
			}
			toget = results[0];
			if (player->Pay(1,toget*LEADERSHIP_INF_PER_COUNTER) == frr_normal){
				player->GiveFreeCounters(toget);
				return;
			}
			sprintf(buff,"You can buy up to %d counters %d inf each",LEADERSHIP_MAX_ADD_COUNTERS,LEADERSHIP_INF_PER_COUNTER);
		}
	}
	void sc_P(Player*player){
		Log("e_Leadership::sc_P : starts");
		char buff[256];
		sprintf(buff,"Player %s uses Leadership (primary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		sprintf(buff,"You gets free %d counters",LEADERSHIP_FREE_COUNTERS);
		_Interface.PrintThingPlayer(player->GetNumber()-1,buff);
		player->GiveFreeCounters(LEADERSHIP_FREE_COUNTERS);
		sc_S(player);
	}
	e_Leadership(){
		nt_strload(id,"Leadership\0");
		type = Leadership;
		nt_strload(image,STRAT_B_PATH[type]);
		reset();
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffect* Clone(){
		return new e_Leadership(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};