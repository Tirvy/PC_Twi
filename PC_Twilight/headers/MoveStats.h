enum MoveOutType { MO_none, MO_lowspeed, MO_roll };

struct MoveStats{
	bool pass[DT_MAX];
	bool active[DT_MAX];
	MoveOutType moveout[DT_MAX]; 
	MoveStats();
	void Reset();
};