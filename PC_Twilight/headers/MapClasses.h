class LinkedHexes{
	vector<Hex*> hexes;
	vector<LinkType> links;
public:
	LinkedHexes();
	LinkType GetLink(Hex* hex);
	LinkType GetLink(int i);
	int AddLink(Hex* hex, LinkType LT);
	int DeleteLink(Hex* hex, LinkType LT);
	Hex* GetLinkedHex(int i);
	int GetLinkNumber();
	void reset();
};

class SpeedMap{
	int* distances;
public:
	SpeedMap();
	~SpeedMap();
	int CalculateMap(Player* player, Hex* hex);
	int CalculateMap(Hex* hex);//расчет для пустой начальной карты
	void reset();
	int GetDistance(Hex* hex);
	int GetDistance(Player* player, Hex* from, Hex* to);
	//int GetHexNumber(Hex* hex);
	bool IsPassable(Player* player, Hex* hex);
	void ShowMap();//debug
};

struct PathStep{
	Hex* hex;
	int speed;
};

class PathFinder{
	vector<vector<PathStep>> marchroutes;
	Hex* from;
	Hex* to;
	int speed;
	Player* player;
	SpeedMap* speedmap;
public:
	PathFinder();
	PathFinder(Hex* hex1, Hex* hex2, int sp, Player* owner, SpeedMap* spmap);
	void set(Hex* hex1, Hex* hex2, int sp, Player* owner, SpeedMap* spmap);
	void reset();
	vector<Hex*> NextStep(Hex* hex, int sp);
	int SplitRoutes(vector<vector<PathStep>>::iterator tail, vector<vector<PathStep>>* routes);
	int FindRoutes();
	void ShowRoutes();//debug
	bool IsHexInRoutes(Hex* hex);
	vector<Hex*> AvailableHexes();
	int RoutesThroughHex(Hex* hex);
};