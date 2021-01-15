bool e_Objective::GetQ(GameEffectQs queue){
	//_Interface.PrintThingAll("e_Objective::GetQ");
	return false;	
}
e_Objective::e_Objective(){
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = false;
	value = 0;
	//sprintf(reqs,"No description");
	reqs = "No description";
	//sprintf(reqsShort,"No description");
	reqsShort = "No description";
	type = vp_stage1;
}
VP_type  e_Objective::GetType(){
	return type;
}
string e_Objective::GetReqs(){
	return reqs;
}
string e_Objective::GetShortReqs(){
	return reqsShort;
}
void e_Objective::reset(){
}

GameEffectRets e_Objective::Execute(ExecuteParams EP){
	//_Interface.PrintThingAll("e_Objective::Execute");
	return er_none;
}

e_Objective* e_Objective::Clone(){
	return new e_Objective(*this);
}

string e_Objective::Save(){
	return string();
}

void e_Objective::Load(string str){}

#include "objective\\o_Tracker.cpp"
#include "objective\\o_PublicStage1.cpp"
#include "objective\\o_PublicStage2.cpp"
#include "objective\\o_Preliminary.cpp"
#include "objective\\o_Secret.cpp"
#include "objective\\o_Special.cpp"