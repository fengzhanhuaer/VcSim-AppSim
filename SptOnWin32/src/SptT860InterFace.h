#ifndef SptT860INTERFACE_H
#define SptT860INTERFACE_H

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
	class XMLAttribute;
	class XMLComment;
	class XMLText;
	class XMLDeclaration;
	class XMLUnknown;
	class XMLPrinter;
}

namespace spt
{
	const uint16 CN_GOOSEMaxCellNum = 256;
	const uint16 CN_OneGooseLinkMax = 20;
	const uint16 CN_OneSVLinkMax = 5;
	const uint16 CN_SvMaxCellNum = 256;
	const uint16 CN_MaxEhtFrameLen = 3200;
	enum GoSvDataType
	{
		E_GOSV_NULL,
		E_GOSV_BOOL,//8301h
		E_GOSV_BITSTR,//84h
		E_GOSV_DPOS,//840206h
		E_GOSV_Q,//840300H
		E_GOSV_INT32,//8504H
		E_GOSV_INT16,//8504H
		E_GOSV_INT8,//8504H
		E_GOSV_UINT32,//8604h
		E_GOSV_UINT16,//8604h
		E_GOSV_UINT8,//8604h
		E_GOSV_FLOAT32,//870508H
		E_GOSV_TIMSSTAMP,//9108h
	};

