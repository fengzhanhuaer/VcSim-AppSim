#ifndef APIAPPCFG_H
#define APIAPPCFG_H

namespace spt
{
	struct ApiAppCfg
	{
		//ƽ̨��������
		struct Platform
		{
			enum E_HARDWARE hardware;
			enum E_SOFTWARE software;
			enum E_DEVTYPE devtype;
		}platform;
		//�˻��ӿ�����
		struct HmiCfg
		{
			ApiMenu* AppRootMenu;//���˵�
			/// <summary>
			/// ��������
			/// </summary>
			char DispName[40];//��ʾ����
			/// <summary>
			/// ����汾
			/// </summary>
			char FullTypeName[40];//�ͺ�����
			uint32 NetPortNum;//������Ŀ����ǰ���ڣ�
			/// <summary>
			/// GZK-35kV-T3-L-31-S-1-SD-INFO
			/// GZK��Ʒϵ�У�SPD/GCN/GZK
			/// 35kV��ѹ�ȼ�
			/// T3Ӳ��ƽ̨
			/// L��·��T��ѹ����Bĸ�߲�Ʒ���
			/// 31��Ʒ�ͺ�,��ͬƽ̨�ڿذ汾Ӧ�ò�ͬ,��ͬ�ͺţ����ܲ�Ʒ�汾Ӧ�ò�ͬ
			/// S����N����
			/// 1 �����֧������1A��5A������汾�����԰汾
			/// SD�����ǣ�SDɽ����NORͨ�ó��淢���汾��TEST���԰汾
			/// INFO����˵����Ϣ
			/// </summary>
			char FatcoryTypeName[100];//�����ڿ��ͺ�
			char DeviceSampleName[40];//�ͺż�д,����¼�����Ƶ�
		}hmicfg;
		//Ӧ����������
		struct SampAppCfg
		{
			ApiSampAppTask* AppArrBase;//Ӧ������
			uint32 AppArrLen;//Ӧ���������
			uint32 SysHz;//����ϵͳƵ��,3λС��
			uint32 CycleSamp;//ÿ�ܲ���������
		}sampAppCfg;
		bool8 IsHardWare(E_HARDWARE hd)const;
		bool8 IsSoftWare(E_SOFTWARE st)const;
		bool8 IsDevice(E_DEVTYPE dev)const;
	};
}
#endif // !APIAPPCFG_H
