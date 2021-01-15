FunctionList::FunctionList(){
	header = false;
	distance = 0.12;
	scale = 0.08;
	posx = 0;
	posy = 0;
}
FunctionList::~FunctionList(){
	clear();
}
void FunctionList::CallClear(const Event *ev, void *data){
	KillStr * kica = (KillStr*)data;
	(kica->call)(0,kica->param);
	kica->kill->clear();
	delete kica->kill;
	delete kica;
}
void FunctionList::setHead(string name){
	if (header == true)
		nps;//FIX!!!
	PT(TextNode) headpg = new TextNode("header");
	headpg->set_text(name);
	NodePath head(name);
	head = NodePath(headpg->generate());
	//head = _Window->get_aspect_2d().attach_new_node(headpg->generate());
	head.set_pos(posx,0,posy);
	head.set_scale(scale);
	nps.push_front(head);
	header = true;
}
void FunctionList::setScale(double scale_in){
	distance *= scale_in/scale;
	scale = scale_in;
}
void FunctionList::setSpacing(double spacing){
	distance = spacing;
}
void FunctionList::setPos(float x, float y){
	posx = x;
	posy = y;
}
void FunctionList::addFunction(EventHandler::EventCallbackFunction *ret, string name, void * data){
	NodePath newnode;
	PT(PGButton) debutton;

	debutton = new PGButton(name);
	debutton->setup(name);
	newnode = NodePath(debutton);
	newnode.set_pos(posx,0,posy-distance*(nps.size()+header));
	newnode.set_scale(scale);
	if (data == 0)
		data = (void*)debutton;
	_Framework.define_key(debutton->get_click_event(MouseButton::one() ), "button press", &CallClear, new KillStr(ret,data,this));
	nps.push_back(newnode);
}
void FunctionList::draw(){
	list<NodePath>::iterator temp = nps.begin();
	while (temp!= nps.end()){
		temp->reparent_to(_Window->get_aspect_2d());
		++temp;
	}
}
void FunctionList::clear(){
	list<NodePath>::iterator iter = nps.begin();
	while (iter != nps.end()){
		iter->remove_node();
		++iter;
	}
	nps.clear();
}