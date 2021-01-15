LinkedHexes::LinkedHexes(){
	reset();
}

void LinkedHexes::reset(){
	hexes.clear();
	links.clear();
}

LinkType LinkedHexes::GetLink(Hex *hex){
	LinkType result = ltNone;
	for (int i=0; i<hexes.size(); i++){
		if (hexes.at(i) == hex){
			result = links.at(i);
			break;
		}
	}
	return result;
}

LinkType LinkedHexes::GetLink(int i){
	if ((i >= 0) && (i < links.size()))
		return links.at(i);
	return ltNone;
}

int LinkedHexes::AddLink(Hex *hex, LinkType LT){
	if (GetLink(hex) == ltNone){
		hexes.push_back(hex);
		links.push_back(LT);
	}
	return 1;
}

int LinkedHexes::DeleteLink(Hex *hex, LinkType LT){
	vector<Hex*>::iterator iterH = hexes.begin();
	vector<LinkType>::iterator iterL = links.begin();
	for (iterH = hexes.begin(); iterH != hexes.end(); iterH++){
		if (((*iterH) == hex) && ((*iterL) == LT)){
			hexes.erase(iterH);
			links.erase(iterL);
			break;
		}
		iterL++;
	}
	return 0;
}

Hex* LinkedHexes::GetLinkedHex(int i){
	if ((i<0)||(i>=hexes.size()))
		return 0;
	vector<Hex*>::iterator iter = hexes.begin();
	for (int k=0; k<i; k++)
		iter++;
	return *iter;
}

int LinkedHexes::GetLinkNumber(){
	return hexes.size();
}
/////////////////////////////////////////////////////////////
SpeedMap::SpeedMap(){
	if (_Map.GetHexList()->size()>0){
		distances = new int[_Map.GetHexList()->size()];
		reset();
	}
	else
		distances = 0;
}

SpeedMap::~SpeedMap(){
	delete [] distances;
}

void SpeedMap::reset(){
	if (distances != 0)
		for (int i=0; i<_Map.GetHexList()->size(); i++){
			distances[i] = 10;
		}
}

bool SpeedMap::IsPassable(Player* player,Hex *hex){
	Army* army = 0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
		if (((*aiter)->GetHex() == hex) && ((*aiter)->GetPlanet() == 0))
			army = *aiter;
	
	bool fleetblock = false;
	if (army!=0){
		if ((army->GetOwner() != player)&&(army->IsUnitWithAbility(uaCapitalShip)))
			fleetblock = true;
	}
	return !fleetblock && player->GetMoveStats()->pass[hex->GetDanger()];
}

int SpeedMap::CalculateMap(Player *player, Hex *hex){
	if (_Map.GetHexList()->size()==0)
		return 0;
	vector<Hex*>* hexlist = _Map.GetHexList();
	int MAX_SPEED = 6;
	reset();
	distances[_Map.Hex2Int(hex)] = 0;
	vector<Hex*>::iterator iter;
	vector<Hex*>::iterator temp;
	int k=0;
	for (int sp = 0; sp <= MAX_SPEED; sp++){
		k=0;
		for (iter = hexlist->begin(); iter != hexlist->end(); iter++){
			if ((distances[k] == sp)&&((sp == 0)||(IsPassable(player,*iter)))){
			//if ((distances[k] == sp)){
				for (int i=0; i<(*iter)->GetLinkedHexes()->GetLinkNumber(); i++){
					if (distances[_Map.Hex2Int((*iter)->GetLinkedHexes()->GetLinkedHex(i))]>(sp+1))
						distances[_Map.Hex2Int((*iter)->GetLinkedHexes()->GetLinkedHex(i))]=sp+1;
				}
			}
			k++;
		}
	}
	return 1;
}

int SpeedMap::CalculateMap(Hex *hex){
	if (_Map.GetHexList()->size()==0)
		return 0;
	vector<Hex*>* hexlist = _Map.GetHexList();
	int MAX_SPEED = 8;
	reset();
	distances[_Map.Hex2Int(hex)] = 0;
	vector<Hex*>::iterator iter;
	vector<Hex*>::iterator temp;
	int k=0;
	for (int sp = 0; sp <= MAX_SPEED; sp++){
		k=0;
		for (iter = hexlist->begin(); iter != hexlist->end(); iter++){
			if (distances[k] == sp){
			//if ((distances[k] == sp)){
				for (int i=0; i<(*iter)->GetLinkedHexes()->GetLinkNumber(); i++){
					if (distances[_Map.Hex2Int((*iter)->GetLinkedHexes()->GetLinkedHex(i))]>(sp+1))
						distances[_Map.Hex2Int((*iter)->GetLinkedHexes()->GetLinkedHex(i))]=sp+1;
				}
			}
			k++;
		}
	}
	return 1;
}

int SpeedMap::GetDistance(Hex *hex){
	return distances[_Map.Hex2Int(hex)];
}

int SpeedMap::GetDistance(Player* player, Hex *from, Hex *to){
	CalculateMap(player,from);
	return GetDistance(to);
}

void SpeedMap::ShowMap(){
	int k=0;
	for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
		cout<<"Show map: "<<(*iter)->GetId()<<" "<<distances[k]<<endl;
		k++;
	}
}
/////////////////////////////////////////////////////////////////////
PathFinder::PathFinder(Hex *hex1, Hex *hex2, int sp, Player *owner, SpeedMap* spmap){
	from = hex1;
	to = hex2;
	speed = sp;
	player = owner;
	marchroutes.clear();
	speedmap = spmap;
}

