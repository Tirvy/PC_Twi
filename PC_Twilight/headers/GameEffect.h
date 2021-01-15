

class GameEffect{
protected:
	//stringid;
	string id;
	string image;
public:
	GameEffect();
	//string GetId();
	string GetId();
	string GetImg();
	virtual bool GetQ(GameEffectQs queue) = 0;
	virtual GameEffectRets Execute(ExecuteParams EP)=0;
	virtual GameEffect * Clone() = 0;
	virtual string Save() = 0;
	virtual void Load(string str) = 0;
};
GameEffect::GameEffect(){
	id = "";
	image = EMPTY_EVENT_IMG;
}
string GameEffect::GetId(){//string
	return id;
}
string GameEffect::GetImg(){
	return image;
}


#include "Politic_Card.h"
#include "Strategy_Card.h"
#include "Objective_Card.h"
#include "RaceEffects.h"
#include "TechEffects.h"
#include "Action_Card.h"