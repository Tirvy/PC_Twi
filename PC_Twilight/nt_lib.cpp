#include <string>
#include <time.h>
#include <stdlib.h>

// returns the number of symbols before \0 or \n
int nt_strlen(const string str){
	int i=0;
	while ((str[i]!='\n')&&(str[i]!='\0'))
		++i;
	return i;
}

// Copies symbols from source to str till first non-letter
void nt_strcsy(string& str, const char * source){
	int i=0;
	str.clear();
	while (((source[i]<='z')&&(source[i]>='a'))||((source[i]<='Z')&&(source[i]>='A'))){
		str.push_back(source[i]);
		++i;
	}
}

int nt_rand(const int max){
	int temp;
	//cout<<"GREAT KOREAN RANDOM!\n";
	temp = rand() % max;
	return temp;
}

int strcmp(string a, string b){
	if (a == b)
		return 0;
	return 1;
}

// returns the number of symbols equal in both srts till first mismatch
int nt_streq(const string str,const string pos){
	int i=0;
	int s1=str.size();
	int s2=pos.size();
	while (((str[i]==pos[i])||(str[i]==pos[i]+('a'-'A'))||(str[i]==pos[i]+('A'-'a')))&&(i<s1)&&(i<s2))
		i++;
	return i;
}

//
bool nt_isnum(const char c){
	if (((c>='0')&&(c<='9'))||(c=='-'))
		return true;
	return false;
}
bool nt_isendl(const char c){
	if ((c=='\0')||(c=='\n')||(c=='\r')||(c==0)||(c==10))
		return true;
	return false;
}

// rolls i, so buffer[i] would point to first not ' ' character after 'c'
int nt_roll(const string buff,int*i,const char c = ' '){
	if (c==0){
		while(nt_isnum(buff[*i]))
			(*i)++;
		while(!(nt_isnum(buff[*i]) || nt_isendl(buff[*i])))
			(*i)++;
		if (nt_isendl(buff[*i]))
			return -1;
		}
	else{
		while((buff[*i]!=c)&&(buff[*i]!='/n')&&(buff[*i]!='/0'))
			(*i)++;
		if ((buff[*i]=='/n')||(buff[*i]=='/0'))
			return -1;
		++(*i);
		while((buff[*i]==' ')||(buff[*i]==9))
			(*i)++;
	}
	return 1;
	//++(*i);
}

// Creates an array and copies source to empty
int nt_strload(string& empty, const char * source){
	empty = string(source);
	if (empty[empty.size()-1] == '\n')
		empty.erase(--empty.end());
	return 0;
}

int nt_strload(string & empty, const string source){
	empty = source;
	return 0;
}

int nt_tonumber(const string str){
	int i=0,sum=0,sign=1;
	if (str[0]=='-'){
		sign = -1;
		i = 1;
	}
	while ((str[i]<='9')&&(str[i]>='0')){
		sum*=10;
		sum+=str[i]-'0';
		++i;
	}
	return sum*sign;
}

// Throwable thing. Better get to use it
struct throwable{
	char str1[128];
	char str2[128];
	int elem1,elem2;
	throwable(const char * in_str){
		strcpy(str1,in_str);
		elem1 = 0;
	}
	throwable(const string in_str){
		strcpy(str1,in_str.c_str());
		elem1 = 0;
	}
	throwable(const char * in_str, const int in_elem){
		strcpy(str1,in_str);
		strcpy(str2,"");
		elem1 = in_elem;
		elem2=0;
	}
	throwable(const string in_str, const int in_elem){
		strcpy(str1,in_str.c_str());
		strcpy(str2,"");
		elem1 = in_elem;
		elem2=0;
	}
	throwable(const char * in_str, const int in_elem1, const int in_elem2){
		strcpy(str1,in_str);
		strcpy(str2,"");
		elem1 = in_elem1;
		elem2 = in_elem2;
	}
	throwable(const char * in_str1, const char * in_str2){
		strcpy(str1,in_str1);
		strcpy(str2,in_str2);
		elem1 = 0;
		elem2 = 0;
	}
	throwable(const char * in_str1, const string in_str2){
		strcpy(str1,in_str1);
		strcpy(str2,in_str2.c_str());
		elem1 = 0;
		elem2 = 0;
	}
	throwable(const char * in_str1, const char * in_str2, const int in_elem){
		strcpy(str1,in_str1);
		strcpy(str2,in_str2);
		elem1 = in_elem;
		elem2 = 0;
	}
	throwable(const string in_str1, const char * in_str2, const int in_elem){
		strcpy(str1,in_str1.c_str());
		strcpy(str2,in_str2);
		elem1 = in_elem;
		elem2 = 0;
	}
};

