list<string> SaveDecks(){
	list<string> save;
	vector<e_Objective*> tempdeck;
	save.clear();
	save.push_back(ini_deck);
	save.push_back(ini_objdeck);
	for (vector<e_Objective*>::iterator iter = _GameStats.GetPublicObjectives()->begin(); iter!= _GameStats.GetPublicObjectives()->end(); ++iter)
		save.push_back((*iter)->GetId());
	save.push_back(ini_objdeck_end);
	save.push_back(ini_objopendeck);
	for (vector<e_Objective*>::iterator iter = _GameStats.GetPublicOpenObjectives()->begin(); iter!= _GameStats.GetPublicOpenObjectives()->end(); ++iter)
		save.push_back((*iter)->GetId());
	save.push_back(ini_objopendeck_end);
	save.push_back(ini_prelimdeck);
	for (vector<e_Objective*>::iterator iter = _GameStats.GetPrelimObjectives()->begin(); iter!= _GameStats.GetPrelimObjectives()->end(); ++iter)
		save.push_back((*iter)->GetId());
	save.push_back(ini_prelimdeck_end);
	save.push_back(ini_secretdeck);
	for (vector<e_Objective*>::iterator iter = _GameStats.GetSecretObjectives()->begin(); iter!= _GameStats.GetSecretObjectives()->end(); ++iter)
		save.push_back((*iter)->GetId());
	save.push_back(ini_secretdeck_end);
	save.push_back(ini_politics);
	for (deque<e_Politic*>::iterator iter = _GameStats.GetPoliticDeck()->begin(); iter!= _GameStats.GetPoliticDeck()->end(); ++iter)
		save.push_back((*iter)->GetId());
	save.push_back(ini_politics_end);
	save.push_back(ini_actions);
	for (vector<e_ActionCard*>::iterator iter = _GameStats.GetActionDeck()->begin(); iter!= _GameStats.GetActionDeck()->end(); ++iter)
		save.push_back((*iter)->GetId());
	save.push_back(ini_actions_end);
	save.push_back(ini_deck_end);
	return save;
};

void LoadDecks(list<string>::iterator begin){//ест итератор на <decks>
	list<string>::iterator iter = begin;
	iter++;
	std::istringstream iss(*iter);
	string q;
	iss>>q;
	vector<e_Objective*> sPublic;
	vector<e_Objective*> sPublicOpen;
	vector<e_Objective*> sPrelim;
	vector<e_Objective*> sSecret;
	list<e_Politic*> sPolitics;
	vector<e_ActionCard*> sActions;
	while (q.compare(ini_deck_end)!=0){
		if (q.compare(ini_objdeck)==0){
			Log("LoadDecks : objectives");
			sPublic.clear();
			iter++;
			iss.clear();
			iss.str(*iter);
			iss>>q;
			while (q.compare(ini_objdeck_end)!=0){
				for (vector<e_Objective*>::iterator temp=ObjectiveList.begin(); temp!=ObjectiveList.end(); temp++)
					if ((*temp)->GetId().compare(q)==0)
						sPublic.push_back((*temp)->Clone());
				iter++;
				iss.clear();
				iss.str(*iter);
				iss>>q;
			}
		}
		else if (q.compare(ini_objopendeck)==0){
			Log("LoadDecks : open objectives");
			sPublicOpen.clear();
			iter++;
			iss.clear();
			iss.str(*iter);
			iss>>q;
			while (q.compare(ini_objopendeck_end)!=0){
				for (vector<e_Objective*>::iterator temp=ObjectiveList.begin(); temp!=ObjectiveList.end(); temp++)
					if ((*temp)->GetId().compare(q)==0)
						sPublicOpen.push_back((*temp)->Clone());
				iter++;
				iss.clear();
				iss.str(*iter);
				iss>>q;
			}
		}
		else if (q.compare(ini_prelimdeck)==0){
			Log("LoadDecks : preliminaries");
			sPrelim.clear();
			iter++;
			iss.clear();
			iss.str(*iter);
			iss>>q;
			while (q.compare(ini_prelimdeck_end)!=0){
				for (vector<e_Objective*>::iterator temp=ObjectiveList.begin(); temp!=ObjectiveList.end(); temp++)
					if ((*temp)->GetId().compare(q)==0)
						sPrelim.push_back((*temp)->Clone());
				iter++;
				iss.clear();
				iss.str(*iter);
				iss>>q;
			}
		}
		else if (q.compare(ini_secretdeck)==0){
			Log("LoadDecks : secrets");
			sSecret.clear();
			iter++;
			iss.clear();
			iss.str(*iter);
			iss>>q;
			while (q.compare(ini_secretdeck_end)!=0){
				for (vector<e_Objective*>::iterator temp=ObjectiveList.begin(); temp!=ObjectiveList.end(); temp++)
					if ((*temp)->GetId().compare(q)==0)
						sSecret.push_back((*temp)->Clone());
				iter++;
				iss.clear();
				iss.str(*iter);
				iss>>q;
			}
		}
		else if (q.compare(ini_politics)==0){
			Log("LoadDecks : politics");
			sPolitics.clear();
			iter++;
			iss.clear();
			iss.str(*iter);
			iss>>q;
			while (q.compare(ini_politics_end)!=0){
				for (list<e_Politic*>::iterator temp=PoliticsList.begin(); temp!=PoliticsList.end(); temp++)
					if ((*temp)->GetId().compare(q)==0)
						sPolitics.push_back((e_Politic*)((*temp)->Clone()));
				iter++;
				iss.clear();
				iss.str(*iter);
				iss>>q;
			}
		}
		else if (q.compare(ini_actions)==0){
			Log("LoadDecks : actions");
			sActions.clear();
			iter++;
			iss.clear();
			iss.str(*iter);
			iss>>q;
			while (q.compare(ini_actions_end)!=0){
				for (vector<e_ActionCard*>::iterator temp=ActionCardList.begin(); temp!=ActionCardList.end(); temp++)
					if ((*temp)->GetId().compare(q)==0)
						sActions.push_back((e_ActionCard*)((*temp)->Clone()));
				iter++;
				iss.clear();
				iss.str(*iter);
				iss>>q;
			}
		}
		iter++;
		iss.clear();
		iss.str(*iter);
		iss>>q;
	}
	_GameStats.SetObjectiveDecks(sPublic,sPrelim,sSecret,sPublicOpen);
	_GameStats.InitPoliticDeck(sPolitics);
	_GameStats.SetActionDeck(sActions);
	_GameStats.SetTechDeck(TechList);
};