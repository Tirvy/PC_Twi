
int CheatMachine::UseCheat(string line){
	string elem;
	istringstream iss;
	iss.str(line);
	iss >> elem;
	if (elem.compare(cheat_giveme) == 0){
		iss>>elem;
		LoadEffect(elem, _Players[_Interface.GetCurrPlayer()]);
	}
	else if (elem.compare(cheat_givemeac) == 0){
	}
	else if (elem.compare(cheat_givemepc) == 0){
	}
	else if (elem.compare(cheat_givemecc) == 0){
	}
	else if (elem.compare(cheat_givemetech) == 0){
	}
	else if (elem.compare(cheat_endgame) == 0){
	}
	return 1;
}