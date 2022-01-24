/**@mainpage  继电保护软件平台库
* <table>
* <tr><th>Project  <td>Relay Protection Software Platform
* <tr><th>Author   <td>fengzhanhua
* <tr><th>Source   <td>http://172.18.52.171/svn/Platform
* </table>
* @section   项目详细描述
* 继电保护自动化装置保护测控功能开发基础平台库
* @section   功能描述
* -# 本版基于国产化硬件平台开发
* -# 基于采集执行单元、测控装置、35kV保护装置使用场景开发
* -# 本程序提供通用的开发框架，供应用进行二次开发
* @section   用法描述
* -# 本程序提供静态链与头文件
* @section   更新历史
* <table>
* <tr><th>Date        <th>H_Version  <th>S_Version  <th>Author    <th>Description  </tr>
* <tr><td>2016/08/16  <td>0.1    <td>0.1   <td>冯占华  <td>创建初始版本 </tr>
* <tr><td>2018/08/16  <td>0.1    <td>0.2   <td>冯占华  <td>加入液晶模块 </tr>
* <tr><td>2019/08/16  <td>1.0    <td>0.9   <td>冯占华  <td>基于国产化35kV装置进行功能接口开发 </tr>
* <tr><td>2020/01/16  <td>1.0    <td>0.91  <td>冯占华  <td>
* -# 基于新一代采集执行单元装置进行功能接口开发
* -# 仿真环境使用vs2019 默认开放宏WIN32_SIM；\n
*	 国产化装置默认开放宏SYLIX_GZK；
* </tr>
* <tr><td>2021/10/10  <td>1.0    <td>0.92   <td>冯占华  <td>
* 增加平台运行模式设置,在AppStartUp.cfg中:
* -# AppCmd=AppRun为正常运行模式
* -# AppCmd=FactoryMode为工厂模式，该模式用于进行CPU板卡BSP、文件系统等的初始化，该模式下，平台不进行文件的写操作\n
* </tr>
* <tr><td>2021/11/15  <td>1.0    <td>0.93   <td>冯占华  <td>修改采集装置集成测试问题 </tr>
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

