#ifndef APIPARA_H
#define APIPARA_H

namespace spt
{
	/// <summary>
	/// ����������
	/// </summary>
	class ApiParaGroup :protected SalParaGroup
	{
	public:
		/// <summary>
		/// ��ȡ����CRCУ���
		/// </summary>
		/// <param name="Zone"></param>
		/// <returns></returns>
		uint32 GetCrc(uint16 Zone);//��ȡ��ֵCRC
		uint16 CurZone();//��ȡ��ǰ���,��0��ʼ
		/// <summary>
		/// ��ʼ����ֵ��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="CurZone">��0��ʼ����ǰ���</param>
		/// <param name="MaxZone">�����ţ����ֻ��һ�飬����1�������Ų��ܳ���30</param>
		/// <param name="ElementNum"></param>
		void PowerUpIni(const char* Name, const char* DesName, uint16 CurZone, uint16 MaxZone, uint16 ElementNum);
		/// <summary>
		/// ��ʼ����ֵ��(��һ�鶨ֵ)
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="ElementNum"></param>
		void PowerUpIni(const char* Name, const char* DesName, uint16 ElementNum);
		int32 CheckStatus();//1 is ok,others is error.
		int32 CheckStatus(uint16 Zone);//1 is ok,others is error.
		int32 DefaultData();//Ĭ�϶�ֵ
		uint16 DataChangeCnt();//��ֵ���±�־��1~255��ÿ�ζ�ֵ�洢����ֵ��һ(���ж�ֵ����)
		uint16 DataChangeCnt(uint16 Zone);//��ֵ���±�־��1~255��ÿ�ζ�ֵ�洢����ֵ��һ
		/// <summary>
		/// ����ֵ������Ӧ��ʹ����
		/// ÿ�ζ�ֵ���º�Ӧ����Ҫ��������
		/// </summary>
		/// <returns></returns>
		bool8 UpdateForUse();
		const stAppFlags* AppFlags()const;
		/// <summary>
		/// ��ȡ�洢���̲���
		/// </summary>
		/// <param name="Zone"></param>
		/// <returns>�μ� E_SaveStep </returns>
		int32 GetSaveStepFlag(uint32 Zone);
		/// <summary>
		/// �����ò���תΪ��ʽ������ʹ��
		/// </summary>
		/// <param name="ZoneNum"></param>
		/// <returns></returns>
		int32 LoadBakParaForUse(int32 ZoneNum);
	};
	/// <summary>
	/// ����Ԫ��
	/// </summary>
	class ApiPara :protected SalPara
	{
	public:
		/// <summary>
		/// ͨ���Ͷ�ֵ��INT32��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Min"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="DotNum"></param>
		/// <param name="Units"></param>
		void PowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units);
		/// <summary>
		/// ͨ���Ͷ�ֵ��INT32��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Min"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="DotNum"></param>
		/// <param name="Units"></param>
		/// <param name="ExInfo">��Ӧ������</param>
		void PowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units, int32 ExInfo);
		void SetRange(int32 Max, int32 Min);//���ö�ֵ������
		void SetDisp(bool8 Disp);//���ö�ֵ�Ƿ����չʾ
		int32 Int32();//��ǰ�鶨ֵ��ֵ��������
		float32 Float32();//��ǰ�鶨ֵ��ֵ��������
		//Bool�Ͷ�ֵ
		void BlPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default);
		bool8 Bool();
		//�ַ��Ͷ�ֵ
		// MaxLen ���ֵΪ40
		void StrPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, const char* DefName);
		const char* StrData();//��ǰ�鶨ֵ��ֵ
		//ֻ���Ͷ�ֵ�����綨ֵ����
		void ZonePowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units);
		//ö���Ͷ�ֵ��Ĭ��ֵ��д����ö�ٵ���ţ�����ö�ٵ�ֵ
		void EnumPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default, SalEnumDes* Enum, uint8 EnumNum, const VarUnits& Units);
		int32 EnumIndex();
		int32 EnumVal();
		//CT����ֵ
		void CTEnumPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default);
		int32 CtValue();
		//����CT����ֵ�ĵ����Ͷ�ֵ,���ඨֵ���ڱ༭ʱ���������Сֵ����ct����ֵ����,���ֵ����Сֵ������1A��д��Ĭ��ֵ��д1A��5A������Ӧ���м�ֵ
		void RelatedCTPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Min, int32 Default, int32 Max, uint8 DotNum, const VarUnits& Units, ApiPara& SecondCt);
		//���Ͷ��
		void UnitOnOffPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, int32 Default);
		/// <summary>
		/// �����Ͷ�ֵ
		/// </summary>
		/// <param name="Name">����</param>
		/// <param name="DesName">������ַ</param>
		/// <param name="Group">ʵ����</param>
		/// <param name="Default">Ĭ��ֵ</param>
		/// <param name="Max">���ֵ</param>
		/// <param name="ByteNum">�ֽ���</param>
		/// <param name="Des">���ȱ���ΪByteNum*8</param>
		void BitOnOffPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint32 ByteNum, SalBitDes* Des);
		/// <summary>
		/// Hex�Ͷ�ֵ
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="ByteNum"></param>
		void HexPowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint32 ByteNum);
		/// <summary>
		/// �޷���32λ���ͣ�����PTCTϵ��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Min"></param>
		/// <param name="Default"></param>
		/// <param name="Max"></param>
		/// <param name="DotNum"></param>
		/// <param name="Units"></param>
		/// <param name="ExInfo">��Ӧ������</param>
		void UInt32PowerUpIni(const char* Name, const char* DesName, class ApiParaGroup& Group, uint32 Min, uint32 Default, uint32 Max, uint8 DotNum, const VarUnits& Units, int32 ExInfo);
		uint32 Uint32();
	protected:

	};
}

#endif // !APIPARA_H

