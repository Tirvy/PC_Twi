class Army{
private:
	friend Unit* MoveUnit(Army* from, Army* to, Unit* un);
	friend void MoveUnit(Army* from, Army* to, int num);
	Player* _owner;
	vector<Unit*> _units;
	Hex* _armyHex;//�������, � ������� ��������� �����
	Planet* _armyPlanet;//�������, �� ������� ��������� �����, NULL ���� � �������
	int _position;//-1 - ������,0,1,2 - ����� �������, �� ������� ��������� �����
public:
	bool _retreating;
	//�����������
	Army(Player* in_owner, Hex* in_hex, Planet* in_pl=0);
	//���� � ���� ��������
	Player* GetOwner();
	Planet* GetPlanet();
	int GetPosition();
	Hex* GetHex();
	int GetArmyHP();//���������� HP �����
	int GetArmyPower();//���������� ���� �����, ������ Sum((11-pow)*shots)
	bool isDefeated();//�������� �������������� �����
	bool IsUnitInArmy(Unit* unit);
	vector<Unit*>* GetUnits();//PowExv<Unit>*
	int StackSize(UnitType UT);//���������� ������ ��������� ����
	Unit* GetUnit(int n);//���������� ��������� �� n-��� ����, ���� �� ���� � NULL ���� ��� ���
	Unit* GetUnit(UnitType UT);//���������� ��������� �� ������ � ����� ���� ���������� ����
	Unit* GetUnit(UnitType UT, int n);//���������� ��������� �� n-�� ���� ������� ���� � �����
	int GetUnitNumber(Unit* un);//���������� ����� ����� � ������ ����� � 0, ���� �� �����
	//����������/�������� ������
	Unit* AddUnit(UnitType UT, bool isDamaged=false);
	void AddUnits(UnitType UT, int n);//��������� n ������ ��������� ����
	int KillUnit(Unit* unit);
	void KillArmy();//������ ������� units
	void RemoveKilledUnits();
	//���������, ���������
	vector<Unit*> GetPassengers(Unit* car);//���������� ������ ������, ������� � car
	int SetPassenger(Unit* car, Unit* pas);//������ ���� pas � car,
		//� ������ ������ ���������� ����� ���������� ��������� ���� � car,
		//����� -1
	int IsFreePlace(Unit* car, Unit* pas); //������ �� � ���� ���-�� ���
	int FleetSupply();//���������� ����������� ����-������� ��� ������ �����
	int CheckPasSupport();//���������
	int CheckFleetSupport();//���������
	int FighterCapacity(Unit* unit = 0);//���-�� ��������, �������������� ������ ��� unit
	int FreeStackSize(UnitType UT);//
	int SpaceRedistribute(Unit* unit);//���������������� ����, ������������q � ������� � ���������
	//����
	int AssignDamage(Unit* un);//������� ���� ���������� �����, ���������� ���������� ����
	//������ �� ���� �����
	void Repair();//������ ������� ���� ������������ ��������
	void RefreshStats();//���������� ������ ������ � �����
	//������
	int IsUnitWithAbility(UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//������ ���-�� ������ � ������ ������� � �� ������ � ������ �������� b
	Unit* GetUnitWithAbility(UnitAbType in_UAT,int n,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//���������� ��������� �� ���� � ������ ������� � �� ������
	int ModUnitAbility(UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//������������ ���� ���� ������ � ����� � ������ �������
	int AssignUnitAbility(UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//��������� ���� ���� ������ � ����� � ������ �������
	int AddUnitAbility(UnitType UT, UnitAbType in_UAT,int f1=FIELD_SKIP,int f2=FIELD_SKIP,int f3=FIELD_SKIP);
		//��������� ������ ���� ������ � ����� ��������� ���� UT
	int DeleteUnitAbility(UnitAbType in_UAT);
		//������� ������ � ���� ������ � �����
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