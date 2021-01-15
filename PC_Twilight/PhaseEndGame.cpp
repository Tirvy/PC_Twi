int GetLeaders(int* r, int n){
	int tie=0;
	for (int i=0; i<n; i++){
		if (r[i])
			tie++;
	}
	return tie;
};

Player* GetWinner(int* r, int n){
	Player* player = 0;
	if (GetLeaders(r,n)==1){
		for (int i=0; i<n; i++)
			if (r[i])
				player = _Players[i];
	}
	return player;
}

int EndOfGame(){
	int number = _GameStats.GetPlayersNumber();
	Player* winner = 0;
	int* results = new int[number];
	int leaders = number;
	int i;
	char str[257];
	char str1[257];
	for (i=0; i<number; i++)
		results[i]=1;
	//ищем игрока с "I win teh gaem!"
	for (i = 0; i < number; i++){
		if (_Players[i]->ObjectiveWin() != 0){
			winner = _Players[i];
			leaders = 1;
			sprintf(str,"Player %s wins the game by %s!",winner->GetName().c_str(),winner->ObjectiveWin()->GetShortReqs().c_str());
			_Interface.PrintThingAll(str);
			break;
		}
	}
	//ищем игрока/игроков с наибольшими VP
	int maxVP=0;
	if (winner == 0){
		for (i=0; i<number; i++)
			if (maxVP<_Players[i]->recountVP())
				maxVP=_Players[i]->recountVP();
		for (i=0; i<number; i++)
			if (_Players[i]->recountVP()<maxVP)
				results[i]=0;
		leaders = GetLeaders(results,number);
		//если ничья, то наибольшее число заданий
		int maxObj=0;
		if (leaders>1){
			for (i=0; i<number; i++)
				if ((maxObj<_Players[i]->DoneObjectives())&&(results[i]))
					maxObj=_Players[i]->DoneObjectives();
			for (i=0; i<number; i++)
				if ((_Players[i]->DoneObjectives()<maxObj)&&(results[i]))
					results[i]=0;
			leaders = GetLeaders(results,number);
		}
		//если ничья, то кол-во планет
		int maxPlanets=0;
		if (leaders>1){
			for (i=0; i<number; i++)
				if ((maxPlanets<_Players[i]->NumberOfPlanets())&&(results[i]))
					maxPlanets=_Players[i]->NumberOfPlanets();
			for (i=0; i<number; i++)
				if ((_Players[i]->NumberOfPlanets()<maxPlanets)&&(results[i]))
					results[i]=0;
			leaders = GetLeaders(results,number);
		}
		//если ничья, то каунтеры в резерве
		/*int unusedCC=0;
		if (leaders>1){
			for (i=0; i<number; i++)
				if ((unusedCC<_Players[i]->UnusedCC())&&(results[i]))
					unusedCC=_Players[i]->UnusedCC();
			for (i=0; i<number; i++)
				if ((_Players[i]->UnusedCC()<unusedCC)&&(results[i]))
					results[i]=0;
			leaders = GetLeaders(results,number);
		}*/
		//если ничья, то каунтеры на листе расы
		int activeCC=0;
		if (leaders>1){
			for (i=0; i<number; i++)
				if ((activeCC<_Players[i]->ActiveCC())&&(results[i]))
					activeCC=_Players[i]->ActiveCC();
			for (i=0; i<number; i++)
				if ((_Players[i]->ActiveCC()<activeCC)&&(results[i]))
					results[i]=0;
			leaders = GetLeaders(results,number);
		}
	}
	//итог
	if (leaders==1){
		winner = GetWinner(results,number);
		sprintf(str,"Congratulations! Player %s win the game!",winner->GetName());
		_Interface.PrintThingAll(str);
	}
	else{
		if (leaders==0)
			_Interface.PrintThingAll("Sum Ting Wong: can't find the winner");
		else{
			sprintf(str,"Draw. Tie between players: ");
			for (i=0; i<number; i++){
				if (results[i]){
					sprintf(str1,"%s, ",_Players[i]->GetName());
					strcat(str,str1);
				}
			}
			_Interface.PrintThingAll(str);
		}
	}
	SelectDialogYesNo("Finish game");
	delete [] results;
	return 1;
}