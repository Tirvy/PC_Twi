
MapTranslator::MapTranslator(){
}
int MapTranslator::translate(string filepath, Map * tehmap, Settings *tehset){
	int i;
	int curx, cury, total = 0, k = 0;
	int StringNumber = 0;
	char inmap = 0;
	bool inited = false;
	PowVec<Hex> *first = 0;
	if ((fi = fopen(filepath.c_str(), "rt"))==0)
		throw throwable("MapTranslator::translate Cant open file to read ",filepath.c_str());
	while (( !feof(fi) )&&( fgets(buffer, 100 , fi)!=0 )){
		++StringNumber;
		i=0;
		while ((buffer[i]==' ')||(buffer[i]==9))
			++i;
		if ((buffer[i] == '#')||(buffer[i] == '\n'))
			continue;
		//++i;
		if ((nt_streq(c_Players, &(buffer[i]) )) == nt_strlen(c_Players)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			tehset->players = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_Systems, &(buffer[i]) )) == nt_strlen(c_Systems)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			total = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_Diameter, &(buffer[i]) )) == nt_strlen(c_Diameter)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			k = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_Red, &(buffer[i]) )) == nt_strlen(c_Red)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			tehset->red_tiles = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_Empty, &(buffer[i]) )) == nt_strlen(c_Empty)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			tehset->empty_tiles = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_Planet, &(buffer[i]) )) == nt_strlen(c_Planet)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			tehset->planet_tiles = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_Remove, &(buffer[i]) )) == nt_strlen(c_Remove)){
			if (inmap!=0)
				throw throwable(filepath,StringNumber);
			nt_roll (buffer, &i, '=');
			tehset->remove_tiles = nt_tonumber(&buffer[i]);
			continue;
		}
		if ((nt_streq(c_MakeMaph, &(buffer[i]) )) == nt_strlen(c_MakeMaph)){
			if ((inmap!=0)||(k==0)||(total==0))
				throw throwable(filepath,StringNumber);
			inmap = 1;
			tehmap->Initialize(total,k);
			inited = true;
			curx = -(k-1)/2;
			cury = -(k-1)/2;
			continue;
		}
		if ((nt_streq(c_MakeMapv, &(buffer[i]) )) == nt_strlen(c_MakeMapv)){
			if ((inmap!=0)||(k==0)||(total==0))
				throw throwable(filepath,StringNumber);
			inmap = -1;
			tehmap->Initialize(total,k);
			inited = true;
			curx = -(k-1)/2;
			cury = -(k-1)/2;
			continue;
		}
		if ((nt_streq(c_CloseMaph, &(buffer[i]) )) == nt_strlen(c_CloseMaph)){
			if ((inmap!=1)||(k==0)||(total==0))
				throw throwable(filepath,StringNumber);
			inmap = 2;
			continue;
		}
		if ((nt_streq(c_CloseMapv, &(buffer[i]) )) == nt_strlen(c_CloseMapv)){
			if ((inmap!=-1)||(k==0)||(total==0))
				throw throwable(filepath,StringNumber);
			inmap = -2;
			continue;
		}
		if (inmap==1){
			while (buffer[i]!='\n'){
				if (((buffer[i]>='0')&&(buffer[i]<='9')) || (buffer[i]=='-') || ((buffer[i]<='z')&&(buffer[i]>='a')) || ((buffer[i]<='Z')&&(buffer[i]>='A'))){
					//tehmap->SetRoundh(curx,cury,buffer[i]);
					++curx;
				}
				++i;
			}
			if (curx!=((k-1)/2) + 1)
				throw throwable("MapTranslator::translate - unexpected end of line",StringNumber);
			++cury;
			curx = -((k-1)/2);
			continue;
		}
		if (inmap==-1){
			while (buffer[i]!='\n'){
				if (((buffer[i]>='0')&&(buffer[i]<='9')) || (buffer[i]=='-') || ((buffer[i]<='h')&&(buffer[i]>='a'))){
					//tehmap->SetRoundv(curx,cury,buffer[i]);
					++curx;
				}
				++i;
			}
			if (curx<((k-1)/2))
				throw throwable("MapTranslator::translate - unexpected end of line",StringNumber);
			++cury;
			curx = -((k-1)/2);
			continue;
		}
	}
	if (!inited)
		throw throwable("MapTranslator::translate = not inited");
	return 1;
}
/*int MapTranslator::translate(string filepath, Map * tehmap, Settings *tehset){
	char map4p[] = "-3333---a222b-321123-3210123321123--d222c--3333--";
	unsigned int i;
	tehset->players = 4; 
	tehset->red_tiles = 4;
	tehset->empty_tiles = 8;
	tehset->planet_tiles = 20;
	tehmap->Initialize(37,7);
	for (i=0;i<strlen(map4p);++i){
		tehmap->SetRoundh((i%7)-3,3-(i/7),map4p[i]);
	}
	return 1;
}*/

const char MapTranslator::c_Players[] = "players";
const char MapTranslator::c_Systems[] = "totalsystems";
const char MapTranslator::c_Red[] = "red";
const char MapTranslator::c_Empty[] = "empty";
const char MapTranslator::c_Planet[] = "planet";
const char MapTranslator::c_Remove[] = "remove";
const char MapTranslator::c_Diameter[] = "diameter";
const char MapTranslator::c_MakeMaph[] = "[maph";
const char MapTranslator::c_CloseMaph[] = "[/maph";
const char MapTranslator::c_MakeMapv[] = "[mapv";
const char MapTranslator::c_CloseMapv[] = "[/mapv";