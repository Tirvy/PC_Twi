#include "Tactical.cpp"

#include "InitialStats.cpp"

#include "events\\TechEvent.cpp"

#include "events\\r_0.cpp"

#include "events\\s_0.cpp"

#include "events\\o_0.cpp"

#include "events\\p_0.cpp"

class EmptyEvent:public Event{
public:
	bool GetQ(EventQs queue){
		if (queue==eq_None)
			return true;
		return false;
	}
	EventRets Execute(ExecuteParams){
		return er_normal;
	}
};