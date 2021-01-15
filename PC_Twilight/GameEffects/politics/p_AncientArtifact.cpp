class e_p_AncientArtifact:public e_Politic{
protected:
	void YayEff(){
		int roll = rand()%DICE+1;
		char str[127];
		int i,k;
		sprintf(str,"So, we're pushing The Big Red Button and its... %d",roll);
		_Interface.PrintThingAll(str);
		if (roll<=5){
			sprintf(str,"Damn it, we are screwed");
			_Interface.PrintThingAll(str);
			Log("e_p_AncientArtifact::YayEff : get Mecatol");
			Hex* mecatol = _Map.GetHexh(0,0);
			bool t;
			int damage;
			Log("e_p_AncientArtifact::YayEff : go to search targets");
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
				if ((*aiter)->GetHex() == mecatol){
					Log("e_p_AncientArtifact::YayEff : destroy army in mecatol");
					t = false;
					for (int i=1; i<=(*aiter)->IsUnitWithAbility(uaNone); i++){
						(*aiter)->GetUnitWithAbility(uaNone,i)->AddAbility(uaKilled);
						t = true;
					}
					Log("e_p_AncientArtifact::YayEff : added uaKilled");
					if (t)
						CombatInterface().DestroyUnit(*aiter,(*aiter)->GetUnitWithAbility(uaNone,1));
					Log("e_p_AncientArtifact::YayEff : destroyed army in mecatol");
				}
				if ((isAdjacent(mecatol,(*aiter)->GetHex())==1)&&((*aiter)->GetPlanet()==0)){
					Log("e_p_AncientArtifact::YayEff : adjacent hex fleet");
					damage=0;
					for (int k=1; k<=3; k++)
						if ((rand()%DICE+1)>=5)
							damage++;
					Log("e_p_AncientArtifact::YayEff : go to assign damage");
					CombatInterface().SelectCasualties(*aiter,0,damage,bt_Space);
					Log("e_p_AncientArtifact::YayEff : end");
				}
			}
		}
		else{
			sprintf(str,"All players are receiving 2 free Technologies");
			_Interface.PrintThingAll(str);
			for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
				i = k % _GameStats.GetPlayersNumber();
				_Interface.SetCurrPlayer(i);
				int cost = FREE_TECH_COST;
				int CC = 0;
				_Players[i]->ExecuteGameEffect(ExecuteParams(eq_ResearchTech,_Players[i],&cost,&CC));
				_Players[i]->ExecuteGameEffect(ExecuteParams(eq_ResearchTech,_Players[i],&cost,&CC));
				//ResearchTechDialog(_Players[i],FREE_TECH_COST,0);
				//ResearchTechDialog(_Players[i],FREE_TECH_COST,0);
			}
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
	e_p_AncientArtifact(){
		//nt_strload(id,"Ancient Artifact\0");
		id = "AncientArtifact";
		tvote.yesno.resize(1);
		//strcpy(effect,"y: roll die 1-5:\n all units and ships in Mecatol are destroyed and every fleed adjacent take 3 rolls of strength 5\n 6-10: all players gain 2 techs\n n: discard\n");
		effect = "y: roll die 1-5: all units and ships in Mecatol are destroyed and every fleed adjacent take 3 rolls of strength 5 6-10: all players gain 2 techs n: discard";
	}
	GameEffect * Clone(){
		return new e_p_AncientArtifact(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};