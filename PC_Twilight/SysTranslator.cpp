
SystemTranslator::SystemTranslator(){
}
int SystemTranslator::translate(string filepath, SystemDeck ** toform){
	int i;
	int StringNumber = 0, WormHoleNumber = -1, PlanetNumber = -1;
	PowVec<Hex> *temp = 0;
	bool flag = false, inplanet = false;
	PowVec<Hex> *first = 0;
	if ((fi = fopen(filepath.c_str(), "rt"))==0)
		throw throwable("Cant open file to read ",filepath.c_str());
	while (( !feof(fi) )&&( fgets(buffer, 100 , fi)!=0 )){
		++StringNumber;
		i=0;
		while ((buffer[i]==' ')||(buffer[i]==9))
			++i;
		if ((buffer[i] == '#')||(buffer[i] == '\n'))
			continue;
		//++i;
		if ((nt_streq(c_MakeSystem, &(buffer[i]) )) == nt_strlen(c_MakeSystem)){
			if (flag)
				throw throwable(filepath,"MakeSystem",StringNumber);
			flag = true;
			inplanet = false;
			if (temp == 0){
				temp = new PowVec<Hex>;
				first = temp;
			}
			else{
				temp->next = new PowVec<Hex>;
				temp = temp->next;
			}
			temp->elem = new Hex;
			continue;
		}
		if ((nt_streq(c_CloseSystem, &(buffer[i]) )) == nt_strlen(c_CloseSystem)){
			if (!flag)
				throw throwable(filepath,"CloseSystem",StringNumber);
			flag = false;
			WormHoleNumber = -1;
			PlanetNumber = -1;
			continue;
		}
		if (((nt_streq(c_GetId, &(buffer[i]) )) == nt_strlen(c_GetId))&&(!inplanet)){
			if (temp == 0)
				throw throwable(filepath,"GetId",StringNumber);
			nt_roll (buffer, &i, '=');
			nt_strload(temp->elem->id, &buffer[i]);
			continue;
		}
		if ((nt_streq(c_GetImage, &(buffer[i]) )) == nt_strlen(c_GetImage)){
			if (temp == 0)
				throw throwable(filepath,"GetImage",StringNumber);
			continue;
		}
		if ((nt_streq(c_GetDanger, &(buffer[i]) )) == nt_strlen(c_GetDanger)){

			if (temp == 0)
				throw throwable(filepath,"GetDanger",StringNumber);
			nt_roll (buffer, &i, '=');
			if ((nt_streq(c_DangerAsteroids, &(buffer[i]) )) == nt_strlen(c_DangerAsteroids))
				temp->elem->danger = Asteroids;
			else if ((nt_streq(c_DangerIonStorm, &(buffer[i]) )) == nt_strlen(c_DangerIonStorm))
				temp->elem->danger = IonStorm;
			else if ((nt_streq(c_DangerSupernova, &(buffer[i]) )) == nt_strlen(c_DangerSupernova))
				temp->elem->danger = Supernova;
			else if ((nt_streq(c_DangerNebula, &(buffer[i]) )) == nt_strlen(c_DangerNebula))
				temp->elem->danger = Nebula;
			else if ((nt_streq(c_DangerGravityRift, &(buffer[i]) )) == nt_strlen(c_DangerGravityRift))
				temp->elem->danger = GravityRift;
			else 
				throw throwable(filepath,"GetDanger2",StringNumber);
			continue;
		}
		if ((nt_streq(c_MakeWormHole, &(buffer[i]) )) == nt_strlen(c_MakeWormHole)){
			if (temp == 0)
				throw throwable(filepath,"MakeWormHole",StringNumber);
			++WormHoleNumber;
			continue;
		}
		if ((nt_streq(c_GetWormHoleType, &(buffer[i]) )) == nt_strlen(c_GetWormHoleType)){
			if ((temp == 0)||( WormHoleNumber== -1 )||( WormHoleNumber== 4 ))
				throw throwable(filepath,"GetWormHoleType",StringNumber);
			nt_roll(buffer, &i, '=');
			if ((nt_streq(c_WormHoleTypeA, &(buffer[i]) )) == nt_strlen(c_WormHoleTypeA))
				temp->elem->portal[WormHoleNumber] = wh_A;
			else if ((nt_streq(c_WormHoleTypeB, &(buffer[i]) )) == nt_strlen(c_WormHoleTypeB))
				temp->elem->portal[WormHoleNumber] = wh_B;
			else if ((nt_streq(c_WormHoleTypeC, &(buffer[i]) )) == nt_strlen(c_WormHoleTypeC))
				temp->elem->portal[WormHoleNumber] = wh_C;	//Zoldn fix copypaste error
			else if ((nt_streq(c_WormHoleTypeD, &(buffer[i]) )) == nt_strlen(c_WormHoleTypeD))
				temp->elem->portal[WormHoleNumber] = wh_D;	//Zoldn fix copypaste error
			else 
				throw throwable(filepath,"GetWormHoleType2",StringNumber);
			continue;
		}
		if ((nt_streq(c_CloseWormHole, &(buffer[i]) )) == nt_strlen(c_CloseWormHole)){
			if (temp == 0)
				throw throwable(filepath,"CloseWormHole",StringNumber);
			continue;
		}
		if ((nt_streq(c_MakePlanet, &(buffer[i]) )) == nt_strlen(c_MakePlanet)){
			if ((temp == 0)||( PlanetNumber== 3 ))
				throw throwable(filepath,"MakePlanet",StringNumber);
			inplanet = true;
			++PlanetNumber;
			temp->elem->planets[PlanetNumber] = new Planet;
			temp->elem->planets[PlanetNumber]->_location = temp->elem;
			continue;
		}
		if ((nt_streq(c_ClosePlanet, &(buffer[i]) )) == nt_strlen(c_ClosePlanet)){
			inplanet = false;
			continue;
		}
		if ((nt_streq(c_GetPlanetId, &(buffer[i]) )) == nt_strlen(c_GetPlanetId)){
			if ((temp == 0)||( PlanetNumber== 3 )||( PlanetNumber== -1 ))
				throw throwable(filepath,"GetPlanetId",StringNumber);
			nt_roll (buffer, &i, '=');
			nt_strload(temp->elem->planets[PlanetNumber]->_id, &buffer[i]);
			continue;
		}
		if ((nt_streq(c_GetPlanetProduction, &(buffer[i]) )) == nt_strlen(c_GetPlanetProduction)){
			if ((temp == 0)||( PlanetNumber== 3 )||( PlanetNumber== -1 ))
				throw throwable(filepath,"GetPlanetProduction",StringNumber);
			nt_roll (buffer, &i, '=');
			temp->elem->planets[PlanetNumber]->_rescap = (buffer[i]-'0');
			continue;
		}
		if ((nt_streq(c_GetPlanetInfluence, &(buffer[i]) )) == nt_strlen(c_GetPlanetInfluence)){
			if ((temp == 0)||( PlanetNumber== 3 )||( PlanetNumber== -1 ))
				throw throwable(filepath,"GetPlanetInfluence",StringNumber);
			nt_roll (buffer, &i, '=');
			temp->elem->planets[PlanetNumber]->_infcap = (buffer[i]-'0');
			continue;
		}
		if ((nt_streq(c_GetPlanetColor, &(buffer[i]) )) == nt_strlen(c_GetPlanetColor)){
			if ((temp == 0)||( PlanetNumber== 3 )||( PlanetNumber== -1 ))
				throw throwable(filepath,"GetPlanetColor",StringNumber);
			nt_roll (buffer, &i, '=');
			if ((nt_streq(c_PlanetColorRed, &(buffer[i]) )) == nt_strlen(c_PlanetColorRed))
				temp->elem->planets[PlanetNumber]->_rtech = 1;
			else if ((nt_streq(c_PlanetColorBlue, &(buffer[i]) )) == nt_strlen(c_PlanetColorBlue))
				temp->elem->planets[PlanetNumber]->_btech = 1;
			else if ((nt_streq(c_PlanetColorGreen, &(buffer[i]) )) == nt_strlen(c_PlanetColorGreen))
				temp->elem->planets[PlanetNumber]->_gtech = 1;
			else if ((nt_streq(c_PlanetColorYellow, &(buffer[i]) )) == nt_strlen(c_PlanetColorYellow))
				temp->elem->planets[PlanetNumber]->_ytech = 1;
			else 
				throw throwable(filepath,"GetPlanetColor2",StringNumber);
			continue;
		}
		if ((nt_streq(c_GetPlanetTechpower, &(buffer[i]) )) == nt_strlen(c_GetPlanetTechpower)){
			if ((temp == 0)||( PlanetNumber== 3 )||( PlanetNumber== -1 ))
				throw throwable(filepath,"GetPlanetTechpower",StringNumber);
			nt_roll (buffer, &i, '=');
			if (buffer[i]!='1'){
				if (temp->elem->planets[PlanetNumber]->_rtech == 1)
					temp->elem->planets[PlanetNumber]->_rtech = buffer[i]-'0';
				if (temp->elem->planets[PlanetNumber]->_btech == 1)
					temp->elem->planets[PlanetNumber]->_btech = buffer[i]-'0';
				if (temp->elem->planets[PlanetNumber]->_gtech == 1)
					temp->elem->planets[PlanetNumber]->_gtech = buffer[i]-'0';
				if (temp->elem->planets[PlanetNumber]->_ytech == 1)
					temp->elem->planets[PlanetNumber]->_ytech = buffer[i]-'0';
			}
			continue;
		}
		if ((nt_streq(c_GetPlanetSpecial, &(buffer[i]) )) == nt_strlen(c_GetPlanetSpecial)){
			if ((temp == 0)||( PlanetNumber== 3 )||( PlanetNumber== -1 ))
				throw throwable(filepath,"GetPlanetSpecial",StringNumber);
			nt_roll (buffer, &i, '=');
			if ((nt_streq(c_PlanetSpecialST, &(buffer[i]) )) == nt_strlen(c_PlanetSpecialST))
				temp->elem->planets[PlanetNumber]->_Special = ShockTroops;
			else if ((nt_streq(c_PlanetSpecialF, &(buffer[i]) )) == nt_strlen(c_PlanetSpecialF))
				temp->elem->planets[PlanetNumber]->_Special = Fighters;
			else if ((nt_streq(c_PlanetSpecialGF, &(buffer[i]) )) == nt_strlen(c_PlanetSpecialGF))
				temp->elem->planets[PlanetNumber]->_Special = GroundForces;
			else if ((nt_streq(c_PlanetSpecialS, &(buffer[i]) )) == nt_strlen(c_PlanetSpecialS))
				temp->elem->planets[PlanetNumber]->_Special = TradeStation;
			else 
				throw throwable(filepath,"GetPlanetSpecial2",StringNumber);
			continue;
		}
	}
	(*toform) = new SystemDeck(first);
	fclose(fi);
	return 1;
}


