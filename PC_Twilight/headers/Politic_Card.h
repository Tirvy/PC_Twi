struct Voting{
	vector<Player*> player;
	vector<Planet*> planet;
	vector<Hex*> system;
	vector<bool> yesno;
	int votes;
	Voting(){
		player.clear();
		planet.clear();
		system.clear();
		yesno.clear();
		votes = 0;
	}
	bool SameAs(Voting other){
		if ((yesno.size() != other.yesno.size())||(player.size() != other.player.size())||(planet.size() != other.planet.size())||(system.size() != other.system.size()))
			return false;
		if ((equal(yesno.begin(),yesno.end(),other.yesno.begin()))&&(equal(player.begin(),player.end(),other.player.begin()))&&(equal(planet.begin(),planet.end(),other.planet.begin()))&&(equal(system.begin(),system.end(),other.system.begin())))
			return true;
		return false;
	}
};


class e_Politic:public GameEffect{
protected:
	friend class InfoArea;
	Voting tvote;
	string effect;
	virtual void DoEffect(Voting won) = 0;
private:
public:

	//e_Politic(PCtypes in_type = pc_none);
	string GetEffect();
	GameEffectRets Execute(ExecuteParams EP);
	bool GetQ(GameEffectQs queue);
};