PathFinder::PathFinder(){
	from = 0;
	to = 0;
	speed = 0;
	player = 0;
	marchroutes.clear();
	speedmap = 0;
}

void PathFinder::reset(){
	marchroutes.clear();
}

vector<Hex*> PathFinder::NextStep(Hex *hex, int sp){
	vector<Hex*>::iterator iter;
	vector<Hex*> result;
	result.clear();
	Hex* nexthex;
	for (int i=0; i<hex->GetLinkedHexes()->GetLinkNumber(); i++){
		nexthex = hex->GetLinkedHexes()->GetLinkedHex(i);
		if ((speedmap->GetDistance(nexthex)<=sp)&&((speedmap->IsPassable(player,nexthex))||(nexthex == to)))
			result.push_back(nexthex);
	}
	return result;
}

int PathFinder::SplitRoutes(vector<vector<PathStep>>::iterator tail, vector<vector<PathStep>>* routes){
	int sp = tail->back().speed;
	Hex* hex = tail->back().hex;
	vector<PathStep> temp;
	temp.clear();
	PathStep step;
	//temp = *tail;
	for (vector<PathStep>::iterator iter = tail->begin(); iter != tail->end(); iter++){
		step.hex = iter->hex;
		step.speed = iter->speed;
		temp.push_back(step);
	}
	vector<Hex*> next = NextStep(hex,sp-1);
	int k = 0;
	for (vector<Hex*>::iterator iter = next.begin(); iter != next.end(); iter++){
		//cout<<"Split Routes "<<endl;
		step.hex = *iter;
		step.speed = sp-1;
		if (k == 0){
			tail->push_back(step);
		}
		else{
			routes->push_back(temp);
			routes->back().push_back(step);
		}
		k++;
	}
	return k;
}

int PathFinder::FindRoutes(){
	marchroutes.clear();
	PathStep step;
	step.hex = from;
	step.speed = speed;
	vector<PathStep> temp;
	temp.push_back(step);
	marchroutes.push_back(temp);
	vector<vector<PathStep>>::iterator iter = marchroutes.begin();
	vector<vector<PathStep>> routes;
	int k = 0;
	for (int sp = speed; sp >= speedmap->GetDistance(from); sp--){
		routes.clear();
		step.hex = from;
		step.speed = sp;
		temp.clear();
		temp.push_back(step);
		routes.push_back(temp);
		k = 0;
		iter = routes.begin();
		while (iter != routes.end()){
			if (iter->back().speed > 0){
				if (!SplitRoutes(iter,&routes)){
					k++;
				}
			}
			else
				k++;
			iter = routes.begin();
			for (int j=0; j<k; j++)
				iter++;
		}
		marchroutes.insert(marchroutes.end(),routes.begin(),routes.end());
	}
	return marchroutes.size();
}

void PathFinder::ShowRoutes(){
	vector<vector<PathStep>>::iterator iter;
	vector<PathStep>::iterator temp;
	for (iter = marchroutes.begin(); iter != marchroutes.end(); iter++){
		cout<<"Route ";
		for (temp = iter->begin(); temp != iter->end(); temp++){
			cout<<temp->hex->GetId()<<"("<<temp->speed<<")"<<"->";
		}
		cout<<endl;
	}
}

bool PathFinder::IsHexInRoutes(Hex* hex){
	vector<vector<PathStep>>::iterator iter;
	vector<PathStep>::iterator temp;
	bool result = false;
	for (iter = marchroutes.begin(); iter != marchroutes.end(); iter++){
		for (temp = iter->begin(); temp != iter->end(); temp++){
			if (temp->hex == hex){
				result = true;
				break;
			}
		}
		if (result)
			break;
	}
	return result;
}

int PathFinder::RoutesThroughHex(Hex *hex){
	vector<vector<PathStep>>::iterator iter = marchroutes.begin();
	vector<PathStep>::iterator temp;
	bool todelete = true;
	int k = 0;
	while (iter != marchroutes.end()){
		todelete = true;
		for (temp = iter->begin(); temp != iter->end(); temp++){
			if (temp->hex == hex){
				todelete = false;
				break;
			}
		}
		if (todelete)
			marchroutes.erase(iter);
		else
			k++;
		iter = marchroutes.begin();
		for (int i=0; i<k; i++)
			iter++;
	}
	return marchroutes.size();
}

void PathFinder::set(Hex *hex1, Hex *hex2, int sp, Player *owner, SpeedMap *spmap){
	from = hex1;
	to = hex2;
	speed = sp;
	player = owner;
	speedmap = spmap;
	marchroutes.clear();
}

vector<Hex*> PathFinder::AvailableHexes(){
	vector<vector<PathStep>>::iterator iter;
	vector<PathStep>::iterator temp;
	vector<Hex*> result;
	vector<Hex*>* hexes = _Map.GetHexList();
	vector<PathStep> list;
	PathStep PS;
	list.clear();
	for (vector<Hex*>::iterator i = hexes->begin(); i != hexes->end(); i++){
		PS.hex = *i;
		PS.speed = 0;
		list.push_back(PS);
	}
	result.clear();
	for (iter = marchroutes.begin(); iter != marchroutes.end(); iter++)
		for (temp = iter->begin(); temp != iter->end(); temp++)
			list.at(_Map.Hex2Int(temp->hex)).speed = 1;
	result.clear();
	for (vector<PathStep>::iterator i = list.begin(); i != list.end(); i++)
		if (i->speed)
			result.push_back(i->hex);
	return result;
}