bool Unit::HasAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	bool result = false;
	for (vector<UnitAbility>::iterator iter = abilities.begin(); iter != abilities.end(); iter++){
		if (iter->UAT == in_UAT){
			result = true;
			if ((f1 != FIELD_SKIP)&&(f1 != iter->field1))
				result=false;
			if ((f2 != FIELD_SKIP)&&(f2 != iter->field2))
				result=false;
			if ((f3 != FIELD_SKIP)&&(f3 != iter->field3))
				result=false;
		}
	}
	return result;
};

int Unit::AddAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	UnitAbility UA(in_UAT,f1,f2,f3);
	if (HasAbility(in_UAT))
		AssignAbility(in_UAT,f1,f2,f3);
	else
		abilities.push_back(UA);
	return 1;
};

int Unit::DeleteAbility(UnitAbType in_UAT){
	for (vector<UnitAbility>::iterator iter = abilities.begin(); iter != abilities.end(); iter++){
		if (iter->UAT == in_UAT){
			abilities.erase(iter);
			break;
		}
	}
	return 1;
};

int Unit::AssignAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	for (vector<UnitAbility>::iterator iter = abilities.begin(); iter != abilities.end(); iter++){
		if (iter->UAT == in_UAT){
			if (f1!=FIELD_SKIP)
				iter->field1=f1;
			if (f2!=FIELD_SKIP)
				iter->field2=f2;
			if (f3!=FIELD_SKIP)
				iter->field3=f3;
		}
	}
	return 1;
};

int Unit::ModAbility(UnitAbType in_UAT, int f1, int f2, int f3){
	for (vector<UnitAbility>::iterator iter = abilities.begin(); iter != abilities.end(); iter++){
		if (iter->UAT == in_UAT){
			if (f1!=FIELD_SKIP)
				iter->field1+=f1;
			if (f2!=FIELD_SKIP)
				iter->field2+=f2;
			if (f3!=FIELD_SKIP)
				iter->field3+=f3;
		}
	}
	return 1;
};

UnitAbility Unit::GetAbility(UnitAbType in_UAT){
	UnitAbility result(uaNone,-42,-42,-42);
	for (vector<UnitAbility>::iterator iter = abilities.begin(); iter != abilities.end(); iter++)
		if (iter->UAT == in_UAT)
			result = *iter;
	return result;
};

void Unit::DeleteAllAbilites(){
	abilities.clear();
};

void CopyUnitAbility(Unit* from, Unit* to){
	to->abilities = from->abilities;
};