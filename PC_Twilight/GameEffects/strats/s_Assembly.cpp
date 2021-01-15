

class e_Assembly:public e_StratCard{
public:
	int ASSEMBLY_POLITICS_DRAWN;
	int ASSEMBLY_ACTIONS_DRAWN;
	int ASSEMBLY_COUNTERS_COST;
	int ASSEMBLY_TOTAL_RES_INF;
	void reset(){
		ASSEMBLY_POLITICS_DRAWN = 1;
		ASSEMBLY_ACTIONS_DRAWN = 2;
		ASSEMBLY_COUNTERS_COST = 1;
		ASSEMBLY_TOTAL_RES_INF = 6;
		UseP = false;
		UseS = false;
	}
	void special(int n){}
	void sc_S(Player*player){
		char buff[128];
		int * res;
		int i,j,totval;
		bool doin = true;
		ostringstream ss;
		if (player->GetCountersSA()<ASSEMBLY_COUNTERS_COST){
			_Interface.PrintThingAll("Sorry, not enough counters");
			return;
		}
		sprintf(buff,"Player %s uses Assembly (secondary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		player->TakeCounter(CC_strat,ASSEMBLY_COUNTERS_COST);
		sprintf(buff,"To use this ablility you have payed %d SA counters",ASSEMBLY_COUNTERS_COST);
		_Interface.PrintThingAll(buff);
		while (doin){
			vector<int> tempvec = SelectDialogOwnedPlanet("Choose planets to open",player,true,2,false,false);
			if (tempvec.size() == 0)
				return;
			res = &tempvec[0];
			i = totval = 0;
			//plans = player->GetPlanetsList();
			//while (plans!=0){
			for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
				if (player->IsPlanetOpen(*piter)){
					//plans = plans->next;
					continue;
				}
				if (res[i] > 0)
					totval+= (*piter)->GetInf() + (*piter)->GetRes();
				++i;
				//plans = plans->next;
			}
			if (totval <= ASSEMBLY_TOTAL_RES_INF){
				i = j = 0;
				//plans = player->GetPlanetsList();
				//while (plans!=0){
				ss<<'{'<<player->GetName()<<"}'s planets to open are: ";
				for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
					++j;
					if (player->IsPlanetOpen(*piter)){
						//plans = plans->next;
						continue;
					}
					if (res[i] > 0){
						ss<<(*piter)->GetName()<<"; ";
						player->RefreshPlanet(j-1);
					}
					++i;
					//plans = plans->next;
				}
				_Interface.PrintThingAll(ss.str());
				doin = false;
			}
		}
	}
	void sc_P(Player*player){
		bool ab;
		int * result;
		Player* other;
		e_Politic* agenda;
		ostringstream ss;
		char buff[256];
		sprintf(buff,"Player %s uses Assembly (primary ability)",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		player->AddPolitic(_GameStats.DrawPolitic());
		player->AddAction(2);
		//player->givepolitic(ASSEMBLY_POLITICS_DRAWN);
		//player->giveaction(ASSEMBLY_ACTIONS_DRAWN);
		if (_GameStats.Speaker == player->GetNumber()-1){
			_Interface.PrintThingAll("Speaker has to choose self politic, other speaker");
			ab = false;
		}
		else{
			_GrIn.InitChoise("Choose eather a) or b)");
			_GrIn.AddOption(EMPTY_EVENT_IMG,"a) Self Speaker");
			_GrIn.AddOption(EMPTY_EVENT_IMG,"b) Self Politic");
			vector<int> tempvec = _GrIn.LaunchChoise();
			result = &tempvec[0];
			if (result[0] == 1){
				_Interface.PrintThingAll("Chosen a) - self speaker, other politic");
				ab = true;
			}
			else{
				_Interface.PrintThingAll("Chosen b) - self politic, other speaker");
				ab = false;
			}
		}
		other = SelectDialogPlayer("Choose other player",player);
		ss<<"Other player is "<<other->GetName();
		_Interface.PrintThingAll(ss.str());
		if (ab){
			_GameStats.Speaker = player->GetNumber()-1;
			_Interface.SetCurrPlayer(other->GetNumber()-1);
			agenda = ChoosePolitic(other);
		}
		else{
			_GameStats.Speaker = other->GetNumber()-1;
			agenda = ChoosePolitic(player);
		}
		if (agenda == 0)//если у выбранного игрока нет политоты, то вытащить из колоды
			agenda = _GameStats.DrawPolitic();
		_Interface.SetCurrPlayer(player->GetNumber()-1);
		if (agenda != 0)
			agenda->Execute(ExecuteParams());
		else
			_Interface.PrintThingAll("Assembly::Execute : we are out of politics!");
	}
	e_Assembly(){
		nt_strload(id,"Assembly\0");
		type = Assembly;
		nt_strload(image,STRAT_B_PATH[type]);
		reset();
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffect* Clone(){
		return new e_Assembly(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};