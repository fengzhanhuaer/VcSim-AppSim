#ifndef SALDATETIME_H
#define SALDATETIME_H

struct tm;

namespace spt
{
	/// <summary>
	/// 时间戳品质位定义
	/// </summary>
	union SalDateQ
	{
		struct
		{
			uint32 isLeap : 1;//闰秒
			uint32 isNegLeap : 1;//负闰秒
			uint32 res : 3;
			//以下8位为标准的UTC的q的一部分,出自61850-7-2：5.5.3.7.3.2 FractionOfSecond
			uint32 isSyncErr : 1;//是否同步失败
			uint32 isClockErr : 1;//时钟故障
			uint32 isLeapSecondKnown : 1;//是否处理了闰秒
			//上面的8位，在本地的事项中进行记录
			uint32 TimeAccuracy : 5;//时钟精度，1/TimeAccuracy，单位为秒
		}bits;
		uint32 q;
	};
	/// <summary>
	/// 标准UTC时间戳
	/// </summary>
	struct SalStdUtcStamp
	{
		uint32 uSec;
		uint32 u_Fra_Q;//小数部分单位为us
	};
	/// <summary>
	/// 本地系统时间戳
	/// 精确到us，起始于公元1年1月1日 00:00:00
	/// </summary>
	struct SalDateStamp
	{
		uint32 usL;
		uint32 usH;
		SalDateQ q;
		SalDateQ Q() { return q; };
		int64 Us()const;//获取us时标
		void Set(int64 us);//设置时标
		void Now();//用系统时间更新时标
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
		/// Fmt is 2021年03月02日 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void ToStrHzFmt1(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021年03月02日 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void ToStrHzFmt2(SalString& Str)const;
		/// <summary>
		/// Fmt is 2021年03月02日 13:06:08.123.456
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
		/// Fmt is 2021年03月02日 13:06:08
		/// </summary>
		/// <param name="Str"></param>
		void FromStrHzFmt1(const char* Str);
		/// <summary>
		/// Fmt is 2021年03月02日 13:06:08.123
		/// </summary>
		/// <param name="Str"></param>
		void FromStrHzFmt2(const char* Str);
		/// <summary>
		/// Fmt is 2021年03月02日 13:06:08.123.456
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
	/// 本地时间RTC
	/// </summary>
	struct SalRtc
	{
		uint8 q;//本地Utc的品质的低8位
		uint8 month;///1~12
		uint8 day;///1~31
		uint8 hour;///0~23
		uint8 minute;///0~59
		uint8 second;///0~60
		uint16 year;///0~65535
		uint16 ms;///0~999
		uint16 us;///0~999
		// 获取当前时标
		void Now();
		void FromTm(const struct tm* t);
		void ToTm(struct tm* t)const;
		int64 Stamp(); //公元1年1月1日 00:00 : 00至今的时间戳
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
		// Fmt is 2021年03月02日 13:06:08
		void ToStrHzFmt1(SalString& Str)const;
		//Fmt is 2021年03月02日 13:06:08.123
		void ToStrHzFmt2(SalString& Str)const;
		//Fmt is 2021年03月02日 13:06:08.123.456
		void ToStrHzFmt3(SalString& Str)const;
		//Fmt is 2021年03月02日 13:06:08
		void FromStrHzFmt1(const char* Str);
		//Fmt is 2021年03月02日 13:06:08.123
		void FromStrHzFmt2(const char* Str);
		//Fmt is 2021年03月02日 13:06:08.123.456
		void FromStrHzFmt3(const char* Str);
		void Check();
	};

