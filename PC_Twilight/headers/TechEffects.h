class e_Tech:public GameEffect{
	friend class InfoArea;
protected:
	string name;
	string description;
	int cost;				//добавка к цене
	TechTree color;			//цвет
	RacesType race;			//расовая
	TechType TT;			//тип техи
	TechType prereq1;		//пререквизит 1
	TechType prereq2;		//пререквизит 2
	bool isboth;			//если true, то нужны оба
private:
public:
	e_Tech();
	bool GetQ(GameEffectQs queue);
	string GetName();
	string GetDescription();
	TechTree GetColor();
	int GetCost();
	RacesType GetRace();
	TechType GetTechType();
	bool HavePrereqs(Player* player);
	GameEffectRets Execute(ExecuteParams EP);
};

//Красные техи:
class e_HylarVAssualtLaser:public e_Tech{
public:
	e_HylarVAssualtLaser();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_DeepSpaceCannon:public e_Tech{
public:
	e_DeepSpaceCannon();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_WarSun:public e_Tech{
public:
	e_WarSun();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_DuraniumArmor:public e_Tech{
	bool active;
public:
	e_DuraniumArmor();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_MagenDefenseGrid:public e_Tech{
public:
	e_MagenDefenseGrid();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_ADT:public e_Tech{
public:
	e_ADT();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_AssaultCannon:public e_Tech{
	bool active;
public:
	e_AssaultCannon();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_GravityNegator:public e_Tech{
	bool active;
public:
	e_GravityNegator();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//зеленые техи:
class e_Cybernetics:public e_Tech{
public:
	e_Cybernetics();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_X89:public e_Tech{
public:
	e_X89();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_GenSynthesis:public e_Tech{
public:
	e_GenSynthesis();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_StasisCapsules:public e_Tech{
public:
	e_StasisCapsules();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_DacxiveAnimators:public e_Tech{
	static const int DA_REVIVE_ROLL = 6;
	int GFs1,GFs2;
public:
	e_DacxiveAnimators();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NeuralComputing:public e_Tech{
public:
	e_NeuralComputing();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_HyperMetabolism:public e_Tech{
public:
	e_HyperMetabolism();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_NeuralMotivator:public e_Tech{
public:
	e_NeuralMotivator();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//синие техи:
class e_XRDtransporters:public e_Tech{
public:
	e_XRDtransporters();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_TypeIVDrive:public e_Tech{
public:
	e_TypeIVDrive();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_AdvancedFighters:public e_Tech{
public:
	e_AdvancedFighters();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_ManeuveringJets:public e_Tech{
public:
	e_ManeuveringJets();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_Antimass:public e_Tech{
public:
	e_Antimass();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_GravityDrive:public e_Tech{
public:
	e_GravityDrive();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_LightWaveDeflector:public e_Tech{
public:
	e_LightWaveDeflector();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_FleetLogistics:public e_Tech{
	int use;
public:
	e_FleetLogistics();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//желтые техи:
class e_GravitonLaserSystem:public e_Tech{
public:
	e_GravitonLaserSystem();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_EnviroCompensator:public e_Tech{
public:
	e_EnviroCompensator();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_SarweenTools:public e_Tech{
public:
	e_SarweenTools();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_Microtechnology:public e_Tech{
public:
	e_Microtechnology();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_Nanotechnology:public e_Tech{
	bool isHostile;
public:
	e_Nanotechnology();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_IntegratedEconomy:public e_Tech{
public:
	e_IntegratedEconomy();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_Transfabrication:public e_Tech{
public:
	e_Transfabrication();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_TransitDiodes:public e_Tech{
public:
	e_TransitDiodes();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Arborecs
class e_ArborecBioplasmosis:public e_Tech{
public:
	e_ArborecBioplasmosis();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_ArborecSporeAcceleration:public e_Tech{
public:
	e_ArborecSporeAcceleration();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Creuss
class e_CreussDimensionalSplicers:public e_Tech{
public:
	e_CreussDimensionalSplicers();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_CreussSlaveWormholeGenerator:public e_Tech{
public:
	e_CreussSlaveWormholeGenerator();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Hacan
class e_HacanProductionCenters:public e_Tech{
	int used;
public:
	e_HacanProductionCenters();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_HacanQuantumDatahubNode:public e_Tech{
public:
	e_HacanQuantumDatahubNode();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Jol-Nar
class e_JolNarSpatialConduitNetwork:public e_Tech{
public:
	e_JolNarSpatialConduitNetwork();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_JolNarElectroResonanceTurbines:public e_Tech{
public:
	e_JolNarElectroResonanceTurbines();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Letnev
class e_LetnevNoneuclidianShields:public e_Tech{
public:
	e_LetnevNoneuclidianShields();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_LetnevL4Disruptors:public e_Tech{
public:
	e_LetnevL4Disruptors();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//L1z1x
class e_L1z1xDreadnoughtInvasionPods:public e_Tech{
public:
	e_L1z1xDreadnoughtInvasionPods();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_L1z1xInheritanceSystems:public e_Tech{
	static const int INHERITANCE_SYSTEMS_RES_COST = 2;
public:
	e_L1z1xInheritanceSystems();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Mentak
class e_MentakSalvageOperations:public e_Tech{
	bool destrUnits[MAX_UNIT];
public:
	e_MentakSalvageOperations();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_MentakMirrorComputing:public e_Tech{
public:
	e_MentakMirrorComputing();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Muaat
class e_MuaatMagmusReactor:public e_Tech{
public:
	e_MuaatMagmusReactor();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_MuaatNovaSeed:public e_Tech{
	int isNuked;
public:
	e_MuaatNovaSeed();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Naalu
class e_NaaluTelepathicMindWeapon:public e_Tech{
public:
	e_NaaluTelepathicMindWeapon();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_NaaluHybridCrystalDrives:public e_Tech{
public:
	e_NaaluHybridCrystalDrives();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Norr
class e_NorrValkyrieArmor:public e_Tech{
	int HP;
public:
	e_NorrValkyrieArmor();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_NorrExotrireme:public e_Tech{
	bool active;
public:
	e_NorrExotrireme();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Saar
class e_SaarFloatingFactories:public e_Tech{
public:
	e_SaarFloatingFactories();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_SaarChaosMapping:public e_Tech{
public:
	e_SaarChaosMapping();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Sol
class e_SolMarkIICarrier:public e_Tech{
	bool launched;
public:
	bool GetQ(GameEffectQs queue);
	e_SolMarkIICarrier();
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};

class e_SolSpecOpsTraining:public e_Tech{
public:
	e_SolSpecOpsTraining();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Winnu
class e_WinnuBiopticRecyclers:public e_Tech{
	int used;
public:
	e_WinnuBiopticRecyclers();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_WinnuLazaxGateFolding:public e_Tech{
public:
	e_WinnuLazaxGateFolding();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Xxcha
class e_XxchaDiplomats:public e_Tech{
	int used;
public:
	e_XxchaDiplomats();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_XxchaInstinctTraining:public e_Tech{
	int used;
public:
	e_XxchaInstinctTraining();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Yin
class e_YinFanatic:public e_Tech{
public:
	e_YinFanatic();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_YinSpinner:public e_Tech{
public:
	e_YinSpinner();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//Yssaril
class e_YssarilShuttleLogistics:public e_Tech{
	bool done;
public:
	e_YssarilShuttleLogistics();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
class e_YssarilMageonImplants:public e_Tech{
public:
	e_YssarilMageonImplants();
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};