int BreakRoute(Player* pl1, Player* pl2){
	TradeRoute* tr1 = 0;
	TradeRoute* tr2 = 0;
	char buff[255];
	int i;
	for (i = 0; i < MAX_TRADES; i++)
		if (pl1->GetTrade(i)->owner == pl2)
			tr1 =pl1->GetTrade(i);
	for (i = 0; i < MAX_TRADES; i++)
		if (pl2->GetTrade(i)->owner == pl1)
			tr2 =pl2->GetTrade(i);
	if ((tr1 != 0) && (tr2 != 0)){
		SwapTrades(pl1,tr1,pl2,tr2);
		sprintf(buff,"Player %s and player %s break their trade agreement",pl1->GetName().c_str(),pl2->GetName().c_str());
		_Interface.PrintThingAll(buff);
	}
	return 0;
};

class e_Trade:public e_StratCard{
	int TRADE_FREE_GOODS;
	int TRADE_CANCEL_LIMIT;
	int TRADE_SEC_MODIFIER;

	void reset(){
		TRADE_FREE_GOODS = 3;
		TRADE_CANCEL_LIMIT = 2;
		TRADE_SEC_MODIFIER = 1;
		UseP = false;
		UseS = false;
	}
public:
	void special(int n){}
	void sc_P(Player*player){
		int i,j,sum,zsum;
		int * result;
		//TradeRoute* temp;
		PowDouble<TradeRoute,Player> dev1,dev2;
		char buff[256];
		sprintf(buff,"Player %s uses Trade (primary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		_Interface.ViewPlayersTrades();
		_GrIn.InitChoise("Choose either a or b");
		_GrIn.AddOption(EMPTY_EVENT_IMG,"a) Recive 3 trade goods");
		_GrIn.AddOption(EMPTY_EVENT_IMG,"b) Cancel up to 2 trade agreement");
		vector<int> tempvec = _GrIn.LaunchChoise();
		result = &tempvec[0];
		if (result[0] == 1)
			player->GiveGoods(TRADE_FREE_GOODS);// a
		if (result[1] == 1){
			dev1 = SelectDialogTradeRoute(true);// b, two times, can pass
			if (dev1.elem1!=0)
				for (i=0;i<MAX_TRADES;++i)
					if (dev1.elem1->owner->GetTrade(i)->owner == dev1.elem2)
						SwapTrades(dev1.elem2,dev1.elem1,dev1.elem1->owner,dev1.elem1->owner->GetTrade(i));
			dev1 = SelectDialogTradeRoute(true);
			if (dev1.elem1!=0)
				for (i=0;i<MAX_TRADES;++i)
					if (dev1.elem1->owner->GetTrade(i)->owner == dev1.elem2)
						SwapTrades(dev1.elem2,dev1.elem1,dev1.elem1->owner,dev1.elem1->owner->GetTrade(i));
		}

		_Interface.PrintThingAll("Get your goods from TRs!");//giving goods, accordinally to routes
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			sum = 0;
			zsum = 0;
			for (j=0; j<MAX_TRADES; ++j)
				if (_Players[i]->GetTrade(j)->owner != _Players[i])
					sum += _Players[i]->GetTrade(j)->power;
			if ((sum>0)&&(_Players[i] != player))
				sum -= TRADE_SEC_MODIFIER;
			_Players[i]->ExecuteGameEffect(ExecuteParams(eq_TradeModificator,_Players[i],&sum,&zsum));
			if (sum > 0)
				_Players[i]->GiveGoods(sum);
		}

		while (true){
			_Interface.SetCurrPlayer(player->GetNumber()-1);
			if (!SelectDialogYesNo("Do you wish to orginize a new trade?"))// choosing 2 routes
				break;
			dev1 = SelectDialogTradeRoute(false);
			if (dev1.elem1==0)
				break;
			dev2 = SelectDialogTradeRoute(false,dev1.elem1);
			if (dev2.elem1==0)
				break;
			sum = 0;
			if ( dev1.elem2 == dev2.elem2 ){//check for 1 player
				_Interface.PrintThingAll("Cant swap between one player");
				continue;
			}
			for (i=0;i<MAX_TRADES;++i)//check for previous routes
				if ((dev1.elem2->GetTrade(i)!=dev1.elem1)&&(dev1.elem2->GetTrade(i)->owner == dev2.elem2)){
					_Interface.PrintThingAll("Already got 1 route between these players");
					sum = -1;
				}
			if (sum == -1)
				continue;

			if (dev1.elem2!=player){//asking to agree
				_Interface.SetCurrPlayer(dev1.elem2->GetNumber()-1);
				sprintf(buff,"Agree to trade your %d to {%s} %d?",dev1.elem1->power,dev2.elem2->GetName().c_str(),dev2.elem1->power);
				if (!SelectDialogYesNo(buff)){
					_Interface.PrintThingAll("Player refused to make this trade");
					continue;
				}
			}
			if (dev2.elem2!=player){
				_Interface.SetCurrPlayer(dev2.elem2->GetNumber()-1);
				sprintf(buff,"Agree to trade your %d to {%s} %d?",dev2.elem1->power,dev1.elem2->GetName().c_str(),dev1.elem1->power);
				if (!SelectDialogYesNo(buff)){
					_Interface.PrintThingAll("Player refused to make this trade");
					continue;
				}	
			}
			if (!SwapTrades(dev1.elem2,dev1.elem1,dev2.elem2,dev2.elem1))//swap
				_Interface.PrintError("Couldnt swap trades");
		}
	}
	void sc_S(Player*player){
		_Interface.PrintThingAll("Trade2 got no secondary");
	}
	e_Trade(){
		nt_strload(id,"Trade\0");
		type = Trade;
		nt_strload(image,STRAT_B_PATH[type]);
		reset();
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffect* Clone(){
		return new e_Trade(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};