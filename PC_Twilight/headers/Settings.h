

class Settings{
	int players;
	//races
	int red_tiles, empty_tiles, planet_tiles, remove_tiles;
	int tiles_per_player;
	int* PlayerHomeSystems;
public:	
	Settings();
	Settings(int in_players);
	int num_players(); // returns number of players
	int GetSysNumber(SystemType ST); // number of red,empty,planetary tiles needed to construct map
	int GetHSCoords(int player, int* x, int* y); // make x and y coords of players HomeSystem
	friend class MapTranslator;
}
_Settings;