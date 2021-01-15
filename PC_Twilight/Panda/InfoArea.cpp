

InfoArea::InfoArea(){
	for (int i = 0; i<ias_max; ++i)
		_infos.push_back(i);
	nodes = 0;
	row = 0;
	_inftoshow = ias_player;
	_pltoshow = 0;
}
NodePath* InfoArea::DrawLine(const string str){
	PowVec<NodePath> * tnode;
	if (nodes == 0){
		nodes = new PowVec<NodePath>();
		tnode = nodes;
	}
	else{
		tnode = nodes;
		while (tnode->next != 0)
			tnode = tnode->next;
		tnode->next = new PowVec<NodePath>();
		tnode = tnode->next;
	}

	TextNode string("InfoString");
	string.set_text(str);
	string.set_card_color(0,0,0.8,0.5);
	string.set_card_as_margin(0, 0, 0, 0);
	string.set_card_decal(true);
	string.set_wordwrap(INFO_W);

	tnode->elem = new NodePath(_Window->get_aspect_2d().attach_new_node(string.generate()));
	tnode->elem->set_pos(INFO_X,	0.0,	INFO_Y - INFO_D*row);
	tnode->elem->set_scale(INFO_S);
	row += string.get_num_rows();

	return tnode->elem;
}
PT(PGButton) InfoArea::DrawButton(const string str){
	PowVec<NodePath> * tnode;
	if (nodes == 0){
		nodes = new PowVec<NodePath>();
		tnode = nodes;
	}
	else{
		tnode = nodes;
		while (tnode->next != 0)
			tnode = tnode->next;
		tnode->next = new PowVec<NodePath>();
		tnode = tnode->next;
	}

		
	PT(PGButton) bttn = MakeButton(str,"");
	//bttn->get_text_node()->set_wordwrap(INFO_W);

	tnode->elem = new NodePath(_Window->get_aspect_2d().attach_new_node(bttn));
	tnode->elem->set_pos(INFO_X,	0.0,	INFO_Y - INFO_D*row);
	tnode->elem->set_scale(INFO_S);
	row += bttn->get_text_node()->get_num_rows();

	return bttn;
}

void InfoArea::DrawBack(){
	PT(PGButton) button;
	PT(Texture) texture;
	NodePath temp;
	int i;

	NodePath AreaBack = _Window->load_model(_Window->get_aspect_2d(),"data/menu/bg/InfoAreaBack.png");
	AreaBack.set_scale(0.056);
	AreaBack.set_pos(1.225,	0.0,	0.36);

	for (i=0; i<_GameStats.GetPlayersNumber();++i){
		button = MakeButton(" ",string(PATH_TO_AA_TEXTURES) + _Players[i]->GetBanner() + TextureExtension);
		_Framework.define_key(button->get_click_event(MouseButton::one()),"info chplayer",&SetNewPlayer,&_infos[i]);
		temp = _Window->get_aspect_2d().attach_new_node(button);
		temp.set_scale(0.05);
		temp.set_pos(1.61,	0.0,	0.8 - i * 0.1);
		_playerbt.push_back(temp);
	}

	for (i=0; i < ias_max;++i){
		button = MakeButton(InfoAreaButtns[i],"");
		_Framework.define_key(button->get_click_event(MouseButton::one()),"info chinfo",&SetNewInfo,&_infos[i]);
		temp = _Window->get_aspect_2d().attach_new_node(button);
		temp.set_scale(0.045);
		temp.set_pos(0.74 + 0.13*i,	0.0,	-0.15);
		_infobt.push_back(temp);
	}
}

