void CombatInterface::GEE(GameEffectQs Q, Army *attArmy, Army *defArmy, int round){
	RefreshArmyAbilities(attArmy,1);
	if (defArmy!=0)
		RefreshArmyAbilities(defArmy,1);
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,attArmy,defArmy,round,1));
	if (defArmy!=0)
		defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,defArmy,attArmy,round,0));
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(Q,attArmy,defArmy,round,1));
	if (defArmy!=0)
		defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(Q,defArmy,attArmy,round,0));
}

void CombatInterface::GES(GameEffectQs Q, Army *attArmy, Army *defArmy, int round){
	string str;
	switch (Q){
		case eq_BeforeBattleRoundAction:
			str = "Select action 'Before battle round'";
			break;
		default:
			str = "Select action to make";
	}
	attArmy->GetOwner()->MakeQueueAction(ExecuteParams(Q,attArmy,defArmy,round,1),str);
	if (defArmy!=0)
		defArmy->GetOwner()->MakeQueueAction(ExecuteParams(Q,defArmy,attArmy,round,0),str);
}

int CombatInterface::CombatTacticalAction(Army* attArmy){
	Hex* battleHex = attArmy->GetHex();
	if (attArmy == 0)//проверка существования армии
		return 0;
	if (attArmy->GetHex() == 0)//проверка корректности гекса боя
		return 0;
	Battle_Result result=SpaceCombat(attArmy);//космический бой
	if (result == br_AttackerWins){
		//CheckTradeStations(battleHex,attArmy->GetOwner());
		CheckTradeStations();//захват торговых станций
		Landing(attArmy);//в случае победы атакующего, начало высадки
	}
	return 1;
}

Battle_Result CombatInterface::SpaceCombat(Army* attArmy){
	Hex* battleHex = attArmy->GetHex();
	Battle_Result result=br_MAX;
	int round=0;
	bool attDefeated = false;
	bool defDefeated = false;
	bool battle = true;
	bool retreat = false;//защищающийся
	bool withdraw = false;//атакующий
	bool AttackerAction = true;
	bool DefenderAction = true;
	Army* defArmy = FindOpponentArmy(attArmy);//ищем оборонительную армию
	//истребы высаживаются из транспортов
	for (vector<Unit*>::iterator iter = attArmy->GetUnits()->begin(); iter != attArmy->GetUnits()->end(); iter++)
		if ((*iter)->HasAbility(uaFighter))
			attArmy->SetPassenger(0,*iter);
	//PDS fire
	GEE(eq_PDSmain,attArmy,0,0);
	//проверка на досрочный конец
	if (attArmy->isDefeated())
		return br_AttackerLoses;
	if (defArmy == 0)//если нет вражеских юнитов, выход с победой атакующего
		return br_AttackerWins;
	//если есть, начало боя
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BattleStart,attArmy,defArmy,0,0));
	defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BattleStart,defArmy,attArmy,0,1));
	if (attArmy->isDefeated())
		return br_AttackerLoses;
	if (defArmy->isDefeated())
		return br_AttackerWins;
	sprintf(str,"Space battle begins at: {%s}",battleHex->GetId().c_str());
	_Interface.PrintThingAll(str);
	sprintf(str,"   Attacker: Player %d{%s}",attArmy->GetOwner()->GetId(),attArmy->GetOwner()->GetName().c_str());
	_Interface.PrintThingAll(str);
	if (defArmy->GetOwner() != 0){
		sprintf(str,"   Defender: Player %d{%s}",defArmy->GetOwner()->GetId(),defArmy->GetOwner()->GetName().c_str());
		_Interface.PrintThingAll(str);
	}
	else
		_Interface.PrintThingAll("   Defender: neutral");
	if ((attArmy->GetOwner() != 0) && (defArmy->GetOwner() != 0))
		BreakRoute(attArmy->GetOwner(),defArmy->GetOwner());//разрыв договора
	//прекомбат эффекты
	battle=!attArmy->isDefeated() && !defArmy->isDefeated();
	GEE(eq_BeforeBattle,attArmy,defArmy,round);//пассивные эффекты и всякие проверки
	while (battle){//активные абилки авангарда
		RefreshArmyAbilities(attArmy,1);
		RefreshArmyAbilities(defArmy,1);
		attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,attArmy,defArmy,round,1));
		defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,defArmy,attArmy,round,0));
		if (AttackerAction)
			AttackerAction = attArmy->GetOwner()->MakeQueueAction(ExecuteParams(eq_BeforeBattleAction,attArmy,defArmy,round,1),"Select action 'Before Space Battle'",true);
		if (DefenderAction)
			DefenderAction = defArmy->GetOwner()->MakeQueueAction(ExecuteParams(eq_BeforeBattleAction,defArmy,attArmy,round,0),"Select action 'Before Space Battle'",true);
		battle = (AttackerAction || DefenderAction) && !attArmy->isDefeated() && !defArmy->isDefeated();
	}
	battle=!attArmy->isDefeated()&&!defArmy->isDefeated();
	while (battle){//бой
		round++;
		_Interface.PrintThingAll("New battle round");
		GEE(eq_BeforeBattleRound,attArmy,defArmy,round);
		GES(eq_BeforeBattleRoundAction,attArmy,defArmy,round);
		//ROLL! ROLL! ROLL!
		if (!attArmy->isDefeated() && !defArmy->isDefeated())
			RollingDices(attArmy,defArmy,bt_Space,true);
		AutoRepairs(attArmy);
		AutoRepairs(defArmy);
		GEE(eq_AfterBattleRound,attArmy,defArmy,round);
		GES(eq_AfterBattleRoundAction,attArmy,defArmy,round);
		//проверки конца боя
		if (attArmy->isDefeated() || defArmy->isDefeated() || attArmy->_retreating || defArmy->_retreating)
			battle=false;
	}
	GEE(eq_AfterBattle,attArmy,defArmy,round);
	//attDefeated=attArmy->isDefeated();
	//defDefeated=defArmy->isDefeated();
	attArmy->CheckPasSupport();
	defArmy->CheckPasSupport();
	attArmy->RemoveKilledUnits();//удаление юнитов uaKilled
	defArmy->RemoveKilledUnits();
	/*attDefeated=attArmy->isDefeated();
	defDefeated=defArmy->isDefeated();
	if (withdraw && !attDefeated && !defDefeated)
		Retreat(attArmy);
	if (retreat && !attDefeated && !defDefeated)
		Retreat(defArmy);*/
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Retreat,attArmy,defArmy,-1,1));
	defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Retreat,defArmy,attArmy,-1,0));
	attArmy->CheckPasSupport();//проверка на тех, кто не умеет отступать
	defArmy->CheckPasSupport();
	attArmy->RemoveKilledUnits();//удаление юнитов uaKilled
	defArmy->RemoveKilledUnits();
	attDefeated=attArmy->isDefeated();
	defDefeated=defArmy->isDefeated();
	if (attDefeated)
		attArmy->KillArmy();
	if (defDefeated)
		defArmy->KillArmy();
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BattleEnd,attArmy,defArmy,0,0));
	defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BattleEnd,defArmy,attArmy,0,1));
	_Interface.PrintThingAll("Battle results:");
	if (attDefeated){//результаты боя
		if (defDefeated){
			_Interface.PrintThingAll("Draw");
			result=br_Draw;
		}
		else{
			sprintf(str,"Defending player %s wins",defArmy->GetOwner()->GetName().c_str());
			_Interface.PrintThingAll(str);
			result=br_AttackerLoses;
		}
	}
	else{//атакующий выжил
		if (defDefeated){
			sprintf(str,"Attacking player %s wins",attArmy->GetOwner()->GetName().c_str());
			_Interface.PrintThingAll(str);
			result=br_AttackerWins;
		}
		else{//оба выжили
			_Interface.PrintThingAll("SUM TING WONG: both players stay with fleets after battle and retreats");
			result=br_MAX;
		}
	}
	return result;
};

