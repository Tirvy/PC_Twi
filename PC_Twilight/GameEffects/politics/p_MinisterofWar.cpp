class e_p_MinisterOfWar_add: public GameEffect{
	bool active;
public:
	e_p_MinisterOfWar_add(){
		id = "MinisterOfWar_add";
		image = EMPTY_EVENT_IMG;
	}
	bool GetQ(GameEffectQs queue){
		if (((queue == eq_BeforeBattleAction) && active) || (queue == eq_BeforeBattle))
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* minister = EP.army1;
		Army* target = EP.army2;
		GameEffectQs Q = EP.queue;
		char buff[255];
		if (target == 0)
			return er_none;
		if (target->isDefeated())
			return er_none;
		if (minister == 0)
			return er_none;
		if (minister->GetOwner() == 0)
			return er_none;
		if (Q == eq_BeforeBattle)
			active = true;
		if (minister->GetOwner()->GetCountersSA() < 1){
			_Interface.PrintThingPlayer(minister->GetOwner()->GetNumber()-1,"Not enough SACC to use this ability");
			return er_none;
		}
		if (SelectDialogYesNo("Use Minister of War ability (1 SACC to pay)?")){
			sprintf(buff,"Player %s uses Minister of War ability",minister->GetOwner()->GetName().c_str());
			_Interface.PrintThingAll(buff);
			minister->GetOwner()->TakeCounter(CC_strat);
			active = false;
			if (target->GetPlanet() == 0)
				CombatInterface().SelectCasualties(target,minister,1,bt_Space);
			else
				CombatInterface().SelectCasualties(target,minister,1,bt_Invasion);
			return er_normal;
		}
		return er_none;
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfWar_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_MinisterOfWar:public e_Politic{
protected:
	void PlayerEff(Player* player){
		char buff[255];
		sprintf(buff,"Player %s is Minister of War now",player->GetName().c_str());
		_Interface.PrintThingAll(buff);
		player->AddGameEffect(new e_p_MinisterOfWar_add());
	}
	void DoEffect(Voting won){
		PlayerEff(won.player[0]);
	}
public:
	e_p_MinisterOfWar(){
		id = "MinisterOfWar";
		tvote.player.resize(1);
		effect = "Elected player may spend 1 SACC to inflict 1 damage to enemy fleet before any Space battle he participates begins";
	}
	GameEffect * Clone(){
		return new e_p_MinisterOfWar(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
