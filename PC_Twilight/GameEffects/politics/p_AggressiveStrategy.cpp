class e_p_AggressiveStrategy_nay: public GameEffect{
public:
	e_p_AggressiveStrategy_nay(){
		nt_strload(id,"AggressiveStrategy nay\0");
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_StratSecStart)||(queue == eq_StratActiveStart)||(queue == eq_StatusStart));
	}
	GameEffectRets Execute(ExecuteParams EP){
		if (EP.queue == eq_StatusStart)
			return er_delete;
		EP.stratcard->UseS = false;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_AggressiveStrategy_nay(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_AggressiveStrategy:public e_Politic{
protected:
	void YayEff(){
		int i,j,k;
		for (i=0;i<MAX_STRAT;++i)
			for (j=0;j<_GameStats.GetPlayersNumber();++j)
				if (_Players[j]->GetInitiative() == i){
					_Interface.SetCurrPlayer(j);
					for (k=0;k<MAX_STRAT;++k){
						if (_Players[j]->GotStrat((StratsType)k)){
							_StratShared[k]->reset();
							_Players[j]->ExecuteGameEffect(ExecuteParams(eq_StratSecStart,_Players[j],_StratShared[k]));
							switch (k){
								case Leadership:
									((e_Leadership*)(_StratShared[k]));
									break;
								case Diplomacy:
									((e_Diplomacy*)(_StratShared[k]))->DIPLOMACY_COUNTERS_COST = 0;;
									break;
								case Assembly:
									((e_Assembly*)(_StratShared[k]))->ASSEMBLY_COUNTERS_COST = 0;
									break;
								case Production:
									((e_Production*)(_StratShared[k]))->PRODUCTION_COUNTERS_COST = 0;
									break;
								case Trade:
									((e_Trade*)(_StratShared[k]));
									break;
								case Warfare:
									((e_Warfare*)(_StratShared[k]))->WARFARE_SECONDARY_COUNTERS_COST = 0;
									break;
								case Technology:
									((e_Technology*)(_StratShared[k]))->TECHNOLOGY_SECONDARY_COUNTERS_COST = 0;
									break;
								case Bureaucracy:
									((e_Bureaucracy*)(_StratShared[k]))->BUREAUCRACY_SECONDARY_COUNTERS_COST = 0;
									break;
								_Players[j]->ExecuteGameEffect(ExecuteParams(eq_StratSecEnd,_Players[j],_StratShared[k]));
							}
							_StratShared[k]->sc_S(_Players[j]);
						}
					}
				}
	}
	void NayEff(){
		int i;
		for (i=0;i<_GameStats.GetPlayersNumber();++i)
			_Players[i]->AddGameEffect(new e_p_AggressiveStrategy_nay);
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:

	e_p_AggressiveStrategy(){
		//nt_strload(id,"AggressiveStrategy\0");
		id = "AggressiveStrategy";
		tvote.yesno.resize(1);
		//strcpy(effect,"y: all do their secondary ablity\n n: no secondary untill next round");
		effect = "y: all do their secondary ability n: no secondary untill next round";
	}
	GameEffect * Clone(){
		return new e_p_AggressiveStrategy(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
