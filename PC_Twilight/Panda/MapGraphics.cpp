#define CCHIGH 0.2
#define FLYINGHIGH 1.2
#define SPECIAL_HEIGHT 1.0
#define GROUNDHIGH 0.2

#define UNITSCALE 1.8
#define UNITBASENUMBER 6
#define CARRIEDNUMBER 6
#define UNITHEXDIST 1.1
#define CARRIEDSCALE 1.5
#define CARRIEDDIST 0.3
#define CARRIEDHIGH 0.2
#define NUMBERHIGH 0.03
#define NUMBERSCALE 0.05
#define PLANETDIST 0.4
#define M_PI 3.14159

#define CC_CHILD 1
#define SPECIAL_CHILD 2
#define FLEET_CHILD 3
#define PLANET_CHILDS 4

NodePath MapGraphics::CreateModel(const string name,int color){
	char buff[256];
	NodePath ret;
	PT(Texture) temptexture;
	sprintf(buff,"%s%s%s",PathToUnitModel,name.c_str(),ModelsExtension);
	ret = NodePath(window->load_model(framework->get_models(), buff));
	sprintf(buff,"%s%s%s",PathToPStuffTextures,name.c_str(),TextureExtension);
	temptexture = TexturePool::load_texture(buff);
	ret.set_texture(temptexture,1);
	ret.set_name(name);
	ret.set_color_scale(PlayerColor[color][0],PlayerColor[color][1],PlayerColor[color][2],0.95);
	return ret;
}
void SetOnCircle(NodePath model, float angle, float dist,float hight = 0.0){
	model.set_pos(dist*sin(angle),dist*cos(angle),hight);
	model.set_hpr(-angle/(2*M_PI)*360.0,0.0,0.0);
}
void SetTextNumber(NodePath model, int number){
	TextNode numbernode("Number");
	std::ostringstream convert;
	convert << number;
	numbernode.set_text(convert.str());
	numbernode.set_align(TextProperties::A_center);
	numbernode.set_font(font);
	numbernode.set_card_color(0,0,0,0.5);
	numbernode.set_card_as_margin(0, 0, 0, 0);
	numbernode.set_card_decal(true);

	NodePath & textpath = model.attach_new_node(numbernode.generate());
	textpath.set_pos(0.0,0.0,NUMBERHIGH);
	textpath.set_hpr(180.0,-90.0,0.0);
	textpath.set_texture_off(0);
	textpath.set_scale(NUMBERSCALE);
}

