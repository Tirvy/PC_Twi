class e_p_MinisterOfExploration_add: public GameEffect{
	Player* minister;
	bool isNeutral;
public:
	e_p_MinisterOfExploration_add(Player* player){
		id = "MinisterOfExploration_add";
		minister = player;
		isNeutral = false;
	}
	e_p_MinisterOfExploration_add(){
		id = "MinisterOfExploration_add";
		//minister = player;
		minister = 0;
		isNeutral = false;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_Landing) || (queue == eq_AfterLanding));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		Planet* planet = EP.planet;
		char buff[255];
		if ((Q == eq_Landing) && (player != minister))
			isNeutral = (planet->GetOwner() == 0);
		if ((Q == eq_AfterLanding) && isNeutral && (planet->GetOwner() == player)){
			sprintf(buff,"Minister of exploration player %s has received 1 Trade Good for planet %s captured by player %s",minister->GetName().c_str(),planet->GetName().c_str(),player->GetName().c_str());
			_Interface.PrintThingAll(buff);
			minister->GiveGoods(1);
			isNeutral = false;
		}
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfExploration_add(*this);
	}
	string Save(){
		std::stringstream ss;
		if (minister != 0)
			ss<<minister->GetNumber();
		return ss.str();
	}
	void Load(std::string str){
		std::istringstream iss(str);
		string s;
		int p;
		iss>>s>>p;
		minister = _Players[p-1];
	}
};

class e_p_MinisterOfExploration:public e_Politic{
protected:
	void PlayerEff(Player* player){
		char buff[255];
		sprintf(buff,"Player %s is Minister of Exploration now",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			if (_Players[i] != player)
				_Players[i]->AddGameEffect(new e_p_MinisterOfExploration_add(player));
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_MinisterOfExploration(){
		id = "MinisterOfExploration";
		tvote.player.resize(1);
		effect = "Elected player receive 1 Trade Good when other players successfully invade neutral planets with thier land units";
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfExploration(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
