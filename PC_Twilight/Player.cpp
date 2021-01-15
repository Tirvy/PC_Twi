
Player::Player(string newname, int snumber){
	int i;
	if (newname.size() != 0) 
		_name = newname;
	else
		_name = "";
	banner = "";
	_number = snumber;
	_unitstats = new UnitStats();
	_unitstats->SetDefault();
	_movestats = new MoveStats();
	_movestats->Reset();
	_initiative = 0;
	_race = MAX_RACE;
	_color = 7;
	_planets.clear();
	for (i=0;i<MAX_STRAT;++i)
		_strats[i] = 0;
	for (i=0;i<MAX_TECH;++i)
		_techs[i] = false;
	_counters[CC_strat]=0;
	_counters[CC_fleet]=0;
	_counters[CC_comm]=0;
	_goods = 0;
	_trades[0] = 0;
	_trades[1] = 0;
	_PlayerGameEffect.clear();
	eHS = 0;
	//_PlayerObjectives.clear();
}
void	Player::TakeGoods(int n){
	if (n > _goods)
		_goods = 0;
	else
		_goods-=n;
}
int		Player::GetNumber(){
	return _number;
}
int		Player::SetHS(Hex* nHS){
	int i;
	HS = nHS;
	for (i=1;i<=MAX_PLANETS;++i)
		Capture(nHS->GetPlanet(i));
	_unitstats->SetFlagship(_race);
	banner = string("banners/") + RacesFull[_race];
	RefreshPlanet();
	return 1;
}

bool	Player::MakeAction(){
	int c = 0;
	int * arr = 0;
	GameEffectRets ret;
	char buff[256];
	bool done = true;
	bool HasActiveStrats = false;	
	list<GameEffect*>::iterator taaa;
	for (int j=0;j<MAX_STRAT;++j)
		if (GotStrat((StratsType)j) == 1)
			HasActiveStrats = true;
	//HasActiveStrats = false;//NADO TRUE
	ExecuteGameEffect(ExecuteParams(eq_ActionStart,this));
	while (done){
		_GrIn.InitChoise("Choose an action to make",!HasActiveStrats);
		for (taaa = _PlayerGameEffect.begin(); taaa != _PlayerGameEffect.end(); taaa++)
			if ((*taaa)->GetQ(eq_AAA))
				_GrIn.AddOption((*taaa)->GetImg(),(*taaa)->GetId().c_str());//Zoldn's ".c_str()"
		vector<int> tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() != 0)
			arr = &tempvec[0];
		if (arr == 0){
			sprintf(buff,"Player %s passes",_name.c_str());
			_Interface.PrintThingAll(buff);
			return true;
		}
		c = -1;
		taaa = _PlayerGameEffect.begin();
		while (true){//
			if ((*taaa)->GetQ(eq_AAA)){
				++c;
				if (arr[c]==1)
					break;
			}
			++taaa;
		} 
		ret = (*taaa)->Execute(ExecuteParams(eq_AAA,this));
		if (ret == er_delete){
			_PlayerGameEffect.erase(taaa);
			done = false;
		}
		if (ret == er_normal)
			done = false;
		if (ret == er_delete_none)
			_PlayerGameEffect.erase(taaa);
	}
	return false;
}
const	string Player::GetName(){
	return _name;
}
bool	Player::CheckPass(string cpass){
	if (cpass==_pass)
		return true;
	return false;
}
int		Player::GetId(){
	return _number;
}
int		Player::SetInitiative(int x){
	_initiative = x;
	return 1;
}
int		Player::GetInitiative(){
	return _initiative;
}
int		Player::GetConnection(){
	return _connection;
}
Hex*	Player::GetHS(){
	return HS;
}

int		Player::SetExtraHS(Hex* nHS){
	int i;
	eHS = nHS;
	for (i=1;i<=MAX_PLANETS;++i)
		Capture(nHS->GetPlanet(i));
	return 1;
}

Hex*	Player::GetExtraHS(){
	return eHS;
}

