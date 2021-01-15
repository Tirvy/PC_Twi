//методы e_Technology

void e_Technology::reset(){
	TECHNOLOGY_PRIMARY_RESOURCE_COST_1 = 0;
	TECHNOLOGY_PRIMARY_RESOURCE_COST_2 = 8;
	TECHNOLOGY_SECONDARY_RESOURCE_COST = 6;
	TECHNOLOGY_SECONDARY_COUNTERS_COST = 1;
	UseP = false;
	UseS = false;
};

void e_Technology::special(int n){
}

void e_Technology::sc_S(Player*player){
	char str[127];
	Log("e_Technology::sc_S : start");
	sprintf(str,"Player %s uses Technology (secondary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(str);
	int cost = TECHNOLOGY_SECONDARY_RESOURCE_COST;
	int CC = TECHNOLOGY_SECONDARY_COUNTERS_COST;
	if (player->GetCountersSA()>=TECHNOLOGY_SECONDARY_COUNTERS_COST)
		//ResearchTechDialog(player,TECHNOLOGY_SECONDARY_RESOURCE_COST,TECHNOLOGY_SECONDARY_COUNTERS_COST);
		player->ExecuteGameEffect(ExecuteParams(eq_ResearchTech,player,&cost,&CC));
	else
		_Interface.PrintThingAll("Not enough command counters");
	Log("e_Technology::sc_S : end");
};

void e_Technology::sc_P(Player*player){
	char str[127];
	int cost = TECHNOLOGY_PRIMARY_RESOURCE_COST_1;
	int CC = 0;
	Log("e_Technology::sc_P : end");
	sprintf(str,"Player %s uses Technology (primary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(str);
	player->ExecuteGameEffect(ExecuteParams(eq_ResearchTech,player,&cost,&CC));
	//ResearchTechDialog(player,TECHNOLOGY_PRIMARY_RESOURCE_COST_1,0);
	sprintf(str,"Player %s can research another technology",player->GetName().c_str());
	_Interface.PrintThingPlayer(player->GetNumber() - 1,str);
	cost = TECHNOLOGY_PRIMARY_RESOURCE_COST_2;
	//ResearchTechDialog(player,TECHNOLOGY_PRIMARY_RESOURCE_COST_2,0);
	player->ExecuteGameEffect(ExecuteParams(eq_ResearchTech,player,&cost,&CC));
	Log("e_Technology::sc_P : end");
};

e_Technology::e_Technology(){
	//nt_strload(id,"Technology\0");
	id = "Technology";
	type = Technology;
	//nt_strload(image,STRAT_B_PATH[type]);
	image = STRAT_B_PATH[type];
	reset();
};

bool e_Technology::GetQ(GameEffectQs queue){
	if (queue==eq_AAA)
		return true;
	return false;
};

e_StratCard* e_Technology::Clone(){
	return new e_Technology(*this);
}
string e_Technology::Save(){
	return string();
}
void e_Technology::Load(std::string str){}