MapGraphics::MapGraphics(){
	inited = false;
	radius = 0;
	basenode = NodePath();
	hexes = 0;
}
void MapGraphics::init(PandaFramework* framework_in,WindowFramework *window_in){
	framework = framework_in;
	window = window_in;
}
void MapGraphics::initmap(int radius_in){//, const string PathToBaseNode){
	NodePath *newnode;
	PT(Texture) temptexture;
	radius = radius_in;
	newnode = new NodePath("BaseMapNode");
	newnode->set_pos(0,0,0);
	newnode->set_scale(2.0);
	newnode->reparent_to(window->get_render());
	basenode = *newnode;
	hexes = new NodePath[radius_in];//Zoldn 2*radius*(2*radius+1) + 2*radius
	hex_ships = new int [radius_in];//Zoldn 2*radius*(2*radius+1) + 2*radius
	for (int i=0;i<radius_in;++i){//Zoldn   2*radius*(2*radius+1) + 2*radius
		hexes[i] = NodePath();
		hex_ships[i]=0;
	}
	inited = true;
	//AddHex(PathToBaseNode,0,0,1);
	NodePath tree = NodePath(window->load_model(framework->get_models(), (string(PathToTextures)+"techtree.png").c_str()));
	tree.set_hpr(180,90,0);
	tree.set_pos(0.0,0.0,-0.5);
	tree.reparent_to(_Window->get_render());
}
bool MapGraphics::AddHex(const string path, int x, int y, int planets){
	char buff[128];
	NodePath* tempnode, *tempnode2;
	PT(Texture) temptexture;
	float mod = 3.5;
	if (!inited){
		Eggog("MapGraphics::AddHex:: was not inited");
		return false;
	}
	if (!hexes[_Map.TranslateToNumber(x,y)].is_empty()){
		hexes[_Map.TranslateToNumber(x,y)].remove_node();
		/*sprintf(buff,"%shexes/%s%s",PathToTextures,path.c_str(),TextureExtension);
		temptexture = TexturePool::load_texture(buff);
		hexes[_Map.TranslateToNumber(x,y)].set_texture(temptexture,1);
		return true;*/
	}
	sprintf(buff,"%s%s%s",PathToHexModel,StardartHexFile,ModelsExtension);
	tempnode = new NodePath(window->load_model(framework->get_models(), buff));
	tempnode->set_name(path);
	tempnode->reparent_to(basenode);
    tempnode->set_scale(1.0);
    tempnode->set_pos(x*mod + abs(y%2)*mod/2, y*mod/2*sqrt(3.0), 0);
	sprintf(buff,"%shexes/%s%s",PathToTextures,path.c_str(),TextureExtension);
	temptexture = TexturePool::load_texture(buff);
	tempnode->set_texture(temptexture,1);
	hexes[_Map.TranslateToNumber(x,y)] = (*tempnode);

	ostringstream convert;
	convert << _Map.TranslateToNumber(x,y);
	tempnode->set_tag(HEX_TAG,convert.str());

	tempnode2 = new NodePath("CCNode");
	tempnode2->set_pos(0,0,1.5);
	tempnode2->reparent_to(*tempnode);	

	tempnode2 = new NodePath("SpecialNode");
	tempnode2->set_pos(0,0,SPECIAL_HEIGHT);
	tempnode2->reparent_to(*tempnode);

	tempnode2 = new NodePath("FlyingFleetNode");
	tempnode2->set_pos(0,0,FLYINGHIGH);
	tempnode2->reparent_to(*tempnode);

	switch(planets){//432x376 : 216x188 : 142x115 : 275x261
		case 1:
			tempnode2 = new NodePath("1stPlanet");
			tempnode2->set_pos(0,0,GROUNDHIGH);
			tempnode2->reparent_to(*tempnode);
			break;
		case 2:
			tempnode2 = new NodePath("1stPlanet");
			tempnode2->set_pos(0.22,-0.9,GROUNDHIGH);
			tempnode2->reparent_to(*tempnode);

			tempnode2 = new NodePath("2ndPlanet");
			tempnode2->set_pos(-0.22,0.9,GROUNDHIGH);
			tempnode2->reparent_to(*tempnode);
			break;
		case 3:
			tempnode2 = new NodePath("1stPlanet");
			tempnode2->set_pos(-0.5,-0.8,GROUNDHIGH);
			tempnode2->reparent_to(*tempnode);

			tempnode2 = new NodePath("2ndPlanet");
			tempnode2->set_pos(-0.6,0.6,GROUNDHIGH);
			tempnode2->reparent_to(*tempnode);

			tempnode2 = new NodePath("3rdPlanet");
			tempnode2->set_pos(0.9,0,GROUNDHIGH);
			tempnode2->reparent_to(*tempnode);
			break;
	}

	return true;
}
NodePath MapGraphics::GetBasicNode(){
	return basenode;
}



