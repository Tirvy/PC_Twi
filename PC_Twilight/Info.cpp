Info::Info(){
};

string Info::UnitInfo(Unit *unit, Army *army){
	if (unit==0){
		(output="No unit");
		return output;
	}
	if (army==0){
		(output="No army");
		return output;
	}
	char * temp = new char[4];
	output.clear();
	output+=ShipsShort[unit->Class];
	int cap,gfcap,fgcap=0;
	int pasnumber=0;
	int passangers[MAX_UNIT];
	for (UnitType UT=GF; UT<=FG; UT=(UnitType)((int)UT+1))
		passangers[UT]=0;
	if (unit->HasAbility(uaSustain))
		if (unit->GetAbility(uaSustain).field1)
			output+="(dmg)";
	if (army->GetOwner() != 0){
		cap = 0;
		fgcap = 0;
		gfcap = 0;
		if (unit->HasAbility(uaCarrier)){
			cap = unit->GetAbility(uaCarrier).field1;
			fgcap = unit->GetAbility(uaCarrier).field2;
			gfcap = unit->GetAbility(uaCarrier).field3;
		}
		if (cap+gfcap+fgcap>0){
			output += "( ";
			for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++)
				if (((*iter)->carrier == unit)&&((*iter)->Class <= FG))
					passangers[(*iter)->Class]=passangers[(*iter)->Class]+1;
			for (UnitType UT = GF; UT <= FG; UT=(UnitType)((int)UT+1)){
				if (passangers[UT]>0){
					output+=ShipsShort[UT];
					if (passangers[UT]>1){
						sprintf(temp," x%d",passangers[UT]);
						output += temp;
					}
					output += "; ";
				}
			}
			if (unit->HasAbility(uaUnlimGF)){//если флагман Сол
				pasnumber=passangers[FG]+passangers[MU]+passangers[PDS];
				if (pasnumber<cap){
					output += "0";
					if (cap-pasnumber>1){
						sprintf(temp," x%d",cap-pasnumber);
						output += temp;
					}
				}
			}
			else{
				pasnumber=passangers[FG]+passangers[MU]+passangers[PDS]+passangers[GF]+passangers[ST];
				cap=max(max(cap,gfcap),fgcap);
				if (pasnumber<cap){
					output += "0";
					if (cap-pasnumber>1){
						sprintf(temp," x%d",cap-pasnumber);
						output += temp;
					}
				}
			}
			output += ")";
		}
	}
	return output;
};

Info::~Info(){
	//delete [] output; 
};
