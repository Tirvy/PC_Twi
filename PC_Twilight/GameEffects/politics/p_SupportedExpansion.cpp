
class e_p_SupportedExpansion:public e_Politic{
protected:
	void YayEff(){
		int i,k,plan;
		vector<int> sys;
		for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
			i = k % _GameStats.GetPlayersNumber();
			_Interface.SetCurrPlayer(i);
			while(true){
				sys = _GrIn.SysChoise("Choose system to put GF",true);
				if (sys.size() == 0)
					break;
				plan = SelectDialogPlanetInSystem(_Map.GetHexh(sys[0],sys[1]),_Players[i],false);
				if (plan <= 0)
					continue;
				if (_Map.GetHexh(sys[0],sys[1])->GetPlanet(plan)->GetOwner() == 0){
					_Interface.PrintThingAll("planet captured");
					_Players[i]->Capture(_Map.GetHexh(sys[0],sys[1])->GetPlanet(plan));
					FindArmy(_Map.GetHexh(sys[0],sys[1]),_Players[i],true,_Map.GetHexh(sys[0],sys[1])->GetPlanet(plan))->AddUnit(GF);
					break;
				}
				else{
					_Interface.PrintThingPlayer(i,"cant capture enemy planet");
				}
			}
		}
	}
	void NayEff(){
		int i;
		//PowExv<Planet>* plans;
		Army* army;
		vector<Planet*>::iterator tempiter;
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			//plans = _Players[i]->GetPlanetsList();
			//while (plans!=0){
			for (vector<Planet*>::iterator piter = _Players[i]->GetPlanetsList()->begin(); piter != _Players[i]->GetPlanetsList()->end(); piter++){
				army = FindArmy((*piter)->GetSystem(),_Players[i],false,*piter);
				if (((*piter)->GetSystem() != (*piter)->GetOwner()->GetHS())&&(army == 0)){
					tempiter = piter;
					--piter;
					_Players[i]->DeCapture(*tempiter);
				}
				//plans = plans->next;
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
	e_p_SupportedExpansion(){
		//nt_strload(id,"PlanetarySecurity\0");
		id = "SupportedExpansion";
		tvote.yesno.resize(1);
		//strcpy(effect,"For: non HS that are not garrisoned with at least 1 GF revert to neutral 	Against: Discard this card. ");
		effect = "For: all players may place 1 free GF on any neutral planet 	Against: non HS that are not garrisoned with at least 1 unit revert to neutral ";
	}
	GameEffect * Clone(){
		return new e_p_SupportedExpansion(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
