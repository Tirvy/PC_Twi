class e_p_CrownOfThalnos_add: public GameEffect{
public:
	e_p_CrownOfThalnos_add(){
		nt_strload(id,"Crown_of_Thalnos_add\0");
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_Battle);
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		if (EP.queue == eq_Battle){
			for (int i=1; i<=army->IsUnitWithAbility(uaInfantry); i++){
				army->GetUnitWithAbility(uaInfantry,i)->ModAbility(uaLandBattle,-1);
			}
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_p_CrownOfThalnos_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_CrownOfThalnos:public e_Politic{
protected:
	void PlayerEff(Player* player){
		player->AddGameEffect(new e_p_CrownOfThalnos_add());
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_CrownOfThalnos(){
		//nt_strload(id,"Crown of Thalnos\0");
		id = "CrownOfThalnos";
		tvote.player.resize(1);
		//strcpy(effect,"Elect player: Player's GF get +1");
		effect = "Elect player: Elected player's GF get +1";
	}
	GameEffect * Clone(){
		return new e_p_CrownOfThalnos(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};