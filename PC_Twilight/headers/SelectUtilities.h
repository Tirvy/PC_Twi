bool SelectDialogYesNo(const string str);
int SelectDialogPlanetInSystem(const string str, Hex* hex, Player* curPlayer, bool* mask, int planets);
	//выбор планет для высадки и бомбардировки
int SelectDialogPlanetInSystem(Hex* hex,Player* player = 0, bool own=false);
	//номер планеты из hex, которая принадлежит player(own=true) или не принадлежит(own=false), начиная с 1.
Unit* SelectDialogOneUnit(const string str, Army* army, bool pass, UnitAbType UAT, int f1 = FIELD_SKIP, int f2 = FIELD_SKIP, int f3 = FIELD_SKIP );
	//выбор одного юнита (урон)
vector<int> SelectDialogGroupUnits(const string str, Army* army, bool pass, UnitAbType UAT, int f1 = FIELD_SKIP, int f2 = FIELD_SKIP, int f3 = FIELD_SKIP );
	//выбор нескольких юнитов (AFB, Mentak, bombs) без uaMultiple
PowDEV<Unit,Army> SelectDialogOneUnit(const string str, int x, int y, UnitAbType UAT, bool pass, bool NotInCarrier = false, Unit* car = 0);
vector<int> SelectDialogOwnedPlanet(const string str, Player* player,  bool multiple, int openonly, bool passable, bool goods);
Player * SelectDialogPlayer(const string str, Player* exept = 0);
PowDouble<TradeRoute,Player> SelectDialogTradeRoute(bool free_made, TradeRoute* exclude = 0);
Roll* SelectDialogRoll(Player* player, Roll* rolls, int count);
TechType SelectDialogTech(const string str, Player* player, int* prices);
e_Objective* SelectDialogObjective(const string str, Player* player, bool publ, bool secr);

Planet* SelectDialogPlanet(const string str, const string strhex, Hex* hex, Player* active, bool passable = true, bool friendly = true, bool neutral = false, bool hostile = false, bool noHS = false, bool TradeStations = false);
	//обобщает выбор планеты для всяких экшонов и не только
	//параметры:
	//str - строка описание
	//hex - гекс, если hex == 0, то будет выбор гекса
	//active - активный игрок, осуществляющий выбор
	//passable - возможность паса
	//friendly, neutral, hostile - фильтры выбора по отношению к активному игроку
	//noHS - запрет выбор домашних систем (в случае hex == 0)
	//TradeStations - запрет выбора торговых станций