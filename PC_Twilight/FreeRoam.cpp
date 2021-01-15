//RaceTech заменил tt_MAX в циклах

int Interface::PrintOrder(const InterType order, int*x, int*y,int*z){
	switch(order){
		case it_css: if ((x == 0)||(y==0)) throw throwable("it_css must have X and Y to get result");
				cout<<c_Prefix<<"Choosing system mode (css)\n";
				break;
		case it_csp: if ((x == 0)||(y==0)) throw throwable("it_csp must have X and Y to get result");
				cout<<c_Prefix<<"Choosing planet mode (csp)\n";
				break;
		case it_csu:  if ((x == 0)||(y==0)) throw throwable("it_css must have X and Y to get result");
				cout<<c_Prefix<<"Choosing unit mode (csu)\n";
				break;
		case it_csc: if ((x == 0)||(y==0)) throw throwable("it_csc must have X and Y to get result");
				cout<<c_Prefix<<"Choosing carrier mode (csu)/(csp)\n";
				break;
		case it_con: if (z == 0) throw throwable("it_con must have Z to get result");
				cout<<c_Prefix<<"Choosing option mode (con)\n";
				break;
		case it_csv:  if ((z == 0)||(y==0)) throw throwable("it_css must have Y and Z to get result");
				cout<<c_Prefix<<"Choosing value mode (csv)\n";
				break;
		case it_cnf: cout<<c_Prefix<<"Confirm/Pass mode\n";
				break;
		case it_roam: cout<<c_Prefix<<"Roaming mode\n";
				break;
		default: cout<<c_Prefix<<"Sum Ting Wong mode\n";
	}
	return 1;
}
 int Interface::ChooseSystem(const InterType toget, int*x,int*y){
	int a=*x,b=*y,c = 0,i=0;
	if (toget!=it_css){
		PrintError("Forbidden use in this mode.");
		return 0;
	}
	if (nt_roll (buffer, &i, 0)<=0){
		PrintError("usage: (css x,y)");
		return 0;
	}
	c = nt_tonumber(&buffer[i]);
	if (nt_roll (buffer, &i, 0)<=0){
		PrintError("usage: (css x,y)");
		return 0;
	}
	a = c;
	b = nt_tonumber(&buffer[i]);
	if (_Map.GetHexh(a,b) != 0)
		cout<<c_Prefix<<"Chosen system: {"<< _Map.GetHexh(a,b)->GetId() <<"} at ( "<<a<<", "<<b<<")\n";
	else{
		PrintError("Wrong coords");
		return 0;
	}
	*x = a;
	*y = b;
	return 1;
}
 int Interface::ChoosePlanet(const InterType toget,int a,int b,int*x,int*y){
	int c,i=0;
	if ((toget!=it_csp)&&(toget!=it_roam)&&(toget!=it_csc)){
		PrintError("Forbidden use in this mode.");
		return 0;
	}
	if (_Map.GetHexh(a,b) == 0){
		PrintError("Wrong coords");
		return 0;
	}
	if (nt_roll (buffer, &i, 0)<=0){
		PrintError("usage: (csp n)");
		return 0;
	}
	c = nt_tonumber(&buffer[i]);
	if (_Map.GetHexh(a,b)->GetPlanet(c) == 0){
		PrintError("Planet is our of reach!");
		return 0;
	}
	cout<<c_Prefix<<"Chosen planet: {"<<_Map.GetHexh(a,b)->GetPlanet(c)->GetName()<<"} in {"<<_Map.GetHexh(a,b)->GetId()<<"} at ( "<<a<<", "<<b<<")\n";
	*x = 'p';
	*y = c;
	return 1;
}
int Interface::ChooseUnit(const InterType toget,int*x,int*y,int*z){
	int i=0,a,b,c=0;
	Army* tarmy = 0;
	if (z==0){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if (((*aiter)->GetHex() == _Map.GetHexh(*x,*y)) && ((*aiter)->GetPlanet() == 0)){
				tarmy = *aiter;
				break;
			}
		}
		if (tarmy == 0)
			throw throwable("No unit in space",*x,*y);
	}
	else
		c=*z;
	if ((toget!=it_csc)&&(toget!=it_csu)){
		PrintError("Forbidden use in this mode.");
		return 0;
	}
	if ((nt_roll (buffer, &i, 0)<=0)&&(c == 0)){
		PrintError("usage: (csu n)");
		return 0;
	}
	a = nt_tonumber(&buffer[i]);
	if ((z != 0)&&(nt_roll (buffer, &i, 0)<=0)){
		PrintError("usage: (csu 'planet number' 'unit number')");
		return 0;
	}
	if (c!=0)
		b = nt_tonumber(&buffer[i]);
	//cout<<c<<(_GameStats.GetArmies())[c-1].Number()<<','<<a<<','; //Maybe here is some bug, who knows?
	/*if ((_GameStats.GetArmies())[c-1].Number() < a){
		PrintError("Not so many units in the army");
		return 0;
	}*/
	*x = 'u';
	if (z == 0)
		*y = a;
	else {
		*z = a;
		*y = b;
	}
	return 1;
}
int Interface::ChooseOption(const InterType toget, int*x){
	int c,i=0;
	if (toget != it_con){
		PrintError("Forbidden in this mode");
		return 0;
	}
	if (nt_roll (buffer, &i, 0)<=0){
		PrintError("usage: (con x)");
		return 0;
	}
	c = nt_tonumber(&buffer[i]);
	if ((c>(*x)) || (c<=0)){
		PrintError("Option is out of list");
		return 0;
	}
	if (x==0)
		throw throwable("Interface::ChooseOption  x == 0");
	*x = c;
	return 1;
}
int Interface::ChooseValue(const InterType toget, int*x, int*y){
	int a,b,i=0;
	if (toget != it_csv){
		PrintError("Forbidden in this mode");
		return 0;
	}
	if ((x==0)||(y==0))
		throw throwable("Interface::ChooseValue no x/y");
	
	if (nt_roll (buffer, &i, 0)<=0){
		PrintError("usage: (csv x y)");
		return 0;
	}
	a = nt_tonumber(&buffer[i]);
	if ((a>(*x)) || (a<=0)){
		cout<<*x<<','<<a; // debug
		PrintError("Value is out of list");
		return 0;
	}
	if (nt_roll (buffer, &i, 0)<=0){
		PrintError("usage: (csv x y)");
		return 0;
	}
	b = nt_tonumber(&buffer[i]);
	*x = a;
	*y = b;
	return 1;
}
int Interface::ViewGalaxyPlanets(){
	/*int k,i,j,l;
	k = _Map.GetMaxRadius();
	for (i = k; i>=-k; --i){
		if (abs(i)%2 == 1)
			cout<<"    ";
		for (j = -k; j<=k; ++j){
			if (_Map.GetRoundh(j,i) != '-'){
				cout<<'|';
				for (l=1;l<=3;++l){
					if (_Map.GetHexh(j,i)->GetPlanet(l) == 0)
						cout<<" - ";
					else{
						if (_Map.GetHexh(j,i)->GetPlanet(l)->GetOwner() == 0)
							cout<<" o ";
						else
							cout<<'('<<_Map.GetHexh(j,i)->GetPlanet(l)->GetOwner()->GetId()<<')';
					}
				}
				cout<<'|';
			}
			else
				cout<<"        ";
		}
		cout<<endl<<endl;
	}*/
	return 0;
}
int Interface::ViewGalaxyCounters(){
	/*int k,i,j,l;
	k = _Map.GetMaxRadius();
	for (i = k; i>=-k; --i){
		if (abs(i)%2 == 1)
			cout<<"    ";
		for (j = -k; j<=k; ++j){
			if (_Map.GetRoundh(j,i) != '-'){
				cout<<'|';
				for (l=1;l<=_GameStats.GetPlayersNumber();++l){
					if (_Map.GetHexh(j,i)->GotCC(l))
						cout<<"P"<<l;
					else
						cout<<"  ";
				}
				cout<<'|';
			}
			else
				cout<<"        ";
		}
		cout<<endl<<endl;
	}*/
	return 0;
}
int Interface::ViewGalaxyMovable(){
	/*int k,i,j,l;
	k = _Map.GetMaxRadius();
	for (i = k; i>=-k; --i){
		if (abs(i)%2 == 1)
			cout<<"    ";
		for (j = -k; j<=k; ++j){
			if (_Map.GetRoundh(j,i) != '-'){
				cout<<'|';
				for (l=1;l<=_GameStats.GetPlayersNumber();++l){
					if ((! _Map.GetHexh(j,i)->GotCC(l))&&(FindArmy(j,i,_Players[l-1]) != 0))
						cout<<"A"<<l;
					else
						cout<<"  ";
				}
				cout<<'|';
			}
			else
				cout<<"        ";
		}
		cout<<endl<<endl;
	}*/
	return 0;
}
int Interface::ViewGalaxyResources(){
	/*int k,i,j,l,m,n;
	k = _Map.GetMaxRadius();
	for (i = k; i>=-k; --i){
		if (abs(i)%2 == 1)
			cout<<"     ";
		for (j = -k; j<=k; ++j){
			if (_Map.GetRoundh(j,i) != '-'){
				cout<<'|';
				m=0;
				n=0;
				for (l=1;l<4;++l){
					if (_Map.GetHexh(j,i)->GetPlanet(l) != 0){
						m+=_Map.GetHexh(j,i)->GetPlanet(l)->GetRes();
						n+=_Map.GetHexh(j,i)->GetPlanet(l)->GetInf();
					}
				}
				printf("%3d,%2d ",m,n);
				cout<<'|';
			}
			else
				cout<<"         ";
		}
		cout<<endl<<endl;
	}*/
	return 0;
}
int Interface::ViewSystemPlanets(int a, int b){
	/*int i=0,l;
	if (nt_roll (buffer, &i, 0)<=0)
		cout<<c_Prefix<<"Showing system at "<<a<<", "<<b<<endl;
	else{
		a = nt_tonumber(&buffer[i]);
		if (nt_roll (buffer, &i, 0)<=0){
			PrintError("usage: (vsp x,y)");
			return 0;
		}
		b = nt_tonumber(&buffer[i]);
		cout<<c_Prefix<<"Showing system at "<<a<<", "<<b<<endl;
	}
	for (l=1;l<=3;++l){
		if (_Map.GetHexh(a,b)->GetPlanet(l) != 0){
			cout<<c_Prefix<<"{"<<_Map.GetHexh(a,b)->GetPlanet(l)->GetName()<<"}["<<l<<"] in {"<<_Map.GetHexh(a,b)->GetId()<<"} at ( "<<a<<", "<<b<<")\n";
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetOwner() != 0)
				cout<<c_Prefix<<"    Owner is: "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetOwner()->GetName()<<" ("<<_Map.GetHexh(a,b)->GetPlanet(l)->GetOwner()->GetId()<<")\n";
			cout<<c_Prefix<<"    Res: "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetRes()<<"; "<<"Inf:"<<_Map.GetHexh(a,b)->GetPlanet(l)->GetInf()<<"; ";
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Red) > 0)
				cout<<"Tech:Red - "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Red)<<"; ";
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Blue) > 0)
				cout<<"Tech:Blue - "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Blue)<<"; ";
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Green) > 0)
				cout<<"Tech:Green - "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Green)<<"; ";
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Yellow) > 0)
				cout<<"Tech:Yellow - "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetBonus(Yellow)<<"; ";
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetSpecial() > st_ZERO)
				switch(_Map.GetHexh(a,b)->GetPlanet(l)->GetSpecial()){
					case ShockTroops: cout<<"Special: Shock Troops";
						break;
					case Fighters: cout<<"Special: Fighters";
						break;
					case GroundForces: cout<<"Special: Ground Forces";
						break;
					case TradeStation: cout<<"Special: Trade Station";
						break;
				}
		cout<<endl;
		}
	}*/
	return 0;
}
int Interface::PrintSystemArmy(Hex * hex,Player * player){
	/*int i;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetOwner() == player) && ((*aiter)->GetHex() == hex) && ((*aiter)->GetPlanet() == 0)){
			cout<<c_Prefix<<"In space: ";
			for (i=GF; i<MAX_UNIT; ++i){
				if ((*aiter)->StackSize((UnitType)i)!=0)
					cout<<ShipsFull[i]<<": "<<(*aiter)->StackSize((UnitType)i)<<"; ";
			}
			cout<<endl;
		}
	}
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetOwner() == player) && ((*aiter)->GetHex() == hex) && ((*aiter)->GetPlanet() != 0)){
			cout<<c_Prefix<<"On Planet {"<<(*aiter)->GetPlanet()->GetName()<<"}: ";
			for (i=GF; i<MAX_UNIT; ++i){
				if ((*aiter)->StackSize((UnitType)i)!=0)
					cout<<ShipsFull[i]<<": "<<(*aiter)->StackSize((UnitType)i)<<"; ";
			};
			cout<<endl;
		}
	}*/
	return 1;
}
void Interface::ViewGalaxyExtendent(){
	/*int k = _Map.GetMaxRadius();
	int m=0;
	for (int i = k; i>=-k; --i){
		for (int l=1;l<=3;l++){
			if (abs(i)%2 == 1)
				cout<<"      ";
			for (int j = -k; j<=k; ++j){
				if (_Map.GetRoundh(j,i) != '-'){
					cout<<'|';
					int res=0;
					int inf=0;
					if (_Map.GetHexh(j,i)->GetPlanet(l) != 0){
						if (_Map.GetHexh(j,i)->GetPlanet(l)->GetOwner() == 0)
							printf("( )");
						else{
							m=_Map.GetHexh(j,i)->GetPlanet(l)->GetOwner()->GetId();
							printf("(%d)",m);
						};
						res=_Map.GetHexh(j,i)->GetPlanet(l)->GetRes();
						inf=_Map.GetHexh(j,i)->GetPlanet(l)->GetInf();
						printf("%d,%d,",res,inf);
						m=0;
						//вывод техов/спец абилок планет
						for (TechTree TT=Red;TT<=Yellow;TT=(TechTree)((int)TT+1)){
							if (_Map.GetHexh(j,i)->GetPlanet(l)->GetBonus(TT)>0)
								for (int z=0; z<_Map.GetHexh(j,i)->GetPlanet(l)->GetBonus(TT);z++){
									cout<<TechColorShort[TT];
									m++;
								};
						};
						if (_Map.GetHexh(j,i)->GetPlanet(l)->GetSpecial() != st_ZERO)
							m+=2;
						cout<<SpecialShort[_Map.GetHexh(j,i)->GetPlanet(l)->GetSpecial()];
						if (m==0)
							printf("  ");
						if (m==1)
							printf(" ");
					}
					else{
						if (l==1){
							cout<<"         ";
						}
						else {
							if (l==2){//вывод опасностей
								cout<<DangersLong[_Map.GetHexh(j,i)->GetDanger()];
							}
							else{//вывод вормхолов
								m=0;
								for (WormholeType WHT=wh_A; WHT<=wh_D; WHT=(WormholeType)((int)WHT+1)){
									if (_Map.GetHexh(j,i)->GotPortal(WHT)){
										cout<<WormholeShort[WHT];
										m+=2;
									};
								};
								while (m<9){
									cout<<" ";
									m++;
								};
							};
						};
					};
					cout<<'|';
				}
				else
					if (j<0)
						cout<<"         ";
			}
			cout<<endl;
		};
		cout<<endl;		
	}*/
};

