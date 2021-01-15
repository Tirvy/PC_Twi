int GetRefreshBonus(Player* player, Planet* planet){
	Army* army;
	switch (planet->GetSpecial()){
		case ShockTroops:
			army = FindAllyArmy(player,planet->GetSystem(),planet);
			if (army==0)
				army = NewArmy(player,planet->GetSystem(),planet);
			army->AddUnits(ST,2);
			break;
		case Fighters:
			army = FindAllyArmy(player,planet->GetSystem(),0);
			if (army==0)
				army = NewArmy(player,planet->GetSystem(),0);
			army->AddUnits(FG,2);
			player->CheckFleets();
			break;
		case GroundForces:
			army = FindAllyArmy(player,planet->GetSystem(),planet);
			if (army==0)
				army = NewArmy(player,planet->GetSystem(),planet);
			army->AddUnits(GF,2);
			break;
		case TradeStation:
			player->GiveGoods(2);
			break;
	}
	planet->AddState(psExhausted);
	return 1;
};

class e_PlanetRefreshAbilities:public GameEffect{
public:
	e_PlanetRefreshAbilities(){
		id = "PlanetRefreshAbilities";
		image = EMPTY_EVENT_IMG;
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_StatusEnd)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		_Interface.SetCurrPlayer(player->GetNumber()-1);
		Planet* selection = 0;
		char str[127];
		int k = 0;
		int refreshplanets = 0;
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++)
			if ((*piter)->GetSpecial())
				refreshplanets++;
		if (!refreshplanets)
			_Interface.PrintThingPlayer(player->GetNumber()-1,"No planets with refresh ability");
		while (refreshplanets){
			_GrIn.InitChoise("You can exhaust planet(s) with refresh ability",true);
			for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
				if (((*piter)->GetSpecial())&&(player->IsPlanetOpen(*piter))){
					sprintf(str,"%s (%s)",(*piter)->GetName().c_str(),SpecialShort[(*piter)->GetSpecial()].c_str());
					_GrIn.AddOption(EMPTY_EVENT_IMG,str);
				}
			}
			vector<int> tempvec = _GrIn.LaunchChoise();
			if (tempvec.size() != 0){
				k = -1;
				for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
					if (((*piter)->GetSpecial())&&(player->IsPlanetOpen(*piter))){
						k++;
						if (tempvec.at(k) == 1){
							selection = *piter;
							break;
						}
					}
				}
				if (selection != 0)
					GetRefreshBonus(player,selection);
				refreshplanets--;
			}
			else
				refreshplanets=0;
		}
		return er_none;
	}
	GameEffect * Clone(){
		return new e_PlanetRefreshAbilities(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_StatusPhaseTradeAgreementBreak:public GameEffect{
public:
	e_StatusPhaseTradeAgreementBreak(){
		id = "TradeAgreementBreak";
		image = EMPTY_EVENT_IMG;
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_StatusEnd)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		_Interface.SetCurrPlayer(player->GetNumber()-1);
		int activetrades = 0;
		int i,k;
		char buff[255];
		for (i = 0; i < MAX_TRADES; i++)
			if (player->GetTrade(i)->owner != player)
				activetrades++;
		cout<<"activetrades "<<activetrades<<endl;
		if (!activetrades){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"No active agreements to break");
			return er_none;
		}
		vector<TradeRoute*> options;
		options.clear();
		_GrIn.InitChoise("Select agreement to break",true);
		for (i = 0; i < MAX_TRADES; i++){
			if (player->GetTrade(i)->owner != player){
				sprintf(buff,"%s(%d)",player->GetTrade(i)->owner->GetName().c_str(),player->GetTrade(i)->power);
				_GrIn.AddOption(EMPTY_EVENT_IMG,buff);
				options.push_back(player->GetTrade(i));
			}
		}
		vector<int> ret;
		ret.clear();
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			return er_none;
		k = -1;
		for (i = 0; i < ret.size(); i++)
			if (ret.at(i) == 1)
				BreakRoute(player,player->GetTrade(i)->owner);
		return er_none;
	}
	GameEffect * Clone(){
		return new e_StatusPhaseTradeAgreementBreak(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_StatusPhaseScuttleUnits:public GameEffect{
public:
	e_StatusPhaseScuttleUnits(){
		id = "ScuttleUnits";
		image = EMPTY_EVENT_IMG;
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_StatusEnd)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		_Interface.SetCurrPlayer(player->GetNumber()-1);
		Hex* hex;
		vector<int> ret;
		while (true){
			ret = _GrIn.SysChoise("Select system to scuttle unit",true);
			if (ret.size() == 0)
				break;
			hex = _Map.GetHexh(ret.at(0),ret.at(1));
			ScuttleUnits(hex,player);
		}
		return er_none;
	}
	GameEffect * Clone(){
		return new e_StatusPhaseScuttleUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};