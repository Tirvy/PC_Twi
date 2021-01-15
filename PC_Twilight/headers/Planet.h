
class Planet{
	string _id; // Planet Name
	Hex* _location; // system, in which this planet located
	Player* _owner; // owner. 0, if neutral
	int _rescap,_infcap; // Resourses and influence of the planet
	int _rtech, _btech, _gtech, _ytech; // the power of <color> techs
	SpecialsType _Special; // refresh ability
	list<PlanetState> _effects;	//Zoldn's planet effects
public:
	Planet();
	string GetName(); // returns id
	Hex* GetSystem(); // returns location
	int SetOwner(Player* sowner);
	Player* GetOwner(); // returns player-owner
	int GetRes(); // returns rescap
	int GetInf(); // returns infcap
	int GetBonus(TechTree Color); // returns techbonus for this color
	SpecialsType GetSpecial(); // returns refresh ability
	void GetInfo(string buff); // prints all planets info to buff
	friend class SystemTranslator;

	void AddState(PlanetState PS);
	bool HasState(PlanetState PS);
	void DeleteState(PlanetState PS);

	void SetRes(int res);
	void SetInf(int inf);
	void SetHex(Hex* hex);
};