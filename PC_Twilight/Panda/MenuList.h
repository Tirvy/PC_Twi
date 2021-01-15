enum MenuListType {mlt_none, mlt_dropdown, mlt_column, mlt_choise, mlt_switch};

class MenuList{
	float xc,yc,sc;
	MenuListType type;
	vector<string> OptStr;
	vector<EventHandler::EventCallbackFunction*> OptFunc;
	vector<void*> OptData;
	int* watched, tempwatch;
	NodePath HeadNode, DescNode;
	bool UpOrLeftDescr;
	static void Called(const Event *ev, void *data);
	static void CallKill(const Event *ev, void *data);
	static void ShDrD(const Event *ev, void *data);
	static void ChWat(const Event *ev, void *data);
public:
	MenuList();
	MenuList(const MenuList& tocopy);
	~MenuList();
	void SetPos(float x, float y, float scale);
	void SetWatched(int* watced_in);
	void AddOption(string name, EventHandler::EventCallbackFunction* call = 0, void * data = 0);
	void FillofFiles(string extension, EventHandler::EventCallbackFunction* call = 0, void * data = 0);
	void FillofNumbers(int max, EventHandler::EventCallbackFunction* call = 0, void * data = 0);
	void AddDecr(string in_descr, bool UporLeft = false);
	int GetWatched();
	void Draw(MenuListType drawtype);
};


struct ExecOpt{
	EventHandler::EventCallbackFunction * call;
	void * param;
	MenuList * obj;
	ExecOpt(EventHandler::EventCallbackFunction* call_in, void* param_in, MenuList* obj_in){
		call = call_in;
		param = param_in;
		obj = obj_in;
	}
};