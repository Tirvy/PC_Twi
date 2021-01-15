class e_p_MinisterOfCommerce_add: public GameEffect{
public:
	e_p_MinisterOfCommerce_add(){
		id = "MinisterOfCommerce_add";
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StatusPhase);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		char buff[255];
		bool isActiveTrade;
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			isActiveTrade = false;
			for (int j = 0; j < MAX_TRADES; j++)
				if (_Players[i]->GetTrade(j)->owner != _Players[i])
					isActiveTrade = true;
			if ((_Players[i] != player) && isActiveTrade && (_Players[i]->GetGoods() > 0)){
				_Players[i]->TakeGoods(1);
				player->GiveGoods(1);
				sprintf(buff,"Minister of Commerce player %s takes 1 Trade Good from player %s",player->GetName().c_str(),_Players[i]->GetName().c_str());
				_Interface.PrintThingAll(buff);
			}
		}
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfCommerce_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_MinisterOfCommerce:public e_Politic{
protected:
	void PlayerEff(Player* player){
		char buff[255];
		sprintf(buff,"Player %s is Minister of Commerce now",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		player->AddGameEffect(new e_p_MinisterOfCommerce_add());
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_MinisterOfCommerce(){
		id = "MinisterOfCommerce";
		tvote.player.resize(1);
		effect = "Elected player in Status Phase receives 1 Trade Good from each player that have at least 1 active Trade Agreement";
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfCommerce(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
