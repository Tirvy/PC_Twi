//10 ресурсов или 10 вли€ни€
o_1_10ror10i::o_1_10ror10i(){
	id = "o_1_10ror10i";
	reqs = "I now spend 10 resources or 10 influence";
	reqsShort = "10 res or 10 inf";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_10ror10i::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_10ror10i::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int* r;
	int pay_type=0;
	if (Q == eq_ObjCheck)
		isFulfill = true;
	if (Q == eq_Fulfill){
		_GrIn.InitChoise("Choose way to pay",true);
		_GrIn.AddOption(EMPTY_EVENT_IMG,"10 resources");
		_GrIn.AddOption(EMPTY_EVENT_IMG,"10 influence");
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
void o_1_10ror10i::reset(){
	value = 1;
}
e_Objective* o_1_10ror10i::Clone(){
	return new o_1_10ror10i(*this);
}
string o_1_10ror10i::Save(){
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
void o_1_10ror10i::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//5 techs
o_1_5techs::o_1_5techs(){
	id = "o_1_5techs";
	reqs = "I have 5 Technology Advances";
	reqsShort = "5 techs";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_5techs::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_5techs::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int techs = 0;
	if (Q == eq_ObjCheck){
		for (TechType TT=ttHylar; TT<MAX_TECH; TT=(TechType)((int)TT+1)){
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
void o_1_5techs::reset(){
	value = 1;
}
e_Objective* o_1_5techs::Clone(){
	return new o_1_5techs(*this);
}
string o_1_5techs::Save(){
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
void o_1_5techs::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//6 товаров
o_1_6tg::o_1_6tg(){
	id = "o_1_6tg";
	reqs = "I now spend 6 Trade Goods";
	reqsShort = "6 goods";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_6tg::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_6tg::Execute(ExecuteParams EP){
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
void o_1_6tg::reset(){
	value = 1;
}
e_Objective* o_1_6tg::Clone(){
	return new o_1_6tg(*this);
}
string o_1_6tg::Save(){
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
void o_1_6tg::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//5 планет
o_1_5planets::o_1_5planets(){
	id = "o_1_5planets";
	reqs = "I control 5 planets outside my Home System";
	reqsShort = "5 planets";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_5planets::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_5planets::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	//PowExv<Planet>* temp = player->GetPlanetsList();
	int planets = 0;
	if (Q == eq_ObjCheck){
		//while (temp!=0){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++)
			if ((*piter)->GetSystem() != player->GetHS())
				planets++;
			//temp=temp->next;
		//}
		if (planets>=PLANETS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_5planets::reset(){
	value = 1;
}
e_Objective* o_1_5planets::Clone(){
	return new o_1_5planets(*this);
}
string o_1_5planets::Save(){
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
void o_1_5planets::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//3 дока
o_1_3docks::o_1_3docks(){
	id = "o_1_3docks";
	reqs = "All three of my Space Docks are on the board";
	reqsShort = "3 docks";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_3docks::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_3docks::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	//PowVec<Army>* army = _Armies.next;
	int d = 0;
	if (Q == eq_ObjCheck){
		//while (army!=0){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
			if (((*aiter)->GetOwner()==player)&&((*aiter)->StackSize(DCK)))
				d+=(*aiter)->StackSize(DCK);
			//army=army->next;
		//}
		if (d>=DOCKS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_3docks::reset(){
	value = 1;
}
e_Objective* o_1_3docks::Clone(){
	return new o_1_3docks(*this);
}
string o_1_3docks::Save(){
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
void o_1_3docks::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//контролирую ћекатол –екс
o_1_Mecatol::o_1_Mecatol(){
	id = "o_1_Mecatol";
	reqs = "I control Mecatol Rex";
	reqsShort = "Mecatol Rex";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_Mecatol::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_Mecatol::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++){
			if ((*piter)->GetName() == MECATOLREX)
				isFulfill = true;
		}
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_Mecatol::reset(){
	value = 1;
}
e_Objective* o_1_Mecatol::Clone(){
	return new o_1_Mecatol(*this);
}
string o_1_Mecatol::Save(){
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
void o_1_Mecatol::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//блокада дока
o_1_Blockade::o_1_Blockade(){
	id = "o_1_Blockade";
	reqs = "I blockade enemy Space Dock";
	reqsShort = "Blockade";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_Blockade::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_Blockade::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Army* army;
	Army* opponent;
	int i;
	if (Q == eq_ObjCheck){
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
			if (isFulfill)
				break;
			army = FindArmy(*iter,player);
			if (army == 0)
				continue;
			if (!army->IsUnitWithAbility(uaCapitalShip))
				continue;
			for (i = 1; i <= MAX_PLANETS; i++){
				if ((*iter)->GetPlanet(i) != 0){
					opponent = FindArmy(*iter,0,false,(*iter)->GetPlanet(i));
					if (opponent == 0)
						continue;
					if ((opponent->GetOwner() != player) && (opponent->StackSize(DCK))){
						isFulfill = true;
						break;
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
void o_1_Blockade::reset(){
	value = 1;
}
e_Objective* o_1_Blockade::Clone(){
	return new o_1_Blockade(*this);
}
string o_1_Blockade::Save(){
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
void o_1_Blockade::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//успешное вторжение
o_1_Invasion::o_1_Invasion(){
	id = "o_1_Invasion";
	reqs = "I win in one Invasion Combat against enemy army in this round";
	reqsShort = "Invasion";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_Invasion::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_Invasion::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_Invasions >= 1)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_Invasion::reset(){
	value = 1;
}
e_Objective* o_1_Invasion::Clone(){
	return new o_1_Invasion(*this);
}
string o_1_Invasion::Save(){
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
void o_1_Invasion::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//успешный бой
o_1_SpaceVictory::o_1_SpaceVictory(){
	id = "o_1_SpaceVictory";
	reqs = "I win in one Space Battle against at least 3 enemy ships in this round";
	reqsShort = "Space Victory";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_SpaceVictory::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_SpaceVictory::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_SpaceBattles >= 1)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_SpaceVictory::reset(){
	value = 1;
}
e_Objective* o_1_SpaceVictory::Clone(){
	return new o_1_SpaceVictory(*this);
}
string o_1_SpaceVictory::Save(){
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
void o_1_SpaceVictory::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//захват 3 планет
o_1_Take3Planets::o_1_Take3Planets(){
	id = "o_1_Take3Planets";
	reqs = "I capture 3 planets in this round";
	reqsShort = "Take 3 planets";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_Take3Planets::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_Take3Planets::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ObjCheck){
		if (player->GetObjectiveTracker()->_CapturedPlanets.size() >= CAPTURED_PLANETS)
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_Take3Planets::reset(){
	value = 1;
}
e_Objective* o_1_Take3Planets::Clone(){
	return new o_1_Take3Planets(*this);
}
string o_1_Take3Planets::Save(){
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
void o_1_Take3Planets::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//планеты с кредитами всех цветов
o_1_PlanetAllColors::o_1_PlanetAllColors(){
	id = "o_1_PlanetAllColors";
	reqs = "I control planets with red, green and blue Technology credits";
	reqsShort = "Take All Colors";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_PlanetAllColors::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_PlanetAllColors::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> pl;
	pl.clear();
	pl.resize(tt_MAX);
	if (Q == eq_ObjCheck){
		for (vector<Planet*>::iterator iter = player->GetPlanetsList()->begin(); iter != player->GetPlanetsList()->end(); iter++)
			for (TechTree TT = Red; TT <= Blue; TT = (TechTree)((int)TT+1))
				if ((*iter)->GetBonus(TT) > 0)
					pl[TT] += 1;
		if ((pl[Red] > 0) && (pl[Green] > 0) && (pl[Blue] > 0))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_PlanetAllColors::reset(){
	value = 1;
}
e_Objective* o_1_PlanetAllColors::Clone(){
	return new o_1_PlanetAllColors(*this);
}
string o_1_PlanetAllColors::Save(){
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
void o_1_PlanetAllColors::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//техи всех цветов
o_1_Tech4Color::o_1_Tech4Color(){
	id = "o_1_Tech4Color";
	reqs = "I have Technologies in all 4 colors";
	reqsShort = "4 tech colors";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_Tech4Color::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_Tech4Color::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	vector<int> techs;
	techs.clear();
	techs.resize(tt_MAX);
	if (Q == eq_ObjCheck){
		for (int i = 0; i <= ttTransitDiodes; i++)
			if (player->GotTech((TechType)i))
				techs.at(_GameStats.GetTechDeck()->at(i)->GetColor()) += 1;
		if ((techs[Red]>0) && (techs[Green]>0) && (techs[Blue]>0) && (techs[Yellow]>0))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_Tech4Color::reset(){
	value = 1;
}
e_Objective* o_1_Tech4Color::Clone(){
	return new o_1_Tech4Color(*this);
}
string o_1_Tech4Color::Save(){
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
void o_1_Tech4Color::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//техи одного цвета
o_1_TechInColor::o_1_TechInColor(){
	id = "o_1_TechInColor";
	reqs = "I have 3 Technologies in one color";
	reqsShort = "3 tech in color";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_TechInColor::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_TechInColor::Execute(ExecuteParams EP){
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
void o_1_TechInColor::reset(){
	value = 1;
}
e_Objective* o_1_TechInColor::Clone(){
	return new o_1_TechInColor(*this);
}
string o_1_TechInColor::Save(){
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
void o_1_TechInColor::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//10 res
o_1_10res::o_1_10res(){
	id = "o_1_10res";
	reqs = "I now spend 10 resources";
	reqsShort = "10 res";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_10res::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_10res::Execute(ExecuteParams EP){
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
void o_1_10res::reset(){
	value = 1;
}
e_Objective* o_1_10res::Clone(){
	return new o_1_10res(*this);
}
string o_1_10res::Save(){
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
void o_1_10res::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//10 inf
o_1_10inf::o_1_10inf(){
	id = "o_1_10inf";
	reqs = "I now spend 10 influence";
	reqsShort = "10 influence";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_10inf::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_10inf::Execute(ExecuteParams EP){
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
void o_1_10inf::reset(){
	value = 1;
}
e_Objective* o_1_10inf::Clone(){
	return new o_1_10inf(*this);
}
string o_1_10inf::Save(){
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
void o_1_10inf::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}

//3 каунтера
o_1_3CC::o_1_3CC(){
	id = "o_1_3CC";
	reqs = "I now spend 3 Command Counters from Strategy Allocation/Command Pool";
	reqsShort = "3 CC";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_3CC::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_3CC::Execute(ExecuteParams EP){
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
void o_1_3CC::reset(){
	value = 1;
}
e_Objective* o_1_3CC::Clone(){
	return new o_1_3CC(*this);
}
string o_1_3CC::Save(){
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
void o_1_3CC::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}
//o_1_GreatInf
o_1_GreatInf::o_1_GreatInf(){
	id = "o_1_GreatInf";
	reqs = "I have total influence greater than total influence of my left neighboor and greater than total influence of my right neighboor";
	reqsShort = "Greater Influence";
	value = 1;
	type = vp_stage1;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = true;
}
bool o_1_GreatInf::GetQ(GameEffectQs queue){
	if ((queue == eq_ObjCheck)||(queue == eq_Fulfill)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_1_GreatInf::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int p = player->GetNumber()-1;
	int r = (p+1)%_GameStats.GetPlayersNumber();
	int l = (p-1+_GameStats.GetPlayersNumber())%_GameStats.GetPlayersNumber();
	if (Q == eq_ObjCheck){
		if ((_Players[p]->TotalInf() > _Players[r]->TotalInf()) && (_Players[p]->TotalInf() > _Players[l]->TotalInf()))
			isFulfill = true;
	}
	if (Q == eq_Fulfill){
		isDone = true;
		isFulfill = false;
	}
	return er_none;
}
void o_1_GreatInf::reset(){
	value = 1;
}
e_Objective* o_1_GreatInf::Clone(){
	return new o_1_GreatInf(*this);
}
string o_1_GreatInf::Save(){
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
void o_1_GreatInf::Load(std::string str){
	std::istringstream iss(str);
	int d, f, o;
	string q;
	iss>>q>>d>>f>>o;
	isDone = d;
	isFulfill = f;
	isOpen = o;
}