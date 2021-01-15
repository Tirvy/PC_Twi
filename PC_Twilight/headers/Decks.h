template < typename T > class Deck{
	string id;
	PowVec<T> *cards;
	int number;
public:
	Deck();
	Deck(PowVec<T> * in_cards);
	~Deck();
	int GetNumber(); // Returns number of cards in deck
	void shuffle(); // Shuffles cards in deck
	int Add(PowVec<T> * in_cards); // returns 1. Adds cards to the end of deck
	PowVec<T> * PopFirst(int num=1); // First num cards are deleted from deck. A PowVec with deled cards returned
	PowVec<T> * GetList(); // returns cards. Stupid thing, better dont use.
	PowVec<T> * Choose(int num); // takes [num] card out of the deck
	PowVec<T> * Copy(int num); // takes [num] card out of the deck
	int FindById(string str); // returns the number of a card with same id.
	int OrderById(); // orders cards by their id.
};