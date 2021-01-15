//Diversified
o_s_Diversified::o_s_Diversified(){
	id = "o_s_Diversified";
	reqs = "I control Mecatol Rex; I have a Space Dock here, and I have at least 2 Technology Advances in each of three (not yellow) different colors";
	reqsShort = "Diversified";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Diversified::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Diversified::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	//PowExv<Planet>* planet = player->GetPlanetsList();
	Planet* planet = 0;
	Army* army = 0;
	Army* fleet = 0;
	bool mecatol = false;
	bool spacedock = false;
	bool techs = false;
	if (Q == eq_ObjCheck){
		//while (planet!=0){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if (strcmp((*piter)->GetName(),MECATOLREX)==0){
				mecatol = true;
				planet = *piter;
				break;
			}
			//planet=planet->next;
		}
		if (mecatol){
			army = FindAllyArmy(player,planet->GetSystem(),planet);
			fleet = FindAllyArmy(player,planet->GetSystem(),0);
			if (army!=0)
				if (army->StackSize(DCK))
					spacedock = true;
			if (fleet!=0)
				if (fleet->StackSize(DCK))
					spacedock = true;
		}
		int red = 0;
		int green = 0;
		int blue = 0;
		for (TechType TT = ttHylar; TT<=ttFleetLogistics; TT=(TechType)((int)TT+1)){
			switch (_GameStats.GetTechDeck()->at(TT)->GetColor()){
				case Red:
					red++;
					break;
				case Green:
					green++;
					break;
				case Blue:
					blue++;
					break;
			}
		}
		if ((red>=TECHS)&&(green>=TECHS)&&(blue>=TECHS))
			techs = true;
		if ((mecatol)&&(spacedock)&&(techs))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Diversified::reset(){
	value = 2;
}
e_Objective* o_s_Diversified::Clone(){
	return new o_s_Diversified(*this);
}
string o_s_Diversified::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Diversified::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Usurper
o_s_Usurper::o_s_Usurper(){
	id = "o_s_Usurper";
	reqs = "I control Mecatol Rex; I have a Space Dock and at least 6 Ground Forces here";
	reqsShort = "Usurper";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Usurper::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Usurper::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	//PowExv<Planet>* planet = player->GetPlanetsList();
	Planet* planet = 0;
	Army* army = 0;
	Army* fleet = 0;
	bool mecatol = false;
	bool spacedock = false;
	bool infantry = false;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if (strcmp((*piter)->GetName(),MECATOLREX)==0){
				mecatol = true;
				planet = *piter;
				break;
			}
			//planet=planet->next;
		}
		if (mecatol){
			army = FindAllyArmy(player,planet->GetSystem(),planet);
			fleet = FindAllyArmy(player,planet->GetSystem(),0);
			if (army!=0){
				if (army->StackSize(DCK))
					spacedock = true;
				if (army->IsUnitWithAbility(uaInfantry)>=GFs)
					infantry = true;
			}
			if (fleet!=0)
				if (fleet->StackSize(DCK))
					spacedock = true;
		}
		if ((mecatol)&&(spacedock)&&(infantry))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Usurper::reset(){
	value = 2;
}
e_Objective* o_s_Usurper::Clone(){
	return new o_s_Usurper(*this);
}
string o_s_Usurper::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Usurper::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Forceful
o_s_Forceful::o_s_Forceful(){
	id = "o_s_Forceful";
	reqs = "I control Mecatol Rex; I have a Space Dock here, and at least 4 Dreadnoughts in the Mecatol Rex system";
	reqsShort = "Forceful";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Forceful::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Forceful::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	//PowExv<Planet>* planet = player->GetPlanetsList();
	Planet* planet = 0;
	Army* army = 0;
	Army* fleet = 0;
	bool mecatol = false;
	bool spacedock = false;
	bool dreadnoughts = false;
	int d = 0;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if (strcmp((*piter)->GetName(),MECATOLREX)==0){
				mecatol = true;
				planet = *piter;
				break;
			}
			//planet=planet->next;
		}
		if (mecatol){
			army = FindAllyArmy(player,planet->GetSystem(),planet);
			fleet = FindAllyArmy(player,planet->GetSystem(),0);
			if (army!=0){
				if (army->StackSize(DCK))
					spacedock = true;
			}
			if (fleet!=0){
				if (fleet->StackSize(DCK))
					spacedock = true;
				if (fleet->StackSize(DR)>=DREADNOUGHTS)
					dreadnoughts = true;
			}
		}
		if ((mecatol)&&(spacedock)&&(dreadnoughts))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Forceful::reset(){
	value = 2;
}
e_Objective* o_s_Forceful::Clone(){
	return new o_s_Forceful(*this);
}
string o_s_Forceful::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Forceful::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Master of Ships
o_s_MasterOfShips::o_s_MasterOfShips(){
	id = "o_s_MasterOfShips";
	reqs = "I control Mecatol Rex; I have a Space Dock here, and at least 8 (non-fighter) ships in the Mecatol Rex system";
	reqsShort = "Master of Ships";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_MasterOfShips::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_MasterOfShips::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	//PowExv<Planet>* planet = player->GetPlanetsList();
	Planet* planet = 0;
	Army* army = 0;
	Army* fleet = 0;
	bool mecatol = false;
	bool spacedock = false;
	bool ships = false;
	int d = 0;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if (strcmp((*piter)->GetName(),MECATOLREX)==0){
				mecatol = true;
				planet = *piter;
				break;
			}
			//planet=planet->next;
		}
		if (mecatol){
			army = FindAllyArmy(player,planet->GetSystem(),planet);
			fleet = FindAllyArmy(player,planet->GetSystem(),0);
			if (army!=0){
				if (army->StackSize(DCK))
					spacedock = true;
			}
			if (fleet!=0){
				if (fleet->StackSize(DCK))
					spacedock = true;
				if (fleet->IsUnitWithAbility(uaCapitalShip)>=SHIPS)
					ships = true;
			}
		}
		if ((mecatol)&&(spacedock)&&(ships))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_MasterOfShips::reset(){
	value = 2;
}
e_Objective* o_s_MasterOfShips::Clone(){
	return new o_s_MasterOfShips(*this);
}
string o_s_MasterOfShips::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_MasterOfShips::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Conqueror
o_s_Conqueror::o_s_Conqueror(){
	id = "o_s_Conqueror";
	reqs = "I control all planets in Home System of another player";
	reqsShort = "Conqueror";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Conqueror::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Conqueror::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	bool conquer = false;
	if (Q == eq_ObjCheck){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			if (_Players[i] != player){
				conquer = true;
				for (int k = 1; k <= MAX_PLANETS; k++){
					if (_Players[i]->GetHS()->GetPlanet(k) != 0)
						if (_Players[i]->GetHS()->GetPlanet(k)->GetOwner() != player)
							conquer = false;
				}
				if (_Players[i]->eHS != 0){
					for (int k = 1; k <= MAX_PLANETS; k++){
						if (_Players[i]->GetExtraHS()->GetPlanet(k) != 0)
							if (_Players[i]->GetExtraHS()->GetPlanet(k)->GetOwner() != player)
								conquer = false;
					}
				}
			}
			if (conquer){
				isFulfill = true;
				break;
			}
		}
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Conqueror::reset(){
	value = 2;
}
e_Objective* o_s_Conqueror::Clone(){
	return new o_s_Conqueror(*this);
}
string o_s_Conqueror::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Conqueror::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Expansionist
o_s_Expansionist::o_s_Expansionist(){
	id = "o_s_Expansionist";
	reqs = "I control 8 systems outside my Home System";
	reqsShort = "Expansionist";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Expansionist::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Expansionist::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int systems = 0;
	if (Q == eq_ObjCheck){
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++)
			if ((*iter != player->GetHS()) && (HexController(*iter) == player))
				systems++;
		if (systems >= SYSTEMS_CONTROL)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Expansionist::reset(){
	value = 2;
}
e_Objective* o_s_Expansionist::Clone(){
	return new o_s_Expansionist(*this);
}
string o_s_Expansionist::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Expansionist::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Focused
o_s_Focused::o_s_Focused(){
	id = "o_s_Focused";
	reqs = "I control at least 4 planets with same technology specailization (not yellow)";
	reqsShort = "Focused";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Focused::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Focused::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int systems = 0;
	vector<int> pl;
	pl.clear();
	pl.resize(tt_MAX);
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator iter = player->GetPlanetsList()->begin(); iter != player->GetPlanetsList()->end(); iter++)
			for (TechTree TT = Red; TT <= Blue; TT = (TechTree)((int)TT+1))
				if ((*iter)->GetBonus(TT) > 0)
					pl[TT] += 1;
		for (TechTree TT = Red; TT <= Blue; TT = (TechTree)((int)TT+1))
			if (pl[TT] >= PLANETS_CONTROL)
				isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Focused::reset(){
	value = 2;
}
e_Objective* o_s_Focused::Clone(){
	return new o_s_Focused(*this);
}
string o_s_Focused::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Focused::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//Industrial
o_s_Industrial::o_s_Industrial(){
	id = "o_s_Industrial";
	reqs = "I control Mecatol Rex; all my 5 Dreadnoughts and 3 Space Docks are on the board";
	reqsShort = "Industrial";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Industrial::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Industrial::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	bool mecatol = false;
	bool spacedock = false;
	bool dreadnoughts = false;
	int d = 0;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if (strcmp((*piter)->GetName(),MECATOLREX)==0){
				mecatol = true;
				break;
			}
		}
		spacedock = (player->CheckUnits().at(DR) >= SPACEDOCKS);
		dreadnoughts = (player->CheckUnits().at(DR) >= DREADNOUGHTS);
		if (mecatol && spacedock && dreadnoughts)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Industrial::reset(){
	value = 2;
}
e_Objective* o_s_Industrial::Clone(){
	return new o_s_Industrial(*this);
}
string o_s_Industrial::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Industrial::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//o_s_Merciless
o_s_Merciless::o_s_Merciless(){
	id = "o_s_Merciless";
	reqs = "I destroyed last Space Dock of another player in this round";
	reqsShort = "Merciless";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Merciless::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Merciless::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_Merciless)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Merciless::reset(){
	value = 2;
}
e_Objective* o_s_Merciless::Clone(){
	return new o_s_Merciless(*this);
}
string o_s_Merciless::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Merciless::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//o_s_Regulator
o_s_Regulator::o_s_Regulator(){
	id = "o_s_Regulator";
	reqs = "I destroyed two Space Dock of two different players in this round";
	reqsShort = "Regulator";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Regulator::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Regulator::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_DestroyedDocks.size() >= 2)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Regulator::reset(){
	value = 2;
}
e_Objective* o_s_Regulator::Clone(){
	return new o_s_Regulator(*this);
}
string o_s_Regulator::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Regulator::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//o_s_Technocrat
o_s_Technocrat::o_s_Technocrat(){
	id = "o_s_Technocrat";
	reqs = "I control at least 6 planets with technology specailization (not yellow)";
	reqsShort = "Focused";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Technocrat::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Technocrat::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int planets = 0;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator iter = player->GetPlanetsList()->begin(); iter != player->GetPlanetsList()->end(); iter++)
			for (TechTree TT = Red; TT <= Blue; TT = (TechTree)((int)TT+1))
				if ((*iter)->GetBonus(TT) > 0)
					planets++;
		if (planets >= PLANETS_CONTROL)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Technocrat::reset(){
	value = 2;
}
e_Objective* o_s_Technocrat::Clone(){
	return new o_s_Technocrat(*this);
}
string o_s_Technocrat::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Technocrat::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//o_s_Threatening
o_s_Threatening::o_s_Threatening(){
	id = "o_s_Threatening";
	reqs = "I control two systems adjacent to Home Systems of two players";
	reqsShort = "Threatening";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_Threatening::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_Threatening::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int systems = 0;
	Hex* HS;
	if (Q == eq_ObjCheck){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			if (_Players[i] != player){
				HS = _Players[i]->GetHS();
				for (int j = 0; j < HS->GetLinkedHexes()->GetLinkNumber(); j++){
					if (HS->GetLinkedHexes()->GetLink(HS->GetLinkedHexes()->GetLinkedHex(j)) == ltBound){
						if (HexController(HS->GetLinkedHexes()->GetLinkedHex(j)) == player){
							systems++;
							break;
						}
					}
				}
			}
		}
		if (systems >= 2)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_Threatening::reset(){
	value = 2;
}
e_Objective* o_s_Threatening::Clone(){
	return new o_s_Threatening(*this);
}
string o_s_Threatening::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_Threatening::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
/*
//o_s_KeeperOfGates
o_s_KeeperOfGates::o_s_KeeperOfGates(){
	id = "o_s_KeeperOfGates";
	reqs = "I have at least one ship in every system containing a wormhole (no D-wormholes and Nexus)";
	reqsShort = "Keeper of Gates";
	value = 2;
	type = vp_secret;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_s_KeeperOfGates::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_s_KeeperOfGates::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int systems = 0;
	Army* army;
	if (Q == eq_ObjCheck){
		isFulfill = true;
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
			if ((*iter)->GetId().compare(NEXUS) == 0)
				continue;
			for (int i = wh_A; i < wh_D; i++){
				if ((*iter)->GotPortal(i)){
					systems++;
					army = FindArmy(*iter,player);
					if (army == 0)
						isFulfill = false;
					else
						if (army->IsUnitWithAbility(uaCapitalShip) == 0)
							isFulfill = false;
				}
			}
		}
		if (systems == 0){
			_Interface.PrintThingPlayer(player->GetNumber()-1,"Keeper of Gate is not legal on this map");
		}		
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_s_KeeperOfGates::reset(){
	value = 2;
}
e_Objective* o_s_KeeperOfGates::Clone(){
	return new o_s_KeeperOfGates(*this);
}
string o_s_KeeperOfGates::Save(){
	int d = 0, f = 0, o = 0;
	if (isDone)
		d = 1;
	if (isFulfill)
		f = 1;
	if (isOpen)
		o = 1;
	std::stringstream ss;
	ss<<d<<" "<<f<<" "<<o;
	return ss.str();
}
void o_s_KeeperOfGates::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}*/