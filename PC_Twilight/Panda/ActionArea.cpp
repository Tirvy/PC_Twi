
void ActionArea::GUI_Button(const Event *ev, void *data){
	NodePath that = *(NodePath*)data;
	std::deque<NodePath>::iterator tvec = _ActionArea.Nodes.begin();
	std::deque<PT(PGEntry)>::iterator tent = _ActionArea.Entries.begin();
	int i = 0,n;
	while (that != *tvec){
		++tvec;
		++i;
	}
	if (_ActionArea.numer){
		int j = i;
		while (j>0){
			++tent;
			--j;
		}
		istringstream convert1((*tent)->get_plain_text());
		convert1 >> n;
		++n;
		ostringstream convert2;
		convert2 << n;
		(*tent)->set_text(convert2.str());
	}
	else {
		_ActionArea.values[i] = 1;
		GUI_Confirm(0,0);
	}
}
void ActionArea::GUI_RMButton(const Event *ev, void *data){
	NodePath that = *(NodePath*)data;
	std::deque<NodePath>::iterator tvec = _ActionArea.Nodes.begin();
	std::deque<PT(PGEntry)>::iterator tent = _ActionArea.Entries.begin();
	int i = 0,n;
	while (that != *tvec){
		++tvec;
		++i;
	}
	if (_ActionArea.numer){
		int j = i;
		while (j>0){
			++tent;
			--j;
		}
		istringstream convert1((*tent)->get_plain_text());
		convert1 >> n;
		--n;
		ostringstream convert2;
		convert2 << n;
		(*tent)->set_text(convert2.str());
	}
}
void ActionArea::GUI_MMButton(const Event *ev, void *data){
	NodePath that = *(NodePath*)data;
	std::deque<NodePath>::iterator tvec = _ActionArea.Nodes.begin();
	std::deque<PT(PGEntry)>::iterator tent = _ActionArea.Entries.begin();
	int i = 0,n;
	while (that != *tvec){
		++tvec;
		++i;
	}
	tvec->set_scale(abs(tvec->get_scale().get_x() - ACTION_AREA_BACK_S*9));
}
void ActionArea::GUI_Pass(const Event *ev, void *data){
	//ActionArea* that = (ActionArea*)data;
	//std::deque<NodePath>::iterator tNodes = _ActionArea.Nodes.begin();
	_GrIn.passed = true;
	_ActionArea.ClearArea();
	_ActionArea.done = true;
	_GrIn.system = false;
}
void ActionArea::GUI_Confirm(const Event *ev, void *data){
	//std::deque<NodePath>::iterator tNodes = _ActionArea.Nodes.begin();
	std::deque<PT(PGEntry)>::iterator tent = _ActionArea.Entries.begin();
	int i;
	if (_ActionArea.numer)
		for (i=0;i<_ActionArea.optnum;++i){
			if (tent == _ActionArea.Entries.end())
				cout<<"Sum Ting Wong in Acion area cnf";
			istringstream convert((*tent)->get_plain_text());
			convert >> _ActionArea.values[i];
			if (_ActionArea.values[i] < 0)
				_ActionArea.values[i] = 0;
			++tent;
		}
	else {
	}	
	_ActionArea.ClearArea();
	_ActionArea.done = true;
}
void ActionArea::GUI_Up_Lines(const Event *ev, void *data){
	LPoint2f mpos = _Mouse->get_mouse();
	if ((_ActionArea.totalrows > ActionAreaHeight)&&(_ActionArea.curline > 0))
		if ((mpos.get_x() > _ActionArea.mx - _ActionArea.dx)&&(mpos.get_x() < _ActionArea.mx + _ActionArea.dx)&&(mpos.get_y() > _ActionArea.mz - _ActionArea.dz)&&(mpos.get_y() < _ActionArea.mz + _ActionArea.dz))
			{
				--_ActionArea.curline;
				_ActionArea.RedrawArea();
			}
}
void ActionArea::GUI_Down_Lines(const Event *ev, void *data){
	LPoint2f mpos = _Mouse->get_mouse();
	if ((_ActionArea.totalrows > ActionAreaHeight)&&(_ActionArea.curline+ActionAreaHeight < _ActionArea.totalrows))
		if ((mpos.get_x() > _ActionArea.mx - _ActionArea.dx)&&(mpos.get_x() < _ActionArea.mx + _ActionArea.dx)&&(mpos.get_y() > _ActionArea.mz - _ActionArea.dz)&&(mpos.get_y() < _ActionArea.mz + _ActionArea.dz))
			{
				++_ActionArea.curline;
				_ActionArea.RedrawArea();
			}
}