int		Player::AddStrat(StratsType x){
	if (_strats[x]!=0)
		throw throwable("Player::AddStrat : adding already having card",x,x);
	_strats[x] = 1;
	//this->AddGameEffect(StratCardList
	return 1;
}
int		Player::GetColor(){
	return _color;
}
string	Player::GetBanner(){
	return banner;
}
int		Player::GotStrat(StratsType x){
	int r = 0;
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++){
		if ((*iter)->GetId().compare(_GameStats.GetStrategies()->at(x)->GetId()) == 0){
			r = 1;
			break;
		}
	}
	return r;
}
int		Player::GetCountersSA(){
	return _counters[CC_strat];
}
int		Player::GetCountersFS(){
	return _counters[CC_fleet];
}
int		Player::GetCountersCP(){
	return _counters[CC_comm];
}
int		Player::Refresh(){
}
TradeRoute*	Player::GetTrade(int _number){
	if ((_number>1)||(_number<0))
		throw throwable("Player::GetTrade _number = ",_number);
	return (_trades[_number]);
} 
TradeRoute*	Player::SwapTrades(int _number, TradeRoute* route){
	if ((_number>1)||(_number<0))
		throw throwable("Player::GetTrade _number = ",_number);
	if (((this==_trades[_number]->owner)&&(this==route->owner))||((_trades[_number]->owner!=this)&&(route->owner!=this)))
		return false;
	TradeRoute* temp;
	temp = route;
	route = _trades[_number];
	_trades[_number] = temp;
	return route;
}
bool	Player::AddTrade(int power){
	if (_trades[0]==0)
		_trades[0] = new TradeRoute(power,this);
	else if (_trades[1]==0)
		_trades[1] = new TradeRoute(power,this);
	else
		return false;
	return true;
}
UnitStats*	Player::GetUnitStats(){
	return _unitstats;
}
MoveStats*	Player::GetMoveStats(){
	return _movestats;
}
int		Player::ReturnStrats(){
	int i;
	for (i=0;i<MAX_STRAT;++i)
		_strats[i] = false;
	return 1;
}
bool	Player::GotTech(TechType c){
	return _techs[c];
}
bool	Player::GiveTech(TechType c){
	if (_techs[c])
		throw throwable("Player::GiveTech already got tech");
	_techs[c] = true;
	return true;
}
bool*	Player::GetTechList(){
	return _techs;
}
void	Player::ReDirsrCC(int SA, int FS, int CP){
	if (SA+FS+CP != _counters[CC_strat]+_counters[CC_fleet]+_counters[CC_comm])
		throw throwable("Player::ReDirsrCC _counters dont match");
	_counters[CC_strat]=SA;
	_counters[CC_fleet]=FS;
	_counters[CC_comm]=CP;
}
void	Player::AddCC(int SA, int FS, int CP){
	_counters[CC_strat]+=SA;
	_counters[CC_fleet]+=FS;
	_counters[CC_comm]+=CP;
}
RacesType	Player::GetRace(){
	return _race;
}
int		Player::GetGoods(){
	return _goods;
}
int		Player::GiveGoods(int x){
	if (x>=0)
		_goods+=x;
	else
		throw throwable("Player::Give_goods < 0");
	return 1;
}

int		Player::AddPlanet(Planet* planet){
	if (planet == 0)
		return 0;
	_planets.push_back(planet);
	planet->SetOwner(this);
	int x,y,i=0;
	planet->GetSystem()->GetCoords(&x,&y);
	while((i<MAX_PLANETS)&&(planet->GetSystem()!=0)&&(planet!=planet->GetSystem()->GetPlanet(i+1)))
		++i;
	_MapGraphics.PutSpecial(FLAG,this,x,y,i);
	return 1;
}
int		Player::Capture(Planet * planet){
	if (planet == 0)
		return 0;
	if (planet->GetOwner() == this)
		return 0;
	ExecuteGameEffect(ExecuteParams(eq_BeforeCapture,this,planet));
	_planets.push_back(planet);
	_planets.back()->AddState(psCaptured);
	_planets.back()->AddState(psExhausted); // REMEMBERERERERERER!!!!
	if (planet->GetOwner()!=0)
		planet->GetOwner()->DeCapture(planet);
	//marker
	planet->SetOwner(this);
	ExecuteGameEffect(ExecuteParams(eq_OnCapture,this,planet));
	int x,y,i=0;
	planet->GetSystem()->GetCoords(&x,&y);
	cout<<"Capture "<<x<<" "<<y<<endl;
	while((i<MAX_PLANETS)&&(planet->GetSystem()!=0)&&(planet!=planet->GetSystem()->GetPlanet(i+1)))
		++i;
	_MapGraphics.PutSpecial(FLAG,this,x,y,i);//если закомментить, то не вылетает
	return 1;
}
int		Player::DeCapture(Planet * planet){
	//marker
	int x,y,i=0;
	planet->GetSystem()->GetCoords(&x,&y);
	while((i<MAX_PLANETS)&&(planet->GetSystem()!=0)&&(planet!=planet->GetSystem()->GetPlanet(i+1)))
		++i;
	_MapGraphics.KillSpecial(FLAG,x,y,i);

	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++){
		if ((*piter) == planet){
			_planets.erase(piter);
			break;
		}
	}
	planet->SetOwner(0);
	return 1;
}
vector<Planet*>*	Player::GetPlanetsList(){
	return &_planets;
}

