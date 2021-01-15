#define SSTR( x ) dynamic_cast< std::ostringstream & >(( std::ostringstream() << std::dec << x ) ).str()

bool _ClearReplay = true;
ofstream _ReplayStream;
string _ReplayName = "..\\Release\\data\\replays\\Replay.tws";
deque<vector<int>> _Replay;

void ToReplay(string str){
	if (_ClearReplay){
		time_t t = time(0);
		tm *now = localtime( & t );
		_ReplayName = string("..\\Release\\data\\replays\\Replay-")+SSTR(now->tm_yday)+'-'+SSTR(now->tm_min)+'-'+SSTR(now->tm_hour) + ".twr";
		_ReplayStream.open(_ReplayName.c_str());
		if (!_ReplayStream.is_open())
			Eggog(_ReplayName + "cant be opened");
		_ReplayStream << _GameStats._random_seed << endl;
		_ReplayStream << str << endl;
		_ReplayStream.close();
		_ClearReplay = false;
	}
	else{
		_ReplayStream.open(_ReplayName.c_str(), std::ios_base::out | std::ios_base::app );
		if (!_ReplayStream.is_open())
			Eggog(_ReplayName + "cant be opened");
		_ReplayStream << str << endl;
		_ReplayStream.close();
	}
}

void LoadReplay(string from, GameInitSettings* InitS){
	string line;
	ifstream myfile(from.c_str());
	istringstream ss;
	vector<int> buff;
	int t;
	Log("Loading replay! ---------------------------------- :");
	_Replay.clear();
	_ClearReplay = false;
	if (myfile.is_open()){
		getline(myfile,line);
		ss.clear();
		ss.str(line);
		ss >> t;
		InitS->RandSeed = t;
		while (getline(myfile,line)){
			buff.clear();
			ss.clear();
			ss.str(line);
			ss >> t;
			while (!ss.eof()){
				buff.push_back(t);
				ss >> t;
			}
			_Replay.push_back(buff);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}