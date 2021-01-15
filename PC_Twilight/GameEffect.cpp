#include "Tactical.cpp"
#include "Transfer.cpp"
#include "SendGoods.cpp"

#include "InitialStats.cpp"





#include "GameEffects\\BattleGameEffect.cpp"

#include "GameEffects\\CommonGameEffect.cpp"

#include "GameEffects\\r_0.cpp"

#include "GameEffects\\s_0.cpp"

#include "GameEffects\\o_0.cpp"

#include "GameEffects\\p_0.cpp"

#include "GameEffects\\t_0.cpp"

#include "GameEffects\\a_0.cpp"

#include "GameEffects\\RefreshGameEffect.cpp"

class EmptyGameEffect:public GameEffect{
public:
	bool GetQ(GameEffectQs queue){
		if (queue==eq_None)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams){
		return er_normal;
	}
	GameEffect * Clone(){
		return 0;
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};