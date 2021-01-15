/*enum UnitAbType {uaSpaceBattle, uaLandBattle, uaInfantry, uaCarried
	uaFirstTarget, uaStructure, uaProduction, uaCarrier,
	uaCapitalShip, uaCannon, uaSustain, uaAFB, uaBombard, uaProdCount, uaHeavyShip,
	uaLightShip, uaHyperDrive, uaAutoRepair, uaCritical, uaHeavyDamage, uaLimitOnPlanet,
	uaDamagedPenalty, uaEvasion

};*/
//type = 0 - создание юнита
//type = 1 - обновление боевых абилок
//type = 2 - обновление летных абилок
void InitialAbilities(Unit* unit, int type, Army* army){
	UnitType UT = unit->Class;
	UnitAbType UAT;
	unit->AddAbility(uaNone);
	if (FM!=UT){
		if (type<=1){//боевые абилки, которые часто изменяются
			if ((army->GetOwner()->GetUnitStats()->GetParametr(UT,sHP)>1) && (!unit->HasAbility(uaSustain)))
				unit->AddAbility(uaSustain,0,1,1);
			if (UT<=ST)
				UAT = uaLandBattle;
			if (UT==PDS)
				UAT = uaCannon;
			if ((UT>=FG)&&(UT<=WS))
				UAT = uaSpaceBattle;
			unit->AddAbility(UAT,defStat[UT][sPW],defStat[UT][sSH]);
			if (UT==DS)
				unit->AddAbility(uaAFB,9,2);
			if (UT==PDS)
				unit->AssignAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,1);
		}
		if ((type==0)||(type==2)){//скорости
			if ((UT>=DS)&&(UT<=WS)){
				unit->AddAbility(uaHyperDrive,defStat[UT][sSP]);
				unit->AddAbility(uaSupply);
			}
			switch (UT){
				case CR:
				case WS:
					unit->AddAbility(uaCarrier,6,0,0);
					break;
				case FG:
					unit->DeleteAbility(uaHyperDrive);
					unit->DeleteAbility(uaSupply);
					break;
				case DCK:
					unit->DeleteAbility(uaHyperDrive);
					unit->DeleteAbility(uaSupply);
					unit->AddAbility(uaCarrier,0,3,0);
					break;
				case CS:
				case DR:
					unit->DeleteAbility(uaCarrier);
					break;
			}
		}
		if ((type==3)||(type==0)){
			switch (UT){
				case DCK:
					if (unit->HasAbility(uaProduction))
						unit->AssignAbility(uaProduction,0);
					else
						unit->AddAbility(uaProduction,0,1,1);
				break;
			}
		}
		if (type==0){
			//if (army->GetOwner()->GetUnitStats()->GetParametr(UT,sHP)>1)
			//	unit->AddAbility(uaSustain,0,1,1);
			switch (UT){
				case GF:
					unit->AddAbility(uaInfantry);
					unit->AddAbility(uaCarried,1);
					unit->AddAbility(uaNeedSupport,0);
					unit->AddAbility(uaDropped);
					unit->AddAbility(uaInvasion);
					unit->AddAbility(uaMultiple);
					break;
				case MU:
					unit->AddAbility(uaCarried,1);
					unit->AddAbility(uaNeedSupport,0);
					unit->AddAbility(uaDropped);
					unit->AddAbility(uaInvasion);
					break;
				case ST:
					unit->AddAbility(uaInfantry);
					unit->AddAbility(uaCarried,1);
					unit->AddAbility(uaNeedSupport,0);
					unit->AddAbility(uaDropped);
					unit->AddAbility(uaInvasion);
					unit->AddAbility(uaFirstTarget,1);
					unit->AddAbility(uaMultiple);
					break;
				case PDS:
					unit->AddAbility(uaCannon,FIELD_SKIP,FIELD_SKIP,1);
					unit->AddAbility(uaStructure);
					unit->AddAbility(uaCarried,1);
					unit->AddAbility(uaNeedSupport,0);
					unit->AddAbility(uaLimitOnPlanet,2);
					unit->AddAbility(uaDropped);
					unit->AddAbility(uaPlanetaryShield);
					break;
				case FG:
					unit->AddAbility(uaCarried,0);
					unit->AddAbility(uaNeedSupport,1);
					unit->AddAbility(uaMultiple);
					unit->AddAbility(uaFighter);
					break;
				case DS:
					unit->AddAbility(uaCapitalShip);
					unit->AddAbility(uaLightShip);
					break;
				case CS:
					unit->AddAbility(uaCapitalShip);
					unit->AddAbility(uaLightShip);
					break;
				case CR:
					unit->AddAbility(uaCapitalShip);
					//unit->AddAbility(uaCarrier,6,0,0);
					break;
				case DR:
					//unit->AddAbility(uaDamagedPenalty,0,1);
					unit->AddAbility(uaCapitalShip);
					unit->AddAbility(uaBombard,0,0,0);
					unit->AddAbility(uaDreadnought);
					unit->AddAbility(uaHeavyShip);
					break;
				case WS:
					unit->AddAbility(uaCapitalShip);
					//unit->AddAbility(uaCarrier,6,0,0);
					unit->AddAbility(uaBombard,0,1,1);
					unit->AddAbility(uaHeavyShip);
					break;
				case DCK:
					unit->AddAbility(uaStructure);
					unit->AddAbility(uaProduction,0,1,1);
					unit->AddAbility(uaLimitOnPlanet,1);
					//unit->AddAbility(uaCarrier,0,3,0);
					break;
			}
		}
	}
	else{
		FlagshipAbilities(unit,type,army);
	}
	if ((type == 0) || (type == 2))
		if (army->GetOwner() != 0)
			army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterRefreshAbilities,army,unit));
}

