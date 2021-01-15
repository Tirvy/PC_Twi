class e_a_TestActionCard:public e_ActionCard{
public:
	e_a_TestActionCard(){
		_name = "Test Action Card";
		_description = "Before action. Receive 1 Trade Good";
		_when = acBeforeAction;
		id = "TestActionCard";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		if (Q == eq_AAA){
			Player* player = EP.player;
			char buff[255];
			sprintf(buff,"Player %s receives 1 Trade Good from TestActionCard",player->GetName().c_str());
			_Interface.PrintThingAll(buff);
			player->GiveGoods(1);
			return er_delete_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_TestActionCard(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};