int CombatInterface::Landing(Army *attArmy, bool isTransfer){
	Army* landArmy=0;
	Army* defArmy=0;
	Planet* curPlanet;
	Hex* hex = attArmy->GetHex();
	bool* bomb=0;
	int planets = 0;
	int choise = 0;
	_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
	bool landing = true;
	bool isPlanetsToLand = false;
	bool isInvasionUnits = false;
	bool isInvasion;
	Battle_Result BT;
	int i,j;
	for (i=1; i<=MAX_PLANETS; i++)
		if (hex->GetPlanet(i)!=0)
			planets++;
	if (planets==0)
		return 0;
	isInvasionUnits = attArmy->IsUnitWithAbility(uaDropped);
	bool* toland = new bool[planets];
	for (int i=0; i<planets; i++){
		if ((hex->GetPlanet(i+1)->GetSpecial()!=TradeStation) && ((!isTransfer) || (hex->GetPlanet(i+1)->GetOwner() == attArmy->GetOwner())))
			toland[i]=true;
		else
			toland[i]=false;
	}
	for (int i=0; i<planets; i++)
		if (toland[i])
			isPlanetsToLand=true;
	landing = isPlanetsToLand && isInvasionUnits;
	while (landing){
		choise = SelectDialogPlanetInSystem("Select planet to land", hex, attArmy->GetOwner(),toland,planets);
		if (choise){
			curPlanet = hex->GetPlanet(choise);
			sprintf(str,"Player %s starts landing on planet %s",attArmy->GetOwner()->GetName().c_str(),curPlanet->GetName().c_str());
			_Interface.PrintThingAll(str);
			landArmy = FindAllyArmy(attArmy->GetOwner(),hex,curPlanet);
			if (landArmy == 0)
				landArmy = NewArmy(attArmy->GetOwner(),hex,curPlanet);
			int mask[MAX_UNIT];
			vector<UnitSelection> options;
			UnitSelection US;
			options.clear();
			_GrIn.InitChoise("Select units for landing",true,true,true);
			for (i = 0; i <MAX_UNIT; i++)
				mask[i] = 0;
			for (vector<Unit*>::iterator ziter = attArmy->GetUnits()->begin(); ziter != attArmy->GetUnits()->end(); ziter++)
				if ((*ziter)->HasAbility(uaDropped))
					mask[(*ziter)->Class] = mask[(*ziter)->Class] + 1;
			for (UnitType UT = GF; UT < MAX_UNIT; UT = (UnitType)((int)UT + 1)){
				if (mask[UT]){
					if (attArmy->GetUnit(UT)->HasAbility(uaMultiple)){
						sprintf(str,"%s",ShipsShort[UT].c_str());
						sprintf(stra," x%d",mask[UT]);
						strcat(str,stra);
						_GrIn.AddNumerical(SHIPS_IMG[UT],str);
						US.UT = UT;
						US.army = attArmy;
						US.multiple = true;
						US.n = mask[UT];
						US.selected = 0;
						US.unit = 0;
						options.push_back(US);
					}
					else{
						for (j = 1; j <= mask[UT]; j++){
							sprintf(str,"%s",ShipsShort[UT].c_str());
							if ((attArmy->GetUnit(UT,j)->HasAbility(uaSustain))&&(attArmy->GetUnit(UT,j)->GetAbility(uaSustain).field1))
								strcat(str,"(dmg)");
							_GrIn.AddNumerical(SHIPS_IMG[UT],str);
							US.UT = UT;
							US.army = attArmy;
							US.n = 1;
							US.unit = attArmy->GetUnit(UT,j);
							US.selected = 0;
							US.multiple = false;
							options.push_back(US);
						}
					}
				}
			}
			vector<int> ret = _GrIn.LaunchChoise();
			if (ret.size() == 0)
				break;
			i = 0;
			for (UnitType UT = GF; UT < MAX_UNIT; UT = (UnitType)((int)UT + 1))
				mask[UT] = landArmy->StackSize(UT);
			for (vector<UnitSelection>::iterator iter = options.begin(); iter != options.end(); iter++){
				if (ret.at(i) > iter->n){
					iter->selected = iter->n;
					_Interface.PrintThingAll("Warning: trying to pick up more units than exist, moving all available");
				}
				else
					iter->selected = ret.at(i);
				mask[iter->UT] += iter->selected;
				if (attArmy->GetUnit(iter->UT)->HasAbility(uaLimitOnPlanet)){
					if (attArmy->GetUnit(iter->UT)->GetAbility(uaLimitOnPlanet).field1 < mask[iter->UT]){
						sprintf(str,"You can't have too many %s on planet",ShipsShort[iter->UT].c_str());
						_Interface.PrintThingAll(str);
						mask[iter->UT] -= iter->n;
						iter->selected = 0;
					}
				}
				i++;
			}
			for (vector<UnitSelection>::iterator iter = options.begin(); iter != options.end(); iter++){
				if (iter->selected){
					if (iter->multiple)
						for (j = 1; j <= iter->selected; j++)
							MoveUnit(attArmy,landArmy,iter->army->GetUnit(iter->UT,1));
					else
						MoveUnit(attArmy,landArmy,iter->unit);
				}
			}
			toland[choise-1]=false;
			attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Landing,attArmy->GetOwner(),curPlanet));
			if (curPlanet->GetOwner()!=landArmy->GetOwner()){//высадка на недружественную планету
				defArmy=FindOpponentArmy(landArmy);
				//бомбы
				isInvasion=!landArmy->isDefeated();
				attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Bombardment,attArmy,defArmy,isInvasion));
				//PDS fire to landing party
				landArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_PDSfire,landArmy->GetOwner(),landArmy));
				//наземное вторжение
				BT=InvasionCombat(attArmy,landArmy,defArmy);
				if (BT == br_AttackerWins){
					if (curPlanet->GetOwner() != landArmy->GetOwner()){
						sprintf(str,"Player %s conquered planet %s",landArmy->GetOwner()->GetName().c_str(),curPlanet->GetName().c_str());
						_Interface.PrintThingAll(str);
						landArmy->GetOwner()->Capture(landArmy->GetPlanet());
					};
				}
				else
					_Interface.PrintThingAll("Conquest failed");
			}
			attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterLanding,attArmy->GetOwner(),curPlanet));
		}
		else
			break;
		isPlanetsToLand=false;
		for (int i=1; i<=planets; i++)
			if (toland[i-1])
				isPlanetsToLand=true;
		isInvasionUnits = attArmy->IsUnitWithAbility(uaDropped);;
		landing = isPlanetsToLand && isInvasionUnits;
	}
	//сброс статуса бомбардировщиков
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterBombardment,attArmy,defArmy,false));
	delete[] toland;
	return 1;
};