bool	Player::CanBuildDock(Planet* planet){
	bool blockaded = false;	//The system does not contain any enemy ships.
	bool hasdock = false;	//there is no dock on planet already
	if (planet->GetSpecial() == TradeStation)
		return false;
	if (CheckUnits().at(DCK) >= defUnitNumbers[DCK])
		return false;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetHex() == planet->GetSystem())&&((*aiter)->GetOwner() != this) && ((*aiter)->GetPlanet() == 0)){
			blockaded = true;
			break;
		}
	}
	Army* temp = FindAllyArmy(this,planet->GetSystem(),planet);
	if ((temp != 0) && (temp->StackSize(DCK)))
		hasdock = true;
	return ((!planet->HasState(psCaptured)) && (!blockaded) && (!hasdock));//Zoldn
}
bool	Player::IsPlanetOpen(Planet* planet){
	return (!planet->HasState(psExhausted));
}
int		Player::RefreshPlanet(int _number){

	if (_number == -1)
		for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++){
			(*piter)->DeleteState(psExhausted);
			(*piter)->DeleteState(psCaptured);
			(*piter)->DeleteState(psDiplomated);
		}
	else{
		_planets[_number]->DeleteState(psExhausted);
	}
	return 1;
}

int		Player::Pay(int type, int howmuch){
	const int MARK = 42;// for a temporary planet status
	int Payed_goods = 0;
	//PowExv<Planet>* plans;
	int tospend = howmuch;
	int retstatus = 1;
	char buff[127];
	int i;
	bool done;
	string paytype[] = {"resources","influence","trade goods"};
	sprintf(buff,"Need to spend: %d %s",howmuch,paytype[type].c_str());
	done = false;
	vector<int> payed;
	if (howmuch <= 0)
		return frr_normal;
	int TradeToResInf = 1;
	int x = 0;
	int tg = 0;
	ExecuteGameEffect(ExecuteParams(eq_Payment,this,&TradeToResInf,&x));
	if (type == 2)
		TradeToResInf = 1;
	while (!done){
		payed = SelectDialogOwnedPlanet(buff,this,true,1,true,true);
		if (payed.size() == 0)
			return frr_none;
		//checking if inaf
		int total = 0;
		i=0;
		for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++){
			if (!(*piter)->HasState(psExhausted)){//Zoldn	
				if (payed[i] > 0){
					if (type == 0)
						total += (*piter)->GetRes();
					if (type == 1)
						total += (*piter)->GetInf();
				}
				++i;
			}
			//cout<<"Payer"<<payed[i]<<endl;
		}
		tg = payed.back();
		if ((tg <= _goods) && (tg*TradeToResInf + total >= tospend))//payed[i]
			done = true;
		if (tg <= _goods)//payed[i]
			sprintf(buff,"(Naf naf goods) Need to spend: %d %s",tospend,paytype[type].c_str());
		else
			sprintf(buff,"(Naf naf %s) Need to spend: %d %s",paytype[type].c_str(),tospend,paytype[type].c_str());
	}
	_goods -= tg;// payed[i]

	i=0;
	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++){
		if (!(*piter)->HasState(psExhausted)){//Zoldn
			if (payed[i] > 0){
				(*piter)->AddState(psExhausted);
			}
			++i;
		}
	}
	return frr_normal;
}

bool	Player::TakeCounter(int CT, int howmuch){
	switch(CT){
		case 0:if (_counters[CC_strat]>0){
				if (_counters[CC_strat]<howmuch)
					Eggog("Player::TakeCounter you want too much");
				_counters[CC_strat]-=howmuch;
				return true;
			}
			break;
		case 1:if (_counters[CC_fleet]>0){
				if (_counters[CC_fleet]<howmuch)
					Eggog("Player::TakeCounter you want too much");
				_counters[CC_fleet]-=howmuch;
				return true;
			}
			break;
		case 2:if (_counters[CC_comm]>0){
				if (_counters[CC_comm]<howmuch)
					Eggog("Player::TakeCounter you want too much");
				_counters[CC_comm]-=howmuch;
				return true;
			}
			break;
	}
	return false;
}

int		Player::GetVotes(){
	int sum = 0;
	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++)
		if (!(*piter)->HasState(psExhausted))//Zoldn
			sum+=(*piter)->GetInf();
	if (sum == 0)
		sum = 1;
	return sum;
}
int		Player::GetInfluence(){
	int sum = 0;
	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++)
		if (!(*piter)->HasState(psExhausted))//Zoldn
			sum+=(*piter)->GetInf();
	return sum;
}
int		Player::GetResources(){
	int sum = 0;
	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++)
		if (!(*piter)->HasState(psExhausted))//Zoldn
			sum+=(*piter)->GetRes();
	return sum;
}

