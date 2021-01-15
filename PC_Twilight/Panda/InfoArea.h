#define INFO_Y 0.84
#define INFO_X 0.74
#define INFO_D 0.065
#define INFO_S 0.05
#define INFO_W 16.0

enum InfoAreaShow {ias_diplomacy, ias_player,ias_planets, ias_techs, ias_actions, ias_politics, ias_trades, ias_objectives, ias_max};
string InfoAreaButtns[] = {"DPL", "PLS","OPL","TCH","ACT","POL","TRD","OBJ","Sam and Ron"};

class InfoArea{
	InfoAreaShow _inftoshow;
	int _pltoshow;
	PowVec<NodePath>* nodes;
	vector<NodePath> _infobt;
	vector<NodePath> _playerbt;
	vector<int> _infos;
	int row;
	void clear();
	PT(PGButton) DrawButton(const string str);
	NodePath* DrawLine(const string str);
	static void SetNewPlayer(const Event *ev, void *data);
	static void SetNewInfo(const Event *ev, void *data);


	static void DrawPlayer(const Event *ev, void *data);
	static void DrawPlanets(const Event *ev, void *data);
	static void DrawTechs(const Event *ev, void *data);
	static void DrawActions(const Event *ev, void *data);
	static void DrawPolitics(const Event *ev, void *data);
	static void DrawTradeRoutes(const Event *ev, void *data);
	static void DrawObjectives(const Event *ev, void *data);

	static void DrawPlanInfo(const Event *ev, void *data);
	static void DrawPlayers(const Event *ev, void *data);

	static void ReDrawInfo(const Event *ev, void *data);
public:
	InfoArea();
	void DrawBack();
	static void DrawSysInfo(const Event *ev, void *data);
	static void DrawArmiesSystem(const Event *ev, void *data);
	static void DrawRawText(const Event *ev, void *data);
}
_InfoArea;