Battle_Result CombatInterface::InvasionCombat(Army *attArmy, Army *landArmy, Army *defArmy){
	_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
	if (landArmy->isDefeated()){
		landArmy->KillArmy();
		return br_AttackerLoses;
	}
	if (defArmy==0)
		return br_AttackerWins;
	bool attDefeated = landArmy->isDefeated();
	bool defDefeated = defArmy->isDefeated();
	bool battle = !attDefeated && !defDefeated;
	bool AttackerAction = true;
	bool DefenderAction = true;
	Battle_Result result=br_MAX;
	int round=0;
	landArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BattleStart,landArmy,defArmy,0,0));
	sprintf(str,"Invasion battle on planet %s begins",landArmy->GetPlanet()->GetName().c_str());
	_Interface.PrintThingAll(str);
	sprintf(str,"   Attacker: Player %d{%s}",landArmy->GetOwner()->GetId(),landArmy->GetOwner()->GetName().c_str());
	_Interface.PrintThingAll(str);
	if (defArmy->GetOwner()!=0){
		sprintf(str,"   Defender: Player %d{%s}",defArmy->GetOwner()->GetId(),defArmy->GetOwner()->GetName().c_str());
		_Interface.PrintThingAll(str);
	}
	else
		_Interface.PrintThingAll("   Defender: neutral");
	if ((attArmy->GetOwner() != 0) && (defArmy->GetOwner() != 0))
		BreakRoute(attArmy->GetOwner(),defArmy->GetOwner());
	//GEE(eq_BeforeBattle,landArmy,defArmy,round);
	battle=!landArmy->isDefeated() && !defArmy->isDefeated();
	GEE(eq_BeforeBattle,landArmy,defArmy,round);//пассивные эффекты и всякие проверки
	while (battle){//активные абилки авангарда
		RefreshArmyAbilities(landArmy,1);
		RefreshArmyAbilities(defArmy,1);
		landArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,landArmy,defArmy,round,1));
		defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Battle,defArmy,landArmy,round,0));
		if (AttackerAction)
			AttackerAction = landArmy->GetOwner()->MakeQueueAction(ExecuteParams(eq_BeforeBattleAction,landArmy,defArmy,round,1),"Select action 'Before Land Battle'",true);
		if (DefenderAction)
			DefenderAction = defArmy->GetOwner()->MakeQueueAction(ExecuteParams(eq_BeforeBattleAction,defArmy,landArmy,round,0),"Select action 'Before Land Battle'",true);
		battle = (AttackerAction || DefenderAction) && !landArmy->isDefeated() && !defArmy->isDefeated();
	}
	battle=!landArmy->isDefeated()&&!defArmy->isDefeated();
	while (battle){
		round++;
		_Interface.PrintThingAll("New battle round");
		GEE(eq_BeforeBattleRound,landArmy,defArmy,round);//проверка ивентов до боя
		GES(eq_BeforeBattleRoundAction,landArmy,defArmy,round);
		RollingDices(landArmy,defArmy,bt_Invasion,true);
		battle=(!landArmy->isDefeated())&&(!defArmy->isDefeated());
		GEE(eq_AfterBattleRound,landArmy,defArmy,round);
	}
	GEE(eq_AfterBattle,landArmy,defArmy,round);
	_Interface.SetCurrPlayer(landArmy->GetOwner()->GetId()-1);
	attDefeated=landArmy->isDefeated();
	defDefeated=defArmy->isDefeated();
	if (attDefeated)
		landArmy->KillArmy();
	if (defDefeated && !attDefeated)
		defArmy->KillArmy();
	landArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_BattleEnd,landArmy,defArmy,0,0));
	if (attDefeated){
		if (defDefeated){
			_Interface.PrintThingAll("Draw");
			result=br_Draw;
		}
		else{
			_Interface.PrintThingAll("Defender wins");
			result=br_AttackerLoses;
		}
	}
	else{
		if (defDefeated){
			_Interface.PrintThingAll("Attacker wins");
			defArmy->KillArmy();
			result=br_AttackerWins;
		}
		else{
			_Interface.PrintThingAll("Retreat");
			result=br_MAX;
		}
	}
	return result;
};

