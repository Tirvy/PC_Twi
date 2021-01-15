class e_p_CompensatedDisarmament:public e_Politic{
protected:
	void PlanEff(Planet* plan){
		if (plan->GetOwner() == 0)
			return;
		Army* army = FindArmy(plan->GetSystem(),plan->GetOwner(),false,plan);
		if (army == 0)
			return;
		while(army->IsUnitWithAbility(uaLandBattle)){
			plan->GetOwner()->GiveGoods(1);
			army->KillUnit(army->GetUnitWithAbility(uaLandBattle,1));
		}
	}
	void DoEffect(Voting won){
		PlanEff(won.planet[0]);
	}
public:
	
	e_p_CompensatedDisarmament(){
		//nt_strload(id,"CompensatedDisarmament\0");
		id = "CompensatedDisarmament";
		tvote.planet.resize(1);
		//strcpy(effect,"All units on chosen planet are destroyed. Owner gets goods for each unit.");
		effect = "All units on chosen planet are destroyed. Owner gets goods for each unit.";
	}
	GameEffect * Clone(){
		return new e_p_CompensatedDisarmament(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};