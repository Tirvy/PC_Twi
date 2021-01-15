MenuList::MenuList(){
	type = mlt_none;
	OptStr.clear();
	OptFunc.clear();
	OptData.clear();
	tempwatch = 0;
	watched = &tempwatch;
	xc = yc = sc = 0.05;
}
MenuList::MenuList(const MenuList& tocopy){
	type = tocopy.type;
	OptStr = tocopy.OptStr;
	OptFunc = tocopy.OptFunc;
	OptData = tocopy.OptData;
	tempwatch = tocopy.tempwatch;
	if (tocopy.watched != &tocopy.tempwatch)
		watched = tocopy.watched;
	else
		watched = &tempwatch;
	xc = tocopy.xc;
	yc = tocopy.yc;
	sc = tocopy.sc;
}
void MenuList::SetPos(float x, float y, float scale){
	xc = x;
	yc = y;
	sc = scale;
}
void MenuList::SetWatched(int* watced_in){
	watched = watced_in;
}
void MenuList::AddOption(string name, EventHandler::EventCallbackFunction* call, void * data){
	OptStr.push_back(name);
	if ((call == 0)&&(watched == 0)){
		cout<<"Watcher not pointed\n";
	}
	else if (call != 0){
		OptFunc.push_back(call);
		OptData.push_back(data);
	}
	else{
		OptFunc.push_back(&ChWat);
		OptData.push_back(new ExecOpt(&ChWat,new int(OptData.size()),this));
	}
}
int MenuList::GetWatched(){
	return *watched;
}
void MenuList::Draw(MenuListType drawtype){
	int i;
	NodePath temp;
	PT(PGButton)  pbut;

	if (type != mlt_none)
		return;
	type = drawtype;
	switch (drawtype){
		case mlt_none:
			break;
		case mlt_dropdown:
			pbut = new PGButton("menulist");
			pbut->setup(OptStr[*watched]);
			_Framework.define_key(pbut->get_click_event(MouseButton::one() ), "bpress", &ShDrD, new ExecOpt(0,0,this));
			temp = NodePath(pbut);
			temp.set_pos(xc,0,yc);
			temp.set_scale(sc);
			HeadNode = temp;
			HeadNode.reparent_to(_Window->get_aspect_2d());
			break;
		case mlt_column:
		case mlt_choise:
			for (i = 0; i < OptStr.size(); ++i){
				pbut = new PGButton("menulist");
				pbut->setup(OptStr[i]);
				if (type = mlt_choise)
					_Framework.define_key(pbut->get_click_event(MouseButton::one() ), "bpress", &CallKill, new ExecOpt(OptFunc[i],OptData[i],this));
				else
					_Framework.define_key(pbut->get_click_event(MouseButton::one() ), "bpress", &Called, new ExecOpt(OptFunc[i],OptData[i],this));
				temp = NodePath(pbut);
				if (i == 0){
					temp.set_pos(xc,0,yc);
					temp.set_scale(sc);
					HeadNode = temp;
					HeadNode.reparent_to(_Window->get_aspect_2d());
				}
				else{
					temp.set_pos(0,0,-i * sc * 30);
					temp.reparent_to(HeadNode);
				}
			}
			break;
		case mlt_switch:
			pbut = new PGButton("menulist");
			pbut->setup(OptStr[*watched]);
			_Framework.define_key(pbut->get_click_event(MouseButton::one() ), "bpress", &ChWat, new ExecOpt(OptFunc[*watched],0,this));
			temp = NodePath(pbut);
			temp.set_pos(xc,0,yc);
			temp.set_scale(sc);
			HeadNode = temp;
			HeadNode.reparent_to(_Window->get_aspect_2d());
			break;
		default:
			cout<<"The type is 0 "<<drawtype<<'.'<<endl;
	}
	if (!DescNode.is_empty()){
		DescNode.set_scale(sc);
		DescNode.set_pos(xc - 1.5*!UpOrLeftDescr*sc,0,yc + 1.5*UpOrLeftDescr*sc);
		DescNode.reparent_to(_Window->get_aspect_2d());
	}
}
MenuList::~MenuList(){
	while (HeadNode.get_children().get_num_paths() > 0)
		HeadNode.get_child(0).remove_node();
	HeadNode.remove_node();
	DescNode.remove_node();
}
void MenuList::CallKill(const Event *ev, void *data){
	ExecOpt* exec = (ExecOpt*)data;
	(exec->call)(0,exec->param);
	delete exec->obj;
}
void MenuList::Called(const Event *ev, void *data){
	ExecOpt* exec = (ExecOpt*)data;
	(exec->call)(0,exec->param);
}
void MenuList::ShDrD(const Event *ev, void *data){
	ExecOpt* exec = (ExecOpt*)data;
	int i,j;
	if (exec->call == 0){
		NodePath temp;
		PT(PGButton)  pbut;
		double shift;
		exec->obj->HeadNode.reparent_to(_Window->get_aspect_2d());
		if (exec->obj->yc - (exec->obj->OptStr.size())*1.5*exec->obj->sc < -0.95)
			shift = (-0.95 - exec->obj->yc + (exec->obj->OptStr.size()) * 1.5 * exec->obj->sc) / exec->obj->sc;
		else
			shift = 0;
		for (i = 0; i < exec->obj->OptStr.size(); ++i){
			pbut = new PGButton("menulistelem");
			//if ((exec->obj->watched != 0)&&(i > *exec->obj->watched))
			//	j = i+1;
			//else
				j = i;
			pbut->setup(exec->obj->OptStr[j]);
			_Framework.define_key(pbut->get_click_event(MouseButton::one() ), "bpress", &ShDrD, new ExecOpt(exec->obj->OptFunc[j],exec->obj->OptData[j],exec->obj));
			temp = NodePath(pbut);
			temp.set_pos(0,1,-(i+1) * 1.5 + shift);
			temp.reparent_to(exec->obj->HeadNode); // ÁÀÃÓËß!!!  Íóæíà êîíñòàíòà
		}
	}
	else {
		(exec->call)(0,exec->param);
		while (exec->obj->HeadNode.get_children().get_num_paths() > 0)
			exec->obj->HeadNode.get_child(0).remove_node();
	}
}
void MenuList::ChWat(const Event *ev, void *data){
	ExecOpt* exec = (ExecOpt*)data;
	if (exec->param != 0){
		if (*(int*)exec->param >= exec->obj->OptStr.size()){
			cout<<"Wrong num"<<endl;
			return;
		}
		*(exec->obj->watched) = *(int*)(exec->param);
	}
	else{
		if (*exec->obj->watched >= exec->obj->OptStr.size()-1)
			*exec->obj->watched = 0;
		else
			++ *exec->obj->watched;
	}
	exec->obj->HeadNode.remove_node();
	MenuListType tt = exec->obj->type;
	exec->obj->type = mlt_none;
	exec->obj->Draw(tt);
}

void MenuList::FillofFiles(string extension, EventHandler::EventCallbackFunction* call, void * data){
	DIR *dp;
	dirent *d;

	dp = opendir("..//Release//data");
	while((d = readdir(dp)) != NULL)
		if (strstr(d->d_name,extension.c_str()) != 0){
				AddOption(d->d_name,call,data);
		}
	closedir(dp);
}
void MenuList::FillofNumbers(int max, EventHandler::EventCallbackFunction* call, void * data){ 
	int i;
	ostringstream ss;
	for (i=0; i<max; ++i){
		ss.str("");
		ss<<'['<<i<<']';
		AddOption(ss.str(),call,data);
	}
}

void MenuList::AddDecr(string in_descr, bool UporLeft){
	TextNode TN("Descr");
	TN.set_text(in_descr);
	UpOrLeftDescr = UporLeft;
	if (UporLeft){}
	else
		TN.set_align(TextProperties::A_right);
	DescNode = NodePath(TN.generate());
	
}
