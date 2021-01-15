//Красные техи:
class e_HylarVAssualtLaser:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_DeepSpaceCannon:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_DuraniumArmor:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_MagenDefenseGrid:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_ADT:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_AssaultCannon:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_GravityNegator:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//зеленые техи:
class e_Cybernetics:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_X89:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_GenSynthesis:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_StasisCapsules:public GameEffect{
	bool launched;
public:
	bool GetQ(GameEffectQs queue);
	e_StasisCapsules();
	GameEffectRets Execute(ExecuteParams EP);
};

class e_DacxiveAnimators:public GameEffect{
	static const int DA_REVIVE_ROLL = 6;
	int GFs1,GFs2;
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_NeuralComputing:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//синие техи:
class e_XRDtransporters:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_TypeIVDrive:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_AdvancedFighters:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};

class e_ManeuveringJets:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
//желтые техи:
class e_GravitonLaserSystem:public GameEffect{
public:
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
};
