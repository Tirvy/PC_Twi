
class e_p_PlanetarySecurity:public e_Politic{
protected:
	void YayEff(){
		int i;
		Army* army;
		vector<Planet*>::iterator tempiter;
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			for (vector<Planet*>::iterator piter = _Players[i]->GetPlanetsList()->begin(); piter != _Players[i]->GetPlanetsList()->end(); piter++){
				army = FindArmy((*piter)->GetSystem(),_Players[i],false,*piter);
				if (((*piter)->GetSystem() != (*piter)->GetOwner()->GetHS())&&((army == 0)||(army->GetUnitWithAbility(uaLandBattle,1) == 0))){
					if (army!=0){
						army->KillArmy();
						ClearArmies();
					}
					tempiter = piter;
					--piter;
					_Players[i]->DeCapture(*tempiter);
				}
			}
			/*for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++)
				CheckTradeStations(*iter,_Players[i]);*/
		}
		CheckTradeStations();
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
	e_p_PlanetarySecurity(){
		//nt_strload(id,"PlanetarySecurity\0");
		id = "PlanetarySecurity";
		tvote.yesno.resize(1);
		//strcpy(effect,"For: non HS that are not garrisoned with at least 1 GF revert to neutral 	Against: Discard this card. ");
		effect = "For: non HS that are not garrisoned with at least 1 GF revert to neutral 	Against: Discard this card. ";
	}
	GameEffect * Clone(){
		return new e_p_PlanetarySecurity(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
