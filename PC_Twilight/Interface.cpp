#include "FreeRoam.cpp"

Interface::Interface(){
	sets = 0;
	rdy = false;
	CurrentPlayer = -1;
}
int Interface::SetSettings(GameStats* nsets){
	sets = nsets;
	return 1;
}
bool Interface::SetBuff(const string line){
	if (rdy)
		return false;
	strcpy(buffer,line.c_str());
	rdy = true;
	return true;
}
int Interface::SetCurrPlayer(int x){
	if (CurrentPlayer == x)
		return -1;
	cout<<x<<endl;
	cout<<c_Prefix<<"----- Turn goes to "<<_Players[x]->GetName()<<'['<<x+1<<"] -----"<<endl;
	CurrentPlayer = x;
	_StatusArea.Draw();
	_MapArea.SetBackColor();
	return x;
}
int Interface::GetCurrPlayer(){
	return CurrentPlayer;
}

int Interface::FreeRoam(InterType toget, int*x, int*y,int*z){
	int i,m,n; // OMGSOMANY!!11one
	int a=0,b=0,c=0; // a,b - current coord (dont touch outside of css). c - variable
	if (sets == 0)
		throw throwable("Interface::FreeRoam(): sets == 0");
	if (toget == it_css){
		vector<int> tempvec = _GrIn.SysChoise("Choose a system");
		*x = tempvec[0];
		*y = tempvec[1];
		return 1;
	}
	if ((x!=0)&&(y!=0)){
		a = *x;
		b = *y;
	}
	if (!PrintOrder(toget,x,y,z))
		return 1;
	while (!rdy)
		taskMgr->poll();
	rdy = false;
	while (strlen(buffer)!=0){
		i=0;
		while (buffer[i]==' ')
			++i;
		if ((buffer[i] == '#')||(buffer[i] == '\n'))
			continue;
		if (((nt_streq(c_Help1, &(buffer[i]) )) == nt_strlen(c_Help1)) ||
			((nt_streq(c_Help2, &(buffer[i]) )) == nt_strlen(c_Help2)) ||
			((nt_streq(c_Help3, &(buffer[i]) )) == nt_strlen(c_Help3))) {
			cout<<c_HelpMessage;
			continue;
		}
		if ((nt_streq(c_ChooseSystem, &(buffer[i]) )) == nt_strlen(c_ChooseSystem)){
			if (ChooseSystem(toget,x,y) == 0)
				continue;
			else
				return 1;
		}
		if ((nt_streq(c_ChoosePlanet, &(buffer[i]) )) == nt_strlen(c_ChoosePlanet)){
			if (ChoosePlanet(toget,a,b,x,y) == 0)
				continue;
			else
				return 1;
		}
		if ((nt_streq(c_ChooseUnit, &(buffer[i]) )) == nt_strlen(c_ChooseUnit)){
			if (ChooseUnit(toget,x,y,z) == 0)
				continue;
			else
				return 1;
		}
		if ((nt_streq(c_ChooseOption, &(buffer[i]) )) == nt_strlen(c_ChooseOption)){
			if (ChooseOption(toget,z) == 0)
				continue;
			else
				return 1;
		}
		if ((nt_streq(c_ChooseValue, &(buffer[i]) )) == nt_strlen(c_ChooseValue)){
			if (ChooseValue(toget,z,y) == 0)
				continue;
			else
				return 1;
		}
		if ((nt_streq(c_GetCurrent, &(buffer[i]) )) == nt_strlen(c_GetCurrent)) {
			if (_Map.GetHexh(a,b) == 0){
				cout<<c_Prefix<<"Curr coords: "<<a<<", "<<b<<endl;
				PrintError("Wrong coords");
				continue;
			}
			cout<<c_Prefix<<"Current system: {"<< _Map.GetHexh(a,b)->GetId() <<"} at ( "<<a<<", "<<b<<")\n";
			continue;
		}
		if ((nt_streq(c_ViewGalaxyPlanets, &(buffer[i]) )) == nt_strlen(c_ViewGalaxyPlanets)){
			ViewGalaxyPlanets();
			continue;
		}
		if ((nt_streq(c_ViewGalaxyCounters, &(buffer[i]) )) == nt_strlen(c_ViewGalaxyCounters)){
			ViewGalaxyCounters();
			continue;
		}
		if ((nt_streq(c_ViewGalaxyResources, &(buffer[i]) )) == nt_strlen(c_ViewGalaxyResources)) {
			ViewGalaxyResources();
			continue;
		}
		if ((nt_streq(c_ViewGalaxyExtendent, &(buffer[i]) )) == nt_strlen(c_ViewGalaxyExtendent)) {
			ViewGalaxyExtendent();
			continue;
		}
		if ((nt_streq(c_ViewGalaxyArmies, &(buffer[i]) )) == nt_strlen(c_ViewGalaxyArmies)){
			ViewGalaxyArmies();
			continue;
		}
		if ((nt_streq(c_ViewSystemArmies, &(buffer[i]) )) == nt_strlen(c_ViewSystemArmies)){
			if (nt_roll (buffer, &i, 0)<=0){  // ÏÎÄÐÅÇÀÒÜ ÔÓÍÊÖÈÞ
				ViewSystemArmies(a,b);			// ÏÎÄÐÅÇÀÍÎ
			}
			else{
				m = nt_tonumber(&buffer[i]);
				if (nt_roll (buffer, &i, 0)<=0){
					PrintError("usage: (vsp x,y)");
					continue;
				}
				n = nt_tonumber(&buffer[i]);
				ViewSystemArmies(m,n);
			}		
			cout<<endl;
			continue;
		};
		if ((nt_streq(c_ViewSystemPlanets, &(buffer[i]) )) == nt_strlen(c_ViewSystemPlanets)) {
			ViewSystemPlanets(a,b);
			continue;
		}
		if (((nt_streq(c_ViewPlayers1, &(buffer[i]) )) == nt_strlen(c_ViewPlayers1))||
			((nt_streq(c_ViewPlayers2, &(buffer[i]) )) == nt_strlen(c_ViewPlayers2))){
			ViewPlayersInfo();
			continue;
		}
		if ((nt_streq(c_ViewObjectivesLaws, &(buffer[i]) )) == nt_strlen(c_ViewObjectivesLaws)){
			ViewObjectivesLaws();
			continue;
		}
		if (((nt_streq(c_ViewTrades, &(buffer[i]) )) == nt_strlen(c_ViewTrades))){
			ViewPlayersTrades();
			continue;
		}
		if (((nt_streq(c_Confirm1, &(buffer[i]) )) == nt_strlen(c_Confirm1))||
			((nt_streq(c_Confirm2, &(buffer[i]) )) == nt_strlen(c_Confirm2))||
			((nt_streq(c_Confirm3, &(buffer[i]) )) == nt_strlen(c_Confirm3))){
				cout<<c_Prefix<<"Confirmed."<<endl;
				if (DoubleCheck())
					return 2;
				continue;
		}
		if ((nt_streq(c_Pass, &(buffer[i]) )) == nt_strlen(c_Pass)){
				cout<<c_Prefix<<"Passed."<<endl;
				if (DoubleCheck())
					return 3;
				continue;
		}
		PrintError("Unrecognized command");
	}
	return 1;
}
// free roam end-------------------------------------------
bool Interface::DoubleCheck(){
	/*cout<<c_Prefix<<"Are you sure (y/n)? :"<<endl;
	while (( !feof(stdin) )&&( fgets(buffer, 100 , stdin)!=0 )&&(buffer[0]!='y')&&(buffer[0]!='n')){}
	return (buffer[0]=='y');*/
	return true; //debug
}
bool Interface::DoubleCheck(int x){
	char c;
	cout<<c_Prefix<<"Are you agreed to use this result (y/n)? :"<<x<<endl;
	while ((cin>>c,c!= 'y')&&(c != 'n')){}
	return (c=='y');
}
bool Interface::DoubleCheck(int x, int y){
	char c;
	cout<<c_Prefix<<"Are you agreed to use this results (y/n)? :"<<x<<','<<y<<endl;
	while ((cin>>c,c!= 'y')&&(c != 'n')){}
	return (c=='y');
}
int Interface::PrintError(const string str){
	cout<<c_Prefix<<"Error: "<<str<<"\n";
	return 1;
}
int Interface::PrintToSpawn(spawnarmy* UT){
	int i;
	cout<<c_Prefix<<"Left to place: ";
	for (i=0;i<MAX_UNIT;++i){
		if (UT->unit[i]!=0)
			cout<<ShipsFull[i]<<": "<<UT->unit[i]<<"; ";
	}
	cout<<endl;
	return 1;
}
int Interface::PrintThingPlayer(int who, const string str){
	if (str.size() == 0)
		throw throwable("Interface::PrintThing == 0");
	if (_Players[who]->GetConnection() == -1){
		cout<<c_Prefix<<str<<endl;
		_ChatArea.AddLine(str);
	}
	return 1;
}
int Interface::PrintThingAll(const string str){
	string buff;
	if (str.size() == 0)
		throw throwable("Interface::PrintThing == 0");
	cout<<c_Prefix<<" /all "<<str<<endl;
	buff = string("/all: ") + str;
	_ChatArea.AddLine(buff);
	return 1;
}