// Vector or smth like that. Cause i dont trust STL. Cause i dont know it))
template < typename T >
struct PowVec{
	T* elem;
	PowVec<T>* next;
	
	PowVec( T* in_elem = 0, PowVec<T>* in_next = 0 ){
		elem = in_elem;
		next = in_next;
	}
	int Number(){ // Возвращает оставшуюся длину списка
		int i=0;
		PowVec<T>* temp;
		temp = this;
		while (temp!=0){
			temp = (temp->next);
			++i;
		}
		return i;
	}
	void Delete(int n){
		int i;
		PowVec<T>* temp, *del;
		temp = this;
		if (n == 0)
			throw throwable("PowVec<T>& Delete n==0");
		for(i=0;i < (n-1);i++){
			if (temp->next == 0)
				throw throwable("PowVec<T>& Delete out of reach");
			temp = (temp->next);
		}
		if (temp->next == 0)
			throw throwable("PowVec<T>& Delete out of reach");
		del = temp->next;
		temp->next = del->next;
		del->next = 0;
		delete del;
	}
	PowVec<T>& operator[](int n){
		int i;
		PowVec<T>* temp;
		temp = this;
		for(i=0;i<n;i++){
			if (temp->next == 0)
				throw throwable("PowVec<T>& operator[] out of reach");
			temp = (temp->next);
		}
		return (*temp);
	}
	PowVec<T>& operator+=(PowVec<T> * added){
		PowVec<T>* temp;
		temp = this;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = added;
		return *this;
	}
	PowVec<T>& operator+=(T * added){
		PowVec<T>* temp;
		temp = this;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = new PowVec(added);
		return *this;
	}
	~PowVec<T>(){
		if (elem!=0)
			delete elem;
		if (next!=0)
			delete next;
	}
};


template < typename T > 
struct PowExv{
	T* elem;
	PowExv<T>* next;
	int status;
	PowExv( T* in_elem = 0, int in_status = 0, PowExv<T>* in_next = 0 ){
		elem = in_elem;
		status = in_status;
		next = in_next;
	}
	int Number(){ // Возвращает оставшуюся длину списка
		int i=0;
		PowExv<T>* temp;
		temp = this;
		while (temp!=0){
			temp = (temp->next);
			++i;
		}
		return i;
	}
	void Delete(int n){
		int i;
		PowExv<T>* temp, *del;
		temp = this;
		if (n == 0)
			throw throwable("PowVec<T>& Delete n==0");
		for(i=0;i < (n-1);i++){
			if (temp->next == 0)
				throw throwable("PowVec<T>& Delete out of reach");
			temp = (temp->next);
		}
		if (temp->next == 0)
			throw throwable("PowVec<T>& Delete out of reach");
		del = temp->next;
		temp->next = del->next;
		del->next = 0;
		delete del;
	}
	PowExv<T>& operator[](int n){
		int i;
		PowExv<T>* temp;
		temp = this;
		for(i=0;i<n;i++){
			if (temp->next == 0)
				throw throwable("PowVec<T>& operator[] out of reach");
			temp = (temp->next);
		}
		return (*temp);
	}
	PowExv<T>& operator+=(PowExv<T> * added){
		PowExv<T>* temp;
		temp = this;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = added;
		return *this;
	}
	PowExv<T>& operator+=(T * added){
		PowExv<T>* temp;
		temp = this;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = new PowExv(added);
		return *this;
	}
	~PowExv<T>(){
		if (elem!=0)
			delete elem;
		if (next!=0)
			delete next;
	}
};



template < typename T1, typename T2 > 
struct PowDEV{
	T1* elem1;
	T2* elem2;
	PowDEV<T1,T2>* next;
	int status;
	PowDEV( T1* in_elem1 = 0, T2* in_elem2 = 0, int in_status = 0, PowDEV<T1,T2>* in_next = 0 ){
		elem1 = in_elem1;
		elem2 = in_elem2;
		status = in_status;
		next = in_next;
	}
	int Number(){ // Возвращает оставшуюся длину списка
		int i=0;
		PowDEV<T>* temp;
		temp = this;
		while (temp!=0){
			temp = (temp->next);
			++i;
		}
		return i;
	}
	void Delete(int n){
		int i;
		PowDEV<T>* temp, *del;
		temp = this;
		if (n == 0)
			throw throwable("PowVec<T>& Delete n==0");
		for(i=0;i < (n-1);i++){
			if (temp->next == 0)
				throw throwable("PowVec<T>& Delete out of reach");
			temp = (temp->next);
		}
		if (temp->next == 0)
			throw throwable("PowVec<T>& Delete out of reach");
		del = temp->next;
		temp->next = del->next;
		del->next = 0;
		delete del;
	}
	PowDEV<T1,T2>& operator[](int n){
		int i;
		PowDEV<T1,T2>* temp;
		temp = this;
		for(i=0;i<n;i++){
			if (temp->next == 0)
				throw throwable("PowVec<T>& operator[] out of reach");
			temp = (temp->next);
		}
		return (*temp);
	}
	PowDEV<T1,T2>& operator+=(PowDEV<T1,T2> * added){
		PowDEV<T1,T2>* temp;
		temp = this;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = added;
		return *this;
	}
	~PowDEV(){
		if (elem1!=0)
			delete elem1;
		if (elem2!=0)
			delete elem2;
		if (next!=0)
			delete next;
	}
};


