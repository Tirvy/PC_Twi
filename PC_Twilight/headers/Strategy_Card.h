class e_StratCard:public GameEffect{
private:
	int bonus;
protected:
	StratsType type;
public:
	virtual void reset() = 0;
	virtual void sc_S(Player*player) = 0;
	virtual void sc_P(Player*player) = 0;

	virtual void special(int n) = 0;

	bool UseP;
	bool UseS;

	void AddBonus(); //Adds one bonus
	void NullBonus(); //Nulls bonus
	int GetBonus(); //Returns bonus status (dont forget to null, if used)
	void SetBonus(int n);
	StratsType GetType(); //Returns type of strategy card
	GameEffectRets Execute(ExecuteParams EP); //Executes this Strategy card
};
//описания классов страткарт
//дипломатия
class e_Diplomacy:public e_StratCard{
public:
	int DIPLOMACY_COUNTERS_COST;
	int DIPLOMACY_INF_COST;
private:
	void reset();
	void sc_S(Player*player);
	void sc_P(Player*player);
	void special(int n);
public:
	e_Diplomacy();
	bool GetQ(GameEffectQs queue);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//война
class e_Warfare:public e_StratCard{
	static const int WARFARE_SECONDARY_SHIPS_TO_MOVE = 2;
public:
	int WARFARE_SECONDARY_COUNTERS_COST;
private:
	void reset();
	void sc_S(Player*player);
	void sc_P(Player*player);
	void special(int n);
public:
	e_Warfare();
	bool GetQ(GameEffectQs queue);
	e_StratCard* Clone();
	string Save();
	void Load(string str);
};

class e_HighAlert:public GameEffect{
	Hex* HighAlertHex;
	Player* ActivePlayer;
	int xl,yl,pl;
public:
	e_HighAlert();
	e_HighAlert(Hex* hex, Player* owner);
	bool GetQ(GameEffectQs queue);
	GameEffectRets Execute(ExecuteParams EP);
	GameEffect* Clone();
	string Save();
	void Load(string str);
};
//технология
class e_Technology:public e_StratCard{
public:
	int TECHNOLOGY_PRIMARY_RESOURCE_COST_1;
	int TECHNOLOGY_PRIMARY_RESOURCE_COST_2;
	int TECHNOLOGY_SECONDARY_RESOURCE_COST;
	int TECHNOLOGY_SECONDARY_COUNTERS_COST;
private:
	void reset();
	void sc_S(Player* player);
	void sc_P(Player* player);
	void special(int n);
public:
	e_Technology();
	bool GetQ(GameEffectQs queue);
	e_StratCard* Clone();
	string Save();
	void Load(string str);
};
//бюрократия
class e_Bureaucracy:public e_StratCard{
	static const int BUREAUCRACY_PRIMARY_FREE_COUNTERS = 1;
public:
	int BUREAUCRACY_SECONDARY_COUNTERS_COST;
private:
	void reset();
	void sc_S(Player* player);
	void sc_P(Player* player);
	void special(int n);
public:
	e_Bureaucracy();
	bool GetQ(GameEffectQs queue);
	e_StratCard* Clone();
	string Save();
	void Load(string str);
};


e_StratCard* _StratShared[MAX_STRAT];