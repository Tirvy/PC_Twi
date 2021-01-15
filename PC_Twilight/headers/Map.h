#define MAX_ROUND '4'

class Map{
	friend void LoadMap(list<string>::iterator begin, list<string>::iterator end);

	//int* HexRound; // the Round in which this hex is layed. 0 for mecatol, -1 for unalailable, abcdefgh - for homesystems.
	//Hex ** Hexes;
	//list<Hex*> worms[wh_MAX];
	//int k; // Koef for translating coord to memory
	int Initialize(int SystemsNumber, int in_k); // Basic initiaization of params
	//int SetPlayerHSh(int y, int x, int player); //sets player homesystems locations 
	//int SetPlayerHSv(int y, int x, int player);
	//int SetRoundh(int x, int y, int round); //sets Round for (x,y).
	//int SetRoundv(int x, int y, int round); // here and later h=che-style, v=VW-style

	vector<Hex*> hexlist; //ZoldnMap, цикл по координатам - зло, ибо есть шансы упасть за край мира, будут циклы просто по гексам
public:
	Map();
	//int GetMaxRadius();
	int LaySystemh(int x, int y, Hex* hex); // puts system in (x,y)
	//int LaySystemv(int x, int y, Hex* hex); // if system<>0 - returns 0 with no actions 
	Hex * GetHexh(int x, int y) const; // returns system in (x,y)
	//Hex * GetHexv(int x, int y) const;
	//Hex ** GetHexes();
	//list<Hex*> & GetWormholes(WormholeType type);
	//int GetHexesNumber();
	//int GetSysByRoundh(int round, int*x,int*y);
	//int GetSysByRoundv(int round, int*x,int*y);
	//int GetRoundh(int x,int y) const; // returns Round for (x,y)
	//int GetRoundv(int x,int y);
	int TranslateToNumber(int x, int y);
	void TransletaToCoords(int n, int* x, int* y);
	friend class MapTranslator;
	
	//ZoldnMap methods
	friend class ZoldnMapTranslator;
	int CreateHexLinks(bool boundary = true, bool portals = true);//заполняет вектора соседей
	void RemovePortalLinks();//удаляет связи между порталами
	vector<Hex*>* GetHexList();//возвращает список гексов *>*
	int Hex2Int(Hex* hex);//номер гекса в списке, если нет, то -1
	Hex* Int2Hex(int k);//возвращает гекс по номеру в списке
}
_Map;

/*
Large Map rounds Che-style:
-1	-1	4	4	4	4	4	-1	-1
-1	4	3	3	3	3	4	-1	-1
-1	4	3	2	2	2	3	4	-1
4	3	2	1	1	2	3	4	-1
4	3	2	1	0	1	2	3	4
4	3	2	1	1	2	3	4	-1
-1	4	3	2	2	2	3	4	-1
-1	4	3	3	3	3	4	-1	-1
-1	-1	4	4	4	4	4	-1	-1

Large Map rounds VW-style:
-1	-1	-1	4	4	4	-1	-1	-1
-1	4	4	3	3	3	4	4	-1
4	3	3	2	2	2	3	3	4
4	3	2	1	1	1	2	3	4
4	3	2	1	0	1	2	3	4
4	3	2	2	1	2	2	3	4
4	4	3	3	2	3	3	4	4
-1	-1	4	4	3	4	4	-1	-1
-1	-1	-1	-1	4	-1	-1	-1	-1
*/