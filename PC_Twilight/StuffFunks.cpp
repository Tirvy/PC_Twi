#include "UnitsFunks.cpp"
#include "TechFunks.cpp"
#include "Spawn.cpp"
#include "CarriableFunks.cpp"
#include "MapFunks.cpp"
#include "ArmyFunks.cpp"
#include "PlayersFunks.cpp"
#include "ObjectiveFunks.cpp"

int isAdjacent(Hex *h1, Hex *h2){
	int x1,y1,x2,y2;
	int result=317;
	x1=GetXh(h1);
	y1=GetYh(h1);
	x2=GetXh(h2);
	y2=GetYh(h2);
	if (y1==y2){
		if (abs(x1-x2)<=1)
			result=abs(x1-x2);
	}
	else{
		if (abs(y1-y2)==1){
			if ((abs(y1)%2==0)&&((x1==x2)||(x1==x2+1))){//добавлен модуль, ибо при y1<0 остаток тоже получается меньше нуля и ветка пропускается
				result=1;
			}
			if ((abs(y1)%2==1)&&((x1==x2)||(x1==x2-1))){//добавлен модуль, ибо при y1<0 остаток тоже получается меньше нуля и ветка пропускается
				result=1;
			}
		}
	}
	return result;
};

int Distance(Hex* h1,Hex*h2){
	/*if (GetYh(h1) == GetYh(h2))
		return GetXh(h1) - GetXh(h2);
	if (GetYh(h1) - GetYh(h2) == 1)
		return (GetXh(h1) - GetXh(h2)) + 1 + (GetXh(h2) > GetXh(h1))*/
	return -1;
}

int TREE_SIZE = 12;
bool Reach_Able(Player* player,Hex*h){
	if (( player->GetMoveStats()->moveout[h->GetDanger()] == MO_lowspeed )||
		( player->GetMoveStats()->pass[h->GetDanger()] == false )){
		return false;
	}
	return true;
}

/*bool Reach_Able_Able(Player* player,int x,int y){
	return ((_Map.GetRoundh(x,y) != '-')&&(Reach_Able(player,_Map.GetHexh(x,y))));
}

const int OFFSET[2][6][2] =	{
		{ {1,0},	{1,-1},		{0,-1},		{-1,0},		{0,1},		{1,1} },
		{ {1,0},	{0,-1},		{-1,-1},	{-1,0},		{-1,1},		{0,1} }
						};*/	
/*PowTree<Hex>* Reach(Player* player,Hex * h,int maxdist, bool * check = 0, int dist = 0){
//check = offset, starting from the one on the right (+1,0), then clockwise
//means {E,SE,SW,W,NW,NE} or {}
	PowTree<Hex>* DaTree = new PowTree<Hex>(h,dist,TREE_SIZE);
	bool newcheck[6][6];
	bool tempcheck[6];
	int x,y,i,j;
	int mod;
	if (check == 0){
		check = &(tempcheck[0]);
		for (i=0;i<6;++i)
			check[i] = 1;
	}
	h->GetCoords(&x,&y);
	mod = abs(y+1)%2;
	if ((dist > 1)&&( player->GetMoveStats()->moveout[h->GetDanger()] == MO_lowspeed )){
		delete DaTree;
		return 0;
	}
	if (dist == maxdist){
		return DaTree;
	}
	for (i=0;i<6;++i)
		for (j=0;j<6;++j)
			newcheck[i][j] = ((j==i)||(j==i+1)||(j==i-5));
	for (i=0;i<6;++i){
		if (_Map.GetRoundh(x+OFFSET[mod][i][0],y+OFFSET[mod][i][1]) == '-'){
			check[i] = 0;
		}
		else if (!Reach_Able_Able(player,x+OFFSET[mod][i][0],y+OFFSET[mod][i][1])){
			for (j=0;j<6;++j)
				newcheck[i][j] = 0;
			if(Reach_Able_Able(player,x+OFFSET[mod][(i+5)%6][0],y+OFFSET[mod][(i+5)%6][1]))
				newcheck[(i+5)%6][(i+2)%6] = true;
			if(Reach_Able_Able(player,x+OFFSET[mod][(i+1)%6][0],y+OFFSET[mod][(i+1)%6][1])){
				newcheck[(i+1)%6][i] = true;
				newcheck[(i+1)%6][(i+5)%6] = true;
			}
		}
	}
	for (i=0;i<6;++i){
		if ((check == 0)||(check[i])){
			DaTree->AddChild(Reach(player,_Map.GetHexh(x+OFFSET[mod][i][0],y+OFFSET[mod][i][1]),maxdist,&newcheck[i][0],dist+1));
		}
	}
	for (i = wh_NONE + 1; i < wh_MAX; ++i){
		if (h->GotPortal((WormholeType)i)){
			list<Hex*>::iterator hexes = _Map.GetWormholes((WormholeType)i).begin();
			list<Hex*>::iterator end = _Map.GetWormholes((WormholeType)i).end();
			while (hexes != end){
				if (*hexes != h)
					DaTree->AddChild(Reach(player,*hexes,maxdist,0,dist+1));
				++hexes;
			}
			/*for (j=0; j<_Map.GetHexesNumber(); ++j){
				if ((hexes[j]!=0)&&(hexes[j]->GotPortal((WormholeType)i)))
					DaTree->AddChild(Reach(player,hexes[j],maxdist,0,dist+1));
			}*/
		/*}
	} 
	return DaTree;
}*/
/*
PowTree<Hex>* FindInMoveTree(PowTree<Hex>* tree,Hex* tofind,int depth = -2){
	int i;
	PowTree<Hex>* ret = 0;
	if (depth == -1)
		return 0;
	if (tree->elem == tofind)
		return tree;
	for (i = 0;i<tree->GetSize();++i){
		if (tree->child[i] != 0){
			ret = FindInMoveTree(tree->child[i],tofind,depth-1);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}*/

