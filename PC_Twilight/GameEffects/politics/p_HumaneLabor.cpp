class e_p_HumanLabor_YAY: public GameEffect{
public:
	e_p_HumanLabor_YAY(){
		id = "HumanLabor_YAY";
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_BeforeBuild);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		int i;
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if ((*aiter)->GetOwner() == player){
				if ((*aiter)->GetPlanet() != 0){
					for (i = 1; i <= (*aiter)->StackSize(DCK); i++){
						(*aiter)->GetUnit(DCK,i)->ModAbility(uaProduction,-2);
					}
				}
			}
		}
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_HumanLabor_YAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_HumanLabor_NAY: public GameEffect{
public:
	e_p_HumanLabor_NAY(){
		id = "HumanLabor_NAY";
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_BeforeBuild) || (queue == eq_StatusPhase));
	}
	GameEffectRets Execute(ExecuteParams EP){
		int i;
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		if (Q == eq_BeforeBuild)
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
				if ((*aiter)->GetOwner() == player)
					for (i = 1; i <= (*aiter)->StackSize(DCK); i++)
						(*aiter)->GetUnit(DCK,i)->AssignAbility(uaProduction,FIELD_SKIP,0);
		if (Q == eq_StatusPhase)
			return er_delete;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_HumanLabor_NAY(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_HumanLabor:public e_Politic{
protected:
	void YayEff(){
		char buff[255];
		sprintf(buff,"Human Labor LAW is now active. All Space Docks receive -2 production limit");
		_Interface.PrintThingAll(buff);
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_HumanLabor_YAY());
	}
	void NayEff(){
		char buff[255];
		sprintf(buff,"Human Labor LAW is now active. All Space Docks can't produce units in this round");
		_Interface.PrintThingAll(buff);
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_HumanLabor_NAY());
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_HumanLabor(){
		id = "HumanLabor";
		tvote.yesno.resize(1);
		effect = "YAY: all Space Docks receive -2 production limit; NAY: Space Docks can't produce units in this round";
	}
	GameEffect * Clone(){
		return new e_p_HumanLabor(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
