enum SystemDeckSizes {st_Planet, st_Empty, st_Special, st_Remove};

const string ztHexesOpen = "<hexes>";
const string ztHexesClose = "</hexes>";
const string ztMapName = "Name";
const string ztPlayerNumber = "Players";
const string ztCreated = "Created";

const string ztFixed = "Fixed";
const string ztHomeSystem = "HomeSystem";
const string ztExtraHomeSystem = "ExtraHomeSystem";
const string ztRandomEmpty = "RandomEmpty";
const string ztRandomSpecial = "RandomSpecial";
const string ztRandomPlanet = "RandomPlanet";
const string ztRandomOnePlanet = "RandomOnePlanet";
const string ztRandomMultiPlanet = "RandomMultiPlanet";
const string ztRemove = "Remove";
const string ztSlot = "Slot";

class ZoldnMapTranslator{
	Map* map;
	SystemDeck *deckred,*deckempty,*deckplanet,*deckspecial,*deckHS;
	int playerNumber;
	//int HexesToPlayer;
	int manualSystemDeckSizes[4];
public:
	ZoldnMapTranslator(Map* in_map){
		deckred = 0;
		deckempty = 0;
		deckplanet = 0;
		deckspecial = 0;
		deckHS = 0;
		map = in_map;
		playerNumber = 0;
		for (int i = 0; i < 4; i++)
			manualSystemDeckSizes[i] = 0;
		//HexesToPlayer = 0;
	}
	void InitHexDecks(){
		string str;
		Interface().GetSystemsFile(str, RedSys);
		SystemTranslator().translate(str,&deckred);
		Interface().GetSystemsFile(str, EmptySys);
		SystemTranslator().translate(str,&deckempty);
		Interface().GetSystemsFile(str, PlanetSys);
		SystemTranslator().translate(str,&deckplanet);
		Interface().GetSystemsFile(str, SpecSys);
		SystemTranslator().translate(str,&deckspecial);
		Interface().GetSystemsFile(str, HomeSys);
		SystemTranslator().translate(str,&deckHS);
	}
	void ShuffleDecks(){
		deckred->shuffle();
		deckempty->shuffle();
		deckplanet->shuffle();
	}
	Hex* FindHexByID(string id){
		Hex* result = 0;
		int n;
		if (n = deckplanet->FindById(id))
			return deckplanet->Choose(n)->elem;
		if (n = deckempty->FindById(id))
			return deckempty->Choose(n)->elem;
		if (n = deckred->FindById(id))
			return deckred->Choose(n)->elem;
		if (n = deckspecial->FindById(id))
			return deckspecial->Choose(n)->elem;
		if (n = deckHS->FindById(id))
			return deckHS->Choose(n)->elem;
		cout<<"ZoldnMapTranslator::FindHexByID : Can't find hex with ID "<<id<<endl;
		return result;
	}
	int NewGameMapCreation(GameInitSettings InitS){
		Hex* slot = 0;
		string MapName;
		string filename;
		vector<string> file;
		file.clear();
		filename = InitS.MapName;// для дебага"preset4p.twm"
		//filename = InitS.GalName;
		cout<<filename<<endl;
		ifstream myfile(filename.c_str());
		string buff;
		std::istringstream iss;
		string elem1,elem2;
		int x,y,d,i;
		bool HexLoad = false;
		Hex* hex;
		int numberofhexes = 0;
		string str;
		InitHexDecks();
		if (!myfile.is_open()){
			cout<<"ZoldnMapTranslator::NewGameMapCreation : "<<filename<<endl;
			Eggog("ZoldnMapTranslator::NewGameMapCreation : Unable to open file");
			return 0;
		}
		while (getline (myfile,buff)){//считываем файл в память
			if (buff.size() == 0)//скип пустых строчек
				continue;
			if (buff[0] == '#')//скип комментов
				continue;
			file.push_back(buff);
		}
		for (vector<string>::iterator iter = file.begin(); iter != file.end(); iter++){
			iss.clear();
			iss.str(*iter);
			iss >> elem1;
			if (elem1.compare(ztMapName) == 0){
				iss >> elem2;
				MapName = elem2;
				cout<<"ZoldnMapTranslator::NewGameMapCreation : loading map "<<MapName<<endl;
				continue;
			}
			if (elem1.compare(ztPlayerNumber) == 0){
				iss >> playerNumber;
				cout<<"ZoldnMapTranslator::NewGameMapCreation : players = "<<playerNumber<<endl;
				continue;
			}
			if (elem1.compare(ztHexesOpen) == 0){
				HexLoad = true;
				continue;
			}
			if (elem1.compare(ztHexesClose) == 0){
				HexLoad = false;
				continue;
			}
			if (elem1.compare(ztCreated) == 0){
				iss>>_GameStats._ManualBuildDeck[0]>>_GameStats._ManualBuildDeck[1]>>_GameStats._ManualBuildDeck[2]>>_GameStats._ManualBuildDeck[3];
				_GameStats._IsManualCreation = true;
				//HexesToPlayer = (manualSystemDeckSizes[0] + manualSystemDeckSizes[1] + manualSystemDeckSizes[2] - manualSystemDeckSizes[3])/_GameStats.GetPlayersNumber();
				cout<<"Manual creation is ON "<<_GameStats._ManualBuildDeck[0]<<_GameStats._ManualBuildDeck[1]<<_GameStats._ManualBuildDeck[2]<<_GameStats._ManualBuildDeck[3]<<endl;
				continue;
			}
			if ((HexLoad) && (elem1.compare(ztRemove) != 0))
				numberofhexes++;
		}
		cout<<"NewGameMapCreation : was found "<<numberofhexes<<" hexes"<<endl;
		_MapGraphics.initmap(numberofhexes);//инициализация графики
		//загрузка Fixed гексов
		HexLoad = false;
		for (vector<string>::iterator iter = file.begin(); iter != file.end(); iter++){
			iss.clear();
			iss.str(*iter);
			iss >> elem1;
			if (elem1.compare(ztHexesOpen) == 0){
				HexLoad = true;
				continue;
			}
			if (HexLoad){
				if (elem1.compare(ztRemove) == 0){
					iss >> elem2;
					hex = FindHexByID(elem2);
					cout<<"Banned system "<<elem2<<endl;
					continue;
				}
				if (elem1.compare(ztFixed) == 0){
					iss >> elem2 >> x >> y;
					hex = FindHexByID(elem2);
					map->LaySystemh(x,y,hex);
					continue;
				}
				if (elem1.compare(ztHomeSystem) == 0){
					iss >> d >> x >> y;
					str = RacesFull[InitS.PlayerRaces.at(d-1)] + "_HS";
					hex = FindHexByID(str);
					map->LaySystemh(x,y,hex);
					_Players[d-1]->SetHS(hex);
					continue;
				}
				if (elem1.compare(ztExtraHomeSystem) == 0){
					iss >> d >> x >> y;
					str = RacesFull[InitS.PlayerRaces.at(d-1)] + "_Extra";
					hex = FindHexByID(str);
					if (hex){
						map->LaySystemh(x,y,hex);
						_Players[d-1]->SetExtraHS(hex);
					}
					continue;
				}
				if (elem1.compare(ztSlot) == 0){
					iss >> x >> y;
					slot = new Hex;
					slot->SetId("Slot");
					map->LaySystemh(x,y,slot);
					continue;
				}
			}
		}
		//загрузка Random гексов
		ShuffleDecks();
		HexLoad = false;
		for (vector<string>::iterator iter = file.begin(); iter != file.end(); iter++){
			iss.clear();
			iss.str(*iter);
			iss >> elem1;
			if (elem1.compare(ztHexesOpen) == 0){
				HexLoad = true;
				continue;
			}
			if (HexLoad){
				if (elem1.compare(ztRandomEmpty) == 0){
					iss >> x >> y;
					hex = deckempty->Choose(1)->elem;
					map->LaySystemh(x,y,hex);
					continue;
				}
				if (elem1.compare(ztRandomSpecial) == 0){
					iss >> x >> y;
					hex = deckred->Choose(1)->elem;
					map->LaySystemh(x,y,hex);
					continue;
				}
				if (elem1.compare(ztRandomPlanet) == 0){
					iss >> x >> y;
					hex = deckplanet->Choose(1)->elem;
					map->LaySystemh(x,y,hex);
					continue;
				}
				if (elem1.compare(ztRandomOnePlanet) == 0){
					iss >> x >> y;
					PowVec<Hex>* temp = deckplanet->GetList();
					i = 1;
					while (temp != 0){
						if (temp->elem->GetPlanet(2) == 0)
							break;
						temp = temp->next;
						i++;
					}
					hex = deckplanet->Choose(i)->elem;
					map->LaySystemh(x,y,hex);
					continue;
				}
				if (elem1.compare(ztRandomMultiPlanet) == 0){
					iss >> x >> y;
					PowVec<Hex>* temp = deckplanet->GetList();
					i = 1;
					while (temp != 0){
						if (temp->elem->GetPlanet(2) != 0)
							break;
						temp = temp->next;
						i++;
					}
					hex = deckplanet->Choose(i)->elem;
					map->LaySystemh(x,y,hex);
					continue;
				}
			}
		}
		_Map.CreateHexLinks();//определяет соседей каждого гекса
		return 1;
	}
	////ручное формирование галактики
	int CreateDecksForPlayers(bool debug = false){
		int i,j;
		InitHexDecks();
		ShuffleDecks();
		vector<Hex*> common;
		vector<Hex*>::iterator iter;
		vector<Hex*> forplayer;
		common.clear();
		int HexesToPlayer = (_GameStats._ManualBuildDeck[0] + _GameStats._ManualBuildDeck[1] + _GameStats._ManualBuildDeck[2] - _GameStats._ManualBuildDeck[3])/_GameStats.GetPlayersNumber();
		for (i = 0; i < _GameStats._ManualBuildDeck[0]; i++)
			common.push_back(deckplanet->Choose(1)->elem);
		for (i = 0; i < _GameStats._ManualBuildDeck[1]; i++)
			common.push_back(deckempty->Choose(1)->elem);
		for (i = 0; i < _GameStats._ManualBuildDeck[2]; i++)
			common.push_back(deckred->Choose(1)->elem);
		sync_shuffle(common);
		for (i = 0; i < _GameStats._ManualBuildDeck[3]; i++)
			common.erase(common.begin());
		iter = common.begin();
		HexesToPlayer = (_GameStats._ManualBuildDeck[0] + _GameStats._ManualBuildDeck[1] + _GameStats._ManualBuildDeck[2] - _GameStats._ManualBuildDeck[3])/_GameStats.GetPlayersNumber();
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
			for (j = 0; j < HexesToPlayer; j++){
				_Players[i]->AddHexToDeck(*iter);
				iter++;
			}
		}
		if (debug){
			for (i = 0; i < _GameStats.GetPlayersNumber(); i++){
				cout<<"Player "<<_Players[i]->GetName()<<" has:"<<endl;
				for (j = 0; j < HexesToPlayer; j++)
					cout<<"    "<<_Players[i]->_SystemHand.at(j)->GetId()<<endl;
			}
		}
		return 1;
	}
	int ManualGalaxyBuild(){
		int i,j,k;
		int curNumber;
		Player* curPlayer;
		bool isPlanets;
		bool isNearSpecial, checkSpecial, isNoSpecialInHand, isOtherPlaceForSpecial;
		bool isPlaceForDangers;
		Hex* hex;
		Hex* toplace;
		Hex* mecatol = 0;
		const int MAX_RING = 6;
		vector<bool> HaveToPlacePlanet;
		vector<int> ret;
		char buff[255];
		for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
			HaveToPlacePlanet.push_back(false);
		int maxring = 0;
		int current_ring = 1;
		int HexesToPlayer = (_GameStats._ManualBuildDeck[0] + _GameStats._ManualBuildDeck[1] + _GameStats._ManualBuildDeck[2] - _GameStats._ManualBuildDeck[3])/_GameStats.GetPlayersNumber();
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
			if ((*iter)->GetId().compare(MECATOLSYSTEM) == 0){
				mecatol = *iter;
				break;
			}
		}
		if (mecatol == 0){
			Eggog("ZoldnMapTranslator::ManualGalaxyBuild : No Mecatol!");
			return 0;
		}
		SpeedMap SM;
		SM.CalculateMap(mecatol);
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
			if ((*iter)->GetId().compare(MECATOLSYSTEM) == 0){
				mecatol = *iter;
				break;
			}
		}
		int rounds_sizes[MAX_RING];//убрасть в константы максимальный круг
		for (i = 0; i < MAX_RING; i++)
			rounds_sizes[i] = 0;
		//находим, сколько тайлов нужно заполнить в каждом кругу
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++)
			if ((SM.GetDistance(*iter) < MAX_RING) && ((*iter)->GetId().compare("Slot") == 0))
				rounds_sizes[SM.GetDistance(*iter)] = rounds_sizes[SM.GetDistance(*iter)]+1;
		for (i = 0; i < HexesToPlayer; i++){
			//for (j = _GameStats.Speaker;j < _GameStats.Speaker+_GameStats.GetPlayersNumber(); j++){
			for (j = 0;j < _GameStats.GetPlayersNumber(); j++){
				if (i%2 == 0)	//прямой ход выкладки
					curNumber = _GameStats.Speaker + j;
				else			//обратный ход выкладки
					curNumber = _GameStats.Speaker - j - 1 + _GameStats.GetPlayersNumber();
				curNumber = curNumber % _GameStats.GetPlayersNumber();
				curPlayer = _Players[curNumber];
				if (rounds_sizes[current_ring] == 0)
					current_ring++;
				while (true){
					hex = curPlayer->SelectSystemManualBuild();//выбрали гекс из руки
					if (HaveToPlacePlanet[curNumber] && (hex->GetPlanet(1) == 0)){//проверка на выкладку подряд двух пустых
						isPlanets = false;
						for (k = 0; k < curPlayer->_SystemHand.size(); k++)
							if (curPlayer->_SystemHand.at(k)->GetPlanet(1) != 0)
								isPlanets = true;
						if (isPlanets){
							_Interface.PrintThingPlayer(curNumber,"You have to place system with planet this turn");
							continue;
						}
					}
					sprintf(buff,"Place system on galaxy map in %d-ring",current_ring);
					ret = _GrIn.SysChoise(buff,true);
					if (ret.size() == 0)
						continue;
					toplace = _Map.GetHexh(ret[0],ret[1]);
					if (toplace->GetId().compare("Slot") != 0){//только в свободный слот
						_Interface.PrintThingPlayer(curNumber,"You can't place on this tile");
						continue;
					}
					if (SM.GetDistance(toplace) != current_ring){//проверка на выкладку в нужное кольцо
						_Interface.PrintThingPlayer(curNumber,"You can't place in this ring");
						continue;
					}
					if (hex->GetDanger() != DT_NONE){//проверка на 2 специальные рядом
						isNearSpecial = false;
						isNoSpecialInHand = false;
						for (k = 0; k < toplace->GetLinkedHexes()->GetLinkNumber(); k++)
							if (toplace->GetLinkedHexes()->GetLinkedHex(k)->GetDanger() != DT_NONE)
								isNearSpecial = true;
						for (k = 0; k < curPlayer->_SystemHand.size(); k++)
							if (curPlayer->_SystemHand[k]->GetDanger() == DT_NONE)
								isNoSpecialInHand = true;
						isOtherPlaceForSpecial = false;
						for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
							if ((*iter)->GetId().compare("Slot") == 0){
								checkSpecial = false;
								for (k = 0; k < (*iter)->GetLinkedHexes()->GetLinkNumber(); k++)
									if ((*iter)->GetLinkedHexes()->GetLinkedHex(k)->GetDanger() != DT_NONE)
										checkSpecial = true;
								if (!checkSpecial)
									isOtherPlaceForSpecial = true;
							}
						}
						if (isNearSpecial && (isNoSpecialInHand || isOtherPlaceForSpecial)){
							_Interface.PrintThingPlayer(curNumber,"You can't place next to another special system");
							continue;
						}
					}
					_Map.LaySystemh(ret[0],ret[1],hex);
					if (hex->GetPlanet(1) == 0)
						HaveToPlacePlanet[curNumber] = true;
					else
						HaveToPlacePlanet[curNumber] = false;
					rounds_sizes[current_ring] = rounds_sizes[current_ring] - 1;
					sprintf(buff,"Player %s places tile %s",curPlayer->GetName().c_str(),hex->GetId().c_str());
					_Interface.PrintThingAll(buff);
					curPlayer->RemoveHexFromDeck(hex);
					break;
				}
			}
		}
		//создает связи между выложенными порталами
		_Map.RemovePortalLinks();
		_Map.CreateHexLinks(false,true);
		return 1;
	}
};