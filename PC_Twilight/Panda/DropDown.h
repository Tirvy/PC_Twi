class DropDown{
	int curnum;
	float xc,yc,sc;
	FunctionList *FL;
	NodePath NP;
	vector<string> opts;
	static void ShowDD(const Event *ev, void *data);
	static void ChangeVal(const Event *ev, void *data);
public:
	DropDown(float x, float y, float scale);
	void AddOption(string name);
	void SetCurVal(int n);
	void Draw();
	int GetCurVal();
	~DropDown();
};

struct wdini{
	DropDown* DD;
	int val;
	wdini(DropDown* DD_in, int val_in){
		DD = DD_in;
		val = val_in;
	}
};