int Interface::GetGalFile(string& str){
	(str=PATH_TO_DATA);
	(str+="gal4p.tdc");
	return 1;
}
int Interface::GetMapFile(string& str){
	(str=PATH_TO_DATA);
	(str+="map4p.tdc");
	return 1;
}
int Interface::GetSystemsFile(string& str, SystemType ST){
	(str=PATH_TO_DATA);
	switch(ST){
		case RedSys:(str+="red.tdc");
			break;
		case EmptySys:(str+="empty.tdc");
			break;
		case PlanetSys:(str+="planets.tdc");
			break;
		case HomeSys:(str+="home.tdc");
			break;
		case SpecSys:(str+="special.tdc");
			break;
		default: throw throwable("Interface::GetSystemsFile bad system");
			break;
	}
	return 1;
}
string	Interface::GetPlayerName(string  str, int n){
	char nom[] = "__";
	(str="player");
	nom[0] = (char)n + '1';
	(str+=nom);
	return str;
}
string	Interface::GetPlayerPass(string  str, int n){
	char nom[] = "";
	(str=nom);
	return str;
}
int Interface::GetHex(int *x, int *y){
	cout<<"  Choose a Hex: ";
	cin>>(*x)>>(*y);
	cout<<endl;
	return 1;
}
int Interface::GetNumber(int *x, int min, int max){
	int c;
	cout<<"  Enter a Number: ";
	cin>>c;
	cout<<endl;
	if (c > max){
		cout<<"Number too big"<<endl;
		return 0;
	}
	else if (c < min){
		cout<<"Number too small"<<endl;
		return 0;
	}
	(*x) = (int)c;
	return 1;
}
int Interface::GetPlanet(Planet* planet){
	planet = 0;
	return 1;
}
int Interface::PrintDeckList(PowVec<Hex> * list){
	PowVec<Hex>*temp;
	int i=1;
	temp = list;
	cout<<"  Deck: ";
	while (temp!=0){
		cout<<i<<": "<<temp->elem->GetId()<<", ";
		++i;
		temp = temp->next;
	}
	cout<<"End."<<endl;
	return 1;
}
int Interface::PrintWrongHex(int x, int y){
	cout<<x<<", "<<y<<" are not suitable coords!"<<endl;
	return 1;
}
int Interface::PrintWrongHex(){
	cout<<"  Wrong coords!"<<endl;
	return 1;
}
int Interface::PrintEmptyCoords(Map * map, int round){
	/*int i, k;
	cout<<"  Still not allocated coords are: ";
	k = map->GetMaxRadius();
	for (i=0; i<k*k; ++i){
		if ((map->GetRoundh((i/k)-(k-1)/2,(i%k)-(k-1)/2) == round)&&(map->GetHexh((i/k)-(k-1)/2,(i%k)-(k-1)/2) == 0))
			cout<<'('<<((i/k)-(k-1)/2)<<','<<((i%k)-(k-1)/2)<<"); ";
	}
	cout<<"End."<<endl;*/
	return 1;
}
int Interface::PrintPlayerName(Player * player){
	cout<<"  Current Player: "<<(player->GetName())<<endl;
	return 1;
}
int Interface::PrintGalaxy(Map * map){
	/*int x, y, k;
	cout<<"  Created Galaxy looks like:"<<endl;
	k = map->GetMaxRadius();
	for (y = -k; y<=k; ++y){
		for (x = -k; x<=k; ++x){
			if (map->GetRoundh(x,y) != '-'){
				cout<<'('<<(x)<<','<<(y)<<") = '";
				if (map->GetHexh(x,y) != 0)
					cout<<(map->GetHexh(x,y)->GetId())<<"'; ";
				else
					cout<<"ERROR";
			}
		}
		cout<<endl;
	}
	cout<<"End."<<endl;*/
	return 1;
}



