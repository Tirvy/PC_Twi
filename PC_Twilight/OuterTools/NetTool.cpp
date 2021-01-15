#include "NetTool.h"

ErNetDatagram::ErNetDatagram(){
	ndata.clear();
}
ErNetDatagram::ErNetDatagram(Datagram in){
	ndata = in;
}
ErNetDatagram::ErNetDatagram(void* data, size_t sizeofdata){
	if (data == 0)
		ndata.clear();
	else
		ndata.assign(data,sizeofdata);
	cout<<"sending: ";
	GetDataAsVector();
}
const void* ErNetDatagram::GetData(){
	return (void*)((int*)ndata.get_data()+1);
}
int ErNetDatagram::GetType(){
}
int ErNetDatagram::GetNumber(){
}
vector<int> ErNetDatagram::GetDataAsVector(){
	int i,j;
	vector<int> ret;
	ostringstream ss;
	ret.clear();
	i = ndata.get_length() / sizeof(int);
	if (i == 0){
		ss.str("");
		ToReplay(ss.str());
		return ret;
	}
	ret.resize(i);
	cout<<"The data is ";
	for (j=0; j < i; ++j){
		ret[j] = ((const int*)ndata.get_data())[j];
		cout<<ret[j]<<", ";
		ss<<ret[j]<<' ';
	}
	ToReplay(ss.str());
	return ret;
}
void ErNetDatagram::PackDatagram(void* data, size_t sizeofdata, int type, int number){
	ndata.assign(data,sizeofdata);
}

//--------------------------------------------------
//--------------------------------------------------

NetInterface::NetInterface(){
	_cManager = new QueuedConnectionManager();
	_cReader = new QueuedConnectionReader(_cManager,0);
	_cWriter = new ConnectionWriter(_cManager,0);
	_port = 42317;
	_backlog = 1000;
	_accept = false;
	_DoOnMsg = 0;
	_resend = false;
	_Read = new GenericAsyncTask("reader", &tskReaderPolling, (void*) NULL);
	taskMgr->add(_Read);
} 
int NetInterface::GetConNum(Connection* connection){
	int i;
	for (i=0; i<_activeConnections.size(); ++i)
		if (_activeConnections[i] == connection)
			return i;
	return -1;
}
void NetInterface::Accept(EventHandler::EventCallbackFunction* newdo){
	if (newdo == 0)
		return;
	_DoOnMsg = newdo;
	_accept = true;
}
void NetInterface::Reject(){
	_accept = false;
}
bool NetInterface::InitServer(){
	_cListener = new QueuedConnectionListener(_cManager,0);
	_cListener->add_connection(_cManager->open_TCP_server_rendezvous(_port,_backlog));
	_Listen = new GenericAsyncTask("listener", &tskListenerPolling, (void*) NULL);
	taskMgr->add(_Listen);
	return true;
}
NetInterface::~NetInterface(){
	deque<PT(Connection)>::iterator cons = _activeConnections.begin();
	while (cons != _activeConnections.end()){
		_cReader->remove_connection(*cons);
		_cManager->close_connection(*cons);
		++cons;
	}
	_activeConnections.clear();
}
void NetInterface::SetResend(bool sure){
	_resend = sure;
}
bool NetInterface::ConnectTo(string address){
	PT(Connection) newcon = _cManager->open_TCP_client_connection(address,_port,3000);
	if (newcon){
		_cReader->add_connection(newcon);
		_activeConnections.push_back(newcon);
		cout<<"good";
		return true;
	}
	return false;
}
bool NetInterface::SendMsg(Datagram& data, int conNumber){
	cout<<"Sending message to "<<conNumber;
	if (_activeConnections.size() > conNumber){
		if (_cWriter->send(data,_activeConnections[conNumber]))
			cout<<" was a success!"<<endl;
		else
			cout<<" was a failure("<<endl;
		return true;
	}
	cout<<" was a failure, cuz no such connection"<<endl;
	return false;
}
bool NetInterface::SendMsg(ErNetDatagram & data, int conNumber){
	cout<<"Sending message sized "<<data.ndata.get_length()/sizeof(int)<<" to "<<conNumber;
	if (_activeConnections.size() > conNumber){
		if (_cWriter->send(data.ndata,_activeConnections[conNumber]))
			cout<<" was a success!"<<endl;
		else
			cout<<" was a failure("<<endl;
		return true;
	}
	cout<<" was a failure, cuz no such connection"<<endl;
	return false;
}

AsyncTask::DoneStatus tskListenerPolling(GenericAsyncTask* task, void* data) {
	if (_NeCo._cListener->new_connection_available()){
		PT(Connection) newConnection;
		if (_NeCo._cListener->get_new_connection(newConnection)){
			_NeCo._activeConnections.push_back(newConnection);
			_NeCo._cReader->add_connection(newConnection);
		}
	}
	return AsyncTask::DS_cont;
}

AsyncTask::DoneStatus tskReaderPolling(GenericAsyncTask* task, void* data) {
	if (_NeCo._cReader->data_available()){
		NetDatagram Data;
		if (_NeCo._cReader->get_data(Data)){
			cout<<"Got some net data"<<endl;
			if (_NeCo._accept){
				cout<<"Accepted connection data from "<<_NeCo.GetConNum(Data.get_connection())<<endl;
				_NeCo._accept = false;
				(*_NeCo._DoOnMsg)(0,(void*)&Data);
			}
			else{
				cout<<"Accepted data from "<<_NeCo.GetConNum(Data.get_connection())<<" size of "<<Data.get_length()/sizeof(int)<<endl;
				_NeCo.messages.push_back(ErNetDatagram(Data));
			}
			if (_NeCo._resend)
				for (int i = 0; i<_NeCo._activeConnections.size();++i){
					if (Data.get_connection() != _NeCo._activeConnections[i]){
						cout<<"Resend data to "<<i<<endl;
						_NeCo.SendMsg(Data,i);
					}
				}
		}
	}
	return AsyncTask::DS_cont;
}