void	Player::GiveFreeCounters(int n, bool redistribute){
	int m,i;
	int * result;
	char buff[64];
	if (!redistribute)
		sprintf(buff,"Distribute new %d counters. Now its %d/%d/%d",n,_counters[CC_strat],_counters[CC_fleet],_counters[CC_comm]);
	else{
		n+= _counters[CC_strat]+_counters[CC_comm]+_counters[CC_fleet];
		sprintf(buff,"Redistribute all your %d counters. It was %d/%d/%d.",n,_counters[CC_comm],_counters[CC_fleet],_counters[CC_strat]);
	}
	vector<int> tempvec;
	tempvec.clear();
	while (true){
		_GrIn.InitChoise(buff,false,true,true);
		for (i=0;i<CC_MAX;++i)
			_GrIn.AddNumerical(COUNTER_POOLS[i],CC_PoolsFull[i]);
		tempvec = _GrIn.LaunchChoise();
		result = &tempvec[0];
		m=0;
		for (i=0;i<CC_MAX;++i)
			m += result[i];
		if (m == n)
			break;
	}
	if (redistribute){
		_counters[CC_strat] = result[CC_strat];
		_counters[CC_fleet] = result[CC_fleet];
		_counters[CC_comm] = result[CC_comm];
	}
	else{
		_counters[CC_strat] += result[CC_strat];
		_counters[CC_fleet] += result[CC_fleet];
		_counters[CC_comm] += result[CC_comm];
	}
}

GameEffect*	Player::AddGameEffect(GameEffect* newGameEffect){
	_PlayerGameEffect.push_back(newGameEffect);
	return _PlayerGameEffect.back();
}

int		Player::ExecuteGameEffect(ExecuteParams& EP){
	list<GameEffect*>::iterator temp = _PlayerGameEffect.begin();
	while (temp != _PlayerGameEffect.end()){
		if ((*temp)->GetQ(EP.queue)){
			if ((*temp)->Execute(EP) == er_delete)
				temp = _PlayerGameEffect.erase(temp);
			else
				++temp;
		}
		else
			++temp;
	}
	return 0;
}
int		Player::PayRes(int x){
	return Pay(0,x);
}
int		Player::PayInf(int x){
	return Pay(1,x);
}
int		Player::recountVP(){
	_VP = 0;
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++)
		if ((*iter)->GetQ(eq_Objective))
			if (((e_Objective*)(*iter))->isDone)
				_VP += ((e_Objective*)(*iter))->value;
	return _VP;
}

void	Player::RefreshObjectives(){
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++)
		if ((*iter)->GetQ(eq_Objective))
			((e_Objective*)(*iter))->isFulfill = false;
}

void	Player::ShowObjectives(){
	list<e_Objective*>::iterator iter;
	char str[257];
	//for (iter = _PlayerObjectives.begin(); iter!=_PlayerObjectives.end(); ++iter){
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++){
		if ((*iter)->GetQ(eq_Objective)){
			sprintf(str,"%s (%d _VP)",((e_Objective*)(*iter))->GetReqs(),((e_Objective*)(*iter))->value);
			if (((e_Objective*)(*iter))->isFulfill)
				strcat(str,"[Fulfill]");
			if (((e_Objective*)(*iter))->isOpen)
				strcat(str,"[Open]");
			if (((e_Objective*)(*iter))->isDone)
				strcat(str,"[Done]");
			if (((e_Objective*)(*iter))->isSecret)
				strcat(str,"[Secret]");
			_Interface.PrintThingAll(str);
		}
	}
}

e_Politic*	Player::AddPolitic(e_Politic* pol, bool silent){
	_politics.push_back(pol);
	char buff[255];
	if (!silent){
		sprintf(buff,"New political card: %s",pol->GetId().c_str());
		_Interface.PrintThingPlayer(_number-1,buff);
	}
	return _politics.back();
}

void	Player::CheckFleets(){
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetOwner() == this){
			(*aiter)->CheckFleetSupport();
			(*aiter)->CheckPasSupport();
			if ((*aiter)->IsUnitWithAbility(uaKilled))
				CombatInterface().DestroyUnit(*aiter,(*aiter)->GetUnitWithAbility(uaKilled,1));
		}
	}
}

