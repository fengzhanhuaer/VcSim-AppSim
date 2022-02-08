#ifndef SPTAIO_H
#define SPTAIO_H

namespace spt
{
	class SptIoCell :public  HalIoCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, uint32 IoType, uint32 Node);
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node);
	protected:

	};

	union AngSampValuePrivateQ
	{
		struct
		{
			uint32 invalid : 2;
			uint32 test : 1;
		};
		uint32 u32;
	};
	struct AngSampValueCell
	{
		uint32 q;
		u32value value;
	};
	class SptAngBoard :public HalBoard
	{
	public:

	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
	protected:


	};
	class SptAngVirInputBoard :public HalBoard
	{
	public:
		struct ElmentInfo
		{
			uint16 frmNode;
			uint16 instNode;
			int32 value;
			uint32 q;
			uint32 adcoe;
			uint32 addcadjust;
			uint32 adadjust;
			void* cellPtr;
		};
		struct QDownParaHeader
		{
			uint16 frmNO;
			uint16 frmNum;
		};
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum, uint32 AdNum, uint8 AdNodeNum);
		void RecMsg(void* Buf, uint32 BufLen);
		void RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen);
		virtual int32 ProcIni()override;
		virtual int32 ProcIn()override;
		virtual int32 ProcOut()override;
		const ElmentInfo* CellPara(uint32 Index);
		void SetOutCoe(uint32 Index, uint32 Value);
		void SetOutADAdjust(uint32 Index, uint32 Value);
		void SetAdDcAdJust(uint32 Index, int32 Value);
		uint32 AdNum();
		void RgsProcIn(class SptSvInDataSet* Board);
	protected:
		SingleStackBuf ProcInBuf;
		uint16 dataNumOfRealFrm;
		ArrayBuf realDataMap;
		bool8 qUpdate;
		bool8 adCoeUpdate;
		bool8 adadjustUpdate;
		bool8 addcadjustUpdate;
		QDownParaHeader qDownPara;
		QDownParaHeader coeDownPara;
		QDownParaHeader adAdjustDownPara;
		QDownParaHeader addcAdjustDownPara;
		uint32 adNum;
		uint8 adNodeNum;
		uint16 lastSampCnt;
		uint16 sampCntJumpCnt;
	};
	class SptAngVirOutputBoard :public HalBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
	};
	class SptNormalAngInBoard :public SptAngBoard
	{
	public:

	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);

	};
	typedef SampRingBuf<AngSampValueCell, 8> AngSampRingBuf;
	class SptAngSampCell : public SptIoCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node, uint32 FrameNo, const VarUnits& Units);
		virtual void PushValue(const AngSampValueCell& Value);
		const AngSampValueCell& Value();
		const VarUnits* Units();
		bool8 IsReversal();
		virtual void SaveIds(void* Ele);
		uint16 AdIndex();
		uint16 AdNode();
		bool8 IsSingleAd();
	protected:
		AngSampRingBuf* ringBuf;
		AngSampValueCell value;
		const VarUnits* units;
		bool8 reverse;//·´¼«ÐÔ
		uint16 adIndex;
		uint16 adNode;
		uint32 fpagCoe;
		bool8 singleAd;
	};
	class SptNormalAngSampCell : public SptAngSampCell
	{
	protected:

	};
	class SptSampAng_9_2SampCell : public SptAngSampCell
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  HalBoard* Group, HalBoard* VirGroup, uint32 IoType, uint32 Node, uint32 FrameNo, const VarUnits& Units);
		void SetNodeLinkFlag(struct SVcbInfo* SvcbInfo, bool8 Flag, uint16 Node);
		void SetNodeLinkFlag(bool8 Flag, uint16 SvCbIndex, uint16 Node);
		bool8 NodeLinkFlag();
		struct SVcbInfo* SvcbInfo();
	protected:
		bool8 isNodeLinkOk;
		struct SVcbInfo* svcbInfo;
	};
	class SptSvInDataSet :public SptAngBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IoType, uint32 ElementNum);
		bool8 SetSvCbCfg(struct SVcbInfo* svcbSub, uint32 PortIndex, uint16 FpgaFrameIndex);
		virtual int32 ProcIni()override;
		void SetRecvStatus(uint8* Buf, uint32 Len);
	protected:
		uint32 cardPort;
		uint32 innerCardPort;
		struct SVcbInfo* svcbSub;
		bool8 isLinked;
		bool8 isEnable;
	};
	class SptSvOutDataSet :public SptAngBoard
	{
	public:
		struct ElmentInfo
		{
			uint16 frmNode;
		};
		struct QDownPara
		{
			uint16 frmNO;
			uint16 frmNum;
		};
		void PowerUpIni(const char* Name, const char* DesName, uint32 Delay, uint32 IoType, uint32 ElementNum);
		void SetOuterName(const char* Str);
		SalString& OuterName();
		bool8 SetSvCbCfg(struct SVcbInfo* SvcbPub, uint16 FpgaFrameIndex);
		virtual int32 ProcOut()override;
		virtual int32 ProcIni()override;
		void SetDelay(uint32 DelayUs);
		void SetSelIndex(uint16 Index, uint16 SelIndex);
		uint32 GetOutSelIndex(uint32 Index);
	protected:
		bool8 isLinked;
		bool8 isEnable;
		QDownPara selIndex;
		ArrayBuf realDownPara;
		bool8 selUpdate;
		uint16 delayUs;
		uint16 sampCount;
		String100B outerName;
		uint32 dataSetCellOutNum;
		SingleStackBuf outCellPtrBuf;
		struct SVcbInfo* svcbPub;
		uint8 svSendNet[6];
	};



}

#endif // !SPTAIO_H

