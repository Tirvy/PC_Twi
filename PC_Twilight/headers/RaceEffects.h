//Hacan
class e_HacanFlagship:public GameEffect{
	int rerolls;
public:
	e_HacanFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_HacanAdditionalTG:public GameEffect{
public:
	e_HacanAdditionalTG();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Jol-Nar
class e_JolNarRacialAbilityStats:public GameEffect{
public:
	e_JolNarRacialAbilityStats();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_JolNarTechnology:public GameEffect{
public:
	e_JolNarTechnology();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_JolNarReroll:public GameEffect{
public:
	e_JolNarReroll();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//L1z1x
class e_L1z1xRacialAbilityStats:public GameEffect{
public:
	e_L1z1xRacialAbilityStats();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_L1z1xFlagship:public GameEffect{
public:
	e_L1z1xFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Letnev
class e_LetnevBattleAbility:public GameEffect{
	bool isActive;
public:
	e_LetnevBattleAbility();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_LetnevFleetSupply:public GameEffect{
public:
	e_LetnevFleetSupply();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Mentak
class e_MentakPreBattle:public GameEffect{
	bool active;
public:
	e_MentakPreBattle();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_MentakFlagship:public GameEffect{
	bool IsFourthMoon;
public:
	e_MentakFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_MentakStealGoods:public GameEffect{
	static const int MINIMUM_TG_TO_STEAL = 3;
	static const int NUMBER_OF_PLAYERS = 2;
	bool active;
public:
	e_MentakStealGoods();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Muaat
class e_MuaatWarSunSpeed:public GameEffect{
public:
	e_MuaatWarSunSpeed();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_MuaatWarSunSpawn:public GameEffect{
public:
	e_MuaatWarSunSpawn();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_MuaatFlagshipSpawn:public GameEffect{
public:
	e_MuaatFlagshipSpawn();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_MuaatSuperNovaMove:public GameEffect{
public:
	e_MuaatSuperNovaMove();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Naalu
class e_NaaluRacialAbilityStats:public GameEffect{
public:
	e_NaaluRacialAbilityStats();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NaaluInitiative:public GameEffect{
public:
	e_NaaluInitiative();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NaaluFlagship:public GameEffect{
public:
	e_NaaluFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NaaluRetreat:public GameEffect{
	bool active;
public:
	e_NaaluRetreat();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Nekro
class e_NekroFlagship:public GameEffect{
public:
	e_NekroFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NekroValefarAssmilator:public GameEffect{
	int CopiedRaceTechs;
	bool IsDestroyedEnemyUnit;
	static const int MAX_COPY_RACE_TECHS = 2;
public:
	bool GetQ(GameEffectQs queue);
	e_NekroValefarAssmilator();
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NekroTechResearch:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	e_NekroTechResearch();
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NekroAbstain:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	e_NekroAbstain();
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Norr
class e_NorrRacialAbilityStats:public GameEffect{
public:
	e_NorrRacialAbilityStats();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_NorrFlagship:public GameEffect{
public:
	e_NorrFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Saar
class e_SaarExploration:public GameEffect{
public:
	e_SaarExploration();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_SaarDocks:public GameEffect{
public:
	e_SaarDocks();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Sol
class e_SolCounter:public GameEffect{
public:
	e_SolCounter();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_SolRecruit:public GameEffect{
	static const int SOL_GF_FOR_COUNTER = 2;
public:
	e_SolRecruit();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Winnu
class e_WinnuFlagship:public GameEffect{
public:
	e_WinnuFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_WinnuTechnology:public GameEffect{
public:
	e_WinnuTechnology();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_WinnuPolitic:public GameEffect{
public:
	e_WinnuPolitic();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_WinnuLocalUnrest:public GameEffect{
public:
	e_WinnuLocalUnrest();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Xxcha
class e_XxchaRacialAbilityStats:public GameEffect{
public:
	e_XxchaRacialAbilityStats();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_XxchaDiplomacy:public GameEffect{
public:
	e_XxchaDiplomacy();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_XxchaVeto:public GameEffect{
public:
	e_XxchaVeto();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Yin
class e_YinFanaticism:public GameEffect{
public:
	e_YinFanaticism();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_YinReverse:public GameEffect{
	Planet* target;
	bool launched;
public:
	e_YinReverse();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_YinKamikaze:public GameEffect{
	bool active;
public:
	e_YinKamikaze();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_YinFlagship:public GameEffect{
	bool IsVanHaugeEnabled;
	int VanHaugeEnable(Army* army);
	int VanHaugeDisable(Army* army);
	bool active;
public:
	e_YinFlagship();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Yssaril
class e_YssarilAdditionalAC:public GameEffect{
public:
	e_YssarilAdditionalAC();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_YssarilWait:public GameEffect{
	int cooldown;
public:
	e_YssarilWait();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_YssarilSpy:public GameEffect{
	bool active;
public:
	e_YssarilSpy();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};