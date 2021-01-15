class e_p_CentrillicGas:public e_Politic{
protected:
	void YayEff(){
		int roll = rand()%DICE+1;
		char buff[255];
		Player* player = 0;
		sprintf(buff,"Result for Centrillic Gas is... %d",roll);
		_Interface.PrintThingAll(buff);
		if (roll<=3){
			sprintf(buff,"All units in Nebulas and Ion Storms are destroyed");
			_Interface.PrintThingAll(buff);
			bool t;
			Log("e_p_AncientArtifact::YayEff : go to search targets");
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
				if (((*aiter)->GetHex()->GetDanger() == Nebula) || ((*aiter)->GetHex()->GetDanger() == IonStorm)){
					Log("e_p_AncientArtifact::YayEff : destroy army in hex");
					t = false;
					for (int i=1; i<=(*aiter)->IsUnitWithAbility(uaNone); i++){
						(*aiter)->GetUnitWithAbility(uaNone,i)->AddAbility(uaKilled);
						t = true;
					}
					Log("e_p_AncientArtifact::YayEff : added uaKilled");
					if (t)
						CombatInterface().DestroyUnit(*aiter,(*aiter)->GetUnitWithAbility(uaNone,1));
					Log("e_p_AncientArtifact::YayEff : destroyed army in hex");
				}
			}
		}
		else{
			for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++){
				if (((*iter)->GetDanger() == Nebula) || ((*iter)->GetDanger() == IonStorm)){
					player = HexController(*iter);
					if (player != 0){
						player->GiveGoods(5);
						sprintf(buff,"Player %s receive 5 Trade Goods from system %s",player->GetName().c_str(),(*iter)->GetId().c_str());
						_Interface.PrintThingAll(buff);
					}
				}
			}
		}
	}
	void NayEff(){
	}
	void DoEffect(Voting won){
		if (won.yesno[0])
			YayEff();
		else
			NayEff();
	}
public:
	e_p_CentrillicGas(){
		id = "CentrillicGas";
		tvote.yesno.resize(1);
		effect = "YAY: roll a die, 1-3: destroy all unit in Nebulas and Ion Storms, 4-10: all players receive 5 Trade Goods for each system with Nebula or Ion Storm he controls; NAY: discard";
	}
	GameEffect * Clone(){
		return new e_p_CentrillicGas(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};