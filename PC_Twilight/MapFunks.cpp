

int GetXh(Hex*hex){
	/*int i,j,k=_Map.GetMaxRadius();
	for (i=-k;i<=k;++i)
		for (j=-k;j<=k;++j)
			if (_Map.GetHexh(i,j) == hex)
				return i;
	throw throwable("GetXh not found");*/
	return hex->xc;
}
int GetYh(Hex*hex){
	/*int i,j,k=_Map.GetMaxRadius();
	for (i=-k;i<=k;++i)
		for (j=-k;j<=k;++j)
			if (_Map.GetHexh(i,j) == hex)
				return j;
	throw throwable("GetYh not found");*/
	return hex->yc;
}


Player* HexController(Hex* hex){
	Player *player = 0;
	int i;
	for (i=0;i<MAX_PLANETS;++i){
		if (hex->GetPlanet(i+1) != 0){
			if (hex->GetPlanet(i+1)->GetOwner() == 0)
				return 0;
			else if (player == 0)
				player = hex->GetPlanet(i+1)->GetOwner();
			else if (player != hex->GetPlanet(i+1)->GetOwner())
				return 0;
		}
	}
	i=0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetHex() == hex){
			if (player == 0)
				return (*aiter)->GetOwner();
			else if (player != (*aiter)->GetOwner())
				return 0;
			else
				return player;
		}
	}
	return 0;
}