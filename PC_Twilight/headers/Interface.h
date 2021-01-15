enum InterType { it_css, it_csp, it_csu, it_csc, it_con, it_csv, it_cnf, it_roam };

class Interface{
	char buffer[127];
	bool rdy;
	GameStats* sets;
	int CurrentPlayer;
	static const char c_Help1[];
	static const char c_Help2[];
	static const char c_Help3[];
	static const char c_ChooseSystem[];
	static const char c_ChoosePlanet[];
	static const char c_ChooseUnit[];
	static const char c_ChooseOption[];
	static const char c_ChooseValue[];
	static const char c_Pass[];
	static const char c_Confirm1[];
	static const char c_Confirm2[];
	static const char c_Confirm3[];
	static const char c_GetCurrent[];
	static const char c_ViewGalaxyPlanets[];
	static const char c_ViewGalaxyArmies[];
	static const char c_ViewGalaxyCounters[];
	static const char c_ViewGalaxyResources[];
	static const char c_ViewGalaxyExtendent[];
	static const char c_ViewSystemPlanets[];
	static const char c_ViewSystemArmies[];
	static const char c_ViewPlayers1[];
	static const char c_ViewPlayers2[];
	static const char c_ViewObjectivesLaws[];
	static const char c_ViewTrades[];
	static const char c_Prefix[];
	static const char c_HelpMessage[];
	static const char c_UnknownInput[];

public:	
	Interface();
	bool SetBuff(const string line);
	bool DoubleCheck();
	bool DoubleCheck(int x);
	bool DoubleCheck(int x, int y);
	int FreeRoam(InterType toget, int*x=0, int*y=0,int*z=0);//-~-
	int PrintError(const string str);
	int PrintOrder(const InterType order, int*x, int*y,int*z);
	int SetSettings(GameStats* nsets);
	int PrintToSpawn(spawnarmy* UT);
	int ChooseSystem(const InterType toget, int*x,int*y);
	int ChoosePlanet(const InterType toget, int a,int b,int*x,int*y);
	int ChooseUnit(const InterType toget,int*x,int*y, int *z);
	int ChooseOption(const InterType toget,int*x);
	int ChooseValue(const InterType toget,int*x,int*y);
	int PrintSystemArmy(Hex * hex,Player * player);
	int ViewGalaxyPlanets();
	int ViewGalaxyResources();
	int ViewGalaxyCounters();
	int ViewGalaxyMovable();
	int ViewSystemPlanets(int a, int b);
	int ViewPlayersInfo();
	int ViewObjectivesLaws();
	int ViewPlayersTrades();
	int PrintThingPlayer(int who, const string str);
	int PrintThingAll(const string str);

	int SetCurrPlayer(int x);
	int GetCurrPlayer();
	int GetMapFile(string& str);
	int GetGalFile(string& str);
	int GetSystemsFile(string& str, SystemType ST);
	string GetPlayerName(string  str, int n);
	string GetPlayerPass(string  str, int n);
	int GetHex(int *x, int *y);
	int GetNumber(int *x, int min = INT_MIN, int max = INT_MAX);
	int GetPlanet(Planet* planet);
	int Print(const string str);//--
	int PrintDeckList(PowVec<Hex> * list);
	int PrintWrongHex(int x, int y);
	int PrintWrongHex();
	int PrintEmptyCoords(Map * map, int round);
	int PrintPlayerName(Player * player);
	int PrintGalaxy(Map * map);

	void ViewGalaxyExtendent();//vge
	void ViewGalaxyArmies();//vga
	void ViewSystemArmies(int a, int b);//vsa è vsa x y
}
_Interface;