
Map::Map(){
	hexlist.clear();
}
/*int Map::GetMaxRadius(){
	return (k-1)/2;
}*/
int Map::Initialize(int SystemsNumber, int in_k){
	/*int i;
	k = in_k;
	Hexes = new Hex*[k*k];
	HexRound = new int[k*k];
	for (i=0;i<k*k;++i){
		Hexes[i]=0;
	}
	for (i=0;i<k*k;++i)
		HexRound[i] = -1;*/
	hexlist.clear();
	return 1;
}
/*int Map::SetPlayerHSh( int y, int x, int player){
	
}
int Map::SetPlayerHSv( int y, int x, int player){
	return SetPlayerHSh(-y,x,player);
}*/
/*int Map::SetRoundh(int x, int y, int round){
	if ((x>(k-1)/2) || (y>(k-1)/2) || (x<-(k-1)/2) || (y<-(k-1)/2))
		throw throwable("Wrong hex coord for Map::SetRoundh",x+y);
	HexRound[(x+(k-1)/2)*k + (y+(k-1)/2)] = round;
	return 1;
}
int Map::SetRoundv(int x, int y, int round){
	return SetRoundh(-y,x,round);
}*/
Hex * Map::GetHexh(int x, int y) const{
	/*if ((x>(k-1)/2) || (y>(k-1)/2) || (x<-(k-1)/2) || (y<-(k-1)/2))
		throw throwable("Wrong hex coord for Map::GetHexh",x,y);
	return Hexes[(x+(k-1)/2)*k + (y+(k-1)/2)];*/
	Hex* result = 0;
	int xc,yc;
	/*for (vector<Hex*>::iterator hiter = hexlist.begin(); hiter != hexlist.end(); hiter++){
		(*hiter)->GetCoords(&xc,&yc);
		if ((x == xc) && (y == yc))
			result = *hiter;
	}*/
	for (int i = 0; i < hexlist.size(); i++){
		hexlist.at(i)->GetCoords(&xc,&yc);
		if ((x == xc) && (y == yc))
			result = hexlist.at(i);
	}
	return result;
}
/*Hex * Map::GetHexv(int x, int y) const{
	return GetHexh(-y,x);
}*/
/*int Map::GetSysByRoundh(int round, int*x,int*y){
	int i;
	for (i=0;i<(k*k);++i){
		if ((HexRound[i] == round)&&(Hexes[i] == 0)){
			*x = (i/k)-(k-1)/2;
			*y = (i%k)-(k-1)/2;
			return 1;
		}
	}
	return 0;
}
int Map::GetSysByRoundv(int round, int*x,int*y){
	int x1,y1;
	x1 = -(*y);
	y1 = *x;
	GetSysByRoundh(round, &x1,&y1);
	*x = x1;
	*y = y1;
}*/
int Map::LaySystemh(int x, int y, Hex* hex){
	/*if ((x>(k-1)/2) || (y>(k-1)/2) || (x<-(k-1)/2) || (y<-(k-1)/2))
		throw throwable("Wrong hex coord for Map::LaySystemh",x,y);
	Hexes[(x+(k-1)/2)*k + (y+(k-1)/2)] = hex;
	for (int i = 0; i<wh_MAX; ++i)
		if (hex->GotPortal((WormholeType)i))
			worms[i].push_back(hex);*/
	Hex* replace = GetHexh(x,y);
	int i;
	int plans;
	if (replace == 0){
		hex->number = hexlist.size();
		hex->xc = x;
		hex->yc = y;
		hexlist.push_back(hex);
		for (plans = 0; ((plans<MAX_PLANETS)&&(hex->GetPlanet(plans+1) != 0));++plans){}
	}
	else{
		replace->danger = hex->danger;
		replace->id = hex->id;
		for (i = 0; i < MAX_PLANETS; i++)
			if (replace->planets[i] != 0)
				delete replace->planets[i];
		for (i = 0; i < MAX_PLANETS; i++)
			replace->planets[i] = 0;
		plans = 0;
		for (i = 0; i < MAX_PLANETS; i++){
			if (hex->GetPlanet(i+1) != 0)
				plans++;
			replace->planets[i] = hex->GetPlanet(i+1);
			if (hex->GetPlanet(i+1))
				replace->planets[i]->SetHex(replace);
		}
		for (i = 0; i < wh_D; i++)
			replace->portal[i] = hex->portal[i];
	}
	cout<<hex->GetId()<<','<<plans<<endl;
	_MapGraphics.AddHex(hex->GetId(),x,y,plans);
	return 1;
}
/*int Map::LaySystemv(int x, int y, Hex* hex){
	return LaySystemh(-y,x,hex);
}*/
/*int Map::GetRoundh(int x,int y) const{
	if ((x>(k-1)/2) || (y>(k-1)/2) || (x<-(k-1)/2) || (y<-(k-1)/2))
		return '-';
		//throw throwable("Wrong hex coord for Map::GetRoundh",x+y);
	return HexRound[(x+(k-1)/2)*k + (y+(k-1)/2)];
}
int Map::GetRoundv(int x,int y){
	return GetRoundh(-y,x);
}*/
int Map::TranslateToNumber(int x, int y){
	//int radius = GetMaxRadius();
	//return (x+radius) + (y+radius)*(2*radius+1);
	return GetHexh(x,y)->number;
}
void Map::TransletaToCoords(int n, int* x, int* y){
	/*int radius = GetMaxRadius();
	*x = n%(2*radius+1) - radius;
	*y = n/(2*radius+1) - radius;*/
	*x = GetHexList()->at(n)->xc;
	*y = GetHexList()->at(n)->yc;
}
/*Hex * * Map::GetHexes(){
	return Hexes;
}*/
/*list<Hex*> & Map::GetWormholes(WormholeType type){
	return worms[type];
}*/
/*int Map::GetHexesNumber(){
	//return k*k;
	return hexlist.size();
}*/

