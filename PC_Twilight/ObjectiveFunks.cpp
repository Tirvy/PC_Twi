vector<e_Objective*> FormPublicObjectiveDeck(int stage1, int stage2, bool EndOfGame){
	vector<e_Objective*> st1;
	vector<e_Objective*> st2;
	vector<e_Objective*> temp;
	vector<e_Objective*> deck;// = new vector<e_Objective*>;
	deck.clear();
	//список заданий первого этапа
	st1.push_back(new o_1_10ror10i());
	st1.push_back(new o_1_5techs());
	st1.push_back(new o_1_6tg());
	st1.push_back(new o_1_5planets());
	st1.push_back(new o_1_3docks());
	st1.push_back(new o_1_Mecatol());
	st1.push_back(new o_1_Blockade());
	st1.push_back(new o_1_Invasion());
	st1.push_back(new o_1_SpaceVictory());
	st1.push_back(new o_1_Take3Planets());
	st1.push_back(new o_1_PlanetAllColors());
	st1.push_back(new o_1_Tech4Color());
	st1.push_back(new o_1_TechInColor());
	st1.push_back(new o_1_10res());
	st1.push_back(new o_1_10inf());
	st1.push_back(new o_1_3CC());
	st1.push_back(new o_1_GreatInf());
	sync_shuffle(st1);
	//список заданий второго этапа
	st2.push_back(new o_2_20ror20i());
	st2.push_back(new o_2_12tg());
	st2.push_back(new o_2_20res());
	st2.push_back(new o_2_20inf());
	st2.push_back(new o_2_6CC());
	st2.push_back(new o_2_9techs());
	st2.push_back(new o_2_10planets());
	st2.push_back(new o_2_Invasion());
	st2.push_back(new o_2_SpaceVictory());
	st2.push_back(new o_2_TechInColor());
	st2.push_back(new o_2_mecatol3());
	st2.push_back(new o_2_mecatol6());
	st2.push_back(new o_2_GreatInf());
	st2.push_back(new o_2_DestroyedDock());
	st2.push_back(new o_2_Supremacy());
	st2.push_back(new o_2_Domination());	
	sync_shuffle(st2);
	//сборка колоды заданий
	int k=0;
	vector<e_Objective*>::iterator iter = st1.begin();
	while ((k<stage1)&&(k<st1.size())){
		deck.push_back(st1[k]);
		k++;
	}
	k=0;
	while ((k<stage2)&&(k<st2.size())){
		temp.push_back(st2[k]);
		k++;
	}
	if (EndOfGame){
		temp.push_back(new o_2_ImperiumRex());
		sync_shuffle(temp);
	}
	k=0;
	while (k<temp.size()){
		deck.push_back(temp[k]);
		k++;
	}
	return deck;
};

vector<e_Objective*> FormPreliminaryObjectiveDeck(){
	vector<e_Objective*> deck;
	deck.clear();
	deck.push_back(new o_p_Antagonist());
	deck.push_back(new o_p_Defender());
	deck.push_back(new o_p_Commander());
	deck.push_back(new o_p_Scientist());
	deck.push_back(new o_p_Researcher());
	deck.push_back(new o_p_Enemy());
	deck.push_back(new o_p_Infiltrator());
	deck.push_back(new o_p_Explorer());
	deck.push_back(new o_p_Invader());
	deck.push_back(new o_p_Traitor());
	sync_shuffle(deck);
	return deck;
};

vector<e_Objective*> FormSecretObjectiveDeck(){
	vector<e_Objective*> deck;
	deck.clear();
	deck.push_back(new o_s_MasterOfShips());
	deck.push_back(new o_s_Forceful());
	deck.push_back(new o_s_Usurper());
	deck.push_back(new o_s_Diversified());
	deck.push_back(new o_s_Conqueror());
	deck.push_back(new o_s_Expansionist());
	deck.push_back(new o_s_Threatening());
	deck.push_back(new o_s_Technocrat());
	deck.push_back(new o_s_Merciless());
	deck.push_back(new o_s_Industrial());
	deck.push_back(new o_s_Focused());
	deck.push_back(new o_s_Regulator());
	sync_shuffle(deck);
	return deck;
};

