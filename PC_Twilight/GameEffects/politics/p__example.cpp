class e_p_name_add: public GameEffect{
public:
	e_p_name_add(){
		nt_strload(id,"name_add\0");
	}
	bool GetQ(GameEffectQs queue){
		return (queue == eq_None);
	}
	GameEffectRets Execute(ExecuteParams EP){
		if (EP.queue == eq_None)
			return er_delete;
		return er_normal;
	}
	GameEffect * Clone(){
		return new e_p_name_add(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};

class e_p_name:public e_Politic{
protected:
	void YayEff(){
	}
	void NayEff(){
	}
	void PlayerEff(Player* player){
	}
	void HexEff(Hex* system){
	}
	void PlanEff(Planet* plan){
	}
public:
	e_p_name(){
		nt_strload(id,"name\0");
		type = pc_yaynay;
		strcpy(effect,"y: all do their secondary ablity\n n: no secondary untill next round");
	}
	GameEffect * Clone(){
		return new e_p_name(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};
