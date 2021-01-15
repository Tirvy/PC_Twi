class e_InitialUnitStats: public GameEffect{
public:
	bool GetQ(GameEffectQs queue){
		//if ((queue==eq_BeforeBattleRound)||(queue==eq_BeforeBattle)||(queue==eq_Movement))
		//	return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		player->GetUnitStats()->SetDefault();
		for (StatType stype=sPW; stype<MAX_STAT; stype=(StatType)((int)stype+1)){
			player->GetUnitStats()->SetParametr(FM,stype,FMstats[player->GetRace()][stype]);
		};
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if ((*aiter)->GetOwner()==player)
				(*aiter)->RefreshStats();
		}
		return er_none;
	}
};