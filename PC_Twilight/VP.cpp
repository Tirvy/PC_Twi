VictoryPoint::VictoryPoint(int power_in,VP_type type_in,const string descr){
	power = power_in;
	type = type_in;
	nt_strload(description,descr);
}
int VictoryPoint::GetPower(){
	return power;
}
VP_type VictoryPoint::GetType(){
	return type;
}
string VictoryPoint::GetDescr(){
	return description;
}