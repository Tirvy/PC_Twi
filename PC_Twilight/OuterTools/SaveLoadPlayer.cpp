list<string> SavePlayer(Player* pl){
	list<string> ret;
	char buff[512];

	sprintf(buff,ini_str_value.c_str(),ini_name.c_str(),pl->GetName().c_str());
	ret.push_back(string(buff));

	sprintf(buff,ini_num_value.c_str(),ini_color.c_str(),pl->GetColor());
	ret.push_back(string(buff));

	sprintf(buff,ini_num_value.c_str(),ini_race.c_str(),pl->GetRace());
	ret.push_back(string(buff));

	sprintf(buff,ini_num_value3.c_str(),ini_ccs.c_str(),pl->GetCountersSA(),pl->GetCountersFS(),pl->GetCountersCP());
	ret.push_back(string(buff));

	sprintf(buff,ini_num_value.c_str(),ini_goods.c_str(),pl->GetGoods());
	ret.push_back(string(buff));

	sprintf(buff,ini_num_value.c_str(),ini_connection.c_str(),pl->GetConnection());
	ret.push_back(string(buff));

	sprintf(buff,ini_num_value.c_str(),ini_initiative.c_str(),pl->GetInitiative());
	ret.push_back(string(buff));

	for (int i = 0; i<MAX_TRADES; ++i){
		sprintf(buff,ini_num_value0.c_str(),ini_trade.c_str());
		sprintf(buff,"%s %d %d \n",buff,pl->_trades[i]->power,pl->_trades[i]->owner->GetNumber()-1);
		ret.push_back(string(buff));
	}

	sprintf(buff,ini_num_value0.c_str(),ini_techs.c_str());
	for (int i = 0; i<MAX_TECH; ++i)
		if (pl->GotTech((TechType)i))
			sprintf(buff,"%s %d",buff,i);
	strcat(buff,"\n");
	ret.push_back(string(buff));
	ret.splice(ret.end(),SaveEffects(pl));
	return ret;
}
enum LoadPlayerStatus {lps_none,lps_trade};
void LoadPlayer(list<string>::iterator begin, list<string>::iterator end, int numb){
	int i=numb;
	int traden = 0;
	int trpower;
	Player* trowner;
	LoadPlayerStatus status = lps_none;
	std::istringstream iss;
	list<string>::iterator temp = begin;
	string elem,eq,vals;
	int valn,valt,valz;
	//for (i=0;(_Players[i] != 0)&&(i<_GameStats.GetPlayersNumber());++i){}
	//cout<<i<<endl;
	//_Players[i] = new Player(0,0,i+1);
	bool skip = false;
	bool done = true;
	while (temp != end){
		//cout<<"LoadPlayer: "<<*temp<<endl;
		iss.clear();
		iss.str(*temp);
		iss>>elem;
		if (elem.compare("</player>") == 0){
			//cout<<"Player load end!"<<endl;
			break;
		}
		if (((*temp)[0] == '<')&&((*temp)[1] == '/')){
		}
		else if ((*temp)[0] == '<'){
			if (elem.compare(ini_eff) == 0){
				LoadEffects(temp,_Players[i]);
				skip = true;
			}
		}
		else{
			if (status == lps_none){
				iss>>eq;
				if (elem.compare(ini_name) == 0){
					iss>>vals;
					nt_strload(_Players[i]->_name,vals.c_str());
				}
				else if (elem.compare(ini_color) == 0){
					iss>>valn;
					_Players[i]->_color = valn;
				}
				else if (elem.compare(ini_race) == 0){
					iss>>valn;
					_Players[i]->_race = (RacesType)valn;
					_Players[i]->_unitstats->SetFlagship(_Players[i]->_race);					//Ernies code
					_Players[i]->banner = string("banners/") + RacesFull[_Players[i]->_race];	//Ernies code
				}
				else if (elem.compare(ini_ccs) == 0){
					iss>>valn>>valt>>valz;
					_Players[i]->_counters[0] = valn;
					_Players[i]->_counters[1] = valt;
					_Players[i]->_counters[2] = valz;
				}
				else if (elem.compare(ini_goods) == 0){
					iss>>valn;
					_Players[i]->_goods = valn;
				}
				else if (elem.compare(ini_connection) == 0){
					iss>>valn;
					_Players[i]->_connection = valn;
				}
				else if (elem.compare(ini_initiative) == 0){
					iss>>valn;
					_Players[i]->SetInitiative(valn);
				}
				else if (elem.compare(ini_techs) == 0){
					iss>>valn;
					_Players[i]->_techs[valn] = true;
					while (!iss.eof()){
						iss>>valn;
						_Players[i]->_techs[valn] = true;
					}
				}
				else if (elem.compare(ini_trade) == 0){
					iss>>valn>>valt;
					_Players[i]->_trades[traden] = new TradeRoute(valn,_Players[valt]);
					traden++;
				}
				//else cout<<"smth wrong "<<elem<<endl;
			}
			else if (status == lps_trade){
				iss>>eq>>valn;
				if (elem.compare(ini_power) == 0)
					trpower = valn;
				else if (elem.compare(ini_owner) == 0)
					trowner = _Players[valn];
				//else cout<<"smth wrong "<<elem<<endl;
			}
		}
		++temp;
	}
}