void InfoArea::DrawSysInfo(const Event *ev, void *data){
	int x = ((int*)data)[0],y = ((int*)data)[1];
	char buff[1024];
	_InfoArea.clear();
	int i;
	PT(PGButton) button;
	Hex* hex = _Map.GetHexh(x,y);
	Planet* plan;
	sprintf(buff,"System {%s} (%d,%d)",hex->GetId().c_str(),x,y);
	_InfoArea.DrawLine(buff);
	_InfoArea.DrawLine("Planets: ");	
	for (i=0;i<MAX_PLANETS;++i){
		plan = hex->GetPlanet(i+1);
		if (hex->GetPlanet(i+1) != 0){
			sprintf(buff,"{%s}: %d/%d",plan->GetName().c_str(),plan->GetRes(),plan->GetInf());
			button = _InfoArea.DrawButton(buff);
			_Framework.define_key(button->get_click_event(MouseButton::one() ), "button press", &DrawPlanInfo, plan);
		}
		else if (i==0){
			_InfoArea.DrawLine("None in this system");
		}
	}

	for (int i=0;i<_GameStats.GetPlayersNumber();++i)
		if (hex->GotCC(i+1)){
			sprintf(buff,"Got {%s}'s CC",_Players[i]->GetName().c_str());
			_InfoArea.DrawLine(buff);
		}

	Army* tarmy = FindArmy(x,y,0,false);
	if (tarmy != 0){
		sprintf(buff,"{%s}'s Army:",tarmy->GetOwner()->GetName().c_str());
		_InfoArea.DrawLine(buff);
		for (int i=0;i<MAX_UNIT;++i){
			if (tarmy->StackSize((UnitType)i) > 0){
				sprintf(buff,"[%s] : %d",ShipsShort[i].c_str(),tarmy->StackSize((UnitType)i));
				_InfoArea.DrawLine(buff);
			}
		}
		if (FindOpponentArmy(tarmy)){
			PT(PGButton) bt = _InfoArea.DrawButton("View Armies");
			_Framework.define_key(bt->get_click_event(MouseButton::one()), "varmies", DrawArmiesSystem, tarmy);
		}
	}
}
void InfoArea::DrawPlanInfo(const Event *ev, void *data){
	Planet* plan;
	Army* tarmy;
	char buff[1024];

	_InfoArea.clear();
	plan = (Planet*) data;
	int x,y;
	plan->GetSystem()->GetCoords(&x,&y);
	sprintf(buff,"{%s}:",plan->GetName().c_str());//,plan->GetSystem()->GetId());
	_InfoArea.DrawLine(buff);
	sprintf(buff,"%d res / %d inf",plan->GetRes(),plan->GetInf());
	_InfoArea.DrawLine(buff);
	if (plan->GetOwner()!=0)
		sprintf(buff,"Owner: {%s}",plan->GetOwner()->GetName().c_str());
	else
		sprintf(buff,"neutral");
	_InfoArea.DrawLine(buff);
	if (plan->GetSpecial()!=st_ZERO){
		sprintf(buff,"Special: %s",SpecialFull[plan->GetSpecial()].c_str());
		_InfoArea.DrawLine(buff);
	}
	for (int i=0; i <= Yellow; ++i){
		if (plan->GetBonus((TechTree)i) > 0){
			sprintf(buff,"%s tech bonus: %d",TechColorFull[i].c_str(),plan->GetBonus((TechTree)i));
			_InfoArea.DrawLine(buff);
		}
	}

	tarmy = FindArmy(x,y,plan->GetOwner(),false,plan);
	if (tarmy==0){
		return;
	}
	_InfoArea.DrawLine("Army:");
	for (int i=0;i<MAX_UNIT;++i){
		if (tarmy->StackSize((UnitType)i) > 0){
			sprintf(buff,"[%s] : %d",ShipsShort[i].c_str(),tarmy->StackSize((UnitType)i));
			_InfoArea.DrawLine(buff);
		}
	}
}
void InfoArea::DrawPlayers(const Event *ev, void *data){
	char buff[1024];
	_InfoArea.clear();
	for (int i = 0; i<_GameStats.GetPlayersNumber(); ++i){
		PT(PGButton) button;
		sprintf(buff,"%s [%s] [%s]",_Players[i]->GetName().c_str(),RacesFull[_Players[i]->GetRace()].c_str(),PLAYER_COLOR_FULL[_Players[i]->GetColor()].c_str());
		button = _InfoArea.DrawButton(buff);
		_Framework.define_key(button->get_click_event(MouseButton::one() ), "button press", &DrawPlayer, _Players[i]);
	}
}
void InfoArea::DrawPlayer(const Event *ev, void *data){
	char buff[1024],buff2[1024];
	Player* pl;
	int j,k;
	_InfoArea.clear();
	pl = (Player*)data;
	int n = pl->GetNumber() - 1;

	sprintf(buff,"N %d {%s} [%s] [%s]",n+1,pl->GetName().c_str(),RacesFull[pl->GetRace()].c_str(),PLAYER_COLOR_FULL[pl->GetColor()].c_str());
	_InfoArea.DrawLine(buff);
	sprintf(buff,"Strats: ");
	for (j=0;j<MAX_STRAT;++j){
		if (pl->GotStrat((StratsType)j) == 1){
			strcat(buff,StratsFull[j].c_str());
			strcat(buff," A;");
		}
		if (pl->GotStrat((StratsType)j) == 2){
			strcat(buff,StratsFull[j].c_str());
			strcat(buff," B;");
		}
	}
	_InfoArea.DrawLine(buff);

	sprintf(buff,"CCs: ST: %d / FS: %d / CP: %d",pl->GetCountersSA(),pl->GetCountersFS(),pl->GetCountersCP());
	_InfoArea.DrawLine(buff);

	sprintf(buff,"Goods: %d",pl->GetGoods());
	_InfoArea.DrawLine(buff);

	sprintf(buff,"VPs: %d",pl->recountVP());
	_InfoArea.DrawLine(buff);

	list<e_Objective*>::iterator iter;
	sprintf(buff,"Objectives: ");
	for (list<GameEffect*>::iterator iter = pl->_PlayerGameEffect.begin(); iter != pl->_PlayerGameEffect.end(); iter++){
		if ((*iter)->GetQ(eq_Objective)){
			if (((e_Objective*)(*iter))->isDone){
				strcat(buff,((e_Objective*)(*iter))->GetId().c_str());
				strcat(buff,", ");
			}
		}
	}
	_InfoArea.DrawLine(buff);
}
void InfoArea::DrawTradeRoutes(const Event *ev, void *data){
	int total = MAX_TRADES * _GameStats.GetPlayersNumber();
	int i;
	TradeRoute * troute;
	char buff[1024];
	_InfoArea.clear();
	for (i = 0;i<total;++i){
		troute = _Players[i/MAX_TRADES]->GetTrade(i % MAX_TRADES);
		if (troute!=0){
			if (troute->owner != _Players[i/MAX_TRADES])
				sprintf(buff,"{%s}'s %d  from {%s}",troute->owner->GetName().c_str(),troute->power,_Players[i/MAX_TRADES]->GetName().c_str());
			else
				sprintf(buff,"{%s}'s %d",troute->owner->GetName().c_str(),troute->power);
			_InfoArea.DrawLine(buff);
		}
	}
}
void InfoArea::DrawArmiesSystem(const Event *ev, void *data){
	//Army *army1=((Army **)data)[0],*army2=((Army **)data)[1];
	Army* army1 = (Army*)data;
	Army* army2 = FindOpponentArmy(army1);
	bool stacked[MAX_UNIT];
	char buff[1024];
	int i;
	_InfoArea.clear();

	for (i=0;i<MAX_UNIT;++i)
		stacked[i]=false;
	sprintf(buff,"{%s}'s army:",army1->GetOwner()->GetName().c_str());
	_InfoArea.DrawLine(buff);
	//tunit = army1->GetUnits();
	for (vector<Unit*>::iterator iter = army1->GetUnits()->begin(); iter != army1->GetUnits()->end(); iter++){
	//while(tunit!=0){
		if (!stacked[(*iter)->Class]){
			if ((*iter)->HasAbility(uaSustain) == false){
				stacked[(*iter)->Class] = true;
				sprintf(buff,"%s x%d",ShipsShort[(*iter)->Class].c_str(),army1->StackSize((*iter)->Class));
				_InfoArea.DrawLine(buff);
			}
			else
				_InfoArea.DrawLine(_Info.UnitInfo(*iter,army1));
		}
		//tunit = tunit->next;
	}

	for (i=0;i<MAX_UNIT;++i)
		stacked[i]=false;
	sprintf(buff,"{%s}'s army:",army2->GetOwner()->GetName().c_str());
	_InfoArea.DrawLine(buff);
	//tunit = army2->GetUnits();
	//while(tunit!=0){
	for (vector<Unit*>::iterator iter = army2->GetUnits()->begin(); iter != army2->GetUnits()->end(); iter++){
		if (!stacked[(*iter)->Class]){
			if ((*iter)->HasAbility(uaSustain) == false){
				stacked[(*iter)->Class] = true;
				sprintf(buff,"%s x%d",ShipsShort[(*iter)->Class].c_str(),army2->StackSize((*iter)->Class));
				_InfoArea.DrawLine(buff);
			}
			else
				_InfoArea.DrawLine(_Info.UnitInfo(*iter,army2));
		}
		//tunit = tunit->next;
	}
}
void InfoArea::clear(){
	PowVec<NodePath>* tnode = nodes;
	row = 0;
	if (tnode == 0)
		return;
	while (tnode!=0){
		tnode->elem->remove_node();
		tnode->elem = 0;
		tnode = tnode->next;
	}
	delete nodes;
	nodes = 0;
}
void InfoArea::DrawPlanets(const Event *ev, void *data){
	char buff[1024],buff2[1024];
	Player* pl;
	int j,k;
	_InfoArea.clear();
	pl = (Player*)data;
	int n = pl->GetNumber() - 1;


	//planets = pl->GetPlanetsList();
	_InfoArea.DrawLine("Untapped planets: ");
	//while (planets!=0){
	for (vector<Planet*>::iterator piter = pl->GetPlanetsList()->begin(); piter != pl->GetPlanetsList()->end(); piter++){
		//if ((planets->status==ps_open)||(planets->status==ps_opencaptured)){
		if (!(*piter)->HasState(psExhausted)){//Zoldn planet status change
			sprintf(buff2,"{%s}:%d/%d: ",(*piter)->GetName().c_str(),(*piter)->GetRes(),(*piter)->GetInf());
			if ((*piter)->GetSpecial() != st_ZERO){
				strcat(buff2,SpecialFull[(*piter)->GetSpecial()].c_str());
				strcat(buff2,":");
			}
			for (j=0;j<RaceTech;j++)
				if ((*piter)->GetBonus((TechTree)j)>0)
					for (k=0;k<(*piter)->GetBonus((TechTree)j);++k){
						strcat(buff2,TechColorShort[j].c_str());
						strcat(buff2,":");
					}
			_InfoArea.DrawLine(buff2);
		}
		//planets = planets->next;
	}

	//planets = pl->GetPlanetsList();
	_InfoArea.DrawLine("Tapped planets: ");
	//while (planets!=0){
	for (vector<Planet*>::iterator piter = pl->GetPlanetsList()->begin(); piter != pl->GetPlanetsList()->end(); piter++){
		//if ((planets->status==ps_exhausted)||(planets->status==ps_captured)){
		if ((*piter)->HasState(psExhausted)){//Zoldn planet status change
			sprintf(buff2,"{%s}:%d/%d: ",(*piter)->GetName().c_str(),(*piter)->GetRes(),(*piter)->GetInf());
			if ((*piter)->GetSpecial() != st_ZERO){
				strcat(buff2,SpecialFull[(*piter)->GetSpecial()].c_str());
				strcat(buff2,":");
			}
			for (j=0;j<RaceTech;j++)
				if ((*piter)->GetBonus((TechTree)j)>0)
					for (k=0;k<(*piter)->GetBonus((TechTree)j);++k){
						strcat(buff2,TechColorShort[j].c_str());
						strcat(buff2,":");
					}
			_InfoArea.DrawLine(buff2);
		}
		//planets = planets->next;
	}
}
void InfoArea::DrawPolitics(const Event *ev, void *data){
	char buff[1024];
	int i;
	deque<e_Politic*>::iterator temp,end;
	_InfoArea.clear();
	for (i = 0;i<_GameStats.GetPlayersNumber();++i){
		if (i != _GameStats.GetLocalPlayer()->GetNumber() - 1){
			sprintf(buff,"{%s} got %d politic cards",_Players[i]->GetName().c_str(),_Players[i]->_politics.size());
			_InfoArea.DrawLine(buff);
		}
	}
	temp = _GameStats.GetLocalPlayer()->_politics.begin();
	end = _GameStats.GetLocalPlayer()->_politics.end();
	_InfoArea.DrawLine("You got: ");
	while (temp!=end){
		PT(PGButton) button;
		sprintf(buff,"{%s}",(**temp).GetId().c_str());
		button = _InfoArea.DrawButton(buff);
		_Framework.define_key(button->get_click_event(MouseButton::one() ), "button press", &DrawRawText, &(*temp)->effect);
		++temp;
	}
}
void InfoArea::DrawTechs(const Event *ev, void *data){
	char buff[1024],buff2[1024];
	Player* pl;
	PT(PGButton) bt;
	int j,k;
	_InfoArea.clear();
	pl = (Player*)data;
	int n = pl->GetNumber() - 1;

	sprintf(buff,"Techs: ");
	for (j=0;j<MAX_TECH;++j)
		if (pl->GotTech((TechType)j)){
			bt = _InfoArea.DrawButton(_GameStats.GetTechDeck()->at(j)->GetName());//TechFull[j]
			_Framework.define_key(bt->get_click_event(MouseButton::one() ), "button press", &DrawRawText, (void*)&_GameStats.GetTechDeck( )->at(j)->description);
		}
}
void InfoArea::DrawActions(const Event *ev, void *data){
	char buff[1024];
	int i;
	list<GameEffect*>::iterator iter;
	_InfoArea.clear();
	for (i = 0;i<_GameStats.GetPlayersNumber();++i){
		if (i != _GameStats.GetLocalPlayer()->GetNumber() - 1){
			sprintf(buff,"{%s} got %d action cards",_Players[i]->GetName().c_str(),_Players[i]->GetActionsNumber());
			_InfoArea.DrawLine(buff);
		}
	}
	iter = _GameStats.GetLocalPlayer()->_PlayerGameEffect.begin();
	while (iter != _GameStats.GetLocalPlayer()->_PlayerGameEffect.end()){
		if ((*iter)->GetQ(eq_ActionCard)){
			PT(PGButton) button;
			sprintf(buff,"{%s}",((e_ActionCard*)(*iter))->GetId().c_str());
			button = _InfoArea.DrawButton(buff);
			_Framework.define_key(button->get_click_event(MouseButton::one() ), "button press", &DrawRawText, &((e_ActionCard*)(*iter))->_description);
		}
		iter++;
	}
}
void InfoArea::DrawObjectives(const Event *ev, void *data){
	list<e_Objective*>::iterator iter;
	Player * pl = _GameStats.GetLocalPlayer();
	char str[1024];
	_InfoArea.clear();
	//for (iter = pl->_PlayerObjectives.begin(); iter!=pl->_PlayerObjectives.end(); ++iter){
	for (list<GameEffect*>::iterator iter = pl->_PlayerGameEffect.begin(); iter != pl->_PlayerGameEffect.end(); iter++){
		if ((*iter)->GetQ(eq_Objective)){
			sprintf(str,"%s (%d VP)",((e_Objective*)(*iter))->GetReqs().c_str(),((e_Objective*)(*iter))->value);
			if (((e_Objective*)(*iter))->isFulfill)
				strcat(str,"[Fulfill]");
			if (((e_Objective*)(*iter))->isOpen)
				strcat(str,"[Open]");
			if (((e_Objective*)(*iter))->isDone)
				strcat(str,"[Done]");
			if (((e_Objective*)(*iter))->isSecret)
				strcat(str,"[Secret]");
			_InfoArea.DrawLine(str);
		}
	}
}
void InfoArea::DrawRawText(const Event *ev, void *data){
	string text = *(string*)data;
	_InfoArea.clear();
	_InfoArea.DrawLine(text);
	PT(PGButton) bt = _InfoArea.DrawButton(" - Back");
	_Framework.define_key(bt->get_click_event(MouseButton::one() ), "back", &ReDrawInfo, 0);
}
void InfoArea::SetNewPlayer(const Event *ev, void *data){
	((PGButton*)_InfoArea._playerbt[_InfoArea._pltoshow].get_node(0))->set_active(true);
	_InfoArea._pltoshow = *(int*)data;
	((PGButton*)_InfoArea._playerbt[_InfoArea._pltoshow].get_node(0))->set_active(false);
	_InfoArea.ReDrawInfo(0,0);
}
void InfoArea::SetNewInfo(const Event *ev, void *data){
	((PGButton*)_InfoArea._infobt[_InfoArea._inftoshow].get_node(0))->set_active(true);
	_InfoArea._inftoshow = *(InfoAreaShow*)data;
	((PGButton*)_InfoArea._infobt[_InfoArea._inftoshow].get_node(0))->set_active(false);
	_InfoArea.ReDrawInfo(0,0);
}
void InfoArea::ReDrawInfo(const Event *ev, void *data){
	switch (_InfoArea._inftoshow){
		case ias_diplomacy: _InfoArea.DrawPlayers(0,0);
			break;
		case ias_player: _InfoArea.DrawPlayer(0,_Players[_InfoArea._pltoshow]);
			break;
		case ias_planets: _InfoArea.DrawPlanets(0,_Players[_InfoArea._pltoshow]);
			break;
		case ias_techs: _InfoArea.DrawTechs(0,_Players[_InfoArea._pltoshow]);
			break;
		case ias_actions: _InfoArea.DrawActions(0,_Players[_InfoArea._pltoshow]);
			break;
		case ias_politics: _InfoArea.DrawPolitics(0,0);
			break;
		case ias_trades: _InfoArea.DrawTradeRoutes(0,0);
			break;
		case ias_objectives: _InfoArea.DrawObjectives(0,0);
			break;
		default: Eggog("InfoArea::ReDrawInfo got wrong infotoshow");
			break;
	}
}