void MapGraphics::CreateUnit(Army* from, Unit* un, bool multiple){
	int x,y,pos,i;
	NodePath hex;
	double offangle;
	if (un == 0)
		return;
	from->GetHex()->GetCoords(&x,&y);
	hex = hexes[_Map.TranslateToNumber(x,y)];
	pos = from->GetPosition();
	if ((pos == -1)&&(un->carrier == 0)&&(multiple)){//Free fighters in space - multiple block
		int carried = from->FreeStackSize(un->Class);
		if (carried == 1){
			++hex_ships[_Map.TranslateToNumber(x,y)];
			int status = hex_ships[_Map.TranslateToNumber(x,y)];
			//un->model = CreateModel(ShipsShort[un->Class],PLAYER_COLOR_END[from->GetOwner()->GetColor()]);
			un->model = CreateModel(ShipsShort[un->Class],from->GetOwner()->GetColor());
			un->model.reparent_to(hex.get_child(FLEET_CHILD));
			if (status >= UNITBASENUMBER){	// Additional SHIPS
				offangle = 2.0*M_PI/status;
				for (i=1;i <= status;++i){
					NodePath oldnode = hex.get_child(FLEET_CHILD).get_children().get_path(i-1);
					oldnode.set_scale(UNITSCALE*UNITBASENUMBER/status);
					SetOnCircle(oldnode,offangle*i,UNITHEXDIST);
				}
			}
			else{	// Standart Ships
				offangle = 2*M_PI*(status)/UNITBASENUMBER;
				un->model.set_scale(UNITSCALE);
				SetOnCircle(un->model,offangle,UNITHEXDIST);
			}
			SetTextNumber(un->model,1);
			if (un->model.is_empty())
				Eggog("MapGraphics::CreateUnit n0!!!");
		}
		else{
			un->model = from->GetUnit(un->Class)->model;
			un->model.get_child(1).remove_node();
			SetTextNumber(un->model,carried);
			/*for (i=0;i < hex.get_child(FLEET_CHILD).get_children().size();++i){
				if (hex.get_child(FLEET_CHILD).get_child(i).get_name() == ShipsShort[un->Class]){
					un->model = hex.get_child(FLEET_CHILD).get_child(i);
					un->model.get_child(1).remove_node();
					SetTextNumber(un->model,carried);
				}
			}*/
			if (un->model.is_empty())
				Eggog("MapGraphics::CreateUnit n1!!!");
		}
	}
	else if ((pos == -1)&&(un->carrier == 0)){	// SHIPS block (with carriables)
		++hex_ships[_Map.TranslateToNumber(x,y)];
		int status = hex_ships[_Map.TranslateToNumber(x,y)];
		//un->model = CreateModel(ShipsShort[un->Class],PLAYER_COLOR_END[from->GetOwner()->GetColor()]);
		un->model = CreateModel(ShipsShort[un->Class],from->GetOwner()->GetColor());
		un->model.reparent_to(hex.get_child(FLEET_CHILD));
		if (status >= UNITBASENUMBER){	// Additional SHIPS
			offangle = 2.0*M_PI/status;
			for (i=1;i <= status;++i){
				NodePath oldnode = hex.get_child(FLEET_CHILD).get_children().get_path(i-1);
				oldnode.set_scale(UNITSCALE*UNITBASENUMBER/status);
				SetOnCircle(oldnode,offangle*i,UNITHEXDIST);
			}
		}
		else{	// Standart Ships
			offangle = 2*M_PI*(status)/UNITBASENUMBER;
			un->model.set_scale(UNITSCALE);
			SetOnCircle(un->model,offangle,UNITHEXDIST);
		}
			if (un->model.is_empty())
				Eggog("MapGraphics::CreateUnit n2!!!");
	}	// SHIPS block end
	else if (pos == -1){// if in space, but is carried by smth
		//PowExv<Unit> * passangers;
		vector<Unit*> passangers;//Zoldn's
		int carried = 0;
		passangers = from->GetPassengers(un->carrier);
		for(vector<Unit*>::iterator iter = passangers.begin(); iter != passangers.end(); iter++)
			if ((*iter)->Class == un->Class)
				++carried;
		/*while (passangers != 0){
			if (passangers->elem->Class == un->Class)
				++carried;
			passangers = passangers->next;
		}*/
		if (carried == 1){
			//un->model = CreateModel(ShipsShort[un->Class],PLAYER_COLOR_END[from->GetOwner()->GetColor()]);
			un->model = CreateModel(ShipsShort[un->Class],from->GetOwner()->GetColor());
			un->model.reparent_to(un->carrier->model);
			un->model.set_scale(CARRIEDSCALE);
			offangle = (2*M_PI)*CarriableNumber(un->Class)/CARRIEDNUMBER;
			SetOnCircle(un->model,offangle,CARRIEDDIST,CARRIEDHIGH);
			SetTextNumber(un->model,1);
		}
		else{
			for (i=1;i < un->carrier->model.get_children().size();++i){
				if (un->carrier->model.get_child(i).get_name() == ShipsShort[un->Class]){
					un->model = un->carrier->model.get_child(i);
					un->model.get_child(1).remove_node();
					SetTextNumber(un->model,carried);
				}
			}
		}
		if (un->model.is_empty())
			Eggog("MapGraphics::CreateUnit n3!!!");
	}	// carried end
	else { // planetary
		if (un->Class == DCK){
			//un->model = CreateModel(ShipsShort[un->Class],PLAYER_COLOR_END[from->GetOwner()->GetColor()]);
			un->model = CreateModel(ShipsShort[un->Class],from->GetOwner()->GetColor());
			un->model.reparent_to(hex.get_child(PLANET_CHILDS+from->GetPosition()));
			un->model.set_scale(UNITSCALE);
		}
		else{
			int carried = from->StackSize(un->Class);
			if (carried == 1){
				//un->model = CreateModel(ShipsShort[un->Class],PLAYER_COLOR_END[from->GetOwner()->GetColor()]);
				un->model = CreateModel(ShipsShort[un->Class],from->GetOwner()->GetColor());
				un->model.reparent_to(hex.get_child(PLANET_CHILDS+from->GetPosition()));
				un->model.set_scale(CARRIEDSCALE);
				if (!FindOpponentArmy(from)){
					offangle = (2*M_PI)*CarriableNumber(un->Class)/CARRIEDNUMBER;
					SetOnCircle(un->model,offangle,PLANETDIST);
				}
				else{
					offangle = (3*M_PI)*CarriableNumber(un->Class)/CARRIEDNUMBER;
					SetOnCircle(un->model,offangle,PLANETDIST);
				}
				SetTextNumber(un->model,1);
			}
			else{
				un->model = from->GetUnit(un->Class)->model;
				un->model.get_child(1).remove_node();
				SetTextNumber(un->model,carried);
				/*for (i=0;i < hex.get_child(PLANET_CHILDS+from->GetPosition()).get_children().size();++i){//un->carrier->model.get_children().size();++i){
					if (hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).get_name() == ShipsShort[un->Class]){
						hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).get_child(1).remove_node();
						un->model = hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i);
						SetTextNumber(un->model,carried);
					}
				}*/
			}
			if (un->model.is_empty())
				Eggog("MapGraphics::CreateUnit n4!!!");
		}
	}
}
void MapGraphics::MoveUnit(Army* from, Army*to, Unit*un, bool multiple){

}
void MapGraphics::KillUnit(Army* from, Unit* un, bool multiple){
	int x,y,pos,i;
	PT(Texture) temptexture;
	NodePath hex;
	double offangle;
	if (un == 0)
		return;
	from->GetHex()->GetCoords(&x,&y);
	hex = hexes[_Map.TranslateToNumber(x,y)];
	pos = from->GetPosition();
	if ((pos == -1)&&(un->carrier == 0)&&(multiple)){//Free fighters in space - multiple block
		int carried = from->FreeStackSize(un->Class);
		if (carried <= 1){
			--hex_ships[_Map.TranslateToNumber(x,y)];
			un->model.get_child(1).remove_node();
			un->model.remove_node();
		}
		else{
			un->model.get_child(1).remove_node();
			SetTextNumber(un->model,carried-1);
		}
	}
	else if ((pos == -1)&&(un->carrier == 0)){
		--hex_ships[_Map.TranslateToNumber(x,y)];
		int status = hex_ships[_Map.TranslateToNumber(x,y)];
		un->model.remove_node();
		if (status >= UNITBASENUMBER){	// Additional SHIPS  //бага тут
			offangle = 2.0*M_PI/status;
			for (i=1;i <= status;++i){
				NodePath oldnode = hex.get_child(FLEET_CHILD).get_children().get_path(i-1);
				oldnode.set_scale(UNITSCALE*UNITBASENUMBER/status);
				SetOnCircle(oldnode,offangle*i,UNITHEXDIST);
			}
		}
		else{	// Standart Ships
			offangle = 2*M_PI/UNITBASENUMBER;
			for (i=1;i <= status;++i){
				NodePath oldnode = hex.get_child(FLEET_CHILD).get_children().get_path(i-1);
				oldnode.set_scale(UNITSCALE);
				SetOnCircle(oldnode,offangle*i,UNITHEXDIST);
			}
		}
	}
	else if (pos == -1){// if in space, but is carried by smth
		vector<Unit*> passangers;
		int carried = 0;
		passangers = from->GetPassengers(un->carrier);
		//while (passangers != 0){
		for (vector<Unit*>::iterator iter = passangers.begin(); iter != passangers.end(); iter++)
			if ((*iter)->Class == un->Class)
				++carried;
		if (carried == 1){
			un->model.get_child(1).remove_node();
			un->model.remove_node();
			//un->model.get_child(1).remove_node();
			//un->model.remove_node();
			//un->model = NodePath();
		}
		else{
			un->model.get_child(1).remove_node();
			SetTextNumber(un->model,carried-1);
			/*for (i=1;i < un->carrier->model.get_children().size();++i){
				if (un->carrier->model.get_child(i).get_name() == ShipsShort[un->Class]){
					un->model = un->carrier->model.get_child(i);
					un->model.get_child(1).remove_node();
					SetTextNumber(un->model,carried-1);
				}
			}*/
		}
	}	// carried end
	else{// Planetary unit
		if (un->Class == DCK)
			un->model.remove_node();
		else{
			int carried = from->StackSize(un->Class);
			if (carried == 1){
				un->model.get_child(1).remove_node();
				un->model.remove_node();
				/*for (i=0;i < hex.get_child(PLANET_CHILDS+from->GetPosition()).get_children().size();++i){//un->carrier->model.get_children().size();++i){
					if (hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).get_name() == ShipsShort[un->Class]){
						hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).get_child(1).remove_node();
						hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).remove_node();
					}
				}*/
				if (FindOpponentArmy(from)&&(FindOpponentArmy(from)->GetUnit(un->Class))){
					offangle = (2*M_PI)*CarriableNumber(un->Class)/CARRIEDNUMBER;
					SetOnCircle(FindOpponentArmy(from)->GetUnit(un->Class)->model,offangle,PLANETDIST);
				}
			}
			else{
				for (i=0;i < hex.get_child(PLANET_CHILDS+from->GetPosition()).get_children().size();++i){//un->carrier->model.get_children().size();++i){
					if (hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).get_name() == ShipsShort[un->Class]){
						hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i).get_child(1).remove_node();
						NodePath node = hex.get_child(PLANET_CHILDS+from->GetPosition()).get_child(i);
						un->model = node;
						SetTextNumber(node,carried-1);
					}
				}
			}
		}
	}
}