void Interface::ViewGalaxyArmies(){
	/*cout<<"Army format: (Player id) power/HP"<<endl;
	int k = _Map.GetMaxRadius();
	int m=0;
	int n=0;
	for (int i = k; i>=-k; --i){
		if (abs(i)%2 == 1)
			cout<<"     ";
		for (int j = -k; j<=k; ++j){
			if (_Map.GetRoundh(j,i) != '-'){
				cout<<'|';
				m=0;
				n=0;
				for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
					if (((*aiter)->GetHex() == _Map.GetHexh(j,i))&&((*aiter)->GetPlanet() == 0)){
						m=(*aiter)->GetArmyHP();
						n=(*aiter)->GetArmyPower();
						if ((*aiter)->GetOwner() != 0){
							cout<<"("<<(*aiter)->GetOwner()->GetId()<<")";
							printf("%3d/%2d",n,m);
						}
						else
							cout<<"( )      ";
						break;
					}
				}
				//if (*aiter == 0)
				//	cout<<"         ";
				cout<<'|';
			}
			else
				if (j<0)
					cout<<"          ";
		}
		cout<<endl<<endl;
	}
	cout<<endl;*/
};

void Interface::ViewSystemArmies(int a, int b){
	/*cout<<c_Prefix<<"Showing system at "<<a<<", "<<b<<": "<<_Map.GetHexh(a,b)->GetId()<<endl;
	cout<<"Space fleet:"<<endl;
	int cap,gf_cap,fg_cap;
	int pas_number=0;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if (((*aiter)->GetHex() == _Map.GetHexh(a,b))&&((*aiter)->GetPlanet() == 0)){
			if ((*aiter)->GetOwner() != 0)
				cout<<"   Player["<<(*aiter)->GetOwner()->GetId()<<"]: "<<(*aiter)->GetOwner()->GetName()<<endl;
			for (vector<Unit*>::iterator titer = (*aiter)->GetUnits()->begin(); titer != (*aiter)->GetUnits()->end(); titer++){
				if (((*titer)->Class >= DS)||(((*titer)->Class <= FG)&&((*titer)->carrier == 0))){
					cout<<"      "<<ShipsShort[(*titer)->Class]<<"["<<(*aiter)->GetUnitNumber(*titer)<<"]";
					if ((*aiter)->GetOwner()->GetUnitStats()->GetParametr((*titer)->Class,sHP)>1)
						cout<<"("<<(*titer)->HP<<" hp)";
					cap=(*aiter)->GetOwner()->GetUnitStats()->GetParametr((*titer)->Class,sCP);
					gf_cap=(*aiter)->GetOwner()->GetUnitStats()->GetParametr((*titer)->Class,sGFCP);
					fg_cap=(*aiter)->GetOwner()->GetUnitStats()->GetParametr((*titer)->Class,sFGCP);
					cap=cap+gf_cap+fg_cap;	
					if (cap > 0){
						cout<<"(";
						pas_number=0;
						for (vector<Unit*>::iterator citer = (*aiter)->GetUnits()->begin(); citer != (*aiter)->GetUnits()->end(); citer++){
							if ((*citer)->carrier == *titer){
								cout<<ShipsShort[(*citer)->Class]<<"["<<(*aiter)->GetUnitNumber(*citer)<<"]";
								if ((*aiter)->GetOwner()->GetUnitStats()->GetParametr((*citer)->Class,sHP)>1)
									cout<<"("<<(*citer)->HP<<" hp)";
								cout<<"_";
								pas_number++;
							}
						}
						for (int z=pas_number; z<cap; z++)
							cout<<" 0_";
						cout<<")";
					}
					cout<<endl;
				}
			}
		}
	}
	for (int l=1;l<=3;l++){
		if (_Map.GetHexh(a,b)->GetPlanet(l) != 0){
			cout<<"Army on planet "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetName()<<"("<<
				_Map.GetHexh(a,b)->GetPlanet(l)->GetRes()<<"/"<<
				_Map.GetHexh(a,b)->GetPlanet(l)->GetInf()<<"):"<<endl;
			if (_Map.GetHexh(a,b)->GetPlanet(l)->GetOwner() != 0)
				cout<<"   Planet owner: player["<<_Map.GetHexh(a,b)->GetPlanet(l)->GetOwner()->GetId()<<"]: "<<_Map.GetHexh(a,b)->GetPlanet(l)->GetOwner()->GetName()<<endl;
			else
				cout<<"   neutral"<<endl;
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
				if (((*aiter)->GetHex() == _Map.GetHexh(a,b))&&((*aiter)->GetPlanet() == _Map.GetHexh(a,b)->GetPlanet(l))){
					if ((*aiter)->GetOwner()!=0)
						cout<<"   Player "<<(*aiter)->GetOwner()->GetId()<<"{"<<(*aiter)->GetOwner()->GetName()<<"}"<<endl;
					else
						cout<<"   neutral"<<endl;
					for (vector<Unit*>::iterator titer = (*aiter)->GetUnits()->begin(); titer != (*aiter)->GetUnits()->end(); titer++){
						cout<<"      "<<ShipsShort[(*titer)->Class]<<"["<<(*aiter)->GetUnitNumber(*titer)<<"]";
						if ((*aiter)->GetOwner()->GetUnitStats()->GetParametr((*titer)->Class,sHP)>1)
							cout<<"("<<(*titer)->HP<<" hp)";
						cout<<endl;
					}
				}
			}
		}
	}*/
}

