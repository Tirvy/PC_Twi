
class VictoryPoint{
	int power;
	VP_type type;
	string description;
public:
	VictoryPoint(int power_in,VP_type type_in,const string descr);
	int GetPower();
	VP_type GetType();
	string GetDescr(); // returns description of this VP
};