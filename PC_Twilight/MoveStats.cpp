
MoveStats::MoveStats(){
	Reset();
}
//enum DangerType { DT_NONE, Nebula, Asteroids, IonStorm, Supernova, GravityRift, DT_MAX};
const bool standart_pass[DT_MAX] = { 1, 0, 0, 0, 0, 0};
const bool standart_active[DT_MAX] = { 1, 1, 0, 1, 0, 1};
const MoveOutType standart_moveout[DT_MAX] = { MO_none, MO_lowspeed, MO_none, MO_lowspeed, MO_none, MO_lowspeed };

void MoveStats::Reset(){
	for (int i=0;i<DT_MAX;++i){
		pass[i] = standart_pass[i];
		active[i] =	standart_active[i];
		moveout[i] = standart_moveout[i];
	}
}