int ConvertBonus(Player* player, int bonus){
	if (bonus <= 0)
		return 0;
	char str[255];
	vector<int> ret;
	int i,sum;
	while (true){
		ret.clear();
		sprintf(str,"Convert your %d bonus(es) from Strategy card",bonus);
		_GrIn.InitChoise(str,false,true,true);
		for (i = 0; i < CC_MAX; i++)
			_GrIn.AddNumerical(EMPTY_EVENT_IMG,CC_PoolsFull[i]);
		_GrIn.AddNumerical(GOODS_IMG,"Trade Goods");
		ret = _GrIn.LaunchChoise();
		if (ret.size() != (CC_MAX + 1)){
			Log("ConvertBonus : SUM TING WONG ret.size() != 4");
			continue;
		}
		sum = 0;
		for (i = 0; i <= CC_MAX; i++)
			sum += ret.at(i);
		if (sum > bonus){
			Log("ConvertBonus : wants too much");
			continue;
		}
		if (sum < bonus){
			Log("ConvertBonus : you can get moar");
			continue;
		}
		player->GiveGoods(ret.at(CC_MAX));
		player->AddCC(ret.at(CC_strat),ret.at(CC_fleet),ret.at(CC_comm));
		sprintf(str,"Player %s receives %d Counter(s) and %d Trade Good(s) from Stratcard bonuses",player->GetName().c_str(),ret.at(CC_strat)+ret.at(CC_fleet)+ret.at(CC_comm),ret.at(CC_MAX));
		_Interface.PrintThingAll(str);
		break;
	}
	return 1;
}

int DistrStrats(){ // ѕерераспределение —трат карт и инициативы.
	int i,j,c,k, round = 1;
	int * arr;
	char str[255];
	char stra[255];
	bool strats[MAX_STRAT];// BUG! can be skipped with pass/cnf
	for (i=0;i<MAX_STRAT;++i)
		strats[i] = false;
	int stratcardtoplayer = 1;
	if (_GameStats.GetPlayersNumber() <= 4)
		stratcardtoplayer = 2;
	if (_GameStats.GetPlayersNumber() == 2)
		stratcardtoplayer = 3;
	for (int z=1; z<=stratcardtoplayer; z++){
		for (i=_GameStats.Speaker;i<_GameStats.Speaker+_GameStats.GetPlayersNumber();++i){
			_Interface.SetCurrPlayer(i % _GameStats.GetPlayersNumber());
			_GrIn.InitChoise("Choose Strat card");
			for (j=0;j<MAX_STRAT;++j)
				if (strats[j]==false){
					sprintf(str,StratsFull[j].c_str());
					if (_GameStats.GetStrategies()->at(j)->GetBonus()){
						sprintf(stra," (%d bonus)",_GameStats.GetStrategies()->at(j)->GetBonus());
						strcat(str,stra);
					}
					_GrIn.AddOption(STRAT_B_PATH[j],str);
				}
			vector<int> tempvec = _GrIn.LaunchChoise();
			arr = &tempvec[0];
			for (c=0,k=0;c<MAX_STRAT;++c){
				if (strats[c])
					continue;
				if (arr[k]==1)
					break;
				else
					++k;
			}
			//_Players[i % _GameStats.GetPlayersNumber()]->AddStrat((StratsType)c);
			//обработка бонусов
			ConvertBonus(_Players[i % _GameStats.GetPlayersNumber()],_GameStats.GetStrategies()->at(c)->GetBonus());
			_GameStats.GetStrategies()->at(c)->Execute(ExecuteParams(eq_SpecialStratCard,_Players[i % _GameStats.GetPlayersNumber()],_GameStats.GetStrategies()->at(c)));
			_GameStats.GetStrategies()->at(c)->NullBonus();
			_Players[i % _GameStats.GetPlayersNumber()]->AddGameEffect(_GameStats.GetStrategies()->at(c)->Clone());
			sprintf(str,"Player %s selects %s strategy",_Players[i % _GameStats.GetPlayersNumber()]->GetName().c_str(),StratsFull[c].c_str());
			Log(str);
			_Interface.PrintThingAll(str);
			//_Players[i % _GameStats.GetPlayersNumber()]->AddAAA(new e_DullStrat((StratsType)c));
			//_Players[i % _GameStats.GetPlayersNumber()]->AddGameEffect(new e_DullStrat((StratsType)c));
			strats[c] = true;
			/*if ((i+1 == _GameStats.Speaker+_GameStats.GetPlayersNumber())&&(MAX_STRAT / _GameStats.GetPlayersNumber() > round)){
				++round; // ƒополнительные трапеции при игре на 3 и 4х игроков
				i = _GameStats.Speaker - 1;
			}*/
		}
	}
	//добавл€ем бонусы
	for (i = 0; i < MAX_STRAT; i++)
		if (!strats[i])
			_GameStats.GetStrategies()->at(i)->AddBonus();
	for (i=MAX_STRAT-1;i>=0;--i) // «адаем всем инициативу.
		for (j=0;j<_GameStats.GetPlayersNumber();++j)
			if (_Players[j]->GotStrat((StratsType)i)){
				_Players[j]->SetInitiative(i);
				if (i==0)
					_GameStats.Speaker = j;
			};
	cout<<_GameStats.Speaker;
	return 1;
}

bool StrategyPhase(){
	int i,b=8;
	_GameStats.CurPhase = gpt_strategy;
	_GameStats.CurTurn = 0;
	SaveTranslator().MakeSave(GetAutoSaveName());
	char buff[255];
	sprintf(buff,"--- ROUND %d BEGINS ---",_GameStats.CurRound);
	_Interface.PrintThingAll(buff);
	_Interface.PrintThingAll("--- STRATEGY PHASE ---");
	for (i=0;i<_GameStats.GetPlayersNumber();++i)
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_StrategyStart,_Players[i]));

	DistrStrats();
	for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_StrategyEnd,_Players[i]));
	for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
		_Players[i]->MakeQueueAction(ExecuteParams(eq_StrategyAction,_Players[i]),"Select action 'during Strategy Phase'");
	//обновление статуса заданий
	for (i=0;i<_GameStats.GetPlayersNumber();++i)
		_Players[i]->RefreshObjectives();
	return false;
}