int		Player::DoneObjectives(){
	int result = 0;
	/*list<e_Objective*>::iterator iter;
	for (iter = _PlayerObjectives.begin(); iter!=_PlayerObjectives.end(); ++iter)
		if ((*iter)->isDone)
			result++;*/
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++)
		if ((*iter)->GetQ(eq_Objective))
			if (((e_Objective*)(*iter))->isDone)
				result++;
	return result;
}

int		Player::NumberOfPlanets(){
	return _planets.size();
}

int		Player::UnusedCC(){
	int result = 16;
	result -= GetCountersCP();
	result -= GetCountersSA();
	result -= GetCountersFS();
	for (vector<Hex*>::iterator hiter = _Map.GetHexList()->begin(); hiter != _Map.GetHexList()->end(); hiter++)
		if ((*hiter)->GotCC(GetNumber()))
			result--;
	return result;
};

int		Player::ActiveCC(){
	return GetCountersCP()+GetCountersSA()+GetCountersFS();
}

int		Player::Produce(Hex*system, int ProdLimit,int ResAdd, bool nodck){
	Army* army = 0;
	int i,j,l,m,d;
	int* ret = 0;
	int totallimit = 0;
	int spacelimit = 0;//производственные мощности в космосе (Саары, Арбореки)
	int docklimit = 0;
	int overflow = 0;
	int totalres = 0;
	int tospend = 0;
	int docksbuild = 0;
	char buff[255];
	char str[63];
	int bonus = 0;//бонусные ресурсы (Sarween Tools)
	bool blockade = true;
	bool overlimit = false;
	Unit* unit = 0;
	ProductionPlace PP;
	vector<ProductionPlace> places;
	vector<int> tempvec;
	vector<int> existunits = CheckUnits();
	vector<int> afterbuild = existunits; 
	//docklimit = defUnitNumbers[DCK] - existunits.at(DCK);
	places.clear();
	//эффекты перед производством
	_unitstats->SetDefault();
	_unitstats->SetFlagship(_race);
	RefreshArmyAbilities(this,3);
	ExecuteGameEffect(ExecuteParams(eq_BeforeBuild, this, system, &bonus));
	//ищем производственные мощности в космосе и на планетах
	army = FindAnyArmy(system);
	if (army == 0){
		PP.planet = 0;
		PP.limit = 0;
		PP.army = NewArmy(this,system);
		PP.dock = false;
		places.push_back(PP);
		blockade = false;
	}
	else if (army->GetOwner() == this){
		PP.planet = 0;
		PP.limit = 0;
		PP.army = army;
		PP.dock = false;
		for (i = 1; i <= army->IsUnitWithAbility(uaProduction,FIELD_SKIP,1); i++)
			PP.limit += army->GetUnitWithAbility(uaProduction,i,FIELD_SKIP,1)->GetAbility(uaProduction).field1;
		totallimit += PP.limit;
		spacelimit = PP.limit;
		places.push_back(PP);
		blockade = false;
	}
	for (j = 1; j <= MAX_PLANETS; j++){
		if ((system->GetPlanet(j) != 0) && (system->GetPlanet(j)->GetOwner() == this)){
			army = FindAnyArmy(system,system->GetPlanet(j));
			if (army == 0){
				PP.planet = system->GetPlanet(j);
				PP.limit = 0;
				PP.army = NewArmy(this,system,system->GetPlanet(j));
				PP.dock = CanBuildDock(system->GetPlanet(j));
				places.push_back(PP);
			}
			else if (army->GetOwner() == this){
				PP.planet = system->GetPlanet(j);
				PP.limit = 0;
				PP.army = army;
				PP.dock = CanBuildDock(system->GetPlanet(j));
				for (i = 1; i <= army->IsUnitWithAbility(uaProduction,FIELD_SKIP,1); i++)
					PP.limit += army->GetUnitWithAbility(uaProduction,i,FIELD_SKIP,1)->GetAbility(uaProduction).field1;
				totallimit += PP.limit;
				places.push_back(PP);
			}
		}
	}
	for (vector<ProductionPlace>::iterator iter = places.begin(); iter != places.end(); iter++)
		if (iter->dock)
			docksbuild++;
	if (!totallimit && (nodck || !docksbuild))//если негде, то стоп
		return 0;
	if (ProdLimit)
		totallimit = min(ProdLimit,totallimit);
	SpawnUnit opt;
	vector<SpawnUnit> options;
	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++)
		if (!(*piter)->HasState(psExhausted))
			totalres += (*piter)->GetRes();
	while (true){
		//создаем список юнитов для производства
		options.clear();//ЧИСТИМ опции
		sprintf(buff,"Select units to produce (limit: %d; res: %d; goods: %d; free: %d)",totallimit,totalres,_goods,ResAdd + bonus);
		_GrIn.InitChoise(buff,true,true,true);
		//космические юниты
		if (!blockade && totallimit){
			for (UnitType UT = FG; UT <= FM; UT = (UnitType)((int)UT+1)){
				if (_unitstats->GetParametr(UT,sNP)){
					sprintf(buff,"%s: %d/%d",ShipsFull[UT].c_str(),_unitstats->GetParametr(UT,sCOST),_unitstats->GetParametr(UT,sNP));
					_GrIn.AddNumerical(SHIPS_IMG[UT],buff);
					opt.UT = UT;
					opt.iter = places.begin();
					options.push_back(opt);
				}
			}
		}
		//наземные юниты по планетам
		for (vector<ProductionPlace>::iterator iter = places.begin(); iter != places.end(); iter++){
			if (iter->limit || spacelimit){
				for (UnitType UT = GF; UT <= PDS; UT = (UnitType)((int)UT+1)){
					if (_unitstats->GetParametr(UT,sNP)){
						if (iter->planet == 0)
							sprintf(str,"in Space");
						else
							sprintf(str,"%s",iter->planet->GetName().c_str());
						sprintf(buff,"%s: %d/%d (%s)",ShipsFull[UT].c_str(),_unitstats->GetParametr(UT,sCOST),_unitstats->GetParametr(UT,sNP),str);
						_GrIn.AddNumerical(SHIPS_IMG[UT],buff);
						opt.UT = UT;
						opt.iter = iter;
						opt.n = 0;
						options.push_back(opt);
					}
				}
			}
		}
		//доки
		if (!nodck){
			for (vector<ProductionPlace>::iterator iter = places.begin(); iter != places.end(); iter++){
				if (iter->dock){
					sprintf(str,iter->planet->GetName().c_str());
					sprintf(buff,"%s: %d (%s)",ShipsFull[DCK].c_str(),_unitstats->GetParametr(DCK,sCOST),str);
					_GrIn.AddNumerical(SHIPS_IMG[DCK],buff);
					opt.UT = DCK;
					opt.iter = iter;
					opt.n = 0;
					options.push_back(opt);
				}
			}
		}
		tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() != 0)
			ret = &tempvec[0];
		if (ret == 0)
			break;
		for (i = 0; i < options.size(); i++)
			options.at(i).n = ret[i];
		//проверки лимитов
		overlimit = false;
		overflow = 0;
		m = 0;
		for (vector<ProductionPlace>::iterator iter = places.begin(); iter != places.end(); iter++){
			l = 0;
			for (i = 0; i < options.size(); i++){
				if ((options.at(i).iter == iter) && (options.at(i).UT <= PDS))
					l += _unitstats->GetParametr(options.at(i).UT,sNP)*options.at(i).n;
				if ((options.at(i).iter == iter) && (options.at(i).UT <= FM))
					m += _unitstats->GetParametr(options.at(i).UT,sNP)*options.at(i).n;
			}
			if (l > iter->limit){
				if (iter->planet == 0)
					overlimit = true;
				else
					overflow += (l - iter->limit);
			}
		}
		if (overflow > spacelimit)
			overlimit = true;
		if (m > totallimit){
			sprintf(buff,"Excess of common production limit %d, you try to build %d",totallimit,m);
			_Interface.PrintThingPlayer(GetNumber()-1,buff);
			continue;
		}
		
		if (overlimit){
			_Interface.PrintThingPlayer(GetNumber()-1,"Excess of local production limit");
			continue;
		}
		afterbuild = existunits;
		for (vector<SpawnUnit>::iterator iter = options.begin(); iter != options.end(); iter++)
			afterbuild.at(iter->UT) += (iter->n)*_unitstats->GetParametr(iter->UT,sNP);
		bool _numberlimit = false;
		for (UnitType UT = GF; UT < MAX_UNIT; UT = (UnitType)((int)UT + 1)){
			if (afterbuild.at(UT) > defUnitNumbers[UT]){
				sprintf(buff,"Trying to build %d %s over limit %d",afterbuild.at(UT),ShipsShort[UT].c_str(),defUnitNumbers[UT]);
				_Interface.PrintThingPlayer(GetNumber()-1,buff);
				_numberlimit = true;
			}
		}
		if (_numberlimit)
			continue;
		//оплата
		tospend = 0;
		for (i = 0; i < options.size(); i++)
			tospend += _unitstats->GetParametr(options.at(i).UT,sCOST)*options.at(i).n;
		if (tospend > totalres+_goods+ResAdd+bonus){
			sprintf(buff,"Not enough resources to pay (need to pay %d)",tospend);
			_Interface.PrintThingPlayer(GetNumber()-1,buff);
			continue;
		}
		if (!Pay(0, tospend - ResAdd - bonus)){
			_Interface.PrintThingPlayer(GetNumber()-1,"Cancel payment");
			continue;
		}
		//спаун юнитов
		_Interface.PrintThingPlayer(GetNumber()-1,"Spawning units");
		int flag = 0;
		ExecuteGameEffect(ExecuteParams(eq_SpawnUnits,this,options,system,&flag));
		if (!flag){//обычный спаун
			for (i = 0; i < options.size(); i++){
				for (j = 0; j < options.at(i).n*_unitstats->GetParametr(options.at(i).UT,sNP); j++){
					unit = options.at(i).iter->army->AddUnit(options.at(i).UT);
					if (unit->Class == DCK)
						unit->AssignAbility(uaProduction,FIELD_SKIP,0);//док не может производить в этом раунде
					if ((options[i].iter->army->GetPlanet() == 0) && unit->HasAbility(uaNeedSupport,0))
						options[i].iter->army->SpaceRedistribute(unit);
				}
			}
		}
		CheckFleets();
		ExecuteGameEffect(ExecuteParams(eq_AfterBuild,this,system,&bonus));
		ExecuteGameEffect(ExecuteParams(eq_DockBuild,this,system,&bonus));
		break;
	}
	return 1;
}