void CombatInterface::RollingDices(Army* attArmy, Army* defArmy, Battle_Type BT, bool isBoth){
	Roll* rollsA;//броски атакующего
	int rA = 0;	
	int dmgA = 0;
	int dmghA = 0;
	Roll* rollsD;//броски защищающегося
	int rD = 0;
	int dmgD = 0;
	int dmghD = 0;
	int k;
	int d;
	int hit;
	bool isHeavyDamage = false;
	//PowExv<Unit>* temp = attArmy->GetUnits();
	//while (temp!=0){
	for (vector<Unit*>::iterator iter = attArmy->GetUnits()->begin(); iter != attArmy->GetUnits()->end(); iter++)
		rA += HowManyDices(attArmy,*iter,BT);
		//temp=temp->next;
	if (rA)
		rollsA = new Roll[rA];
	//temp = attArmy->GetUnits();
	k=0;
	//while (temp!=0){
	for (vector<Unit*>::iterator iter = attArmy->GetUnits()->begin(); iter != attArmy->GetUnits()->end(); iter++){
		for (int i = 0; i < HowManyDices(attArmy,*iter,BT); i++){
			rollsA[k].isRerolled=false;
			rollsA[k].unit= *iter;
			rollsA[k].value=rand()%DICE+1;
			rollsA[k].power=GetPower(BT,*iter,attArmy);
			k++;
		}
		//temp=temp->next;
	}
	if (isBoth){//броски второго игрока, если он участвует
		//temp = defArmy->GetUnits();
		for (vector<Unit*>::iterator iter = defArmy->GetUnits()->begin(); iter != defArmy->GetUnits()->end(); iter++)
			rD+=HowManyDices(defArmy,*iter,BT);
			//temp=temp->next;
		//};
		if (rD)
			rollsD = new Roll[rD];
		//temp = defArmy->GetUnits();
		k=0;
		//while (temp!=0){
		for (vector<Unit*>::iterator iter = defArmy->GetUnits()->begin(); iter != defArmy->GetUnits()->end(); iter++){
			for (int i = 0; i < HowManyDices(defArmy,*iter,BT); i++){
				rollsD[k].isRerolled=false;
				rollsD[k].unit=*iter;
				rollsD[k].value=rand()%10+1;
				rollsD[k].power=GetPower(BT,*iter,defArmy);
				k++;
			}
			//temp=temp->next;
		}
	}
	//вывод бросков активного игрока
	_Interface.SetCurrPlayer(attArmy->GetOwner()->GetId()-1);
	k=ShowRolls(attArmy,rollsA,rA);
	//эффекты рероллов
	attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterRollingDices,attArmy,defArmy,rollsA,rA));
	attArmy->GetOwner()->MakeQueueAction(ExecuteParams(eq_AfterRollingDicesAction,attArmy,defArmy,rollsA,rA),"Select action 'rerolls'");
	//эффекты рероллов на броски противника (речек)
	if (isBoth){//броски второго игрока
		_Interface.SetCurrPlayer(defArmy->GetOwner()->GetId()-1);
		k=ShowRolls(defArmy,rollsD,rD);
		//эффекты рероллов
		defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterRollingDices,defArmy,attArmy,rollsD,rD));
		defArmy->GetOwner()->MakeQueueAction(ExecuteParams(eq_AfterRollingDicesAction,defArmy,attArmy,rollsD,rD),"Select action 'rerolls'");
		//эффекты рероллов на броски противника (речек)
	}
	//перевод бросков в урон
	//temp=attArmy->GetUnits();
	k=0;
	//while (temp!=0){
	for (vector<Unit*>::iterator iter = attArmy->GetUnits()->begin(); iter != attArmy->GetUnits()->end(); iter++){
		if (HowManyDices(attArmy,*iter,BT)){
			hit=GetPower(BT,*iter,attArmy);
			for (int i=0; i < HowManyDices(attArmy,*iter,BT); i++){
				d=1;
				isHeavyDamage=false;
				//эффекты "при броске 10"
				attArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterRoll,attArmy,*iter,&(rollsA[k].value)));
				if ((rollsA[k].value>=hit)||(rollsA[k].value==10)){
					if ((*iter)->HasAbility(uaCritical)&&(rollsA[k].value==10))
						d=(*iter)->GetAbility(uaCritical).field1;
					else
						d=1;
					if ((*iter)->HasAbility(uaHeavyDamage))
						dmghA+=d;
					else
						dmgA+=d;
				}
				k++;
			}
		}
		//temp=temp->next;
	}
	if (isBoth){
		//temp=defArmy->GetUnits();
		k=0;
		//while (temp!=0){
		for (vector<Unit*>::iterator iter = defArmy->GetUnits()->begin(); iter != defArmy->GetUnits()->end(); iter++){
			if (HowManyDices(defArmy,*iter,BT)){
				hit=GetPower(BT,*iter,defArmy);
				for (int i = 0; i < HowManyDices(defArmy,*iter,BT); i++){
					d=1;
					isHeavyDamage=false;
					//эффекты "при броске 10"
					defArmy->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterRoll,defArmy,*iter,&(rollsD[k].value)));	
					if ((*iter)->HasAbility(uaCritical)&&(rollsD[k].value==10))
						d=(*iter)->GetAbility(uaCritical).field1;
					else
						d=1;
					if ((rollsD[k].value>=hit)||(rollsD[k].value==10)){
						if ((*iter)->HasAbility(uaHeavyDamage))
							dmghD+=d;
						else
							dmgD+=d;
					}
					k++;
				}
			}
			//temp=temp->next;
		}
	}
	//назначение потерь
	dmghA=SelectCasualties(defArmy,attArmy,dmghA,BT,true);
	SelectCasualties(defArmy,attArmy,dmgA+dmghA,BT,false);
	if (isBoth){
		dmghD=SelectCasualties(attArmy,defArmy,dmghD,BT,true);
		SelectCasualties(attArmy,defArmy,dmghD+dmgD,BT,false);
	}
};

