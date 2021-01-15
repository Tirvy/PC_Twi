void PreGame(){
	int i,k;
	_GameStats.InitPoliticDeck(PoliticsList);

	//стартовые юниты
	for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		_Players[i]->RefreshPlanet();
		_Players[i]->AddGameEffect(StartUnits[_Players[i]->GetRace()]->Clone());
		_Players[i]->AddPolitic(_GameStats.DrawPolitic());
		_Players[i]->AddPolitic(_GameStats.DrawPolitic());
	}
	//общие эффекты
	for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		for (vector<GameEffect*>::iterator iter = CommonEffects.begin(); iter != CommonEffects.end(); ++iter){
			//пока все раздается всем, потом сделать в соответствии с опциями
			_Players[i]->AddGameEffect((*iter)->Clone());
		}
	}
	//техи
	_GameStats.SetTechDeck(TechList);
	//запуск прегейм очереди
	for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_Pregame,_Players[i]));
	}
	//
	_GameStats.CurRound = 1;
	_GameStats.CurTurn = 0;

	//создание дек заданий
	vector<e_Objective*> Public = FormPublicObjectiveDeck(6,3,true);
	vector<e_Objective*> Prelim = FormPreliminaryObjectiveDeck();
	vector<e_Objective*> Secret = FormSecretObjectiveDeck();
	vector<e_Objective*> Opened;
	Opened.clear();
	_GameStats.SetObjectiveDecks(Public,Prelim,Secret,Opened);//запись векторов в _GameStats
	//раздача секреток/предварительных + основное задание на Ч ПО
	for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		//_Players[i]->AddObjective(new o_g_VP());
		//_Players[i]->AddGameEffect(new o_g_VP());
		//_Players[i]->AddGameEffect(_Players[i]->AddObjective(new o_g_VP()));
		_Players[i]->AddGameEffect(new o_g_VP());
		GiveSecretObjective(_Players[i],1);
	}
	//создание деки экшонов
	vector<e_ActionCard*> actions = FormActionCardDeck();
	_GameStats.SetActionDeck(actions);
	//определение стратов
	_GameStats.SetStrategies(StratCardList);
	for (i = 0; i < MAX_STRAT; i++)//обнуляем бонусы
		_GameStats.GetStrategies()->at(i)->NullBonus();
	//Вроде как уже задается
	//for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
	//	_Players[i]->AddAction(1);
	//_GameStats.VPftw = 9;//временно, для теста
	//объяление первого публичного задания
	OpenPublicObjective(Public.front());
}