int Interface::ViewPlayersTrades(){
	int i,j;
	for (i=0;i<_GameStats.GetPlayersNumber();++i){
		cout<<_Players[i]->GetName()<<" got:"<<endl;
		for (j=0;j<MAX_TRADES;++j)
			cout<<c_Prefix<<"      "<<'{'<<_Players[i]->GetTrade(j)->owner->GetName()<<"}'s "<<_Players[i]->GetTrade(j)->power<<" route ["<< i*MAX_TRADES+j+1 <<']'<<endl;
	}
	return 1;
}
int Interface::ViewPlayersInfo(){
	int i,j,k;
	for (i=0;i<_GameStats.GetPlayersNumber();++i){
		if ((_Players[i]->GetRace() > MAX_RACE)||(_Players[i]->GetRace() < 0))
			throw throwable("Interface::ViewPlayersInfo()",_Players[i]->GetRace());
		cout<<c_Prefix<<"Player: "<<_Players[i]->GetName()<<'['<<i+1<<"] - "<<RacesFull[_Players[i]->GetRace()]<<"\n";
		cout<<c_Prefix<<"    "<<"Strategy Cards: ";
		for (j=0;j<MAX_STRAT;++j){
			if (_Players[i]->GotStrat((StratsType)j) == 1)
				cout<<StratsFull[j]<<" available; ";
			if (_Players[i]->GotStrat((StratsType)j) == 2)
				cout<<StratsFull[j]<<" activated; ";
		}
		cout<<'\n';
		cout<<c_Prefix<<"    "<<"Counters: ";
		cout<<"SA: "<<_Players[i]->GetCountersSA()<<"; ";
		cout<<"FS: "<<_Players[i]->GetCountersFS()<<"; ";
		cout<<"CP: "<<_Players[i]->GetCountersCP()<<"; ";
		cout<<'\n';

		cout<<c_Prefix<<"    "<<"Goods: "<<_Players[i]->GetGoods()<<'\n';

		cout<<c_Prefix<<"    "<<"Got Technologies: ";
		for (j=0;j<MAX_TECH;++j)
			if (_Players[i]->GotTech((TechType)j))
				cout<<TechFull[j]<<", ";
		cout<<'\n';
		
		//planets = _Players[i]->GetPlanetsList();
		cout<<c_Prefix<<"    "<<"Untapped planets: "<<'\n';
		//while (planets!=0){
		for (vector<Planet*>::iterator piter = _Players[i]->GetPlanetsList()->begin(); piter != _Players[i]->GetPlanetsList()->end(); piter++){
			//if (planets->status==1){
			if (!(*piter)->HasState(psExhausted)){//Zoldn planet state change
				printf("%s        %10s: %3d/%3d; ",c_Prefix,(*piter)->GetName(),(*piter)->GetRes(),(*piter)->GetInf());
				cout<<SpecialFull[(*piter)->GetSpecial()];
				for (j=1;j<RaceTech;j++)//замена, было j<tt_MAX
					if ((*piter)->GetBonus((TechTree)j)>0)
						for (k=0;k<(*piter)->GetBonus((TechTree)j);++k)
							cout<<TechColorShort[j];
				cout<<'\n';
			}
			//planets = planets->next;
		}
	
		//planets = _Players[i]->GetPlanetsList();
		cout<<c_Prefix<<"    "<<"Exhausted planets: "<<'\n';
		//while (planets!=0){
		for (vector<Planet*>::iterator piter = _Players[i]->GetPlanetsList()->begin(); piter != _Players[i]->GetPlanetsList()->end(); piter++){
			//if ((planets->status==0)||(planets->status==-1)){
			if ((*piter)->HasState(psExhausted)){//Zoldn planet state change
				printf("%s        %10s: %2d /%2d ; ",c_Prefix,(*piter)->GetName(),(*piter)->GetRes(),(*piter)->GetInf());
				cout<<SpecialFull[(*piter)->GetSpecial()];
				for (j=1;j<RaceTech;j++)//замена, было j<tt_MAX
					if ((*piter)->GetBonus((TechTree)j)>0)
						for (k=0;k<(*piter)->GetBonus((TechTree)j);++k)
							cout<<TechColorShort[j];
				cout<<'\n';
			}
			//planets = planets->next;
		}
		//cout<<c_Prefix<<"    "<<"Victory Points: "<<_Players[i]->GetVPs()<<'\n';
	}
	return 1;
}
int Interface::ViewObjectivesLaws(){//не нужно бюрократия
	/*int n,i;
	PowVec<e_Objective> * otemp;
	cout<<c_Prefix<<"*laws are not done yet"<<'\n';
	cout<<c_Prefix<<"Current open Objectives are :"<<'\n';
	otemp = _GameStats.GetObjectivesOpen()->next;
	n=1;
	while (otemp!=0){
		cout<<c_Prefix<<"    "<<'['<<n<<"] <"<<otemp->elem->GetReqs()<<"> complited by:";
		for (i=0;i<_GameStats.GetPlayersNumber();++i)
			if (otemp->elem->Compited(i))
				cout<<" {"<<_Players[i]->GetId()<<"} ";
		cout<<endl;
		otemp = otemp->next;
		++n;
	}*/
	return 1;
}