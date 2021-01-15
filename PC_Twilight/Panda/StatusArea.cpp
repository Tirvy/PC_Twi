StatusArea::StatusArea(){
	StatusString = 0;
}
void StatusArea::DrawBack(){
	NodePath AreaBack = _Window->load_model(_Window->get_aspect_2d(),"data/menu/bg/StatusAreaBack.png");
	AreaBack.set_scale(0.1775);
	AreaBack.set_pos(	0.0,	0.0,	0.96);
	
	PT(PGButton) debutton;

	menu.AddOption("Menu");
	menu.AddOption("Save",SaveGame);
	menu.SetPos(1.5,0.94,0.08);
	menu.Draw(mlt_dropdown);
}
void StatusArea::Draw(){

	char buff[128];


	sprintf(buff,"%s | Round:%d | %s",GamePhases[_GameStats.CurPhase].c_str(),_GameStats.CurRound,(_Players)[_Interface.GetCurrPlayer()]->GetName().c_str());


	PT(TextNode) TimeLine;
	TimeLine = new TextNode("Chat line");
	TimeLine->set_text(buff);
	TimeLine->set_text_scale(1.5);
	if (StatusString == 0){}
	else{
		StatusString->remove_node();
		delete StatusString;
	}
	StatusString = new NodePath(_Window->get_aspect_2d().attach_new_node(TimeLine));
	StatusString->set_scale(0.05);
	StatusString->set_pos(	-1.7,	0.0,	0.94);

}
void StatusArea::SaveGame(const Event *ev, void *data){
	SaveTranslator().MakeSave("..\\Release\\data\\quicksave.tws");
}