const char Interface::c_Help1[] = "-help";
const char Interface::c_Help2[] = "-h";
const char Interface::c_Help3[] = "help";
const char Interface::c_ChooseSystem[] = "css";
const char Interface::c_ChoosePlanet[] = "csp";
const char Interface::c_ChooseUnit[] = "csu";
const char Interface::c_ChooseOption[] = "con";
const char Interface::c_ChooseValue[] = "csv";
const char Interface::c_Pass[] = "pass";
const char Interface::c_Confirm1[] = "cnf";
const char Interface::c_Confirm2[] = "confirm";
const char Interface::c_Confirm3[] = "end";
const char Interface::c_GetCurrent[] = "gcs";
const char Interface::c_ViewGalaxyPlanets[] = "vgp";
const char Interface::c_ViewGalaxyCounters[] = "vgc";
const char Interface::c_ViewGalaxyArmies[] = "vga";
const char Interface::c_ViewGalaxyResources[] = "vgr";
const char Interface::c_ViewGalaxyExtendent[] = "vge";
const char Interface::c_ViewSystemPlanets[] = "vsp";
const char Interface::c_ViewSystemArmies[] = "vsa";
const char Interface::c_ViewPlayers1[] = "vpi";
const char Interface::c_ViewPlayers2[] = "vps";
const char Interface::c_ViewObjectivesLaws[] = "vol";
const char Interface::c_ViewTrades[] = "vpt";

const char Interface::c_Prefix[] = "> ";
const char Interface::c_UnknownInput[] = "> Error: unrecognized input.\n";
const char Interface::c_HelpMessage[] = "> -h | --help | help : Help.\n"
"> css x,y : Choose system.\n"
"> csp N : Choose planet.\n"
"> csu N : Choose unit.\n"
"> con N : Choose option number.\n"
"> pass : Pass.\n"
"> cnf | confirm | end : Confirm.\n"
"> gcs : Get current system.\n"
"> vgp : Viev galaxy plantes.\n"
"> vga : Viev galaxy armies. TotalFleetPower = (Sum(10-pow),HP)\n"
"> vgr : Viev galaxy resources.\n"
"> vge : Viev galaxy extended.\n"
"> vsp x,y : Viev system planets.\n"
"> vsp : Viev system planets.\n"
"> vsa x,y : Viev system armies.\n"
"> vsa : Viev system armies.\n"
"> vpi | vps : Viev players info.\n"
"> vpi name | vpi N : Viev player info.\n";