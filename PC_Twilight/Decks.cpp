template < typename T > 
Deck<T>::Deck(){
	id = "";
	cards = 0;
	number = 0;
}
template < typename T > 
Deck<T>::Deck(PowVec<T> * in_cards){
	id = 0;
	cards = 0;
	number = 0;
	Add(in_cards);
}
template < typename T > 
Deck<T>::~Deck(){
	if (cards != 0)
		delete cards;
}
template < typename T > 
int Deck<T>::GetNumber(){
	return number;
}
template < typename T > 
void Deck<T>::shuffle(){
	int i,temp,tempnum;
	PowVec<T> * newstart;
	tempnum = number;
	if (number == 0)
		throw throwable("SystemDeck::shuffle() - empty Deck ");
	temp = nt_rand(number);
	newstart = &(*cards)[temp];
	if (temp == 0)
		cards = ((*cards).next);
	else 
		(*cards)[temp-1].next = (*cards)[temp].next;
	newstart->next = 0;
	for (i=1; i<number;  ++i){
		temp = nt_rand(number - i);
		(*newstart)[i-1].next;
		(*newstart)[i-1].next = &(*cards)[temp];
		if (temp == 0)
			cards = ((*cards).next);
		else 
			(*cards)[temp-1].next = (*cards)[temp].next;
		(*newstart)[i].next = 0;
	}
	cards = newstart;
}
template < typename T > 
int Deck<T>::Add(PowVec<T> * in_cards){
	PowVec<T>* temp;
	if (number == 0)
		cards = in_cards;
	else
		(*cards) += in_cards;
	number = 0;
	temp = cards;
	while (temp!=0){
		++number;
		temp = temp->next;
	}
	return 1;
}
template < typename T > 
PowVec<T> * Deck<T>::PopFirst(int num){
	PowVec<T> * RetValue;
	if ( num > number )
		throw throwable("SystemDeck::PopFirst - num > number");
	if ( num <= 0)
		throw throwable("SystemDeck::PopFirst - num <= 0");
	RetValue = cards;
	cards = (*cards)[num-1].next;
	(*RetValue)[num-1].next = 0;
	number = number - num;
	//Add(0);
	return RetValue;
}
template < typename T > 
PowVec<T> * Deck<T>::GetList(){
	return cards;
}
template < typename T > 
PowVec<T> * Deck<T>::Choose(int num){
	PowVec<T> * RetValue;
	if (( num > number )||( num < 1))
		throw throwable("SystemDeck::Choose - num > number or < 1");
	RetValue = &((*cards)[num-1]);
	if ( num > 1 )
		(*cards)[num-2].next = ((*cards)[num-1]).next;
	else
		cards = cards->next;
	RetValue->next = 0 ;
	--number;
	return RetValue;		
}
template < typename T > 
PowVec<T> * Deck<T>::Copy(int num){
	PowVec<T> * RetValue;
	if (( num > number )||( num < 1))
		throw throwable("SystemDeck::Choose - num > number or < 1");
	RetValue = new PowVec<T>((*cards)[num-1]);
	RetValue->next = 0 ;
	return RetValue;		
}
template < typename T > 
int Deck<T>::FindById(string str){
	int i = 0;
	PowVec<T> *temp;
	temp = cards;
	while ((temp!=0)&&(str.compare(0,str.size(),temp->elem->GetId(),0,str.size()) != 0)){
		++i;
		temp = temp->next;
	}
	if (temp==0)
		return 0;
	return i+1;
}