void BuildGalaxy(){
	ZoldnMapTranslator _ZoldnMapTranslator(&_Map);
	if (_GameStats._IsManualCreation){
		_ZoldnMapTranslator.CreateDecksForPlayers();
		_ZoldnMapTranslator.ManualGalaxyBuild();
	}
}