//зеленые технологии
//cybernetics
e_Cybernetics::e_Cybernetics(){
	id = "Cybernetics";
	name = "Cybernetics";
	description = "Fighters receive +1 on all combat rolls";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttCybernetics;
	prereq1 = ttAntimass;
	prereq2 = ttStasis;
	isboth = false;
}
bool e_Cybernetics::GetQ(GameEffectQs queue){
	if (queue==eq_Battle)
		return true;
	return false;
}
GameEffectRets e_Cybernetics::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	for (int i=1; i<=army->IsUnitWithAbility(uaFighter); i++)
		army->GetUnitWithAbility(uaFighter,i)->ModAbility(uaSpaceBattle,-1);
	return er_none;
}
GameEffect* e_Cybernetics::Clone(){
	return new e_Cybernetics(*this);
}
string e_Cybernetics::Save(){
	return string();
}
void e_Cybernetics::Load(std::string str){}
//X-89
e_X89::e_X89(){
	id = "X89";
	name = "X-89 Bacterial Weapon";
	description = "Dreadnoughts and War Suns may destroy all enemy GF on planet, then discard all your Action Cards";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttX89;
	prereq1 = ttAssaultCannon;
	prereq2 = ttTransitDiodes;
	isboth = false;
}
bool e_X89::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeBombardment)
		return true;
	return false;
}
GameEffectRets e_X89::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* target = EP.army2;
	int attack = EP.attacker;
	Unit* unit;
	if ((attack==1)&&(army->IsUnitWithAbility(uaHeavyShip))&&(target->IsUnitWithAbility(uaInfantry))){
		if (SelectDialogYesNo("Use X-89 Bacterial Weapon? You will lose all Action Cards")){
			for (int i=1; i<=target->IsUnitWithAbility(uaInfantry);i++)
				target->GetUnitWithAbility(uaInfantry,i)->AddAbility(uaKilled);
			CombatInterface().DestroyUnit(target,target->GetUnitWithAbility(uaKilled,1));
			army->GetOwner()->DiscardActions();//потеря экшон-карт
		}
	}
	return er_none;
}
GameEffect* e_X89::Clone(){
	return new e_X89(*this);
}
string e_X89::Save(){
	return string();
}
void e_X89::Load(std::string str){}
//gen synth
e_GenSynthesis::e_GenSynthesis(){
	id = "GenSynthesis";
	name = "Gen Synthesis";
	description = "GF receive +1 on all combat rolls; when destroyed, roll 5+ to return to Home System";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttGenSynthesis;
	prereq1 = ttCybernetics;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_GenSynthesis::GetQ(GameEffectQs queue){
	if ((queue==eq_Battle)||(queue==eq_AfterAssignDamage))
		return true;
	return false;
}
GameEffectRets e_GenSynthesis::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	GameEffectQs Q = EP.queue;
	int attacker = EP.attacker;
	int check = 0;
	bool IsInHome = false;
	int k=0;
	int planet=0;
	char str[127];
	bool mask[MAX_PLANETS];
	int howmanyplanets=0;
	Planet* returnPlanet;
	Army* returnArmy=0;
	Unit* unit = EP.unit;
	if (Q == eq_Battle)//+1 к пехоте
		for (int i=1; i<=army->IsUnitWithAbility(uaInfantry); i++)
			army->GetUnitWithAbility(uaInfantry,i)->ModAbility(uaLandBattle,-1);
	if (Q == eq_AfterAssignDamage){//воскрешение
		if ((attacker==0)&&(unit->HasAbility(uaInfantry))&&(unit->HasAbility(uaKilled))){
			check = rand()%DICE+1;
			if (check>=5){
				for (int i=0; i<MAX_PLANETS; i++){
					if ((army->GetOwner()->GetHS()->GetPlanet(i+1)!=0)&&(army->GetOwner()->GetHS()->GetPlanet(i+1)->GetOwner()==army->GetOwner())){
						mask[i]=true;
						howmanyplanets++;
						returnPlanet = army->GetOwner()->GetHS()->GetPlanet(i+1);
					}
					else
						mask[i]=false;
				}
				if (howmanyplanets>0){//ищем планету для возврата
					if (army->GetHex()==army->GetOwner()->GetHS()){
						returnArmy=army;
					}
					else{
						if (howmanyplanets>1){
							planet = SelectDialogPlanetInSystem("Select planet to return infantry",army->GetOwner()->GetHS(),army->GetOwner(),mask,MAX_PLANETS);
							if (planet!=0)
								returnPlanet=army->GetOwner()->GetHS()->GetPlanet(planet);
						}
						returnArmy = FindAllyArmy(army->GetOwner(),army->GetOwner()->GetHS(),returnPlanet);
						if (returnArmy==0)
							returnArmy = NewArmy(army->GetOwner(),army->GetOwner()->GetHS(),returnPlanet);
					}
					returnArmy->AddUnit(unit->Class);
					sprintf(str,"Player's %s GF returns to %s by Gen Synthesis",army->GetOwner()->GetName(),returnArmy->GetPlanet()->GetName());
					_Interface.PrintThingAll(str);
				}
			}
		}
	}
	return er_none;
}
GameEffect* e_GenSynthesis::Clone(){
	return new e_GenSynthesis(*this);
}
string e_GenSynthesis::Save(){
	return string();
}
void e_GenSynthesis::Load(std::string str){}
//stasis
e_StasisCapsules::e_StasisCapsules(){
	id = "Stasis";
	name = "Stasis Capsules";
	description = "Cruisers and Dreadnoughts may carry 1 GF unit";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttStasis;
	prereq1 = ttEnviroCompensator;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_StasisCapsules::GetQ(GameEffectQs queue){
	if (queue == eq_AfterRefreshAbilities)
		return true;
	return false;
}
GameEffectRets e_StasisCapsules::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	Army* army = EP.army1;
	Unit* unit = EP.unit;
	if (Q == eq_AfterRefreshAbilities)
		if ((unit->Class == CS) || (unit->Class == DR))
			if (unit->HasAbility(uaCarrier))
				unit->ModAbility(uaCarrier,FIELD_SKIP,FIELD_SKIP,1);
			else
				unit->AddAbility(uaCarrier,0,0,1);
	return er_none;
}
GameEffect* e_StasisCapsules::Clone(){
	return new e_StasisCapsules(*this);
}
string e_StasisCapsules::Save(){
	return string();
}
void e_StasisCapsules::Load(std::string str){}
//dacxive
e_DacxiveAnimators::e_DacxiveAnimators(){
	id = "Dacxive";
	name = "Dacxive Animators";
	description = "If you win an Invasion Combat, roll for every GF unit killed (yours and opponent's) and revive them on 6+";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttDacxiveAnimators;
	prereq1 = ttNeuralMotivator;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_DacxiveAnimators::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeBattle)||(queue==eq_AfterBattle))
		return true;
	return false;
}
GameEffectRets e_DacxiveAnimators::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* target = EP.army2;
	GameEffectQs Q = EP.queue;
	char str[127];
	int toRevive=0;
	if (army->GetPlanet()!=0){
		if (Q == eq_BeforeBattle){
			GFs1=target->IsUnitWithAbility(uaInfantry);
			for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
				if ((*aiter)->GetOwner()==army->GetOwner())
					GFs1+=(*aiter)->IsUnitWithAbility(uaInfantry);
			GFs2=0;
		}
		if (Q == eq_AfterBattle){
			if (!army->isDefeated()&&target->isDefeated()){
				GFs2=0;
				for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++)
					if ((*aiter)->GetOwner()==army->GetOwner())
						GFs2+=(*aiter)->IsUnitWithAbility(uaInfantry);
				for (int i=0; i<GFs1-GFs2; i++)
					if (rand()%DICE+1>=DA_REVIVE_ROLL)
						toRevive++;
				army->AddUnits(GF,toRevive);
				sprintf(str,"Dacxive animators revive %d GF",toRevive);
				_Interface.PrintThingAll(str);
			}
		}
	}
	return er_none;
}
GameEffect* e_DacxiveAnimators::Clone(){
	return new e_DacxiveAnimators(*this);
}
string e_DacxiveAnimators::Save(){
	return string();
}
void e_DacxiveAnimators::Load(std::string str){}
//neural comp
e_NeuralComputing::e_NeuralComputing(){
	id = "NeuralComputing";
	name = "Neural Computing";
	description = "Your cost to purchase new Technologies is reduced by 2";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttNeuralComputing;
	prereq1 = ttNeuralMotivator;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_NeuralComputing::GetQ(GameEffectQs queue){
	if (queue==eq_TechnologyBuy)
		return true;
	return false;
}
GameEffectRets e_NeuralComputing::Execute(ExecuteParams EP){
	Player* player = EP.player;
	int* bonus = EP.TechCostBonus;
	*bonus = *bonus - 2;
	return er_none;
}
GameEffect* e_NeuralComputing::Clone(){
	return new e_NeuralComputing(*this);
}
string e_NeuralComputing::Save(){
	return string();
}
void e_NeuralComputing::Load(std::string str){}
//neural motiv
e_NeuralMotivator::e_NeuralMotivator(){
	id = "NeuralMotivator";
	name = "Neural Motivator";
	description = "Draw 1 extra Action Card during each Status Phase";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttNeuralMotivator;
	prereq1 = ttStasis;
	prereq2 = ttMicroTechnology;
	isboth = false;
}
bool e_NeuralMotivator::GetQ(GameEffectQs queue){
	if (queue==eq_StatusPhase)
		return true;
	return false;
}
GameEffectRets e_NeuralMotivator::Execute(ExecuteParams EP){
	int* ACs = EP.ActionCards;
	*ACs = *ACs + 1;
	return er_none;
}
GameEffect* e_NeuralMotivator::Clone(){
	return new e_NeuralMotivator(*this);
}
string e_NeuralMotivator::Save(){
	return string();
}
void e_NeuralMotivator::Load(std::string str){}
//hyper metabolism
e_HyperMetabolism::e_HyperMetabolism(){
	id = "HyperMetabolism";
	name = "Hyper Metabolism";
	description = "During Status Phase gain 1 extra Command Counter. Before drawing Action Cards you may discard one to draw 1 additional Action Card";
	cost = 0;
	color = Green;
	race = MAX_RACE;
	TT = ttHyperMetabolism;
	prereq1 = ttGenSynthesis;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_HyperMetabolism::GetQ(GameEffectQs queue){
	if (queue==eq_StatusPhase)
		return true;
	return false;
}
GameEffectRets e_HyperMetabolism::Execute(ExecuteParams EP){
	int* CCs = EP.CommandCounters;
	*CCs = *CCs + 1;
	return er_none;
}
GameEffect* e_HyperMetabolism::Clone(){
	return new e_HyperMetabolism(*this);
}
string e_HyperMetabolism::Save(){
	return string();
}
void e_HyperMetabolism::Load(std::string str){}