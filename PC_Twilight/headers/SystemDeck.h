class SystemDeck:public Deck<Hex>{
	string id;
	PowVec<Hex> *cards;
	int number;
public:
	SystemDeck();
	SystemDeck(PowVec<Hex> * in_cards); // Makes a Deck from these cards
	~SystemDeck();
	int GetNumber(); // Returns number of cards in deck
	void shuffle(); // Shuffles cards in deck
	int Add(PowVec<Hex> * in_cards); // returns 1.: Adds cards to the end of deck
	PowVec<Hex> * PopFirst(int num=1); // First num cards are deleted from deck. A PowVec with deled cards returned
	PowVec<Hex> * GetList(); // returns cards. Stupid thing, better dont use.
	PowVec<Hex> * Choose(int num); // takes [num] card out of the deck
	PowVec<Hex> * Copy(int num); // takes [num] card out of the deck
	int FindById(string str); // returns the number of a card with same id.
	int OrderById(); // orders cards by their id.
	friend class SystemTranslator;
};