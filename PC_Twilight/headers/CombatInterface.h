class CombatInterface{
	static const char c_Prefix[];
	static const int ROLL_NUMBER=100;
	char str[127];
	char stra[127];
public:
	//�������� ������
	int CombatTacticalAction(Army* attArmy);//�������� �����, �������������� 3-6 ����� ������������ ��������, ���������� 1, ���� ��� ��
	Battle_Result SpaceCombat(Army* attArmy);//��������� ������������ ���
	int Landing(Army* attArmy, bool isTransfer = false);//������ �������
	Battle_Result InvasionCombat(Army* attArmy, Army* landArmy, Army* defArmy);//�������� �� �������
	//int ShowArmy(Army* attArmy);//������� �����, ���������� ����� ������
	void GEE(GameEffectQs Q, Army* attArmy, Army* defArmy, int round);//Game Effect Execute
	void GES(GameEffectQs Q, Army* attArmy, Army* defArmy, int round);//Game Effect Select
	//����� � ���������� ������:
	void RollingDices(Army* attArmy, Army* defArmy, Battle_Type BT, bool isBoth);//������ ������ � ���������� ������
	int HowManyDices(Army *army, Unit* unit, Battle_Type BT);//������� ������ �� �����
	int GetPower(Battle_Type BT, Unit* un, Army* army);//������ ���� �����
	int SelectCasualties(Army* target, Army* attacker, int dmg, Battle_Type BT, bool isHeavyDamage = false);
	//������
	int CheckFleet(Army* army);//�������� ������, ����������� ������ ���������
	//void StatusCheck(Army* army);
	//int ApplyDamage(Army* attArmy, Army* target, Unit* unit);
	int ShowRolls(Army* army, Roll* rolls, int count);
	void AutoRepairs(Army* army);
	//void OnDamage(Army* army, Army* target, Unit* unit);
	//�����������
	int Retreat(Army* army);
	bool CanRetreat(Army* army);//0 - ��� ������ ��� �����������, 1 - ���� (�������), 2- ���� (�����������)
	//������ ���������� �����
	int DamageUnit(Army* army, Unit* unit);
	int DestroyUnit(Army* army, Unit* unit);
	int ScuttleUnit(Army* army, Unit* unit);
	int FleetSupplyCheck(Army* army);
};