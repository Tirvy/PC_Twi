class e_p_ArmsReduction:public e_Politic{
protected:
	void YayEff(){
		int DRtoKill = 0;
		int CStoKill = 0;
		int DRs;
		int CSs;
		int i,j;
		char buff[255];
		vector<int> ret;
		vector<UnitArmy> options;
		UnitArmy UA;
		_Interface.PrintThingAll("All players destroy thier Dreadnoughts excess number of 2 and all his Cruisers excess number of 4");
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
			DRtoKill = 0;
			CStoKill = 0;
			DRs = _Players[i]->CheckUnits().at(DR);
			CSs = _Players[i]->CheckUnits().at(CS);
			if (DRs > 2)
				DRtoKill = DRs - 2;
			if (CSs > 4)
				CStoKill = CSs - 4;
			while (DRtoKill || CStoKill){
				ret.clear();
				options.clear();
				sprintf(buff,"You have to destroy %d Dreadnought(s) and %d Cruiser(s)",DRtoKill,CStoKill);
				_GrIn.InitChoise(buff,false,true,true);
				for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
					if ((*aiter)->GetOwner() == _Players[i]){
						if (DRtoKill && ((*aiter)->StackSize(DR))){
							for (j = 1; j <= (*aiter)->StackSize(DR); j++){
								sprintf(buff,"%s (%s)",_Info.UnitInfo((*aiter)->GetUnit(DR,j),*aiter).c_str(),(*aiter)->GetHex()->GetId().c_str());
								_GrIn.AddOption(SHIPS_IMG[DR],buff);
								UA.army = *aiter;
								UA.unit = (*aiter)->GetUnit(DR,j);
								UA.selected = 0;
								options.push_back(UA);
							}
						}
						if (CStoKill && ((*aiter)->StackSize(CS))){
							for (j = 1; j <= (*aiter)->StackSize(CS); j++){
								sprintf(buff,"%s (%s)",_Info.UnitInfo((*aiter)->GetUnit(CS,j),*aiter).c_str(),(*aiter)->GetHex()->GetId().c_str());
								_GrIn.AddOption(SHIPS_IMG[CS],buff);
								UA.army = *aiter;
								UA.unit = (*aiter)->GetUnit(CS,j);
								UA.selected = 0;
								options.push_back(UA);
							}
						}
					}
				}
				ret = _GrIn.LaunchChoise();
				if (ret.size() > 0){
					DRs = 0;
					CSs = 0;
					for (j = 0; j < ret.size(); j++){
						if (ret.at(j) > 0){
							if (options.at(j).unit->Class == DR)
								DRs++;
							if (options.at(j).unit->Class == CS)
								CSs++;
						}
					}
					if (DRs < DRtoKill){
						_Interface.PrintThingPlayer(i,"You have selected not enough Dreadnoughts");
						continue;
					}
					if (DRs > DRtoKill){
						_Interface.PrintThingPlayer(i,"You have selected too much Dreadnoughts");
						continue;
					}
					if (CSs < CStoKill){
						_Interface.PrintThingPlayer(i,"You have selected not enough Cruisers");
						continue;
					}
					if (CSs > CStoKill){
						_Interface.PrintThingPlayer(i,"You have selected too much Cruisers");
						continue;
					}
					for (j = 0; j < ret.size(); j++)
						if (ret.at(j) > 0)
							options.at(j).army->KillUnit(options.at(j).unit);
				}
				sprintf(buff,"Player %s has destroyed %d Dreadnought(s) and %d Cruiser(s)",_Players[i]->GetName().c_str(),DRtoKill,CStoKill);
				_Interface.PrintThingAll(buff);
				break;
			}
		}
	}
	void NayEff(){
		int k;
		char buff[255];
		_Interface.PrintThingAll("All players exhaust thier planets with red tech bonus");
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			k = 0;
			for (vector<Planet*>::iterator piter = _Players[i]->GetPlanetsList()->begin(); piter != _Players[i]->GetPlanetsList()->end(); piter++){
				if (((*piter)->GetBonus(Red)) && (!(*piter)->HasState(psExhausted))){
					(*piter)->AddState(psExhausted);
					k++;
				}
			}
			sprintf(buff,"Player %s exhaust %d planet(s)",_Players[i]->GetName().c_str(),k);
			_Interface.PrintThingAll(buff);
		}
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_ArmsReduction(){
		id = "ArmsReduction";
		tvote.yesno.resize(1);
		effect = "YAY: each player have to destroy all his Dreadnoughts excess number of 2 and all his Cruisers excess number of 4; NAY: players have to exhaust thier planets with red tech bonus";
	}
	GameEffect * Clone(){
		return new e_p_ArmsReduction(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};