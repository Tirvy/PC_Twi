class FileList{
	struct KillStr{
		EventHandler::EventCallbackFunction * call;
		void * param;
		FileList * kill;
		KillStr(EventHandler::EventCallbackFunction*call_in, void* param_in, FileList*kill_in){
			call = call_in;
			param = param_in;
			kill = kill_in;
		}
	};
	bool header;
	double scale,distance;
	float posx,posy;
	string ext;
	list<NodePath> nps;
	EventHandler::EventCallbackFunction *ret;
	static void CallClear(const Event *ev, void *data);
public:
	FileList();
	~FileList();
	void setHead(string name);
	void setPos(float x, float y);
	void setExtension(string in_ext);
	void setFolder(string in_ext);
	void setScale(double scale_in);
	void setSpacing(double spacing);
	void setRetFunk(EventHandler::EventCallbackFunction *function);
	void draw();
	void clear();
};