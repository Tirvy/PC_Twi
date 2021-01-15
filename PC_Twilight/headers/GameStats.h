Player NEUTRAL_PLAYER("Neutrals",-1);

class GameStats{
	friend class SaveTranslator;
	friend void ToReplay(string str);

	int _playersnum;
	Player* _neutral_player;
	vector<e_Objective*> _PublicObjDeck;
	vector<e_Objective*> _PublicObjDeckOpen;
	vector<e_Objective*> _PrelimObjDeck;
	vector<e_Objective*> _SecretObjDeck;

	vector<e_Tech*> _TechDeck;

	deque<e_Politic*> _PoliticsDeck;
	list<GameEffect*> _Laws;

	vector<e_ActionCard*> _ActionDeck;

	vector<e_StratCard*> _Strats;

	unsigned int _random_seed;
	
public:
	GamePhaseType CurPhase;
	int Speaker,ActivePlayer;
	int CurTurn,CurRound;
	int VPftw;	//кол-во ПО для победы 

	int* playerstatus;//Zoldn's phase load
	bool _IsManualCreation;//Zoldn's. Флаг того, что карта будет создавать руками, а не с шаблона
	int _ManualBuildDeck[4];//Zoldn's. Хранит инфу о том, сколько каких гексов для формирования колоды

	int SetGameStats(GameInitSettings InitS);
	int GetPlayersNumber();
	Player* GetNeutralPlayer();
	Deck<e_Objective>* GetObjectivesDeck();
	void ClearArmies();	
	//Protect teh Tech!
	void SetTechDeck(vector<e_Tech*> stechs);
	vector<e_Tech*>* GetTechDeck();
	//objectives
	void SetObjectiveDecks(vector<e_Objective*> spublic, vector<e_Objective*> sprelim, vector<e_Objective*> ssecret, vector<e_Objective*> sopened );
	vector<e_Objective*>* GetPublicObjectives();
	vector<e_Objective*>* GetPublicOpenObjectives();
	vector<e_Objective*>* GetSecretObjectives();
	vector<e_Objective*>* GetPrelimObjectives();
	
	void AddLaw(GameEffect* law);
	void InitPoliticDeck(list<e_Politic*> PoliticsList);
	e_Politic* DrawPolitic();
	deque<e_Politic*>* GetPoliticDeck();
	Player* GetLocalPlayer();

	void SetActionDeck(vector<e_ActionCard*> sactions);
	vector<e_ActionCard*>* GetActionDeck();
	e_ActionCard* DrawAction();

	void SetStrategies(vector<e_StratCard*> sstrats);
	vector<e_StratCard*>* GetStrategies();

	//void SetFirstArmy(Player* player, Hex* hex, Planet* planet);

	int NextPlayer();
}
_GameStats;