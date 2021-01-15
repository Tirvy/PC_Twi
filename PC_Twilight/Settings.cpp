
Settings::Settings(){
}
Settings::Settings(int in_players){
	players = in_players;
	PlayerHomeSystems = new int[2*players];
}
int Settings::num_players(){
	return players;
}
int Settings::GetSysNumber(SystemType ST){
	switch(ST){
		case RedSys:return red_tiles;
		case EmptySys:return empty_tiles;
		case PlanetSys:return planet_tiles;
		default: throw throwable("Settings::GetSysNumber bad system");
	}
	return red_tiles;
}
int Settings::GetHSCoords(int player, int* x, int* y){
	if (player > players)
		throw throwable("Settings::GetHSCoords - Player is out of reach");
	*x = PlayerHomeSystems[2*player];
	*y = PlayerHomeSystems[2*player+1];
	return 1;
}