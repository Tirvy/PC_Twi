struct ErNetDatagram{
	Datagram ndata;
	ErNetDatagram();
	ErNetDatagram(Datagram in);
	ErNetDatagram(void* data, size_t sizeofdata);
	const void* GetData();
	int GetType();
	int GetNumber();
	vector<int> GetDataAsVector();
	void PackDatagram(void* data, size_t sizeofdata, int type=0, int number=0);
};

class NetInterface{
	friend AsyncTask::DoneStatus tskListenerPolling(GenericAsyncTask* task, void* data);
	friend AsyncTask::DoneStatus tskReaderPolling(GenericAsyncTask* task, void* data);
	QueuedConnectionManager *_cManager;
	QueuedConnectionListener *_cListener;
	QueuedConnectionReader *_cReader;
	ConnectionWriter *_cWriter;
	int _port, _backlog;
	PT(GenericAsyncTask) _Listen, _Read;
	bool _accept,_nmsg,_resend;
	EventHandler::EventCallbackFunction* _DoOnMsg;
 
	deque<PT(Connection)> _activeConnections;
public:
	deque<ErNetDatagram> messages;

	NetInterface();
	~NetInterface();
	int GetConNum(Connection* connection);
	bool InitServer();
	void SetResend(bool sure);
	void Accept(EventHandler::EventCallbackFunction* newdo);
	void Reject();
	bool ConnectTo(string address);
	bool SendMsg(Datagram& data, int conNumber = 0);
	bool SendMsg(ErNetDatagram& data, int conNumber = 0);
}
_NeCo;

AsyncTask::DoneStatus tskListenerPolling(GenericAsyncTask* task, void* data);
AsyncTask::DoneStatus tskReaderPolling(GenericAsyncTask* task, void* data);