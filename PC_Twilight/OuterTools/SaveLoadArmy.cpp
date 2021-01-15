list<string> SaveArmy(Army* army){
	int x,y,planet,owner;
	//PowExv<Unit>* unit = army->GetUnits();
	list<string> save;
	save.clear();
	string st("<army>");
	char ct[257];
	save.push_back(st);
	army->GetHex()->GetCoords(&x,&y);
	if (army->GetPlanet()==0)
		planet = 0;
	else
		for (int i=1; i<=MAX_PLANETS; i++)
			if (army->GetHex()->GetPlanet(i)==army->GetPlanet())
				planet = i;
	if (army->GetOwner()==0)
		owner = 0;
	else
		owner = army->GetOwner()->GetNumber();
	sprintf(ct,"construct %d %d %d %d",x,y,planet,owner);
	save.push_back(ct);
	int sustain, damage;
	//while (unit!=0){
	for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++){
		if ((*iter)->HasAbility(uaSustain)){
			sustain = 1;
			damage = (*iter)->GetAbility(uaSustain).field1;
		}
		else{
			sustain = 0;
			damage = 0;
		}
		sprintf(ct,"unit %d %d %d %d",(*iter)->Class,army->GetUnitNumber((*iter)->carrier),sustain,damage);
		save.push_back(ct);
		//unit=unit->next;
	}
	save.push_back("</army>");
	return save;
};

int LoadArmy(list<string>::iterator begin, list<string>::iterator end){
	int x,y,owner,planet;
	string check;
	int i1,i2,i3,i4;
	list<string>::iterator iter = begin;
	list<string>::iterator units = begin;
	int k=0;
	iter++;
	std::istringstream iss(*iter);
	iss>>check>>x>>y>>planet>>owner;
	Player* player = 0;
	if ((owner!=0)&&(owner<=_GameStats.GetPlayersNumber()))
		player = _Players[owner-1];
	if (owner==0)
		player = _GameStats.GetNeutralPlayer();
	Hex* hex = _Map.GetHexh(x,y);
	Planet* plan = 0;
	if (planet != 0)
		plan = hex->GetPlanet(planet);
	Army* army = NewArmy(player,hex,plan);
	iter++;
	units = iter;
	Unit* unit;
	while (iter!=end){
		
		iss.clear();
		iss.str(*iter);
		iss>>check>>i1>>i2>>i3>>i4;
		if (check=="</army>")
			break;
		unit = army->AddUnit((UnitType)i1);
		if (i3)
			unit->AddAbility(uaSustain,i4,1,1);
		iter++;
	} 
	k=0;
	iter = units;
	while (iter!=end){
		iss.clear();
		iss.str(*iter);
		iss>>check>>i1>>i2>>i3>>i4;
		if (check=="</army>")
			break;
		k++;
		if ((i2!=0)&&(army->GetUnit(i2)!=0))
			army->SetPassenger(army->GetUnit(i2),army->GetUnit(k));
		iter++;
	}
	return 1;
};

int ShowArmy(list<string> save){
	list<string>::iterator iter;
	cout<<endl<<"Army save debug"<<endl;
	for (iter = save.begin(); iter != save.end(); ++iter)
		cout<<(*iter)<<endl;
	return 1;
};

list<string> SaveArmies(){
	list<string> save;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		save.splice(save.end(),SaveArmy(*aiter));
	return save;
};

int LoadArmies(list<string> save){
	list<string>::iterator iter = save.begin();
	list<string>::iterator iter2 = save.begin();
	list<string>::iterator begin;
	list<string>::iterator end;
	std::istringstream iss;
	string check;
	while (iter!=save.end()){
		iss.clear();
		iss.str(*iter);
		iss>>check;
		if (check=="<army>"){
			iter2 = iter;
			begin = ++iter2;
		}
		if (check=="</army>"){
			iter2 = iter;
			end = --iter2;
			LoadArmy(begin,end);
		}
		iter++;
	}
	return 1;
}