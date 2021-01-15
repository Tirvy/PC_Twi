class e_p_CostOverruns:public e_Politic{
protected:
	void YayEff(){
		int j;
		for (j=0;j<_GameStats.GetPlayersNumber();++j){
			if (_Players[j]->GetPlanetsList()->size() > _Players[j]->GetGoods())
				_Players[j]->TakeGoods(_Players[j]->GetGoods());
			else
				_Players[j]->TakeGoods(_Players[j]->GetPlanetsList()->size());
		}
	}
	void NayEff(){
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_CostOverruns(){
		//nt_strload(id,"CostOverruns\0");
		id = "CostOverruns";
		tvote.yesno.resize(1);
		//strcpy(effect,"y: discard good for every planet controlled\n n: nothing");
		effect = "y: discard good for every planet controlled\n n: nothing";
	}
	GameEffect * Clone(){
		return new e_p_CostOverruns(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