vector<int>	Player::CheckUnits(){
	vector<int> result;
	result.clear();
	for (UnitType UT = GF; UT < MAX_UNIT; UT = (UnitType)((int)UT + 1))
		result.push_back(0);
	vector<Unit*>* tunit;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetOwner() == this){
			tunit = (*aiter)->GetUnits();
			for (vector<Unit*>::iterator iter = tunit->begin(); iter != tunit->end(); iter++)
				result.at((*iter)->Class) += 1;
		}
	}
	return result;
}

int		Player::ActivateDocks(){
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if ((*aiter)->GetOwner() == this)
			for (int i = 1; i <= (*aiter)->IsUnitWithAbility(uaProduction); i++)
				(*aiter)->GetUnitWithAbility(uaProduction,i)->AssignAbility(uaProduction,FIELD_SKIP,1);
	return 1;
}

int		Player::AddAction(int number){
	if (number < 0)
		return 0;
	GameEffect* ac;
	char buff[255];
	for (int i = 0; i < number; i++){
		ac = AddGameEffect(_GameStats.DrawAction());
		sprintf(buff,"New Action Card: %s",((e_ActionCard*)ac)->GetName().c_str());
		_Interface.PrintThingPlayer(_number-1,buff);
	}
	ExecuteGameEffect(ExecuteParams(eq_ReceiveActionCard,this));
	return 1;
}

