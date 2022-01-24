/**@mainpage  �̵籣�����ƽ̨��
* <table>
* <tr><th>Project  <td>Relay Protection Software Platform
* <tr><th>Author   <td>fengzhanhua
* <tr><th>Source   <td>http://172.18.52.171/svn/Platform
* </table>
* @section   ��Ŀ��ϸ����
* �̵籣���Զ���װ�ñ�����ع��ܿ�������ƽ̨��
* @section   ��������
* -# ������ڹ�����Ӳ��ƽ̨����
* -# ���ڲɼ�ִ�е�Ԫ�����װ�á�35kV����װ��ʹ�ó�������
* -# �������ṩͨ�õĿ�����ܣ���Ӧ�ý��ж��ο���
* @section   �÷�����
* -# �������ṩ��̬����ͷ�ļ�
* @section   ������ʷ
* <table>
* <tr><th>Date        <th>H_Version  <th>S_Version  <th>Author    <th>Description  </tr>
* <tr><td>2016/08/16  <td>0.1    <td>0.1   <td>��ռ��  <td>������ʼ�汾 </tr>
* <tr><td>2018/08/16  <td>0.1    <td>0.2   <td>��ռ��  <td>����Һ��ģ�� </tr>
* <tr><td>2019/08/16  <td>1.0    <td>0.9   <td>��ռ��  <td>���ڹ�����35kVװ�ý��й��ܽӿڿ��� </tr>
* <tr><td>2020/01/16  <td>1.0    <td>0.91  <td>��ռ��  <td>
* -# ������һ���ɼ�ִ�е�Ԫװ�ý��й��ܽӿڿ���
* -# ���滷��ʹ��vs2019 Ĭ�Ͽ��ź�WIN32_SIM��\n
*	 ������װ��Ĭ�Ͽ��ź�SYLIX_GZK��
* </tr>
* <tr><td>2021/10/10  <td>1.0    <td>0.92   <td>��ռ��  <td>
* ����ƽ̨����ģʽ����,��AppStartUp.cfg��:
* -# AppCmd=AppRunΪ��������ģʽ
* -# AppCmd=FactoryModeΪ����ģʽ����ģʽ���ڽ���CPU�忨BSP���ļ�ϵͳ�ȵĳ�ʼ������ģʽ�£�ƽ̨�������ļ���д����\n
* </tr>
* <tr><td>2021/11/15  <td>1.0    <td>0.93   <td>��ռ��  <td>�޸Ĳɼ�װ�ü��ɲ������� </tr>
* </table>
**********************************************************************************
*/

#ifndef SPTMAIN_H
#define SPTMAIN_H

#include "SptSampInt.h"
#include "SptMsInt.h"
#include "SptLog.h"
#include "SptAppFlags.h"
#include "SptAppTask.h"
#include "SptTaskMonitor.h"
#include "SptAppIo.h"
#include "SptT860InterFace.h"
#include "SptCmmTask.h"
#include "SptCheckTask.h"

namespace spt
{
	class SptMain
	{
	public:
		enum E_StartMode
		{
			E_Normal,
			E_Factory,
		};
	public:
		const struct ApiAppCfg* AppCfg();
		bool8 IsHardWare(E_HARDWARE hd);
		bool8 IsSoftWare(E_SOFTWARE st);
		bool8 IsDevice(E_DEVTYPE dev);
		void SetAppCfg(struct ApiAppCfg* AppCfg, int argc, char** argv);
		E_StartMode StartMode();
	public:
		const SalString& AppRoot();
		static SptMain& Instance();
		void PowerUpIni(int32 Para);
		void Run();
		bool8 IsStartOver();
	protected:
		void PowerUpDealStartPara(int argc, char** argv);
		void CalcAppCrc(int argc, char** argv);
		SptMain();
		~SptMain();
	private:
		String100B appRoot;
		struct ApiAppCfg* appCfg;
		E_StartMode startmode;
		bool8 isStartOver = 0;
	};
}

extern "C" {
	int SptEntry(int argc, char** argv);
	int SimSysStartUp();
}


#endif // !SPTMAIN_H