int CombatInterface::HowManyDices(Army *army, Unit* unit, Battle_Type BT){
	int result = 0;
	switch (BT){
		case bt_Space:
			if (unit->HasAbility(uaSpaceBattle))
				result=unit->GetAbility(uaSpaceBattle).field2;
			if (unit->HasAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,1))
				result=0;
			break;
		case bt_AssaultCannon:
			if (unit->Class==DR)
				result=unit->GetAbility(uaSpaceBattle).field2;
			break;
		case bt_Mentak:
			if (unit->HasAbility(uaMentak))
				result=unit->GetAbility(uaSpaceBattle).field2;
			break;
		case bt_Bombardment:
			if (unit->HasAbility(uaSpaceBattle)&&unit->HasAbility(uaBombard,1))
				result=unit->GetAbility(uaSpaceBattle).field2;
			break;
		case bt_AFB:
			if (unit->HasAbility(uaAFB,FIELD_SKIP,FIELD_SKIP,1))
				result=unit->GetAbility(uaAFB).field2;
			break;
		case bt_Invasion:
			if (unit->HasAbility(uaLandBattle))
				result=unit->GetAbility(uaLandBattle).field2;
			break;
		case bt_PDS:
			if ((army->GetPlanet()!=0)&&(unit->HasAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,1)))
				result=unit->GetAbility(uaCannon).field2;
			if ((army->GetPlanet()==0)&&(unit->HasAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,0)))
				result=unit->GetAbility(uaCannon).field2;
			break;
		case bt_DSC:
			if ((army->GetPlanet()!=0)&&(unit->HasAbility(uaDeepSpaceCannon,1)))
				result=unit->GetAbility(uaCannon).field2;
			if ((army->GetPlanet()==0)&&(unit->HasAbility(uaDeepSpaceCannon,0)))
				result=unit->GetAbility(uaCannon).field2;
			break;
	};
	return result;
};

