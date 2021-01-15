enum ChoiseType {ct_simple,ct_simple_p,ct_numerical};

struct InOption{
	string texture;
	string descr;
	int currvalue;
	int maxvalue;
	InOption(){
		currvalue = 0;
		maxvalue = 0;
	}
};

struct AskStruct{
	vector<InOption> options;
	bool system;
	bool pass;
	bool cnf;
	bool numer;
	AskStruct(bool pass_in = false, bool cnf_in = false, bool numer_in = false, bool system_in = false){
		options.clear();
		system = system_in;
		pass = pass_in;
		cnf = cnf_in;
		numer = numer_in;
	}
};

class GraphicInterface{

	friend class ActionArea;
	friend void LMB(const Event *ev, void *data);

	bool inited;
	bool system;
	int x,y;
	int LastPlayer;
	bool launched;
	bool timed;
	int timeleft;
	string descr;
	AskStruct chopt;
	bool passed;

public:
	GraphicInterface();
	void InitChoise(const string in_descr, bool pass_in = false, bool cnf_in = false, bool numer_in = false);
	void AddOption(const string pathtoimage, const string in_descr);
	void AddNumerical(const string pathtoimage, const string in_descr, int standart = 0, int max = -1);
	vector<int> LaunchChoise();
	vector<int> SysChoise(const string in_descr, bool pass_in = false);

}
_GrIn;