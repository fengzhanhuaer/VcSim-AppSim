#ifndef SPTAPPFLAGS_H
#define SPTAPPFLAGS_H

namespace spt
{
	typedef struct stAppFlags
	{
		/// <summary>
		/// ���Զ��״̬
		/// </summary>
		bool8 ckRemoteState;
		/// <summary>
		/// ����Զ��״̬
		/// </summary>
		bool8 protRemoteState;
		/// <summary>
		/// װ�ü���״̬
		/// </summary>
		bool8 unitTestState;
		/// <summary>
		/// װ�õ���״̬
		/// </summary>
		bool8 unitDebugState;
		/// <summary>
		/// װ�ó�ʼ����ɽ��빤��״̬
		/// </summary>
		bool8 blAppPowerUpIniOver;
		/// <summary>
		/// װ�ý��渴��(�̶�չ��200ms)
		/// </summary>
		bool8 blFaceRevert;
		/// <summary>
		/// װ�ø���(�̶�չ��2000ms),��Ӧ�ý�������
		/// </summary>
		bool8 blUnitRevert;
	}tsAppFlags;
	class SptFlags
	{
	public:
		/// <summary>
		/// װ�õ����ź�
		/// 20msȷ�ϣ�5ms����
		/// �����źų���50ms��ƽ̨��ʼ��ʼ½����������洢����ֵ�洢�ȹ���
		/// </summary>
		bool8 PowerDownFlags()const { return powerDownFlags; };
		/// <summary>
		/// �����ź�Ϊ1��ȥ��ǰ��ʼʱ�䣬ms
		/// </summary>
		uint32 PowerDownStartEdgeMs()const { return powerDownStartEdgeMs; };
		/// <summary>
		/// �����ź�(ȥ����)�Ƿ���ʱ�䷶Χ��
		/// </summary>
		/// <param name="LowLimit">����ʱ��ms</param>
		/// <param name="HighLimit">����ʱ��ms</param>
		/// <returns>�����ź�Ϊ0ʱ������0�������ź�Ϊ1ʱ���ж�ʱ�䷶Χ</returns>
		bool8 IsPowerDownAtRange(uint32 LowLimit, uint32 HighLimit)const;
		void SptFlagProcess();
	private:
		MsDelayTimer msPowerDownDelayTimer;
		bool8 powerDownFlags;
		uint32 powerDownStartEdgeMs;
	};
}


#endif // !SPTAPPFLAGS_H

