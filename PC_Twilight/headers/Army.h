class Army{
private:
	friend Unit* MoveUnit(Army* from, Army* to, Unit* un);
	friend void MoveUnit(Army* from, Army* to, int num);
	Player* _owner;
	vector<Unit*> _units;
	Hex* _armyHex;//система, в которой находится армия
	Planet* _armyPlanet;//планета, на которой находится армия, NULL если в космосе
	int _position;//-1 - космос,0,1,2 - номер планеты, на которой находится армия
public:
	bool _retreating;
	//конструктор
	Army(Player* in_owner, Hex* in_hex, Planet* in_pl=0);
	//геты и тому подобное
	Player* GetOwner();
	Planet* GetPlanet();
	int GetPosition();
	Hex* GetHex();
	int GetArmyHP();//возвращает HP армии
	int GetArmyPower();//возвращает силу армии, равную Sum((11-pow)*shots)
	bool isDefeated();//проверка боеспособности армии
	bool IsUnitInArmy(Unit* unit);
	vector<Unit*>* GetUnits();//PowExv<Unit>*
	int StackSize(UnitType UT);//количество юнитов заданного типа
	Unit* GetUnit(int n);//возвращает указатель на n-ный юнит, если он есть и NULL если его нет
	Unit* GetUnit(UnitType UT);//возвращает указатель на первый в армии юнит указанного типа
	Unit* GetUnit(UnitType UT, int n);//возвращает указатель на n-ый юнит данного типа в армии
	int GetUnitNumber(Unit* un);//возвращает номер юнита в списке армии и 0, если не нашел
	//добавление/удаление юнитов
	Unit* AddUnit(UnitType UT, bool isDamaged=false);
	void AddUnits(UnitType UT, int n);//добавляет n юнитов заданного типа
	int KillUnit(Unit* unit);
	void KillArmy();//полная очистка units
	void RemoveKilledUnits();
	//пассажиры, снабжение
	vector<Unit*> GetPassengers(Unit* car);//возвращает список юнитов, сидящих в car
	int SetPassenger(Unit* car, Unit* pas);//сажает юнит pas в car,
		//в случае успеха возвращает число оставшихся свободных мест в car,
		//иначе -1
	int IsFreePlace(Unit* car, Unit* pas); //влезет ли в юнит что-то еще
	int FleetSupply();//возвращает минимальный флит-супплай для данной армии
	int CheckPasSupport();//пассажиры
	int CheckFleetSupport();//снабжение
	int FighterCapacity(Unit* unit = 0);//кол-во истребов, поддерживаемых флотом без unit
	int FreeStackSize(UnitType UT);//
	int SpaceRedistribute(Unit* unit);//перераспределяет юнит, произведенныq в космосе в транспорт
	//урон
	int AssignDamage(Unit* un);//наносит урон выбранному юниту, возвращает нанесенный урон
	//методы ко всей армии
	void Repair();//полная починка всех поврежденных кораблей
	void RefreshStats();//обновление статов юнитов в армии
	//абилки
	int IsUnitWithAbility(UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//выдает кол-во юнитов с данной абилкой и ее полями в случае заданных b
	Unit* GetUnitWithAbility(UnitAbType in_UAT,int n,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//возвращает указатель на юнит с данной абилкой и ее полями
	int ModUnitAbility(UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//модифицирует поля всех юнитов в армии с данной абилкой
	int AssignUnitAbility(UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//назначает поля всех юнитов в армии с данной абилкой
	int AddUnitAbility(UnitType UT, UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//добавляет абилку всем юнатам в армии заданного типа UT
	int DeleteUnitAbility(UnitAbType in_UAT);
		//убирает абилку у всех юнитов в армии
};

struct spawnarmy{
	int unit[MAX_UNIT];
	spawnarmy(){
		int i;
		for (i=0;i<MAX_UNIT;++i)
			unit[i]=0;
	}
};

Army* FindAllyArmy(Player* player, Hex* hex, Planet* planet = 0);
Army* FindOpponentArmy(Army* army);
Army* NewArmy(Player* player, Hex* hex, Planet* planet = 0);

struct Roll{
	int value;
	int power;
	Unit* unit;
	bool isRerolled;
	Roll(){
		value=0;
		power=0;
		unit=0;
		isRerolled=false;
	}
};

struct UnitArmy{
	Unit* unit;
	Army* army;
	int selected;
};

struct ProductionPlace{
	Planet* planet;
	int limit;
	Army* army;
	bool dock;
};

struct SpawnUnit{
	UnitType UT;
	vector<ProductionPlace>::iterator iter;
	int n;
};

struct UnitSelection{
	UnitType UT;
	Army* army;
	Unit* unit;
	bool multiple;
	int n;
	int selected;
	/*UnitSelection(UnitType inUT, Army* inArmy, int inn){
		UT = inUT;
		army = inArmy;
		n = inn;
	}*/
};


vector<Army*> _Armies;