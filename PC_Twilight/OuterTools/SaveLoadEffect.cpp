int LoadEffect(string str, Player* player){
	std::istringstream iss(str);
	string id;
	iss>>id;
	for (vector<GameEffect*>::iterator temp=CommonEffects.begin(); temp!=CommonEffects.end(); ++temp){
		if ((*temp)->GetId().compare(id)==0){
			player->AddGameEffect((*temp)->Clone())->Load(str);
			return 1;
		}
	}
	for (vector<e_Objective*>::iterator temp=ObjectiveList.begin(); temp!=ObjectiveList.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			//player->AddGameEffect((*temp)->Clone())->Load(str);
			//player->AddGameEffect(player->AddObjective((*temp)->Clone()));
			player->AddGameEffect((*temp)->Clone());
			player->_PlayerGameEffect.back()->Load(str);
			//player->_PlayerObjectives.back()->Load(str);
			return 1;
		}
	}
	for (list<e_Politic*>::iterator temp=PoliticsList.begin(); temp!=PoliticsList.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			player->AddPolitic((e_Politic*)((*temp)->Clone()),true)->Load(str);
			return 1;
		}
	}
	for (vector<e_Tech*>::iterator temp=TechList.begin(); temp!=TechList.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			player->AddGameEffect((*temp)->Clone())->Load(str);
			return 1;
		}
	}
	for (vector<GameEffect*>::iterator temp=RaceEffectList.begin(); temp!=RaceEffectList.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			player->AddGameEffect((*temp)->Clone())->Load(str);
			return 1;
		}
	}
	for (vector<e_StratCard*>::iterator temp=StratCardList.begin(); temp!=StratCardList.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			player->AddGameEffect((*temp)->Clone())->Load(str);
			return 1;
		}
	}
	for (vector<GameEffect*>::iterator temp=Miscellaneous.begin(); temp!=Miscellaneous.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			player->AddGameEffect((*temp)->Clone())->Load(str);
			return 1;
		}
	}
	for (vector<e_ActionCard*>::iterator temp=ActionCardList.begin(); temp!=ActionCardList.end(); temp++){
		if ((*temp)->GetId().compare(id)==0){
			player->AddGameEffect((*temp)->Clone())->Load(str);
			return 1;
		}
	}
	return 0;
}

void LoadEffects(list<string>::iterator begin, Player* player){
	list<string>::iterator iter = begin;
	iter++;
	std::istringstream iss(*iter);
	string str1, str2;
	while ((*iter).compare(ini_eff_end) != 0){
		if (!LoadEffect(*iter,player))
			cout<<"Bad effect to load "<<*iter<<endl;
		iter++;
	}
};

list<string> SaveEffects(Player* player){
	list<string> result;
	//result.clear();
	//string str();
	char buffer[512];
	result.push_back("<effect>\n");
	for (list<GameEffect*>::iterator iter = player->_PlayerGameEffect.begin(); iter!=player->_PlayerGameEffect.end(); iter++){
		sprintf(buffer,"%s %s\n",(*iter)->GetId().c_str(),(*iter)->Save().c_str());
		result.push_back(buffer);
	}
	//for (list<e_Objective*>::iterator iter = player->PlayerObjectives.begin(); iter!=player->PlayerObjectives.end(); iter++)
	//	result.push_back((*iter)->Save());
	for (deque<e_Politic*>::iterator iter = player->_politics.begin(); iter!=player->_politics.end(); iter++){
		sprintf(buffer,"%s %s\n",(*iter)->GetId().c_str(),(*iter)->Save().c_str());
		result.push_back(buffer);
	}
	result.push_back("</effect>\n");
	return result;
};