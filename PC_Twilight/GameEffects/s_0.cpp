
void e_StratCard::AddBonus(){
	++bonus;
}
StratsType e_StratCard::GetType(){
	return type;
}
int e_StratCard::GetBonus(){
	return bonus;
}
void e_StratCard::NullBonus(){
	bonus = 0;
}
void e_StratCard::SetBonus(int n){
	bonus = n;
}
GameEffectRets e_StratCard::Execute(ExecuteParams EP){
	GameEffectQs Q = EP.queue;
	if (Q == eq_AAA){
		Player* player = EP.player;
		Player* curPlayer = 0;
		int i,num = _GameStats.GetPlayersNumber();
		bool flag = false;
		char buff[128];
		reset();
		UseP = true;
		EP.player->ExecuteGameEffect(ExecuteParams(eq_StratActiveStart,player,this));
		if (UseP)
			sc_P(player);
		if (UseS)
			sc_S(player);
		EP.player->ExecuteGameEffect(ExecuteParams(eq_StratActiveEnd,player,this));
		for (i = 0; !((flag)&&(_Players[i % num] == player)) ;++i){
			if (flag){
				curPlayer=_Players[i % num];//очереди запускать от игрока, выполняющего вторичку, а не от главного
				_Interface.SetCurrPlayer(i % num);
				reset();
				UseS = true;
				curPlayer->ExecuteGameEffect(ExecuteParams(eq_StratSecStart,curPlayer,this));//тут

				sprintf(buff,"Use secondary of %s?",StratsFull[type].c_str());
				if (((!UseP) && (!UseS)) || !SelectDialogYesNo(buff))
					continue;

				if (UseP)
					sc_P(_Players[i % num]);
				if (UseS)
					sc_S(_Players[i % num]);
				curPlayer->ExecuteGameEffect(ExecuteParams(eq_StratSecEnd,curPlayer,this));//тут
			}
			if (_Players[i % num] == player)
				flag = true;
		}
		return er_delete;
	}
	if (Q == eq_SpecialStratCard){
		special(EP.stratcard->GetBonus());
		return er_normal;
	}
	return er_normal;
}



class e_DullStrat:public GameEffect{
	StratsType type;
public:
	e_DullStrat(StratsType ST){
		type = ST;
		//nt_strload(id,StratsFull[type]);
		id = StratsFull[type];
		//nt_strload(image,STRAT_B_PATH[type]);
		image = STRAT_B_PATH[type];
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		EP.player->_strats[type]=2;
		return (_StratShared[type]->Execute(EP));
	}
	GameEffect * Clone(){
		return new e_DullStrat(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};


#include "strats\\s_Leadership.cpp"
#include "strats\\s_Diplomacy.cpp"
#include "strats\\s_Assembly.cpp"
#include "strats\\s_Production.cpp"
#include "strats\\s_Trade.cpp"
#include "strats\\s_Warfare.cpp"
#include "strats\\s_Technology.cpp"
#include "strats\\s_Bureaucracy.cpp"