#ifndef SPTPLATFORM_H
#define SPTPLATFORM_H

#ifdef _MSC_VER
#define WIN32_SIM
#pragma warning (disable: 4996)
#endif // _MSC_VER
#ifdef SYLIXOS
#define SYLIX_GZK
#define SYMBOL_EXPORT __attribute__((section(LW_SYMBOL_KERNEL_SECTION)))
#endif //SYLIXOS

//#define GZK_APP
#define GZK_LCD

#if defined(WIN32_SIM)&&defined(GZK_LCD)
#define WIN32_LCD_SIM
#endif

namespace spt
{
	//Ӳ��ƽ̨
	enum E_HARDWARE
	{
		EH_GZKLCD = 1,//������LCD�忨
		EH_GZKSAULCD = 2,//��������ִLCD�忨
		EH_GZK35KVP = 10000,//������35kV���汣��Ӳ��ƽ̨
		EH_GZK35KVSMART,//������35kV����װ��
		EH_GZKCK = 20000,//���������Ӳ��ƽ̨
		EH_GZKSAU = 30000,//��������ִӲ��ƽ̨
	};
	//���ƽ̨
	enum E_SOFTWARE
	{
		ES_GZKLCD = 1,//LCD���
		ES_GCNPROT,//������װ��
		ES_GZKPROT,//��һ��װ��
		ES_GCNCK,//���������װ��
		ES_GZKCK,//��һ�����װ��
		ES_GZKSAU,//��һ����ִװ��
	};
	//Ӧ�����
	enum E_DEVTYPE
	{
		ED_LCD = 1,//LCD���
		ED_SAULCD = 2,//��ִLCD���
		ED_35KVP = 10000,//35kv���汣�����
		ED_35KVSSAB,//35kV���ܱ���Ͷ
		ED_TOOLS,//װ�ù��߼�
		ED_CK = 20000,//������
		ED_SAU31 = 30000,//��ִ���
		ED_SAU31_Sub,//��ִװ�ô԰忨
	};

}


#endif // !SPTPLATFORM_H

