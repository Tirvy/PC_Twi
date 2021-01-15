struct UnitAbility{
	UnitAbType UAT;
	int field1;
	int field2;
	int field3;
	UnitAbility(UnitAbType in_UAT, int f1 = 0, int f2 = 0, int f3 = 0){
		UAT = in_UAT;
		field1 = f1;
		field2 = f2;
		field3 = f3;
	}
	UnitAbility(){
		UAT = uaNone;
		field1 = 0;
		field2 = 0;
		field3 = 0;
	}
};

void InitialAbilities(Unit* unit, int type, Army* army);
void FlagshipAbilities(Unit* unit, int type, Army* army);
void RefreshArmyAbilities(Army* army, int type);
void RefreshArmyAbilities(Player* player, int type);


/*
   UAT                f1         f2         f3
uaNone                -          -          -        ����������� ������ (debug)
uaSpaceBattle         power      shots      -        ��������� � ��������
uaLandBattle          power      shots      -        ��������� � �������� ���
uaInfantry            -          -          -        ������ (GF � ST)
uaCarried             toCommon   toFG       toGF     ��������� � ����
uaCarrier             fromPlanet -          -        �����������, �������� � ������� ��� 1
uaInvasion            -          -          -        ����� ������� �� ������� � ����������
uaDropped             -          -          -        ����� ������� �� ������� ��� ���������
uaStructure           -          -          -        �������������
uaFirstTarget         -          -          -        ������ ���� ��� ���������� �����
uaProduction          base       takebonus  active   ����������� ����� �����������
uaCapitalShip         -          -          -        �������� �������
uaCannon              power      shots      frplanet deep space cannon
uaSustain             damaged    absorb     active   ����������� �����������
uaAFB                 status     power      shots    AFB
uaBombard             status     thr PDS    needInv  �������������
uaHyperDrive          speed      -          -        �����
uaAutoRepair          -          -          -        �����������
uaCritical            damage     -          -        ����������� ���������
uaHeavyDamage         -          -          -        ���� � Capital Ships
uaLimitOnPlanet       limit      -          -        ����� �� �������
uaDamagedPenalty      -power     -shots     -        �������� ������������� ��� �����������
uaEvasion             status     -          -        ��������� (��������)
uaFighter             -          -          -        ����������� (��� ����)
uaMultiple            -          -          -        GF, FG, ST
uaUnlimGF             -          -          -        Genesis I
uaKilled              -          -          -        ������ ����
uaHeavyDamage         -          -          -        ���� �� ����� ������� ���� � Capital ships
uaYinFighter          Infantry   Planet     -        ��� ������ � �������� ������� ��� ������/�������� ���
uaNeedSupport         type       -          -        0 - ������, 1 - ������� ������, 2 - �����������
uaSupply			  -          -          -        ���� � ��������� �����

*/