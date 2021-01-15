
int GameStats::SetGameStats(GameInitSettings InitS){
	_random_seed = InitS.RandSeed;
	srand(_random_seed);
	_playersnum = InitS.PlayersNumber;
	CurPhase = gpt_pregame;
	CurRound = 0;
	CurTurn = 0;
	ActivePlayer = 0;
	Speaker = InitS.Speaker;
	if ((Speaker < 0)||(Speaker >= _playersnum))
		Speaker = rand() % _playersnum;
	playerstatus = new int[_playersnum];
	for (int i=0; i < _playersnum; i++)
		playerstatus[i]=0;
	_IsManualCreation = false;
	return 1;
}
int GameStats::GetPlayersNumber(){
	return _playersnum;
}
Player* GameStats::GetNeutralPlayer(){
	return _neutral_player;
}
void GameStats::ClearArmies(){
	while (_Armies.size() != 0){
		delete _Armies.front();
		_Armies.erase(_Armies.begin());
	}
}
//objectives
void GameStats::SetObjectiveDecks(vector<e_Objective*> spublic, vector<e_Objective*> sprelim, vector<e_Objective*> ssecret, vector<e_Objective*> sopened){
	_PublicObjDeck = spublic;
	_PublicObjDeckOpen = sopened;
	_PrelimObjDeck = sprelim;
	_SecretObjDeck = ssecret;
}

vector<e_Objective*>* GameStats::GetPrelimObjectives(){
	return &_PrelimObjDeck;
}

vector<e_Objective*>* GameStats::GetPublicOpenObjectives(){
	return &_PublicObjDeckOpen;
}

vector<e_Objective*>* GameStats::GetSecretObjectives(){
	return &_SecretObjDeck;
}

vector<e_Objective*>* GameStats::GetPublicObjectives(){
	return &_PublicObjDeck;
}
void GameStats::AddLaw(GameEffect* law){
	_Laws.push_back(law);
}
void GameStats::InitPoliticDeck(list<e_Politic*> PoliticsList){
	list<e_Politic*>::iterator _inter = PoliticsList.begin();
	while (_inter != PoliticsList.end()){
		_PoliticsDeck.push_back((e_Politic*)(*_inter)->Clone());
		++_inter;
	}
	sync_shuffle(_PoliticsDeck);
}

e_Politic* GameStats::DrawPolitic(){
	e_Politic* ret = (e_Politic*)(*(_PoliticsDeck.begin()))->Clone();
	_PoliticsDeck.pop_front();
	return ret;
}

void GameStats::SetTechDeck(vector<e_Tech*> stechs){
	_TechDeck = stechs;
}
vector<e_Tech*>* GameStats::GetTechDeck(){
	return &_TechDeck;
}

deque<e_Politic*>* GameStats::GetPoliticDeck(){
	return &_PoliticsDeck;
}
Player* GameStats::GetLocalPlayer(){
	int i;
	if (_Players[_Interface.GetCurrPlayer()]->GetConnection() == -1)
		return _Players[_Interface.GetCurrPlayer()];
	for (i=0;i<_playersnum;++i){
		if (_Players[i]->GetConnection() == -1)
			return _Players[i];
	}
	Eggog("GameStats::GetLocalPlayer() didnt find player");
	return 0;
}
//0 - пас
//1 - активный игрок
//2 - походивший в круге, но не пасанувший
//3 - не ходивший в круге и не пасанувший
int GameStats::NextPlayer(){
	int r = -1;
	int initiative = 99;
	int maxstatus = 0;
	for (int i=0; i < GetPlayersNumber(); ++i)
		if (_GameStats.playerstatus[i]>maxstatus)
			maxstatus = _GameStats.playerstatus[i];
	if (maxstatus == 0)
		return -1;
	if (maxstatus == 2)
		for (int i=0; i < GetPlayersNumber(); ++i)
			if (_GameStats.playerstatus[i] == 2)
				_GameStats.playerstatus[i] = 3;
	for (int i=0; i < GetPlayersNumber(); ++i){
		if ((_GameStats.playerstatus[i] == 3) && (_Players[i]->GetInitiative()<initiative)){
			r = i;
			initiative = _Players[i]->GetInitiative();
		}
	}
	return r;
}

void GameStats::SetActionDeck(vector<e_ActionCard*> sactions){
	_ActionDeck = sactions;
}

vector<e_ActionCard*>* GameStats::GetActionDeck(){
	return &_ActionDeck;
}

e_ActionCard* GameStats::DrawAction(){
	e_ActionCard* ret = (e_ActionCard*)(*(_ActionDeck.begin()))->Clone();
	_ActionDeck.erase(_ActionDeck.begin());
	return ret;
}

void GameStats::SetStrategies(vector<e_StratCard*> sstrats){
	_Strats = sstrats;
}

vector<e_StratCard*>* GameStats::GetStrategies(){
	return &_Strats;
}