class e_p_TechnologyTariffs_YAY: public GameEffect{
public:
	e_p_TechnologyTariffs_YAY(){
		id = "TechnologyTariffs_YAY";
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_TechnologyBuy);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		int* bonus = EP.TechCostBonus;
		TechType TT = EP.Tech;
		if (_GameStats.GetTechDeck()->at(TT)->GetColor() == Red)
			*bonus = *bonus + 4;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_TechnologyTariffs_YAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_TechnologyTariffs_NAY: public GameEffect{
public:
	e_p_TechnologyTariffs_NAY(){
		id = "TechnologyTariffs_NAY";
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_TechnologyAvailable) || (queue == eq_StatusPhase));
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		int* bonus = EP.TechCostBonus;
		TechType TT = EP.Tech;
		int* TechOpen = EP.TechCostBonus;
		GameEffectQs Q = EP.queue;
		if (Q == eq_TechnologyAvailable)
			if (_GameStats.GetTechDeck()->at(TT)->GetColor() == Green)
				*TechOpen = 0;
		if (Q == eq_StatusPhase)
			return er_delete;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_TechnologyTariffs_NAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_TechnologyTariffs:public e_Politic{
protected:
	void YayEff(){
		char buff[255];
		sprintf(buff,"Technology Tariffs LAW is now active. All red technology costs +4 res to purchase");
		_Interface.PrintThingAll(buff);
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_TechnologyTariffs_YAY());
	}
	void NayEff(){
		char buff[255];
		sprintf(buff,"Technology Tariffs LAW is now active. Green technologies cannot be acquired or purchased for the remainder of this round");
		_Interface.PrintThingAll(buff);
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_TechnologyTariffs_NAY());
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_TechnologyTariffs(){
		id = "TechnologyTariffs";
		tvote.yesno.resize(1);
		effect = "YAY: All red technology costs +4 res to purchase; NAY: Green technologies cannot be acquired or purchased for the remainder of this round";
	}
	GameEffect * Clone(){
		return new e_p_TechnologyTariffs(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