	struct GoSvAddressInfo
	{
		bool8 parseErr;
		uint8 DstMac[6];
		uint16 appId;
		uint16 Vlan;
		uint8 Vlan_PRIORITY;
		uint16 Vlan_Id;
	};
	struct GooseGocbInfo
	{
		/// <summary>
		/// ���ƿ��뱾��IOģ�������쳣
		/// </summary>
		bool8 cfgErr;
		/// <summary>
		/// ���ƿ�����쳣
		/// </summary>
		bool8 parseErr;
		/// <summary>
		/// ��������ַ�쳣
		/// ������CCD�����쳣
		/// </summary>
		bool8 sAddrErr;
		bool8 linked;
		uint16 index;//����˳��
		/// <summary>
		/// ��FPGA����˳��
		/// </summary>
		uint16 fpgaCmmIndex;
		uint16 dataElementNum;
		uint8 dataType[CN_GOOSEMaxCellNum];
		uint16 dataNumSub;
		uint16 dataLinkedNum[CN_GOOSEMaxCellNum];
		uint16 dataGroupId[CN_GOOSEMaxCellNum][CN_OneGooseLinkMax];
		uint16 dataInstId[CN_GOOSEMaxCellNum][CN_OneGooseLinkMax];
		uint16 dataCardPort[CN_GOOSEMaxCellNum][CN_OneGooseLinkMax];
		struct Control
		{
			uint8 cbRefLen;
			char cbRef[256];
			uint32 confRev;
			uint8 appIDLen;
			char appID[256];
			uint8 datSetLen;
			char datSet[150];
			uint8 datSetRefLen;
			char datSetRef[150];
			uint32 timetolive;
			uint8 nameLen;
			char name[150];
		}control;
		struct Connect
		{
			uint32 minTimeMs;
			uint32 maxTimeMs;
			char apName[64];
			uint8 apNameLen;
			char iedName[64];
			uint8 iedNameLen;
			GoSvAddressInfo addr;
			uint8 PortEnableNum;//ʹ���˽��յĸ���(AB����һ��)
			uint8 APortEnable[40];//���ն˿����ý���ʹ��
			uint16 ACard_Port[40];//���ն˿����ð忨�������ں�
			uint8 BPortEnable[40];//���ն˿����ý���ʹ��
			uint16 BCard_Port[40];//���ն˿����ð忨�������ں�
			uint16 AInnerPortIndex[40];//�����ڲ��˿����÷����Ķ˿�
			uint16 BInnerPortIndex[40];//�����ڲ��˿����÷����Ķ˿�
		}connect;
		struct FrameInfo
		{
			bool8 frameOk;
			uint16 frameLen;
			uint16 utcOffSet;
			uint16 stOffSet;
			uint16 sqOffSet;
			uint16 testOffSet;
			uint16 dataSetOffSet;//pos of date set
			uint16 dataSetLen;
			uint8 dataLen[CN_GOOSEMaxCellNum];//(���ݲ��ֳ���)
			uint16 dataSetTagOffSet[CN_GOOSEMaxCellNum];//��dataSetOffSetΪ��׼��tag��ƫ��
			uint16 dataSetDataOffSet[CN_GOOSEMaxCellNum];//��dataSetOffSetΪ��׼�����ݵ�ƫ��
			uint8 templete[CN_MaxEhtFrameLen];
			uint32 res;
		}frame;
	};
	struct SVcbInfo
	{
		/// <summary>
		/// ���ƿ��뱾��IOģ�������쳣
		/// </summary>
		bool8 cfgErr;
		/// <summary>
		/// ���ƿ�����쳣
		/// </summary>
		bool8 parseErr;
		/// <summary>
		/// ��������ַ�쳣
		/// ������CCD�����쳣
		/// </summary>
		bool8 sAddrErr;
		bool8 linked;
		uint16 index;
		/// <summary>
		/// ��FPGA����˳��
		/// </summary>
		uint16 fpgaCmmIndex;
		uint16 dataElementNum;
		uint16 dataElementSub;
		uint16 dataLinkedNum[CN_SvMaxCellNum];
		uint16 dataGroupId[CN_SvMaxCellNum][CN_OneSVLinkMax];
		uint16 dataInstId[CN_SvMaxCellNum][CN_OneSVLinkMax];
		uint16 dataCardPort[CN_SvMaxCellNum][CN_OneSVLinkMax];
		struct Control
		{
			uint8 cbRefLen;
			char cbRef[256];
			uint32 confRev;
			uint32 nofASDU;
			uint32 smpRate;//������
			bool8 SmvOpts_refreshTime;
			bool8 SmvOpts_sampleRate;
			bool8 SmvOpts_sampleSynchronized;
			bool8 SmvOpts_security;
			uint8 smvIDLen;
			char smvID[256];
			uint8 datSetLen;
			char datSet[150];
			uint8 datSetRefLen;
			char datSetRef[150];
			uint8 nameLen;
			char name[150];
		}control;
		struct Connect
		{
			char apName[20];
			uint8 apNameLen;
			char iedName[64];
			uint8 iedNameLen;
			GoSvAddressInfo addr;
			uint8 PortEnableNum;//�Ƿ�ʹ���˽���
			uint8 PortEnable[40];//���ն˿����ý���ʹ��
			uint16 Card_Port[40];//���ն˿����ð忨�������ں�
			uint16 InnerPortIndex[40];//�����ڲ��˿����÷����Ķ˿�
		}connect;
		struct FrameInfo
		{
			bool8 frameOk;
			uint16 frameLen;
			uint16 sampCountOffSet;//pos of tag samp count
			uint16 syncOffSet;//pos of tag sync
			uint16 dataSetOffSet;//pos of date set
			uint16 dataSetLen;
			uint8 templete[CN_MaxEhtFrameLen];
			uint8 stNum[6];
			uint8 stNumLen;
			uint8 sqNum[6];
			uint8 sqNumLen;
			uint32 res;
		}frame;
	};
	struct SptGoSvCcdParseInfo
	{
		uint16 goEnablePubNum;
		uint16 svEnablePubNum;
		uint16 svEnableSubNum;
		uint16 goEnableSubNum;
		uint16 goPubBufNum;
		uint16 goPubNum;
		GooseGocbInfo* gocbPub;
		uint16 svPubBufNum;
		uint16 svPubNum;
		SVcbInfo* svcbPub;
		uint16 svSubBufNum;
		uint16 svSubNum;
		SVcbInfo* svcbSub;
		uint16 goSubBufNum;
		uint16 goSubNum;
		GooseGocbInfo* gocbSub;
	};
	struct SptGoSvInfo
	{
		struct SptGoSvCcdParseInfo ParseInfo;
	};
	class SptCcdFile
	{
	public:
		struct OutStatus
		{
			uint32 fileCrc;//�ļ�Crc;
			bool8 fileNoExist;//�ļ�������
			bool8 parseErr;//ccd�����쳣
			bool8 crcErr;//crcУ���쳣
			bool8 attLost;//����ȱʧ
			bool8 attErr;//�����쳣
			bool8 frameLenOverFlow;//֡�������
			bool8 goosePubParseErr;//GOOSE���ͽ����쳣
			bool8 svPubParseErr;//SV���ͽ����쳣
			bool8 svSubParseErr;//SV���ս����쳣
			bool8 gooseSubParseErr;//SV���ս����쳣
		};
	public:
		M_Singleton(SptCcdFile);
		int32 PowerUpIni(int32 GoCbInMaxNum, int32 GoCbOutMaxNum, int32 SvCbInMaxNum, int32 SvCbOutMaxNum);
		/// <summary>
		/// CCD��ʼ����Ϣ
		/// </summary>
		/// <returns></returns>
		SptCcdFile::OutStatus& CcdParseStatus() { return outputstatus; };
		SptGoSvInfo& GoSvInfo() { return gosvInfo; };
		static uint8 GetGoSvDataTypeId(uint8 Id);
		static uint16 GetGoSvDataTypeLen(uint8 Id);
	protected:
		SptCcdFile();
		int32 ParseCCD(const char* FileName);
		int32 ParseGoosePub(const tinyxml2::XMLElement* node);
		int32 ParseGooseSub(const tinyxml2::XMLElement* node);
		int32 ParseGoosePubGoCb(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGooseSubGoCb(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGoosePubGoCbControl(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGooseSubGoCbControl(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGoosePubGoCbConnectedAP(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGooseSubGoCbConnectedAP(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGoosePubGoCbDataSet(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGooseSubGoCbDataSet(const tinyxml2::XMLElement* node, GooseGocbInfo* Info);
		int32 ParseGoSvDataType(const tinyxml2::XMLAttribute* node);
		int32 ParseSVPub(const tinyxml2::XMLElement* node);
		int32 ParseSVSub(const tinyxml2::XMLElement* node);
		int32 ParseSVPubCb(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseSVSubCb(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		void CreatFrameTemplete(SVcbInfo* Info);
		void CreatFrameTemplete(GooseGocbInfo* Info);
		int32 TagChanLenEncode(uint8* pLen, uint16 Len);
		int32 ParseSVPubCbDataSet(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseSVSubCbDataSet(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseSVPubCbControl(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseSVSubCbControl(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseSVPubConnectedAP(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseSVSubConnectedAP(const tinyxml2::XMLElement* node, SVcbInfo* Info);
		int32 ParseAddress(const tinyxml2::XMLElement* node, GoSvAddressInfo* Info);
		bool8 CalCcdCrc();
		static int32 GetGoSvDataTypeInfo(uint8 Id, uint8& FullLen, uint8& LenLen, uint8& DataLen);
		int32 EncodeGoSvDataTypeInfo(uint8* Buf, uint8 Id);
	protected:

	protected:
		OutStatus outputstatus;
		uint32 CrcFile;
		uint32 CrcCal;
		SptGoSvInfo gosvInfo;
	};

	class SptT860Info
	{
	public:

	public:
		M_Singleton(SptT860Info);
		int32 PowerUpIni(int32 Para);
		int32 CheckOutputDataSet();
	protected:
		SptT860Info();

		int32 LinkOutputDataSet();
	protected:

		bool8 enable;
	};

}



#endif