/*void CombatInterface::StatusCheck(Army* army){
	PowExv<Unit>* temp = army->GetUnits();
	while (temp!=0){
		temp->status=0;
		temp=temp->next;
	};
};*/

/*int CombatInterface::ApplyDamage(Army* army, Army* target, Unit* unit){
	int d = 0;
	d=target->AssignDamage(unit);
	OnDamage(army,target,unit);
	//army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterAssignDamage,army,target,unit,1));
	target->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterAssignDamage,army,target,unit,0));
	army->CheckSupport();
	target->CheckSupport();
	army->RemoveKilledUnits();//удаление юнитов uaKilled
	target->RemoveKilledUnits();//
	return d;
};*/

/*void CombatInterface::OnDamage(Army *army, Army *target, Unit *unit){
	army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterAssignDamage,army,target,unit,1));
	target->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterAssignDamage,army,target,unit,0));
	army->CheckPasSupport();
	target->CheckPasSupport();
	if (unit->HasAbility(uaKilled)){
		if (!army->IsUnitInArmy(unit)&&!target->IsUnitInArmy(unit))
			cout<<"Kill unit SUM TING WONG"<<endl;
		if (target->IsUnitInArmy(unit))
			target->KillUnit(unit);
		if (army->IsUnitInArmy(unit))
			army->KillUnit(unit);
	}
	while (army->IsUnitWithAbility(uaKilled))
		OnDamage(army,target,army->GetUnitWithAbility(uaKilled,1));
	while (target->IsUnitWithAbility(uaKilled))
		OnDamage(army,target,target->GetUnitWithAbility(uaKilled,1));
};*/

int CombatInterface::ShowRolls(Army *army, Roll *rolls, int count){
	//PowExv<Unit>* temp=army->GetUnits();
	int k=0;
	bool pr=false;
	sprintf(str,"Player's %d{%s} rolls",army->GetOwner()->GetId(),army->GetOwner()->GetName().c_str());
	_Interface.PrintThingAll(str);
	//while (temp!=0){
	for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++){
		pr=false;
		for (int i=0; i<count; i++){
			if (rolls[i].unit == *iter){
				pr=true;
				sprintf(str,"%s (%d+): ",ShipsShort[(*iter)->Class].c_str(),rolls[i].power);
			}
		}
		if (pr){
			for (int i=0; i<count; i++){
				if (rolls[i].unit == *iter){
					sprintf(stra,"%d[%d] ",rolls[i].value, i+1);
					strcat(str,stra);
					k++;
				}
			}
			_Interface.PrintThingAll(str);
		}
		//temp=temp->next;
	}
	return k;
};

