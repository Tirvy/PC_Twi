bool SelectDialogYesNo(const string str);
int SelectDialogPlanetInSystem(const string str, Hex* hex, Player* curPlayer, bool* mask, int planets);
	//����� ������ ��� ������� � �������������
int SelectDialogPlanetInSystem(Hex* hex,Player* player = 0, bool own=false);
	//����� ������� �� hex, ������� ����������� player(own=true) ��� �� �����������(own=false), ������� � 1.
Unit* SelectDialogOneUnit(const string str, Army* army, bool pass, UnitAbType UAT, int f1 = FIELD_SKIP, int f2 = FIELD_SKIP, int f3 = FIELD_SKIP );
	//����� ������ ����� (����)
vector<int> SelectDialogGroupUnits(const string str, Army* army, bool pass, UnitAbType UAT, int f1 = FIELD_SKIP, int f2 = FIELD_SKIP, int f3 = FIELD_SKIP );
	//����� ���������� ������ (AFB, Mentak, bombs) ��� uaMultiple
PowDEV<Unit,Army> SelectDialogOneUnit(const string str, int x, int y, UnitAbType UAT, bool pass, bool NotInCarrier = false, Unit* car = 0);
vector<int> SelectDialogOwnedPlanet(const string str, Player* player,  bool multiple, int openonly, bool passable, bool goods);
Player * SelectDialogPlayer(const string str, Player* exept = 0);
PowDouble<TradeRoute,Player> SelectDialogTradeRoute(bool free_made, TradeRoute* exclude = 0);
Roll* SelectDialogRoll(Player* player, Roll* rolls, int count);
TechType SelectDialogTech(const string str, Player* player, int* prices);
e_Objective* SelectDialogObjective(const string str, Player* player, bool publ, bool secr);

Planet* SelectDialogPlanet(const string str, const string strhex, Hex* hex, Player* active, bool passable = true, bool friendly = true, bool neutral = false, bool hostile = false, bool noHS = false, bool TradeStations = false);
	//�������� ����� ������� ��� ������ ������� � �� ������
	//���������:
	//str - ������ ��������
	//hex - ����, ���� hex == 0, �� ����� ����� �����
	//active - �������� �����, �������������� �����
	//passable - ����������� ����
	//friendly, neutral, hostile - ������� ������ �� ��������� � ��������� ������
	//noHS - ������ ����� �������� ������ (� ������ hex == 0)
	//TradeStations - ������ ������ �������� �������