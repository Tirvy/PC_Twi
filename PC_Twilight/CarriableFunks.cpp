
void RelocateCarriable(Army* army,Unit*carrier){
	int i,parmynumber=0,CarryCap = 0;
	int x,y;
	Player* player = army->GetOwner();
	vector<Army*> parmies;
	Unit* unit;
	UnitAbility cartype = carrier->GetAbility(uaCarrier);
	UnitAbType UAT;
	for (i=0;i<MAX_PLANETS;++i){
		if (army->GetHex()->GetPlanet(i+1) != 0){
			parmies.push_back(FindArmy(army->GetHex(),player,false,army->GetHex()->GetPlanet(i+1)));
			++parmynumber;
		}
	}
	if (cartype.field1>0)
		UAT = uaCarried;
	if (cartype.field2>0)
		UAT = uaFighter;
	if (cartype.field3>0)
		UAT = uaInfantry;
	while (true){
		army->GetHex()->GetCoords(&x,&y);
		PowDEV<Unit,Army> carry = SelectDialogOneUnit("Choose a unit to place on carrier",x,y,UAT,true,true,carrier);
		if ((carry.elem1 == 0) || (carry.elem2 == 0))
			break;
		if (army->IsFreePlace(carrier,carry.elem1)){
			cout<<"Is free place1 "<<army->IsFreePlace(carrier,carry.elem1)<<endl;
			unit = MoveUnit(carry.elem2,army,carry.elem1);
			cout<<"set pass "<<endl;
			if (!army->SetPassenger(carrier,unit))
				break;
			carry.elem1 = 0;
			carry.elem2 = 0;
			cout<<"Is free place2 "<<endl;
		}
		else{
			_Interface.PrintThingAll("No free space in carrier for this unit");
			break;
		}
	}
		/*fr = _Interface.FreeRoam(it_csu,&x,&y,&z);
		if (fr == frr_confirm){
			_Interface.PrintThingAll("Relocations confirmed");
			break;
		}
		if (fr == frr_pass){
			_Interface.PrintThingAll("Relocations passed (still not functional)");//SIC(!)
			break;
		}
		if (z>parmynumber){
			_Interface.PrintError("There is no such planet");
			continue;
		}
		if ((z>0)&&(parmies[z-1] == 0)){
			_Interface.PrintError("There is no your units on this planet");
			continue;
		}
		if (z == 0)
			warmy = army;
		if (z > 0)
			warmy = parmies[z-1]->elem;
		if (warmy->GetUnit(y) == 0){
			_Interface.PrintError("There is no such unit in here");
			continue;
		}
		ut = warmy->GetUnit(y)->Class;
		if (!IsCarriable((UnitType)ut)){
			_Interface.PrintError("Cant be transported");
			continue;
		}*/
		/*if (carry.elem1->IsAbility(uaInfantry))
			if (carrier->GetAbility(uaCarrier)->field3>0)
				CarryCap=carrier->GetAbility(uaCarrier)->field3;
			else
				if (carrier->GetAbility(uaCarrier)->field1>0)
					CarryCap=carrier->GetAbility(uaCarrier)->field1;
				else
					_Interface.PrintThingAll("Not a Carrier-Type for this unit");
		if (carry.elem1->IsAbility(uaFighter))
			if (carrier->GetAbility(uaCarrier)->field2>0)
				CarryCap=carrier->GetAbility(uaCarrier)->field2;
			else
				if (carrier->GetAbility(uaCarrier)->field1>0)
					CarryCap=carrier->GetAbility(uaCarrier)->field1;
				else
					_Interface.PrintThingAll("Not a Carrier-Type for this unit");

		CarryCap = army->GetOwner()->GetUnitStats()->GetParametr(carrier->Class,sCP);
		if (ut==GF)
			CarryCap += player->GetUnitStats()->GetParametr(carrier->Class,sGFCP);
		if (ut==FG)
			CarryCap += player->GetUnitStats()->GetParametr(carrier->Class,sFGCP);
		if (CarryCap == 0 ){
			_Interface.PrintThingAll("Not a Carrier-Type for this unit");
			continue;
		}
		if (CarryCap - army->GetPassenger(carrier)->Number() <= 0 ){
			_Interface.PrintThingAll("This carrier is full of this stuff");
			continue;
		}*/
		//unit = warmy->GetUnit(y);
		//unit = MoveUnit(carry.elem2,army,carry.elem1);
		//army->SetPassenger(carrier,unit);
		//carry.elem1 = 0;
		//carry.elem2 = 0;
}

