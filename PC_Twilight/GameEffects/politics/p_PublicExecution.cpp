class e_p_PublicExecution_add: public GameEffect{
public:
	e_p_PublicExecution_add(){
		id = "e_p_PublicExecution_add";
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_Battle) || (queue == eq_StatusEnd));
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		if (EP.queue == eq_Battle){
			army->ModUnitAbility(uaSpaceBattle,+1);
			army->ModUnitAbility(uaLandBattle,+1);
			army->ModUnitAbility(uaAFB,+1);
			army->ModUnitAbility(uaCannon,+1);
		}
		if (EP.queue == eq_StatusEnd)
			return er_delete;
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_p_PublicExecution_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_PublicExecution:public e_Politic{
protected:
	void PlayerEff(Player* player){
		player->AddGameEffect(new e_p_PublicExecution_add());
		for (vector<Planet*>::iterator iter = player->GetPlanetsList()->begin(); iter != player->GetPlanetsList()->end(); iter++)
			(*iter)->AddState(psExhausted);
		player->DiscardActions();
		char buff[512];
		sprintf(buff,"Player %s has public executed and loses all Action Cards, exhausts all planets and receives -1 penalty to all combat rolls in this round",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_PublicExecution(){
		//nt_strload(id,"Crown of Thalnos\0");
		id = "e_p_PublicExecution";
		tvote.player.resize(1);
		//strcpy(effect,"Elect player: Player's GF get +1");
		effect = "Elect player: Elected player loses all Action Cards, exhausts all his planet and receive -1 penalty to all combat rolls till end of round";
	}
	GameEffect * Clone(){
		return new e_p_PublicExecution(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};