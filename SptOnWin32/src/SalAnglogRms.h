#ifndef SalAnglogRms_H
#define SalAnglogRms_H

namespace spt
{
	enum E_Ang_Phase
	{
		EAP_Null,
		EAP_A,
		EAP_B,
		EAP_C,
		EAP_Z,
		EAP_AB,
		EAP_BC,
		EAP_CA,
		EAP_ABC,
		EAP_AZ,
		EAP_BZ,
		EAP_CZ,
		EAP_ABZ,
		EAP_BCZ,
		EAP_CAZ,
		EAP_ABCZ,
		EAP_Phase_Total
	};
	extern const SalEnumDes EPhaseStr[EAP_Phase_Total];
	const char* GetPhaseStr(uint32 Phase);
	enum E_Ang_Bit_Phase
	{
		EABP_Null,
		EABP_A = 0X01,
		EABP_B = 0X02,
		EABP_C = 0X04,
		EABP_Z = 0X08,
		EABP_AB = 0X03,
		EABP_BC = 0X06,
		EABP_CA = 0X05,
		EABP_ABC = 0X07,
		EABP_AZ = 0X09,
		EABP_BZ = 0X0A,
		EABP_CZ = 0X0C,
		EABP_ABZ = 0X0B,
		EABP_BCZ = 0X0E,
		EABP_CAZ = 0X0D,
		EABP_ABCZ = 0X0F,
		EABP_Phase_Total
	};
	uint32 ConvertAngBitPhase2AngPhase(uint32 BitPhase);
	//32位模拟量有效值
	typedef struct
	{
		int32 data1;
		int32 data2;
		uint32 q;
	}i32AngRms;
	class SalAngRms :public InstObject
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class SalAngRmsGroup* Group, bool8 IsBase, uint16 Data1DotNum, const VarUnits* Units1, uint16 Data2DotNum, const VarUnits* Units2, uint16 QLen);
		bool8 PushData(int32 Data1, int32 Data2, uint32 Q);
		uint32 DataNum();
		const i32AngRms& RealData();
		const VarUnits* Units1();
		const VarUnits* Units2();
		const VarUnits* TransUnits1();
		const VarUnits* TransUnits2();
		float32 Data1Coe() { return data1Coe; };
		float32 Data2Coe() { return data2Coe; };
		uint16 Data1DotNum()const { return data1DotNum; };
		uint16 Data2DotNum() const { return data1DotNum; };
		uint16 Data3Len() const { return data3Len; };
		bool8 IsBase()const { return isBase; };
		bool8 IsDisp();
	protected:
		bool8 isDisp;
		bool8 isBase;
		uint8 dataNum;
		i32AngRms angRms;
		uint8 data1DotNum;
		uint8 data2DotNum;
		uint8 data3Len;
		const VarUnits* oriunits1;
		const VarUnits* oriunits2;
		const VarUnits* transunits1;
		const VarUnits* transunits2;
		float32 data1Coe;
		float32 data2Coe;
		uint32 stateNum;
	};

	class SalAngRmsGroup :public InstObjectGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 BufLen);
		void Set(uint32 Index, const i32AngRms& Rms);
		void Update(bool8 AdJustAngle);
		uint32 GetNewestDataIndex();
		SalAngRms* Cell(uint32 InstId);
		const i32AngRms* GetRealData(uint32 BufIndex, uint32 InstId);
	private:
		bool8 startStore;
		RingBuf ringBuf;
	};


}


#endif // !SalAnglogRms_H

