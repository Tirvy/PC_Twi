class e_p_IntergalacticCommerce_add: public GameEffect{
public:
	int powers[MAX_TRADES-1];
	TradeRoute* routes[MAX_TRADES-1];
	e_p_IntergalacticCommerce_add(){
		nt_strload(id,"IntergalacticCommerce_add\0");
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_StatusStart);
	}
	GameEffectRets Execute(ExecuteParams EP){
		int i = 0;
		if (EP.queue == eq_StatusEnd){
			while (routes[i] != 0){
				routes[i]->power = powers[i];
				++i;
			}
		}
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_p_IntergalacticCommerce_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_IntergalacticCommerce:public e_Politic{
protected:
	void YayEff(){
		int i;
		bool isPortal;
		list<Hex*>::iterator hexes;
		for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++){
			isPortal = false;
			for (i=wh_NONE+1;i<wh_MAX;++i)
				if ((*hiter)->GotPortal((WormholeType)i))
					isPortal = true;
			if (isPortal)
				if (HexController(*hiter) != 0)
					HexController(*hiter)->GiveGoods(3);
		}
	}
	void NayEff(){
		int i,j;
		e_p_IntergalacticCommerce_add* eff;
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			eff = new e_p_IntergalacticCommerce_add;
			for (j=0;j<MAX_TRADES;++j){
				eff->powers[j] = _Players[i]->GetTrade(j)->power;
				eff->routes[j] = _Players[i]->GetTrade(j);
				_Players[i]->GetTrade(j)->power = 1;
			}
			_Players[i]->AddGameEffect(eff);
		}
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_IntergalacticCommerce(){
		//nt_strload(id,"IntergalacticCommerce\0");
		id = "IntergalacticCommerce";
		tvote.yesno.resize(1);
		//strcpy(effect,"For: each wormhole gives 3 TG to its owner 	Against: Each trade contract value is reduced to 1 remainder of this round ");
		effect = "YAY: Each wormhole system that contain ships immediately gives its controller 3 TG; NAY: Each trade contract's value is reduced to 1 for the remainder of this round";
	}
	GameEffect * Clone(){
		return new e_p_IntergalacticCommerce(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
