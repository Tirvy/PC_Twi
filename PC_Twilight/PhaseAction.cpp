/*bool ActionPhase(){
	int i,j,passed = 0;
	bool pass[MAX_PLAYERS];
	_GameStats.CurPhase = gpt_action;
	for (i=0;i<_GameStats.GetPlayersNumber();++i){
		pass[i]=false;
	}
	while(passed<_GameStats.GetPlayersNumber())
		for (i=0;i<MAX_STRAT;++i)
			for (j=0;j<_GameStats.GetPlayersNumber();++j)
				if ((_Players[j]->GetInitiative() == i)&&(!pass[j])){
					_Interface.SetCurrPlayer(j);
					pass[j] = _Players[j]->MakeAction();
					if (pass[j])
						++passed;
				}
	return false;
}*/

bool ActionPhase(bool fromload = false){
	int i,k,passed = 0;
	char str[127];
	Player* curPlayer;
	int curPl;
	bool saving = !fromload;
	_GameStats.CurPhase = gpt_action;
	_Interface.PrintThingAll("--- ACTION PHASE ---");
	if (!fromload){
		for (i=0;i<_GameStats.GetPlayersNumber();++i)
			_GameStats.playerstatus[i]=3;
		curPl = _GameStats.NextPlayer();
		_GameStats.ActivePlayer = curPl;
		_GameStats.CurTurn = 1;
	}
	else{
		for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
			i = k % _GameStats.GetPlayersNumber();
			if (_GameStats.playerstatus[i]==1)
				curPl = i;
		}
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
			cout<<"Load players' statuses "<<_GameStats.playerstatus[i]<<endl;
		cout<<"Curplayer is "<<curPl<<endl;
	}
	while (curPl != -1){
		_GameStats.playerstatus[curPl] = 1;
		curPlayer = _Players[curPl];
		_Interface.SetCurrPlayer(curPlayer->GetNumber() - 1);
		sprintf(str,"Turn goes to player %d, (%s)",curPlayer->GetNumber(),RacesFull[curPlayer->GetRace()].c_str());
		_Interface.PrintThingAll(str);
		//SaveTranslator().MakeSave("..\\Release\\data\\autosave.tws");
		if (saving){//убирает перезапись того сейва, с которого идет загрузка
			SaveTranslator().MakeSave(GetAutoSaveName());
			saving = true;
		}
		if (_Players[curPl]->MakeAction())
			_GameStats.playerstatus[curPl] = 0;
		else
			_GameStats.playerstatus[curPl] = 2;
		curPl = _GameStats.NextPlayer();
		_GameStats.CurTurn++;
		saving = true;
	}
	return false;
}