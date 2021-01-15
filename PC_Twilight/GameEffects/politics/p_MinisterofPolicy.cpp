class e_p_MinisterOfPolicy_add: public GameEffect{
public:
	e_p_MinisterOfPolicy_add(){
		id = "e_p_MinisterOfPolicy_add";
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StatusPhase);
	}
	GameEffectRets Execute(ExecuteParams EP){
		int* ACs = EP.ActionCards;
		*ACs = *ACs + 1;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfPolicy_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_MinisterOfPolicy:public e_Politic{
protected:
	void PlayerEff(Player* player){
		char buff[255];
		sprintf(buff,"Player %s is Minister of Policy now",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		player->AddGameEffect(new e_p_MinisterOfPolicy_add());
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_MinisterOfPolicy(){
		id = "MinisterOfPolicy";
		tvote.player.resize(1);
		effect = "Elected player in Status Phase receives 1 additional Action Card";
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfPolicy(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
