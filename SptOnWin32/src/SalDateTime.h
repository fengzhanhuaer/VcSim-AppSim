#ifndef SALDATETIME_H
#define SALDATETIME_H

struct tm;

namespace spt
{
	/// <summary>
	/// ʱ���Ʒ��λ����
	/// </summary>
	union SalDateQ
	{
		struct
		{
			uint32 isLeap : 1;//����
			uint32 isNegLeap : 1;//������
			uint32 res : 3;
			//����8λΪ��׼��UTC��q��һ����,����61850-7-2��5.5.3.7.3.2 FractionOfSecond
			uint32 isSyncErr : 1;//�Ƿ�ͬ��ʧ��
			uint32 isClockErr : 1;//ʱ�ӹ���
			uint32 isLeapSecondKnown : 1;//�Ƿ���������
			//�����8λ���ڱ��ص������н��м�¼
			uint32 TimeAccuracy : 5;//ʱ�Ӿ��ȣ�1/TimeAccuracy����λΪ��
		}bits;
		uint32 q;
	};
	/// <summary>
	/// ��׼UTCʱ���
	/// </summary>
	struct SalStdUtcStamp
	{
		uint32 uSec;
		uint32 u_Fra_Q;//С�����ֵ�λΪus
	};
	/// <summary>
	/// ����ϵͳʱ���
	/// ��ȷ��us����ʼ�ڹ�Ԫ1��1��1�� 00:00:00
	/// </summary>
	struct SalDateStamp
	{
		uint32 usL;
		uint32 usH;
		SalDateQ q;
		SalDateQ Q() { return q; };
		int64 Us()const;//��ȡusʱ��
		void Set(int64 us);//����ʱ��
		void Now();//��ϵͳʱ�����ʱ��
		/// <summary>
		/// time_t: seconds since the Epoch 00:00:00 UTC, Jan 1, 1970)
		/// </summary>
		int64 toUtcSec();
		/// <summary>
		/// time_t: seconds since the Epoch 00:00:00 UTC, Jan 1, 1970)
		/// </summary>
		int64 fromUtcSec(int64 Sec);
		void toUtcCode(uint32& Sec, uint32& fractionAndQ);
		void fromUtcCode(uint32 Sec, uint32 fractionAndQ);
		void toPriUtcCode(uint32& Sec, uint32& fractionAndQ);
		void fromPriUtcCode(uint32 Sec, uint32 fractionAndQ);
		void Set(struct SalRtc* Rtc);
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void FromStrFmt1(const char* Str);
		/// <summary>
		/// Fmt is 2021-03-02 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void FromStrFmt2(const char* Str);
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt1(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt10(SalString& Str)const;
		/// <summary>
		/// Fmt is 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt11(SalString& Str)const;
		/// <summary>
		/// Fmt is 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt12(SalString& Str)const;
		/// <summary>
		/// Fmt is 13:06:08.123456
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt13(SalString& Str)const;
		/// <summary>
		/// Fmt is 02/03/2021
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt14(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt2(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021-03-02 13:06:08:123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt22(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08.123.456
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt3(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021��03��02�� 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void ToStrHzFmt1(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021��03��02�� 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrHzFmt2(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021��03��02�� 13:06:08.123.456
		/// </summary>
		/// <param name="Str"></param>
		void ToStrHzFmt3(SalString& Str)const;
		/// <summary>
		/// Fmt is 20210302
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt40(SalString& Str)const;
		/// <summary>
		/// Fmt is 130608
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt41(SalString& Str)const;
		/// <summary>
		/// Fmt is 20210302.130608
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt42(SalString& Str)const;
		/// <summary>
		/// Fmt is 20210302_130608_789
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt43(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08.123.456,Q
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt5(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08.123.456,Q
		/// </summary>
		/// <param name="Str"></param>
		void FromStrFmt5(const char* Str);
		/// <summary>
		/// Fmt is 2021��03��02�� 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void FromStrHzFmt1(const char* Str);
		/// <summary>
		/// Fmt is 2021��03��02�� 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void FromStrHzFmt2(const char* Str);
		/// <summary>
		/// Fmt is 2021��03��02�� 13:06:08.123.456
		/// </summary>
		/// <param name="Str"></param>
		void FromStrHzFmt3(const char* Str);
		void ToSNTPV4(uint32& sec, uint32& fraction)const;
		void FromSNTPV4(uint32 sec, uint32 fraction);
		/// <summary>
		/// Fmt is Jan 1 2021 13:06:08
		/// </summary>
		/// <param name="Date"></param>
		/// <param name="Time"></param>
		void FromStrBuild(const char* Date, const char* Time);
	public:
		static const uint32 Dt1MicroSecond = 1;
		static const uint32 Dt1MilliSecond = 1000 * Dt1MicroSecond;
		static const uint32 Dt1Second = 1000 * Dt1MilliSecond;
		static const uint32 Dt1Minute = Dt1Second * 60;
		static const uint32 Dt1Hour = Dt1Minute * 60;
		static const uint64 Dt1Day = (uint64)Dt1Hour * 24;
		static const uint64 UTCBASE = 62135596800000000;
		static const uint64 SNTPV4BASE = 59926608000000000;
	};
	/// <summary>
	/// ����ʱ��RTC
	/// </summary>
	struct SalRtc
	{
		uint8 q;//����Utc��Ʒ�ʵĵ�8λ
		uint8 month;///1~12
		uint8 day;///1~31
		uint8 hour;///0~23
		uint8 minute;///0~59
		uint8 second;///0~60
		uint16 year;///0~65535
		uint16 ms;///0~999
		uint16 us;///0~999
		// ��ȡ��ǰʱ��
		void Now();
		void FromTm(const struct tm* t);
		void ToTm(struct tm* t)const;
		int64 Stamp(); //��Ԫ1��1��1�� 00:00 : 00�����ʱ���
		void FromStamp(uint64 Us);
		void FromStamp(const struct SalDateStamp* t);
		//Fmt is 2021/03/02 13:06:08
		void FromStrFmt1(const char* Str);
		//Fmt is 2021-03-02 13:06:08
		void FromStrFmt2(const char* Str);
		//Fmt is Jan 1 2021 13:06:08
		void FromStrBuild(const char* Date, const char* Time);
		//Fmt is 2021/03/02 13:06:08
		void ToStrFmt1(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt10(SalString& Str)const;
		/// <summary>
		/// Fmt is 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt11(SalString& Str)const;
		/// <summary>
		/// Fmt is 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt12(SalString& Str)const;
		/// <summary>
		/// Fmt is 13:06:08.123456
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt13(SalString& Str)const;
		/// <summary>
		/// Fmt is 02/03/2021
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt14(SalString& Str)const;
		//Fmt is 2021/03/02 13:06:08.123
		void ToStrFmt2(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021-03-02 13:06:08:123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt22(SalString& Str)const;
		//Fmt is 2021/03/02 13:06:08.123.456
		void ToStrFmt3(SalString& Str)const;
		//Fmt is 20210302
		void ToStrFmt40(SalString& Str)const;
		//Fmt is 130608
		void ToStrFmt41(SalString& Str)const;
		//Fmt is 20210302.130608
		void ToStrFmt42(SalString& Str)const;
		//Fmt is 20210302_130608_789
		void ToStrFmt43(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08.123.456,Q
		/// </summary>
		/// <param name="Str"></param>
		void ToStrFmt5(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021/03/02 13:06:08.123.456,Q
		/// </summary>
		/// <param name="Str"></param>
		void FromStrFmt5(const char* Str);
		// Fmt is 2021��03��02�� 13:06:08
		void ToStrHzFmt1(SalString& Str)const;
		//Fmt is 2021��03��02�� 13:06:08.123
		void ToStrHzFmt2(SalString& Str)const;
		//Fmt is 2021��03��02�� 13:06:08.123.456
		void ToStrHzFmt3(SalString& Str)const;
		//Fmt is 2021��03��02�� 13:06:08
		void FromStrHzFmt1(const char* Str);
		//Fmt is 2021��03��02�� 13:06:08.123
		void FromStrHzFmt2(const char* Str);
		//Fmt is 2021��03��02�� 13:06:08.123.456
		void FromStrHzFmt3(const char* Str);
		void Check();
	};

	class DatePara : CfgFile
	{
	public:
		enum E_MODE
		{
			E_LocalRun = 0,//������ʱ
			E_SNTP,//SNTP
			E_ELE_IRIG_B,//��B��
			E_LIGHT_IRIG_B,//��B��
			E_SubBoard,//�Ӱ忨
			E_Total,//
		};
		static SalEnumDes Mode[E_Total];
	public:
		int32 PowerUpIni(int32 Para);
		M_Singleton(DatePara);
	public:
		CfgUint32 AdJustMode;//Уʱ��ʽ
		CfgUint32 IrigB_Precision;//B��ʱ�Ӿ���
		CfgUint32 IrigB_Delay;//B��ʱ�Ӷ��ʱ
		CfgUint32 IrigB_AckCnt;//B��ʱ��ͬ��ȷ��ʱ��
		CfgUint32 IrigB_UnSynCnt;//B��ʱ��ʧ��ȷ��ʱ��
		CfgInt32 IrigB_CheckCode;//B��У�鷽ʽ
		CfgInt32 IrigB_HostContDif;//B��֡������ֵ
		CfgUint32 IrigB_ReSyncDif;//B����ͬ����ֵ
		CfgInt32 TimeZone;//����ʱ��-12~12
	protected:
		virtual PCfgDataBase* CfgPool() { return pool; };
		virtual uint32 CfgPoolSize() { return M_ArrLen(pool); };
		DatePara();
	private:
		PCfgDataBase pool[60];
	};
	bool8 IsLeapYear(uint16 Year);
	class DateUpdate
	{

	public:
		union UpdateFpgaFrameCfg
		{
			struct
			{
				uint8 LightOrEle : 1;//0���ʱ��1���ʱ
				uint8 DisableIrigB : 1;//��ֹB���ʱ
				uint8 CheckMode : 2;//00��У�飬01 ��У�飬10żУ��
			}bits;
			uint8 u8;
		};
		struct UpdateFpgaFrame
		{
			uint16 FrmNo;
			uint8 UpdateFlag;//0xAA:CPU����FPGAʱ��-ֻ��������Ϣ0x55:CPU����FPGAʱ��-�����뼰������Ϣ0x00:FPGA����ά��ʱ��
			uint8 FeedDog;//0xAA:CPUָʾFPGAι��  0x00:CPUָʾFPGA��ֹι��
			uint8 Cfg;
			uint8 UtcSec[4];
			uint8 UtcUs_Q[4];
			uint8 Bcd_Sec;
			uint8 Sum_L;
			uint8 Sum_H;
		};
		//DLT 1100.1-2009 ����ϵͳ��ʱ��ͬ��ϵͳ ��1���֣������淶
		union FpgaTimeFrame
		{
			struct FpgaMuTimeFrame
			{
				uint16 frmNo;
				uint16 SvSyn;//SVͬ����־
				uint8 utcSec[4];
				uint8 utcFrq_Q[4];
				uint8 irigb_Stat;//bit 0 У�����
				uint8 irigb[16];
				uint8 res[8];
			}muframe;
			uint8 buf[256];
		};
		struct OutPut
		{
			uint64 recFrameNum;//���յ���֡��
			uint8 Irig_B_precision;//B�뾫��
			bool8 HostBCodeCheckAlarm;//B��У���쳣
			bool8 HostBCodePrecisionAlarm;//B�뾫���쳣
			bool8 HostTPortAlarm;//��ʱ�ź�״̬
			bool8 HostTSrvAlarm;//��ʱ����״̬
			bool8 HostContAlarm;//֡�����쳣
		};
		struct State
		{
			bool8 recMoudlePowerInied;//����ģ���ʼ�����
			bool8 frmDateUpdate;//�յ�FPGA����֡
			bool8 frmDownFpgaTimeUpdate;//�·�FPGAʱ��֡
			bool8 frmFpgaTimeInied;//FPGAʱ���ʼ����־
			bool8 frmFpgaForceUpdateSec;//ǿ�Ƹ���FPGAʱ��
			bool8 IrigBSynOk;//B��ͬ���ɹ�
			bool8 IrigBPowerUpSynOk;//B������ͬ���ɹ�
			uint8 IrigBProcessRecOkCnt;//B�����ͬ����������ȷ����
			bool8 isHmiSetStamp;//Hmi����ʱ���־
			bool8 isSntpSetStamp;//Sntp����ʱ���־
			uint8 forceSetStampDelay;//����ϵͳʱ�����ʱʹ��FPGAʱ��
			uint8 IrigBContAlmCnt;//֡����澯��������
			uint8 IrigBContRevertCnt;//֡���临����������
			bool8 IrigBHasLost;//B���ж�ʧ
		};
	public:
		virtual void UpdateTimeInMsInt(SalDateStamp& Stamp) {};
		virtual void UpdateTimeInSampInt(SalDateStamp& Stamp) {};
		virtual void UpdateTimeInTask(SalDateStamp& Stamp) {};
		virtual void GetHwTime(SalDateStamp& Stamp);
		virtual void SetHwTime(SalDateStamp& Stamp);
		virtual void RecFpgaMsg(uint8* buf, uint32 MsgLen);
		bool8 HmiSetDateTime(const SalDateStamp& Stamp);
		const struct OutPut& Output();
	protected:
		DateUpdate();
	protected:
		UpdateFpgaFrame updateFrame;
		FpgaTimeFrame frmDate;
		State state;
		MsTimer localIrigBLostTimer;//B�붪ʧʱ��
		MsTimer localIrigBCheckPortErr;//����δ�յ���B��ʱ��B������쳣
		MsTimer localIrigBCheckPortOk;//����δ�յ���B��ʱ��B������쳣
		MsTimer localIrigBCheckSrvErr;//����δ�յ���B��ʱ��B������쳣
		MsStampTimer localIrigBCheckLost;// ���B���Ƿ�����ж�
		MsStampTimer localIrigBCheckCont;// ���B���Ƿ�����
		OutPut output;
		SalDateStamp hmiSetStamp;//Hmi����ʱ��
		SalDateStamp sntpSetStamp;//sntp����ʱ��
		SalRtc realTimeIrigBRtc;//ʵʱB��
		SalStdUtcStamp realTimerFpgaUtc;//ʵʱFpgaUtc
		SalDateStamp lastTimeIrigBStamp;//�ϴ��յ���B��ʱ��

	};
	class GzkToolsDateUpdate :public DateUpdate
	{
	public:
		void UpdateFromIrigB(SalDateStamp& Stamp);
		void UpdateFromSntp(SalDateStamp& Stamp);
	public:
		virtual void UpdateTimeInMsInt(SalDateStamp& Stamp);
		virtual void UpdateTimeInSampInt(SalDateStamp& Stamp);
	};
	class PcSimDateUpdate :public GzkToolsDateUpdate
	{
	public:
		virtual void UpdateTimeInTask(SalDateStamp& Stamp);
	public:

	};
	class Gzk35kVDateUpdate :public GzkToolsDateUpdate
	{
	public:
		Gzk35kVDateUpdate(SalDateStamp* SysStamp);
	public:
		virtual void UpdateTimeInMsInt(SalDateStamp& Stamp);
		virtual void UpdateTimeInSampInt(SalDateStamp& Stamp);
		virtual void SetHwTime(SalDateStamp& Stamp);
		void SetStampInMsInt(SalDateStamp& Stamp);
	private:
		SalDateStamp* SysStamp;
	};
	class GzkSauDateUpdate :public GzkToolsDateUpdate
	{
	public:

	public:
		virtual void SetHwTime(SalDateStamp& Stamp);
		virtual void UpdateTimeInSampInt(SalDateStamp& Stamp);
		void UpdateFpgaTime();
	private:
		void UpdateMainBoard(SalDateStamp& Stamp);
		void UpdateSubBoard(SalDateStamp& Stamp);
	};

	class SptDateTask :public Task
	{
	public:

	public:
		static SptDateTask& Instance();
		void UpdateTimeInMsInt();
		void UpdateTimeInSampInt();
		virtual int32 PowerUpIni(int32 Para);
		const SalDateStamp& Now();
		void RecFpgaMsg(uint8* buf, uint32 MsgLen);
		bool8 HmiSetDateTime(const SalDateStamp& Stamp);
		void ForceUpdateHwRtc();
		void ForceGetRtcFromHw();
		DateUpdate* UpdateHandle() { return update; };
	protected:
		virtual int32 OneLoop();
		SptDateTask();
		void UpdateStatus();
	protected:
		bool8 forceUpdateHwRtc;
		SalDateStamp localStamp;
		DateUpdate* update;
		MsTimer localRtcSetMsTimer;
	};
}

#endif // !SALDATETIME_H

