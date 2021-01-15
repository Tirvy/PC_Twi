
class MapGraphics{

	bool inited;
	int radius;
	NodePath basenode;
	NodePath * hexes;
	int * hex_ships;
	PandaFramework *framework;
	WindowFramework *window;

	NodePath CreateModel(const string name,const int color = 0);
public:
	MapGraphics();
	void init(PandaFramework* framework_in,WindowFramework *window_in);
	void initmap(int radius);//, const string PathToBaseNode);
	bool AddHex(const string path, int x, int y, int planets);
	NodePath GetBasicNode();


	void CreateUnit(Army* from, Unit* un, bool multiple = false);
	void MoveUnit(Army* from, Army*to, Unit*un, bool multiple = false);
	void KillUnit(Army* from, Unit* un, bool multiple = false);

	void PutCC(int x, int y, Player* player);
	void ClearCCs();
	void ClearCC(int x, int y, Player* player);

	void PutSpecial(const string name, Player * player,int x,int y,int planet = -1);
	void KillSpecial(const string name, int x,int y,int planet = -1);

	void ChooseHex(int *x, int* y);
}
_MapGraphics;