void MapGraphics::ChooseHex(int *x, int* y){
}

void MapGraphics::PutCC(int x, int y, Player* player){
	NodePath hex;
	NodePath tempnode;
	Hex* hexy = _Map.GetHexh(x,y);
	int height;
	PT(Texture) temptexture;
	char buff[256];
	hex = hexes[_Map.TranslateToNumber(x,y)];
	height = 0;
	for (int i=0;i<MAX_PLAYERS;++i)
		if (hexy->GotCC(i))
			++height;
	tempnode = NodePath(window->load_model(framework->get_models(), PathToCCModel));
	tempnode.set_name("CC");
	tempnode.reparent_to(hex.get_child(CC_CHILD));
	tempnode.set_scale(1.5);
    tempnode.set_pos(0, 0, CCHIGH*height);

	int color = player->GetColor();
	sprintf(buff,"%s%s%s",PathToPStuffTextures,"CC",TextureExtension);
	temptexture = TexturePool::load_texture(buff);
	tempnode.set_texture(temptexture,1);
	tempnode.set_color_scale(PlayerColor[color][0],PlayerColor[color][1],PlayerColor[color][2],0.95);
}
void MapGraphics::ClearCCs(){
	cout<<"bu";
}
void MapGraphics::ClearCC(int x, int y, Player* player){
	NodePath hex;
	hex = hexes[_Map.TranslateToNumber(x,y)];
	while (hex.get_child(CC_CHILD).get_num_children()>0){
		hex.get_child(CC_CHILD).get_child(0).remove_node();
	}
}
void MapGraphics::PutSpecial(const string name, Player * player,int x,int y,int planet){
	NodePath hex;
	NodePath tempnode;
	char buff[255];
	Hex* hexy = _Map.GetHexh(x,y);
	int height;
	PT(Texture) temptexture;
	hex = hexes[_Map.TranslateToNumber(x,y)];
	height = 0;
	sprintf(buff,"%s%s%s",PathToSpecialsModel,name.c_str(),ModelsExtension);
	tempnode = NodePath(window->load_model(framework->get_models(), buff));
	tempnode.set_name(name);
	if (planet == -1)
		tempnode.reparent_to(hex.get_child(SPECIAL_CHILD));
	else
		tempnode.reparent_to(hex.get_child(PLANET_CHILDS+planet));
	tempnode.set_scale(1.0);
	/*sprintf(buff,"%s%s%s%s",PathToSpecialTextures,name,PLAYER_COLOR_END[player->GetColor()],TextureExtension);
	temptexture = TexturePool::load_texture(buff);
	tempnode.set_texture(temptexture,1);*/
	int color = player->GetColor();
	sprintf(buff,"%s%s%s",PathToPStuffTextures,name.c_str(),TextureExtension);
	temptexture = TexturePool::load_texture(buff);
	tempnode.set_texture(temptexture,1);
	tempnode.set_color_scale(PlayerColor[color][0],PlayerColor[color][1],PlayerColor[color][2],0.95);
}
void MapGraphics::KillSpecial(const string name, int x,int y,int planet){
	NodePath hex;
	NodePath parent;
	int i;
	hex = hexes[_Map.TranslateToNumber(x,y)];
	if (planet == -1)
		parent = hex.get_child(SPECIAL_CHILD);
	else
		parent = hex.get_child(PLANET_CHILDS+planet);
	for (i=0;i<parent.get_num_children();++i){
		if (parent.get_child(i).get_name() == name){
			parent.get_child(i).remove_node();
			return;
		}
	}
	Log("MapGraphics::KillSpecial:: didnt kill special" + name);
}