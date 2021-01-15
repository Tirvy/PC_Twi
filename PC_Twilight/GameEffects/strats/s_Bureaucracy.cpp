void e_Bureaucracy::reset(){
	BUREAUCRACY_SECONDARY_COUNTERS_COST = 1;
	UseP = false;
	UseS = false;
}


void e_Bureaucracy::special(int n){
	if (n)
		_Interface.PrintThingAll("Open new public objectives from bonuses of Bureaucracy");
	for (int i = 0; i < n; i++)
		OpenPublicObjective(_GameStats.GetPublicObjectives()->front());
}

void e_Bureaucracy::sc_P(Player *player){
	char str[257];
	Log("e_Bureaucracy::sc_P : start");
	//sprintf(str,"Player %s uses Senatorial Control",player->GetName().c_str());
	sprintf(str,"Player %s uses Bureaucracy (primary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(str);
	//бесплатный каунтер
	player->GiveFreeCounters(BUREAUCRACY_PRIMARY_FREE_COUNTERS);
	//открытие задания
	int* r;
	vector<e_Objective*>* Public = _GameStats.GetPublicObjectives();
	e_Objective* obj1;
	e_Objective* obj2;
	if (Public->size()>=2){
		obj1 = Public->at(0);
		obj2 = Public->at(1);
		_GrIn.InitChoise("Select public objective to open");
		_GrIn.AddOption(OBJ_IMG[obj1->GetType()],obj1->GetShortReqs());
		_GrIn.AddOption(OBJ_IMG[obj2->GetType()],obj2->GetShortReqs());
		vector<int> tempvec = _GrIn.LaunchChoise();
		r = &tempvec[0];
		if (r!=0){
			if (r[0]==1)
				OpenPublicObjective(obj1);
			else
				OpenPublicObjective(obj2);
		}
	}
	else{
		if (Public->size()==1)
			OpenPublicObjective(Public->front());
	}
	//выполнение задания
	//player->ExecuteGameEffect(ExecuteParams(eq_ObjCheck,player));
	CompliteObj(player,true,false);
	Log("e_Bureaucracy::sc_P : end");
}

void e_Bureaucracy::sc_S(Player *player){
	if (!player->TakeCounter(CC_strat,BUREAUCRACY_SECONDARY_COUNTERS_COST)){
		_Interface.PrintThingPlayer(player->GetNumber()-1, "Not enough counters to use secondary of Bureaucracy");
		return;
	}
	char buff[256];
	sprintf(buff,"Player %s uses Bureaucracy (secondary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(buff);
	//sprintf(buff,"Player %s uses New Agendas and receives 1 Political and 1 Action Card",player->GetName().c_str());
	//_Interface.PrintThingAll(buff);
	player->AddPolitic(_GameStats.DrawPolitic());
	player->AddAction(1);
}

e_Bureaucracy::e_Bureaucracy(){
	//nt_strload(id,"Bureaucracy\0");
	id = "Bureaucracy";
	type = Bureaucracy;
	//nt_strload(image,STRAT_B_PATH[type]);
	image = STRAT_B_PATH[type];
	reset();
}

bool e_Bureaucracy::GetQ(GameEffectQs queue){
	if ((queue==eq_AAA) || (queue==eq_SpecialStratCard))
		return true;
	return false;
}

e_StratCard* e_Bureaucracy::Clone(){
	return new e_Bureaucracy(*this);
}

string e_Bureaucracy::Save(){
	return string();
}
void e_Bureaucracy::Load(std::string str){}