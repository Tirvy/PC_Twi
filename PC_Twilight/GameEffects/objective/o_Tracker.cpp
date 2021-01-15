o_Tracker::o_Tracker(){
	id = "Tracker";
	reset();
}
void o_Tracker::reset(){
	_DestroyedEnemyUnits.clear();
	_DestroyedEnemyUnits.resize(MAX_UNIT);
	_Infiltrator = 0;
	_Invaders = 0;
	_Traitor = 0;
	_Merciless = 0;
	_Invasions = 0;
	_SpaceBattles = 0;
	_DocksUnderAttack = 0;
	_PDSUnderAttack = 0;
	_SpaceBattlesFlag = false;
	_InvasionsFlag = false;
	_CapturedPlanets.clear();
	_DestroyedDocks.clear();
}
void o_Tracker::show(Player* player){
	int i;
	if (player != 0)
		cout<<"Tracker: player "<<player->GetName()<<endl;
	cout<<"Tracker: Destroyed units - ";													//+
	for (i = 0; i < _DestroyedEnemyUnits.size(); i++)
		cout<<ShipsShort[i]<<" "<<_DestroyedEnemyUnits[i]<<" ";
	cout<<endl;
	cout<<"Tracker: killed ships near enemy HS "<<_Infiltrator<<endl;						//+
	cout<<"Tracker: captured enemy planets "<<_Invaders<<endl;								//+
	cout<<"Tracker: attacks players with trade agreement break "<<_Traitor<<endl;			//+
	cout<<"Tracker: destroyed last dock "<<_Merciless<<endl;								//+
	cout<<"Tracker: successful invasions on planets with army "<<_Invasions<<endl;			//+
	cout<<"Tracker: victories against fleet with at least 3 ships "<<_SpaceBattles<<endl;	//+
	cout<<"Tracker: captured planets - ";													//+
	for (i = 0; i < _CapturedPlanets.size(); i++)
		cout<<_CapturedPlanets.at(i)->GetName()<<" ";
	cout<<endl;
	cout<<"Tracker: Destroyed Docks of players - ";													//+
	for (i = 0; i < _DestroyedDocks.size(); i++)
		cout<<_DestroyedDocks.at(i)->GetName()<<" ";
	cout<<endl;
}
bool o_Tracker::GetQ(GameEffectQs queue){
	if (queue == eq_LoadGame)
		return true;
	if ((queue==eq_StrategyEnd) || (queue == eq_ActionStart))
		return true;
	if ((queue==eq_AfterAssignDamage) || (queue == eq_OnCapture) || (queue == eq_BeforeCapture))
		return true;
	if ((queue == eq_BattleStart) || (queue == eq_BattleEnd))
		return true;
	if (queue == eq_PlanetDestroyed)
		return true;
	if (queue == eq_ObjectiveTracker)
		return true;
	return false;
}
GameEffectRets o_Tracker::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Army* army = EP.army1;
	Army* opponent = EP.army2;
	Unit* unit = EP.unit;
	Planet* planet = EP.planet;
	int isAttacker = EP.attacker;
	std::istringstream iss(_loadstring);
	int i,d,k,dx,dy,dk;
	string q;
	if (Q == eq_LoadGame){
		iss>>q;
		iss>>_Infiltrator;
		iss>>_Invaders;
		iss>>_Traitor;
		iss>>_Merciless;
		iss>>_Invasions;
		iss>>_SpaceBattles;
		for (i = 0; i < MAX_UNIT; i++){
			iss>>d;
			_DestroyedEnemyUnits[i] = d;
		}
		iss>>d;
		for (i = 0; i < d; i++){
			iss>>dx>>dy>>dk;
			if (_Map.GetHexh(dx,dy) == 0){
				Log("o_Tracker::Execute : hex loading fail");
				continue;
			}
			if (_Map.GetHexh(dx,dy)->GetPlanet(dk) == 0){
				Log("o_Tracker::Execute : planet loading fail");
				continue;
			}
			_CapturedPlanets.push_back(_Map.GetHexh(dx,dy)->GetPlanet(dk));
		}
		iss>>d;
		for (i = 0; i < d; i++){
			iss>>k;
			_DestroyedDocks.push_back(_Players[k-1]);
		}
	}
	if (Q == eq_StrategyEnd){//сброс в начале экшон-фазы
		reset();
		show(player);//debug
	}
	if (Q == eq_ActionStart){
		show(player);//debug
	}
	if (Q == eq_PlanetDestroyed){
		vector<Planet*>::iterator iter = _CapturedPlanets.begin();
		while (iter != _CapturedPlanets.end()){
			if (*iter == planet){
				_CapturedPlanets.erase(iter);
				break;
			}
			iter++;
		}
	}
	if ((Q == eq_AfterAssignDamage) && (isAttacker == 1)){
		if (unit->HasAbility(uaKilled))
			_DestroyedEnemyUnits[unit->Class] += 1;
		if ((army->GetHex()->GetLinkedHexes()->GetLink(army->GetOwner()->GetHS()) != ltNone) && (unit->HasAbility(uaCapitalShip)))
			_Infiltrator++;
	}
	if (Q == eq_BeforeCapture){
		if ((planet->GetOwner() != 0) && (planet->GetOwner() != player))
			_Invaders++;
	}
	if (Q == eq_OnCapture){
		if (find(_CapturedPlanets.begin(),_CapturedPlanets.end(),planet) == _CapturedPlanets.end())
			_CapturedPlanets.push_back(planet);
	}
	if (Q == eq_BattleStart){
		_SpaceBattlesFlag = false;
		_InvasionsFlag = false;
		_lastdock = false;
		if (army->GetPlanet() == 0){
			if ((opponent != 0) && (opponent->IsUnitWithAbility(uaCapitalShip) >= 3))
				_SpaceBattlesFlag = true;
		}
		else
			if ((opponent != 0) && !opponent->isDefeated())
				_InvasionsFlag = true;
		_DocksUnderAttack = 0;
		_PDSUnderAttack = 0;
		if (opponent != 0){
			_DocksUnderAttack = opponent->StackSize(DCK);
			if (opponent->GetPlanet() != 0)
				_PDSUnderAttack = opponent->StackSize(PDS);
		}
		if ((opponent != 0) && (isAttacker == 0))
			for (i = 0; i < MAX_TRADES; i++)
				if (army->GetOwner()->GetTrade(i)->owner == opponent->GetOwner())
					_Traitor++;
		if ((opponent != 0) && (opponent->GetOwner() != 0) && (opponent->StackSize(DCK) > 0) && (opponent->StackSize(DCK) == opponent->GetOwner()->CheckUnits().at(DCK)))
			_lastdock = true;
	}
	if (Q == eq_BattleEnd){
		if (army->GetPlanet() == 0){
			if (_SpaceBattlesFlag && !army->isDefeated() && opponent->isDefeated())
				_SpaceBattles++;
		}
		else
			if (_InvasionsFlag && !army->isDefeated() && opponent->isDefeated())
				_Invasions++;
		if (_lastdock && (opponent->GetOwner()->CheckUnits().at(DCK) == 0))
			_Merciless++;
		_DestroyedEnemyUnits.at(DCK) += _DocksUnderAttack - opponent->StackSize(DCK);
		if (opponent->GetPlanet() != 0)
			_DestroyedEnemyUnits.at(PDS) += _PDSUnderAttack - opponent->StackSize(PDS);
		if ((_DocksUnderAttack > 0) && (opponent->StackSize(DCK) < _DocksUnderAttack))
			if (find(_DestroyedDocks.begin(),_DestroyedDocks.end(),opponent->GetOwner()) == _DestroyedDocks.end())
				_DestroyedDocks.push_back(opponent->GetOwner());
	}
	return er_none;
}
GameEffect* o_Tracker::Clone(){
	return new o_Tracker(*this);
}
string o_Tracker::Save(){
	int i,k;
	std::stringstream ss;
	ss<<_Infiltrator<<" ";
	ss<<_Invaders<<" ";
	ss<<_Traitor<<" ";
	ss<<_Merciless<<" ";
	ss<<_Invasions<<" ";
	ss<<_SpaceBattles<<" ";
	for (i = 0; i < MAX_UNIT; i++)
		ss<<_DestroyedEnemyUnits.at(i)<<" ";
	ss<<_CapturedPlanets.size()<<" ";
	for (i = 0; i < _CapturedPlanets.size(); i++){
		ss<<_CapturedPlanets.at(i)->GetSystem()->xc<<" "<<_CapturedPlanets.at(i)->GetSystem()->yc<<" ";
		for (k = 1; k <= MAX_PLANETS; k++){
			if (_CapturedPlanets.at(i)->GetSystem()->GetPlanet(k) == _CapturedPlanets.at(i)){
				ss<<k<<" ";
				break;
			}
		}
	}
	ss<<_DestroyedDocks.size()<<" ";
	for (i = 0; i < _DestroyedDocks.size(); i++)
		ss<<_DestroyedDocks.at(i)->GetNumber()<<" ";
	return ss.str();
}
void o_Tracker::Load(std::string str){
	_loadstring = str;
}