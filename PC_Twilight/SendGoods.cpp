
//backup
class e_SendGoods:public GameEffect{
public:
	e_SendGoods(){
		//nt_strload(id,"Tactical Action\0");
		id = "SendGoods";
		image=GOODS_IMG;
	}
	bool GetQ(GameEffectQs queue){
		if (queue==eq_AAA)
			return true;
		return false;
	}
	GameEffectRets Execute(ExecuteParams EP){
		int i,sum;
		vector<int> ret;
		ostringstream ss;
		ss<<"Gifts of Goods. You have "<<EP.player->GetGoods()<<" goods";
		_GrIn.InitChoise(ss.str(),true,true,true);
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			if (_Players[i] != EP.player)
				_GrIn.AddNumerical(_Players[i]->GetBanner(),_Players[i]->GetName());
		}
		ret = _GrIn.LaunchChoise();
		if (ret.size() == 0)
			return er_none;
		sum = 0;
		for (i=0;i<_GameStats.GetPlayersNumber()-1;++i)
			sum += ret[i];
		if (sum > EP.player->GetGoods())
			_Interface.PrintThingPlayer(EP.player->GetNumber()-1,"Dont have dem goods");
		ss.str("");
		//ss<<"{"<<EP.player->GetName()<<"} sends "<<ret[i]<<" goods to {"<<_Players[i]->GetName()<<"}";
		//_Interface.PrintThingAll(ss.str());
		EP.player->TakeGoods(sum);
		for (i=0;i<_GameStats.GetPlayersNumber();++i){
			if (i < EP.player->GetNumber()-1)
				_Players[i]->GiveGoods(ret[i]);
			if (i > EP.player->GetNumber()-1)
				_Players[i]->GiveGoods(ret[i-1]);
		}
		return er_none;
	}
	GameEffect* Clone(){
		return new e_SendGoods(*this);
	}
	string Save(){
		return string();
	}
	void Load(string str){}
};