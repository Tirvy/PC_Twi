void LMB(const Event *ev, void *data){
	char i;
	int n,x,y;
	NodePath pickedObj;
	LPoint2f mpos = _Mouse->get_mouse();
	//cout<<'{'<<_Mouse->get_mouse_x()<<','<<_Mouse->get_mouse_y()<<'}'; // debug
	if ((_GrIn.system)&&((mpos.get_x()>-1.00)&&(mpos.get_x()<0.37))&&((mpos.get_y()>-0.19)&&(mpos.get_y()<0.90))){//make norm coords
		_Picker->set_from_lens(_Window->get_camera(0), mpos.get_x(), mpos.get_y());
		_Traverser.traverse(_Window->get_render());
		//cout<<_Handler->get_num_entries();
		//cout<<'{'<<_Mouse->get_mouse_x()<<','<<_Mouse->get_mouse_y()<<'}';
		// Map = -1.00<x<0.37; 0.90<y<-0.19
		for (i=0;i<_Handler->get_num_entries();++i){
			if (!_Handler->get_entry(i)->get_into_node_path().find_net_tag(HEX_TAG).is_empty()){
				//cout<<'|'<<_Handler->get_entry(i)->get_into_node_path().find_net_tag(HEX_TAG).get_name();
				istringstream convert(_Handler->get_entry(i)->get_into_node_path().find_net_tag(HEX_TAG).get_tag(HEX_TAG));
				convert >> n;

				_Map.TransletaToCoords(n, &x, &y);
				//cout<<'['<<x<<';'<<y<<']'<<endl;
				_GrIn.x = x;
				_GrIn.y = y;
				_GrIn.system = false;
				_Handler->clear_entries();
				break;
			}
		}
	}
} // re do it

void RMB(const Event *ev, void *data){
	int n,x,y,i;
	int info[3];
	LPoint2f mpos = _Mouse->get_mouse();
	if (((mpos.get_x()>-1.00)&&(mpos.get_x()<0.37))&&((mpos.get_y()>-0.19)&&(mpos.get_y()<0.90))){
		_Picker->set_from_lens(_Window->get_camera(0), mpos.get_x(), mpos.get_y());
		_Traverser.traverse(_Window->get_render());
		for (i=0;i<_Handler->get_num_entries();++i){
			if (!_Handler->get_entry(i)->get_into_node_path().find_net_tag(HEX_TAG).is_empty()){
				istringstream convert(_Handler->get_entry(i)->get_into_node_path().find_net_tag(HEX_TAG).get_tag(HEX_TAG));
				convert >> n;
				_Map.TransletaToCoords(n, &x, &y);
				info[0] = x;
				info[1] = y;
				_InfoArea.DrawSysInfo(0,info);
				_Handler->clear_entries();
				break;
			}
		}
	}
}

void MMB(const Event *ev, void *data){
	LPoint3 mpos,tpos,fpos;
	mpos.set_x(_Mouse->get_mouse_x());
	mpos.set_z(_Mouse->get_mouse_y());
	//tpos = _Camera.get_relative_point(_Window->get_render_2d(),mpos);
	//fpos = _Camera.get_relative_point(_Window->get_aspect_2d(),tpos);*/
	fpos = _Window->get_aspect_2d().get_relative_point(_Window->get_render_2d(),mpos);
	cout<<"Mouse at: "<<fpos.get_x()<<':'<<fpos.get_z()<<endl;
}