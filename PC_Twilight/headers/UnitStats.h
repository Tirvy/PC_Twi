class UnitStats{
private:
	int mStats[MAX_UNIT][MAX_STAT];
public:
	UnitStats();//создает нулевой массив с параметрами юнитов
	void SetParametr(UnitType UT, StatType stat, int value);
	int GetParametr(UnitType UT, StatType stat);
	void SetModifier(UnitType UT, StatType stat, int value);
	void SetDefault();//заполняет массив данных параметрами по умолчанию
	void SetFlagship(RacesType c);
};