int GiveSecretObjective(Player* player, int lvl){
	if ((lvl<0)||(lvl>2))
		return 0;
	char str[257];
	vector<e_Objective*>* deck;
	if (lvl==1)
		deck = _GameStats.GetPrelimObjectives();
	else
		deck = _GameStats.GetSecretObjectives();
	e_Objective* obj;
	if (deck->size()>0){
		obj = deck->front()->Clone();
		//player->AddGameEffect(player->AddObjective(deck->front()->Clone()));
		player->AddGameEffect(deck->front()->Clone());
		//player->AddGameEffect(obj);
		//player->AddObjective(obj);
		//player->AddObjective(deck->front()->Clone());
		_Interface.SetCurrPlayer(player->GetId()-1);
		if (lvl==1)
			sprintf(str,"New preliminary objective: %s - %s (%d VP)",obj->GetShortReqs().c_str(),obj->GetReqs().c_str(),obj->value);
		else
			sprintf(str,"New secret objective: %s - %s (%d VP)",obj->GetShortReqs().c_str(),obj->GetReqs().c_str(),obj->value);
		_Interface.PrintThingPlayer(player->GetNumber()-1,str);
		deck->erase(deck->begin());
	}
	return 1;
}

int OpenPublicObjective(e_Objective* obj){
	char str[257];
	vector<e_Objective*>* Public = _GameStats.GetPublicObjectives();
	vector<e_Objective*>* PublicOpen = _GameStats.GetPublicOpenObjectives();
	vector<e_Objective*>::iterator iter;
	e_Objective* tempObj;
	for (iter = Public->begin(); iter != Public->end(); ++iter)
		if ((*iter)->GetShortReqs().compare(obj->GetShortReqs()) == 0)
			break;
	if (iter != Public->end()){
		PublicOpen->push_back(obj);
		sprintf(str,"New public objective: '%s' (%d VP)",obj->GetReqs().c_str(),obj->value);
		_Interface.PrintThingAll(str);
		for (int i=0;i<_GameStats.GetPlayersNumber();++i){
			tempObj = obj->Clone();
			_Players[i]->AddGameEffect(tempObj);
			//_Players[i]->AddObjective(tempObj);
			//_Players[i]->AddGameEffect(_Players[i]->AddObjective(tempObj));
			_Players[i]->ExecuteGameEffect(ExecuteParams(eq_FinishGame,_Players[i]));
		}
		Public->erase(iter);
	}
	return 1;
}

void CompliteObj(Player* player, bool publ, bool secr){
	e_Objective* obj = 0;
	char str[127];
	bool p = publ;
	bool s = secr;
	int* fs = new int;
	int* t = 0;
	*fs = 1;
	_Interface.SetCurrPlayer(player->GetNumber()-1);
	player->RefreshObjectives();
	player->ExecuteGameEffect(ExecuteParams(eq_ObjCheck,player));
	player->ExecuteGameEffect(ExecuteParams(eq_ObjCanQualify,player,fs,t));
	if (fs)
		while (p || s){
			obj = SelectDialogObjective("Select objective to fulfill",player,p,s);
			if (obj!=0){
				if (SelectDialogYesNo(obj->GetReqs().c_str())){
					obj->Execute(ExecuteParams(eq_Fulfill,player));
					if (obj->isDone){
						sprintf(str,"Player %s has fulfilled objective '%s' and receive %d VP",player->GetName().c_str(),obj->GetReqs().c_str(),obj->value);
						_Interface.PrintThingAll(str);
						player->ExecuteGameEffect(ExecuteParams(eq_FinishGame,player));
						if (obj->GetType() == vp_prelim)//выдача секретки
							GiveSecretObjective(player,2);
						if (obj->isSecret)
							s = false;
						else
							p = false;
					}
				}
			}
			else
				break;
		}
	delete fs;
}