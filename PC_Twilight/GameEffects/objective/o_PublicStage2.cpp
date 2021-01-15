//Империум Рекс
o_2_ImperiumRex::o_2_ImperiumRex(){
	id = "o_2_ImperiumRex";
	reqs = "Imperium Rex: Game Over";
	reqsShort = "Imperium Rex";
	value = 0;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_ImperiumRex::GetQ(GameEffectQs queue){
	if ((queue == eq_FinishGame)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_ImperiumRex::Execute(ExecuteParams EP){
	throw endofgame(1);
	return er_none;
}
void o_2_ImperiumRex::reset(){
	value = 0;
}
e_Objective* o_2_ImperiumRex::Clone(){
	return new o_2_ImperiumRex(*this);
}
string o_2_ImperiumRex::Save(){
	return string();
}
void o_2_ImperiumRex::Load(std::string str){}
//20 ресурсов или 20 влияния
o_2_20ror20i::o_2_20ror20i(){
	id = "o_2_20ror20i";
	reqs = "I now spend 20 resources or 20 influence";
	reqsShort = "20 res or 20 inf";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_20ror20i::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_20ror20i::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int* r;
	int pay_type=0;
	if (Q == eq_ObjCheck)
		isFulfill = true;
	if (Q == eq_Fulfill){
		_GrIn.InitChoise("Choose way to pay",true);
		_GrIn.AddOption(EMPTY_EVENT_IMG,"20 resources");
		_GrIn.AddOption(EMPTY_EVENT_IMG,"20 influence");
		vector<int> tempvec = _GrIn.LaunchChoise();
		r = &tempvec[0];
		if (r!=0){
			if (r[0]==1)
				pay_type = 0;
			else
				pay_type = 1;
			if (EP.player->Pay(pay_type,RES_INF_TO_PAY) == frr_normal){//выполнено
				isDone = true;
				isFulfill = false;
			}
		}
	}
	return er_none;
}
void o_2_20ror20i::reset(){
	value = 2;
}
e_Objective* o_2_20ror20i::Clone(){
	return new o_2_20ror20i(*this);
}
string o_2_20ror20i::Save(){
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
void o_2_20ror20i::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//9 techs
o_2_9techs::o_2_9techs(){
	id = "o_2_9techs";
	reqs = "I have 9 Technology Advances";
	reqsShort = "9 techs";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_9techs::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_9techs::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int techs = 0;
	if (Q == eq_ObjCheck){
		for (TechType TT=ttHylar; TT<=MAX_TECH; TT=(TechType)((int)TT+1)){
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
void o_2_9techs::reset(){
	value = 2;
}
e_Objective* o_2_9techs::Clone(){
	return new o_2_9techs(*this);
}
string o_2_9techs::Save(){
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
void o_2_9techs::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//12 товаров

//10 планет
o_2_10planets::o_2_10planets(){
	id = "o_2_10planets";
	reqs = "I control 10 planets outside my Home System";
	reqsShort = "10 planets";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_10planets::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_10planets::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int planets = 0;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if ((*piter)->GetSystem() != player->GetHS())
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
void o_2_10planets::reset(){
	value = 2;
}
e_Objective* o_2_10planets::Clone(){
	return new o_2_10planets(*this);
}
string o_2_10planets::Save(){
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
void o_2_10planets::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//успешное вторжение
o_2_Invasion::o_2_Invasion(){
	id = "o_2_Invasion";
	reqs = "I win in two Invasion Combats against enemy armies in this round";
	reqsShort = "Invasion";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_Invasion::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_Invasion::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_Invasions >= 2)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_Invasion::reset(){
	value = 2;
}
e_Objective* o_2_Invasion::Clone(){
	return new o_2_Invasion(*this);
}
string o_2_Invasion::Save(){
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
void o_2_Invasion::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//успешный бой
o_2_SpaceVictory::o_2_SpaceVictory(){
	id = "o_2_SpaceVictory";
	reqs = "I win in two Space Battles against at least 3 enemy ships in this round";
	reqsShort = "Space Victory";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_SpaceVictory::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_SpaceVictory::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_SpaceBattles >= 2)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_SpaceVictory::reset(){
	value = 2;
}
e_Objective* o_2_SpaceVictory::Clone(){
	return new o_2_SpaceVictory(*this);
}
string o_2_SpaceVictory::Save(){
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
void o_2_SpaceVictory::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//техи одного цвета
o_2_TechInColor::o_2_TechInColor(){
	id = "o_2_TechInColor";
	reqs = "I have 5 Technologies in one color";
	reqsShort = "5 tech in color";
	value = 2;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_TechInColor::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_TechInColor::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> techs;
	techs.clear();
	techs.resize(tt_MAX);
	if (Q == eq_ObjCheck){
		for (int i = 0; i <= ttTransitDiodes; i++)
			if (player->GotTech((TechType)i))
				techs.at(_GameStats.GetTechDeck()->at(i)->GetColor()) += 1;
		if ((techs[Red]>=TECHS) || (techs[Green]>=TECHS) || (techs[Blue]>=TECHS) || (techs[Yellow]>=TECHS))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_TechInColor::reset(){
	value = 2;
}
e_Objective* o_2_TechInColor::Clone(){
	return new o_2_TechInColor(*this);
}
string o_2_TechInColor::Save(){
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
void o_2_TechInColor::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//20 res
o_2_20res::o_2_20res(){
	id = "o_2_20res";
	reqs = "I now spend 20 resources";
	reqsShort = "20 res";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_20res::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_20res::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		isFulfill = true;
	}
	if (Q == eq_Fulfill){
		if (EP.player->Pay(0,RES) == frr_normal){//выполнено
			isDone = true;
			isFulfill = false;
		}
	}
	return er_none;
}
void o_2_20res::reset(){
	value = 2;
}
e_Objective* o_2_20res::Clone(){
	return new o_2_20res(*this);
}
string o_2_20res::Save(){
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
void o_2_20res::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//20 inf
o_2_20inf::o_2_20inf(){
	id = "o_2_20inf";
	reqs = "I now spend 20 influence";
	reqsShort = "20 influence";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_20inf::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_20inf::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		isFulfill = true;
	}
	if (Q == eq_Fulfill){
		if (EP.player->Pay(1,INF) == frr_normal){//выполнено
			isDone = true;
			isFulfill = false;
		}
	}
	return er_none;
}
void o_2_20inf::reset(){
	value = 2;
}
e_Objective* o_2_20inf::Clone(){
	return new o_2_20inf(*this);
}
string o_2_20inf::Save(){
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
void o_2_20inf::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//12 товаров
o_2_12tg::o_2_12tg(){
	id = "o_2_12tg";
	reqs = "I now spend 12 Trade Goods";
	reqsShort = "12 goods";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_12tg::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_12tg::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetGoods()>=TG_TO_PAY)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		if (player->Pay(2,TG_TO_PAY)==frr_normal){
			isDone = true;
			isFulfill = false;
		}
	}
	return er_none;
}
void o_2_12tg::reset(){
	value = 2;
}
e_Objective* o_2_12tg::Clone(){
	return new o_2_12tg(*this);
}
string o_2_12tg::Save(){
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
void o_2_12tg::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//6 каунтеров
o_2_6CC::o_2_6CC(){
	id = "o_2_6CC";
	reqs = "I now spend 6 Command Counters from Strategy Allocation/Command Pool";
	reqsShort = "6 CC";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_6CC::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_6CC::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> ret;
	int tospend;
	char buff[255];
	if (Q == eq_ObjCheck){
		if (player->GetCountersCP() + player->GetCountersSA() >= COMMAND_COUNTERS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		while (true){
			ret.clear();
			tospend = 0;
			sprintf(buff,"Select counters to spend, you have %d/%d/%d",player->GetCountersSA(),player->GetCountersFS(),player->GetCountersCP());
			_GrIn.InitChoise(buff,true,true,true);
			_GrIn.AddOption(COUNTER_POOLS[CC_strat],"Strategy Allocation");
			_GrIn.AddOption(COUNTER_POOLS[CC_comm],"Command Pool");
			ret = _GrIn.LaunchChoise();
			if (ret.size() == 0)
				break;
			tospend = ret[0] + ret[1];
			if (tospend != COMMAND_COUNTERS){
				_Interface.PrintThingPlayer(player->GetNumber()-1,"Wrong number of counters");
				continue;
			}
			if (ret[0] >  player->GetCountersSA()){
				_Interface.PrintThingPlayer(player->GetNumber()-1,"Too much SACC");
				continue;
			}
			if (ret[1] >  player->GetCountersCP()){
				_Interface.PrintThingPlayer(player->GetNumber()-1,"Too much CPCC");
				continue;
			}
			player->TakeCounter(CC_strat,ret[0]);
			player->TakeCounter(CC_comm,ret[1]);
			isDone = true;
			isFulfill = false;
			break;
		}
	}
	return er_none;
}
void o_2_6CC::reset(){
	value = 2;
}
e_Objective* o_2_6CC::Clone(){
	return new o_2_6CC(*this);
}
string o_2_6CC::Save(){
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
void o_2_6CC::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//o_2_mecatol3
o_2_mecatol3::o_2_mecatol3(){
	id = "o_2_mecatol3";
	reqs = "I control Mecatol Rex and 3 systems adjacent to it (no Asteroids or Supernovas)";
	reqsShort = "Mecatol and 3 systems";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_mecatol3::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_mecatol3::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> ret;
	int i,control,adjacent;
	Planet* mecatol;
	Hex* h;
	control = 0;
	adjacent = 0;
	bool controlmecatol = false;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if ((*piter)->GetName() == MECATOLREX){
				mecatol = *piter;
				if (HexController((*piter)->GetSystem()) == player)
					controlmecatol = true;
				break;
			}
		}
		for (i = 0; i < mecatol->GetSystem()->GetLinkedHexes()->GetLinkNumber(); i++){
			if (mecatol->GetSystem()->GetLinkedHexes()->GetLink(i) == ltBound){
				h = mecatol->GetSystem()->GetLinkedHexes()->GetLinkedHex(i);
				if ((h->GetDanger() != Supernova) || (h->GetDanger() != Asteroids)){
					adjacent++;
					if (HexController(h) == player)
						control++;
				}
			}
		}
		if ((control >= min(3,adjacent)) && controlmecatol)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_mecatol3::reset(){
	value = 2;
}
e_Objective* o_2_mecatol3::Clone(){
	return new o_2_mecatol3(*this);
}
string o_2_mecatol3::Save(){
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
void o_2_mecatol3::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//o_2_mecatol6
o_2_mecatol6::o_2_mecatol6(){
	id = "o_2_mecatol6";
	reqs = "I control Mecatol Rex system and all systems adjacent to it (no Asteroids or Supernovas)";
	reqsShort = "Mecatol and 6 systems";
	value = 3;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_mecatol6::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_mecatol6::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> ret;
	int i,control,adjacent;
	char buff[255];
	Planet* mecatol;
	Hex* h;
	control = 0;
	adjacent = 0;
	bool controlmecatol = false;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if ((*piter)->GetName() == MECATOLREX){
				mecatol = *piter;
				if (HexController((*piter)->GetSystem()) == player)
					controlmecatol = true;
				break;
			}
		}
		for (i = 0; i < mecatol->GetSystem()->GetLinkedHexes()->GetLinkNumber(); i++){
			if (mecatol->GetSystem()->GetLinkedHexes()->GetLink(i) == ltBound){
				h = mecatol->GetSystem()->GetLinkedHexes()->GetLinkedHex(i);
				if ((h->GetDanger() != Supernova) || (h->GetDanger() != Asteroids)){
					adjacent++;
					if (HexController(h) == player)
						control++;
				}
			}
		}
		if ((control == adjacent) && controlmecatol)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_mecatol6::reset(){
	value = 3;
}
e_Objective* o_2_mecatol6::Clone(){
	return new o_2_mecatol6(*this);
}
string o_2_mecatol6::Save(){
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
void o_2_mecatol6::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//o_2_GreatInf
o_2_GreatInf::o_2_GreatInf(){
	id = "o_2_GreatInf";
	reqs = "I have total influence greater than total influence of my both neighboors";
	reqsShort = "Greater Influence";
	value = 3;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_GreatInf::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_GreatInf::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int p = player->GetNumber()-1;
	int r = (p+1)%_GameStats.GetPlayersNumber();
	int l = (p-1+_GameStats.GetPlayersNumber())%_GameStats.GetPlayersNumber();
	if (Q == eq_ObjCheck){
		if (_Players[p]->TotalInf() > (_Players[r]->TotalInf() +  _Players[l]->TotalInf()))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_GreatInf::reset(){
	value = 3;
}
e_Objective* o_2_GreatInf::Clone(){
	return new o_2_GreatInf(*this);
}
string o_2_GreatInf::Save(){
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
void o_2_GreatInf::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//o_2_DestroyedDock
o_2_DestroyedDock::o_2_DestroyedDock(){
	id = "o_2_DestroyedDock";
	reqs = "I destroyed enemy dock in this turn";
	reqsShort = "Destroyed Space Dock";
	value = 2;
	type = vp_stage2;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_DestroyedDock::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_DestroyedDock::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_DestroyedEnemyUnits.at(DCK) > 0)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_2_DestroyedDock::reset(){
	value = 2;
}
e_Objective* o_2_DestroyedDock::Clone(){
	return new o_2_DestroyedDock(*this);
}
string o_2_DestroyedDock::Save(){
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
void o_2_DestroyedDock::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//o_2_Supremacy
o_2_Supremacy::o_2_Supremacy(){
	id = "o_2_Supremacy";
	reqs = "I control 18 planets outside my Home System";
	reqsShort = "Supremacy";
	value = 0;
	type = vp_win;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_Supremacy::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_Supremacy::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_DestroyedEnemyUnits.at(DCK) > 0)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
		throw endofgame(1);
	}
	return er_none;
}
void o_2_Supremacy::reset(){
	value = 0;
}
e_Objective* o_2_Supremacy::Clone(){
	return new o_2_Supremacy(*this);
}
string o_2_Supremacy::Save(){
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
void o_2_Supremacy::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//o_2_Domination
o_2_Domination::o_2_Domination(){
	id = "o_2_Domination";
	reqs = "I control all the planets in the Home Systems of two other players";
	reqsShort = "Domination";
	value = 0;
	type = vp_win;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_2_Domination::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_2_Domination::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	bool conquer = false;
	int controls = 0;
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
			if (conquer)
				controls++;
		}
		if (controls >= 2)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
		throw endofgame(1);
	}
	return er_none;
}
void o_2_Domination::reset(){
	value = 0;
}
e_Objective* o_2_Domination::Clone(){
	return new o_2_Domination(*this);
}
string o_2_Domination::Save(){
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
void o_2_Domination::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}