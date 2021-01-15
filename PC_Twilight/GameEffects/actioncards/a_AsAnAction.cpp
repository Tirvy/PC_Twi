//Local Unrest
class e_a_LocalUnrest:public e_ActionCard{
public:
	e_a_LocalUnrest(){
		_name = "LocalUnrest";
		_description = "As an action. Exhaust any 1 planet in a non-home system and destroy 1 Infantry on that planet; it reverts to neutral status if emptied";
		_when = acAAA;
		id = "a_LocalUnrest";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Planet* planet = 0;
		Army* army;
		int flag;
		if (Q == eq_AAA){
			while (true){
				planet = SelectDialogPlanet("Select planet to use Local Unrest",
					"Select system to use Local Unrest",
					0,player,true,false,false,true,true,true);
				if (planet){
					flag = 0;
					planet->GetOwner()->ExecuteGameEffect(ExecuteParams(eq_ActionCardBreak,player,this,&flag));
					if (flag == 1){
						_Interface.PrintThingPlayer(player->GetNumber()-1,"This player is immune to Local Unrest");
						continue;
					}
					sprintf(buff,"Player %s uses Local Unrest on planet %s",player->GetName().c_str(),planet->GetName().c_str());
					_Interface.PrintThingAll(buff);
					army = FindArmy(planet->GetSystem(),0,true,planet);
					if (army->IsUnitWithAbility(uaInfantry)){
						_Interface.PrintThingAll("Local Unrest: 1 Infantry unit was destroyed");
						CombatInterface().DestroyUnit(army,army->GetUnitWithAbility(uaInfantry,1));
					}
					if (army->isDefeated()){
						sprintf(buff,"Local Unrest: player %s loses control under planet %s",planet->GetOwner()->GetName().c_str(),planet->GetName().c_str());
						_Interface.PrintThingAll(buff);
						army->KillArmy();
						planet->GetOwner()->DeCapture(planet);
						ClearArmies();
					}
				}
				else
					return er_none;
			}
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_LocalUnrest(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Good Year
class e_a_GoodYear:public e_ActionCard{
public:
	e_a_GoodYear(){
		_name = "Good Year";
		_description = "As an action. Receive 1 Trade Good for each your planet outside your Home System";
		_when = acAAA;
		id = "a_GoodYear";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		int goods = 0;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Good Year?")){
				for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++)
					if (((*piter)->GetSystem() != player->GetHS()) && ((*piter)->GetSystem() != player->GetExtraHS()))
						goods++;
				player->GiveGoods(goods);
				sprintf(buff,"Player %s uses Good Year",player->GetName().c_str());
				_Interface.PrintThingAll(buff);
				sprintf(buff,"Player %s has recieved %d Trade Good(s) from Good Year",player->GetName().c_str(),goods);
				_Interface.PrintThingAll(buff);
				return er_delete;
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_GoodYear(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Rise Of Messiah
class e_a_RiseOfMessiah:public e_ActionCard{
public:
	e_a_RiseOfMessiah(){
		_name = "Rise Of Messiah";
		_description = "As an action. Receive 1 free Ground Force on each your planet";
		_when = acAAA;
		id = "a_RiseOfMessiah";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Rise of Messiah?")){
				for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++)
					if ((*piter)->GetSpecial() != TradeStation)
						FindArmy((*piter)->GetSystem(),player,true,*piter)->AddUnit(GF);
				sprintf(buff,"Player %s has used Rise of Messiah (free GF on each planet)",player->GetName().c_str());
				_Interface.PrintThingAll(buff);
				return er_delete;
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_RiseOfMessiah(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Advanced Reinforcements
class e_a_AdvancedReinforcements:public e_ActionCard{
public:
	e_a_AdvancedReinforcements(){
		_name = "Advanced Reinforcements";
		_description = "As an action. Receive 2 Ground Force or 1 Shock Trooper on one of your planet";
		_when = acAAA;
		id = "a_AdvancedReinforcements";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		vector<int> tempvec;
		Planet* planet = 0;
		if (Q == eq_AAA){
			if (player->GetPlanetsList()->size() == 0){
				_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no planet");
				return er_none;
			}
			if (SelectDialogYesNo("Use Advanced Reinforcements?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to place units",
						"Select system with planet to place units",
						0,player,true,true,false,false,false,false);
					if (planet){
						sprintf(buff,"Select unit to place on %s",planet->GetName().c_str());
						_GrIn.InitChoise(buff,true);
						_GrIn.AddOption(SHIPS_IMG[GF],"2 Ground Forces");
						_GrIn.AddOption(SHIPS_IMG[ST],"1 Shock Trooper");
						tempvec = _GrIn.LaunchChoise();
						if (tempvec.size() == 0)
							continue;
						if (tempvec[0] == 1)
							FindArmy(planet->GetSystem(),player,true,planet)->AddUnit(GF,2);
						if (tempvec[1] == 1)
							FindArmy(planet->GetSystem(),player,true,planet)->AddUnit(ST,1);
						sprintf(buff,"Player %s has used Advanced Reinforcements on planet %s",player->GetName().c_str(),planet->GetName().c_str());
						_Interface.PrintThingAll(buff);
						return er_delete;
					}
					else
						return er_none;
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_AdvancedReinforcements(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Alien Technology
class e_a_AlienTechnology:public e_ActionCard{
public:
	e_a_AlienTechnology(){
		_name = "Alien Technology";
		_description = "As an action. You may buy technology for which you have prereqs with base cost 4 resources";
		_when = acAAA;
		id = "a_AlienTechnology";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		int CCs = 0;
		int cost = 4;
		char buff[255];
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Alien Technology?")){
				sprintf(buff,"Player %s uses Alien Technology",player->GetName().c_str());
				_Interface.PrintThingAll(buff);
				player->ExecuteGameEffect(ExecuteParams(eq_ResearchTech,player,&CCs,&cost));
				if (CCs)
					return er_delete;
				else
					return er_none;
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_AlienTechnology(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Civil Defence
class e_a_CivilDefence:public e_ActionCard{
public:
	e_a_CivilDefence(){
		_name = "Civil Defence";
		_description = "As an action. Place 2 PDS on your planet without PDS";
		_when = acAAA;
		id = "a_CivilDefence";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		Planet* planet = 0;
		if (Q == eq_AAA){
			if (player->GetPlanetsList()->size() == 0){
				_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no planets");
				return er_none;
			}
			if (SelectDialogYesNo("Use Civil Defence?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to place 2 PDS",
						"Select system with planet to place 2 PDS",
						0,player,true,true,false,false,false,false);
					if (planet){
						army = FindArmy(planet->GetSystem(),player,true,planet);
						if (army->StackSize(PDS)){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"This planet already has PDS");
							continue;
						}
						army->AddUnits(PDS,2);
						sprintf(buff,"Player %s uses Civil Defence and places 2 PDS on planet %s",player->GetName().c_str(),planet->GetName().c_str());
						_Interface.PrintThingAll(buff);
						ClearArmies();
						return er_delete;
					}
					else
						return er_none;
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_CivilDefence(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Rally of people
class e_a_RallyOfPeople:public e_ActionCard{
public:
	e_a_RallyOfPeople(){
		_name = "Rally of people";
		_description = "As an action. Place 1 free Dreadnought in your Home System";
		_when = acAAA;
		id = "a_RallyOfPeople";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		Hex* h;
		if (player->eHS != 0)
			h = player->eHS;
		else
			h = player->HS;
		army = FindAnyArmy(h);
		if (Q == eq_AAA){
			if (army != 0){
				if (army->GetOwner() != player){
					_Interface.PrintThingPlayer(player->GetNumber()-1,"Your Home System is under blockade");
					return er_none;
				}
			}
			if (SelectDialogYesNo("Use Rally of people?")){
				sprintf(buff,"Player %s uses Rally of people and receives 1 free Dreadnought in his Home System",player->GetName().c_str());
				_Interface.PrintThingAll(buff);
				army = FindArmy(h,player,true);
				army->AddUnit(DR);
				player->CheckFleets();
				return er_delete;
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_RallyOfPeople(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Unexpected Action
class e_a_UnexpectedAction:public e_ActionCard{
public:
	e_a_UnexpectedAction(){
		_name = "Unexpected Action";
		_description = "As an action. Remove your Command Counter from the galaxy map";
		_when = acAAA;
		id = "a_UnexpectedAction";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Hex* h;
		vector<int> tempvec;
		int CCs = 0;
		if (Q == eq_AAA){
			for (vector<Hex*>::iterator iter = _Map.GetHexList()->begin(); iter != _Map.GetHexList()->end(); iter++)
				if ((*iter)->GotCC(player->GetNumber()))
					CCs++;
			if (CCs == 0){
				_Interface.PrintThingPlayer(player->GetNumber()-1,"You have no counter on the galaxy map");
				return er_none;
			}
			if (SelectDialogYesNo("Use Unexpected Action?")){
				while (true){
					tempvec.clear();
					tempvec = _GrIn.SysChoise("Select system to remove your counter",true);
					if (tempvec.size() == 0)
						return er_none;
					h = _Map.GetHexh(tempvec[0],tempvec[1]);
					if (!h->GotCC(player->GetNumber())){
						_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no your Command Counter in this system");
						continue;
					}
					sprintf(buff,"Remove Command Counter from system %s?",h->GetId().c_str());
					if (SelectDialogYesNo(buff)){
						h->ClearCCs(player->GetNumber());
						sprintf(buff,"Player %s uses Unexpected Action and removes Command Counter from system %s",player->GetName().c_str(),h->GetId().c_str());
						_Interface.PrintThingAll(buff);
						return er_delete;
					}
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_UnexpectedAction(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Uprising
class e_a_Uprising:public e_ActionCard{
public:
	e_a_Uprising(){
		_name = "Uprising";
		_description = "As an action. Exhaust all enemy planets in selected non-Home System";
		_when = acAAA;
		id = "a_Uprising";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		int i;
		Hex* h;
		bool isHS;
		vector<int> tempvec;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Uprising?")){
				while (true){
					tempvec.clear();
					tempvec = _GrIn.SysChoise("Select system to exhaust planets",true);
					if (tempvec.size() == 0)
						return er_none;
					h = _Map.GetHexh(tempvec[0],tempvec[1]);
					isHS = false;
					for (i = 0; i < _GameStats.GetPlayersNumber(); i++)
						if ((h == _Players[i]->HS) || (h == _Players[i]->eHS))
							isHS = true;
					if (isHS){
						_Interface.PrintThingPlayer(player->GetNumber()-1,"Can't use on Home System");
						continue;
					}
					sprintf(buff,"Exhaust all enemy planets in system %s?",h->GetId().c_str());
					if (SelectDialogYesNo(buff)){
						for (i = 1; i <= MAX_PLANETS; i++)
							if (h->GetPlanet(i) != 0)
								if (h->GetPlanet(i)->GetOwner() != player)
									h->GetPlanet(i)->AddState(psExhausted);
						sprintf(buff,"Player %s uses Uprising and exhaust all planets in system %s",player->GetName().c_str(),h->GetId().c_str());
						_Interface.PrintThingAll(buff);
						return er_delete;
					}
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_Uprising(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Equipment Sabotage
class e_a_EquipmentSabotage:public e_ActionCard{
public:
	e_a_EquipmentSabotage(){
		_name = "Equipment Sabotage";
		_description = "As an action. Destroy up to 2 PDS on enemy planet";
		_when = acAAA;
		id = "a_EquipmentSabotage";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		Planet* planet = 0;
		int i, tokill;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Equipment Sabotage?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to destroy PDS",
						"Select system with planet for Equipment Sabotage",
						0,player,true,false,false,true,false,false);
					if (planet){
						army = FindArmy(planet->GetSystem(),planet->GetOwner(),false,planet);
						if ((army == 0) || (army->StackSize(PDS) == 0)){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no enemy PDS on this planet");
							continue;
						}
						tokill = min(2, army->StackSize(PDS));
						sprintf(buff,"Destroy %d PDS on planet %s?",tokill,planet->GetName().c_str());
						if (SelectDialogYesNo(buff)){
							for (i = 1; i <= tokill; i++)
								army->KillUnit(army->GetUnit(PDS));
							sprintf(buff,"Player %s uses Equipment Sabotage and destroy player's %s %d PDS on planet %s",player->GetName().c_str(),planet->GetOwner()->GetName().c_str(),tokill,planet->GetName().c_str());
							_Interface.PrintThingAll(buff);
							return er_delete;
						}
					}
					else
						return er_none;
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_EquipmentSabotage(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Plague
class e_a_Plague:public e_ActionCard{
public:
	e_a_Plague(){
		_name = "Plague";
		_description = "As an action. Select enemy planet. Each enemy Infantry unit has 1/2 chance to be destroyed";
		_when = acAAA;
		id = "a_Plague";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		Planet* planet;
		int i, roll, kill;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Plague?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to use Plague",
						"Select system with enemy planet to use Plague",
						0,player,true,false,false,true,false,false);
					if (planet){
						army = FindArmy(planet->GetSystem(),planet->GetOwner(),false,planet);
						if ((army == 0) || (army->IsUnitWithAbility(uaInfantry) == 0)){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no enemy Infantry on this planet");
							continue;
						}
						sprintf(buff,"Use Plague on planet %s?",planet->GetName().c_str());
						if (SelectDialogYesNo(buff)){
							kill = 0;
							for (i = 1; i <= army->IsUnitWithAbility(uaInfantry); i++){
								roll = rand()%DICE+1;
								if (roll >= 6){
									army->GetUnitWithAbility(uaInfantry,i)->AddAbility(uaKilled);
									kill++;
								}
							}
							while (army->IsUnitWithAbility(uaKilled))
								army->KillUnit(army->GetUnitWithAbility(uaKilled,1));
							sprintf(buff,"Player %s uses Plague and destroyes player's %s %d Infanties on planet %s",player->GetName().c_str(),planet->GetOwner()->GetName().c_str(),kill,planet->GetName().c_str());
							_Interface.PrintThingAll(buff);
							return er_delete;
						}
					}
					else
						return er_none;
					
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_Plague(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Secret Industrial Agent
class e_a_SecretIndustrialAgent:public e_ActionCard{
public:
	e_a_SecretIndustrialAgent(){
		_name = "Secret Industrial Agent";
		_description = "As an action. Destroy enemy Space Dock on enemy planet. Can't use on Home System";
		_when = acAAA;
		id = "a_SecretIndustrialAgent";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		Planet* planet;
		int i;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Secret Industrial Agent?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to destroy enemy Space Dock",
						"Select no Home System to destroy Space Dock",
						0,player,true,false,false,true,true,false);
					if (planet){
						army = FindArmy(planet->GetSystem(),planet->GetOwner(),false,planet);
						if ((army == 0) || (army->StackSize(DCK) == 0)){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no enemy Space Dock");
							continue;
						}
						sprintf(buff,"Use Secret Industrial Agent on planet %s?",planet->GetName().c_str());
						if (SelectDialogYesNo(buff)){
							army->KillUnit(army->GetUnit(DCK));
							sprintf(buff,"Player %s uses Secret Industrial Agent and destroyes player's %s Space Dock on planet %s",player->GetName().c_str(),planet->GetOwner()->GetName().c_str(),planet->GetName().c_str());
							_Interface.PrintThingAll(buff);
							return er_delete;
						}
					}
					else
						return er_none;
					
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_SecretIndustrialAgent(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Space Dock Accident
class e_a_SpaceDockAccident:public e_ActionCard{
public:
	e_a_SpaceDockAccident(){
		_name = "Space Dock Accident";
		_description = "As an action. Select enemy planet with Space Dock in no Home System. Its owner can't produce units in this Dock in this round";
		_when = acAAA;
		id = "a_SecretIndustrialAgent";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Army* army;
		Planet* planet;
		int i;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Space Dock Accident?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to turn off enemy Space Dock",
						"Select no Home System to turn off Space Dock",
						0,player,true,false,false,true,true,false);
					if (planet){
						army = FindArmy(planet->GetSystem(),planet->GetOwner(),false,planet);
						if ((army == 0) || (army->StackSize(DCK) == 0)){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no enemy Space Dock");
							continue;
						}
						sprintf(buff,"Use Space Dock Accident on planet %s?",planet->GetName().c_str());
						if (SelectDialogYesNo(buff)){
							army->GetUnit(DCK)->AssignAbility(uaProduction,FIELD_SKIP,0);
							sprintf(buff,"Player %s uses Space Dock Accident and blocks player's %s Space Dock on planet %s",player->GetName().c_str(),planet->GetOwner()->GetName().c_str(),planet->GetName().c_str());
							_Interface.PrintThingAll(buff);
							return er_delete;
						}
					}
					else
						return er_none;
					
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_SpaceDockAccident(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Voluntary Annexation
class e_a_VoluntaryAnnexation:public e_ActionCard{
public:
	e_a_VoluntaryAnnexation(){
		_name = "Voluntary Annexation";
		_description = "As an action. Select neutral planet in system adjacent to system you control. You capture this planet and place free 3 GF on it";
		_when = acAAA;
		id = "a_VoluntaryAnnexation";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Hex* h;
		Army* army;
		Planet* planet;
		vector<int> tempvec;
		int i;
		bool control;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Voluntary Annexation?")){
				while (true){
					planet = SelectDialogPlanet("Select planet to use Voluntary Annexation",
						"Select system with neutral planet adjacent to system your control",
						0,player,true,false,true,false,true,false);
					if (planet){
						control = false;
						for (i = 0; i < planet->GetSystem()->GetLinkedHexes()->GetLinkNumber(); i++){
							if (planet->GetSystem()->GetLinkedHexes()->GetLink(i) == ltBound){
								if (HexController(planet->GetSystem()->GetLinkedHexes()->GetLinkedHex(i)) == player){
									control = true;
									break;
								}
							}
						}
						if (!control){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"There is no adjacent system you control");
							continue;
						}
						
						sprintf(buff,"Use Voluntary Annexation on planet %s?",planet->GetName().c_str());
						if (SelectDialogYesNo(buff)){
							player->Capture(planet);
							army = NewArmy(player,planet->GetSystem(),planet);
							army->AddUnits(GF,3);
							sprintf(buff,"Player %s uses Voluntary Annexation on planet %s",player->GetName().c_str(),planet->GetName().c_str());
							_Interface.PrintThingAll(buff);
							return er_delete;
						}
					}
					else
						return er_none;
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_VoluntaryAnnexation(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};

//Privateers
class e_a_Privateers:public e_ActionCard{
public:
	e_a_Privateers(){
		_name = "Privateers";
		_description = "As an action. Select player, take all his Trade Goods than discard half of taken goods (round up)";
		_when = acAAA;
		id = "a_Privateers";
		image = ACTION_CARD;
	}
	bool GetQ(GameEffectQs queue){
		return ((queue == eq_AAA) || (queue == eq_ActionCard));
	}
	GameEffectRets Execute(ExecuteParams EP){
		GameEffectQs Q = EP.queue;
		Player* player = EP.player;
		char buff[255];
		Player* target;
		vector<int> tempvec;
		int i,goods;
		bool control;
		if (Q == eq_AAA){
			if (SelectDialogYesNo("Use Privateers?")){
				while (true){
					target = SelectDialogPlayer("Select player to steal Trade Goods",player);
					if (target){
						if (target->GetGoods() == 0){
							_Interface.PrintThingPlayer(player->GetNumber()-1,"This player has no Goods");
							continue;
						}
						sprintf(buff,"Steal Goods from player %s?",target->GetName().c_str());
						if (SelectDialogYesNo(buff)){
							goods = target->GetGoods();
							target->TakeGoods(goods);
							player->GiveGoods(goods/2);
							sprintf(buff,"Player %s uses Privateers and steals Trage Goods from player %s",player->GetName().c_str(),target->GetName().c_str());
							_Interface.PrintThingAll(buff);
							sprintf(buff,"You receive %d Trade Good(s) from Privateers",goods/2);
							_Interface.PrintThingAll(buff);
							return er_delete;
						}
						else
							continue;
					}
					else
						return er_none;
				}
			}
			else
				return er_none;
		}
		return er_normal;
	}
	GameEffect* Clone(){
		return new e_a_Privateers(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};