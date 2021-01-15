list<string> SaveHex(Hex* hex){
	list<string> ret;
	char buff[512];
	char str[127];
	int i,j,pl;
	ret.clear();
	sprintf(buff,ini_tag.c_str(),ini_hex.c_str());
	ret.push_back(buff);
	sprintf(buff,"%s %s %d %d\n",ini_hex_construct.c_str(),hex->GetId().c_str(),hex->xc,hex->yc);
	ret.push_back(string(buff));
	sprintf(buff,ini_counters.c_str());
	for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
		if (hex->GotCC(i+1))
			strcat(buff," 1");
		else
			strcat(buff," 0");
	}
	strcat(buff,"\n");
	ret.push_back(string(buff));
	for (i = 1; i<=MAX_PLANETS; i++){
		if (hex->GetPlanet(i) != 0){
			if (hex->GetPlanet(i)->GetOwner() == 0)
				pl = 0;
			else
				pl = hex->GetPlanet(i)->GetOwner()->GetNumber();
			sprintf(buff,"%s %d",ini_planet.c_str(),pl);
			for (j = 0; j < psMax; j++){
				if (hex->GetPlanet(i)->HasState((PlanetState)j)){
					sprintf(str," %d",j);
					strcat(buff,str);
				}
			}
			strcat(buff,"\n");
			ret.push_back(string(buff));
		}
	}
	for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
		if (_Players[i]->GetHS() == hex){
			sprintf(buff,"%s %d\n",ini_HomeSystem.c_str(),i);
			ret.push_back(string(buff));
		}
		if (_Players[i]->GetExtraHS() == hex){
			sprintf(buff,"%s %d\n",ini_ExtraHomeSystem.c_str(),i);
			ret.push_back(string(buff));
		}
	}
	sprintf(buff,ini_ctag.c_str(),ini_hex.c_str());
	ret.push_back(buff);
	return ret;
}

list<string> SaveMap(){
	list<string> ret;
	char buff[512];
	//int x,y,i;
	//bool k;
	sprintf(buff,ini_tag.c_str(),ini_map.c_str());
	ret.push_back(buff);
	sprintf(buff,"%s %d\n",ini_hex_number.c_str(),_Map.GetHexList()->size());
	ret.push_back(string(buff));
	for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++)
		ret.splice(ret.end(),SaveHex(*hiter));
	sprintf(buff,ini_ctag.c_str(),ini_map.c_str());
	ret.push_back(buff);
	//sprintf(buff,ini_tag.c_str(),ini_map.c_str());
	

	//sprintf(buff,ini_num_value.c_str(),ini_diam.c_str(),2*_Map.GetMaxRadius()+1);
	//ret.push_back(string(buff));
	
	/*sprintf(buff,ini_tag.c_str(),ini_rounds.c_str());
	ret.push_back(string(buff));

	for (y = -_Map.GetMaxRadius(); y<=_Map.GetMaxRadius(); ++y){
		sprintf(buff,"");
		for (x = -_Map.GetMaxRadius(); x<=_Map.GetMaxRadius(); ++x){
			sprintf(buff,"%s %c",buff,_Map.GetRoundh(x,y));
		}
		strcat(buff,"\n");
		ret.push_back(string(buff));
	}

	sprintf(buff,ini_ctag.c_str(),ini_rounds.c_str());
	ret.push_back(string(buff));


	sprintf(buff,ini_tag.c_str(),ini_systems.c_str());
	ret.push_back(string(buff));

	for (y = -_Map.GetMaxRadius(); y<=_Map.GetMaxRadius(); ++y){
		sprintf(buff,"");
		for (x = -_Map.GetMaxRadius(); x<=_Map.GetMaxRadius(); ++x)
			if (_Map.GetRoundh(x,y)!='-'){
				if (_Map.GetHexh(x,y) == 0)
					sprintf(buff,"%s $$",buff);
				else
					sprintf(buff,"%s $%s",buff,_Map.GetHexh(x,y)->GetId().c_str());
			}
		strcat(buff,"\n");
		ret.push_back(string(buff));
	}

	sprintf(buff,ini_ctag.c_str(),ini_systems.c_str());
	ret.push_back(string(buff));


	sprintf(buff,ini_tag.c_str(),ini_actived.c_str());
	ret.push_back(string(buff));

	for (y = -_Map.GetMaxRadius(); y<=_Map.GetMaxRadius(); ++y){
		sprintf(buff,"");
		for (x = -_Map.GetMaxRadius(); x<=_Map.GetMaxRadius(); ++x){
			k = false;
			strcat(buff," ");
			for (i = 0;i<_GameStats.GetPlayersNumber();++i){
				if ((_Map.GetHexh(x,y) != 0)&&(_Map.GetHexh(x,y)->GotCC(i))){
					k = true;
					sprintf(buff,"%s%d",buff,i);
				}
			}
			if (!k)
				strcat(buff,"-");
		}
		strcat(buff,"\n");
		ret.push_back(string(buff));
	}

	sprintf(buff,ini_ctag.c_str(),ini_actived.c_str());
	ret.push_back(string(buff));
	//Zoldn's save of planets' states
	sprintf(buff,ini_tag.c_str(),ini_owned.c_str());
	ret.push_back(string(buff));
	int pl, j;
	char str[63];
	for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
		(*iter)->GetCoords(&x,&y);
		for (i = 1; i<=MAX_PLANETS; i++){
			if ((*iter)->GetPlanet(i) != 0){
				if ((*iter)->GetPlanet(i)->GetOwner() == 0)
					pl = 0;
				else
					pl = (*iter)->GetPlanet(i)->GetOwner()->GetNumber();
				sprintf(buff,"%d %d %d %d ",x,y,i,pl);
				for (j = 0; j < psMax; j++){
					if ((*iter)->GetPlanet(i)->HasState((PlanetState)j)){
						sprintf(str,"%d ",j);
						strcat(buff,str);
					}
				}
				strcat(buff,"\n");
				ret.push_back(string(buff));
			}
		}
	}
	for (y = -_Map.GetMaxRadius(); y<=_Map.GetMaxRadius(); ++y){
		sprintf(buff,"");
		for (x = -_Map.GetMaxRadius(); x<=_Map.GetMaxRadius(); ++x){
			k = false;
			strcat(buff," ");
			for (i = 1;i<=MAX_PLANETS;++i){
				if ((_Map.GetHexh(x,y)!=0)&&(_Map.GetHexh(x,y)->GetPlanet(i) != 0)&&(_Map.GetHexh(x,y)->GetPlanet(i)->GetOwner()!=0)){
					k = true;
					sprintf(buff,"%s%d",buff,_Map.GetHexh(x,y)->GetPlanet(i)->GetOwner()->GetNumber());
				}
			}
			if (!k)
				strcat(buff,"-");
		}
		strcat(buff,"\n");
		ret.push_back(string(buff));
	}

	sprintf(buff,ini_ctag.c_str(),ini_owned.c_str());
	ret.push_back(string(buff));


	sprintf(buff,ini_ctag.c_str(),ini_map.c_str());
	ret.push_back(string(buff));*/

	return ret;
}

