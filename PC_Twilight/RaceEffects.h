//Hacan
class e_HacanFlagship:public GameEffect{
	int rerolls;
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Jol-Nar
class e_JolNarRacialAbilityStats:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
class e_JolNarTechnology:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
class e_JolNarReroll:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//L1z1x
class e_L1z1xRacialAbilityStats:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_L1z1xDreadnoughtInvasionPods:public GameEffect{
	bool launched;
public:
	bool GetQ(GameEffectQs queue);
	e_L1z1xDreadnoughtInvasionPods();
	GameEffectRets Execute(ExecuteParams EP);
};

class e_L1z1xInheritanceSystems:public GameEffect{
	static const int INHERITANCE_SYSTEMS_RES_COST = 2;
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_L1z1xFlagship:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Letnev
class e_LetnevNoneuclidianShields:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_LetnevBattleAbility:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Mentak
class e_MentakPreBattle:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_MentakFlagship:public GameEffect{
	bool IsFourthMoon;
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_MentakSalvageOperations:public GameEffect{
	bool destrUnits[MAX_UNIT];
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Muaat
class e_MuaatWarSunSpeed:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_MuaatMagmusReactor:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Naalu
class e_NaaluRacialAbilityStats:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_NaaluRetreat:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Nekro
class e_NekroFlagship:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_NekroValefarAssmilator:public GameEffect{
	int CopiedRaceTechs;
	bool IsDestroyedEnemyUnit;
	static const int MAX_COPY_RACE_TECHS = 2;
public:
	bool GetQ(GameEffectQs queue);
	e_NekroValefarAssmilator();
	GameEffectRets Execute(ExecuteParams EP);
};
//Norr
class e_NorrRacialAbilityStats:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_NorrValkyrieArmor:public GameEffect{
	int HP;
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_NorrFlagship:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_NorrExotrireme:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Sol
class e_SolMarkIICarrier:public GameEffect{
	bool launched;
public:
	bool GetQ(GameEffectQs queue);
	e_SolMarkIICarrier::e_SolMarkIICarrier();
	GameEffectRets Execute(ExecuteParams EP);
};

class e_SolSpecOpsTraining:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Winnu
class e_WinnuFlagship:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_WinnuTechnology:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Xxcha
class e_XxchaRacialAbilityStats:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_XxchaDiplomacy:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//Yin
class e_YinFanaticism:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_YinKamikaze:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_YinFlagship:public GameEffect{
	bool IsVanHaugeEnabled;
	int VanHaugeEnable(Army* army);
	int VanHaugeDisable(Army* army);
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};