string e_ActionCard::GetName(){
	return _name;
}

string e_ActionCard::GetDescription(){
	return _description;
}

playedPhase e_ActionCard::GetPhase(){
	return _when;
}

#include "actioncards\\a_TestActionCard.cpp"
#include "actioncards\\a_AsAnAction.cpp"
#include "actioncards\\a_BeforeBattleRound.cpp"
#include "actioncards\\a_StrategyPhase.cpp"

vector<e_ActionCard*> FormActionCardDeck(){
	int i;
	vector<e_ActionCard*> deck;
	deck.clear();
	for (i = 1; i <= 19; i++)
		deck.push_back(new e_a_TestActionCard());
	/////////////////////////////////////////////////////
	for (i = 1; i <= 4; i++)
		deck.push_back(new e_a_Recheck());
	for (i = 1; i <= 2; i++)
		deck.push_back(new e_a_AdvancedReinforcements());
	deck.push_back(new e_a_AlienTechnology());
	for (i = 1; i <= 2; i++)
		deck.push_back(new e_a_BeaconOfHope());
	deck.push_back(new e_a_CivilDefence());
	deck.push_back(new e_a_CommandSammit());
	for (i = 1; i <= 2; i++)
		deck.push_back(new e_a_EquipmentSabotage());
	deck.push_back(new e_a_FighterPrototype());
	deck.push_back(new e_a_GeomagneticMines());
	deck.push_back(new e_a_GoodYear());
	deck.push_back(new e_a_IntoTheBreach());
	for (i = 1; i <= 4; i++)
		deck.push_back(new e_a_LocalUnrest());
	for (i = 1; i <= 5; i++)
		deck.push_back(new e_a_MoraleBoost());
	deck.push_back(new e_a_Overrun());
	deck.push_back(new e_a_Plague());
	deck.push_back(new e_a_Privateers());
	deck.push_back(new e_a_RallyOfPeople());
	deck.push_back(new e_a_RiseOfMessiah());
	deck.push_back(new e_a_SecretIndustrialAgent());
	for (i = 1; i <= 4; i++)
		deck.push_back(new e_a_SignalJamming());
	deck.push_back(new e_a_SpaceDockAccident());
	deck.push_back(new e_a_TradeStop());
	deck.push_back(new e_a_UnexpectedAction());
	deck.push_back(new e_a_Uprising());
	deck.push_back(new e_a_VoluntaryAnnexation());
	sync_shuffle(deck);
	return deck;
}