const char SystemTranslator::c_MakeSystem[] = "[SystemCard";
const char SystemTranslator::c_CloseSystem[] = "[/SystemCard";
const char SystemTranslator::c_GetId[] = "id";
const char SystemTranslator::c_GetImage[] = "image";
const char SystemTranslator::c_GetDanger[] = "danger";
const char SystemTranslator::c_DangerAsteroids[] = "Asteroids";
const char SystemTranslator::c_DangerIonStorm[] = "IonStorm";
const char SystemTranslator::c_DangerSupernova[] = "Supernova";
const char SystemTranslator::c_DangerNebula[] = "Nebula";
const char SystemTranslator::c_DangerGravityRift[] = "GravityRift";
const char SystemTranslator::c_MakeWormHole[] = "[wormhole";
const char SystemTranslator::c_CloseWormHole[] = "[/wormhole";
const char SystemTranslator::c_GetWormHoleType[] = "type";
const char SystemTranslator::c_WormHoleTypeA[] = "A";
const char SystemTranslator::c_WormHoleTypeB[] = "B";
const char SystemTranslator::c_WormHoleTypeC[] = "C";
const char SystemTranslator::c_WormHoleTypeD[] = "D";
const char SystemTranslator::c_MakePlanet[] = "[planet";
const char SystemTranslator::c_ClosePlanet[] = "[/planet";
const char SystemTranslator::c_GetPlanetId[] = "id";
const char SystemTranslator::c_GetPlanetProduction[] = "production";
const char SystemTranslator::c_GetPlanetInfluence[] = "influence";
const char SystemTranslator::c_GetPlanetColor[] = "techcolour";
const char SystemTranslator::c_PlanetColorRed[] = "red";
const char SystemTranslator::c_PlanetColorBlue[] = "blue";
const char SystemTranslator::c_PlanetColorGreen[] = "green";
const char SystemTranslator::c_PlanetColorYellow[] = "yellow";
const char SystemTranslator::c_GetPlanetTechpower[] = "techquantity";
const char SystemTranslator::c_GetPlanetSpecial[] = "special";
const char SystemTranslator::c_PlanetSpecialST[] = "ShockTroops";
const char SystemTranslator::c_PlanetSpecialF[] = "Fighters";
const char SystemTranslator::c_PlanetSpecialGF[] = "GroundForces";
const char SystemTranslator::c_PlanetSpecialS[] = "Station";

