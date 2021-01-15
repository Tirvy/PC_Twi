class ChatArea{
	int ChatLines;
	bool FollowNew;
	float pos_x,pos_y;
	float border_x,border_y;
	PT(PGEntry) ChatLine;
	PT(PGButton) ChatSend;
	NodePath AreaBack;
	std::deque<PT(TextNode)> Lines;
	std::deque<PT(TextNode)>::iterator CurLine;
	void Redraw();
	PowVec<NodePath>* Nodes;
public:
	ChatArea();
	void DrawChatAreaBack();
	void AddLine(const string line);

	static void GUI_Send_Clicked(const Event *ev, void *data);
	static void GUI_Up_Lines(const Event *ev, void *data);
	static void GUI_Down_Lines(const Event *ev, void *data);
}
_ChatArea;