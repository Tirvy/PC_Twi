string GetAutoSaveName(){
	char buff[1024];
	char str[256];
	sprintf(buff,"%s",autosave_path.c_str());
	for (int i = 0; i < _GameStats.GetPlayersNumber(); i++){
		sprintf(str,"%s_",_Players[i]->GetName().c_str());
		strcat(buff,str);
	}
	sprintf(str,"round_%d_",_GameStats.CurRound);
	strcat(buff,str);
	switch (_GameStats.CurPhase){
		case gpt_action:
			sprintf(str,"turn_%d",_GameStats.CurTurn);
			break;
		case gpt_strategy:
			sprintf(str,"strat");
			break;
		case gpt_status:
			sprintf(str,"status");
			break;
	}
	strcat(buff,str);
	strcat(buff,".tws");
	return string(buff);
}

class SaveTranslator{
public:
	void MakeSave(const string filename){
		char buff[256];
		char strz[256];
		int i;
		list<string> towrite;
		list<string>::iterator temp;
		ofstream myfile (filename.c_str());
		if (!myfile.is_open()){
			cout << "Unable to open file" << endl;
			return;
		}
		/*
		sprintf(buff,ini_num_value,,);
		myfile << buff;
		*/
		sprintf(buff,ini_num_value.c_str(),ini_winlVPs.c_str(),_GameStats.VPftw);
		myfile << buff;
		sprintf(buff,ini_num_value.c_str(),ini_speaker.c_str(),_GameStats.Speaker);
		myfile << buff;
		sprintf(buff,ini_num_value.c_str(),ini_phase.c_str(),_GameStats.CurPhase);
		myfile << buff;
		sprintf(buff,ini_num_value.c_str(),ini_round.c_str(),_GameStats.CurRound);
		myfile << buff;
		sprintf(buff,ini_num_value.c_str(),ini_turn.c_str(),_GameStats.CurTurn);
		myfile << buff;
		sprintf(buff,ini_num_value.c_str(),ini_players.c_str(),_GameStats.GetPlayersNumber());
		myfile << buff;
		sprintf(buff,ini_num_value.c_str(),ini_active.c_str(),_GameStats.ActivePlayer);
		myfile << buff;
		sprintf(buff,ini_num_value0.c_str(),ini_strat.c_str());
		for (i = 0; i < MAX_STRAT; i++){
			sprintf(strz,"%d ",StratCardList[i]->GetBonus());
			strcat(buff,strz);
		}
		strcat(buff,"\n");
		myfile << buff;
		//Zoldn save player status
		sprintf(buff,ini_num_value0.c_str(),ini_status.c_str());
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			sprintf(strz,"%d ",_GameStats.playerstatus[i]);
			strcat(buff,strz);
		}
		strcat(buff,"\n");
		myfile << buff;
		
		//<Zoldn> save objectives and politics
		list<string> decks = SaveDecks();
		for (list<string>::iterator iter = decks.begin(); iter!= decks.end(); ++iter){
			sprintf(buff,"%s\n",iter->c_str());
			myfile << buff;
		}
		//</Zoldn>
		for (i=0;i<_GameStats.GetPlayersNumber();++i){	
			sprintf(buff,ini_tag.c_str(),ini_player.c_str());
			myfile << buff;
			
			towrite = SavePlayer(_Players[i]);
			
			temp = towrite.begin();
			while (temp!= towrite.end()){
				myfile << *temp;
				++temp;
			}

			sprintf(buff,ini_ctag.c_str(),ini_player.c_str());
			myfile << buff;
		}

		towrite = SaveMap();
		temp = towrite.begin();
		while (temp!= towrite.end()){
			myfile << *temp;
			++temp;
		}

		towrite = SaveArmies();
		temp = towrite.begin();
		while (temp!= towrite.end()){
			myfile << *temp << endl;
			++temp;
		}

		cout<<"Save success to "<<filename<<endl;
		myfile.close();
	}

	void LoadSave(const string filename){
		int numb = 0;
		string buff;
		list<string> strs;
		int stek=0;
		string elem,vals,eq;
		int valn;
		std::istringstream iss;
		ifstream myfile (filename.c_str());
		if (!myfile.is_open()){
			cout << "Unable to open file" << endl;
			return;
		}
		while ( getline (myfile,buff) ){
			//cout << buff << '\n';
			//cout<<"SaveLoadTool: "<<buff<<endl;
			if (stek > 0){
				if ((buff[0] == '<')&&(buff[1] == '/'))
					--stek;
				else if (buff[0] == '<')
					++stek;
				strs.push_back(buff);
				if (stek == 0){
					if (buff.compare(2,ini_army.size(),ini_army) == 0)
						LoadArmy(strs.begin(),strs.end());//{}//
					else if (buff.compare(2,ini_map.size(),ini_map) == 0)
						LoadMap(strs.begin(),strs.end());
					else if (buff.compare(2,ini_player.size(),ini_player) == 0){
						LoadPlayer(strs.begin(),strs.end(),numb);
						numb++;
					}
					else if (buff.compare(2,ini_decks.size(),ini_decks) == 0){
						LoadDecks(strs.begin());//Zoldn's save of decks
					}
					else cout<<"ALL IS SOOOOO WRONG!!!\n"<<*(--strs.end());
					strs.clear();
				}
			}
			else{
				if (buff[0] == '<'){
					strs.push_back(buff);
					++stek;
				}
				else{
					iss.clear();
					iss.str(buff);
					iss>>elem>>eq>>valn;
					if (elem.compare(ini_winlVPs) == 0)
						_GameStats.VPftw = valn;
					else if (elem.compare(ini_phase) == 0){
						_GameStats.CurPhase = (GamePhaseType)valn;
						cout<<"Phase load "<<GamePhases[_GameStats.CurPhase]<<endl;
					}
					else if (elem.compare(ini_strat) == 0){
						_GameStats.SetStrategies(StratCardList);
						_GameStats.GetStrategies()->at(0)->SetBonus(valn);
						for (int i = 1; i < MAX_STRAT; i++){
							iss >> valn;
							_GameStats.GetStrategies()->at(i)->SetBonus(valn);
						}
					}
					else if (elem.compare(ini_round) == 0)
						_GameStats.CurRound = valn;
					else if (elem.compare(ini_turn) == 0)
						_GameStats.CurTurn = valn;
					else if (elem.compare(ini_speaker) == 0)
						_GameStats.Speaker = valn;
					else if (elem.compare(ini_players) == 0){
						_GameStats._playersnum = valn;
						_Players = new Player*[_GameStats._playersnum];
						for (;valn>0;--valn)
							//_Players[valn-1] = 0;
							_Players[valn-1] = new Player("my_names_dave",valn);
						//_GameStats.SetGameStats(_GameStats._playersnum,&_Armies,&_Interface,&_PoliticsDeck);//Zoldn, иначе бажит на загрузке армий
					}
					else if (elem.compare(ini_active) == 0)
						_GameStats.ActivePlayer = valn;
					else if (elem.compare(ini_status) == 0){
						_GameStats.playerstatus = new int[_GameStats._playersnum];
						_GameStats.playerstatus[0] = valn;
						for (int i=1; i<_GameStats._playersnum; i++){
							iss>>valn;
							_GameStats.playerstatus[i] = valn;
						}
					}
					else cout<<"ALL IS SO SO WRONG!!!\n"<<buff;
				}
			}
		}
		//_GameStats.SetStrategies(StratCardList);//найти место для инициализации
		myfile.close();
	}
};