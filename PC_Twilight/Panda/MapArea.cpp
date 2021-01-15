void MapArea::DrawBack(){
	AreaBack = _Window->load_model(_Window->get_aspect_2d(),"data/menu/bg/MapAreaBack.png");
	cout<<"lil\n";
	AreaBack.set_scale(0.1225);
	AreaBack.set_pos(-0.55,	0.0,	0.36);
}
void MapArea::SetBackColor(){
	int color = _Players[_Interface.GetCurrPlayer()]->GetColor();
	AreaBack.set_color_scale(PlayerColor[color][0],PlayerColor[color][1],PlayerColor[color][2],0.9);
}