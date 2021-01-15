class e_p_FundResearchComplex_bonus:public GameEffect{
	int xp, yp, p;
public:
	e_p_FundResearchComplex_bonus(Planet* pl){
		nt_strload(id,"FundResearchComplex bonus\0");
		pl->GetSystem()->GetCoords(&xp,&yp);
		for (int i = 1; i <= MAX_PLANETS; i++)
			if (pl->GetSystem()->GetPlanet(i) == pl)
				p = i;
	}
	e_p_FundResearchComplex_bonus(){
		xp = 0;
		yp = 0;
		p = 1;
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_TechnologyBuy)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		TechType TT = EP.Tech;
		int* bonus = EP.TechCostBonus;
		Planet* plan = _Map.GetHexh(xp,yp)->GetPlanet(p);
		if (plan != 0)
			if (plan->GetOwner() == player)
				*bonus = *bonus - 2;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_FundResearchComplex_bonus(*this);
	}
	string Save(){
		std::stringstream ss;
		ss<<xp<<" "<<yp<<" "<<p;
		return ss.str();
	}
	void Load(std::string str){
		std::istringstream iss(str);
		string s;
		iss>>s>>xp>>yp>>p;
	}
};

class e_p_FundResearchComplex:public e_Politic{
protected:
	void PlanEff(Planet* plan){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_FundResearchComplex_bonus(plan));
	}
	void DoEffect(Voting won){
		PlanEff(won.planet[0]);
	}
public:
	e_p_FundResearchComplex(){
		//nt_strload(id,"FundResearchComplex\0");
		id = "FundResearchComplex";
		tvote.planet.resize(1);
		//strcpy(effect,"Owner of chosen planet gets 2 res discount for new techs");
		effect = "Owner of chosen planet gets 2 res discount for new techs";
	}
	GameEffect * Clone(){
		return new e_p_FundResearchComplex(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};