PowExv<Hex>* FindInMoveExv(PowExv<Hex>* list,Hex* tofind,int maxstatus = -1){
	PowExv<Hex>* temp = list;
	while (temp!=0){
		if ((temp->elem == tofind)&&((temp->status < maxstatus)||(maxstatus == -1)))
			return temp;
		temp = temp->next;
	}
	return 0;
}
PowDEV<Unit,Army>* GetUnitList(Player*player){ // remember to delete after usage
	PowDEV<Unit,Army>* ret = 0;
	vector<Unit*>* tunit;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetOwner() == player){
			tunit = (*aiter)->GetUnits();
			for (vector<Unit*>::iterator iter = tunit->begin(); iter != tunit->end(); iter++){
				if (ret == 0)
					ret = new PowDEV<Unit,Army>(*iter,*aiter,0,0);
				else
					(*ret)+= new PowDEV<Unit,Army>(*iter,*aiter,0,0);
			}
		}
	}
	return ret;
}

Hex* GetUnitLocation(Unit* unit){
	Army* army = 0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetUnitNumber(unit) != 0){
			army = *aiter;
			break;
		}
	}
	if (army == 0)
		throw throwable("GetUnitLocation:: no unit, how could it be?");
	return army->GetHex();
}

bool SwapTrades(Player*player1,TradeRoute*route1,Player*player2,TradeRoute*route2){
	int r1,r2,i;
	r1=r2=-1;
	for (i=0;i<MAX_TRADES;++i)
		if (player1->GetTrade(i) == route1)
			r1 = i;
	for (i=0;i<MAX_TRADES;++i)
		if (player2->GetTrade(i) == route2)
			r2 = i;
	if ((r1==-1)||(r2==-1))
		return false;
	ostringstream ss;
	if (route1->owner == player1)
		ss<<"TR made: ("<<route1->power<<") from {"<<player1->GetName()<<"} with ("<<route2->power<<") from {"<<player2->GetName()<<"}";
	else
		ss<<"TR broken: ("<<route1->power<<") from {"<<player1->GetName()<<"} with ("<<route2->power<<") from {"<<player2->GetName()<<"}";
	_Interface.PrintThingAll(ss.str());
	player1->SwapTrades(r1,player2->SwapTrades(r2,player1->GetTrade(r1)));
	return true;
}
int FindInArray(string what, string** arr, int arrsize){
	return arrsize;
} 
int FileToInt(string file, string extension){
	DIR *dp;
	dirent *d;
	int i = 0;


	dp = opendir("..//Release//data");
	while((d = readdir(dp)) != NULL)
		if (strstr(d->d_name,extension.c_str()) != 0){
			if (strstr(file.c_str(), d->d_name) == 0){
				closedir(dp);
				return i;
			}
			++i;
		}
	closedir(dp);
	return -1;
}

string IntToFile(int num, string extension = ""){
	DIR *dp;
	dirent *d;
	int i = 0;
	string str;

	dp = opendir("..//Release//data");
	while((d = readdir(dp)) != NULL)
		if (strstr(d->d_name,extension.c_str()) != 0){
			if (i == num){
				str = string("..//Release//data//") + d->d_name;
				closedir(dp);
				return str;
			}
			++i;
		}
	closedir(dp);
	return "";
}
int GetTemplatePlayerNumber(string filename){
	string elem,eq,buff;
	int players = 0;
	std::istringstream iss;
	ifstream myfile (filename.c_str());
	if (!myfile.is_open()){
		cout << "Unable to open file" << endl;
		return 0;
	}
	cout<<filename<<" ";//debug
	while ( getline (myfile,buff) ){
		iss.clear();
		iss.str(buff);
		iss >> elem;
		if (elem.compare(ini_players) == 0){
			iss >> players;
			break;
		}
	}
	myfile.close();
	return players;
}

vector<RacesType> GetRaces(string filename){
	vector<RacesType> r;
	r.clear();
	string elem,eq,buff;
	int race = 0;
	std::istringstream iss;
	ifstream myfile (filename.c_str());
	if (!myfile.is_open()){
		cout << "Unable to open file" << endl;
		return r;
	}
	while ( getline (myfile,buff) ){
		iss.clear();
		iss.str(buff);
		iss >> elem;
			if (elem.compare(ini_race) == 0){
				iss >> eq >> race;
				r.push_back((RacesType)race);
			}
		}
	myfile.close();
	return r;
}