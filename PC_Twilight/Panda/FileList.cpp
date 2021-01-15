void TestRetFunk(const Event *ev, void *data){
	PT(PGButton) debutton = (PGButton*)data;
	cout<<debutton->get_name()<<endl;
	//cout<<(string)data<<'|'<<strlen((string)data)<<','<<endl;
}

FileList::FileList(){
	header = false;
	distance = 0.12;
	scale = 0.08;
	posx = 0;
	posy = 0;
	ret = &TestRetFunk;
}
FileList::~FileList(){
	clear();
}
void FileList::CallClear(const Event *ev, void *data){
	KillStr * kica = (KillStr*)data;
	(kica->call)(0,kica->param);
	delete kica->kill;
	delete kica;
}
void FileList::setHead(string name){
	PT(TextNode) headpg = new TextNode("header");
	headpg->set_text(name);
	NodePath head(name);
	head = NodePath(headpg->generate());
	head.set_pos(posx,0,posy);
	head.set_scale(scale);
	nps.push_front(head);
	header = true;
}
void FileList::setPos(float x, float y){
	posx = x;
	posy = y;
}
void FileList::setExtension(string in_ext){
	ext = in_ext;
}
void FileList::setScale(double scale_in){
	distance *= scale_in/scale;
	scale = scale_in;
}
void FileList::setSpacing(double spacing){
	distance = spacing;
}
void FileList::draw(){
	DIR *dp;
	dirent *d;
	NodePath newnode;
	PT(PGButton) debutton;
	if (!nps.empty())
		nps.begin()->reparent_to(_Window->get_aspect_2d());

	dp = opendir("..//Release//data");
	while((d = readdir(dp)) != NULL){
		if (strstr(d->d_name,ext.c_str()) != 0){
			debutton = new PGButton(d->d_name);
			debutton->setup(d->d_name);
			newnode = _Window->get_aspect_2d().attach_new_node(debutton);
			newnode.set_pos(posx,0,posy-distance*nps.size());
			newnode.set_scale(scale);
			_Framework.define_key(debutton->get_click_event(MouseButton::one() ), "button press", &CallClear, new KillStr(ret,(void*)debutton,this));
			nps.push_back(newnode);
		}
	}
	closedir(dp);
}
void FileList::setRetFunk(EventHandler::EventCallbackFunction *function){
	ret = function;
}
void FileList::clear(){
	list<NodePath>::iterator iter = nps.begin();
	while (iter != nps.end()){
		iter->remove_node();
		++iter;
	}
	nps.clear();
}