#ifndef ApiAppTask_H
#define ApiAppTask_H


namespace spt
{
	class ApiSampAppTask :protected SampAppTask
	{
	public:
		/*
		*TaskNameӦ�ó�������
		*CallBack�ص�����
		*Period��������,��λΪ��������
		*/
		ApiSampAppTask(const char* TaskName, AppTaskCallBack CallBack, bool8 Enable, uint32 Period);
		/// <summary>
		/// ���д���,ÿ�ε����жϼ�һ
		/// </summary>
		/// <returns></returns>
		uint64 RunCnt();
		/// <summary>
		/// �ж��Ƿ�ʹ��
		/// </summary>
		/// <returns></returns>
		bool8 IsEnable();
		/// <summary>
		/// ʹ���ж�
		/// </summary>
		/// <param name="En"></param>
		/// <returns></returns>
		bool8 Enable(bool8 En);
		/// <summary>
		/// ���ͳ����Ϣ
		/// </summary>
		void ClearLoadInfo();
		/// <summary>
		/// ����
		/// </summary>
		/// <returns></returns>
		const char* Name() { return name; };
		/// <summary>
		/// ������Ϣ
		/// </summary>
		const struct TaskRunInfo& RunInfo() { return runInfo; }
	};
}




#endif // !ApiAppTask_H

