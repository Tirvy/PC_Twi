
class Player{
	friend class GameEffect;
	friend class e_DullStrat;//this should no 
	friend e_Politic* ChoosePolitic(Player*player);
	friend class InfoArea;
	friend class MenuArea;
	friend int InitNewGame(GameInitSettings InitS);
	friend int InitLoadGame(GameInitSettings InitS);

	friend list<string> SavePlayer(Player* pl);
	friend list<string> SaveEffects(Player* player);
	friend void LoadPlayer(list<string>::iterator begin, list<string>::iterator end, int numb);
	friend int LoadEffect(string str, Player* player);

	string _name; // players name
	string _pass; // players password
	int _number;
	int _color;
	string banner;
	RacesType _race;
	int _initiative;
	int _strats[MAX_STRAT];
	int _counters[3]; // number of counters
	UnitStats* _unitstats;
	MoveStats* _movestats;
	int _goods;
	//list<GameEffect*> AAA;
	list<GameEffect*> _PlayerGameEffect;
	//list<e_Objective*> _PlayerObjectives;
	vector<Planet*> _planets;
	bool _techs[MAX_TECH];
	TradeRoute* _trades[2];
	deque<e_Politic*> _politics;
	int _VP;

	
	int _connection;// -2 - empty; -1 - local; >=0 - net
	
public:
	vector<Hex*> _SystemHand;//для раскладки
	SystemDeck* SysDeck;
	Hex* HS;
	Hex* eHS;
	Player(string newname, int snumber=7);// constructor
	const string GetName(); // returns name
	bool CheckPass(string cpass); // checks passwork 0_0
	int GetId(); // returns name. What? nonononononono. wrong, but im lazy to delete it
	int SetHS(Hex* nHS); // sets player new HS and race, according to his HS's name
	Hex* GetHS(); // returns HS
	int SetExtraHS(Hex* nHS); // sets player new HS and race, according to his HS's name
	Hex* GetExtraHS();
	int GetNumber(); // returns players Number in basic list STARTING FROM 1
	int AddStrat(StratsType x); // Gives player strategic card
	int GotStrat(StratsType x); // Returns TRUE if player got this strat unactivated in hand
	int SetInitiative(int x); // Sets players initiative
	int GetInitiative(); // Gets players current initiative
	int GetConnection();
	//int AddAAA(GameEffect* action); // Adds new capability for an As An Action

	//Get's
	RacesType GetRace(); // Returns race of a player
	int GetVotes();
	int GetInfluence(); // returns total influence of open planets
	int GetResources(); // returns total resources of open planets
	int TotalInf();// returns total influence

	//Actions
	int Produce(Hex*system, int ProdLimit=0,int ResAdd=0, bool nodck=false);
	int PayRes(int x);
	int PayInf(int x);
	int Pay(int type, int howmuch); //player pay <howmuch>. type: 0 - res, 1 - inf, 2 - goods
	bool MakeAction(); // Makes something As An Action

	bool MakeStatusAction();// потом заменить на MakeQueueAction
	bool MakeQueueAction(ExecuteParams EP, string str, bool SingleAction = false);


	//Graphics
	int GetColor();
	string GetBanner();

	//CCs
	void ReDirsrCC(int SA, int FS, int CP); // rdistributes counters as given. If sum is not equal - throws exeption
	void AddCC(int SA, int FS, int CP); // adds counters to pools
	bool TakeCounter(int CT, int howmuch = 1); // Takes away 1 counter from 0-SA,1-FS,2-CP. Returns false, if failed
	int GetCountersSA(); // returns a  number of Strategy Allocation counters
	int GetCountersFS(); // returns a  number of Fleet Support counters
	int GetCountersCP(); // returns a  number of Command Pool counters
	void GiveFreeCounters(int n, bool redistribute = false); // gives n counters to freely distribute. If 3rd param is true - player also allowed to redistr other counters

	//techs
	bool GotTech(TechType c); // Returns TRUE if player got this tech
	bool GiveTech(TechType c); // returns true. Gives player the tech.
	bool* GetTechList(); // returns boolean array of techs

	//trade routes
	TradeRoute* GetTrade(int number); // returns an active trade agreement
	TradeRoute* SwapTrades(int number, TradeRoute* route); // returns false, if not a legal trade
	bool AddTrade(int power); // adds basic trade route. Returns false, if its more than 2 routes

	//politics
	e_Politic* AddPolitic(e_Politic* pol, bool silent = false);

	//stats
	UnitStats* GetUnitStats(); // returns UnitStats for this player
	MoveStats* GetMoveStats(); // returns MoveStats for this player

	//trade goods
	int GetGoods(); // returns number of trade goods the player currently have
	int GiveGoods(int x); // gives player x trade goods
	void TakeGoods(int n);

	//new VPs
	//e_Objective* AddObjective(e_Objective* newObjective);
	void RefreshObjectives();//сбрасывает в начале раунд статус выполненности заданий
	friend e_Objective* SelectDialogObjective(const string str, Player* player, bool publ, bool secr);
	void ShowObjectives();//выводит задания игрока (в том числе неоткрытые)
	int recountVP();//пересчет победных очков игрока
	int DoneObjectives();//возвращает кол-во выполненных заданий
	int NumberOfPlanets();//кол-во планет
	int UnusedCC();//
	int ActiveCC();//
	o_Tracker* GetObjectiveTracker();
	e_Objective* ObjectiveWin();

	//Fleet Supply, numbers of units
	void CheckFleets();
	vector<int> CheckUnits();


	//planets
	int AddPlanet(Planet* planet);
	int Capture(Planet * planet);
	int DeCapture(Planet * planet);
	vector<Planet*>* GetPlanetsList();
	bool CanBuildDock(Planet* planet);
	int RefreshPlanet(int number =  -1);
	bool IsPlanetOpen(Planet* planet);

	//status phase refreshes
	int ReturnStrats(); // Returns all the cards from the player
	int Refresh();
	int ActivateDocks();//приводит доки в рабочее состояние

	// GameEffects
	GameEffect* AddGameEffect(GameEffect* newGameEffect);	//Zoldn's change
	int ExecuteGameEffect(ExecuteParams& EP);
	int RemoveGameEffect(string id);

	//Actions
	int AddAction(int number);//adds number action cards
	friend e_ActionCard* SelectDialogActionCard(string str, Player* player, bool pass);
	int GetActionsNumber();
	int DiscardActions(int num = 0);//discard num ACs, num = 0 - all actions
	friend class e_YssarilSpy;

	//manual build galaxy
	int SetDeck(vector<Hex*> deck);
	Hex* SelectSystemManualBuild();
	void AddHexToDeck(Hex* hex);
	void RemoveHexFromDeck(Hex* hex);
};
Player** _Players;