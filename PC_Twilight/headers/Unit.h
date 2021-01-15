#define FIELD_SKIP -42

struct Unit{
	UnitType Class;
	int HP;
	int prioritet;
	int power;
	int shots;
	int speed;
	int production;
	Unit* carrier;//ссылка на юнит-перевозчик
	bool damaged;
	vector<UnitAbility> abilities;
	NodePath model;
	Unit(UnitType ut, int in_hp, int in_pr, int in_pow, int in_sh, int in_sp, int in_prod, Unit* in_car, bool in_dmg){
		Class=ut;
		HP=in_hp;
		prioritet=in_pr;
		power=in_pow;
		shots=in_sh;
		speed=in_sp;
		carrier=in_car;
		damaged=in_dmg;
		production=in_prod;
		abilities.clear();
		model = NodePath();//Ernie
	}
	~Unit(){}//Ernies
	bool HasAbility(UnitAbType in_UAT, int f1=FIELD_SKIP, int f2=FIELD_SKIP, int f3=FIELD_SKIP);
	int AddAbility(UnitAbType in_UAT, int f1=0, int f2=0, int f3=0);
	int DeleteAbility(UnitAbType in_UAT);
	void DeleteAllAbilites();
	int ModAbility(UnitAbType in_UAT, int f1=FIELD_SKIP, int f2=FIELD_SKIP, int f3=FIELD_SKIP);
	int AssignAbility(UnitAbType in_UAT, int f1=FIELD_SKIP, int f2=FIELD_SKIP, int f3=FIELD_SKIP);
	UnitAbility GetAbility(UnitAbType in_UAT);
};

void CopyUnitAbility(Unit* from, Unit* to);