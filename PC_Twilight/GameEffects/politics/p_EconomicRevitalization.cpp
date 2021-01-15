class e_p_EconomicRevitalization:public e_Politic{
protected:
	void PlayerEff(Player* player){
		int i;
		for (i = 0; i<_GameStats.GetPlayersNumber();++i){
			if (_Players[i]->GetGoods() > 0){
				_Players[i]->TakeGoods(1);
				player->GiveGoods(1);
			}
		}
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_EconomicRevitalization(){
		//nt_strload(id,"EconomicRevitalization\0");
		id = "EconomicRevitalization";
		tvote.player.resize(1);
		//strcpy(effect,"Chosen player takes 1 Trade Good from every other player");
		effect = "Chosen player takes 1 Trade Good from every other player";
	}
	GameEffect * Clone(){
		return new e_p_EconomicRevitalization(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};