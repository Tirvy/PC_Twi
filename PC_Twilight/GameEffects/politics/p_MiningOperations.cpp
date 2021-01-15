class e_p_MiningOperations:public e_Politic{
protected:
	void YayEff(){
		char buff[255];
		Player* player;
		bool t;
		for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
			player = HexController(*iter);
			if (player != 0){
				t = false;
				for (int i = 0; i < (*iter)->GetLinkedHexes()->GetLinkNumber(); i++)
					if (((*iter)->GetLinkedHexes()->GetLink(i) == ltBound) && ((*iter)->GetLinkedHexes()->GetLinkedHex(i)->GetDanger() == Asteroids))
						t = true;
				if (t){
					sprintf(buff,"Player %s receive 4 Trade Goods from Asteroid Mining Facilities",player->GetName().c_str());
					_Interface.PrintThingAll(buff);
					player->GiveGoods(4);
				}
			}
		}
	}
	void NayEff(){
		_Interface.PrintThingAll("All players lose 2 Trade Goods");
		for (int i = 0; i < _GameStats.GetPlayersNumber(); i++)
			_Players[i]->TakeGoods(2);
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_MiningOperations(){
		id = "MiningOperations";
		tvote.yesno.resize(1);
		effect = "YAY: players recieve 4 Trade Goods for each system they control and adjacent to Asteroid Field; NAY: each player loses 2 Trade Goods";
	}
	GameEffect * Clone(){
		return new e_p_MiningOperations(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};