int Map::CreateHexLinks(bool boundary, bool portals){
	//пока список гексов собирается из исходного массива, потом надо сделать новый формат шаблона
	//int radius = _Map.GetMaxRadius();
	/*for (int x=-radius;x<=radius;x++)//создаем список гексов
		for (int y=-radius;y<=radius;y++)
			if (_Map.GetHexh(x,y)!=0)
				hexlist.push_back(_Map.GetHexh(x,y));*/
	//теперь цикл по гексам можно устраивать через итератор
	vector<Hex*>::iterator iter;
	vector<Hex*>::iterator temp;
	if (boundary){
		for (iter = hexlist.begin(); iter != hexlist.end(); iter++){//линки на соседние гексы
			for (temp = hexlist.begin(); temp != hexlist.end(); temp++){
				if (isAdjacent(*iter,*temp)==1){
					(*iter)->GetLinkedHexes()->AddLink(*temp,ltBound);
					//cout<<"ZoldnMap bound link between "<<(*iter)->GetId()<<" and "<<(*temp)->GetId()<<endl;
				}
			}
		}
	}
	if (portals){
		for (WormholeType WH = wh_A; WH < wh_MAX; WH = (WormholeType)((int)WH+1)){//линки через порталы
			for (iter = hexlist.begin(); iter != hexlist.end(); iter++){
				if ((*iter)->GotPortal(WH)){
					for (temp = iter; temp != hexlist.end(); temp++){
						if ((*temp != *iter)&&((*temp)->GotPortal(WH))){
							(*iter)->GetLinkedHexes()->AddLink(*temp,ltPortal);
							(*temp)->GetLinkedHexes()->AddLink(*iter,ltPortal);
							//cout<<"ZoldnMap portal link between "<<(*iter)->GetId()<<" and "<<(*temp)->GetId()<<" by portal "<<(int)WH<<endl;
						}
					}
				}
			}
		}
	}
	return 1;
}

void Map::RemovePortalLinks(){
	vector<Hex*>::iterator iter;
	vector<Hex*>::iterator temp;
	for (WormholeType WH = wh_A; WH < wh_MAX; WH = (WormholeType)((int)WH+1)){//линки через порталы
		for (iter = hexlist.begin(); iter != hexlist.end(); iter++){
			if ((*iter)->GotPortal(WH)){
				for (temp = iter; temp != hexlist.end(); temp++){
					if ((*temp != *iter)&&((*temp)->GotPortal(WH))){
						(*iter)->GetLinkedHexes()->DeleteLink(*temp,ltPortal);
						(*temp)->GetLinkedHexes()->DeleteLink(*iter,ltPortal);
						//(*iter)->GetLinkedHexes()->AddLink(*temp,ltPortal);
						//(*temp)->GetLinkedHexes()->AddLink(*iter,ltPortal);
						//cout<<"ZoldnMap portal link between "<<(*iter)->GetId()<<" and "<<(*temp)->GetId()<<" by portal "<<(int)WH<<endl;
					}
				}
			}
		}
	}
};

vector<Hex*>* Map::GetHexList(){
	return &hexlist;
}

int Map::Hex2Int(Hex *hex){
	int i = 0;
	for (vector<Hex*>::iterator iter = hexlist.begin(); iter != hexlist.end(); iter++){
		if ((*iter) == hex)
			break;
		i++;
	}
	if (i >= hexlist.size())
		return -1;
	return i;
}

Hex* Map::Int2Hex(int k){
	if ((k<0)||(k>=hexlist.size()))
		return 0;
	return hexlist.at(k);
}