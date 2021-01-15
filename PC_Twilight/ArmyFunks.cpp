
void ClearArmies(){
	vector<Army*>::iterator aiter = _Armies.begin();
	while (aiter != _Armies.end()){
		if ((*aiter)->GetUnits()->size() == 0){
			_Armies.erase(aiter);
			aiter = _Armies.begin();//да, снова та неоптимальная лажа
		}
		else
			aiter++;
	}
}

Army* FindArmy(int a, int b, Player*owner, bool CreateNew, Planet * planet){
	vector<Army*>::iterator aiter = _Armies.begin();
	Army* army = 0;
	while (aiter != _Armies.end()){
		if (((*aiter)->GetHex() == _Map.GetHexh(a,b))&&((*aiter)->GetPlanet() == planet)){
			if (((*aiter)->GetOwner() == owner) || (owner == 0)){
				army = *aiter;
				break;
			}
		}
		aiter++;
	}
	if ((army == 0) && CreateNew){
		army = new Army(owner,_Map.GetHexh(a,b),planet);
		_Armies.push_back(army);
	}
	return army;
}

Army* FindArmy(Hex*hex, Player*owner, bool CreateNew, Planet * planet){
	vector<Army*>::iterator aiter = _Armies.begin();
	Army* army = 0;
	while (aiter != _Armies.end()){
		if (((*aiter)->GetHex() == hex)&&((*aiter)->GetPlanet() == planet)){
			if (((*aiter)->GetOwner() == owner) || (owner == 0)){
				army = *aiter;
				break;
			}
		}
		aiter++;
	}
	if ((army == 0) && CreateNew){
		army = new Army(owner,hex,planet);
		_Armies.push_back(army);
	}
	return army;
}

Army* FindAnyArmy(Hex* hex, Planet* planet){
	Army* army = 0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetHex() == hex) && ((*aiter)->GetPlanet() == planet)){
			army = *aiter;
			break;
		}
	}
	return army;
}