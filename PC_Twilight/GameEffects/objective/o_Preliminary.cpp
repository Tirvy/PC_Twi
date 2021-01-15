//Commander
o_p_Commander::o_p_Commander(){
	id = "o_p_Commander";
	reqs = "All 5 of my Dreadnoughts are on the board";
	reqsShort = "Commander";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Commander::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Commander::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int d = 0;
	if (Q == eq_ObjCheck){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if (((*aiter)->GetOwner()==player)&&((*aiter)->StackSize(DR)))
				d+=(*aiter)->StackSize(DR);
		if (d>=DREADNOUGHTS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Commander::reset(){
	value = 1;
}
e_Objective* o_p_Commander::Clone(){
	return new o_p_Commander(*this);
}
string o_p_Commander::Save(){
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
void o_p_Commander::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Defender
o_p_Defender::o_p_Defender(){
	id = "o_p_Defender";
	reqs = "All 6 of my PDS are on the board";
	reqsShort = "Defender";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Defender::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Defender::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int d = 0;
	if (Q == eq_ObjCheck){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if (((*aiter)->GetOwner()==player)&&((*aiter)->StackSize(PDS)))
				d+=(*aiter)->StackSize(PDS);
		if (d>=PDSs)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Defender::reset(){
	value = 1;
}
e_Objective* o_p_Defender::Clone(){
	return new o_p_Defender(*this);
}
string o_p_Defender::Save(){
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
void o_p_Defender::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Scientist
o_p_Scientist::o_p_Scientist(){
	id = "o_p_Scientist";
	reqs = "I have 3 Yellow Technology Advances";
	reqsShort = "Scientist";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Scientist::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Scientist::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int techs = 0;
	if (Q == eq_ObjCheck){
		for (TechType TT=ttEnviroCompensator; TT<=ttTransitDiodes; TT=(TechType)((int)TT+1)){
			if (player->GotTech(TT))
				techs++;
		}
		if (techs>=TECHS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Scientist::reset(){
	value = 1;
}
e_Objective* o_p_Scientist::Clone(){
	return new o_p_Scientist(*this);
}
string o_p_Scientist::Save(){
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
void o_p_Scientist::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Researcher
o_p_Researcher::o_p_Researcher(){
	id = "o_p_Researcher";
	reqs = "I control 4 or more planets with technology specialties";
	reqsShort = "Researcher";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Researcher::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Researcher::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int planets = 0;
	bool spec = false;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			spec = false;
			for (TechTree color = Red; color<=Yellow; color=(TechTree)((int)color+1))
				if ((*piter)->GetBonus(color))
					spec = true;
			if (spec)
				planets++;
		}
		if (planets>=PLANETS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Researcher::reset(){
	value = 1;
}
e_Objective* o_p_Researcher::Clone(){
	return new o_p_Researcher(*this);
}
string o_p_Researcher::Save(){
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
void o_p_Researcher::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Antagonist
o_p_Antagonist::o_p_Antagonist(){
	id = "o_p_Antagonist";
	reqs = "I control a planet in system adjacent with Home System of another player";
	reqsShort = "Antagonist";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Antagonist::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Antagonist::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int d = 0;
	Hex* HS;
	if (Q == eq_ObjCheck){
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
			if (_Players[i] != player){
				HS = _Players[i]->GetHS();
				for (int j = 0; j < HS->GetLinkedHexes()->GetLinkNumber(); j++){
					if (HS->GetLinkedHexes()->GetLink(HS->GetLinkedHexes()->GetLinkedHex(j)) == ltBound){
						for (int k = 1; k <= MAX_PLANETS; k++){
							if (HS->GetLinkedHexes()->GetLinkedHex(j)->GetPlanet(k) != 0){
								if (HS->GetLinkedHexes()->GetLinkedHex(j)->GetPlanet(k)->GetOwner() == player){
									isFulfill = true;
								}
							}
						}
					}
				}
			}
		}
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Antagonist::reset(){
	value = 1;
}
e_Objective* o_p_Antagonist::Clone(){
	return new o_p_Antagonist(*this);
}
string o_p_Antagonist::Save(){
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
void o_p_Antagonist::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Enemy
o_p_Enemy::o_p_Enemy(){
	id = "o_p_Enemy";
	reqs = "I destroyed 3 enemy ships in this round";
	reqsShort = "Enemy";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Enemy::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Enemy::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Unit* unit = EP.unit;
	Army* army = EP.army1;
	Army* target = EP.army2;
	int isAttacker = EP.attacker;
	char buff[256];
	int ships = 0;
	if (Q == eq_ObjCheck){
		for (int i = DS; i <= FM; i++)
			ships += player->GetObjectiveTracker()->_DestroyedEnemyUnits.at(i);
		if (ships >= DESTROYED_SHIPS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Enemy::reset(){
	value = 1;
}
e_Objective* o_p_Enemy::Clone(){
	return new o_p_Enemy(*this);
}
string o_p_Enemy::Save(){
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
void o_p_Enemy::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Infiltrator
o_p_Infiltrator::o_p_Infiltrator(){
	id = "o_p_Infiltrator";
	reqs = "I destroyed at least one enemy ship in system adjacent to its owner Home System";
	reqsShort = "Infiltrator";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Infiltrator::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Infiltrator::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char buff[256];
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_Infiltrator)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Infiltrator::reset(){
	value = 1;
}
e_Objective* o_p_Infiltrator::Clone(){
	return new o_p_Infiltrator(*this);
}
string o_p_Infiltrator::Save(){
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
void o_p_Infiltrator::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//Explorer
o_p_Explorer::o_p_Explorer(){
	id = "o_p_Explorer";
	reqs = "I control 2 systems adjacent to Mecatol Rex";
	reqsShort = "Explorer";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Explorer::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Explorer::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Hex* mecatol = 0;
	int systems = 0;
	char buff[256];
	if (Q == eq_ObjCheck){
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
			if ((*iter)->GetId().compare(MECATOLSYSTEM) == 0){
				mecatol = *iter;
				break;
			}
		}
		if (mecatol != 0){
			for (int i = 0; i < mecatol->GetLinkedHexes()->GetLinkNumber(); i++)
				if (mecatol->GetLinkedHexes()->GetLink(i) == ltBound)
					if (HexController(mecatol->GetLinkedHexes()->GetLinkedHex(i)) == player)
						systems++;
			if (systems >= CONTROL_HEXES)
				isFulfill = true;
		}
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Explorer::reset(){
	value = 1;
}
e_Objective* o_p_Explorer::Clone(){
	return new o_p_Explorer(*this);
}
string o_p_Explorer::Save(){
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
void o_p_Explorer::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Invader
o_p_Invader::o_p_Invader(){
	id = "o_p_Invader";
	reqs = "I successfully capture planet that was controlled by another player this round";
	reqsShort = "Invader";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Invader::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Invader::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char buff[256];
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_Invaders)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Invader::reset(){
	value = 1;
}
e_Objective* o_p_Invader::Clone(){
	return new o_p_Invader(*this);
}
string o_p_Invader::Save(){
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
void o_p_Invader::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//Traitor
o_p_Traitor::o_p_Traitor(){
	id = "o_p_Traitor";
	reqs = "I have attacked my trade partner in this round";
	reqsShort = "Traitor";
	value = 1;
	type = vp_prelim;
	isDone = false;
	isFulfill = false;
	isSecret = true;
	isOpen = true;
}
bool o_p_Traitor::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_p_Traitor::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	char buff[256];
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_Infiltrator)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_p_Traitor::reset(){
	value = 1;
}
e_Objective* o_p_Traitor::Clone(){
	return new o_p_Traitor(*this);
}
string o_p_Traitor::Save(){
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
void o_p_Traitor::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}