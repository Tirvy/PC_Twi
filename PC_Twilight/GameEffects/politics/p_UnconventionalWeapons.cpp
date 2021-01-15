class e_p_UnconventionalWeapon_add: public GameEffect{
public:
	e_p_UnconventionalWeapon_add(){
		nt_strload(id,"UnconventionalWeapon_add\0");
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_Battle);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* attArmy = EP.army1;
		if (EP.queue == eq_Battle){
			for (int i = 1; i <= attArmy->StackSize(DR);i++)
				attArmy->GetUnit(DR,i)->ModAbility(uaSpaceBattle,+2);
			for (int i = 1; i <= attArmy->StackSize(WS);i++)
				attArmy->GetUnit(WS,i)->ModAbility(uaSpaceBattle,+2);
		}

		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_UnconventionalWeapon_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_UnconventionalWeapon:public e_Politic{
protected:
	void YayEff(){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_UnconventionalWeapon_add());
	}
	void NayEff(){
		vector<Planet*>* pl;
		vector<Planet*> options;
		vector<int> ret;
		int tap;
		char buff[255];
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			tap = _Players[i]->CheckUnits().at(DR) + _Players[i]->CheckUnits().at(WS);
			options.clear();
			
			pl = _Players[i]->GetPlanetsList();
			for (vector<Planet*>::iterator piter = pl->begin(); piter != pl->end(); piter++)
				if (!(*piter)->HasState(psExhausted))
					options.push_back(*piter);
			while (options.size() > 0){
				_Interface.SetCurrPlayer(i);
				if (options.size() < tap)
					tap = options.size();
				if (tap == 0)
					break;
				sprintf(buff,"Exhaust %d planet(s)",tap);
				_GrIn.InitChoise(buff,false,true,true);
				for (vector<Planet*>::iterator piter = options.begin(); piter != options.end(); piter++)
					_GrIn.AddNumerical(PLANET_IMG,(*piter)->GetName());
				ret.clear();
				ret = _GrIn.LaunchChoise();
				if (ret.size() == 0){
					Log("e_p_UnconventionalWeapon::NayEff : bad choise");
					continue;
				}
				if (CheckNumericalRet(ret) < tap){
					_Interface.PrintThingPlayer(i,"Not enough planets to exhaust");
					continue;
				}
				if (CheckNumericalRet(ret) > tap){
					_Interface.PrintThingPlayer(i,"Too much planets to exhaust");
					continue;
				}
				Log("e_p_UnconventionalWeapon::NayEff : go to tap planet");
				for (int j = 0; j < ret.size(); j++)
					if (ret.at(j))
						options.at(j)->AddState(psExhausted);
				break;
			}
		}
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_UnconventionalWeapon(){
		id = "UnconventionalWeapon";
		tvote.yesno.resize(1);
		effect = "YAY: All Warsuns and Dreadnoughts receive -2 to all combat rolls;\n NAY: All players have to exhaust one planet for each thier Warsun or Dreadnought";
	}
	GameEffect * Clone(){
		return new e_p_UnconventionalWeapon(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};