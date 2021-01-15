
class e_p_SubsidizedIndustry:public e_Politic{
protected:
	void PlayerEff(Player* player){
		int * res;
		char buff[64];
		int i=0;
		//PowExv<Planet>* plans = player->GetPlanetsList();
		_GrIn.InitChoise("Choose a planet to place a dock",true);
		//while (plans!=0){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if (!player->CanBuildDock(*piter)){
				//plans = plans->next;
				continue;
			}
			sprintf(buff,"{%s} %d/%d",(*piter)->GetName().c_str(),(*piter)->GetRes(),(*piter)->GetInf());
			_GrIn.AddOption(PLANET_IMG,buff);
			//plans = plans->next;
		}
		vector<int> tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() != 0){
			res = &tempvec[0];
			for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
				if (!player->CanBuildDock(*piter)){
					//plans = plans->next;
					continue;
				}
				if (res[i] == 1)
					FindArmy((*piter)->GetSystem(),player,true,*piter)->AddUnit(DCK);
				//plans = plans->next;
				++i;
			}
		}
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_SubsidizedIndustry(){
		//nt_strload(id,"SubsidizedIndustry\0");
		id = "SubsidizedIndustry";
		tvote.player.resize(1);
		//strcpy(effect,"y: all do their secondary ablity\n n: no secondary untill next round");
		effect = "Chosen player puts a dock on any of his planet";
	}
	GameEffect * Clone(){
		return new e_p_SubsidizedIndustry(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};