
DropDown::DropDown(float x, float y, float scale){
	curnum = 0;
	FL = 0;
	xc = x;
	yc = y;
	sc = scale;
	PT(PGButton) BT = new PGButton("curstate");
	BT->setup("Choose");
	NP = NodePath(BT);
	NP.set_pos(x,0,y);
	NP.set_scale(scale);
	_Framework.define_key(BT->get_click_event(MouseButton::one() ), "bpress", &ShowDD, this);
}
void DropDown::AddOption(string name){
	opts.push_back(name);
}
void DropDown::SetCurVal(int n){
	if (n >= opts.size())
		return;
	curnum = n;
	PT(PGButton) BT = new PGButton("curstate");
	BT->setup(opts[n]);
	NP.remove_node();
	NP = NodePath(BT);
	NP.set_pos(xc,0,yc);
	NP.set_scale(sc);
	_Framework.define_key(BT->get_click_event(MouseButton::one() ), "bpress", &ShowDD, this);
	NP.reparent_to(_Window->get_aspect_2d());
}
void DropDown::Draw(){
	NP.reparent_to(_Window->get_aspect_2d());
}
int DropDown::GetCurVal(){
	return curnum;
}
DropDown::~DropDown(){
	if (FL!=0)
		delete FL;
}
void DropDown::ChangeVal(const Event *ev, void *data){
	wdini* wd = (wdini*)data;
	wd->DD->SetCurVal(wd->val);
	wd->DD->FL = 0;
}
void DropDown::ShowDD(const Event *ev, void *data){
	int i;
	DropDown* DD = (DropDown*) data;
	DD->FL = new FunctionList();
	DD->FL->setPos(DD->xc,DD->yc);
	DD->FL->setScale(DD->sc);
	for (i=0;i<DD->opts.size();++i)
		DD->FL->addFunction(&ChangeVal,DD->opts[i],new wdini(DD,i));
	DD->FL->draw();
}