void RelocateCarriable(Player*player,Hex*system){
	int i,parmynumber=0,CarryCap = 0;
	int x,y,z,fr,ut;
	vector<Army*> parmies;
	parmies.clear();
	Army* army,*warmy;
	Unit* unit;
	spawnarmy sarmy;
	army = FindArmy(system,player);
	for (i=0;i<MAX_PLANETS;++i){
		if (army->GetHex()->GetPlanet(i+1) != 0){
			parmies.push_back(FindArmy(army->GetHex(),player,false,army->GetHex()->GetPlanet(i+1)));
			++parmynumber;
		}
	}
	while (true){
		system->GetCoords(&x,&y);
		_Interface.PrintThingAll("Choose a unit to relocate");
		fr = _Interface.FreeRoam(it_csu,&x,&y,&z);
		if (fr == frr_confirm){
			_Interface.PrintThingAll("Relocations confirmed");
			break;
		}
		if (fr == frr_pass){
			_Interface.PrintThingAll("Relocations passed (still not functional)");//SIC(!)
			break;
		}
		if (z>parmynumber){
			_Interface.PrintError("There is no such planet");
			continue;
		}
		if ((z>0)&&(parmies[z-1] == 0)){
			_Interface.PrintError("There is no your units on this planet");
			continue;
		}
		if (z == 0)
			warmy = army;
		if (z > 0)
			warmy = parmies.at(z-1);
		if (warmy->GetUnit(y) == 0){
			_Interface.PrintError("There is no such unit in here");
			continue;
		}
		ut = warmy->GetUnit(y)->Class;
		if (!IsCarriable((UnitType)ut)){
			_Interface.PrintError("Cant be transported");
			continue;
		}
		unit = warmy->GetUnit(y);
		warmy->KillUnit(unit);
		sarmy.unit[ut]=1;
		Spawn(&sarmy,player,system);
	}
}