int CombatInterface::SelectCasualties(Army* target, Army* attacker, int dmg, Battle_Type BT, bool isHeavyDamage){
	int dmgC = dmg;
	Unit* unit;
	UnitAbType UAT;
	int isLand;
	char buff[255];
	if (target->isDefeated())
		return 0;
	if ((BT==bt_Space)||(BT==bt_AssaultCannon)||(BT==bt_Mentak)){
		if (!isHeavyDamage)
			UAT=uaSpaceBattle;//AD=ad_Space;
		else
			UAT=uaCapitalShip;//AD=ad_CapitalShips;
	};
	if (BT==bt_AFB)
		UAT=uaFighter;//AD=ad_Fighters;
	if (BT==bt_Invasion)
		UAT=uaLandBattle;//AD=ad_Invasion;
	if (BT==bt_PDS)
		if (target->GetPlanet()==0)
			UAT=uaSpaceBattle;//AD=ad_Space;
		else
			UAT=uaInvasion;//AD=ad_BeforeInvasion;//
	if (BT==bt_Bombardment)
		UAT=uaInvasion;//AD=ad_BeforeInvasion;
	_Interface.SetCurrPlayer(target->GetOwner()->GetId()-1);
	//Army* armies[] = {attacker, target};
	while ((dmgC>0)&&(target->IsUnitWithAbility(UAT))){
		if ((target != 0) && (attacker != 0))
			_InfoArea.DrawArmiesSystem(0,attacker);//fix for new funk
		//if ((BT==bt_AFB)||((BT==bt_Invasion)&&(target->StackSize(ST)>0))){//авто назначение урона
		if ((BT==bt_AFB)||(target->IsUnitWithAbility(uaFirstTarget))){//авто назначение урона
			if (BT==bt_AFB){
				while ((dmgC>0)&&(target->IsUnitWithAbility(uaFighter))){
					unit=target->GetUnitWithAbility(uaFighter,1);
					dmgC-=DamageUnit(target,unit);
					_Interface.PrintThingAll("Fighter was destroyed by Anti-Fighter Barrage");
				}
			}
			else{
				if (target->GetPlanet() != 0)
					isLand = 1;
				else
					isLand = 0;
				while ((dmgC>0) && target->IsUnitWithAbility(uaFirstTarget,isLand)){
					unit=target->GetUnitWithAbility(uaFirstTarget,isLand);
					dmgC-=DamageUnit(target,unit);
					sprintf(buff,"Damage was assigned to %s",ShipsFull[unit->Class].c_str());
					_Interface.PrintThingAll(buff);
				}
			}
		}
		else{ //игрок выбирает сам
			sprintf(str,"Player %d{%s} selects casualties. Damage left %d",target->GetOwner()->GetId(),target->GetOwner()->GetName().c_str(),dmgC);
			unit = SelectDialogOneUnit(str,target,false,UAT);
			sprintf(buff,"Player %s assigns damage to %s",target->GetOwner()->GetName().c_str(),ShipsShort[unit->Class].c_str());
			_Interface.PrintThingAll(buff);
			dmgC-=DamageUnit(target,unit);
		}
	}
	if (target->isDefeated()){
		sprintf(str,"Player's %d{%s} army was destroyed",target->GetOwner()->GetId(),target->GetOwner()->GetName().c_str());
		_Interface.PrintThingAll(str);
	}
	return dmgC;
};

int CombatInterface::GetPower(Battle_Type BT, Unit *un, Army *army){
	int result=0;
	UnitAbType UAT;
	switch (BT){
		case bt_Space:
		case bt_Mentak:
		case bt_Bombardment:
		case bt_AssaultCannon:
			UAT=uaSpaceBattle;
			break;
		case bt_Invasion:
			UAT=uaLandBattle;
			break;
		case bt_AFB:
			UAT=uaAFB;
			break;
		case bt_PDS:
		case bt_DSC:
			UAT=uaCannon;
			break;
	}
	if (HowManyDices(army,un,BT))
		result=un->GetAbility(UAT).field1;
	return result;
}

void CombatInterface::AutoRepairs(Army *army){
	Unit* unit;
	for (int i=1; i<=army->IsUnitWithAbility(uaAutoRepair); i++){
		unit = army->GetUnitWithAbility(uaAutoRepair,i);
		if (unit->HasAbility(uaSustain,1)){
			unit->AssignAbility(uaSustain,0);
			sprintf(str,"Unit %s auto-repairs",ShipsShort[unit->Class]);
			_Interface.PrintThingAll(str);
		}
	}
}

