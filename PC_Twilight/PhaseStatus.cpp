bool StatusPhase(){
	int i,j;
	_GameStats.CurPhase = gpt_status;
	SaveTranslator().MakeSave(GetAutoSaveName());
	_Interface.PrintThingAll("--- STATUS PHASE ---");
	//старт статус-фазы, уборка кнопки и прочее
	for (i=_GameStats.Speaker;i<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++i)
		_Players[i%_GameStats.GetPlayersNumber()]->ExecuteGameEffect(ExecuteParams(eq_StatusStart,_Players[i%_GameStats.GetPlayersNumber()]));
	//выполнение заданий
	for (i=_GameStats.Speaker;i<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++i){
		//_Players[i%_GameStats.GetPlayersNumber()]->ExecuteGameEffect(ExecuteParams(eq_ObjCheck,_Players[i%_GameStats.GetPlayersNumber()]));
		//_Interface.SetCurrPlayer(_Players[i%_GameStats.GetPlayersNumber()]->GetId()-1);
		CompliteObj(_Players[i%_GameStats.GetPlayersNumber()],true,true);
	}
	//починка
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		(*aiter)->Repair();
	//уборка каунтеров
	for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++)
		(*iter)->ClearCCs();
	//открытие планет, раздача каунтеров, возвращение страт-карт
	vector<int> newCC;
	vector<int> newAC;
	newCC.resize(_GameStats.GetPlayersNumber());
	newAC.resize(_GameStats.GetPlayersNumber());
	for (i=_GameStats.Speaker;i<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++i){
		j = i % _GameStats.GetPlayersNumber();
		newCC[j] = 2;
		newAC[j] = 1;
		_Players[j]->ExecuteGameEffect(ExecuteParams(eq_StatusPhase,_Players[j],&newCC[j],&newAC[j]));
	}
	for (i=_GameStats.Speaker;i<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++i){
		j = i % _GameStats.GetPlayersNumber();
		_Interface.SetCurrPlayer(j);
		_Players[j]->RefreshPlanet();
		_Players[j]->ActivateDocks();
		_Players[j]->GiveFreeCounters(newCC[j],true);
		_Players[j]->AddAction(newAC[j]);
		_Players[j]->CheckFleets();
		_Players[j]->ReturnStrats();
	}
	for (i=_GameStats.Speaker;i<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++i){
		j = i % _GameStats.GetPlayersNumber();
		//_Players[j]->ExecuteGameEffect(ExecuteParams(eq_StatusEnd,_Players[j]));
		_Players[j]->MakeStatusAction();
	}
	_GameStats.CurRound++;
	return false;
}