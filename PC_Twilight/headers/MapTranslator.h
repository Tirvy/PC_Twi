class MapTranslator{
	FILE * fi;
	char buffer[127];
	static const char c_Players[];
	static const char c_Systems[];
	static const char c_Red[];
	static const char c_Empty[];
	static const char c_Planet[];
	static const char c_Remove[];
	static const char c_Diameter[];
	static const char c_MakeMaph[];
	static const char c_CloseMaph[];
	static const char c_MakeMapv[];
	static const char c_CloseMapv[];
public:
	MapTranslator();
	int translate(string filepath, Map * tehmap, Settings *tehset);
}
_MapTranslator;