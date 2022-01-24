#ifndef APIFAULTRECORD_H
#define APIFAULTRECORD_H

namespace spt
{
	/// <summary>
	/// ����¼��������
	/// </summary>
	class ApiFwDigital :protected SalFwDigitalCfgSignal
	{
	public:
		/// <summary>
		/// ����¼����������ʼ��
		/// </summary>
		/// <param name="Name">����</param>
		/// <param name="DesName">������ַ</param>
		/// <param name="Group">���</param>
		/// <param name="Phase">���</param>
		/// <param name="Ccbm">һ���豸����</param>
		/// <param name="SteadyState">��ֵ̬</param>
		/// <param name="Flag">SalFwWaveCfgCell::uFlags</param>
		/// <param name="UpBeforeSetCnt">������ǰ¼������,������λ�ĵ�,����С�ڵ���ApiFwRecordGroup��UpBeforeSetCnt</param>
		/// <param name="UpAfterSetCnt">�����غ�¼������,����λ�ĵ�</param>
		/// <param name="DownBeforeSetCnt">�½���ǰ¼������,������λ�ĵ�,����С�ڵ���ApiFwRecordGroup��UpBeforeSetCnt</param>
		/// <param name="DownAfterSetCnt">�½��غ�¼������,����λ�ĵ�</param>
		/// <param name="IsDisp">�Ƿ���ʾ</param>
		void PowerUpIni(const char* Name, const char* DesName, class  ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp);
		/// <summary>
		/// ���ݸ���
		/// </summary>
		/// <param name="Value">1����ֵ������Ϊ0</param>
		void Update(uint32 Value);
		/// <summary>
		/// �����Ƿ���ʾ
		/// </summary>
		/// <param name="Disp"></param>
		void SetDisp(bool8 Disp);
	};
	/// <summary>
	/// ����¼��ģ����
	/// </summary>
	class ApiFwAnalog :protected SalFwAnalogCfgSignal
	{
	public:
		/// <summary>
		/// ����¼��ģ������ʼ��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Group"></param>
		/// <param name="Phase">���</param>
		/// <param name="Ccbm">һ������</param>
		/// <param name="Units">��λ</param>
		/// <param name="Skew">ͨ������</param>
		/// <param name="CoeA">ת��ϵ��CoeA</param>
		/// <param name="CoeB">ת��ϵ��CoeB</param>
		/// <param name="Primary">һ��ϵ��</param>
		/// <param name="Secondary">����ϵ��</param>
		/// <param name="IsPrimary">�Ƿ�Ϊһ��ֵ</param>
		/// <param name="Flag">SalFwWaveCfgCell::uFlags</param>
		/// <param name="IsDisp"></param>
		void PowerUpIni(const char* Name, const char* DesName, class  ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, const VarUnits& Units, float32 Skew, float32 CoeA, float32 CoeB, float32 Primary, float32 Secondary, bool8 IsPrimary, uint32 Flag, bool8 IsDisp);
		/// <summary>
		/// ���ݸ���
		/// </summary>
		/// <param name="Value"></param>
		void Update(float32 Value);
		/// <summary>
		/// ����ϵ��
		/// </summary>
		/// <param name="Primary">һ��ϵ��</param>
		/// <param name="Secondary">����ϵ��</param>
		void SetCoePS(float32 Primary, float32 Secondary);
		/// <summary>
		/// �����Ƿ���ʾ
		/// </summary>
		/// <param name="Disp"></param>
		void SetDisp(bool8 Disp);
	};
	/// <summary>
	/// ���ϼ�����
	/// </summary>
	class ApiFwEvent : protected SalFwEventCfgSignal
	{
	public:
		/// <summary>
		/// ���ϼ������ʼ��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Event"></param>
		/// <param name="Group"></param>
		/// <param name="Phase"></param>
		/// <param name="Ccbm"></param>
		/// <param name="SteadyState">��ֵ̬</param>
		/// <param name="Flag">SalFwWaveCfgCell::uFlags</param>
		/// <param name="UpBeforeSetCnt">������ǰ¼������,������λ�ĵ�,����С�ڵ���ApiFwRecordGroup��UpBeforeSetCnt</param>
		/// <param name="UpAfterSetCnt">�����غ�¼������,����λ�ĵ�</param>
		/// <param name="DownBeforeSetCnt">�½���ǰ¼������,������λ�ĵ�,����С�ڵ���ApiFwRecordGroup��UpBeforeSetCnt</param>
		/// <param name="DownAfterSetCnt">�½��غ�¼������,����λ�ĵ�</param>
		/// <param name="IsDisp"></param>
		void PowerUpIni(const char* Name, const char* DesName, ApiEvent& Event, class ApiFwRecordGroup& Group, E_Ang_Phase Phase, const char* Ccbm, bool8 SteadyState, uint32 Flag, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 DownBeforeSetCnt, uint16 DownAfterSetCnt, bool8 IsDisp);
		/// <summary>
		/// �����Ƿ���ʾ
		/// </summary>
		/// <param name="Disp"></param>
		void SetDisp(bool8 Disp);
	};
	/// <summary>
	/// ����¼��
	/// </summary>
	class ApiFwRecordGroup :protected SalFwRecordGroup
	{
	public:
		/// <summary>
		/// ����¼����ʼ��
		/// ϵͳƵ�ʡ�����������ApiAppCfg������
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="SysFreq">ϵͳ��̬Ƶ��</param>
		/// <param name="SampPerCircle">ÿ�ܲ�������</param>
		/// <param name="MaxRecordPoint">һ��¼��������,ÿ��֮���ѹ���ε�������60�����</param>
		/// <param name="UpBeforeSetCnt">��ʼ¼���ź�������ǰ¼������,����������е���������ǰ��¼������,����С��MaxRecordPoint</param>
		/// <param name="UpAfterSetCnt">��ʼ¼���ź������غ�¼������,����С��MaxRecordPoint</param>
		/// <param name="FwAngMaxNum">ģ���������</param>
		/// <param name="FwDigMaxNum">�����������</param>
		/// <param name="FwEventMaxNum">����������</param>
		/// <param name="Flag">SalFwRecordGroup::Flags</param>
		void PowerUpIni(const char* Name, const char* DesName, uint32 SysFreq, uint32 SampPerCircle, int32 MaxRecordPoint, uint16 UpBeforeSetCnt, uint16 UpAfterSetCnt, uint16 FwAngMaxNum, uint16 FwDigMaxNum, uint16 FwEventMaxNum, uint32 Flag);
		/// <summary>
		/// ����¼��
		/// </summary>
		/// <param name="isStart"></param>
		void StartRecord(bool8 isStart);
		/// <summary>
		/// ��¼һ��¼��
		/// ���������е���ֵ�������֮����е���
		/// ������StartRecord֮�����
		/// </summary>
		/// <param name="stamp">��ǰ¼��UTCʱ��</param>
		/// <param name="SampStamp">��ǰ¼������ʱ��</param>
		void RecordOnePoint(SalDateStamp& stamp, uint64 SampStamp);
		/// <summary>
		/// ���ù����Ĳ���
		/// </summary>
		/// <param name="Index">��0��ʼ�����Ϊ3</param>
		/// <param name="Group"></param>
		/// <returns></returns>
		int32 SetParaGroup(int32 Index, ApiParaGroup* Group);
		/// <summary>
		/// ���ö�������
		/// �����ڿ�ʼ¼���󣬽���¼��ǰ��������
		/// </summary>
		/// <param name="Type">SalFwData::ActStatus</param>
		/// <returns></returns>
		int32 SetActType(uint32 Type);
		/// <summary>
		/// ���¼��
		/// </summary>
		void ClearRecord();
	};
}

#endif // !APIFAULTRECORD_H

