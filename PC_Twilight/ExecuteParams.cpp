/*
n = 0: eq_StrategyStart, eq_StrategyEnd, eq_StatusStart, eq_StatusEnd
n = 1: Player* ActivePlayer: eq_ActionStart, eq_ActionEnd, eq_StratLidership1, eq_StratDiplomacy1, eq_StratAssembly1, eq_StratProduction1, eq_StratWarfare1, eq_StratTrade1, eq_StratTechnology1, eq_StratBureacracy1, eq_Movement
n = 3: Player* CurrPlayer, Player* ActivePlayer, Settings* settings: eq_StratLidership2, eq_StratDiplomacy2, eq_StratAssembly2, eq_StratProduction2, eq_StratWarfare2, eq_StratTrade2, eq_StratTechnology2, eq_StratBureacracy2
n = 3: Hex* system, Planet* planet: eq_PreFight, eq_FightPreRound, eq_FightRound
*/


// Great GameEffect Structure
void ExecuteParams::reset(){
	queue = eq_None;
	player = 0;
	strattype = MAX_STRAT;
	army1 = 0;
	army2 = 0;
	fround = 0;
	attacker = 0;
	unit = 0;
	roll = 0;
	isInvasion = 0;
	rolls = 0;
	rollNumber = 0;
	modificator = 0;
	Tech = MAX_TECH;
	TechCostBonus = 0;
	stratcard = 0;
	FleetSupply = 0;
	ActionCards = 0;
	CommandCounters = 0;
	hex = 0;
	planet = 0;
	votings = 0;
	politicalcard = 0;
	actioncard = 0;
	spawn.clear();
}
ExecuteParams::ExecuteParams(){
	reset();
}
ExecuteParams::ExecuteParams(ExecuteParams& EP){
	queue = EP.queue;
	player = EP.player;
	strattype = EP.strattype;
	army1 = EP.army1;
	army2 = EP.army2;
	fround = EP.fround;
	attacker = EP.attacker;
	unit = EP.unit;
	roll = EP.roll;
	isInvasion = EP.isInvasion;
	rolls = EP.rolls;
	rollNumber = EP.rollNumber;
	modificator = EP.modificator;
	Tech = EP.Tech;
	TechCostBonus = EP.TechCostBonus;
	stratcard = EP.stratcard;
	FleetSupply = EP.FleetSupply;
	ActionCards = EP.ActionCards;
	CommandCounters = EP.CommandCounters;
	hex = EP.hex;
	planet = EP.planet;
	votings = EP.votings;
	actioncard = EP.actioncard;
	politicalcard = EP.politicalcard;
	spawn = EP.spawn;

}
ExecuteParams::ExecuteParams(GameEffectQs Q){
	reset();
	queue = Q;
}
ExecuteParams::ExecuteParams(GameEffectQs Q, Player* P){
	reset();
	queue = Q;
	player = P;
}
ExecuteParams::ExecuteParams(GameEffectQs Q, Army * attArmy,Army * defArmy,int round,int isattacker){
	reset();
	queue = Q;
	strattype = MAX_STRAT;
	army1 = attArmy;
	army2 = defArmy;
	fround = round;
	attacker = isattacker;
}
ExecuteParams::ExecuteParams(GameEffectQs Q, Player* P, e_StratCard* stratcard_in){
	reset();
	queue = Q;
	player = P;
	stratcard = stratcard_in;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Army* attArmy, Unit* in_unit, int* in_roll){
	reset();
	queue = Q;
	army1 = attArmy;
	unit = in_unit;
	roll = in_roll;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Army* army, Army* target, bool in_isInvasion){
	reset();
	queue = Q;
	army1 = army;
	army2 = target;
	isInvasion = in_isInvasion;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Army* army, Army* target, Unit* in_unit, int in_attacker){
	reset();
	queue = Q;
	army1 = army;
	army2 = target;
	unit = in_unit;
	attacker = in_attacker;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Army* army, Army* target, Roll* in_rolls, int in_rollnumber){
	reset();
	queue = Q;
	army1 = army;
	army2 = target;
	rolls = in_rolls;
	rollNumber = in_rollnumber;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player* in_player, Army* target){
	reset();
	queue = Q;
	army1 = target;
	player = in_player;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Army* army, Army* target, int* in_modif, int isAttacker){
	reset();
	queue = Q;
	army1 = army;
	army2 = target;
	modificator = in_modif;
	attacker = isAttacker;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *P, TechType T, int *TPB){
	reset();
	queue = Q;
	player = P;
	Tech = T;
	TechCostBonus = TPB;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Army *in_army, Unit *in_unit){
	reset();
	queue = Q;
	army1 = in_army;
	unit = in_unit;
};

ExecuteParams::ExecuteParams(GameEffectQs Q, Army *in_army, int *fs){
	reset();
	queue = Q;
	army1 = in_army;
	FleetSupply = fs;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *in_player, int *CCs, int *ACs){
	reset();
	queue = Q;
	player = in_player;
	CommandCounters = CCs;
	ActionCards = ACs;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *in_player, Hex *in_hex, int* bonus){
	reset();
	queue = Q;
	player = in_player;
	hex = in_hex;
	modificator = bonus;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *in_player, Planet *in_planet){
	reset();
	queue = Q;
	player = in_player;
	planet = in_planet;
}
ExecuteParams::ExecuteParams(GameEffectQs Q, Player* in_player, vector<Voting>* vote){
	reset();
	queue = Q;
	player = in_player;
	votings = vote;
}
ExecuteParams::ExecuteParams(GameEffectQs Q, Player* in_player, vector<Voting>* vote, e_Politic ** agenda){
	reset();
	queue = Q;
	player = in_player;
	votings = vote;
	politicalcard = agenda;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *in_player, e_ActionCard *in_AC, int *in_value){
	reset();
	queue = Q;
	player = in_player;
	actioncard = in_AC;
	ActionCards = in_value;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *in_player, Army *in_army, int *in_value){
	reset();
	queue = Q;
	player = in_player;
	army1 = in_army;
	CommandCounters = in_value;
}

ExecuteParams::ExecuteParams(GameEffectQs Q, Player *in_player, std::vector<SpawnUnit> in_spawn, Hex* in_hex, int* in_value){
	reset();
	queue = Q;
	player = in_player;
	spawn = in_spawn;
	CommandCounters = in_value;
	hex = in_hex;
}