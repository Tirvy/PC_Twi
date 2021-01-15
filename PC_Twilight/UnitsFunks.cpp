int CarriableNumber(UnitType ut){
	switch (ut){
		case GF: return 1;
		case PDS: return 2;
		case FG: return 3;
		case ST: return 4;
		default: return 0;
	}
}

bool IsCarriable(UnitType ut){
	return ut<DS;
}

int StackSize(UnitType UT, Player*owner,Hex*hex,Planet*planet = 0){
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetHex() == hex)&&((*aiter)->GetPlanet() == planet)){
			if ((*aiter)->GetOwner() == owner)
				return (*aiter)->StackSize(UT);
			return -1;
		}
	}
	if (planet->GetOwner() == owner)
		return 0;
	return -1;
}

bool SystemStackSize(UnitType UT, Player*owner,Hex*hex){
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if (((*aiter)->GetHex() == hex)&&((*aiter)->GetOwner() == owner))
			return true;
	return false;
}
