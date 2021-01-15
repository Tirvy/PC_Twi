e_Tech::e_Tech(){
	//sprintf(name,"No description");
	name="No description";
	//sprintf(description,"No description");
	description="No description";
	cost = 0;
	color = tt_MAX;
	race = MAX_RACE;
	TT = MAX_TECH;
	prereq1 = MAX_TECH;
	prereq2 = MAX_TECH;
	isboth = false;
}

string e_Tech::GetName(){
	return name;
}

string e_Tech::GetDescription(){
	return description;
}

int e_Tech::GetCost(){
	return cost;
}

TechTree e_Tech::GetColor(){
	return color;
}

RacesType e_Tech::GetRace(){
	return race;
}

TechType e_Tech::GetTechType(){
	return TT;
}

bool e_Tech::HavePrereqs(Player *player){
	if ((prereq1 == MAX_TECH)&&(prereq2 == MAX_TECH))
		return true;
	if ((prereq1 != MAX_TECH)&&(prereq2 == MAX_TECH)&&(player->GotTech(prereq1)))
		return true;
	if ((prereq1 != MAX_TECH)&&(prereq2 != MAX_TECH))
		if (isboth){
			if ((player->GotTech(prereq1))&&(player->GotTech(prereq2)))
				return true;
		}
		else
			if ((player->GotTech(prereq1))||(player->GotTech(prereq2)))
				return true;
	return false;
}

GameEffectRets e_Tech::Execute(ExecuteParams EP){
	_Interface.PrintThingAll("e_Tech::Execute");
	return er_none;
}

/*e_Tech* e_Tech::Clone(){
	return new e_Tech(*this);
}*/

bool e_Tech::GetQ(GameEffectQs queue){
	return false;
}

#include "GameEffects\\techs\\BlueTechEffect.cpp"
#include "GameEffects\\techs\\GreenTechEffect.cpp"
#include "GameEffects\\techs\\RedTechEffect.cpp"
#include "GameEffects\\techs\\YellowTechEffect.cpp"
#include "GameEffects\\TechGameEffect.cpp"