bool	Player::MakeStatusAction(){
	bool done = true;
	int c;
	vector<int> tempvec;
	list<GameEffect*>::iterator taaa;
	GameEffectRets ret;
	_Interface.SetCurrPlayer(_number - 1);
	while (done){
		_GrIn.InitChoise("Choose an action to make",true);
		for (taaa = _PlayerGameEffect.begin(); taaa != _PlayerGameEffect.end(); taaa++)
			if ((*taaa)->GetQ(eq_StatusEnd))
				_GrIn.AddOption((*taaa)->GetImg(),(*taaa)->GetId().c_str());
		tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() == 0)
			break;
		c = -1;
		taaa = _PlayerGameEffect.begin();
		while (true){
			if ((*taaa)->GetQ(eq_StatusEnd)){
				++c;
				if (tempvec.at(c)==1)
					break;
			}
			++taaa;
		} 
		ret = (*taaa)->Execute(ExecuteParams(eq_StatusEnd,this));
		if (ret == er_delete){
			_PlayerGameEffect.erase(taaa);
			done = false;
		}
		if (ret == er_normal)
			done = false;
		if (ret == er_delete_none)
			_PlayerGameEffect.erase(taaa);
	}
	return false;
}

bool	Player::MakeQueueAction(ExecuteParams EP, string str, bool SingleAction){
	bool done = true;
	int c;
	vector<int> tempvec;
	list<GameEffect*>::iterator taaa;
	GameEffectRets ret;
	_Interface.SetCurrPlayer(_number - 1);
	int options = 0;
	for (taaa = _PlayerGameEffect.begin(); taaa != _PlayerGameEffect.end(); taaa++)
		if ((*taaa)->GetQ(EP.queue))
			options++;
	if (options == 0)
		return false;
	while (done && options){
		_Interface.SetCurrPlayer(_number - 1);
		//_GrIn.InitChoise("Choose an action to make",true);
		_GrIn.InitChoise(str,true);
		for (taaa = _PlayerGameEffect.begin(); taaa != _PlayerGameEffect.end(); taaa++)
			if ((*taaa)->GetQ(EP.queue))
				_GrIn.AddOption((*taaa)->GetImg(),(*taaa)->GetId().c_str());
		tempvec = _GrIn.LaunchChoise();
		if (tempvec.size() == 0)
			//break;
			return false;
		c = -1;
		taaa = _PlayerGameEffect.begin();
		while (true){
			if ((*taaa)->GetQ(EP.queue)){
				++c;
				if (tempvec.at(c)==1)
					break;
			}
			++taaa;
		}
		ret = (*taaa)->Execute(EP);
		if (ret == er_delete)//{
			_PlayerGameEffect.erase(taaa);
			//done = false;
		//}
		if (SingleAction && (ret == er_normal))
			break;
		options = 0;
		for (taaa = _PlayerGameEffect.begin(); taaa != _PlayerGameEffect.end(); taaa++)
			if ((*taaa)->GetQ(EP.queue))
				options++;
		//if (ret == er_normal)
		//	done = false;
		//if (ret == er_delete_none)
		//	_PlayerGameEffect.erase(taaa);
	}
	return true;
}

