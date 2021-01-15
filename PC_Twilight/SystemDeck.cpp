SystemDeck::SystemDeck(){
	id = "";
	cards = 0;
	number = 0;
}
SystemDeck::SystemDeck(PowVec<Hex> * in_cards){
	id = "";
	cards = 0;
	number = 0;
	Add(in_cards);
}
SystemDeck::~SystemDeck(){
	if (cards != 0)
		delete cards;
}
int SystemDeck::GetNumber(){
	return number;
}
void SystemDeck::shuffle(){
	int i,temp,tempnum;
	PowVec<Hex> * newstart;
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
int SystemDeck::Add(PowVec<Hex> * in_cards){
	PowVec<Hex>* temp;
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
PowVec<Hex> * SystemDeck::PopFirst(int num){
	PowVec<Hex> * RetValue;
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
PowVec<Hex> * SystemDeck::GetList(){
	return cards;
}
PowVec<Hex> * SystemDeck::Choose(int num){
	PowVec<Hex> * RetValue;
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
PowVec<Hex> * SystemDeck::Copy(int num){
	PowVec<Hex> * RetValue;
	if (( num > number )||( num < 1))
		throw throwable("SystemDeck::Choose - num > number or < 1");
	RetValue = new PowVec<Hex>((*cards)[num-1]);
	RetValue->next = 0 ;
	return RetValue;		
}
int SystemDeck::FindById(string str){
	int i = 0;
	PowVec<Hex> *temp;
	temp = cards;
	while ((temp!=0)&&(str.compare(0,str.size(),temp->elem->GetId(),0,str.size()) != 0)){
		++i;
		temp = temp->next;
	}
	if (temp==0)
		return 0;
	return i+1;
}

void AddDeck(SystemDeck*deck, SystemType ST, bool accordToSettings){
	SystemDeck *tempdeck;
	string str;
	_Interface.GetSystemsFile(str, ST);
	_SystemTranslator.translate(str,&tempdeck);
	if (!accordToSettings)
		deck->Add(tempdeck->PopFirst(tempdeck->GetNumber()));
	else{
		tempdeck->shuffle();
		deck->Add(tempdeck->PopFirst(_Settings.GetSysNumber(ST)));
	}
	delete tempdeck;
}