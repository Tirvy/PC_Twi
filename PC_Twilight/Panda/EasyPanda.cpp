PT(PGButton) MakeButton(string name, string texture){
	PT(PGButton) nbutton;
	nbutton = new PGButton(name);
	nbutton->setup(name,0.1);
	if (texture.size() != 0){
		PT(Texture) ButtonReady=	TexturePool::load_texture(texture);
		PT(Texture) ButtonRollover=	TexturePool::load_texture(texture);
		PT(Texture) ButtonPressed=	TexturePool::load_texture(texture);
		PT(Texture) ButtonInactive=	TexturePool::load_texture(texture);

		if (name.compare(" ") == 0){
			float ratio = ButtonReady->get_orig_file_y_size() / ((float)ButtonReady->get_orig_file_x_size());
			nbutton->set_frame(LVecBase4(-1, 1, -ratio, ratio));
		}

		 
		PGFrameStyle MyStyle=nbutton->get_frame_style(0); // frame_style(0): ready state

		MyStyle.set_color(0.8,0.8,0.8,0.99);
		MyStyle.set_type(PGFrameStyle::T_flat);
		MyStyle.set_texture(ButtonReady);
		nbutton->set_frame_style(0,MyStyle);

		MyStyle.set_color(0.8,0.8,0.8,0.99);
		MyStyle.set_type(PGFrameStyle::T_bevel_in);
		MyStyle.set_texture(ButtonRollover);
		nbutton->set_frame_style(1,MyStyle);

		MyStyle.set_color(0.8,0.8,0.8,0.99);
		MyStyle.set_type(PGFrameStyle::T_bevel_out);
		MyStyle.set_texture(ButtonPressed);
		nbutton->set_frame_style(2,MyStyle);

		MyStyle.set_color(0.4,0.4,0.4,0.99);
		MyStyle.set_type(PGFrameStyle::T_ridge);
		MyStyle.set_texture(ButtonInactive);
		nbutton->set_frame_style(3,MyStyle);
	}
	else{
		nbutton->set_frame(nbutton->get_text_node()->get_frame_actual() * 1.1);
	}
	return nbutton;
}