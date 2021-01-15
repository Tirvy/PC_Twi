
GalTranslator::GalTranslator(){
	int i;
	alldeck = new SystemDeck();
	for (i=RedSys;i<=SpecSys;++i)
		AddDeck(alldeck,(SystemType)i,false);
}

int GalTranslator::translate(string filepath, Map * tehmap, Settings *tehset){
	/*int i, n;
	int curx, cury, k = 0;
	int StringNumber = 0;
	string str;
	bool inited = false;
	PowVec<Hex>* sys;
	SystemDeck *deckred,*deckempty,*deckplanet;
	k = tehmap->GetMaxRadius();
	if ((fi = fopen(filepath.c_str(), "rt"))==0)
		throw throwable("GalTranslator::translate Cant open file to read ",filepath);
	Interface().GetSystemsFile(str, RedSys);
	SystemTranslator().translate(str,&deckred);
	Interface().GetSystemsFile(str, EmptySys);
	SystemTranslator().translate(str,&deckempty);
	Interface().GetSystemsFile(str, PlanetSys);
	SystemTranslator().translate(str,&deckplanet);
	cury = -k;
	while (( !feof(fi) )&&( fgets(buffer, 255 , fi)!=0 )){
		++StringNumber;
		i=0;
		while ((buffer[i]==' ')||(buffer[i]==9))
			++i;
		if ((buffer[i] == '#'))
			continue;
		if ((buffer[i] == '\n')){
			++cury;
			continue;
		}
		for (curx = -k; curx<=k; ++curx){
			if ((tehmap->GetRoundh(curx,cury)>'0')&&(tehmap->GetRoundh(curx,cury)<=MAX_ROUND)){
				n = 0;
				nt_roll (buffer, &i, '$');
				nt_strcsy(str,&buffer[i]);
				++i;
				if (deckred->FindById(str) != 0){
					n = deckred->FindById(str);
					sys = deckred->Choose(n);
				}
				else if (deckempty->FindById(str) != 0){
					n = deckempty->FindById(str);
					sys = deckempty->Choose(n);
				}
				else if (deckplanet->FindById(str) != 0){
					n = deckplanet->FindById(str);
					sys = deckplanet->Choose(n);
				}
				else{
					cout<<curx<<':'<<cury;
					throw throwable("GalTranslator::translate",str.c_str(),StringNumber);
				}
				tehmap->LaySystemh(curx,cury,sys->elem);
				//int plans;
				//for (plans = 0; ((plans<MAX_PLANETS)&&(sys->elem->GetPlanet(plans+1) != 0));++plans){}
				//_MapGraphics.AddHex(sys->elem->GetId(),curx,cury,plans);
				sys->elem = 0;
				delete sys;
			}
		}
		++cury;
	}	
	fclose(fi);*/
	return 1;
}
int GalTranslator::translate(const string buffer, int cury, int num){
	/*int n,i,curx, k = 0;
	k = _Map.GetMaxRadius();
	char str[254];
	PowVec<Hex>* sys;
	i=0;
	cout<<'!'<<buffer<<'!';
	for (curx = -k; (i <= num)&&(curx <= k); ++curx){
		cout<<curx<<'.'<<cury<<'.'<<(char)_Map.GetRoundh(curx,cury)<<'.'<<_Map.GetHexh(curx,cury)<<'.';
		if (_Map.GetRoundh(curx,cury) != '-')
			++i;
	}
	--curx;
	cout<<endl;
	if (curx>k){
		throw throwable("GalTranslator::translate oor",str);
	}
	if (buffer[1] == '$'){
	}
	else if (alldeck->FindById(buffer.c_str()+1) != 0){
		n = alldeck->FindById(buffer.c_str()+1);
		sys = alldeck->Copy(n);
		//cout<<'|'<<curx<<' '<<cury<<' '<<buffer+1<<' '<<(char)_Map.GetRoundh(curx,cury)<<' '<<_Map.GetHexh(curx,cury)<<' '<<k<<endl;
		_Map.LaySystemh(curx,cury,sys->elem);
		sys->elem = 0;
		delete sys;
	}
	else{
		cout<<curx<<':'<<cury;
		throw throwable("GalTranslator::translate nf",str);
	}*/
	return 1;
}