ActionArea::ActionArea(){
	mx = -0.89;
	mz = -0.6;
	done = false;
	optnum = 0;
}

void ActionArea::DrawActionAreaBack(){
	NodePath AreaBack = _Window->load_model(_Window->get_aspect_2d(),"data/menu/bg/ActionAreaBack.png");
	PT(PGButton) tbutt;
	AreaBack.set_scale(ACTION_AREA_BACK_S);
	AreaBack.set_pos(mx,	0.0,	mz);
	AreaBack.set_bin("back",10);
	dx = AreaBack.get_texture()->get_orig_file_x_size() * 0.01*ACTION_AREA_BACK_S;
	dz = AreaBack.get_texture()->get_orig_file_y_size() * 0.01*ACTION_AREA_BACK_S;
	defoff = 2*dx/ActionAreaWidth;

	for (int i = 0; i < ActionAreaHeight; ++i){
		rows[i] = _Window->get_aspect_2d().attach_new_node("ActionAreaNode");
		rows[i].set_pos(mx + defoff/2, 0, mz + (1-2*i)*dz/2.5 + dz/5);
		rows[i].reparent_to(_Window->get_aspect_2d());
	}

	tbutt = new PGButton("Action Up");
	tbutt->setup("U",0.1);
	NodePath ChatUpButton = _Window->get_aspect_2d().attach_new_node(tbutt);
	ChatUpButton.set_scale(0.05);
	ChatUpButton.set_pos(	-1.0,	0.0,	-0.97);
	_Framework.define_key(tbutt->get_click_event(MouseButton::one()),"action u",&GUI_Up_Lines,0);
	_Framework.define_key("wheel_up","action u",&GUI_Up_Lines,0);
	UpDownLines[0] = NodePath(tbutt);


	tbutt = new PGButton("Action Down");
	tbutt->setup("D",0.1);
	NodePath ChatDownButton = _Window->get_aspect_2d().attach_new_node(tbutt);
	ChatDownButton.set_scale(0.05);
	ChatDownButton.set_pos(	-0.9,	0.0,	-0.97);
	_Framework.define_key(tbutt->get_click_event(MouseButton::one()),"action d",&GUI_Down_Lines,0);
	_Framework.define_key("wheel_down","action d",&GUI_Down_Lines,0);
	UpDownLines[1] = NodePath(tbutt);

	UpDownLines[0].detach_node();
	UpDownLines[1].detach_node();
}

void ActionArea::DrawActionAreaBorders(){

}

void ActionArea::RedrawArea(){
	std::deque<NodePath>::iterator tnode = Nodes.begin();
	int i = 0,j;
	while (tnode < Nodes.end()){
		tnode->detach_node();
		++tnode;
	}
	tnode = Nodes.begin();
	while (tnode < Nodes.end()){
		for (j=0; j < (perrow + (i < plusonerows)); ++j){
			if ((i>=curline)&&(i<curline+ActionAreaHeight)){
				tnode->reparent_to(rows[i-curline]);
			}
			++tnode;
			if (tnode == Nodes.end())
				return;
		}
		++i;
	}
	if (totalrows > ActionAreaHeight){
		UpDownLines[0].reparent_to(_Window->get_aspect_2d());
		UpDownLines[1].reparent_to(_Window->get_aspect_2d());
	}
	cout<<endl;
}

