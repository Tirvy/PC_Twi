class UnitStats{
private:
	int mStats[MAX_UNIT][MAX_STAT];
public:
	UnitStats();//������� ������� ������ � ����������� ������
	void SetParametr(UnitType UT, StatType stat, int value);
	int GetParametr(UnitType UT, StatType stat);
	void SetModifier(UnitType UT, StatType stat, int value);
	void SetDefault();//��������� ������ ������ ����������� �� ���������
	void SetFlagship(RacesType c);
};