int LoadHex(list<string>::iterator begin){
	list<string>::iterator temp = begin;
	std::istringstream iss;
	string elem1, elem2;
	ZoldnMapTranslator _ZoldnMapTranslator(&_Map);
	_ZoldnMapTranslator.InitHexDecks();
	Hex* curHex;
	int planet = 1;
	int d1, d2, i;
	while (true){
		iss.clear();
		iss.str(*temp);
		iss >> elem1;
		if (elem1.compare("<hex>") == 0){}
		if (elem1.compare("</hex>") == 0)
			break;
		if (elem1.compare(ini_hex_construct) == 0){
			iss >> elem2 >> d1 >> d2;
			curHex = _ZoldnMapTranslator.FindHexByID(elem2);
			if (curHex == 0)
				cout<<"LoadHex : Failed to load hex "<<elem2<<endl;
			else
				_Map.LaySystemh(d1,d2,curHex);
		}
		if (elem1.compare(ini_counters) == 0){
			for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
				iss >> d1;
				if (d1)
					curHex->SetCC(i+1);
			}
		}
		if (elem1.compare(ini_planet) == 0){
			iss >> d1;
			if (d1){
				//_Players[d1-1]->Capture(curHex->GetPlanet(planet));
				curHex->GetPlanet(planet)->SetOwner(_Players[d1-1]);
				_Players[d1-1]->GetPlanetsList()->push_back(curHex->GetPlanet(planet));
				_MapGraphics.PutSpecial(FLAG,_Players[d1-1],curHex->xc,curHex->yc,planet-1);
			}
			while (!iss.eof()){
				iss >> d2;
				curHex->GetPlanet(planet)->AddState((PlanetState)d2);
			}
			planet++;
		}
		if (elem1.compare(ini_HomeSystem) == 0){
			iss >> d1;
			_Players[d1]->HS = curHex;
		}
		if (elem1.compare(ini_ExtraHomeSystem) == 0){
			iss >> d1;
			_Players[d1]->eHS = curHex;
		}
		temp++;
	}
	return 1;
}

