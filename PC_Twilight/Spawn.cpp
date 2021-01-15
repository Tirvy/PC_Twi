int Spawn(spawnarmy* UT, Player*player, Hex* hex){
	vector<Army*> parmies;
	parmies.clear();
	int parmynumber;
	//int k = _Map.GetMaxRadius();
	int i,j,l,n,chosen;
	int x, y;
	bool DontActuallyCare;
	Unit* nCarrier;
	Unit* nUnit;
	_Interface.SetCurrPlayer(player->GetId() - 1);
	Army* tarmy;
	Army* army = FindArmy(hex,player,true);
	for (i=DS;i<=FM;++i){
		for (j = 0; j<UT->unit[i]; ++j){		
			nUnit = army->AddUnit((UnitType)i);
			InitialAbilities(nUnit,0,army);
		}
		UT->unit[i] = 0;
	}
	_Interface.PrintToSpawn(UT);
	
	if (!hex->GetCoords(&x,&y))
		throw throwable("spawn: wrong coords");
	
	parmynumber = 0;
	for (i = 1; i <= MAX_PLANETS; ++i){
		if (hex->GetPlanet(i) != 0){
			tarmy = FindArmy(hex,player,true,hex->GetPlanet(i));
			parmies.push_back(tarmy);
			parmynumber++;
		}
	}
	DontActuallyCare = true; // happy debug!
	for (i=MAX_UNIT-1;i>=GF;--i){
		while (UT->unit[i] != 0){
			//cout<<">     Spawning "<<"[ "<<ShipsFull[i]<<" ]"<<endl;
			if (((parmynumber>1)||(i==FG))&&(!DontActuallyCare)){
				_Interface.ViewSystemArmies(x,y);
				l=y;
				j=x;
				/*if ((i==DCK)&&(_Interface.FreeRoam(it_csp,&j,&l) == 2)){
					DontActuallyCare = true;
				}
				if ((i!=DCK)&&(_Interface.FreeRoam(it_csc,&j,&l) == 2)){
					DontActuallyCare = true;
				}*/
			}
			else{
				j = 'p';
				l = 1;
			}
			if (DontActuallyCare){
				if (i==DCK){
					chosen = -1;
					for (n=1;n<=MAX_PLANETS;++n)
						if (((chosen==-1)&&(StackSize(DCK,player,hex,hex->GetPlanet(n)) == 0)) || ((chosen!=-1)&&(hex->GetPlanet(n)!=0)&&(hex->GetPlanet(n)->GetRes() > hex->GetPlanet(chosen)->GetRes())&&(StackSize(DCK,player,hex,hex->GetPlanet(n)) == 0)))
							chosen = n;
					if (chosen == -1)
						throw throwable("int spawn no place for Dock");
					j = 'p';
					l = chosen;
				}
				/*else if (i==FG){
					_Interface.ViewSystemArmies(x,y);
					l=y;
					j=x;
					_Interface.FreeRoam(it_csc,&j,&l);
				}*/
				else if (i==FG){
					j = 'f';
				}
				else{
					j = 'p';
					l = 1;
				}
			}
			if ((j=='p')&&((l>3)||(l<1)||(parmies.at(l-1)==0)))
				throw throwable("int spawn: Not a good planet");
			if ((j=='p')&&(i==FG)){
				_Interface.PrintThingAll("Fighers cant land on planets");
				continue;
			}
			if ((i==DCK)&&(parmies.at(l-1)->StackSize(DCK)>0)){
				_Interface.PrintThingAll("Already has a dock");
				continue;
			}
			if ((i==DCK)&&(!player->CanBuildDock(hex->GetPlanet(l)))){
				_Interface.PrintThingAll("Dock can not be placed here");
				continue;
			}
			nUnit = 0;
			if (j=='f'){
				nUnit = army->AddUnit((UnitType)i);//->elem
				//army->elem->CheckSupport();
			}
			else if (j=='p')
				nUnit = parmies.at(l-1)->AddUnit((UnitType)i);//parmies[l-1]->elem->
			else if (j=='u'){
				nCarrier = army->GetUnit(l);
				int CarryCap = 0;
				CarryCap += player->GetUnitStats()->GetParametr(nCarrier->Class,sCP);
				if (i==GF)
					CarryCap += player->GetUnitStats()->GetParametr(nCarrier->Class,sGFCP);
				if (i==FG)
					CarryCap += player->GetUnitStats()->GetParametr(nCarrier->Class,sFGCP);
				if (CarryCap == 0 ){
					_Interface.PrintThingAll("Not a Carrier-Type for this unit");
					continue;
				}
				if (CarryCap - army->GetPassengers(nCarrier).size() <= 0 ){
					_Interface.PrintThingAll("New Carrier is full");
					continue;
				}
				nUnit = army->AddUnit((UnitType)i);
				army->SetPassenger(nCarrier,nUnit);
			}
			else
				throw throwable("spawn: Carrier-Type is not a unit nor planet");
			--(UT->unit[i]);
		}
	}
	return 1;
}

