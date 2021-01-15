enum playedPhase {acBeforeAction, acAAA, acBeforeBattleRound};

class e_ActionCard: public GameEffect{
	friend class InfoArea;
protected:
	string _name;
	string _description;
	playedPhase	_when;
public:
	string GetName();
	string GetDescription();
	playedPhase GetPhase();
	//bool GetQ(GameEffectQs queue);
	//GameEffectRets Execute(ExecuteParams EP);
};