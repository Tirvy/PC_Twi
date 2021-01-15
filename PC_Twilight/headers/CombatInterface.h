class CombatInterface{
	static const char c_Prefix[];
	static const int ROLL_NUMBER=100;
	char str[127];
	char stra[127];
public:
	//основные методы
	int CombatTacticalAction(Army* attArmy);//основной метод, инициализирует 3-6 этапы тактического действия, возвращает 1, если все ок
	Battle_Result SpaceCombat(Army* attArmy);//интерфейс космического боя
	int Landing(Army* attArmy, bool isTransfer = false);//запуск высадки
	Battle_Result InvasionCombat(Army* attArmy, Army* landArmy, Army* defArmy);//сражение на планете
	//int ShowArmy(Army* attArmy);//выводит армию, возвращает число юнитов
	void GEE(GameEffectQs Q, Army* attArmy, Army* defArmy, int round);//Game Effect Execute
	void GES(GameEffectQs Q, Army* attArmy, Army* defArmy, int round);//Game Effect Select
	//дайсы и назначение потерь:
	void RollingDices(Army* attArmy, Army* defArmy, Battle_Type BT, bool isBoth);//броски дайсов и назначение потерь
	int HowManyDices(Army *army, Unit* unit, Battle_Type BT);//сколько дайсов от юнита
	int GetPower(Battle_Type BT, Unit* un, Army* army);//какова сила юнита
	int SelectCasualties(Army* target, Army* attacker, int dmg, Battle_Type BT, bool isHeavyDamage = false);
	//прочее
	int CheckFleet(Army* army);//удаление юнитов, превышающих лимиты снабжения
	//void StatusCheck(Army* army);
	//int ApplyDamage(Army* attArmy, Army* target, Unit* unit);
	int ShowRolls(Army* army, Roll* rolls, int count);
	void AutoRepairs(Army* army);
	//void OnDamage(Army* army, Army* target, Unit* unit);
	//отступления
	int Retreat(Army* army);
	bool CanRetreat(Army* army);//0 - нет гексов для отступления, 1 - есть (обычные), 2- есть (тактические)
	//методы назначения урона
	int DamageUnit(Army* army, Unit* unit);
	int DestroyUnit(Army* army, Unit* unit);
	int ScuttleUnit(Army* army, Unit* unit);
	int FleetSupplyCheck(Army* army);
};