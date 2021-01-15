
InputString::InputString(){
}
InputString::InputString(const InputString& tocopy){
}
void InputString::SetName(string name){
	TextNode TN(name);
	TN.set_text(name);
	_desc = NodePath(TN.generate());
	_dstr = new PGEntry("string");
	_dstr->setup(8,1);
	_str = _desc.attach_new_node(_dstr);
	_str.set_pos(TN.get_width() + 0.5, 0, 0);
}
void InputString::SetPos(float x, float y, float scale){
	_desc.set_pos(x,0,y);
	_desc.set_scale(scale);
}
void InputString::SetString(string name){
	_dstr->set_text(name);
}
void InputString::Activate(){
	_dstr->set_active(true);
}
void InputString::Deactivate(){
	_dstr->set_active(false);
}
string InputString::GetAsString(){
	return _dstr->get_plain_text();
}
int InputString::GetAsNumber(){
	int n;
	istringstream convert1(_dstr->get_plain_text());
	convert1 >> n;
	return n;
}
void InputString::Draw(){
	_desc.reparent_to(_Window->get_aspect_2d());
}
InputString::~InputString(){
	_desc.remove_node();
	_str.remove_node();
}