void FlagshipAbilities(Unit* unit, int type, Army* army){
	RacesType RT;
	if ((army->GetOwner()!=0)&&(army->GetOwner()->GetRace()!=MAX_RACE)){
		RT = army->GetOwner()->GetRace();
		if (type<=1){
			unit->AddAbility(uaSpaceBattle,FMstats[RT][sPW],FMstats[RT][sSH]);
			if (RT==Saar)
				unit->AddAbility(uaAFB,6,4,0);
		}
		if ((type==2)||(type==0)){
			unit->AddAbility(uaHyperDrive,FMstats[RT][sSP]);
			unit->AddAbility(uaSupply);
		}
		if ((type==3)||(type==0)){
			switch (RT){
				case Arborec:
					unit->AddAbility(uaProduction,5,0,1);
					break;
			}
		}
		if (type==0){
			unit->AddAbility(uaSustain,0,1,1);
			unit->AddAbility(uaCapitalShip);
			unit->AddAbility(uaCarrier,FMstats[RT][sCP]);
			switch (RT){
				case Letnev:
					unit->AddAbility(uaBombard,0,1,1);
					unit->AddAbility(uaAutoRepair);
					break;
				case JolNar:
					unit->AddAbility(uaCritical,3);
					break;
				case Sol:
					unit->AddAbility(uaUnlimGF);
					break;
				case Xxcha:
					unit->AddAbility(uaCannon,6,2,0);
					unit->AddAbility(uaDeepSpaceCannon,0);
					break;
				case Saar:
					unit->AddAbility(uaAFB,6,4);
					break;
				case Arborec:
					unit->AddAbility(uaProduction,5,0,1);
					break;
			}
			if (army->GetOwner() != 0)
				army->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_AfterRefreshAbilities,army,unit));
		}
	}
}

void RefreshArmyAbilities(Army* army, int type){
	for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++)
		InitialAbilities(*iter,type,army);
}

void RefreshArmyAbilities(Player* player, int type){
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if ((*aiter)->GetOwner() == player)
			RefreshArmyAbilities(*aiter,type);
}