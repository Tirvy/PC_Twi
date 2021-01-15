void e_Warfare::reset(){
	WARFARE_SECONDARY_COUNTERS_COST = 1;
	UseP = false;
	UseS = false;
}
void e_Warfare::special(int n){
}
void e_Warfare::sc_S(Player* player){
	char str[127];
	int moves = WARFARE_SECONDARY_SHIPS_TO_MOVE;
	int x,y;
	Hex* hexfrom; 
	Hex* hexto;
	Army* armyfrom;
	Army* armyto;
	Unit* unit;
	Unit* fighter;
	bool toPay = false;
	bool pickup = true;
	sprintf(str,"Player %s uses Warfare (secondary ability)",player->GetName().c_str());
	if (player->GetCountersSA()>=WARFARE_SECONDARY_COUNTERS_COST){
		while (moves>0){
			sprintf(str,"Select unactivated system with your fleet (moves left: %d)",moves);
			vector<int> tempvec = _GrIn.SysChoise(str,true);
			if (tempvec.size() == 0)
				break;
			x = tempvec[0];
			y = tempvec[1];
			hexfrom = _Map.GetHexh(x,y);
			armyfrom = FindAllyArmy(player,hexfrom);
			if (hexfrom->GotCC(player->GetId())){
				_Interface.PrintThingAll("This system is activated");
				continue;
			}
			if ((armyfrom==0)||(armyfrom->isDefeated())||(armyfrom->IsUnitWithAbility(uaCapitalShip)==0)){
				_Interface.PrintThingAll("There is no ships in selected system");
				continue;
			}
			vector<int> tempvec2 = _GrIn.SysChoise("Select adjacent system your control to move in",true);//2?
			if (tempvec2.size() == 0)
				continue;
			x = tempvec2[0];
			y = tempvec2[1];
			hexto = _Map.GetHexh(x,y);
			//if (isAdjacent(hexfrom,hexto)!=1){
			if (hexfrom->GetLinkedHexes()->GetLink(hexto) == ltNone){
				_Interface.PrintThingAll("This system isn't adjacent");
				continue;
			}
			if (HexController(hexto)!=player){
				_Interface.PrintThingAll("You don't control this system");
				continue;
			}
			armyto = FindAllyArmy(player,hexto,0);
			if (armyto==0){
				_Interface.PrintThingAll("Can't find fleet to move, it's strange...");
				continue;
			}
			sprintf(str,"Select ship to move from %s to %s",hexfrom->GetId().c_str(),hexto->GetId().c_str());
			unit = SelectDialogOneUnit(str,armyfrom,true,uaCapitalShip);
			if (unit==0)
				continue;
			sprintf(str,"Player %s moves %s from %s to %s",player->GetName().c_str(),ShipsFull[unit->Class].c_str(),hexfrom->GetId().c_str(),hexto->GetId().c_str());
			_Interface.PrintThingAll(str);
			player->ExecuteGameEffect(ExecuteParams(eq_Movement,armyfrom,unit));
			if (unit->HasAbility(uaKilled)){
				CombatInterface().DestroyUnit(armyfrom,unit);
				moves--;
				continue;
			}
			if (unit->HasAbility(uaCarrier)&&(unit->GetAbility(uaCarrier).field3==0)&&(armyfrom->IsUnitWithAbility(uaFighter))){
				pickup = true;
				while (pickup){
					fighter = SelectDialogOneUnit("You can pick up fighters to transport",armyfrom,true,uaFighter,0);
					if (fighter!=0){
						if (armyfrom->IsFreePlace(unit,fighter)){
							armyfrom->SetPassenger(unit,fighter);
							fighter->AssignAbility(uaFighter,1);
						}
						else{
							_Interface.PrintThingAll("No free space in transport for this unit");
							pickup = false;
						}
					}
					else
						pickup = false;
				}
			}
			MoveUnit(armyfrom,armyto,unit);
			armyto->AssignUnitAbility(uaFighter,0);
			for (int i=1; i<=armyto->IsUnitWithAbility(uaFighter); i++)
				armyto->SetPassenger(0,armyto->GetUnitWithAbility(uaFighter,i));
			player->CheckFleets();
			//armyfrom->CheckPasSupport();
			//armyto->CheckPasSupport();
			moves--;
			toPay = true;
		}
		if (toPay)
			player->TakeCounter(CC_strat,WARFARE_SECONDARY_COUNTERS_COST);
	}
	else{
		_Interface.PrintThingAll("You have no SACC to pay");
	}
}

void e_Warfare::sc_P(Player* player){
	char str[127];
	sprintf(str,"Player %s uses Warfare (primary ability)",player->GetName().c_str());
	_Interface.PrintThingAll(str);
	Hex* hex = 0;
	int x,y;
	bool selecting = true;
	while (selecting){
		vector<int> tempvec = _GrIn.SysChoise("Select system to activate High Alert",true);//true?
		if (tempvec.size() == 0)
			continue;
		x = tempvec[0];
		y = tempvec[1];
		hex = _Map.GetHexh(x,y);
		//army = FindAllyArmy(player,hex,0);
		if (hex->GetDanger()!=0){
			_Interface.PrintThingAll("This system cann't be activated");
			continue;
		}
		sprintf(str,"Use High Alert on system %s?",hex->GetId().c_str());
		if (!SelectDialogYesNo(str))
			continue;
		selecting = false;
		sprintf(str,"Player %s uses High Alert on %s",player->GetName().c_str(),hex->GetId().c_str());
		_Interface.PrintThingAll(str);
		//добавление эффекта HighAlert
		player->AddGameEffect(new e_HighAlert(hex,player));
	}
}