enum LoadMapStatus {lms_none, lms_rounds, lms_systems, lms_actived, lms_owned};

void LoadMap(list<string>::iterator begin, list<string>::iterator end){
	list<string>::iterator temp = begin;
	std::istringstream iss;
	string elem1;
	int number;
	while (temp != end){
		iss.clear();
		iss.str(*temp);
		iss >> elem1;
		if (elem1.compare("<map>") == 0){}
		if (elem1.compare("</map>") == 0)
			break;
		if (elem1.compare(ini_hex_number) == 0){
			iss >> number;
			_MapGraphics.initmap(number);
			cout<<"Init _MapGraphics "<<number<<endl;
		}
		if (elem1.compare("<hex>") == 0)
			LoadHex(temp);
		temp++;
	}
	_Map.CreateHexLinks();//определяет соседей каждого гекса
	/*int i,j;
	int z1, z2, z3, z4;
	int curline;
	LoadMapStatus status = lms_none;
	std::istringstream iss;
	list<string>::iterator temp = begin;
	GalTranslator gtrans;
	string elem,eq,vals;
	int valn,valt;
	for (i=0;_Players[i] == 0;++i){}
	while (temp != end){
		iss.clear();
		iss.str(*temp);
		cout<<"Map load: "<<*temp<<endl;
		if ((temp->size()>2)&&((*temp)[0] == '<')&&((*temp)[1] == '/')){
			if (status == lms_none)
				cout<<"no status"<<(*temp);
			else status = lms_none;
		}
		else if ((temp->size()>1)&&((*temp)[0] == '<')){
			//curline = -_Map.GetMaxRadius();
			curline = 0;//Zoldn temporary
			if (status != lms_none)
				cout<<"got over status status"<<(*temp);
			else if (temp->compare(1,(ini_rounds.size()),ini_rounds) == 0)
				status = lms_rounds;
			else if (temp->compare(1,(ini_systems.size()),ini_systems) == 0)
				status = lms_systems;
			else if (temp->compare(1,(ini_actived.size()),ini_actived) == 0)
				status = lms_actived;
			else if (temp->compare(1,(ini_owned.size()),ini_owned) == 0)
				status = lms_owned;
			else if (temp->compare(1,(ini_map.size()),ini_map) == 0)
				{}
			else cout<<"wrong tag"<<*temp;
		}
		else{
			if (status == lms_none){
				iss>>elem>>eq;
				if (elem.compare(ini_diam) == 0){
					iss>>valn;
					_Map.Initialize(0,valn);
					//_MapGraphics.initmap(_Map.GetMaxRadius());//Zoldn заменить
				}
				else cout<<"smth wrong "<<elem<<endl;
			}
			else if (status == lms_rounds){
				i = -_Map.GetMaxRadius();
				while (!iss.eof()){
					iss>>vals;
					//_Map.SetRoundh(i,curline,vals[0]);
					//cout<<curline<<'?'<<i<<'?'<<vals[0]<<endl;
					++i;
				}
				++curline;
			}
			else if (status == lms_systems){
				i=0;
				while (!iss.eof()){
					vals.clear();
					iss>>vals;
					if (vals.size()>1){
						gtrans.translate(vals.c_str(),curline,i);
						++i;
					}
				}
				++curline;
			}
			else if (status == lms_actived){
				i = -_Map.GetMaxRadius();
				while (!iss.eof()){
					iss>>vals;
					if (vals[0] != '-')
						for(j=0;j<vals.size();++j)
							_Map.GetHexh(i,curline)->SetCC(vals[j]-'0');
					++i;
				}
				++curline;
			}
			else if (status == lms_owned){//Zoldn's load planets' states
				iss>>z1>>z2>>z3>>z4;
				if (z4 != 0){
					_Players[z4-1]->AddPlanet(_Map.GetHexh(z1,z2)->GetPlanet(z3));
				}
				while (!iss.eof()){
					iss>>valn;
					_Map.GetHexh(z1,z2)->GetPlanet(z3)->AddState((PlanetState)valn);
				}
				++curline;
			}
			else if (status == lms_owned){
				i = -_Map.GetMaxRadius();
				while (!iss.eof()){
					iss>>vals;
					for(j=0;j<vals.size();++j)
						if (vals[j]!='-')
							_Players[vals[j]-'1']->Capture(_Map.GetHexh(i,curline)->GetPlanet(j+1));
					++i;
				}
				++curline;
			}
		}
		++temp;
	}*/
}