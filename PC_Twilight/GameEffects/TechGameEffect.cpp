//раздел€й и властвуй, все техи переехали по отдельным файлам по цветам

class e_PlanetTechDiscount:public GameEffect{
public:
	e_PlanetTechDiscount(){
		id = "PlanetTechDiscount";
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_TechnologyBuy)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		Player* player = EP.player;
		TechType TT = EP.Tech;
		int* bonus = EP.TechCostBonus;
		TechTree color = _GameStats.GetTechDeck()->at(TT)->GetColor();
		if (color<=Yellow)
			for (vector<Planet*>::iterator piter = player->GetPlanetsList()->begin(); piter != player->GetPlanetsList()->end(); piter++)
				if (player->IsPlanetOpen(*piter))
					*bonus = *bonus - (*piter)->GetBonus(color);
		return er_none;
	}
	GameEffect * Clone(){
		return new e_PlanetTechDiscount(*this);
	}
	string Save(){
		return string();
	}
	void Load(std::string str){}
};