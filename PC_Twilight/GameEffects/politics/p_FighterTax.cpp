class e_p_FighterTax_add: public GameEffect{
public:
	e_p_FighterTax_add(){
		id = "FighterTax_add";
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_BeforeBuild);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		player->GetUnitStats()->SetModifier(FG,sNP,-1);
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_p_FighterTax_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_FighterTax:public e_Politic{
protected:
	void YayEff(){
		_Interface.PrintThingAll("Fighter Tax LAW is now active: Fighter cost is 1 resource");
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->AddGameEffect(new e_p_FighterTax_add());
	}
	void NayEff(){
		int i,j,k;
		int fighterstokill = 0;
		int fightershave = 0;
		int selected;
		char buff[255];
		vector<int> ret;
		vector<Army*> options;
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
			fightershave = _Players[i]->CheckUnits().at(FG);
			fighterstokill = 3;
			if (fightershave < 3)
				fighterstokill = fightershave;
			while (fighterstokill){
				ret.clear();
				options.clear();
				_Interface.SetCurrPlayer(i);
				_GrIn.InitChoise("Select fighters to kill",false,true,true);
				for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
					if (((*aiter)->GetOwner() == _Players[i]) && ((*aiter)->IsUnitWithAbility(uaFighter))){
						sprintf(buff,"FG x%d (%s)",(*aiter)->IsUnitWithAbility(uaFighter),(*aiter)->GetHex()->GetId().c_str());
						_GrIn.AddOption(SHIPS_IMG[FG],buff);
						options.push_back(*aiter);
					}
				}
				ret = _GrIn.LaunchChoise();
				if (ret.size() == 0){
					Log("e_p_FighterTax::NayEff : selection is bad");
					continue;
				}
				selected = 0;
				for (j = 0; j < ret.size(); j++){
					if (ret.at(j) > options.at(j)->IsUnitWithAbility(uaFighter))
						ret.at(j) = options.at(j)->IsUnitWithAbility(uaFighter);
					selected += ret.at(j);
				}
				if (selected < fighterstokill){
					_Interface.PrintThingPlayer(i,"You have selected not enough Fighters");
					continue;
				}
				if (selected > fighterstokill){
					_Interface.PrintThingPlayer(i,"You have selected too much Fighters");
					continue;
				}
				Log("e_p_FighterTax::NayEff : go to fighters annihilation");
				for (j = 0; j < ret.size(); j++){
					for (k = 1; k <= ret.at(j); k++)
						options.at(j)->GetUnitWithAbility(uaFighter,k)->AddAbility(uaKilled);
					CombatInterface().DestroyUnit(options.at(j),options.at(j)->GetUnitWithAbility(uaKilled,1));
				}
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
	e_p_FighterTax(){
		id = "FighterTax";
		tvote.yesno.resize(1);
		effect = "YAY: each Fighter costs 1; NAY: each player must destroy 3 his Fighters if able";
	}
	GameEffect * Clone(){
		return new e_p_FighterTax(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};