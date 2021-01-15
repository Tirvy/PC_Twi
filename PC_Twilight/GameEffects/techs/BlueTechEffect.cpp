//синие технологии
//XRD
e_XRDtransporters::e_XRDtransporters(){
	id = "XRD";
	name = "XRD Transporters";
	description = "Carriers receive +1 movement";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttXRD;
	prereq1 = ttAntimass;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_XRDtransporters::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeMovement)
		return true;
	return false;
}
GameEffectRets e_XRDtransporters::Execute(ExecuteParams EP){
	Player* player = EP.player;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetOwner()==player)
			for (int i=1; i<=(*aiter)->StackSize(CR);i++)
				(*aiter)->GetUnit(CR,i)->ModAbility(uaHyperDrive,+1);
	}
	return er_none;
}
GameEffect* e_XRDtransporters::Clone(){
	return new e_XRDtransporters(*this);
}
string e_XRDtransporters::Save(){
	return string();
}
void e_XRDtransporters::Load(std::string str){}
//Type IV
e_TypeIVDrive::e_TypeIVDrive(){
	id = "TypeIVDrive";
	name = "Type IV Drive";
	description = "Cruisers and Dreadnoughts receive +1 movement";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttTypeIVDrive;
	prereq1 = ttXRD;
	prereq2 = ttNeuralMotivator;
	isboth = true;
}
bool e_TypeIVDrive::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeMovement)
		return true;
	return false;
}
GameEffectRets e_TypeIVDrive::Execute(ExecuteParams EP){
	Player* player = EP.player;
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		if ((*aiter)->GetOwner()==player){
			for (int i=1; i<=(*aiter)->StackSize(CS);i++)
				(*aiter)->GetUnit(CS,i)->ModAbility(uaHyperDrive,+1);
			for (int i=1; i<=(*aiter)->StackSize(DR);i++)
				(*aiter)->GetUnit(DR,i)->ModAbility(uaHyperDrive,+1);
		}
	}
	return er_none;
}
GameEffect* e_TypeIVDrive::Clone(){
	return new e_TypeIVDrive(*this);
}
string e_TypeIVDrive::Save(){
	return string();
}
void e_TypeIVDrive::Load(std::string str){}
//Adv fighters
e_AdvancedFighters::e_AdvancedFighters(){
	id = "AdvFighter";
	name = "Advanced Fighters";
	description = "Fighters don't need carriers. Their movement is 2, Combat rolls +1, and they block enemy ships. Excess fighters count towards Fleet Supply";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttAdvancedFighters;
	prereq1 = ttTypeIVDrive;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_AdvancedFighters::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeMovement)||(queue==eq_Battle)||(queue==eq_FleetSupply))
		return true;
	return false;
}
GameEffectRets e_AdvancedFighters::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	int* supply = EP.FleetSupply;
	int i,FGcap,fighters;
	if (Q == eq_Battle)
		for (i = 1; i <= army->IsUnitWithAbility(uaFighter); i++)
			army->GetUnitWithAbility(uaFighter,i)->ModAbility(uaSpaceBattle,-1);
	if (Q == eq_BeforeMovement){
		for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
			if (((*aiter)->GetOwner() == player) && ((*aiter)->GetPlanet() == 0)){
				for (i = 1; i <= (*aiter)->IsUnitWithAbility(uaFighter); i++){
					(*aiter)->GetUnitWithAbility(uaFighter,i)->AddAbility(uaHyperDrive,2);
					(*aiter)->GetUnitWithAbility(uaFighter,i)->AddAbility(uaSupply);
				}
			}
		}
	}
	if (Q == eq_FleetSupply){
		FGcap = army->FighterCapacity();
		fighters = 0;
		for (vector<Unit*>::iterator iter = army->GetUnits()->begin(); iter != army->GetUnits()->end(); iter++)
			if (((*iter)->HasAbility(uaFighter))&&(!(*iter)->HasAbility(uaKilled)))
				fighters++;
		if (fighters > FGcap)
			*supply += (fighters - FGcap);
	}
	return er_none;
}
GameEffect* e_AdvancedFighters::Clone(){
	return new e_AdvancedFighters(*this);
}
string e_AdvancedFighters::Save(){
	return string();
}
void e_AdvancedFighters::Load(std::string str){}
//Maneuvr jets
e_ManeuveringJets::e_ManeuveringJets(){
	id = "ManeuveringJets";
	name = "Maneuvering Jets";
	description = "Opponent receive -1 on all PDS rolls, -2 from adjacent systems. You receive -1 to Space Mines rolls. Ships don't have to stop in Ion Storms";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttManeuveringJets;
	prereq1 = ttXRD;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_ManeuveringJets::GetQ(GameEffectQs queue){
	if ((queue==eq_BeforeMovement)||(queue==eq_Battle))
		return true;
	return false;
}
GameEffectRets e_ManeuveringJets::Execute(ExecuteParams EP){
	Army* army = EP.army1;
	Army* target = EP.army2;
	int attacker = EP.attacker;
	int mod = 0;
	int dist = 0;
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if ((Q == eq_Battle)&&(attacker==0)){
		dist=isAdjacent(army->GetHex(),target->GetHex());
		if (dist==0)
			mod=1;
		if (dist==1)
			mod=2;
		army->ModUnitAbility(uaCannon,mod);
	}
	if (Q == eq_BeforeMovement){
		player->GetMoveStats()->pass[IonStorm] = 1;
	}
	return er_none;
}
GameEffect* e_ManeuveringJets::Clone(){
	return new e_ManeuveringJets(*this);
}
string e_ManeuveringJets::Save(){
	return string();
}
void e_ManeuveringJets::Load(std::string str){}
//antimass
e_Antimass::e_Antimass(){
	id = "Antimass";
	name = "Antimass Deflectors";
	description = "All ships may move through Asteroid Fields, but not stop in one";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttAntimass;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_Antimass::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeMovement)
		return true;
	return false;
}
GameEffectRets e_Antimass::Execute(ExecuteParams EP){
	Player* player = EP.player;
	player->GetMoveStats()->pass[Asteroids] = 1;
	return er_none;
}
GameEffect* e_Antimass::Clone(){
	return new e_Antimass(*this);
}
string e_Antimass::Save(){
	return string();
}
void e_Antimass::Load(std::string str){}
//gravity drive
e_GravityDrive::e_GravityDrive(){
	id = "GravityDrive";
	name = "Gravity Drive";
	description = "No roll for ships moving out of Gravity Rift. Ship movement +1 when starting from a system adjacent to Gravity Rift or Wormhole";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttGravityDrive;
	prereq1 = ttAntimass;
	prereq2 = MAX_TECH;
	isboth = false;
}
bool e_GravityDrive::GetQ(GameEffectQs queue){
	if (queue==eq_BeforeMovement)
		return true;
	return false;
}
GameEffectRets e_GravityDrive::Execute(ExecuteParams EP){
	Player* player = EP.player;
	vector<Hex*>* hexes = _Map.GetHexList();
	int i;
	bool boost = false;
	player->GetMoveStats()->pass[GravityRift] = 1;
	player->GetMoveStats()->moveout[GravityRift] = MO_none;
	int actportals[wh_MAX];
	actportals[wh_NONE] = 0;
	for (WormholeType WH = wh_A; WH < wh_MAX; WH = (WormholeType)((int)WH + 1)){
		actportals[WH] = 0;
		for (vector<Hex*>::iterator iter = hexes->begin(); iter != hexes->end(); iter++)
			if ((*iter)->GotPortal(WH))
				actportals[WH] += 1;
	}
	for (vector<Army*>::iterator aiter = _Armies.begin(); aiter != _Armies.end(); aiter++){
		boost = false;
		if (((*aiter)->GetOwner() == player) && ((*aiter)->GetPlanet() == 0)){
			for (i = 0; i < (*aiter)->GetHex()->GetLinkedHexes()->GetLinkNumber(); i++){
				if ((*aiter)->GetHex()->GetLinkedHexes()->GetLinkedHex(i)->GetDanger() == GravityRift)
					boost = true;
				for (WormholeType WH = wh_A; WH < wh_MAX; WH = (WormholeType)((int)WH + 1))
					if (((*aiter)->GetHex()->GetLinkedHexes()->GetLinkedHex(i)->GotPortal(WH)) && (actportals[WH]>1))
						boost = true;
			}
			if (boost)
				for (i = 1; i <= (*aiter)->IsUnitWithAbility(uaHyperDrive); i++)
					(*aiter)->GetUnitWithAbility(uaHyperDrive,i)->ModAbility(uaHyperDrive,+1);
		}
	}
	return er_none;
}
GameEffect* e_GravityDrive::Clone(){
	return new e_GravityDrive(*this);
}
string e_GravityDrive::Save(){
	return string();
}
void e_GravityDrive::Load(std::string str){}
//light wave deflectors
e_LightWaveDeflector::e_LightWaveDeflector(){
	id = "LightWaveDeflector";
	name = "Light/Wave Deflector";
	description = "Your ships may move through enemy fleets and continue to the activated system";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttLightWaveDeflector;
	prereq1 = ttXRD;
	prereq2 = ttMagenDefenseGrid;
	isboth = true;
}
bool e_LightWaveDeflector::GetQ(GameEffectQs queue){
	//if ((queue==eq_BeforeMovement)||(queue==eq_Battle))
	//	return true;
	return false;
}
GameEffectRets e_LightWaveDeflector::Execute(ExecuteParams EP){
	return er_none;
}
GameEffect* e_LightWaveDeflector::Clone(){
	return new e_LightWaveDeflector(*this);
}
string e_LightWaveDeflector::Save(){
	return string();
}
void e_LightWaveDeflector::Load(std::string str){}
//Fleet logistics
e_FleetLogistics::e_FleetLogistics(){
	id = "FleetLogistics";
	name = "Fleet Logistics";
	description = "When taking a Tactical Action, you may take 2 Tactical Actions, one after the other, before your turn ends";
	cost = 0;
	color = Blue;
	race = MAX_RACE;
	TT = ttFleetLogistics;
	prereq1 = ttGravityNegator;
	prereq2 = MAX_TECH;
	isboth = false;
	use = 2;
}
bool e_FleetLogistics::GetQ(GameEffectQs queue){
	return ((queue == eq_ActionStart) || (queue == eq_AfterTactical));
}
GameEffectRets e_FleetLogistics::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	Player* player = EP.player;
	if (Q == eq_ActionStart)
		use = 2;
	if (Q == eq_AfterTactical){
		use--;
		if ((use > 0) && SelectDialogYesNo("Do another Tactical Action? (Fleet Logistics)"))
			e_TacticalAction().Execute(ExecuteParams(eq_AAA,player));
	}
	return er_none;
}
GameEffect* e_FleetLogistics::Clone(){
	return new e_FleetLogistics(*this);
}
string e_FleetLogistics::Save(){
	return string();
}
void e_FleetLogistics::Load(std::string str){}