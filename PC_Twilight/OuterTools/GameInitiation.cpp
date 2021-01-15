
#include "SaveLoadArmy.cpp"
#include "SaveLoadMap.cpp"
#include "SaveLoadEffect.cpp"
#include "SaveLoadPlayer.cpp"
#include "SaveLoadDeck.cpp"

#include "SaveLoadTool.cpp"

GameInitSettings InitIniFile(){
	string base, value;
	GameInitSettings InitS;
	int i;
	ostringstream ss;

	ifstream fin(ini_file.c_str());
	if (fin.fail()){
		cout<<ini_file;
		exit(0);
	}
	InitS.SetPlayerNumber(MAX_PLAYERS);
	while (!fin.eof())
	{
		fin >> base;
		fin >> value;
		fin >> value;
		if (base == ini_maptype){
			//_GameStats. = ;
		}
		else if (base == ini_mapfile){
			InitS.MapName = string(PATH_TO_DATA) + value;
			InitS.Mapfile = FileToInt(InitS.MapName,".twm");
			cout<<"{"<<InitS.Mapfile<<"}"<<endl;
			//GetTemplatePlayerNumber(InitS.MapName);
			//InitS.SetPlayerNumber(InitS.PlayersNumber);
		}
		else if (base == ini_galfile){
			InitS.GalName = string(PATH_TO_DATA) + value;
		}
		else if (base == ini_winlVPs){
			istringstream(value) >> InitS.VPs;
		}
		else if (base == ini_players){
			istringstream(value)>>InitS.PlayersNumber;
		}
		else if (base[0] == ini_racetag){
			if (value == ini_random)
				InitS.PlayerRaces[base[1]-'1'] = MAX_RACE;
			else{
				for (i = 0; (i<MAX_RACE)&&(value.compare(RacesFull[i]) != 0); ++i){}
				if (i==MAX_RACE)
					InitS.PlayerRaces[base[1]-'1'] = MAX_RACE;
				else
					InitS.PlayerRaces[base[1]-'1'] = (RacesType)i;
			}
		}
		else if (base[0] == ini_playertag){
			InitS.PlayerNames[base[1]-'1'] = value;
		}
		else if (base == ini_speaker){
			if (value == ini_random)
				InitS.Speaker = InitS.PlayersNumber;
			else
				InitS.Speaker = value[0] - '0';
		}
	}
	InitS.RandSeed = time(NULL);
	cout<<InitS.PlayerNames.size()<<'!';
	fin.close();
	return InitS;
}

int InitLoadGame(GameInitSettings InitS){
	_Interface.SetSettings(&_GameStats);
	_StratShared[0] = new e_Leadership;
	_StratShared[1] = new e_Diplomacy;
	_StratShared[2] = new e_Assembly;
	_StratShared[3] = new e_Production;
	_StratShared[4] = new e_Trade;
	_StratShared[5] = new e_Warfare;
	_StratShared[6] = new e_Technology;
	_StratShared[7] = new e_Bureaucracy;
	for (int i=0; i<_GameStats.GetPlayersNumber(); i++)
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_LaunchEffect,_Players[i]));
	for (int i=0; i<_GameStats.GetPlayersNumber(); i++)
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_LoadGame,_Players[i]));

	for (int i=0;i<InitS.PlayersNumber;++i)
		_Players[i]->_connection = InitS.PlayersCons[i];

	return 1;
}



int InitNewGame(GameInitSettings InitS){
	int i;
	//_MapTranslator.translate(InitS.MapName,&_Map,&_Settings);
	if (InitS.Loadfile != 0)
		LoadReplay("..\\Release\\data\\LastReplay.twr",&InitS);
	_Players = new Player*[InitS.PlayersNumber];
	_GameStats.SetGameStats(InitS);
	_GameStats.VPftw = InitS.VPs;
	_Interface.SetSettings(&_GameStats);
	for (i=0;i<InitS.PlayersNumber;++i){
		_Players[i] = new Player(InitS.PlayerNames[i],i+1);
		_Players[i]->_color = i;
		_Players[i]->SysDeck = 0;
		_Players[i]->_connection = InitS.PlayersCons[i];
		cout<<"Players "<<i<<" connection is "<<_Players[i]->_connection<<endl;
		if (InitS.PlayerRaces[i] != MAX_RACE)
			_Players[i]->_race = (RacesType)InitS.PlayerRaces[i];
		else
			_Players[i]->_race = (RacesType) (rand() % MAX_RACE);
		//_Players[i]->AddAAA(new e_TacticalAction());
		//_Players[i]->AddGameEffect(new e_TacticalAction());
	}
	ZoldnMapTranslator _ZoldnMapTranslator(&_Map);
	_ZoldnMapTranslator.NewGameMapCreation(InitS);
	_GameStats.CurPhase = gpt_strategy;
	return 1;
}

