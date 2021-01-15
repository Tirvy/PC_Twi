class StatusArea{
	NodePath * StatusString;
	MenuList menu;
	static void SaveGame(const Event *ev, void *data);
public:
	StatusArea();
	void DrawBack();
	void Draw();
}
_StatusArea;