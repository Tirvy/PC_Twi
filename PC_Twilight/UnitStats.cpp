UnitStats::UnitStats(){
	for (UnitType UT=GF; UT<MAX_UNIT; UT=(UnitType)((int)UT+1)){
		for (StatType stat=sPW; stat<MAX_STAT; stat=(StatType)((int)stat+1)){
			mStats[UT][stat]=0;
		}
	}
}

void UnitStats::SetParametr(UnitType UT, StatType stat, int value){
	mStats[UT][stat]=value;
}

void UnitStats::SetModifier(UnitType UT, StatType stat, int value){
	mStats[UT][stat]+=value;
}

int UnitStats::GetParametr(UnitType UT, StatType stat){
	int result=mStats[UT][stat];
	return result;
}

void UnitStats::SetDefault(){
	for (UnitType UT=GF; UT<MAX_UNIT; UT=(UnitType)((int)UT+1)){
		for (StatType stat=sPW; stat<MAX_STAT; stat=(StatType)((int)stat+1)){
			mStats[UT][stat]=defStat[UT][stat];
		}
	}
}

void UnitStats::SetFlagship(RacesType c){
	if (c!=MAX_RACE)
		for (StatType stat=sPW; stat<MAX_STAT; stat=(StatType)((int)stat+1)){
			mStats[FM][stat]=FMstats[c][stat];
		}
}