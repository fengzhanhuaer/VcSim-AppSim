#ifndef HMILCDDRIVER_H
#define HMILCDDRIVER_H

namespace spt
{
	enum LcdMsgType
	{
		E_DrawAssic = 0x0101,
		E_DrawStr = 0x0111,
		E_DrawLine = 0x0121,
		E_DrawLine2 = 0x0122,
		E_DrawRect = 0x0131,
		E_ClearRect = 0x0141,
		E_ClearAll = 0x0142,
		E_UpdateRect = 0x0151,
		E_UpdateAll = 0x0152,
		E_DrawUint32 = 0x0201,
		E_KeyMsg = 0x0301,
		E_LcdHeartBeat = 0x0302,
		E_IedName = 0x0401,
		E_LedInfoAsk = 0x0402,
		E_LedInfoAsw = 0x0403,
		E_LedInfoVal = 0x0404,
		E_SockClose = 0x0405,
		E_DrawBitMap = 0x0501,
		E_DrawPicLine = 0x0601,
		E_DrawPicRect = 0x0602,
		E_DrawPicUpdate = 0x0603,
	};

	typedef SalCmmMsg<1024> LcdMsg;

	struct LcdMsgContext
	{
		uint16 type;
		uint16 len;
		char data[512];
	};

	struct LcdDrawAssicMsg
	{
		uint16 type;
		uint16 len;
		uint16 x;
		uint16 y;
		uint16 color;
		char msg[512];
	};
	struct LcdDrawBitMap
	{
		uint16 type;
		uint16 len;
		uint16 x;
		uint16 y;
		uint16 code;
		uint16 color;
	};
	struct LcdDrawRect
	{
		uint16 type;
		uint16 len;
		uint16 x;
		uint16 y;
		uint16 color;
		uint16 w;
		uint16 h;
	};
	struct LcdDrawLine2
	{
		uint16 type;
		uint16 len;
		uint16 sx;
		uint16 sy;
		uint16 ex;
		uint16 ey;
		uint16 color;
		uint16 w;
	};
	struct LcdDrawCmd
	{
		uint16 type;
		uint16 len;
	};
	struct LcdDrawData
	{
		uint16 type;
		uint16 len;
		uint16 x;
		uint16 y;
		uint16 color;
		uint8 fraBit;
		bool8 isRight;
		uint32 data;
	};
	struct LcdKeyMsg
	{
		uint16 type;
		uint16 len;
		uint8 key1;
		uint8 key2;
		uint8 key3;
		uint8 key4;
	};
	struct LcdHeartBeat
	{
		uint16 type;
		uint16 len;
		uint16 Ctx[16];
		uint32 PowerUpTimerMsL;
		uint32 PowerUpTimerMsH;
	};
	struct LcdIedInfo
	{
		uint16 type;
		uint16 len;
		uint16 ledNum;
		uint16 cor;
		char data[100];
	};
	struct LcdPicMode
	{
		uint16 type;
		uint16 len;
		uint16 x;
		uint16 y;
		uint16 w;
		uint16 h;
		char data[800];
	};
#ifdef WIN32_SIM
	class HmiTcpCmmChannel :public SalCmmChannel
	{
	public:
		int32 PowerUpIni(int32 Para);
		int32 SendMsg(void* Data, uint16 DataLen);
		int32 Recv(LcdMsg& Msg);
		virtual int32 ProcIn() override;
		virtual int32 Proc() override;
		virtual int32 ProcOut() override;
		void Close();
		bool8 IsLinkOk();
		int32 StartClient(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort, int32 ClientSock);
		int32 CheckStatus();
	public:
		HmiTcpCmmChannel();
	protected:

	private:
		bool8 forceClose;
		DbgTcpGmClient virlcdCmm;
		bool8 logOk;
		MsTimer msTimer;
		uint32 sendCnt;
		uint32 sendCntBak;
		uint32 recvCntBak;
	};
#endif
	class HmiSerialCmmChannel :public SalCmmChannel
	{
	public:
		int32 PowerUpIni(int32 Para);
		int32 SendMsg(void* Data, uint16 DataLen);
		int32 Recv(LcdMsg& Msg);
		virtual int32 ProcIn() override;
		virtual int32 Proc() override;
		virtual int32 ProcOut() override;
		bool8 IsCmmOk();
		int32 StartClient(uint32 LocalIp, uint16 LocalPort, uint32 RemoteIp, uint16 RemotePort);
		int32 CheckStatus();
	public:
		HmiSerialCmmChannel();
	protected:

	private:
		bool8 cmmOk;
		MsTimer msTimer;
		uint32 sendCntBak;
		uint32 recvCntBak;
	};
#ifdef WIN32_SIM
	class HmiLcdCmm :public HmiTcpCmmChannel
#else
	class HmiLcdCmm :public HmiSerialCmmChannel
#endif
	{
	public:
		static HmiLcdCmm& Instance();
		enum TaskStep
		{
			E_PowerUpIni = 0,
			E_Restart,
			E_Work,
		};
	public:
		void HeartBeat();
		virtual int32 PowerUpIni(int32 Para);
		virtual int32 OneLoop();
		virtual int32 Proc() override;
	public:
		int32 Unpack(LcdMsgContext* Msg);
		void Send(LcdMsgContext* Msg);
		bool8 IsLcdCmmOk();
	protected:
		HmiLcdCmm();
		void HmiLcdHeartCheck();
		virtual int32 ProcIn() override;
		virtual int32 ProcOut() override;
	private:
		uint8 taskStep;
		MsTimer heartBeatCheck;
		MsTimer heartBeat;
	};




}


#endif // !HMILCDDRIVER_H

