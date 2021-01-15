Hex::Hex(){
	id = "";
	planets[0] = 0;
	planets[1] = 0;
	planets[2] = 0;
	danger = DT_NONE;
	portal[0]=wh_NONE;
	portal[1]=wh_NONE;
	portal[2]=wh_NONE;
	portal[3]=wh_NONE;
	for (int i=0;i<MAX_PLAYERS;++i)
		actmarkers[i] = false;
	neighboors.reset();
}
string Hex::GetId(){
	return id;
}
DangerType Hex::GetDanger(){
	return danger;
}

Planet* Hex::GetPlanet(int number){
	if ((number<=0)||(number>MAX_PLANETS))
		throw throwable("Hex::GetPlanet totally out of range");
	return planets[number-1];
}
bool Hex::GotPortal(WormholeType p){
	int i;
	for (i=0;i<4;++i)
		if (portal[i] == p)
			return true;
	return false;
}
bool Hex::GetCoords(int* x,int* y){
	/*int k,i,j;
	if ((x==0)||(y==0))
		throw throwable("Hex::GetCoords : 0 input x,y");
	k = _Map.GetMaxRadius();
	for (i=-k;i<=k;++i)
		for (j=-k;j<=k;++j)
			if (_Map.GetHexh(i,j) == this){
				*x = i;
				*y = j;
				return true;
			}
	return false;*/
	*x = xc;
	*y = yc;
	return true;
}
bool Hex::GotCC(int x){
	return actmarkers[x-1];
}
bool Hex::SetCC(int x){
	bool ret;
	int cx,cy;
	if (x>=MAX_PLAYERS)
		throw throwable("Hex::Activate ");
	ret = actmarkers[x-1];
	actmarkers[x-1] = true;
	GetCoords(&cx,&cy);
	_MapGraphics.PutCC(cx,cy,_Players[x-1]);
	return ret;
}
int Hex::ClearCCs(int numb){
	int i,cx,cy;
	for (i=0;i<MAX_PLAYERS;++i){
		if ((i == numb-1) || (numb == 0)){
			if (actmarkers[i]){
				GetCoords(&cx,&cy);
				_MapGraphics.ClearCC(cx, cy, _Players[i]);
			}
			actmarkers[i] = false;
		}
	}
	return 1;
}

LinkedHexes* Hex::GetLinkedHexes(){
	return &neighboors;
}

void Hex::SetId(string name){
	id = name;
}