class FunctionList{
	struct KillStr{
		EventHandler::EventCallbackFunction * call;
		void * param;
		FunctionList * kill;
		KillStr(EventHandler::EventCallbackFunction*call_in, void* param_in, FunctionList*kill_in){
			call = call_in;
			param = param_in;
			kill = kill_in;
		}
	};
	bool header;
	double scale,distance;
	float posx,posy;
	list<NodePath> nps;
	static void CallClear(const Event *ev, void *data);
public:
	FunctionList();
	~FunctionList();
	void setHead(string name);
	void setPos(float x, float y);
	void setScale(double scale_in);
	void setSpacing(double spacing);
	void addFunction(EventHandler::EventCallbackFunction *ret, string name, void* data = 0);
	void draw();
	void clear();
};