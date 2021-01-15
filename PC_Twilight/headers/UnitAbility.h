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
uaNone                -          -          -        нейтральная абилка (debug)
uaSpaceBattle         power      shots      -        участвует в космобое
uaLandBattle          power      shots      -        участвует в наземном бое
uaInfantry            -          -          -        пехота (GF и ST)
uaCarried             toCommon   toFG       toGF     перевозка и слот
uaCarrier             fromPlanet -          -        перевозимый, пикается с планеты при 1
uaInvasion            -          -          -        можно скинуть на планету с нападением
uaDropped             -          -          -        можно скинуть на планету без нападения
uaStructure           -          -          -        захватываемое
uaFirstTarget         -          -          -        первая цель для назначения урона
uaProduction          base       takebonus  active   произодство лимит возможность
uaCapitalShip         -          -          -        контроль системы
uaCannon              power      shots      frplanet deep space cannon
uaSustain             damaged    absorb     active   выдерживать повреждения
uaAFB                 status     power      shots    AFB
uaBombard             status     thr PDS    needInv  бомбардировки
uaHyperDrive          speed      -          -        полет
uaAutoRepair          -          -          -        автопочинка
uaCritical            damage     -          -        критическое попадание
uaHeavyDamage         -          -          -        урон в Capital Ships
uaLimitOnPlanet       limit      -          -        лимит на планете
uaDamagedPenalty      -power     -shots     -        снижение характеристик при повреждении
uaEvasion             status     -          -        уклонение (наемники)
uaFighter             -          -          -        истребитель (Ван Хауг)
uaMultiple            -          -          -        GF, FG, ST
uaUnlimGF             -          -          -        Genesis I
uaKilled              -          -          -        убитый юнит
uaHeavyDamage         -          -          -        урон от этого корабля идет в Capital ships
uaYinFighter          Infantry   Planet     -        тип пехоты и исходная планета для пехоты/истребов Йин
uaNeedSupport         type       -          -        0 - пехота, 1 - обычный истреб, 2 - продвинутый
uaSupply			  -          -          -        учет в поддержке флота

*/