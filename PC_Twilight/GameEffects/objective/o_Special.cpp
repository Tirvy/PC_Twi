//у меня Ч ПО, игра закончена
o_g_VP::o_g_VP(){
	id = "o_g_VP";
	reqs = "Emperor of the Galaxy";
	reqsShort = "I have X VP";
	value = _GameStats.VPftw;
	type = vp_special;
	isDone = false;
	isFulfill = false;
	isSecret = false;
	isOpen = false;
}
bool o_g_VP::GetQ(GameEffectQs queue){
	if ((queue == eq_FinishGame)||(queue == eq_Objective))
		return true;
	return false;
}
GameEffectRets o_g_VP::Execute(ExecuteParams EP){
	Player* player = EP.player;
	if (player->recountVP()>=_GameStats.VPftw)
		throw endofgame(2);
	return er_none;
}
void o_g_VP::reset(){
	value = 0;
}
e_Objective* o_g_VP::Clone(){
	return new o_g_VP(*this);
}
string o_g_VP::Save(){
	return string();
}
void o_g_VP::Load(std::string str){}