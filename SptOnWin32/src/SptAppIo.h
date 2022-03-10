#ifndef SptAppIo_H
#define SptAppIo_H

#include"SptAio.h"
#include"SptDio.h"
namespace spt
{
	class SptIedIoProcess
	{
	public:
		enum E_SLOWCMD
		{
			E_POWERUPINI,
			E_DICfgCmd,
			E_DOCfgCmd,
			E_DCCfgCmd,
			E_WORK,
		};
		enum E_SLOWCMDTYPE
		{
			E_NULL,
			E_DOWN_BOARD_OFFSET_SET = 0x01,//板卡偏移配置帧
			E_UP_BOARD_OFFSET_SET = 0x81,//板卡偏移回复帧
			E_UP_DO_REC_ST = 0x82,//DO板卡当前执行的命令的st
			E_UP_VERSION,//版本信息V1.00 上送100
			E_UP_DATE1,//日期信息 0x20200809,低位0809
			E_UP_DATE2,//日期信息 0x20200809,高位2020
			E_UP_CRC16,//校验码
			E_UP_DIO_Status_1,//DIO反校帧
			E_UP_CheckStatus_1,//自检状态
		};
	public:
		virtual void PowerUpIni(int Para) = 0;
		virtual void RecvNorIoMsg(void* Buf, uint16 Len) {};
		virtual void RecvAngFrameMsg(void* Buf, uint16 Len) {};
		virtual void RecvGoPosFrameMsg(void* Buf, uint16 Len) {};
		virtual void RecvGoAngFrameMsg(void* Buf, uint16 Len) {};
		virtual void RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen) {};
		virtual void RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen) {};
		virtual void RecBoardInfoMsg(void* Buf, uint32 BufLen) {};
		virtual void RecLightInfoMsg(void* Buf, uint32 BufLen) {};
		virtual void RecBoardMsg(void* Buf, uint32 BufLen) {};
		virtual void RecFpgaSlowMsg(void* Buf, uint32 BufLen) {};
		virtual void ProcIn() {};
		virtual void ProcOut() {};
		virtual void EnableSVSend(bool8 Enable) {};
		virtual void EnableAngErrPointDeal(bool8 Enable) {};
		virtual void EnableGoSend(bool8 Enable) {};
		virtual void CfgSendOver(bool8 Enable) {};
		virtual uint8 GetFpagSlowFlags(uint16 Index) { return 0; };
		virtual uint32 BoardOnLineState() { return 0; };
		virtual void ResetSubBoardState() {};
		bool8 IsIoPowerUpOver();
	protected:
		SptIedIoProcess();
		bool8 IsRecvBoardFrameMsgOk(void* Buf, uint16 Len);
		SingleStackBuf ProcInSerialBoardBuf;
		SingleStackBuf ProcOutSerialBoardBuf;
		SingleStackBuf NorDiSerialBoardBuf;
		SingleStackBuf NorDiAddrBoardBuf;
		SingleStackBuf NorDoSerialBoardBuf;
		SingleStackBuf NorDoAddrBoardBuf;
		SingleStackBuf NorDcSerialBoardBuf;
		SingleStackBuf NorDcAddrBoardBuf;
		SingleStackBuf VirSvFrameInSerialBuf;
		SingleStackBuf VirGoFrameInSerialBuf;
		SingleStackBuf VirEnabledSvDataSetInBuf;
		SingleStackBuf VirEnabledSvDataSetOutBuf;
		SingleStackBuf VirEnabledGoDataSetInBuf;
		SingleStackBuf VirEnabledGoDataSetOutBuf;
		SingleStackBuf VirGoSvStateBoardBuf;
		E_SLOWCMD slowCmdstep;
		uint16 DioMsgCnt;
		bool8 isPowerUpOver;
	};
	class SptGzkMuIoProcess :public SptIedIoProcess
	{
	public:
		struct CtrlFrame
		{
			uint16 frameNo;
			uint16 svSendEnable;
			uint16 goSendEnable;
			uint16 IedTest;
			uint16 cfgSendOver;//配置发送完成
			uint8 angErrPointDeal;//飞点处理
			uint8 Res[7];
		};
	public:
		virtual void PowerUpIni(int Para);
		virtual void RecvNorIoMsg(void* Buf, uint16 Len);
		virtual void RecvAngFrameMsg(void* Buf, uint16 Len);
		virtual void RecvGoPosFrameMsg(void* Buf, uint16 Len);
		virtual void RecvGoAngFrameMsg(void* Buf, uint16 Len);
		virtual void RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen);
		virtual void RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen);
		virtual void RecBoardInfoMsg(void* Buf, uint32 BufLen);
		virtual void RecLightInfoMsg(void* Buf, uint32 BufLen);
		virtual void RecBoardMsg(void* Buf, uint32 BufLen);
		virtual void RecFpgaSlowMsg(void* Buf, uint32 BufLen);
		virtual void ProcIn();
		virtual void ProcOut();
		virtual void EnableSVSend(bool8 Enable);
		virtual void EnableAngErrPointDeal(bool8 Enable);
		virtual void EnableGoSend(bool8 Enable);
		virtual void CfgSendOver(bool8 Enable);
		virtual uint8 GetFpagSlowFlags(uint16 Index);
		virtual uint32 BoardOnLineState() { return boardOnLineState; };
		virtual void ResetSubBoardState();
	protected:
		void SendGoSvSelFrame();
		void SetNorDo(uint32 Index, uint32 Do);
		void SendNorDoFrame();
		void SendSlowCmd();
		void SendCtrlFrame();
		GzkBoardCmmIoNorDOFrame rtDoFrame;
		GzkBoardCmmIoNorDOFrame editDoFrame;
		uint32 SlowCmdCnt;
		uint32 lastSendIndex;
		uint32 boardFrameSumErr;
		uint8 fpgaSlowFlags[8];
		CtrlFrame usedCtrlFlags;
		CtrlFrame rtCrtlFlags;
		bool8 updateCtrlFlags;
		uint32 boardOnLineState;
	};
	class SptIoProcess
	{
	public:

	public:
		void PowerUpIni(int Para);
		void RecvNorIoMsg(void* Buf, uint16 Len);
		void RecvAngFrameMsg(void* Buf, uint16 Len);
		void RecvGoPosFrameMsg(void* Buf, uint16 Len);
		void RecvGoAngFrameMsg(void* Buf, uint16 Len);
		void RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen);
		void RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen);
		void RecBoardInfoMsg(void* Buf, uint32 BufLen);
		void RecLightInfoMsg(void* Buf, uint32 BufLen);
		void RecBoardMsg(void* Buf, uint32 BufLen);
		void RecFpgaSlowMsg(void* Buf, uint32 BufLen);
		void ResetSubBoardState();
		void ProcIn();
		void ProcOut();
		struct stAppFlags& AppFlags() {
			return appFlags;
		};
		void EnableSVSend(bool8 Enable);
		void EnableAngErrPointDeal(bool8 Enable);
		void EnableGoSend(bool8 Enable);
		void CfgSendOver(bool8 Enable);
		uint8 GetFpagSlowFlags(uint16 Index);
		uint32 BoardOnLineState();
		bool8 IsIoPowerUpOver();
		const SptFlags& SptFlag() { return sptFlag; };
		M_Singleton(SptIoProcess);
	protected:
		SptIoProcess();
	protected:
		MsTimer faceRevertStart;
		MsTimer revertStart;
		SptIedIoProcess* proCess;
		struct stAppFlags appFlags;
		SptFlags sptFlag;
	};
}

#endif // !SptAppIo_H