int ZoldnRelocateCarriable(Army* army, Unit* unit){
	vector<Army*> places;
	Army* tarmy;
	Unit* zunit;
	char str[255];
	char stra[255];
	vector<Unit*>* tunit;
	places.clear();
	places.push_back(army);
	int i,j,k;
	UnitSelection US;
	vector<UnitSelection> options;
	options.clear();
	for (i = 1; i <= MAX_PLANETS; i++){
		tarmy = 0;
		if (army->GetHex()->GetPlanet(i) != 0){
			tarmy = FindAllyArmy(army->GetOwner(),army->GetHex(),army->GetHex()->GetPlanet(i));
			if (tarmy != 0)
				places.push_back(tarmy);
		}
	}
	int mask[MAX_UNIT];
	while (true){
		options.clear();
		_GrIn.InitChoise("Select units to pick up",true,true,true);
		for (vector<Army*>::iterator iter = places.begin(); iter != places.end(); iter++){
			for (i = 0; i <MAX_UNIT; i++)
				mask[i] = 0;
			tunit = (*iter)->GetUnits();
			for (vector<Unit*>::iterator ziter = tunit->begin(); ziter != tunit->end(); ziter++)
				if (((*ziter)->carrier != unit) && ((*ziter)->HasAbility(uaCarried)))
					mask[(*ziter)->Class] = mask[(*ziter)->Class] + 1;
			cout<<"Pick up"<<endl;
			for (UnitType UT = GF; UT < MAX_UNIT; UT = (UnitType)((int)UT + 1)){
				if (mask[UT]){
					if ((*iter)->GetUnit(UT)->HasAbility(uaMultiple)){
						sprintf(str,"%s",ShipsShort[UT].c_str());
						if (mask[UT]){
							sprintf(stra," x%d",mask[UT]);
							strcat(str,stra);
						}
						if ((*iter)->GetPlanet()){
							sprintf(stra,"(%s)",(*iter)->GetPlanet()->GetName().c_str());
							strcat(str,stra);
						}
						_GrIn.AddNumerical(SHIPS_IMG[UT],str);
						US.UT = UT;
						US.army = *iter;
						US.multiple = true;
						US.n = mask[UT];
						US.selected = 0;
						US.unit = 0;
						options.push_back(US);
					}
					else{
						for (j = 1; j <= mask[UT]; j++){
							sprintf(str,"%s",ShipsShort[UT].c_str());
							if (((*iter)->GetUnit(UT,j)->HasAbility(uaSustain))&&((*iter)->GetUnit(UT,j)->GetAbility(uaSustain).field1))
								strcat(str,"(dmg)");
							if ((*iter)->GetPlanet()){
								sprintf(stra,"(%s)",(*iter)->GetPlanet()->GetName().c_str());
								strcat(str,stra);
							}
							_GrIn.AddNumerical(SHIPS_IMG[UT],str);
							US.UT = UT;
							US.army = *iter;
							US.n = 1;
							US.unit = (*iter)->GetUnit(UT,j);
							US.selected = 0;
							US.multiple = false;
							options.push_back(US);
						}
					}
				}
			}
		}
		vector<int> ret = _GrIn.LaunchChoise();
		/// retiter;
		int gf = 0, fg = 0, other = 0, common = 0;
		if (ret.size() == 0)
			//return -1;
			break;
		
		i = 0;
		vector<int>::iterator retiter = ret.begin();
		bool loading = false;
		for (vector<UnitSelection>::iterator iter = options.begin(); iter != options.end(); iter++){
			if (ret.at(i)){
				switch (iter->UT){
					case GF:
					case ST:
						gf+=ret.at(i);
						common+=ret.at(i);
						break;
					case FG:
						fg+=ret.at(i);
						common+=ret.at(i);
						break;
					default:
						common+=ret.at(i);
						other+=ret.at(i);
				}
			}
			i++;
		}
		vector<Unit*> vunit = army->GetPassengers(unit);
		for (vector<Unit*>::iterator iter = vunit.begin(); iter != vunit.end(); iter++){
			switch ((*iter)->Class){
				case GF:
				case ST:
					gf++;
					common++;
					break;
				case FG:
					fg++;
					common++;
					break;
				default:
					common++;
					other++;
			}
		}
		cout<<"Zoldn Carried "<<gf<<" "<<fg<<" "<<other<<" "<<common<<endl;
		if (unit->GetAbility(uaCarrier).field1){
			if (!unit->HasAbility(uaUnlimGF))
				if (unit->GetAbility(uaCarrier).field1 < common)
					_Interface.PrintThingAll("Can't upload: too much units");
				else
					loading = true;
			else
				if (unit->GetAbility(uaCarrier).field1 < (common - gf))
					_Interface.PrintThingAll("Can't upload: too much units");
				else
					loading = true;
		}
		else if (unit->GetAbility(uaCarrier).field2){
			if ((unit->GetAbility(uaCarrier).field2 < fg) && (fg == common))
				_Interface.PrintThingAll("Can't upload: too much units or try load not fighters");
			else
				loading = true;
		}
		else if (unit->GetAbility(uaCarrier).field3){
			if ((unit->GetAbility(uaCarrier).field3 < gf) && (gf == common))
				_Interface.PrintThingAll("Can't upload: too much units or try load not infantry");
			else
				loading = true;
		}
		if (!loading)
			//return 0;
			continue;
		i = 0;
		for (vector<UnitSelection>::iterator iter = options.begin(); iter != options.end(); iter++){
			if (ret.at(i) > iter->n){
				iter->selected = iter->n;
				_Interface.PrintThingAll("Warning: trying to pick up more units than exist, moving all available");
			}
			else
				iter->selected = ret.at(i);
			i++;
		}
		for (vector<UnitSelection>::iterator iter = options.begin(); iter != options.end(); iter++){
			if (iter->selected){
				if (iter->multiple){
					for (j = 1; j <= iter->selected; j++){
						k = 1;
						while (iter->army->GetUnit(iter->UT,k)->carrier == unit)
							k++;
						zunit = MoveUnit(iter->army,army,iter->army->GetUnit(iter->UT,k));
						army->SetPassenger(unit,zunit);
					}
				}
				else{
					zunit = MoveUnit(iter->army,army,iter->unit);
					army->SetPassenger(unit,zunit);
				}
			}
		}
		break;
	}
	return 1;
}

int FreeCapacity(Player*player,Army*army,Unit*unit){
	int CarryCap;
	if (!unit->HasAbility(uaCarrier))
		return 0;
	CarryCap = unit->GetAbility(uaCarrier).field1;
	CarryCap += unit->GetAbility(uaCarrier).field2;
	CarryCap += unit->GetAbility(uaCarrier).field3;
	return (CarryCap - army->GetPassengers(unit).size());
}