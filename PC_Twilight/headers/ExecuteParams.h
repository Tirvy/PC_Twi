struct ExecuteParams{
	GameEffectQs queue;
	Player* player;
	StratsType strattype;
	e_StratCard* stratcard;
	Army *army1,*army2;
	int fround,attacker;
	int* roll;	//бросок
	bool isInvasion;
	Unit* unit;
	Roll* rolls;
	int rollNumber;
	int* modificator;
	TechType Tech;
	int* TechCostBonus;
	int* FleetSupply;
	int* ActionCards;
	int* CommandCounters;
	Hex* hex;
	Planet* planet;
	vector<Voting>* votings;
	e_ActionCard* actioncard;
	e_Politic** politicalcard;
	vector<SpawnUnit> spawn;



	ExecuteParams(); // maybe youll need it
	ExecuteParams(ExecuteParams& EP); // copy-constructor
	ExecuteParams(GameEffectQs Q); // for global GameEffects
	ExecuteParams(GameEffectQs Q, Player* P); // for player-specific GameEffects
	ExecuteParams(GameEffectQs Q, Army * attArmy,Army * defArmy,int round,int isattacker); // battle GameEffects
	ExecuteParams(GameEffectQs Q, Player* P, e_StratCard* stratcard_in); // for strat-card specific

	ExecuteParams(GameEffectQs Q, Army* attArmy, Unit* in_unit, int* in_roll);//очередь AfterRoll
	ExecuteParams(GameEffectQs Q, Army* army, Army* target, bool in_isInvasion);//очереди бомбардировки
	ExecuteParams(GameEffectQs Q, Army* army, Army* target, Unit* in_unit, int in_attacker);//AfterAssignDamage
	ExecuteParams(GameEffectQs Q, Army* army, Army* target, Roll* in_rolls, int in_rollnumber);
	ExecuteParams(GameEffectQs Q, Player* in_player, Army* target);
	ExecuteParams(GameEffectQs Q, Army* army, Army* target, int* in_modif, int isAttacker);

	ExecuteParams(GameEffectQs Q, Player* P, TechType T, int* TPB);
	ExecuteParams(GameEffectQs Q, Army* in_army, Unit* in_unit);

	ExecuteParams(GameEffectQs Q, Army* in_army, int* fs);
	ExecuteParams(GameEffectQs Q, Player* player, int* CCs, int* ACs);
	
	ExecuteParams(GameEffectQs Q, Player* in_player, Hex* in_hex, int* bonus);
	ExecuteParams(GameEffectQs Q, Player* in_player, Planet* in_planet);
	
	ExecuteParams(GameEffectQs Q, Player* in_player, vector<Voting>* vote); // очередь голосований политики
	ExecuteParams(GameEffectQs Q, Player* in_player, vector<Voting>* vote, e_Politic ** agenda); // очередь голосований политики 

	ExecuteParams(GameEffectQs Q, Player* in_player, e_ActionCard* in_AC, int* in_value);

	ExecuteParams(GameEffectQs Q, Player* in_player, Army* in_army, int* in_value);

	ExecuteParams(GameEffectQs Q, Player* in_player, vector<SpawnUnit> in_spawn, Hex* in_hex, int* in_value);//Integrated economy
private:
	void reset();
};