#ifndef SPTCHECKTASK_H
#define SPTCHECKTASK_H

namespace spt
{
	/// <summary>
	/// �Լ���
	/// </summary>
	class SptCheckTask :public Task
	{
	public:

	public:
		M_Singleton(SptCheckTask);
		struct CheckAppInst;
		typedef int (*CheckFunction)(struct CheckAppInst* Inst);
		/// <summary>
		/// Ӧ���Լ�ص��ӿ�
		/// </summary>
		struct CheckAppInst
		{
			/// <summary>
			/// ʹ��
			/// </summary>
			bool8 enable;
			/// <summary>
			/// ����
			/// </summary>
			uint32 period;
			/// <summary>
			/// Ӧ�����ò���
			/// </summary>
			void* para;
			/// <summary>
			/// �ص�����
			/// </summary>
			CheckFunction func;
			uint32 lastRunTime;
		};
		/// <summary>
		/// ���Ӧ���Լ�����
		/// </summary>
		/// <param name="Inst"></param>
		/// <returns>-1 is fail </returns>
		int32 AddAppCheckInst(struct CheckAppInst* Inst);
		/// <summary>
		/// �Լ������ʼ��
		/// </summary>
		/// <param name="Para"></param>
		/// <returns></returns>
		virtual int32 PowerUpIni(int32 Para);
	protected:
		virtual int32 OneLoop();
		SptCheckTask();
	private:
		uint32 checkInstNum;
		CheckAppInst* checkInst[40];
	};

}

#endif // !SPTCHECKTASK_H

