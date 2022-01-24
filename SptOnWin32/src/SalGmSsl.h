#ifndef SALGMSSL_H
#define SALGMSSL_H


namespace spt
{
	bool8 IsGmServerIniOk();
	void OpenSslLibIni();
	void OpenSslLibClean();
	int32 DbgGmSslServerIni();
	int32 DbgGmSslClientIni();
	void* DbgGmSslSockServerNew(void* Sock);
	void* DbgGmSslSockClientNew(void* Sock);
	int32 DbgGmSslAccept(void* GmSock);
	int32 DbgGmSslConnect(void* GmSock);
	int32 DbgGmSslClose(void* GmSock);
	int32 DbgGmSslWrite(void* GmSock, const void* Buf, int32 BufLen);
	int32 DbgGmSslRead(void* GmSock, void* Buf, int32 BufLen);
	int32 CheckDbgServerCrt();
	int32 CheckDbgClientCrt();
	//Gm加密Len必须为16的倍数
	int32 SalGmSm4EncryData(const uint8* Data, uint8* Out, uint32 Len);
	//Gm加密Len必须为16的倍数
	int32 SalGmSm4DecryData(const uint8* Data, uint8* Out, uint32 Len);

}


#endif // !SALGMSSL_H