template < typename T > 
struct PowTree{
private:
	int size;
public:
	T* elem;
	int status;
	PowTree<T>**	child;
	PowTree( T* in_elem = 0, int in_status = 0, int nsize = 6 ){
		if (nsize<2)
			throw throwable ("PowTree is not a tree (nsize<2)");
		size = nsize;
		elem = in_elem;
		status = in_status;
		child = new PowTree<T>*[size];
		for (int i=0;i<size;++i)
			child[i]=0;
	}
	bool AddChild(PowTree<T>* newbie){
		int i;
		if (newbie == 0)
			return 0;
		for (i=0;i<size;++i)
			if (child[i] == 0){
				child[i]= newbie;
				break;
			}
		if (i == size)
			throw throwable("PowTree AddChild oversize still not realised");
		return 1;
	}
	/*PowTree<T>* Find(T* tofind){
		int i;
		PowTree<T>* ret = 0;
		if (elem == tofind)
			return this;
		for (i = 0;i<size;++i){
			if (child[i] != 0){
				ret = child[i]->Find(tofind);
				if (ret != 0)
					return ret;
			}
		}
		return 0;
	}*/
	int GetSize(){
		return size;
	}
	~PowTree(){
		for (int i=0;i<size;++i)
			if (child[i]!=0)
				delete child[i];
		delete child;
	}
};


template < typename T > 
PowExv<T>* nt_TreeToVec(PowTree<T>* tree){
	PowExv<T>* ret = new PowExv<T>;
	PowExv<T>* temp = 0;
	int i;
	if (tree == 0){
		//delete ret;
		return 0;
	}
	ret->elem = tree->elem;
	ret->status = tree->status;
	for (i=0;i<tree->GetSize();++i){
		temp = nt_TreeToVec(tree->child[i]);
		if (temp != 0)
			(*ret)+=temp;
	}
	return ret;
}

template < typename T > 
PowExv<T>* nt_TreeToVec(PowTree<T>* tree, int a){// -1 - min status, 1 - max status
	PowExv<T>* ret = new PowExv<T>;
	PowExv<T>* main,*temp;
	bool flag;
	if ((a!=1)&&(a!=-1))
		throw throwable("nt_TreeToVec: a is baaad");
	ret = nt_TreeToVec(tree);
	main = ret->next;
	while (main!=0){
		temp = ret;
		flag = false;
		while (temp!=main){
			if (temp->elem == main->elem){
				if (((a==-1)&&(temp->status > main->status))||((a==1)&&(temp->status < main->status)))
					temp->status = main->status;
				flag = true;
			}
			if ((temp->next == main)&&(flag)){
				temp->next = main->next;
				main->next = 0;
				//delete main;
				main = temp;
			}
			else
				temp = temp->next;
		}
		main = main->next;
	}
	return ret;
}

template < typename T1, typename T2 > 
struct PowDouble{
	T1* elem1;
	T2* elem2;
	PowDouble( T1* in_elem1 = 0, T2* in_elem2 = 0){
		elem1 = in_elem1;
		elem2 = in_elem2;
	}
};

void Log(string log){
	cout<<log<<endl;
}
void Eggog(string eggog){
	cout<<eggog<<endl;
	throw throwable("BAGA!");
}

int CheckRet(vector<int> ret){
	int result = 0;
	for (int i = 0; i < ret.size(); i++)
		if (ret.at(i) == 1)
			result++;
	return result;
}

int CheckNumericalRet(vector<int> ret){
	int result = 0;
	for (int i = 0; i < ret.size(); i++)
		if (ret.at(i) != 0)
			result++;
	return result;
}

template < typename T > 
void sync_shuffle(vector<T> & tosh){
	int i,j;
	T swap;
	for (i = 0; i < tosh.size(); ++ i){
		j = rand() % tosh.size();
		swap = tosh[i];
		tosh[i] = tosh[j];
		tosh[j] = swap;
	}
}

template < typename T > 
void sync_shuffle(deque<T> & tosh){
	int i,j;
	T swap;
	for (i = 0; i < tosh.size(); ++ i){
		j = rand() % tosh.size();
		swap = tosh[i];
		tosh[i] = tosh[j];
		tosh[j] = swap;
	}
}