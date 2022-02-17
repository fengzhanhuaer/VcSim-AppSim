#ifndef SPTDIO_H
#define SPTDIO_H

namespace spt
{
	class SptNormalDcInBoard :public HalBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 CardAddr, uint16 FrameIndex, uint32 ElementNum);
		void RecvMsg(SalDateStamp& Utc, uint8* Frame);
	public:
	protected:
		uint16 temprature;
	};
	class SptNormalDcIn : public SptIoCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node, uint32 FrameNo, const VarUnits& Units);
		void SetValue(int32 Value);
		void ForceSetValue(int32 Value);
	protected:
		const VarUnits* units;
		AngSampValueCell value;
	};
	struct StateBoardValueCell
	{
		SalDateStamp stamp;
		u32value value[1];
	};
	typedef SampRingBuf<StateBoardValueCell, 4> StateBoardSampRingBuf;
	class SptStateBoard :public HalBoard
	{
	public:

	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
	protected:
		SingleStackBuf ElementBuf;
		StateBoardSampRingBuf* ringBuf;
	};
	class SptNormalStateInBoard :public SptStateBoard
	{
	public:

	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
	public:
		void RecvMsg(SalDateStamp& Utc, GzkBoardCmmIoNorDIFrame* Frame);
		virtual int32 ProcIn()override;
		uint32 GetValue(uint32 Index);
	protected:
		uint32 rtValue[1];
	};
	class SptNormalStateOutBoard :public SptStateBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
		virtual int32 ProcOut()override;
		uint32 FrameIndex();
		void RecvMsg(SalDateStamp& Utc, uint8* Frame);
		void RecvMsg(SalDateStamp& Utc, GzkBoardCmmIoNorDIFrame* Frame);
		void SetOutValue(uint32 Index, uint32 Value);
		void SetStartValue(uint32 Value);
	public:
		uint32 GetValue(uint32 Index);
		uint32 RtStartValue();
	protected:
		struct SalDateStamp stateStamp;
		uint8 rtDoValueUpdate;
		uint32 rtValue[1];
		bool8 rtDoValue[sizeof(rtValue) * 8 * 2];
		uint32 rtStart;
		uint32 rtOutState[1];
		uint32 rtOutStateNum;
	};
	union StateValuePrivateQ
	{
		struct
		{
			uint32 invalid : 2;
			uint32 test : 1;
		};
		uint32 u32;
	};
	union StateValueQ
	{
		struct
		{
			uint32 invalid : 2;
			uint32 test : 1;
		};
		uint32 u32;
	};
	struct StateValueCell
	{
		uint32 q;
		u32value value;
		SalDateStamp stamp;
	};
	typedef SampRingBuf<StateValueCell, 4> StateSampRingBuf;
	class SptStateCell : public SptIoCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node);
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, uint32 IoType, uint32 Node);
		virtual void SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
		virtual void ForceSetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
		const StateValueCell& Value();
		virtual void SaveIds(void* Ele);
	protected:
		StateSampRingBuf* ringBuf;
		StateValueCell value;
	};
	class SptNormalStateInCell : public SptStateCell
	{
	public:
		virtual void SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
	protected:

	};
	class SptNormalStateOutCell : public SptStateCell
	{
	public:
		virtual void SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
		virtual void ForceSetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
		void SetOutState(uint32 Value);
	protected:
		bool8 outValue;
	};
	class SptGooseFrameIn :public SptStateBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
		virtual int32 ProcIni()override;
		void RgsProcIn(class SptGooseDataSetIn* Board);
		void RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen);
		void RecPosMsg(void* Buf, uint32 BufLen);
		void RecAngMsg(void* Buf, uint32 BufLen);
	protected:
		uint32 posCellNum;
		uint32 posNotWithTCellNum;
		uint32 posFrameNum;
		uint32 angFrameNum;
		SingleStackBuf PosElementBuf;
		SingleStackBuf U32ElementBuf;
		SingleStackBuf ProcInBuf;
	};
	class SptGooseFrameOut :public SptStateBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
	};

	class SptGooseData :public SptStateCell
	{
	public:
		struct NodeInfo
		{
			SptGooseData* cell;
			bool8 isLinked;
			uint16 dataSetoffSet;
			uint16 dataSetIndex;
			uint16 dataLinkIndex;
			uint32 dataType;
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, uint32 IoType, uint32 Node, uint32 FrameIndex);
		void SetVLinked(bool8 Ok, uint32 Node, uint32 Index, uint32 OffSet, uint32 GoType);
		void SetQLinked(bool8 Ok, uint32 Node, uint32 Index, uint32 OffSet);
		void SetTLinked(bool8 Ok, uint32 Node, uint32 Index, uint32 OffSet);
		virtual void SetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
		const struct NodeInfo& QNode();
		const struct NodeInfo& TNode();
		const struct NodeInfo& VNode();
		bool8 IsPos();
		bool8 SetGoCbCfg(struct GooseGocbInfo* GocbInfo);
		const struct GooseGocbInfo* GocbInfo();
		virtual void GoEnCode(uint32 type, uint8* Buf);
	protected:
		struct NodeInfo qNode;
		struct NodeInfo tNode;
		struct NodeInfo vNode;
		SalStdUtcStamp utcStamp;
		GooseGocbInfo* gocbInfo;
	};
	class SptGooseDataOut :public SptGooseData
	{
	public:
		void GoSetValue(uint32 Value);
		void ForceSetValue(uint32 Value, uint32* Q, SalDateStamp* stamp);
	};
	class SptGooseDataIn :public SptGooseData
	{
	};
	class SptGooseDataSetIn :public SptStateBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, SptGooseFrameIn* VirBoard, uint32 IoType, uint32 ElementNum);
		bool8 SetGoCbCfg(struct GooseGocbInfo* GocbSub, uint32 PortIndex, uint16 FpgaFrameIndex);
		virtual int32 ProcIni()override;
		void SetRecvStatus(uint8* BufA, uint8* BufB, uint32 Len);
	protected:
		bool8 isEnableB;
		uint32 AcardPort;
		uint32 AinnerCardPort;
		uint32 BcardPort;
		uint32 BinnerCardPort;
		bool8 isLinked;
		bool8 isEnabled;
		GooseGocbInfo* gocbSub;
	};
	class SptGooseDataSetOut :public SptStateBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, SptGooseFrameOut* VirBoard, uint32 IoType, uint32 ElementNum);
		SalString& OuterName();
		bool8 SetGoCbCfg(struct GooseGocbInfo* GocbPub, uint16 FpgaFrameIndex);
		void UpdateData(uint32 Node);
		virtual int32 ProcOut()override;
		virtual int32 ProcIni()override;
		SalDateStamp& SendStamp() { return sendstamp; };
	protected:
		static const uint32 frameOffSetInRtFrame = 18;
	protected:
		void IniGoFrame();
		void UpdateFrame(uint8* buf, uint32 BufLen);
		SingleStackBuf dataSetElementBuf;
		CpuFpgaCmmMsgBuf rtSendMsg;
		SalDateStamp sendstamp;
		uint32 stNum;
		uint32 sqNum;
		bool8 isDataUpdate;
		uint32 lastSendStamp;
		String100B outerName;
		GooseGocbInfo* gocbPub;
		uint8 goNetEnable[2];
		bool8 isEnable;
	};

	class SptGoSvStateBoard :public HalBoard
	{
	public:
		struct NetState
		{
			u32value LightT;//发送光强
			u32value LightR;//接收光强
			u32value Temperature;//温度
			u32value Voltage;
		};
	public:
		enum StateOffSet
		{
			E_Light_T,//发送光强
			E_Light_R,//接收光强
			E_Temperature,//温度
			E_Voltage,//电压
			E_StateNumPerNet = 4
		};
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 CardNo, uint32 ElementNum);
		void RecBoardState(uint8* Buf, uint32 Len);
		void RecNetState(uint8* Buf, uint32 Len);
	protected:
		uint16 progRunState;
		uint16 cfgState;
		uint16 svRecCfgState;
		uint16 svSendCfgState;
		NetState netState[16];
		uint8 goRecCfgState[6];
		uint8 goRecTypeCfgState[6];
		uint8 goRecMapCfgState[2];
		uint32 clkCntPps;
		bool8 infoOk;
	};
}
#endif //SPTDIO_H
