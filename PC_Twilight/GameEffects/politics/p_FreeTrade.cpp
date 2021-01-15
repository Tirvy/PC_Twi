class e_p_FreeTrade_YAY: public GameEffect{
public:
	e_p_FreeTrade_YAY(){
		id = "FreeTrade_YAY";
	}
	bool GetQ(GameEffectQs queue){
		if (queue == eq_TradeModificator)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		int* sum = EP.CommandCounters;
		for (int i = 0; i < MAX_TRADES; i++)
			if (player->GetTrade(i)->owner != player)
				*sum += 1;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_FreeTrade_YAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_FreeTrade:public e_Politic{
protected:
	void YayEff(){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_FreeTrade_YAY);
		/*char buff[255];
		_Interface.PrintThingAll("Free Trade LAW is now active. Each time a player receives Trade Goods from his active trade agreements, he receives one additional Trade Good");
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			for (int j = 0; j < MAX_TRADES; j++)
				_Players[i]->GetTrade(j)->power += 1;*/
	}
	void NayEff(){
		char buff[255];
		int tolose;
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			tolose = 2;
			if (_Players[i]->GetGoods() < 2)
				tolose = _Players[i]->GetGoods();
			_Players[i]->TakeGoods(tolose);
			sprintf(buff,"Player %s loses %d Trade Goods",_Players[i]->GetName().c_str(),tolose);
			_Interface.PrintThingAll(buff);
		}
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_FreeTrade(){
		id = "FreeTrade";
		tvote.yesno.resize(1);
		effect = "YAY: Each time a player receives Trade Goods from his active trade agreements, he receives one additional Trade Good; NAY: All players must discard 2 Trade Goods, if able";
	}
	GameEffect * Clone(){
		return new e_p_FreeTrade(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