e_Warfare::e_Warfare(){
	//nt_strload(id,"Warfare\0");
	id = "Warfare";
	type = Warfare;
	//nt_strload(image,STRAT_B_PATH[type]);
	image = STRAT_B_PATH[type];
	reset();
}

bool e_Warfare::GetQ(GameEffectQs queue){
	if (queue==eq_AAA)
		return true;
	return false;
}
e_StratCard* e_Warfare::Clone(){
	return new e_Warfare(*this);
}
string e_Warfare::Save(){
	return string();
}
void e_Warfare::Load(std::string str){}
//High Alert effect
bool e_HighAlert::GetQ(GameEffectQs queue){
	if ((queue==eq_Battle)||(queue==eq_BeforeMovement)||(queue==eq_AfterMovement)||(queue==eq_StatusStart)||(queue==eq_LaunchEffect))
		return true;
	return false;
}
e_HighAlert::e_HighAlert(){
	id = "HighAlert";
	HighAlertHex = 0;
	ActivePlayer = 0;
	xl=0;yl=0;pl=0;
}
e_HighAlert::e_HighAlert(Hex* hex, Player* owner){
	id = "HighAlert";
	HighAlertHex = hex;
	int x,y;
	hex->GetCoords(&x,&y);
	xl=x;yl=y;pl=owner->GetNumber();
	ActivePlayer = owner;
	Army* army = FindAllyArmy(owner,hex,0);
	if (army!=0)
		for (int i=1; i<=army->IsUnitWithAbility(uaSpaceBattle);i++)
			army->GetUnitWithAbility(uaSpaceBattle,i)->AddAbility(uaHighAlert);
	_MapGraphics.PutSpecial(HIGH_ALERT_TOKEN,owner,x,y);
}

GameEffectRets e_HighAlert::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Army* army = EP.army1;
	Player* player = EP.player;
	int x,y;
	char str[127];
	char buff[256];
	if (Q == eq_LaunchEffect){
		cout<<"High Alert launch "<<xl<<" "<<yl<<" "<<pl<<endl;
		HighAlertHex = _Map.GetHexh(xl,yl);
		ActivePlayer = _Players[pl-1];
		_MapGraphics.PutSpecial(HIGH_ALERT_TOKEN,player,xl,yl);
	}
	if ((Q == eq_Battle)&&(army->GetHex() == HighAlertHex)){//+1 в бою
		for (int i=1;i<=army->IsUnitWithAbility(uaCapitalShip);i++){
			army->GetUnitWithAbility(uaCapitalShip,i)->ModAbility(uaSpaceBattle,-1);
			army->GetUnitWithAbility(uaCapitalShip,i)->ModAbility(uaAFB,-1);
			army->GetUnitWithAbility(uaCapitalShip,i)->ModAbility(uaCannon,-1);
		}
	}
	if (Q == eq_BeforeMovement){//+1 к скорости
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if (((*aiter)->GetHex() == HighAlertHex)&&((*aiter)->GetOwner() == player)){
				for (int i=1; i<=(*aiter)->IsUnitWithAbility(uaCapitalShip); i++){
					(*aiter)->GetUnitWithAbility(uaCapitalShip,i)->ModAbility(uaHyperDrive,+1);
					(*aiter)->GetUnitWithAbility(uaCapitalShip,i)->AddAbility(uaHighAlert);
				}
			}
		}
	}
	if ((Q == eq_AfterMovement)&&(army->IsUnitWithAbility(uaHighAlert))){//перенос кнопки
		sprintf(str,"Move High Alert to %s from %s?",army->GetHex()->GetId().c_str(),HighAlertHex->GetId().c_str());
		if (SelectDialogYesNo(str)){
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
				if ((*aiter)->GetOwner()==army->GetOwner())
					(*aiter)->DeleteUnitAbility(uaHighAlert);
			army->DeleteUnitAbility(uaHighAlert);
			sprintf(str,"Player %s moves High Alert to %s from %s",army->GetOwner()->GetName().c_str(),army->GetHex()->GetId().c_str(),HighAlertHex->GetId().c_str());
			_Interface.PrintThingAll(str);
			HighAlertHex->GetCoords(&x,&y);
			_MapGraphics.KillSpecial(HIGH_ALERT_TOKEN,x,y);
			sprintf(buff,"e_HighAlert::Execute : deleting Button from %d %d",x,y);
			Log(string(buff));
			HighAlertHex = army->GetHex();
			HighAlertHex->GetCoords(&x,&y);
			_MapGraphics.PutSpecial(HIGH_ALERT_TOKEN,army->GetOwner(),x,y);
			sprintf(buff,"e_HighAlert::Execute : put Button to %d %d",x,y);
			Log(string(buff));
		}
	}
	if (Q == eq_StatusStart){//удаление кнопки и самого эффекта
		HighAlertHex->GetCoords(&x,&y);
		_MapGraphics.KillSpecial(HIGH_ALERT_TOKEN,x,y);
		return er_delete;
	}
	return er_none;
}
GameEffect* e_HighAlert::Clone(){
	return new e_HighAlert(*this);
}
string e_HighAlert::Save(){
	std::stringstream ss;
	if ((HighAlertHex != 0)&&(ActivePlayer != 0)){
		int x = 0, y = 0;
		int p = ActivePlayer->GetNumber();
		HighAlertHex->GetCoords(&x, &y);
		ss<<x<<" "<<y<<" "<<p;
	}
	else
		Log("WARNING : High alert wasn't saved");
	return ss.str();
}
void e_HighAlert::Load(std::string str){
	std::istringstream iss(str);
	string s;
	iss>>s>>xl>>yl>>pl;
}