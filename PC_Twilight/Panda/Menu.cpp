#include "Menu.h"

void MenuArea::DrawMain(const Event *ev, void *data){
	_MenuArea.status = mmt_main;
	FunctionList* FL;
	FL = new FunctionList;

	_MenuArea.BackPic = _Window->load_model(_Window->get_aspect_2d(),"data/menu/bg/MainMenuBack.png");
	_MenuArea.BackPic.set_scale(0.2);
	_MenuArea.BackPic.set_pos(0.0,	0.0,	0.0);

	//SND_GAME_START->set_volume(0.2); Музыка рабоотает, но пока не нужна
	//SND_MAIN_MENU->set_volume(0.2);
	//SND_MAIN_MENU->play();

	FL->setHead("Welcome to TWI_PC!");
#ifndef NO_HOST
	FL->addFunction(DrawNewGame,	"Start New Game");
	FL->addFunction(DrawQuickGame,	"Quick Start Game");
	FL->addFunction(DrawLoadGame,	"Load Game");
#endif
	FL->addFunction(DrawConToGame,	"Connect to Game");
	FL->addFunction(DrawExitGame,	"Exit");
	FL->draw();
}
void MenuArea::DrawNewGame(const Event *ev, void *data){
#ifndef NO_HOST
	int i,j;
	_MenuArea.InitS = InitIniFile();
	GameInitSettings *InitS = &(_MenuArea.InitS);

	_NeCo.InitServer();
	if (_MenuArea.PlayerNames.size() < InitS->PlayersNumber){
		i = _MenuArea.PlayerNames.size();

		_MenuArea.PlayerNames.resize(InitS->PlayersNumber);
		_MenuArea.PlayerRaces.resize(InitS->PlayersNumber);
		_MenuArea.PlayerStatus.resize(InitS->PlayersNumber);
		_MenuArea.InitS.PlayersCons.resize(InitS->PlayersNumber);
		_MenuArea.InitS.PlayerColors.resize(InitS->PlayersNumber);

		for (; i<InitS->PlayersNumber; ++i){
			_MenuArea.InitS.PlayersCons[i] = -1;

			_MenuArea.PlayerNames[i].SetName("Name:");
			_MenuArea.PlayerNames[i].SetString(InitS->PlayerNames[i]);
			_MenuArea.PlayerNames[i].SetPos(-1.7,0.6 - 0.25*i,0.05);
			_MenuArea.PlayerNames[i].Draw();

			_MenuArea.PlayerRaces[i].SetPos(-1.5,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerRaces[i].AddDecr("Race:");
			_MenuArea.PlayerRaces[i].SetWatched((int*)&(InitS->PlayerRaces[i]));
			for (j = 0;j<MAX_RACE;++j)
				_MenuArea.PlayerRaces[i].AddOption(RacesFull[j]);
			_MenuArea.PlayerRaces[i].AddOption("Random");
			_MenuArea.PlayerRaces[i].Draw(mlt_dropdown);
			//_MenuArea.PlayerRaces[_MenuArea.PlayerRaces.size()].se

			/*_MenuArea.PlayerRaces[i].SetPos(-1.0,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerRaces[i].AddDecr("Color:");
			_MenuArea.PlayerRaces[i].SetWatched((int*)&(InitS->PlayerColors[i]));
			for (j = 0;j<MAX_RACE;++j)
				_MenuArea.PlayerRaces[i].AddOption(RacesFull[j]);
			_MenuArea.PlayerRaces[i].Draw(mlt_dropdown);*/
			
			_MenuArea.PlayerStatus[i].SetPos(-0.8,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerStatus[i].AddOption("Local (->net)");
			_MenuArea.PlayerStatus[i].AddOption("Net (->local)");
			_MenuArea.PlayerStatus[i].Draw(mlt_switch);
		}
	}


	_MenuArea.Map.FillofFiles(".twm");
	_MenuArea.Map.AddDecr("Map:");
	_MenuArea.Map.SetPos(-1.7, 0.8, 0.05);
	_MenuArea.Map.SetWatched(&(InitS->Mapfile));
	_MenuArea.Map.Draw(mlt_dropdown);

	PT(PGButton) accept = MakeButton("Accept de Map","");
	_Framework.define_key(accept->get_click_event(MouseButton::one() ), "accept", &ReloadTemplate, 0);
	_MenuArea.ReloadButton = _Window->get_aspect_2d().attach_new_node(accept);
	_MenuArea.ReloadButton.set_pos(-1.7,0,0.75);
	_MenuArea.ReloadButton.set_scale(0.05);
	
	_MenuArea.Speaker = MenuList();
	_MenuArea.Speaker.FillofNumbers(_MenuArea.InitS.PlayersNumber);
	_MenuArea.Speaker.AddOption("random");
	_MenuArea.Speaker.SetWatched(&InitS->Speaker);
	_MenuArea.Speaker.AddDecr("Speaker:");
	_MenuArea.Speaker.SetPos(1.0, 0.8, 0.05);
	_MenuArea.Speaker.Draw(mlt_dropdown);

	_MenuArea.VPs = MenuList();
	_MenuArea.VPs.FillofNumbers(14);
	_MenuArea.VPs.SetWatched(&InitS->VPs);
	_MenuArea.VPs.AddDecr("VPs ftw:");
	_MenuArea.VPs.SetPos(1.0, 0.7, 0.05);
	_MenuArea.VPs.Draw(mlt_dropdown);

	_MenuArea.Load.AddOption("None");
	_MenuArea.Load.FillofFiles(".twr");
	_MenuArea.Load.AddDecr("Replay:");
	_MenuArea.Load.SetPos(1.0, 0.4, 0.05);
	_MenuArea.Load.SetWatched(&InitS->Loadfile);
	_MenuArea.Load.Draw(mlt_dropdown);

	MenuList *launch = new MenuList();
	launch->SetPos(1.0,-0.9,0.05);
	launch->AddOption("LAUNCH",&StartGameHost,(void*)InitS);
	launch->Draw(mlt_choise);
	_NeCo.Accept(&DrawConnected);
#endif
}
void MenuArea::ReloadTemplate(const Event *ev, void *data){
	int i,j;
	GameInitSettings *InitS = &(_MenuArea.InitS);
	InitS->MapName = IntToFile(InitS->Mapfile,".twm");
	InitS->PlayersNumber = GetTemplatePlayerNumber(InitS->MapName);

	if (_MenuArea.PlayerNames.size() < InitS->PlayersNumber){
		i = _MenuArea.PlayerNames.size();

		for (; i<InitS->PlayersNumber; ++i){
			_MenuArea.PlayerNames.push_back(InputString());
			_MenuArea.PlayerRaces.push_back(MenuList());
			_MenuArea.PlayerStatus.push_back(MenuList());
			_MenuArea.InitS.PlayersCons.push_back(-1);

			_MenuArea.PlayerNames[i].SetName("Name:");
			_MenuArea.PlayerNames[i].SetString(InitS->PlayerNames[i]);
			_MenuArea.PlayerNames[i].SetPos(-1.7,0.6 - 0.25*i,0.05);
			_MenuArea.PlayerNames[i].Draw();

			_MenuArea.PlayerRaces[i].SetPos(-1.5,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerRaces[i].AddDecr("Race:");
			_MenuArea.PlayerRaces[i].SetWatched((int*)&(InitS->PlayerRaces[i]));
			for (j = 0;j<MAX_RACE;++j)
				_MenuArea.PlayerRaces[i].AddOption(RacesFull[j]);
			_MenuArea.PlayerRaces[i].AddOption("Random");
			_MenuArea.PlayerRaces[i].Draw(mlt_dropdown);
			
			_MenuArea.PlayerStatus[i].SetPos(-0.8,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerStatus[i].AddOption("Local (->net)");
			_MenuArea.PlayerStatus[i].AddOption("Net (->local)");
			_MenuArea.PlayerStatus[i].Draw(mlt_switch);
		}
	}
}
void MenuArea::DrawConnected(const Event *ev, void *data){
	int i;
	NetDatagram* ndata = (NetDatagram *) data;
	for (i = 0; i< _MenuArea.InitS.PlayersNumber;++i){
		if ((_MenuArea.PlayerStatus[i].GetWatched() == 1)&&(_MenuArea.InitS.PlayersCons[i] == -1)){
			_MenuArea.PlayerNames[i].SetString(ndata->get_message());
			_MenuArea.PlayerNames[i].Deactivate();
			_MenuArea.InitS.PlayersCons[i] = _NeCo.GetConNum(ndata->get_connection());
			cout<<"Player "<<_MenuArea.PlayerNames[i].GetAsString()<<" got connetion number "<<_MenuArea.InitS.PlayersCons[i]<<endl;
			break;
		}
	}
	if (i == _MenuArea.InitS.PlayersNumber){
		cout<<"For some reason player wasnt connected"<<endl;
	}
	_NeCo.Accept(&DrawConnected);
}
void MenuArea::DrawQuickGame(const Event *ev, void *data){
	_MenuArea.status = mmt_new;
	_MenuArea.InitS = InitIniFile();
	GameSequence(0,(void*)&(_MenuArea.InitS));
}
void MenuArea::DrawConToGame(const Event *ev, void *data){
	ifstream fin(con_file.c_str());
	string str;

	_MenuArea.PlayerNames.resize(2);
	_MenuArea.PlayerNames[0].SetName("Server Ip:");
	_MenuArea.PlayerNames[0].SetPos(-1.0,0.5,0.05);
	fin >> str;
	_MenuArea.PlayerNames[0].SetString(str);
	_MenuArea.PlayerNames[0].Draw();
	_MenuArea.PlayerNames[1].SetName("Your Name:");
	_MenuArea.PlayerNames[1].SetPos(-1.0,0.25,0.05);
	fin >> str;
	_MenuArea.PlayerNames[1].SetString(str);
	_MenuArea.PlayerNames[1].Draw();

	MenuList *launch = new MenuList();
	launch->SetPos(0.0,0.5,0.05);
	launch->AddOption("Connect",TryConnection);
	launch->Draw(mlt_choise);
	
	fin.close();
}
void MenuArea::DrawLoadGame(const Event *ev, void *data){
	int i,j;
	_MenuArea.InitS = InitIniFile();
	GameInitSettings *InitS = &(_MenuArea.InitS);
	InitS->PlayersNumber = 0;
	InitS->Save = true;
	
	_NeCo.InitServer();

	_MenuArea.Map.FillofFiles(".tws");
	_MenuArea.Map.AddDecr("Save file:");
	_MenuArea.Map.SetPos(1.0, 0.6, 0.05);
	_MenuArea.Map.SetWatched(&(InitS->Mapfile));
	_MenuArea.Map.Draw(mlt_dropdown);

	PT(PGButton) accept = MakeButton("Accept de Save","");
	_Framework.define_key(accept->get_click_event(MouseButton::one() ), "accept", &ReloadSave, 0);
	_MenuArea.ReloadButton = _Window->get_aspect_2d().attach_new_node(accept);
	_MenuArea.ReloadButton.set_pos(1.0,0,0.5);
	_MenuArea.ReloadButton.set_scale(0.05);

	MenuList *launch = new MenuList();
	launch->SetPos(1.0,-0.9,0.05);
	launch->AddOption("LAUNCH",&StartGameHost,(void*)InitS);
	launch->Draw(mlt_choise);
	_NeCo.Accept(&DrawConnected);
}
void MenuArea::ReloadSave(const Event *ev, void *data){

	int i,j;
	GameInitSettings *InitS = &(_MenuArea.InitS);
	InitS->MapName = IntToFile(InitS->Mapfile,".tws");
	vector<RacesType> rcs = GetRaces(InitS->MapName);
	InitS->PlayersNumber = rcs.size();

	if (_MenuArea.PlayerNames.size() < InitS->PlayersNumber){
		i = _MenuArea.PlayerNames.size();

		for (; i<InitS->PlayersNumber; ++i){
			_MenuArea.PlayerNames.push_back(InputString());
			_MenuArea.PlayerRaces.push_back(MenuList());
			_MenuArea.PlayerStatus.push_back(MenuList());
			_MenuArea.InitS.PlayersCons.push_back(-1);

			_MenuArea.PlayerNames[i].SetName("Name:");
			_MenuArea.PlayerNames[i].SetString(InitS->PlayerNames[i]);
			_MenuArea.PlayerNames[i].SetPos(-1.55,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerNames[i].Draw();

			_MenuArea.PlayerRaces[i].SetPos(-0.8,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerRaces[i].SetWatched((int*)&(InitS->PlayerRaces[i]));
			for (j = 0;j<MAX_RACE;++j)
				_MenuArea.PlayerRaces[i].AddOption(RacesFull[j]);
			InitS->PlayerRaces[i] = rcs[i];
			_MenuArea.PlayerRaces[i].Draw(mlt_dropdown);
			
			_MenuArea.PlayerStatus[i].SetPos(-0.3,0.5 - 0.25*i,0.05);
			_MenuArea.PlayerStatus[i].AddOption("Local (->net)");
			_MenuArea.PlayerStatus[i].AddOption("Net (->local)");
			_MenuArea.PlayerStatus[i].Draw(mlt_switch);
		}
	}
}
void MenuArea::DrawExitGame(const Event *ev, void *data){
	_exit(0);
}
void MenuArea::start(){
	DrawMain(0,0);
}
void MenuArea::LoadGame(const Event *ev, void *data){
	_MenuArea.status = mmt_new;
	GameInitSettings * InitS = (GameInitSettings*)data;

	SaveTranslator().LoadSave(InitS->MapName);
	InitLoadGame(*InitS);
	
	SND_MAIN_MENU->stop();

	_MenuArea.PlayerRaces.clear();
	_MenuArea.PlayerStatus.clear();
	_MenuArea.PlayerNames.clear();
	_MenuArea.Speaker.~MenuList();
	_MenuArea.Map.~MenuList();
	_MenuArea.VPs.~MenuList();
	_MenuArea.Load.~MenuList();
	_MenuArea.ReloadButton.remove_node();
	_MenuArea.BackPic.remove_node();
}
void MenuArea::StartGameHost(const Event *ev, void *data){
	GameInitSettings InitSout;
	int i,j;
	bool ghost;

	cout<<"Starting game for "<<_MenuArea.InitS.PlayersNumber<<" players"<<endl;

	for (i=0;i<_MenuArea.PlayerNames.size();++i)
		_MenuArea.InitS.PlayerNames[i] = _MenuArea.PlayerNames[i].GetAsString();

	for (i=0;i<_MenuArea.InitS.PlayersNumber;++i){
		if (_MenuArea.InitS.PlayersCons[i] != -1){
			InitSout = _MenuArea.InitS;
			cout<<"Sending initial data to "<<InitSout.PlayerNames[i]<<" connection "<<InitSout.PlayersCons[i]<<endl;
			ghost = true;
			for (j=0;j<InitSout.PlayersNumber;++j){
				if ((i != j)&&(ghost)){
					InitSout.PlayersCons[j] = 0;
					ghost = false;
				}
				else if (i!= j){
					InitSout.PlayersCons[j] = -2;
				}
				else
					InitSout.PlayersCons[j] = -1;
			}
			_NeCo.SendMsg(ErNetDatagram((void*)&InitSout,sizeof(InitSout)),_MenuArea.InitS.PlayersCons[i]);
			_NeCo.SendMsg(ErNetDatagram(Datagram(_MenuArea.InitS.MapName)),_MenuArea.InitS.PlayersCons[i]);
			_NeCo.SendMsg(ErNetDatagram(Datagram(_MenuArea.InitS.GalName)),_MenuArea.InitS.PlayersCons[i]);
			for (j=0;j<InitSout.PlayersNumber;++j)
				_NeCo.SendMsg(ErNetDatagram(_MenuArea.InitS.PlayerNames[j]),_MenuArea.InitS.PlayersCons[i]);
			_NeCo.SendMsg(ErNetDatagram(&(_MenuArea.InitS.PlayerRaces[0]),_MenuArea.InitS.PlayerRaces.size()*sizeof(int)),_MenuArea.InitS.PlayersCons[i]);
			_NeCo.SendMsg(ErNetDatagram(&(InitSout.PlayersCons[0]),InitSout.PlayersCons.size()*sizeof(int)),_MenuArea.InitS.PlayersCons[i]);
		}
	}
	_NeCo.Reject();
	_NeCo.SetResend(true);
	if (!_MenuArea.InitS.Save)
		GameSequence(0,(void*)&_MenuArea.InitS);
	else
		LoadGame(0,(void*)&_MenuArea.InitS);
}
void MenuArea::StartGameClient(const Event *ev, void *data){
	NetDatagram* ndata = (NetDatagram*)data;
	_NeCo.Reject();
	cout<<"Getting initial data from host"<<endl;
	GameInitSettings* InitSIN = (GameInitSettings*) ndata->get_data();
	_MenuArea.InitS.Import(*InitSIN);
	cout<<"Inits Imported"<<endl;
	int i=0,j=0;
	while (i<5){
		switch(i){
			case 0:
				while (_NeCo.messages.size() == 0)
					tskReaderPolling(0,0);
				_MenuArea.InitS.MapName = _NeCo.messages[0].ndata.get_message();
				_NeCo.messages.pop_front();
				cout<<"mapname imported"<<endl;
				++i;
				break;
			case 1:
				while (_NeCo.messages.size() == 0)
					tskReaderPolling(0,0);
				_MenuArea.InitS.GalName = _NeCo.messages[0].ndata.get_message();
				_NeCo.messages.pop_front();
				++i;
				cout<<"galname imported"<<endl;
				break;
			case 2:
				while (_NeCo.messages.size() == 0)
					tskReaderPolling(0,0);
				_MenuArea.InitS.PlayerNames[j] = _NeCo.messages[0].ndata.get_message();
				_NeCo.messages.pop_front();
				++j;
				if (j == _MenuArea.InitS.PlayersNumber)
					++i;
				cout<<"names imported"<<endl;
				break;
			case 3:
				while (_NeCo.messages.size() == 0)
					tskReaderPolling(0,0);
				_MenuArea.InitS.PlayerRaces = _NeCo.messages[0].GetDataAsVector();
				_NeCo.messages.pop_front();
				++i;
				cout<<"races imported"<<endl;
				break;
			case 4:
				while (_NeCo.messages.size() == 0)
					tskReaderPolling(0,0);
				_MenuArea.InitS.PlayersCons = _NeCo.messages[0].GetDataAsVector();
				_NeCo.messages.pop_front();
				++i;
				cout<<"cons imported"<<endl;
				break;
		}
	}
	if (!_MenuArea.InitS.Save)
		GameSequence(0,(void*)&_MenuArea.InitS);
	else{
		LoadGame(0,(void*)&_MenuArea.InitS);
	}
}
void MenuArea::GameSequence(const Event *ev, void *data){
	_MenuArea.status = mmt_new;
	GameInitSettings * InitS = (GameInitSettings*)data;
	InitNewGame(*InitS);
	//CreateBasicGalaxy(*InitS);
	//LoadGalaxy(*InitS);
	PreGame();//Zoldn's move Pregame from twilight.cpp
	
	SND_MAIN_MENU->stop();
	_MenuArea.PlayerRaces.clear();
	_MenuArea.PlayerStatus.clear();
	_MenuArea.PlayerNames.clear();
	_MenuArea.Speaker.~MenuList();
	_MenuArea.Map.~MenuList();
	_MenuArea.VPs.~MenuList();
	_MenuArea.Load.~MenuList();
	_MenuArea.ReloadButton.remove_node();
	_MenuArea.BackPic.remove_node();
}
void MenuArea::TryConnection(const Event *ev, void *data){
	if (_NeCo.ConnectTo(_MenuArea.PlayerNames[0].GetAsString())){
		_NeCo.SendMsg(Datagram(_MenuArea.PlayerNames[1].GetAsString().c_str(),_MenuArea.PlayerNames[1].GetAsString().size()));
		_MenuArea.PlayerNames[0].Deactivate();
		_NeCo.Accept(&StartGameClient);
	}
	else
		cout<<"meh\n";
}