void ActionArea::ClearArea(){
	while (Nodes.size()!=0){
		Nodes[0].remove_node();
		Nodes.erase(Nodes.begin());
	}
	while (Entries.size() != 0)
		Entries.erase(Entries.begin());
	if (desc!=0){
		desc->remove_node();
		desc = 0;
	}
	if (pass!=0){
		pass->remove_node();
		pass = 0;
	}
	if (cnf!=0){
		cnf->remove_node();
		cnf = 0;
	}
	UpDownLines[0].detach_node();
	UpDownLines[1].detach_node();
}
void ActionArea::LaunchOptions(const string descr, AskStruct & chopt){
	int rows, totalnum, plusone;
	int i,j,k;
	InOption* topt;
	std::deque<NodePath>::iterator tnode;
	//std::deque<PT(PGEntry)>::iterator tentry = Entries.begin();
	char buff[512];
	
	numer = chopt.numer;
	curline = 0;
	done = false;
	totalnum = chopt.options.size();
	if (totalnum > 0)
		topt = &chopt.options[0];
	optnum = totalnum;
	values.clear();
	stvalues.clear();
	rows = (totalnum - 1) / ActionAreaWidth + 1;
	totalrows = rows;
	perrow = totalnum / rows;
	plusonerows = totalnum % rows;
	plusone = plusonerows;

	DrawText(descr);

	k=0;
	for (i = 0;i<rows;++i){
		for (j=0; j< perrow + (plusone>0); ++j){
			values.push_back(topt->currvalue);
			stvalues.push_back(topt->currvalue);
			PT(PGButton) nbutton;
			sprintf(buff,"%s%s%s",PATH_TO_AA_TEXTURES,topt->texture.c_str(),TextureExtension);
			nbutton = MakeButton(" ",buff);

			Nodes.insert(Nodes.end(),NodePath(nbutton));
			tnode = Nodes.end();
			--tnode;
			tnode->set_scale(0.08);
			tnode->set_pos(defoff*(j - (perrow+(plusone>0))*1.0/2.0 ), 0, 0);

			_Framework.define_key(nbutton->get_click_event(MouseButton::one()), "button press", &ActionArea::GUI_Button, &(*tnode));
			_Framework.define_key(nbutton->get_press_event(MouseButton::three()), "button press", &ActionArea::GUI_RMButton, &(*tnode));
			_Framework.define_key(nbutton->get_press_event(MouseButton::two()), "button press", &ActionArea::GUI_MMButton, &(*tnode));

			TextNode descrnode("Description");
			descrnode.set_text(topt->descr);
			descrnode.set_align(TextProperties::A_center);
			descrnode.set_font(font);
			descrnode.set_card_color(0,0,0,0.5);
			descrnode.set_card_as_margin(0, 0, 0, 0);
			descrnode.set_card_decal(true);
			descrnode.set_wordwrap(8.0);

			NodePath & textpath = tnode->attach_new_node(descrnode.generate());
			textpath.set_pos(0.0,0.0,ActionAreaTextOff * (1-descrnode.get_num_rows()/6.0));
			textpath.set_scale(0.6 * (1-descrnode.get_num_rows()/6.0));

			if (chopt.numer){
				PT(PGEntry) Number;
				Number = new PGEntry("Numerical");
				Number->setup(2,1);
				ostringstream convert;
				convert << values[k];
				Number->set_text(convert.str());
				NodePath NumberLine = tnode->attach_new_node(Number);
				NumberLine.set_scale(0.6);
				NumberLine.set_pos(	-defoff*2.5,	0.0,	ActionAreaTextOff*1.5);
				Entries.insert(Entries.end(),PT(PGEntry)(Number));
			}
			++topt;
		}
		--plusone;
	}
	if (chopt.pass){
		PT(PGButton) passbutton;
		passbutton = MakeButton("--PASS--","data/menu/actionarea/pass.png");

		_Framework.define_key(passbutton->get_click_event(MouseButton::one() ), "button press", &ActionArea::GUI_Pass, this);

		pass = new NodePath(_Window->get_aspect_2d().attach_new_node(passbutton));
		pass->set_scale(0.065);
		pass->set_pos(-0.7, 0, -0.97);

	}

	if (chopt.cnf){
		PT(PGButton) cnfbutton;
		cnfbutton = MakeButton("-CONFIRM-","data/menu/actionarea/pass.png");

		_Framework.define_key(cnfbutton->get_click_event(MouseButton::one() ), "button press", &ActionArea::GUI_Confirm, this);

		cnf = new NodePath(_Window->get_aspect_2d().attach_new_node(cnfbutton));
		cnf->set_scale(0.065);
		cnf->set_pos(-1.4, 0, -0.97);

	}
	RedrawArea();
}


void ActionArea::DrawText(const string text){

	TextNode choisedescr("ChoiseDescription");
	choisedescr.set_text(text);
	choisedescr.set_align(TextProperties::A_center);
	choisedescr.set_font(font);
	choisedescr.set_card_color(0,0,1.0,0.6);
	choisedescr.set_card_as_margin(0, 0, 0, 0);
	choisedescr.set_card_decal(true);
	choisedescr.set_wordwrap(24.0);
	
	desc = new NodePath(_Window->get_aspect_2d().attach_new_node(choisedescr.generate()));
	desc->set_pos(-0.8,0.0,-0.25+0.08*choisedescr.get_num_rows());
	desc->set_scale(0.1 * (1 - choisedescr.get_num_rows()/6.0));
}
void ActionArea::RemoveText(){
	if (desc!=0){
		desc->remove_node();
		delete desc;
		desc = 0;
	}
}