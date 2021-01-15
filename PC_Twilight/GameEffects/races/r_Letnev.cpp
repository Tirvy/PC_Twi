e_LetnevNoneuclidianShields::e_LetnevNoneuclidianShields(){
	id = "NoneuclidianShielding";
	name = "Noneuclidian Shielding";
	description = "When you use the sustain damage ability of one of your units, it prevents two casualties";
	cost = 4;
	color = RaceTech;
	race = Letnev;
	TT = ttNoneuclidianShielding;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_LetnevNoneuclidianShields::GetQ(GameEffectQs queue){
	if ((queue==eq_Battle)||(queue==eq_AfterBattle))
		return true;
	return false;
}
GameEffectRets e_LetnevNoneuclidianShields::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	GameEffectQs Q = EP.queue;
	if (Q==eq_Battle)
		army->AssignUnitAbility(uaSustain,FIELD_SKIP,2);
	if (Q==eq_AfterBattle)
		army->AssignUnitAbility(uaSustain,FIELD_SKIP,1);
	return er_none;
}
GameEffect* e_LetnevNoneuclidianShields::Clone(){
	return new e_LetnevNoneuclidianShields(*this);
}
string e_LetnevNoneuclidianShields::Save(){
	return string();
}
void e_LetnevNoneuclidianShields::Load(std::string str){}
////////////////////////////////////////////////////
e_LetnevL4Disruptors::e_LetnevL4Disruptors(){
	id = "L4Disruptors";
	name = "L4 Disruptors";
	description = "You donТt need to spend TG to use your racial ability in ground combat";
	cost = 6;
	color = RaceTech;
	race = Letnev;
	TT = ttL4Disruptors;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_LetnevL4Disruptors::GetQ(GameEffectQs queue){
	return false;
}
GameEffectRets e_LetnevL4Disruptors::Execute(ExecuteParams EP){
	return er_none;
}
GameEffect* e_LetnevL4Disruptors::Clone(){
	return new e_LetnevL4Disruptors(*this);
}
string e_LetnevL4Disruptors::Save(){
	return string();
}
void e_LetnevL4Disruptors::Load(std::string str){}
////////////////////////////////////////////////////
e_LetnevBattleAbility::e_LetnevBattleAbility(){
	id = "LetnevBattleAbility";
	image = EMPTY_EVENT_IMG;
	isActive = false;
}
bool e_LetnevBattleAbility::GetQ(GameEffectQs queue){
	//if (queue==eq_BeforeBattleRound)
	if ((queue == eq_BeforeBattleRoundAction) && !isActive)
		return true;
	if (queue == eq_BeforeBattleRound)
		return true;
	return false;
}
GameEffectRets e_LetnevBattleAbility::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Army* army = EP.army1;
	int round = EP.fround;
	char str[127];
	int price;
	bool agree;
	if (Q == eq_BeforeBattleRoundAction){
		if ((round==0)||(army==0)||(army->isDefeated()))
			return er_none;
		if (army->GetOwner()->GotTech(ttL4Disruptors)&&army->GetPlanet()!=0)
			price=0;
		else
			price=2;
		if ((army->GetPlanet()==0)&&(army->GetOwner()->GetGoods()>=price)){
			if (SelectDialogYesNo("Spend 2 trade goods to receive +1 to all combat rolls for this round?")){
				sprintf(str,"Player %s uses Letnev ability",army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(str);
				army->GetOwner()->TakeGoods(2);
				army->ModUnitAbility(uaSpaceBattle,-1);
				isActive = true;
			}
		}
		if ((army->GetPlanet()!=0)&&(army->GetOwner()->GetGoods()>=price)){
			if (price>0)
				agree=SelectDialogYesNo("Spend 2 trade goods to receive +2 to all combat rolls for this round?");
			else
				agree=true;
			if (agree){
				sprintf(str,"Player %s use Letnev ability",army->GetOwner()->GetName().c_str());
				_Interface.PrintThingAll(str);
				army->GetOwner()->TakeGoods(price);
				army->ModUnitAbility(uaLandBattle,-2);
				isActive = true;
			}
		}
	}
	if (Q == eq_BeforeBattleRound)
		isActive = false;
	return er_none;
}
GameEffect* e_LetnevBattleAbility::Clone(){
	return new e_LetnevBattleAbility(*this);
}
string e_LetnevBattleAbility::Save(){
	return string();
}
void e_LetnevBattleAbility::Load(std::string str){
	isActive = false;
}
////////////////////////////////////////////////////
e_LetnevFleetSupply::e_LetnevFleetSupply(){
	id = "LetnevFleetSupply";
}
bool e_LetnevFleetSupply::GetQ(GameEffectQs queue){
	if (queue==eq_FleetSupply)
		return true;
	return false;
}
GameEffectRets e_LetnevFleetSupply::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	int* supply = EP.FleetSupply;
	*supply = *supply - 1;
	return er_none;
}
GameEffect* e_LetnevFleetSupply::Clone(){
	return new e_LetnevFleetSupply(*this);
}
string e_LetnevFleetSupply::Save(){
	return string();
}
void e_LetnevFleetSupply::Load(std::string str){}
////////////////////////////////////////////////////
class e_LetnevStartUnits:public GameEffect{
public:
	bool GetQ(GameEffectQs queue){
		if (queue==eq_Pregame)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* curPlayer = EP.player;
		spawnarmy* units;
		// торговые договоры
		EP.player->AddTrade(1);
		EP.player->AddTrade(1);
		EP.player->GiveGoods(10);
		//стартовые техи
		curPlayer->GiveTech(ttHylar);
		curPlayer->GiveTech(ttAntimass);
		//стартовые ивенты
		curPlayer->AddGameEffect(new e_HylarVAssualtLaser);
		curPlayer->AddGameEffect(new e_Antimass);
		curPlayer->AddGameEffect(new e_LetnevBattleAbility);
		curPlayer->AddGameEffect(new e_LetnevFleetSupply);
		//каунтеры
		curPlayer->AddCC(2,3,3);
		//юниты
		units = new spawnarmy;
		units->unit[GF] = 3;
		units->unit[DR] = 1;
		units->unit[CR] = 1;
		units->unit[DS] = 1;
		units->unit[DCK] = 1;
		Spawn(units,curPlayer,curPlayer->GetHS());
		return er_delete;
	}
	GameEffect * Clone(){
		return new e_LetnevStartUnits(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

