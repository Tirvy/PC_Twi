#define CHAT_AREA_BACK_X 0.89
#define CHAT_AREA_BACK_Y -0.6
#define CHAT_AREA_BACK_S 0.089
#define CHAT_MAX_LINES 13
#define CHAT_WORDWRAP 30.0 

void ChatArea::GUI_Send_Clicked(const Event *ev, void *data){
	//PGItem* CurrentButton=(PGButton *)data;
	// Your action here
	std::string str;
	if ((data == (void*)_ChatArea.ChatSend)||(data == (void*)_ChatArea.ChatLine)){
		str = _ChatArea.ChatLine->get_plain_text();
		if (str[0]!= '_')
			CheatMachine().UseCheat(str);
		_ChatArea.ChatLine->set_text("");
		_ChatArea.ChatLine->set_focus(true);
		_ChatArea.AddLine(str.c_str());
	}
}


void ChatArea::DrawChatAreaBack(){
	PT(PGButton) tbutt;

	AreaBack = _Window->load_model(_Window->get_aspect_2d(),"data/menu/bg/ChatAreaBack.png");
	AreaBack.set_scale(CHAT_AREA_BACK_S);
	AreaBack.set_pos(CHAT_AREA_BACK_X,	0.0,	CHAT_AREA_BACK_Y);
	pos_x = CHAT_AREA_BACK_X;
	pos_y = CHAT_AREA_BACK_Y;
	border_x = AreaBack.get_texture()->get_orig_file_x_size() * 0.01*CHAT_AREA_BACK_S;
	border_y = AreaBack.get_texture()->get_orig_file_y_size() * 0.01*CHAT_AREA_BACK_S;

	ChatLine = new PGEntry("Chat line");
	ChatLine->setup(30,1);
	ChatLine->set_overflow_mode(true);
	//ChatLine->set_active(false); // Let it be here
	NodePath ChatLineHead = _Window->get_aspect_2d().attach_new_node(ChatLine);
	ChatLineHead.set_scale(0.05);
	ChatLineHead.set_pos(	0.05,	0.0,	-0.97);

	ChatSend = new PGButton("Chat send button");
	ChatSend->setup("Send",0.1);
	ChatSend->set_active(false); // Let it be here
	NodePath ChatSendButton = _Window->get_aspect_2d().attach_new_node(ChatSend);
	ChatSendButton.set_scale(0.05);
	ChatSendButton.set_pos(	1.6,	0.0,	-0.97);

	_Framework.define_key(ChatSend->get_click_event(MouseButton::one()),"chat send",&GUI_Send_Clicked,ChatSend);
	_Framework.define_key(ChatLine->get_press_event(KeyboardButton::enter()),"chat send",&GUI_Send_Clicked,ChatLine);


	tbutt = new PGButton("Chat Up");
	tbutt->setup("U",0.1);
	NodePath ChatUpButton = _Window->get_aspect_2d().attach_new_node(tbutt);
	ChatUpButton.set_scale(0.09);
	ChatUpButton.set_pos(	1.63,	0.0,	-0.40);
	_Framework.define_key(tbutt->get_click_event(MouseButton::one()),"chat u",&GUI_Up_Lines,0);
	_Framework.define_key("wheel_up","chat u",&GUI_Up_Lines,0);


	tbutt = new PGButton("Chat Down");
	tbutt->setup("D",0.1);
	NodePath ChatDownButton = _Window->get_aspect_2d().attach_new_node(tbutt);
	ChatDownButton.set_scale(0.09);
	ChatDownButton.set_pos(	1.63,	0.0,	-0.75);
	_Framework.define_key(tbutt->get_click_event(MouseButton::one()),"chat d",&GUI_Down_Lines,0);
	_Framework.define_key("wheel_down","chat d",&GUI_Down_Lines,0);
	Redraw();
}

void ChatArea::GUI_Up_Lines(const Event *ev, void *data){
	LPoint2f mpos = _Mouse->get_mouse();
	if ((mpos.get_x() > _ChatArea.pos_x - _ChatArea.border_x)&&(mpos.get_x() < _ChatArea.pos_x + _ChatArea.border_x)&&(mpos.get_y() > _ChatArea.pos_y - _ChatArea.border_y)&&(mpos.get_y() < _ChatArea.pos_y + _ChatArea.border_y)){//make norm coords
		if (_ChatArea.CurLine > _ChatArea.Lines.begin()){
			--_ChatArea.CurLine;
			_ChatArea.Redraw();
		}
	}
}

void ChatArea::GUI_Down_Lines(const Event *ev, void *data){
	LPoint2f mpos = _Mouse->get_mouse();
	if ((mpos.get_x() > _ChatArea.pos_x - _ChatArea.border_x)&&(mpos.get_x() < _ChatArea.pos_x + _ChatArea.border_x)&&(mpos.get_y() > _ChatArea.pos_y - _ChatArea.border_y)&&(mpos.get_y() < _ChatArea.pos_y + _ChatArea.border_y)){//make norm coords
		if (_ChatArea.CurLine < (--_ChatArea.Lines.end())){
			++_ChatArea.CurLine;
			_ChatArea.Redraw();
		}
	}
}

void ChatArea::Redraw(){

	PowVec<NodePath>* tNodes = Nodes;
	while (tNodes != 0){
		tNodes->elem->remove_node();
		tNodes->elem = 0;
		tNodes = tNodes->next;
	}
	if (tNodes!=0)
		delete tNodes;
	Nodes = 0;

	int NumLines = 0;
	std::deque<PT(TextNode)>::iterator tempit = CurLine;
	while ( ( tempit < Lines.end() )&&( NumLines < ChatLines ) ){
		if (Nodes == 0){
			Nodes = new PowVec<NodePath>;
			tNodes = Nodes;
		}
		else{
			tNodes->next = new PowVec<NodePath>;
			tNodes = tNodes->next;
		}
		(*tempit)->set_max_rows( ChatLines - NumLines );
		tNodes->elem = new NodePath(_Window->get_aspect_2d().attach_new_node((*tempit)->generate()));
		tNodes->elem->set_scale(0.05);
		tNodes->elem->set_pos(	0.05,	0.0,	-0.27 - NumLines * 0.05);
		NumLines += (*tempit)->get_num_rows();
		tempit++;
	}
}
void ChatArea::AddLine(const string line){
	PT(TextNode) newline = new TextNode("newline");
	newline->set_wordwrap(30.0);
	newline->set_text(line);
	Lines.insert(Lines.end(),newline);
	/*if (FollowNew)
		GUI_Down_Lines(0,0);*/
	if (Lines.size()>=CHAT_MAX_LINES)
		++CurLine;
	Redraw();
}

ChatArea::ChatArea(){
	FollowNew = true;
	ChatLines = CHAT_MAX_LINES;
	PT(TextNode) newline = new TextNode("newline");
	newline->set_wordwrap(CHAT_WORDWRAP);
	newline->set_text("Welcome, to the league of twi imper. Have a nice day!");
	Lines.insert(Lines.begin(),newline);
	CurLine = Lines.begin();
}