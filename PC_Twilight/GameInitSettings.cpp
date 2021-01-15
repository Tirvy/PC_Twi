struct GameInitSettings{
	int PlayersNumber, VPs, Speaker, RandSeed, Mapfile, Loadfile;
	bool Save;
	vector<string> PlayerNames;
	vector<int> PlayerRaces;
	vector<int> PlayerColors;
	vector<int> PlayersCons;
	string MapName, GalName;

	GameInitSettings();
	//GameInitSettings(const GameInitSettings & insets);
	void Import(const GameInitSettings & insets);
	void SetPlayerNumber(int n);
};

GameInitSettings::GameInitSettings(){
	PlayerNames.clear();
	PlayerRaces.clear();
	PlayersCons.clear();
	PlayerColors.clear();
	MapName = string(PATH_TO_DATA) + "map4p.tws";
	GalName = string(PATH_TO_DATA) + "gal4p.tws";
	VPs = 9;
	Speaker = -1;
	PlayersNumber = 0;
	Loadfile = 0;
	Mapfile = 0;
	Save = false;
}
void GameInitSettings::Import(const GameInitSettings & insets){
	PlayersNumber = insets.PlayersNumber;
	VPs = insets.VPs;
	Speaker = insets.Speaker;
	RandSeed = insets.RandSeed;
	Loadfile = insets.Loadfile;
	Mapfile = insets.Mapfile;
	Save = insets.Save;
	PlayerNames.resize(PlayersNumber);
}
void GameInitSettings::SetPlayerNumber(int n){
	PlayersNumber = n;
	PlayerNames.clear();
	PlayerRaces.clear();
	PlayersCons.clear();
	PlayerColors.clear();
	for (int i = 0; i<n; ++i){
		PlayerNames.push_back(string());
		PlayerRaces.push_back(RacesType(0));
		PlayerColors.push_back(i);
		PlayersCons.push_back(-1);
	}
}