

class Event{
protected:
	stringid;
	stringimage;
public:
	Event();
	string GetId();
	string GetImg();
	virtual bool GetQ(EventQs queue) = 0;
	virtual EventRets Execute(ExecuteParams EP)=0;
};
Event::Event(){
	id = 0;
}
string Event::GetId(){
	return id;
}
string Event::GetImg(){
	return image;
}

#include "Politic_Card.h"
#include "Strategy_Card.h"
#include "Objective_Card.h"
#include "Action_Card.h"