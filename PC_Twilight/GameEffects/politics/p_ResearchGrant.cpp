class e_p_ResearchGrant_YAY: public GameEffect{
public:
	e_p_ResearchGrant_YAY(){
		id = "ResearchGrant_YAY";
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_TechnologyBuy);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		TechType TT = EP.Tech;
		int* bonus = EP.TechCostBonus;
		TechTree color = _GameStats.GetTechDeck()->at(TT)->GetColor();
		int credit = 0;
		int i;
		if (color<=Yellow){
			for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
				if (player->IsPlanetOpen(*piter)){
					credit = 0;
					for (i = Red; i <= Yellow; i++)
						if ((*piter)->GetBonus((TechTree)i) > credit)
							credit = (*piter)->GetBonus((TechTree)i);
					if ((*piter)->GetBonus(color) == 0)
						*bonus = *bonus - credit;
				}
			}
		}
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_ResearchGrant_YAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_ResearchGrant_NAY: public GameEffect{
public:
	e_p_ResearchGrant_NAY(){
		id = "ResearchGrant_NAY";
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
			if (_GameStats.GetTechDeck()->at(TT)->GetColor() == Yellow)
				*TechOpen = 0;
		if (Q == eq_StatusPhase)
			return er_delete;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_ResearchGrant_NAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_ResearchGrant:public e_Politic{
protected:
	void YayEff(){
		_Interface.PrintThingAll("ResearchGrant LAW is now active. All planets that provide a technology credit now provide that credit to all technology colors");
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_ResearchGrant_YAY());
	}
	void NayEff(){
		_Interface.PrintThingAll("ResearchGrant LAW is now active. No yellow techs may be acquired or purchased for the remainder of this round");
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_ResearchGrant_NAY());
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_ResearchGrant(){
		id = "ResearchGrant";
		tvote.yesno.resize(1);
		effect = "YAY: All planets that provide a technology credit now provide that credit to all technology colors; NAY: No yellow techs may be acquired or purchased for the remainder of this round";
	}
	GameEffect * Clone(){
		return new e_p_ResearchGrant(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
