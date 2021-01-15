enum MainMenuType {mmt_main,mmt_new,mmt_load,mmt_none};
class MenuArea{
	MainMenuType status;
	MenuList Speaker, Map, VPs, Load;
	deque<MenuList> PlayerRaces;
	deque<MenuList> PlayerStatus;
	deque<InputString> PlayerNames;
	GameInitSettings InitS;
	NodePath ReloadButton, BackPic;


	static void DrawMain(const Event *ev, void *data);
	static void DrawNewGame(const Event *ev, void *data);
	static void DrawConnected(const Event *ev, void *data);
	static void DrawQuickGame(const Event *ev, void *data);
	static void DrawConToGame(const Event *ev, void *data);
	static void DrawLoadGame(const Event *ev, void *data);
	static void DrawExitGame(const Event *ev, void *data);

	static void ReloadTemplate(const Event *ev, void *data);
	static void ReloadSave(const Event *ev, void *data);
	static void StartGameHost(const Event *ev, void *data);
	static void StartGameClient(const Event *ev, void *data);
	static void GameSequence(const Event *ev, void *data);
	static void TryConnection(const Event *ev, void *data);
	static void LoadGame(const Event *ev, void *data);
public:
	void start();
}
_MenuArea;