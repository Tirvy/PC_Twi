class InputString{
	NodePath _desc,_str;
	PT(PGEntry) _dstr;
public:
	InputString();
	InputString(const InputString& tocopy);
	~InputString();
	void SetName(string name);
	void SetPos(float x, float y, float scale);
	void SetString(string name);
	void Activate();
	void Deactivate();
	string GetAsString();
	int GetAsNumber();
	void Draw();
};