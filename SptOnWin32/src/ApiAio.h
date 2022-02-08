#ifndef  APIAIO_H
#define APIAIO_H
namespace spt
{
	/** @defgroup ApiIOAnalogIO
	* ģ�����������ģ��
	* @{
	*/
	/// <summary>
	/// ģ��������֡������
	/// </summary>
	class ApiBoardAngFrameIn :protected SptAngVirInputBoard
	{
	public:
		/// <summary>
		/// ����ģ����֡�ϵ��ʼ��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="FrameNo"></param>
		/// <param name="ElementNum">Ԫ����Ŀ</param>
		/// <param name="AdNum">AD����Ŀ</param>
		/// <param name="AdNodeNum">ÿ��AD��Ч�ܽŵ���Ŀ</param>
		void PowerUpIni(const char* Name, const char* DesName, uint16 FrameNo, uint16 ElementNum, uint32 AdNum, uint8 AdNodeNum);
		/// <summary>
		/// �������
		/// </summary>
		/// <returns></returns>
		uint32 StateNum();
		void SetOutValue(uint32 Index, int32 Value);
		/// <summary>
		/// ��������֡��˳������Coe��ע:��AD˳��һ��һ�£�ADϵ�����òμ�ApiNormalAngIn::SetAdCoe
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetOutCoe(uint32 Index, uint32 Value);
		/// <summary>
		/// ����ADУ׼ϵ��
		/// </summary>
		/// <param name="ADIndex">AD���</param>
		/// <param name="AdNode">AD���Ӻ�</param>
		/// <param name="Value"></param>
		void SetOutCoe(uint32 ADIndex, uint32 AdNode, uint32 Value);
		/// <summary>
		/// ����AD΢��ϵ��
		/// </summary>
		/// <param name="AdNo"></param>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetADAdJust(uint32 AdNo, uint32 Index, uint32 Value);
		/// <summary>
		/// ����ADֱ��΢��ϵ��
		/// </summary>
		/// <param name="AdNo"></param>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetAdDcAdJust(uint32 AdNo, uint32 Index, int32 Value);
		/// <summary>
		/// ���÷��͵�Qֵ
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="Value"></param>
		void SetOutQ(uint32 Index, uint32 Value);
		/// <summary>
		/// �Լ�״̬
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	};
	/// <summary>
	/// ����ģ��������忨
	/// </summary>
	class ApiBoardNormalAngIn :protected SptNormalAngInBoard
	{
	public:
		/// <summary>
		/// �ϵ��ʼ��
		/// </summary>
		/// <param name="Name"></param>
		/// <param name="DesName"></param>
		/// <param name="Frame"></param>
		/// <param name="CardType"></param>
		/// <param name="CardAddr"></param>
		void PowerUpIni(const char* Name, const char* DesName, ApiBoardAngFrameIn& Frame, uint16 CardType, uint16 CardAddr);
		/// <summary>
		/// �Լ�״̬
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	};
	/// <summary>
	/// ����ģ��������
	/// </summary>
	class ApiNormalAngIn :protected SptNormalAngSampCell
	{
	public:
		/// <summary>
		/// �ϵ��ʼ��
		/// </summary>
		/// <param name="Board"></param>
		/// <param name="Name">�ź�����</param>
		/// <param name="DesName">�����</param>
		/// <param name="Node">������ţ��ڵ��忨���нڵ����ֵ����0��ʼ</param>
		/// <param name="AdIndex">AD��</param>
		/// <param name="AdNode">AD���Ӻ�</param>
		/// <param name="Units"></param>
		void PowerUpIni(class ApiBoardNormalAngIn& Board, const char* Name, const char* DesName, uint16 Node, uint16 AdIndex, uint16 AdNode, const VarUnits& Units);
		int32 Value();
		int32 Value(uint32 Index);
		/// <summary>
		/// ����ADУ׼ϵ��
		/// </summary>
		/// <param name="Value"></param>
		void SetAdCoe(uint32 Value);
		/// <summary>
		/// �������
		/// </summary>
		/// <returns></returns>
		uint32 StateNum();
		/// <summary>
		/// ���÷�����
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetReversal(bool8 Flag);
		/// <summary>
		/// ���õ�AD��־
		/// </summary>
		/// <param name="IsSingle"></param>
		/// <returns></returns>
		bool8 SetSingleAdFlag(bool8 IsSingle);
	};
	/** @brief SV�������ݼ� */
	class ApiSvInVirBoard : protected SptSvInDataSet
	{
	public:
		//ElementNum����忨Ԫ�ظ���
		void PowerUpIni(const char* Name, const char* DesName, ApiBoardAngFrameIn& Frame, uint16 ElementNum);
		bool8 IsEnable();
		/// <summary>
		/// �Լ�״̬
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// �����쳣
		/// </summary>
		/// <returns></returns>
		bool8 CfgErr();
		/// <summary>
		/// �����쳣
		/// </summary>
		/// <returns></returns>
		bool8 ParseErr();
		/// <summary>
		/// CCD������Ϣ
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct SVcbInfo* SvCbInfo();
	};
	/// <summary>
	/// SV������Ϣ
	/// </summary>
	class ApiSvIn : protected SptSampAng_9_2SampCell
	{
	public:
		//Name�ź�����
		//DesName�����
		//Node������ţ��ڵ��忨���нڵ����ֵ����0��ʼ
		//FrameIndex���ڿ���֡�����˳���
		void PowerUpIni(class ApiBoardAngFrameIn& Board, const char* Name, const char* DesName, uint16 Node, const VarUnits& Units);
		//������Ƿ�����
		bool8 IsLinked();
		uint16 FrameIndex();
		uint16 Node();
		int32 Value();
		/**
		 * @brief ��ȡApiSvIn����ֵ.
		 *
		 * \param Index 0����ǰֵ��1������һ�㣬��������
		 * \return
		 */
		int32 Value(uint32 Index);
		uint32 Q();
		uint32 Q(uint32 Index);
		//�������
		uint32 StateNum();
		//���÷�����
		bool8 SetReversal(bool8 Flag);
		ApiSvInVirBoard* DataSet();
	};
	/// <summary>
	/// ���SV������Ϣ
	/// </summary>
	class ApiBoardCmmSvIn : protected SptSampAng_9_2SampCell
	{
	public:
		//Name�ź�����
		//DesName�����
		//Node������ţ��ڵ��忨���нڵ����ֵ����0��ʼ
		//FrameIndex���ڿ���֡�����˳���
		void PowerUpIni(class ApiBoardAngFrameIn& Board, const char* Name, const char* DesName, uint16 Node, const VarUnits& Units);
		int32 Value();
		int32 Value(uint32 Index);
		uint32 Q();
		uint32 Q(uint32 Index);
		//�������
		uint32 StateNum();
		//���÷�����
		bool8 SetReversal(bool8 Flag);
		/// <summary>
		/// ��������״̬
		/// </summary>
		/// <param name="Flag">�Ƿ�ʹ��</param>
		/// <param name="SvCbIndex">���ƿ���</param>
		/// <param name="SvCbNode">���ƿ��е�ƫ��</param>
		void SetNodeLinkFlag(bool8 Flag, uint16 SvCbIndex, uint16 SvCbNode);
	};
	/// <summary>
	/// ģ�����������忨
	/// </summary>
	class ApiBoardAngFrameOut :protected SptAngVirOutputBoard
	{
	public:
		//ElementNum Ԫ����Ŀ
		void PowerUpIni(const char* Name, const char* DesName, uint16 FrameNo, uint16 ElementNum);
	};
	/// <summary>
	/// SV�����Ϣ
	/// </summary>
	class ApiSvOut : protected SptSampAng_9_2SampCell
	{
	public:
		//Name�ź�����
		//DesName�����
		void PowerUpIni(class ApiBoardAngFrameOut& Board, const char* Name, const char* DesName, const VarUnits& Units);
		//����������Ƿ�����
		bool8 IsNodeLinkOk();
		//�������������ݼ��е�λ��
		uint16 Node();
	};
	/// <summary>
	/// SV�������ݼ�
	/// </summary>
	class ApiSvOutVirDataSet : protected SptSvOutDataSet
	{
	public:
		//ElementNum����忨Ԫ�ظ���
		//Delay���ʱ
		void PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiBoardAngFrameOut& Frame, uint32 Delay, uint16 FrameIndex, uint16 ElementNum);
		//DataSet���ݼ��ĸ���
		uint32 DataSetCellNum();
		//���÷�������������
		void SetOutSelIndex(uint32 Index, uint32 SelIndex);
		//��ȡ��������������
		uint32 GetOutSelIndex(uint32 Index);
		// �����쳣
		bool8 CfgErr();
		// �����쳣
		bool8 ParseErr();
		/// <summary>
		/// CCD������Ϣ
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct SVcbInfo* SvCbInfo();
		/// <summary>
		/// ���ö��ʱ
		/// </summary>
		/// <param name="DealyUs"></param>
		void SetDealy(uint16 DealyUs);
	};
	/// <summary>
	/// ��䴫��SV�����Ϣ
	/// </summary>
	class ApiBoardCmmSv : protected SptSampAng_9_2SampCell
	{
	public:
		//Name�ź�����
		//DesName�����
		//Node������ţ��ڵ��忨���нڵ����ֵ����0��ʼ
		//FrameIndex���ڿ���֡�����˳���
		void PowerUpIni(class ApiBoardCmmSvOutVirDataSet& Board, const char* Name, const char* DesName, const VarUnits& Units);
	};
	/// <summary>
	/// ���SV�������ݼ�
	/// </summary>
	class ApiBoardCmmSvOutVirDataSet : protected SptSvOutDataSet
	{
	public:
		//ElementNum����忨Ԫ�ظ���
		//Delay���ʱ
		void PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiBoardAngFrameOut& Frame, uint16 FrameIndex, uint16 ElementNum);
		uint32 DataSetCellNum();
		/// <summary>
		/// ���÷�������������
		/// </summary>
		/// <param name="Index"></param>
		/// <param name="SelIndex"></param>
		void SetOutSelIndex(uint32 Index, uint32 SelIndex);
	};
	/// <summary>
	/// ģ������Чֵ��
	/// </summary>
	class ApiAngRmsGroup :protected SalAngRmsGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 EventNum, uint32 BufLen);
		/// <summary>
		///  ����ģ������Чֵ 
		/// </summary>
		/// <param name="AdJustAngle">�Ƿ��Զ�У���Ƕ�</param>
		void Update(bool8 AdJustAngle);
	};
	/// <summary>
	/// ģ������Чֵ
	/// </summary>
	class ApiAngRms :protected SalAngRms
	{
	public:
		//��Ԫ���������
		//IsBase �Ƿ�Ϊ����ĽǶȻ�׼����
		//QLen Ʒ��λ�ֽڿ��,��Ʒ��λ����0
		void PowerUpIni(const char* Name, const char* DesName, ApiAngRmsGroup& Group, bool8 IsBase, uint16 Data1DotNum, const VarUnits& Units1, uint16 Data2DotNum, const VarUnits& Units2, uint8 QLen);
		//һԪ������Ƶ��
		void PowerUpIni(const char* Name, const char* DesName, ApiAngRmsGroup& Group, uint16 Data1DotNum, const VarUnits& Units1, uint8 QLen);
		//����ģ�����任�ĺ�ĵ�λ
		void SetDataUnit(const VarUnits& Units1, const VarUnits& Units2);
		//�Ƿ���ʾ
		void SetDisp(bool8 Disp);
		// ����ģ�����任��ϵ��
		void SetDataCoe(float32 Data1Coe1, float32 Data2Coe);
		//��������
		bool8 PushData(int32 Data1, int32 Data2, uint32 Q);
		//�����������ݣ�ƽ̨תΪ����ֵ�洢,���нǶ���Data2��С��λ���洢
		bool8 PushVectData(int32 Real, int32 Img, uint32 Q);
		//��������
		bool8 PushData(int32 Data1, int32 Data2);
		//�����������ݣ�ƽ̨תΪ����ֵ�洢,���нǶ���Data2��С��λ���洢
		bool8 PushVectData(int32 Real, int32 Img);
	};
	/// <summary>
	/// ȫ��Io������־
	/// </summary>
	class ApiIoGlobalFlag
	{
	public:
		/// <summary>
		/// ���÷ְ忨״̬
		/// ���ڲ�ִװ�ã������·��忨����֡
		/// </summary>
		void ResetSubBoardState();
		/// <summary>
		/// ״̬�ź�
		/// </summary>
		/// <returns></returns>
		const tsAppFlags& AppFlags() { return *appFlags; }
		/// <summary>
		/// ʹ��SV����
		/// </summary>
		/// <param name="Enable"></param>
		void EnableSVSend(bool8 Enable);
		/// <summary>
		/// �ɵ㴦��
		/// </summary>
		/// <param name="Enable"></param>
		void EnableAngErrPointDeal(bool8 Enable);
		/// <summary>
		/// ʹ��GO����
		/// </summary>
		/// <param name="Enable"></param>
		void EnableGoSend(bool8 Enable);
		/// <summary>
		/// ���Զ��״̬
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetCkRemoteState(bool8 Flag);
		/// <summary>
		/// ����Զ��״̬
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetProtRemoteState(bool8 Flag);
		/// <summary>
		/// ����״̬
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetUnitTestState(bool8 Flag);
		/// <summary>
		/// ����״̬
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetUnitDebugState(bool8 Flag);
		/// <summary>
		/// Ӧ��������ɱ�־
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetAppPowerUpIniOver(bool8 Flag);
		/// <summary>
		/// ����װ�ø����־��ƽ̨�Զ�չ��200ms��
		/// </summary>
		/// <param name="Flag"></param>
		/// <returns></returns>
		bool8 SetUnitRevert(bool8 Flag);
		/// <summary>
		/// ��ȡFPGA����������״̬
		/// </summary>
		/// <param name="Index">
		/// AEUװ��:0 �忨��ַ 1 �԰忨�ж�ͨѶ�жϵ�״̬
		/// </param>
		/// <returns></returns>
		uint8 GetFpagSlowFlags(uint16 Index);
		/// <summary>
		/// �忨����״̬
		/// </summary>
		/// <returns></returns>
		uint32 BoardOnLineState();
		/// <summary>
		/// ƽ̨���е�ʵʱ״̬��־
		/// </summary>
		/// <returns></returns>
		const SptFlags& SptFlag();
	public:
		static ApiIoGlobalFlag& Instance();
	protected:
		ApiIoGlobalFlag();
	private:
		SptIoProcess& sptIoProcess;
		SptCcdFile::OutStatus ccdstatus;
		tsAppFlags* appFlags;
	};
	/** @} */ // end of ApiIOAnalogIO
}


#endif // ! APIAIO_H