int Player::RemoveGameEffect(string id){
	char buff[255];
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++){
		if ((*iter)->GetId().compare(id) == 0){
			_PlayerGameEffect.erase(iter);
			sprintf(buff,"Player::RemoveGameEffect : removed effect %s",id.c_str());
			Log(buff);
			break;
		}
	}
	return 1;
}

int Player::GetActionsNumber(){
	int acs = 0;
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++)
		if ((*iter)->GetQ(eq_ActionCard))
			acs++;
	return acs;
}

int Player::DiscardActions(int num){
	list<GameEffect*>::iterator iter;
	e_ActionCard* AC = 0;
	if (num < 0)
		return 0;
	int discard = num;
	if ((num == 0) || (num >= GetActionsNumber())){
		iter = _PlayerGameEffect.begin();
		while (iter != _PlayerGameEffect.end()){
			if ((*iter)->GetQ(eq_ActionCard)){
				_PlayerGameEffect.erase(iter);
				iter = _PlayerGameEffect.begin();
			}
			else
				iter++;
		}
	}
	else{
		while (discard){
			AC = SelectDialogActionCard("Select Action Card to discard",this,false);
			RemoveGameEffect(AC->GetId());
			discard--;
		}
	}
	return 1;
}

o_Tracker* Player::GetObjectiveTracker(){
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++)
		if ((*iter)->GetQ(eq_ObjectiveTracker))
			return (o_Tracker*)(*iter);
	Log("Player::GetObjectiveTracker : can't find objective tracker");
	return 0;
}

int Player::TotalInf(){
	int sum = 0;
	for (vector<Planet*>::iterator piter = _planets.begin(); piter != _planets.end(); piter++)
		sum += (*piter)->GetInf();
	return sum;
}

e_Objective* Player::ObjectiveWin(){
	for (list<GameEffect*>::iterator iter = _PlayerGameEffect.begin(); iter != _PlayerGameEffect.end(); iter++)
		if ((*iter)->GetQ(eq_Objective))
			if ((((e_Objective*)(*iter))->isDone) && (((e_Objective*)(*iter))->GetType() == vp_win))
				return ((e_Objective*)(*iter));
	return 0;
}

int Player::SetDeck(vector<Hex*> deck){
	_SystemHand = deck;
	return 1;
}

Hex* Player::SelectSystemManualBuild(){
	Hex* selection = 0;
	_Interface.SetCurrPlayer(_number - 1);
	if (_SystemHand.size() == 0)
		return 0;
	_GrIn.InitChoise("Select system to place");
	for (vector<Hex*>::iterator iter = _SystemHand.begin(); iter != _SystemHand.end(); iter++)
		//_GrIn.AddOption(EMPTY_EVENT_IMG,(*iter)->GetId());
		_GrIn.AddOption("hexes/" + (*iter)->GetId(),(*iter)->GetId());
	vector<int> ret = _GrIn.LaunchChoise();
	for (int i = 0; i < ret.size(); i++)
		if (ret[i] == 1)
			selection = _SystemHand.at(i);
	return selection;
}
void Player::AddHexToDeck(Hex* hex){
	_SystemHand.push_back(hex);
}

void Player::RemoveHexFromDeck(Hex* hex){
	vector<Hex*>::iterator iter = _SystemHand.begin();
	while (iter != _SystemHand.end()){
		if (hex == *iter){
			_SystemHand.erase(iter);
			break;
		}
		iter++;
	}
}