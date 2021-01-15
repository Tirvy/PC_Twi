#define PATH_TO_AA_TEXTURES "data/menu/actionarea/"
#define ActionAreaHeight 2
#define ActionAreaWidth 6
#define ActionAreaTextOff -1.7
#define ACTION_AREA_BACK_S 0.089

class ActionArea{
	
	friend class GraphicInterface;

	NodePath rows[ActionAreaHeight];
	NodePath UpDownLines[2];
	std::deque<NodePath> Nodes;
	std::deque<PT(PGEntry)> Entries;
	float mx, mz, dx, dz, defoff;
	int curline, totalrows, perrow, plusonerows;
	NodePath *pass,*cnf,*desc;
	vector<int> values,stvalues;
	int optnum;
	bool done;
	bool numer;
	void RedrawOptions();
public:
	ActionArea();
	void DrawActionAreaBack();
	void DrawActionAreaBorders();
	void DrawText(const string text);
	void RemoveText();
	void RedrawArea();
	void ClearArea();
	void LaunchOptions(const string descr, AskStruct & chopt);
	static void GUI_Button(const Event *ev, void *data);
	static void GUI_RMButton(const Event *ev, void *data);
	static void GUI_MMButton(const Event *ev, void *data);
	static void GUI_Pass(const Event *ev, void *data);
	static void GUI_Confirm(const Event *ev, void *data);
	static void GUI_Up_Lines(const Event *ev, void *data);
	static void GUI_Down_Lines(const Event *ev, void *data);
}
_ActionArea;