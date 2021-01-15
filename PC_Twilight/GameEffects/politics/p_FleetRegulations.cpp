class e_p_FleetRegulations:public e_Politic{
protected:
	void YayEff(){
		_Interface.PrintThingAll("Not yet done FleetRegulations yay");
	}
	void NayEff(){
		int i;
		for (i = 0; i<_GameStats.GetPlayersNumber();++i)
			_Players[i]->AddCC(0,1,0);
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_FleetRegulations(){
		//nt_strload(id,"FleetRegulations\0");
		id = "FleetRegulations";
		tvote.yesno.resize(1);
		//strcpy(effect,"Y: noone can have more than 5 CC in FS; N: every player gets +1 CC in FS");
		effect = "Y: noone can have more than 5 CC in FS; N: every player gets +1 CC in FS";
	}
	GameEffect * Clone(){
		return new e_p_FleetRegulations(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};