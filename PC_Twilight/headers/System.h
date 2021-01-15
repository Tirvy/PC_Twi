class Hex{
	string id;
	Planet* planets[MAX_PLANETS];
	WormholeType portal[4];
	bool actmarkers[MAX_PLAYERS];
	DangerType danger;
	LinkedHexes neighboors;	//ZoldnMap
public:
	Hex();
	string GetId();
	Planet* GetPlanet(int number);
	bool GotPortal(WormholeType p);
	DangerType GetDanger();
	bool GetCoords(int* x,int* y);
	bool SetCC(int x);//X - с единицы!
	bool GotCC(int x);//X - с единицы!
	int ClearCCs(int numb = 0);//по умолчанию - убирает все, если указан номер игрока (с 1!), то только его
	friend class SystemTranslator;
	friend class Map;

	void SetId(string name);
	LinkedHexes* GetLinkedHexes();	//ZoldnMap
	int xc,yc;	//ZoldnMap
	int number;
};