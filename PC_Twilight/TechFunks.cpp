bool CanGetTech(Player* player, TechType c){//ДЕРЕВО!
	bool result = false;
	if ((_GameStats.GetTechDeck()->at(c)->GetRace() == MAX_RACE)||(_GameStats.GetTechDeck()->at(c)->GetRace() == player->GetRace()))
		if ((_GameStats.GetTechDeck()->at(c)->HavePrereqs(player)))//||(player->GotTech(ttInheritanceSystems))
			result = true;
	int TechOpen = 1;
	player->ExecuteGameEffect(ExecuteParams(eq_TechnologyAvailable,player,c,&TechOpen));
	if (!TechOpen)
		result = false;
	return result;
};

void AddTechGameEffect(Player* player, TechType c){
	Log("AddTechGameEffect : begin");
	player->AddGameEffect(_GameStats.GetTechDeck()->at(c)->Clone());
	player->ExecuteGameEffect(ExecuteParams(eq_LaunchEffect, player));
	Log("AddTechGameEffect : end");
};

//формирует массив цен для передачи в выбор
int* ArrayTechResearch(Player* player, int basecost = 0, bool free = false){
	Log("ArrayTechResearch : begin");
	int* result = new int[MAX_TECH];
	int bonus = 0;
	for (TechType TT=ttHylar; TT<MAX_TECH; TT=(TechType)((int)TT+1))
		if (player->GotTech(TT))
			result[TT]=-1;
		else
			if (CanGetTech(player,TT)){
				if ((free) && (_GameStats.GetTechDeck()->at(TT)->GetColor() != RaceTech))
					result[TT]=0;
				else{
					bonus=0;
					player->ExecuteGameEffect(ExecuteParams(eq_TechnologyBuy,player,TT,&bonus));
					if (basecost+bonus+_GameStats.GetTechDeck()->at(TT)->GetCost()<0)
						result[TT]=0;
					else
						result[TT]=basecost+bonus+_GameStats.GetTechDeck()->at(TT)->GetCost();
				}
			}
			else
				result[TT]=-1;
	Log("ArrayTechResearch : end");
	return result;
}

int* ArrayTechCopy(Player* from, Player* to, bool racial){
	int* result = new int[MAX_TECH];
	for (TechType TT=ttHylar; TT<MAX_TECH; TT=(TechType)((int)TT+1)){
		if (to->GotTech(TT))
			result[TT]=-1;
		else
			if (TT<=ttTransitDiodes){
				if (from->GotTech(TT)){
					result[TT]=0;
				}
			}
			else{
				if ((racial)&&(from->GotTech(TT))){
					result[TT]=0;
				}
				else
					result[TT]=-1;
			}
	}
	return result;
}

int ResearchTechDialog(Player* player, int base, int SACCneed){
	Log("ResearchTechDialog : begin");
	char str[127];
	TechType TechToGet;
	int price;
	int* r=0;
	bool free = false;
	if (base == FREE_TECH_COST)
		free = true;
	int research = 0;
	bool selecting = true;
	if (SACCneed<=player->GetCountersSA()){
		Log("ResearchTechDialog : go to select tech");
		r = ArrayTechResearch(player, base, free);
		while (selecting){
			TechToGet = SelectDialogTech("Select tech to research",player,r);
			if (TechToGet != MAX_TECH){
				price = r[TechToGet];
				if ((price==0)||(free)){
					Log("ResearchTechDialog : obtain free tech");
					sprintf(str,"Player %s has received technology %s",player->GetName().c_str(),_GameStats.GetTechDeck()->at(TechToGet)->GetName().c_str());//TechFull[TechToGet]
					_Interface.PrintThingAll(str);
					if (SACCneed>0)
						player->TakeCounter(CC_strat,SACCneed);
					player->GiveTech(TechToGet);
					AddTechGameEffect(player,TechToGet);
					selecting = false;
					research = 1;
				}
				else{
					Log("ResearchTechDialog : go to payment for tech");
					if (player->Pay(0,price)==frr_normal){
						sprintf(str,"Player %s has received technology %s",player->GetName().c_str(),_GameStats.GetTechDeck()->at(TechToGet)->GetName().c_str());//TechFull[TechToGet]
						_Interface.PrintThingAll(str);
						if (SACCneed>0)
							player->TakeCounter(CC_strat,SACCneed);
						player->GiveTech(TechToGet);
						AddTechGameEffect(player,TechToGet);
						selecting = false;
						research = 1;
					}
				}
			}
			else
				selecting = false;
		}
	}
	else
		Log("ResearchTechDialog : not enough SACC");
	Log("ResearchTechDialog : end");
	return research;
};