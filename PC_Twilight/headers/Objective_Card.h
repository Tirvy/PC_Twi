class e_Objective:public GameEffect{
protected:
	VP_type type;	//тип задания
	string reqs;	//описание
	string reqsShort; //краткое описание для выбора
private:
public:
	int value;		//VPs for qualify
	bool isOpen;	//известно игроку или нет
	bool isSecret;  //секретное (для отображения другим игрокам)
	bool isDone;	//выполнено
	bool isFulfill; //можно выполнить
	e_Objective();
	bool GetQ(GameEffectQs queue);
	VP_type GetType();
	string GetReqs();
	string GetShortReqs();
	void reset();//сброс VP
	GameEffectRets Execute(ExecuteParams EP);
	virtual e_Objective* Clone();
	virtual string Save();
	virtual void Load(string str);
	//удалить штуки с бюрократией
	//bool Compited(int playernum);//убрать
	//virtual bool Check(Player* player) = 0;//убрать
	//void Initiate();//убрать
};

//throw endofgame(1)
struct endofgame{
	//Player* player;
	int f;
	endofgame(int a){
		//player = 0;
		f = a;
	}
};
//Tracker - отслеживает выполнение боевых заданий
class o_Tracker:public GameEffect{
	void reset();
	void show(Player* player = 0);
	bool _SpaceBattlesFlag;
	bool _InvasionsFlag;
	bool _lastdock;
	int _DocksUnderAttack;
	int _PDSUnderAttack;
	string _loadstring;
public:
	vector<Planet*> _CapturedPlanets;
	vector<Player*> _DestroyedDocks;
	vector<int> _DestroyedEnemyUnits;
	int _Infiltrator;
	int _Invaders;
	int _Traitor;
	int _Merciless;
	int _Invasions;
	int _SpaceBattles;
	o_Tracker();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//задания
class o_g_VP:public e_Objective{
public:
	o_g_VP();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};
//public stage 1
class o_1_10ror10i:public e_Objective{
	static const int RES_INF_TO_PAY = 10; 
public:
	o_1_10ror10i();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_5techs:public e_Objective{
	static const int TECHS = 5; 
public:
	o_1_5techs();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_6tg:public e_Objective{
	static const int TG_TO_PAY = 6; 
public:
	o_1_6tg();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_5planets:public e_Objective{
	static const int PLANETS = 5; 
public:
	o_1_5planets();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_3docks:public e_Objective{
	static const int DOCKS = 3; 
public:
	o_1_3docks();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_Mecatol:public e_Objective{
	static const int DOCKS = 3; 
public:
	o_1_Mecatol();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_Blockade:public e_Objective{
public:
	o_1_Blockade();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_Invasion:public e_Objective{
public:
	o_1_Invasion();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_SpaceVictory:public e_Objective{
public:
	o_1_SpaceVictory();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_Take3Planets:public e_Objective{
	static const int CAPTURED_PLANETS = 3;
public:
	o_1_Take3Planets();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_PlanetAllColors:public e_Objective{
public:
	o_1_PlanetAllColors();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_Tech4Color:public e_Objective{
public:
	o_1_Tech4Color();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_TechInColor:public e_Objective{
	static const int TECHS = 3;
public:
	o_1_TechInColor();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_10res:public e_Objective{
	static const int RES = 10;
public:
	o_1_10res();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_10inf:public e_Objective{
	static const int INF = 10;
public:
	o_1_10inf();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_3CC:public e_Objective{
	static const int COMMAND_COUNTERS = 3;
public:
	o_1_3CC();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_1_GreatInf:public e_Objective{
public:
	o_1_GreatInf();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};
//////////////STAGE 2//////////////////
class o_2_20ror20i:public e_Objective{
	static const int RES_INF_TO_PAY = 20; 
public:
	o_2_20ror20i();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_12tg:public e_Objective{
	static const int TG_TO_PAY = 12; 
public:
	o_2_12tg();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_20res:public e_Objective{
	static const int RES = 20;
public:
	o_2_20res();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_20inf:public e_Objective{
	static const int INF = 20;
public:
	o_2_20inf();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_6CC:public e_Objective{
	static const int COMMAND_COUNTERS = 6;
public:
	o_2_6CC();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_9techs:public e_Objective{
	static const int TECHS = 9; 
public:
	o_2_9techs();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_10planets:public e_Objective{
	static const int PLANETS = 10; 
public:
	o_2_10planets();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_Invasion:public e_Objective{
public:
	o_2_Invasion();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_SpaceVictory:public e_Objective{
public:
	o_2_SpaceVictory();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_TechInColor:public e_Objective{
	static const int TECHS = 5;
public:
	o_2_TechInColor();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_mecatol3:public e_Objective{
public:
	o_2_mecatol3();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_mecatol6:public e_Objective{
public:
	o_2_mecatol6();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_GreatInf:public e_Objective{
public:
	o_2_GreatInf();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_DestroyedDock:public e_Objective{
public:
	o_2_DestroyedDock();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_Supremacy:public e_Objective{
public:
	o_2_Supremacy();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_Domination:public e_Objective{
public:
	o_2_Domination();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_2_ImperiumRex:public e_Objective{
public:
	o_2_ImperiumRex();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};
//предварительные
class o_p_Commander:public e_Objective{
	static const int DREADNOUGHTS = 5;
public:
	o_p_Commander();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Defender:public e_Objective{
	static const int PDSs = 6;
public:
	o_p_Defender();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Scientist:public e_Objective{
	static const int TECHS = 3;
public:
	o_p_Scientist();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Researcher:public e_Objective{
	static const int PLANETS = 4;
public:
	o_p_Researcher();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Antagonist:public e_Objective{
public:
	o_p_Antagonist();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Enemy:public e_Objective{
	static const int DESTROYED_SHIPS = 3;
public:
	o_p_Enemy();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Infiltrator:public e_Objective{
public:
	o_p_Infiltrator();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Explorer:public e_Objective{
	static const int CONTROL_HEXES = 2;
public:
	o_p_Explorer();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Invader:public e_Objective{
public:
	o_p_Invader();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_p_Traitor:public e_Objective{
public:
	o_p_Traitor();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};
//секретные
class o_s_Diversified:public e_Objective{
	static const int TECHS = 2;
public:
	o_s_Diversified();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Usurper:public e_Objective{
	static const int GFs = 6;
public:
	o_s_Usurper();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Forceful:public e_Objective{
	static const int DREADNOUGHTS = 4;
public:
	o_s_Forceful();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_MasterOfShips:public e_Objective{
	static const int SHIPS = 8;
public:
	o_s_MasterOfShips();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Conqueror:public e_Objective{
public:
	o_s_Conqueror();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Expansionist:public e_Objective{
	static const int SYSTEMS_CONTROL = 8;
public:
	o_s_Expansionist();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Focused:public e_Objective{
	static const int PLANETS_CONTROL = 4;
public:
	o_s_Focused();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

/*class o_s_KeeperOfGates:public e_Objective{
public:
	o_s_KeeperOfGates();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};*/

class o_s_Industrial:public e_Objective{
	static const int DREADNOUGHTS = 5;
	static const int SPACEDOCKS = 3;
public:
	o_s_Industrial();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Merciless:public e_Objective{
public:
	o_s_Merciless();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Regulator:public e_Objective{
	static const int SPACEDOCKS = 2;
public:
	o_s_Regulator();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Technocrat:public e_Objective{
	static const int PLANETS_CONTROL = 6;
public:
	o_s_Technocrat();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};

class o_s_Threatening:public e_Objective{
public:
	o_s_Threatening();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	void reset();
	e_Objective* Clone();
	string Save();
	void Load(string str);
};