	class DatePara : CfgFile
	{
	public:
		enum E_MODE
		{
			E_LocalRun = 0,//本地守时
			E_SNTP,//SNTP
			E_ELE_IRIG_B,//电B码
			E_LIGHT_IRIG_B,//光B码
			E_SubBoard,//从板卡
			E_Total,//
		};
		static SalEnumDes Mode[E_Total];
	public:
		int32 PowerUpIni(int32 Para);
		M_Singleton(DatePara);
	public:
		CfgUint32 AdJustMode;//校时方式
		CfgUint32 IrigB_Precision;//B码时钟精度
		CfgUint32 IrigB_Delay;//B码时钟额定延时
		CfgUint32 IrigB_AckCnt;//B码时钟同步确认时间
		CfgUint32 IrigB_UnSynCnt;//B码时钟失步确认时间
		CfgInt32 IrigB_CheckCode;//B码校验方式
		CfgInt32 IrigB_HostContDif;//B码帧跳变阈值
		CfgUint32 IrigB_ReSyncDif;//B码再同步阈值
		CfgInt32 TimeZone;//本地时区-12~12
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
				uint8 LightOrEle : 1;//0光对时、1电对时
				uint8 DisableIrigB : 1;//禁止B码对时
				uint8 CheckMode : 2;//00无校验，01 奇校验，10偶校验
			}bits;
			uint8 u8;
		};
		struct UpdateFpgaFrame
		{
			uint16 FrmNo;
			uint8 UpdateFlag;//0xAA:CPU更新FPGA时间-只更新秒信息0x55:CPU更新FPGA时间-更新秒及毫秒信息0x00:FPGA继续维护时间
			uint8 FeedDog;//0xAA:CPU指示FPGA喂狗  0x00:CPU指示FPGA终止喂狗
			uint8 Cfg;
			uint8 UtcSec[4];
			uint8 UtcUs_Q[4];
			uint8 Bcd_Sec;
			uint8 Sum_L;
			uint8 Sum_H;
		};
		//DLT 1100.1-2009 电力系统的时间同步系统 第1部分：技术规范
		union FpgaTimeFrame
		{
			struct FpgaMuTimeFrame
			{
				uint16 frmNo;
				uint16 SvSyn;//SV同步标志
				uint8 utcSec[4];
				uint8 utcFrq_Q[4];
				uint8 irigb_Stat;//bit 0 校验错误
				uint8 irigb[16];
				uint8 res[8];
			}muframe;
			uint8 buf[256];
		};
		struct OutPut
		{
			uint64 recFrameNum;//接收到的帧数
			uint8 Irig_B_precision;//B码精度
			bool8 HostBCodeCheckAlarm;//B码校验异常
			bool8 HostBCodePrecisionAlarm;//B码精度异常
			bool8 HostTPortAlarm;//对时信号状态
			bool8 HostTSrvAlarm;//对时服务状态
			bool8 HostContAlarm;//帧跳变异常
		};
		struct State
		{
			bool8 recMoudlePowerInied;//接收模块初始化完毕
			bool8 frmDateUpdate;//收到FPGA更新帧
			bool8 frmDownFpgaTimeUpdate;//下发FPGA时间帧
			bool8 frmFpgaTimeInied;//FPGA时间初始化标志
			bool8 frmFpgaForceUpdateSec;//强制更新FPGA时间
			bool8 IrigBSynOk;//B码同步成功
			bool8 IrigBPowerUpSynOk;//B码曾经同步成功
			uint8 IrigBProcessRecOkCnt;//B码接收同步过程中正确计数
			bool8 isHmiSetStamp;//Hmi更新时间标志
			bool8 isSntpSetStamp;//Sntp更新时间标志
			uint8 forceSetStampDelay;//设置系统时间后延时使用FPGA时间
			uint8 IrigBContAlmCnt;//帧跳变告警连续计数
			uint8 IrigBContRevertCnt;//帧跳变复归连续计数
			bool8 IrigBHasLost;//B码有丢失
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
		MsTimer localIrigBLostTimer;//B码丢失时间
		MsTimer localIrigBCheckPortErr;//（从未收到过B码时）B码接收异常
		MsTimer localIrigBCheckPortOk;//（从未收到过B码时）B码接收异常
		MsTimer localIrigBCheckSrvErr;//（从未收到过B码时）B码接收异常
		MsStampTimer localIrigBCheckLost;// 检查B码是否出现中断
		MsStampTimer localIrigBCheckCont;// 检查B码是否连续
		OutPut output;
		SalDateStamp hmiSetStamp;//Hmi设置时间
		SalDateStamp sntpSetStamp;//sntp设置时间
		SalRtc realTimeIrigBRtc;//实时B码
		SalStdUtcStamp realTimerFpgaUtc;//实时FpgaUtc
		SalDateStamp lastTimeIrigBStamp;//上次收到的B码时标

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

