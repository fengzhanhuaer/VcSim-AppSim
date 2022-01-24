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
	//硬件平台
	enum E_HARDWARE
	{
		EH_GZKLCD = 1,//国产化LCD板卡
		EH_GZKSAULCD = 2,//国产化采执LCD板卡
		EH_GZK35KVP = 10000,//国产化35kV常规保护硬件平台
		EH_GZK35KVSMART,//国产化35kV智能装置
		EH_GZKCK = 20000,//国产化测控硬件平台
		EH_GZKSAU = 30000,//国产化采执硬件平台
	};
	//软件平台
	enum E_SOFTWARE
	{
		ES_GZKLCD = 1,//LCD软件
		ES_GCNPROT,//国产化装置
		ES_GZKPROT,//新一代装置
		ES_GCNCK,//国产化测控装置
		ES_GZKCK,//新一代测控装置
		ES_GZKSAU,//新一代采执装置
	};
	//应用软件
	enum E_DEVTYPE
	{
		ED_LCD = 1,//LCD软件
		ED_SAULCD = 2,//采执LCD软件
		ED_35KVP = 10000,//35kv常规保护软件
		ED_35KVSSAB,//35kV智能备自投
		ED_TOOLS,//装置工具集
		ED_CK = 20000,//测控软件
		ED_SAU31 = 30000,//采执软件
		ED_SAU31_Sub,//采执装置丛板卡
	};

}


#endif // !SPTPLATFORM_H

