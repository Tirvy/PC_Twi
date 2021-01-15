class e_DockBuildLimit:public GameEffect{
	static const int BASE_DOCK_LIMIT = 2;
public:
	e_DockBuildLimit(){
		id = "DockBuildLimit";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_BeforeBuild)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		//PowVec<Army>* temp = _Armies.next;
		int i;
		int limit;
		//while (temp != 0){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if ((*aiter)->GetOwner() == player){
				if ((*aiter)->GetPlanet() != 0){
					limit = BASE_DOCK_LIMIT + (*aiter)->GetPlanet()->GetRes();
					for (i = 1; i <= (*aiter)->StackSize(DCK); i++){
						(*aiter)->GetUnit(DCK,i)->ModAbility(uaProduction,limit);
					}
				}
			}
			//temp = temp->next;
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_DockBuildLimit(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_FlagshipBuild:public GameEffect{
public:
	e_FlagshipBuild(){
		id = "FlagshipBuild";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_BeforeBuild)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		Hex* hex = EP.hex;
		if (hex != player->GetHS())
			player->GetUnitStats()->SetParametr(FM,sNP,0);
		return er_none;
	}
	GameEffect* Clone(){
		return new e_FlagshipBuild(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_HomeControl:public GameEffect{
public:
	e_HomeControl(){
		id = "HomeControl";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_ObjCanQualify)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		Hex* hex = player->GetHS();
		int* mod = EP.CommandCounters;
		bool controlhome = true;
		for (int i = 1; i <= MAX_PLANETS; i++)
			if ((hex->GetPlanet(i) != 0) && (hex->GetPlanet(i)->GetOwner() != player))
				controlhome = false;
		if (controlhome)
			*mod = 1;
		else
			*mod = 0;
		return er_none;
	}
	GameEffect* Clone(){
		return new e_HomeControl(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_GravityRift:public GameEffect{
	static const int SAVE_ROLL = 5;
public:
	e_GravityRift(){
		id = "GravityRift";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_Movement)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Army* army = EP.army1;
		Unit* unit = EP.unit;
		char buff[257];
		
		if ((army == 0) || (unit == 0)){
			Log("e_GravityRift::Execute : army or unit == 0");
			return er_none;
		}
		if (army->GetHex()->GetDanger() != GravityRift)
			return er_none;
		if (army->GetOwner()->GotTech(ttGravityDrive))
			return er_none;
		if (!unit->HasAbility(uaHyperDrive))
			return er_none;
		Log("e_GravityRift::Execute");
		int roll = rand()%DICE + 1;
		if (roll <= SAVE_ROLL){
			sprintf(buff,"%s was destroyed in system %s trying to leave Gravity Rift, roll %d",ShipsFull[unit->Class].c_str(),army->GetHex()->GetId().c_str(),roll);
			_Interface.PrintThingAll(buff);
			unit->AddAbility(uaKilled);
		}
		else{
			sprintf(buff,"%s successfully left system %s, roll %d",ShipsFull[unit->Class].c_str(),army->GetHex()->GetId().c_str(),roll);
			_Interface.PrintThingAll(buff);
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_GravityRift(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_ResearchTech:public GameEffect{
public:
	e_ResearchTech(){
		id = "ResearchTech";
	}
	bool GetQ(GameEffectQs queue){
		if (queue == eq_ResearchTech)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		int* ResCost = EP.CommandCounters;
		int* CounterCost = EP.ActionCards;
		int r = ResearchTechDialog(player,*ResCost,*CounterCost);
		*CounterCost = r;
		return er_none;
	}
	GameEffect* Clone(){
		return new e_ResearchTech(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_ActionCardLimit:public GameEffect{
	int limit;
public:
	e_ActionCardLimit(){
		id = "ActionCardLimit";
		limit = 7;
	}
	bool GetQ(GameEffectQs queue){
		if (queue == eq_ReceiveActionCard)
			return true;
		return false;
	}
	void reset(){
		limit = 7;
	}
	void SetLimit(int n){
		if (n > 0)
			limit = n;
		else
			limit = 0;
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		e_ActionCard* AC;
		char buff[255];
		_Interface.SetCurrPlayer(player->GetNumber() - 1);
		while (player->GetActionsNumber() > limit){
			sprintf(buff,"You need to discard %d Action Card(s)",player->GetActionsNumber()-limit);
			AC = SelectDialogActionCard(buff,player,false);
			if (AC == 0){
				Log("e_ActionCardLimit::Execute : SUM TING WONG");
				break;
			}
			player->RemoveGameEffect(AC->GetId());
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_ActionCardLimit(*this);
	}
	string Save(){
		std::stringstream ss;
		ss<<limit;
		return ss.str();
	}
	void Load(std::string str){
		std::istringstream iss(str);
		iss>>limit;
	}
};