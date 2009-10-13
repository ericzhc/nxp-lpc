
#pragma  once 


#include "EcBusSocket.h"
#include "DataBuf.h"


class CClientCommDoc;
class CClientComm : public CEcBusSocket
{
	friend UINT  EthCommTask (LPVOID lpParam);		 
public:
	CClientComm( );
	~CClientComm( );
public:
	BOOL Connect ( DWORD dwTimeout = 2000);

	//开始收发
	void StartEngine( );
	//停止收发
	void StopEngine( );

	CDataBuf  m_SendBuf;

protected:
	SOCKET  m_nSocket;


	CClientCommDoc *m_pDocument;

	DWORD  m_dwDestIp;
	unsigned int m_nDestPortNum;
	unsigned int m_nLocalPortNum;

	CWinThread *m_pCommTsk;
	HANDLE      m_hStopEvent;
	HANDLE m_hTaskHandle;

};
