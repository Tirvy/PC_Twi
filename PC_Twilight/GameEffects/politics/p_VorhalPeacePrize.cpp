class e_p_VorhalPeacePrize_add: public GameEffect{
public:
	e_p_VorhalPeacePrize_add(){
		nt_strload(id,"VorhalPeacePrize_add\0");
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StatusPhase);
	}
	GameEffectRets Execute(ExecuteParams EP){
		if (EP.queue == eq_StatusPhase){
			int i,low = 0;
			int* CC = EP.CommandCounters;
			for (i=0;i<_GameStats.GetPlayersNumber();++i){
				if (_Players[i]->GetCountersFS() > low)
					low = _Players[i]->GetCountersFS();
			}
			for (i=0;i<_GameStats.GetPlayersNumber();++i){
				if (_Players[i]->GetCountersFS() == low)
					*CC = *CC+1;
					//_Players[i]->AddCC(0,1,0);
			}
		}
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_VorhalPeacePrize_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_VorhalPeacePrize:public e_Politic{
protected:
	void YayEff(){
		_GameStats.AddLaw(new e_p_VorhalPeacePrize_add);
	}
	void NayEff(){
		int i,low = 0;
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			if (_Players[i]->GetCountersFS() > low)
				low = _Players[i]->GetCountersFS();
		}
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			if (_Players[i]->GetCountersFS() == low)
				_Players[i]->GiveGoods(3);
		}
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_VorhalPeacePrize(){
		//nt_strload(id,"VorhalPeacePrize\0");
		id = "VorhalPeacePrize";
		tvote.yesno.resize(1);
		//trcpy(effect,"For: Player(s) with lowest fleet supply gain 1 CC during status phase. Against: Players(s) with lowest fleet supply gain immediately 3 TG.");
		effect = "For: Player(s) with lowest fleet supply gain 1 CC during status phase. Against: Players(s) with lowest fleet supply gain immediately 3 TG.";
	}
	GameEffect * Clone(){
		return new e_p_VorhalPeacePrize(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};