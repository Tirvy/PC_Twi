

GraphicInterface::GraphicInterface(){
	inited = false;
	launched = false;
	timed = false;
	timeleft = 0;
	system = false;
	passed = false;
	LastPlayer = -1;
}
void GraphicInterface::InitChoise(const string in_descr, bool pass_in, bool cnf_in, bool numer_in){
	if (launched)
		throw throwable("fayol - init");
	inited = true;
	timed = false;
	descr = in_descr;
	chopt = AskStruct(pass_in, cnf_in, numer_in);
}
void GraphicInterface::AddOption(const string pathtoimage, const string in_descr){
	InOption option;
	option.descr=in_descr;
	option.texture=pathtoimage;
	chopt.options.push_back(option);
}
void GraphicInterface::AddNumerical(const string pathtoimage, const string in_descr, int standart, int max){
	InOption option;
	(option.descr=in_descr);
	(option.texture=pathtoimage);
	option.currvalue = standart;
	option.maxvalue = max;
	chopt.options.push_back(option);
}
vector<int> GraphicInterface::LaunchChoise(){
	launched = true;
	passed = false;
	vector<int> ret;
	ErNetDatagram tosnd;
	if (_Replay.size() != 0){
		ret = _Replay[0];
		_Replay.pop_front();
		inited = false;
		launched = false;
	}
	else if (_Players[_Interface.GetCurrPlayer()]->GetConnection() == -1){
		if (LastPlayer != _Interface.GetCurrPlayer()){
			SND_YOUR_TURN->play();
			LastPlayer = _Interface.GetCurrPlayer();
		}
		cout<<"Geting local feedback from player "<<_Interface.GetCurrPlayer()<<endl;
		_ActionArea.LaunchOptions(descr,chopt);
		while (!_ActionArea.done)
			taskMgr->poll();
		inited = false;
		launched = false;
		if (passed)
			ret = vector<int>();
		else
			ret = _ActionArea.values;
		if (ret.size()!=0)
			tosnd = ErNetDatagram((void*)&(ret[0]),sizeof(int)*ret.size());
		else
			tosnd = ErNetDatagram(0,0);
		for (int i=0;i<_GameStats.GetPlayersNumber();++i)
			if (_Players[i]->GetConnection() >= 0)
				_NeCo.SendMsg(tosnd,_Players[i]->GetConnection());
	}
	else{
		cout<<"Waiting feedback from "<<_Players[_Interface.GetCurrPlayer()]->GetConnection()<<" connection"<<endl;
		while (_NeCo.messages.size() == 0)
			taskMgr->poll();
		inited = false;
		launched = false;
		ret = _NeCo.messages[0].GetDataAsVector();
		_NeCo.messages.pop_front();
	}
	return ret;
}
vector<int> GraphicInterface::SysChoise(const string in_descr, bool pass_in){
	system = true;
	passed = false;
	ErNetDatagram tosnd;
	vector<int> ret;
	ret.clear();
	if (_Replay.size() != 0){
		ret = _Replay[0];
		_Replay.pop_front();
		inited = false;
		launched = false;
	}
	else if (_Players[_Interface.GetCurrPlayer()]->GetConnection() == -1){
		if (LastPlayer != _Interface.GetCurrPlayer()){
			SND_YOUR_TURN->play();
			LastPlayer = _Interface.GetCurrPlayer();
		}
		cout<<"Geting local feedback from player "<<_Interface.GetCurrPlayer()<<endl;
		_ActionArea.LaunchOptions(in_descr,AskStruct(pass_in));
		while ((system)&&(!_ActionArea.done))
			taskMgr->poll();
		if (!_ActionArea.done)
			_ActionArea.ClearArea();
		if (passed)
			ret.clear();
		else{
			ret.push_back(x);
			ret.push_back(y);
		}
		if (ret.size()!=0)
			tosnd = ErNetDatagram((void*)&(ret[0]),sizeof(int)*ret.size());
		else
			tosnd = ErNetDatagram(0,0);
		for (int i=0;i<_GameStats.GetPlayersNumber();++i)
			if (_Players[i]->GetConnection() >= 0){
				if (ret.size()!=0)
					_NeCo.SendMsg(ErNetDatagram((void*)&(ret[0]),sizeof(int)*ret.size()),_Players[i]->GetConnection());
				else
					_NeCo.SendMsg(ErNetDatagram(0,0),_Players[i]->GetConnection());
			}
	}
	else{
		cout<<"Waiting feedback from "<<_Players[_Interface.GetCurrPlayer()]->GetConnection()<<" connection"<<endl;
		while (_NeCo.messages.size() == 0)
			taskMgr->poll();
		inited = false;
		launched = false;
		ret = _NeCo.messages[0].GetDataAsVector();
		_NeCo.messages.pop_front();
	}
	return ret;
}