int CombatInterface::Retreat(Army *army){
	_Interface.SetCurrPlayer(army->GetOwner()->GetId()-1);
	Hex* hex = army->GetHex();
	Hex* toRetreat = 0;
	Army* fleet = 0;
	Unit* unit = 0;
	Army* whereretreat;
	int x=0;
	int y=0;
	bool selecting = true;
	while (selecting){
		vector<int> tempvec = _GrIn.SysChoise("Select system to retreat");
		x = tempvec[0];
		y = tempvec[1];
		toRetreat = _Map.GetHexh(x,y);
		if (hex->GetLinkedHexes()->GetLink(toRetreat) == ltNone){
			_Interface.PrintThingAll("You have to retreat to adjacent system with your current system");
			continue;
		}
		whereretreat = FindArmy(toRetreat,0,false,0);
		if (whereretreat != 0){
			if (whereretreat->GetOwner() != army->GetOwner()){
				_Interface.PrintThingAll("System for retreatment must be empty or with your fleet");
				continue;
			}
		}
		if (!army->GetOwner()->GetMoveStats()->active[toRetreat->GetDanger()]){
			_Interface.PrintThingAll("This system cann't be activated");
			continue;
		}
		if (!toRetreat->GotCC(army->GetOwner()->GetId())){
			if (army->GetOwner()->GetCountersSA()>0){
				if (!SelectDialogYesNo("This system isn't activated. Activate it for retreatment?")){
					continue;
				}
			}
			else{
				_Interface.PrintThingAll("This system isn't activated. You have no SACC for its activaion");
				continue;
			}
		}
		//выполнение отступления
		if (!toRetreat->GotCC(army->GetOwner()->GetId())){
			toRetreat->SetCC(army->GetOwner()->GetId());//активация системы
			army->GetOwner()->TakeCounter(0);
		}
		selecting = false;
		fleet = FindAllyArmy(army->GetOwner(),toRetreat);
		if (fleet==0)
			fleet = NewArmy(army->GetOwner(),toRetreat);
		while (army->IsUnitWithAbility(uaCapitalShip)){//перенос кораблей
			unit = army->GetUnitWithAbility(uaCapitalShip,1);
			army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Movement,army,unit));
			if (unit->HasAbility(uaKilled)){
				DestroyUnit(army,unit);
				continue;
			}
			MoveUnit(army,fleet,unit);
		}
		while (army->IsUnitWithAbility(uaFighter)){//перенос истребов
			unit = army->GetUnitWithAbility(uaFighter,1);
			army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_Movement,army,unit));
			if (unit->HasAbility(uaKilled)){
				DestroyUnit(army,unit);
				continue;
			}
			MoveUnit(army,fleet,unit);
		}
		army->KillArmy();
		//CheckTradeStations(toRetreat,army->GetOwner());
		CheckTradeStations();
		army->GetOwner()->CheckFleets();
	}
	return 1;
};

bool CombatInterface::CanRetreat(Army *army){
	bool common = false;
	bool tactical = false;
	Army* here;
	for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++){
		if ((army->GetHex()->GetLinkedHexes()->GetLink(*hiter)!=ltNone)&&(army->GetOwner()->GetMoveStats()->active[(*hiter)->GetDanger()])){//пофиксить
			here = FindArmy(*hiter,0,false,0);
			if (here != 0)
				if (here->GetOwner() != army->GetOwner())
					continue;
			if ((*hiter)->GotCC(army->GetOwner()->GetId()))
				common=true;
			else
				if (army->GetOwner()->GetCountersSA()>0)
					tactical=true;
		}
	}
	return (common||tactical);
};

int CombatInterface::CheckFleet(Army *army){
	if (army->GetPlanet()!=0)
		return 0;

	return 1;
};

int CombatInterface::DamageUnit(Army *army, Unit *unit){
	int d = army->AssignDamage(unit);
	if (unit->HasAbility(uaKilled))
		DestroyUnit(army,unit);
	return d;
}

int CombatInterface::DestroyUnit(Army* army, Unit* unit){
	Army* opponent = FindOpponentArmy(army);
	army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterAssignDamage,army,opponent,unit,0));
	if (opponent!=0)
		opponent->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterAssignDamage,army,opponent,unit,1));
	army->CheckFleetSupport();
	army->CheckPasSupport();
	if (unit != 0)
		unit->AddAbility(uaKilled,1);
	if (army->IsUnitWithAbility(uaKilled,0))
		DestroyUnit(army,army->GetUnitWithAbility(uaKilled,1,0));
	if ((opponent!=0)&&(opponent->IsUnitWithAbility(uaKilled,0)))
		DestroyUnit(opponent,opponent->GetUnitWithAbility(uaKilled,1,0));
	army->RemoveKilledUnits();
	if (opponent!=0)
		opponent->RemoveKilledUnits();
	return 1;
}

int CombatInterface::ScuttleUnit(Army* army, Unit* unit){
	return 1;
}

int CombatInterface::FleetSupplyCheck(Army* army){
	army->CheckFleetSupport();
	army->CheckPasSupport();
	if (army->IsUnitWithAbility(uaKilled))
		DestroyUnit(army,army->GetUnitWithAbility(uaKilled,1,0));
	return 1;
};