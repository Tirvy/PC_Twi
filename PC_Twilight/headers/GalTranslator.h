class GalTranslator{
	FILE * fi;
	char buffer[256];
	static const char c_Players[];
	SystemDeck *alldeck;
public:
	GalTranslator();
	int translate(string filepath, Map * tehmap, Settings *tehset);
	int translate(const string buffer, int cury, int num);
};