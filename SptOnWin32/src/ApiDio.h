#ifndef APIDIO_H
#define APIDIO_H
namespace spt
{
	/** @defgroup ApiIOStateIO
	* ״̬���������ģ��
	* @{
	*/

	//���濪��忨
	class ApiBoardNormalStateIn :protected SptNormalStateInBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex);
		//��λ��ţ�ÿ�α�λ+1(δȥ��)
		uint32 StateNum();
		//��λʱ��,δȥ��
		const SalDateStamp& Stamp();
		//����λ��ֵ,δȥ����ʵʱ״ֵ̬
		//InNo,�忨�����32λλ����
		uint32 Bit32(uint32 InNo);
		//����λ��ֵ,δȥ����ʵʱ״ֵ̬
		//Index ����ֵ��ţ�0����ǰ�㣬1������һ�㣬��������
		//InNo,�忨�����32λλ����
		uint32 Bit32(uint32 Index, uint32 InNo);
		//��λʱ��
		// Index ����ֵ��ţ�0����ǰ�㣬1������һ�㣬��������
		const SalDateStamp& Stamp(uint32 Index);
		//�Լ�״̬
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	protected:

	};
	//���濪��
	class ApiNormalBoolIn :protected SptNormalStateInCell
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(class ApiBoardNormalStateIn& Board, const char* Name, const char* DesName, uint16 InNo);
		//��λ��ţ�ÿ�α�λ+1(δȥ��)
		uint32 StateNum();
		bool8 Value();
		// Index ����ֵ��ţ�0����ǰ�㣬1������һ�㣬��������
		bool8 Value(uint32 Index);
		//��λʱ��,δȥ��
		const SalDateStamp& Stamp();
		// Index ����ֵ��ţ�0����ǰ�㣬1������һ�㣬��������
		const SalDateStamp& Stamp(uint32 Index);
		//�ź�ǿ��״̬����ʱ������������Ӳ��Ϊ׼�������������Ӧ��Ϊ׼�����ǵ������ǿ�á�HMI����ǿ��
		bool8 SignalForce() { return blsignalForce; };
	};
	//���濪���忨
	class ApiBoardNormalStateOut :protected SptNormalStateOutBoard
	{
	public:
		//CardAddr �忨��ַ
		//FrameNo ��DO֡�����λ�ƣ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex);
		/// <summary>
		/// ������λʱ��
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& Stamp();
		/// <summary>
		/// ��У״̬�Ľ���ʱ��
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& StateStamp();
		//����λ��ֵ
		//InNo,�忨������32λλ����,��У��Ϣ
		uint32 VerfyCode(uint32 InNo);
		//VerfyCode ��λʱ��һ
		uint32 VerfyCodeNum();
		//�Լ�״̬
		const struct stOutStatus* CheckStatus() { return &ostatus; };
	};
	//���濪��
	class ApiNormalBoolOut :protected SptNormalStateOutCell
	{
	public:
		//��������
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void ProtOutPowerUpIni(class ApiBoardNormalStateOut& Board, const char* Name, const char* DesName, uint16 InNo);
		//��������
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void ProtStartPowerUpIni(class ApiBoardNormalStateOut& Board, const char* Name, const char* DesName);
		//�źų���
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void SignalPowerUpIni(class ApiBoardNormalStateOut& Board, const char* Name, const char* DesName, uint16 InNo);
		void SetValue(bool8 Val);
		bool8 Value();
		uint32 VerfyCode();//��У��Ϣ
		//��λʱ��
		const SalDateStamp& Stamp();
		//�ź�ǿ��״̬����ʱ������������Ӳ��Ϊ׼�������������Ӧ��Ϊ׼�����ǵ������ǿ�á�HMI����ǿ��
		bool8 SignalForce() { return blsignalForce; };
	};

	/// <summary>
	/// ����ֱ��������
	/// </summary>
	class ApiBoardNormalDcIn :protected SptNormalDcInBoard
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 CardType, uint16 CardAddr, uint16 FrameIndex, uint32 ElementNum);
		/// <summary>
		/// ����ʱ��
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& Stamp();
		uint32 StateNum();
		/// <summary>
		/// �Լ�״̬
		/// </summary>
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// �忨�¶�
		/// </summary>
		/// <returns></returns>
		uint16 Temperature();
	};
	//����ֱ��������
	class ApiNormalDcIn :protected SptNormalDcIn
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(class ApiBoardNormalDcIn& Board, const char* Name, const char* DesName, uint16 InNo, const VarUnits& Units);
		int32 Value();
		//�ź�ǿ��״̬����ʱ������������Ӳ��Ϊ׼�������������Ӧ��Ϊ׼�����ǵ������ǿ�á�HMIǿ��
		bool8 SignalForce() { return blsignalForce; };
	protected:

	};
	//Goose����֡
	class ApiGoInFrame :protected SptGooseFrameIn
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 InNo, uint16 ElementNum);
		/// <summary>
		/// FPGA���͵�GOOSE��������֡����
		/// </summary>
		/// <returns></returns>
		uint32 PosFrameNum();
		/// <summary>
		/// FPGA���͵�GOOSEģ��������֡����
		/// </summary>
		/// <returns></returns>
		uint32 AngFrameNum();
		/// <summary>
		/// GOOSE֡��λʱ��
		/// </summary>
		/// <returns></returns>
		const SalDateStamp& FrameStamp();

	};
	//Goose������ƿ�
	class ApiGoInCb :protected SptGooseDataSetIn
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 ElementNum);
		//�Լ�״̬
		const struct stOutStatus* CheckStatus() { return &ostatus; };
		/// <summary>
		/// A��״̬
		/// </summary>
		/// <returns></returns>
		uint32 StateA();
		/// <summary>
		/// B��״̬
		/// </summary>
		/// <returns></returns>
		uint32 StateB();
		// �����쳣
		bool8 CfgErr();
		// �����쳣
		bool8 ParseErr();
		/// <summary>
		/// CCD������Ϣ
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct GooseGocbInfo* GoCbInfo();
	};
	//Goose����
	class ApiGoIn :protected SptGooseDataIn
	{
	public:
		//�Ƿ����Q
		bool8 IsQLinked();
		//�Ƿ����T
		bool8 IsTLinked();
		//�Ƿ����V
		bool8 IsVLinked();
		//��λʱ��
		const SalDateStamp& Stamp();
		uint32 Q();
		//��λ��ţ�ÿ�α�λ+1(δȥ��)
		uint32 StateNum();
		//��Goose�����Ŀ��ƿ飬δ������Ϊ��
		const ApiGoInCb* GoCb();
		//�ź�ǿ��״̬����ʱ������������Ӳ��Ϊ׼�������������Ӧ��Ϊ׼�����ǵ������ǿ�á�HMIǿ��
		bool8 SignalForce() { return blsignalForce; };
	protected:
		void PowerUpIni(const char* Name, const char* DesName, SptGooseFrameIn* Board, uint32 Type, uint16 InNo);
	};
	//Goose����λ����Ϣ
	class ApiGoPosIn :public ApiGoIn
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		bool8 Value();
	};
	//Goose˫��λ����Ϣ
	class ApiGoDpPosIn :public ApiGoIn
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		uint32 Value();

	};
	//Goose���㿪��
	class ApiDigFloatIn :public ApiGoIn
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		float32 Value();
	};
	//Goose32λInt����
	class ApiDigInt32In :public ApiGoIn
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		int32 Value();
	};
	//Goose32λUint����
	class ApiDigUInt32In :public ApiGoIn
	{
	public:
		//Name�ź�����
		//DesName�����
		//InNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoInFrame& Frame, uint16 InNo);
		uint32 Value();
	};
	//Goose����֡
	class ApiGoOutFrame :protected SptGooseFrameOut
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint16 InNo, uint16 ElementNum);
	};
	//Goose���ݼ�
	class ApiGoOutDataSet :protected SptGooseDataSetOut
	{
	public:
		//CardAddr ������յĵ�һ��忨��ţ�AΪ0��BΪ1���������ơ������Ҫ�ڶ��忨�Ͻ���������EnableCardAddr
		void PowerUpIni(const char* Name, const char* OutName, const char* DesName, ApiGoOutFrame& Frame, uint16 ElementNum);
		// �����쳣
		bool8 CfgErr();
		// �����쳣
		bool8 ParseErr();
		/// <summary>
		/// CCD������Ϣ
		/// </summary>
		/// <returns>0,if parse err.</returns>
		struct GooseGocbInfo* GoCbInfo();
	};
	//Goose����
	class ApiGoOut :protected SptGooseDataOut
	{
	public:
		//GOOSE����������������ͣ�ֻ��IsVLinkedΪ1ʱ��������
		//�������Ͳμ�ö��GoSvDataType
		GoSvDataType GoValueType();
		//�Ƿ����Q
		bool8 IsQLinked();
		//�Ƿ����T
		bool8 IsTLinked();
		//�Ƿ����V
		bool8 IsVLinked();
		//��Goose�����Ŀ��ƿ飬δ������Ϊ��
		const ApiGoOutDataSet* GoCb();
		//Ʒ��
		void SetQ(uint32 Q);
		//��λʱ��,����GOOOSE���������t��ʹ��Ӧ�����õ�t,���Ӧ��δ������ʹ��ϵͳʱ��
		void SetStamp(SalDateStamp& stamp);
		void SetValue(u32value Val);
		const SalDateStamp& Stamp();
		uint32 Q();
		//�ź�ǿ��״̬����ʱ������������Ӳ��Ϊ׼�������������Ӧ��Ϊ׼�����ǵ������ǿ�á�HMIǿ��
		bool8 SignalForce() { return blsignalForce; };
	protected:
		void PowerUpIni(const char* Name, const char* DesName, SptGooseFrameOut* Board, uint32 Type, uint16 OutNo);
	};
	//Goose����λ����Ϣ
	class ApiGoPosOut :public ApiGoOut
	{
	public:
		//Name�ź�����
		//DesName�����
		//OutNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		void SetValue(uint32 Val);
		uint32 Value();
		//���º����̳��Ը��࣬Ӧ�ò����ֱ�ӵ���
		//Ʒ��
		//void SetQ(uint32 Q);
		//��λʱ��
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	//Goose˫��λ����Ϣ
	class ApiGoDpPosOut :public ApiGoOut
	{
	public:
		//Name�ź�����
		//DesName�����
		//OutNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		void SetValue(uint32 Val);
		uint32 Value();
		//���º����̳��Ը��࣬Ӧ�ò����ֱ�ӵ���
		//Ʒ��
		//void SetQ(uint32 Q);
		//��λʱ��
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	//Goose���㿪��
	class ApiGoFloatOut :public ApiGoOut
	{
	public:
		//Name�ź�����
		//DesName�����
		//OutNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		//��λʱ��
		void SetValue(float32 Val);
		float32 Value();
		//���º����̳��Ը��࣬Ӧ�ò����ֱ�ӵ���
		//Ʒ��
		//void SetQ(uint32 Q);
		//��λʱ��
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	//Goose32λ����
	class ApiGoInt32Out :public ApiGoOut
	{
	public:
		//Name�ź�����
		//DesName�����
		//OutNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		/// <summary>
		/// ����GOOSEֵ
		/// </summary>
		/// <param name="Val"></param>
		void SetValue(int32 Val);
		int32 Value();
		//���º����̳��Ը��࣬Ӧ�ò����ֱ�ӵ���
		//Ʒ��
		//void SetQ(uint32 Q);
		//��λʱ��
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	class ApiGoUInt32Out :public ApiGoOut
	{
	public:
		//Name�ź�����
		//DesName�����
		//OutNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		//��λʱ��
		void SetValue(uint32 Val);
		uint32 Value();
		//���º����̳��Ը��࣬Ӧ�ò����ֱ�ӵ���
		//Ʒ��
		//void SetQ(uint32 Q);
		//��λʱ��
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	class ApiGoUnion32Out :public ApiGoOut
	{
	public:
		//Name�ź�����
		//DesName�����
		//OutNo������ţ���0��ʼ
		void PowerUpIni(const char* Name, const char* DesName, ApiGoOutFrame& Board, uint16 OutNo);
		//��λʱ��
		void SetValue(u32value Val);
		u32value Value();
		//���º����̳��Ը��࣬Ӧ�ò����ֱ�ӵ���
		//Ʒ��
		//void SetQ(uint32 Q);
		//��λʱ��
		//void SetStamp(SalDateStamp& stamp);
		//const SalDateStamp& Stamp();
		//uint32 Q();
	};
	/** @} */ // end of ApiIOStateIO
}

#endif // !APIDIO_H

