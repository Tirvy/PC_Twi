class Hex{
	string id;
	Planet* planets[MAX_PLANETS];
	WormholeType portal[4];
	bool actmarkers[MAX_PLAYERS];
	DangerType danger;
	LinkedHexes neighboors;	//ZoldnMap
public:
	Hex();
	string GetId();
	Planet* GetPlanet(int number);
	bool GotPortal(WormholeType p);
	DangerType GetDanger();
	bool GetCoords(int* x,int* y);
	bool SetCC(int x);//X - � �������!
	bool GotCC(int x);//X - � �������!
	int ClearCCs(int numb = 0);//�� ��������� - ������� ���, ���� ������ ����� ������ (� 1!), �� ������ ���
	friend class SystemTranslator;
	friend class Map;

	void SetId(string name);
	LinkedHexes* GetLinkedHexes();	//ZoldnMap
	int xc,yc;	//ZoldnMap
	int number;
};