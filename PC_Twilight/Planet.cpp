
Planet::Planet(){
	_Special = st_ZERO;
	_id = "";
	_location = 0;
	_owner = 0;
	_rtech=0;
	_btech=0;
	_gtech=0;
	_ytech=0;
	_effects.clear();
}
string Planet::GetName(){
	return _id;
}
Hex* Planet::GetSystem(){
	return _location;
}
int Planet::SetOwner(Player* s_owner){
	_owner = s_owner;
	return 1;
}
Player* Planet::GetOwner(){
	return _owner;
}
int Planet::GetRes(){
	return _rescap;
}
int Planet::GetInf(){
	return _infcap;
}
int Planet::GetBonus(TechTree Color){
	switch(Color){
		case Red:	return _rtech;
		case Green:	return _gtech;
		case Blue:	return _btech;
		case Yellow:return _ytech;
		default: throw throwable("Planet::GetBonus - Strange GetBonus param",(int)Color+10);
	}
}
SpecialsType Planet::GetSpecial(){
	return _Special;
}

void Planet::AddState(PlanetState PS){
	if (!HasState(PS))
		_effects.push_back(PS);
}

bool Planet::HasState(PlanetState PS){
	for (list<PlanetState>::iterator iter = _effects.begin(); iter != _effects.end(); iter++)
		if (*iter == PS)
			return true;
	return false;
}

void Planet::DeleteState(PlanetState PS){
	for (list<PlanetState>::iterator iter = _effects.begin(); iter != _effects.end(); iter++)
		if (*iter == PS){
			_effects.erase(iter);
			break;
		}
}

void Planet::SetRes(int res){
	_rescap = res;
}

void Planet::SetInf(int inf){
	_infcap = inf;
}

void Planet::SetHex(Hex *hex){
	_location = hex;
}