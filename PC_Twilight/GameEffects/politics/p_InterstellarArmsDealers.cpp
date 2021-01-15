class e_p_InterstellarArmsDealers_add: public GameEffect{
public:
	e_p_InterstellarArmsDealers_add(){
		nt_strload(id,"InterstellarArmsDealers_add\0");
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_BeforeBuild) || (queue == eq_StatusPhase));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		if (Q == eq_BeforeBuild){
			player->GetUnitStats()->SetModifier(FG,sNP,-1);
			for (UnitType UT = DS; UT <= FM; UT = (UnitType)((int)UT + 1))
				player->GetUnitStats()->SetModifier(UT,sCOST,+1);
		}
		if (Q == eq_StatusPhase)
			return er_delete;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_InterstellarArmsDealers_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_InterstellarArmsDealers:public e_Politic{
protected:
	void YayEff(){
		Army* army;
		vector<Army*> armies;
		vector<Hex*> options;
		vector<int> ret;
		Hex* place;
		char buff[255];
		bool t;
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			armies.clear();
			options.clear();
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
				if (((*aiter)->GetOwner() == _Players[i]) && ((*aiter)->StackSize(DCK))){
					army = FindArmy((*aiter)->GetHex(),_Players[i]);
					if (army == 0)
						armies.push_back(*aiter);
					else
						if (army->GetOwner() == _Players[i])
							armies.push_back(*aiter);
				}
			}
			for (vector<Army*>::iterator aiter = armies.begin(); aiter != armies.end(); aiter++){
				t = false;
				for (vector<Hex*>::iterator hiter = options.begin(); hiter != options.end(); hiter++)
					if (*hiter == (*aiter)->GetHex())
						t = true;
				if (!t)
					options.push_back((*aiter)->GetHex());
			}
			if (options.size()){
				_Interface.SetCurrPlayer(i);
				if (SelectDialogYesNo("Buy 1 Dreadnought and 1 Destroyer for 3 resources?")){
					if (_Players[i]->Pay(0,3) == frr_normal){
						_GrIn.InitChoise("Select system to place units");
						for (vector<Hex*>::iterator hiter = options.begin(); hiter != options.end(); hiter++)
							_GrIn.AddOption(EMPTY_EVENT_IMG,(*hiter)->GetId());
						ret = _GrIn.LaunchChoise();
						if (ret.size() != 0){
							for (int j = 0; j < ret.size(); j++)
								if (ret.at(j) == 1)
									place = options.at(j);
							army = FindArmy(place,_Players[i],true);
							army->AddUnit(DR);
							army->AddUnit(DS);
							sprintf(buff,"Player %s spawns Dreadnought and Destroyer in system %s",_Players[i]->GetName().c_str(),place->GetId().c_str());
							_Interface.PrintThingAll(buff);
							_Players[i]->CheckFleets();
						}
					}
				}
			}
		}
	}
	void NayEff(){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_InterstellarArmsDealers_add());
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_InterstellarArmsDealers(){
		id = "InterstellarArmsDealers";
		tvote.yesno.resize(1);
		effect = "YAY: players may pay 3 resources to receive Dreadnought and Destroyer, they will be placed in system with players's Space Dock; NAY: cost of all ships and fighters +1 till end of round";
	}
	GameEffect * Clone(){
		return new e_p_InterstellarArmsDealers(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};