/*int CreateBasicGalaxy(GameInitSettings InitS){
	int i, x, y;
	PowVec<Hex>* sys;
	string str;
	SystemDeck* tempdeck,*specialdeck;
	_Interface.GetSystemsFile(str, HomeSys);
	_SystemTranslator.translate(str,&tempdeck);
	_Interface.GetSystemsFile(str, SpecSys);
	_SystemTranslator.translate(str,&specialdeck);
	_MapGraphics.initmap(_Map.GetMaxRadius());
	_Map.GetSysByRoundh('0', &x, &y);
	sys = specialdeck->Choose(specialdeck->FindById("MecatolRex"));
	_Map.LaySystemh(x,y,sys->elem);
	sys->elem = 0;
	delete sys;
	_Map.GetSysByRoundh('M', &x, &y);
	sys = specialdeck->Choose(specialdeck->FindById("Mallice"));
	_Map.LaySystemh(x,y,sys->elem);
	sys->elem = 0;
	delete sys;
	tempdeck->shuffle();
	for (i=0;i<InitS.PlayersNumber;++i){
		_Map.GetSysByRoundh(i+'a', &x, &y);
		if (_Players[i]->GetRace() != MAX_RACE)
			sys = tempdeck->Copy(tempdeck->FindById(RacesFull[_Players[i]->GetRace()]));
		else
			sys = tempdeck->Copy(0);
		_Map.LaySystemh(x,y,sys->elem);
		_Players[i]->SetHS(sys->elem);
		sys->elem = 0;
		delete sys;
	}
	return 1;
}*/

int DistribSystems(){
	int i, perplayer;
	SystemDeck *totaldeck;
	SystemDeck **playerdeck;
	totaldeck = new SystemDeck();
	AddDeck(totaldeck,RedSys,true);
	AddDeck(totaldeck,EmptySys,true);
	AddDeck(totaldeck,PlanetSys,true);
	totaldeck->shuffle();
	playerdeck = new SystemDeck*[_Settings.num_players()];
	perplayer = totaldeck->GetNumber() / _Settings.num_players();
	/*for (i=0;i<totaldeck->GetNumber();++i){
		//std::cout<<"'"<<(*((*(totaldeck->GetList()))[i].elem)).GetId()<<"'"<<std::endl;
	}*/
	for (i=0;i<_Settings.num_players();++i)
		_Players[i]->SysDeck = new SystemDeck(totaldeck->PopFirst(perplayer));
	delete totaldeck;
	return 1;
}

/*int CreateGalaxy(GameInitSettings InitS){ // fix speaker
	int i = 0, direction = 1, round = 1;
	int n,x,y;
	while (round <= _Map.GetMaxRadius()){
		while (_Interface.PrintPlayerName(_Players[i])!=1){}
		while (_Interface.PrintEmptyCoords(&_Map, round + '0')!=1){}
		while (_Interface.PrintDeckList(_Players[i]->SysDeck->GetList())!=1){}
		while (_Interface.GetNumber(&n,1,_Players[i]->SysDeck->GetNumber())!=1){}
		while (_Interface.GetHex(&x,&y)!=1){}
		if (round+'0' != _Map.GetRoundh(x,y)){
			_Interface.PrintWrongHex(x,y);
			continue;
		}
		if (_Map.GetHexh(x,y) != 0){
			_Interface.PrintWrongHex();
			continue;
		}
		PowVec<Hex>* sys = _Players[i]->SysDeck->Choose(n);
		_Map.LaySystemh(x,y,sys->elem);
		sys->elem = 0;
		delete sys;
		i+=direction;
		if ((i == 0)&&(direction<=0))
			++direction;
		if ((i == _Settings.num_players()-1)&&(direction>=0))
			--direction;
		//if (_Map.GetSysByRoundh(round + '0',&x,&y) == 0)
		//	++round;
	}
	return 1;
}*/

int LoadGalaxy(GameInitSettings InitS){
	string str;
	_Interface.GetGalFile(str);
	GalTranslator().translate(str,&_Map,&_Settings);
	_Interface.PrintThingAll("----- Enter -help for help on commands -----");
	return 1;	
}