//========================================================
// 文件模块说明:
// 数据类型定义
// 文件版本: v1.00
// 创建时间: 2011.06.01
// Copyright(c) 2011-2011
//========================================================
// 程序修改记录(最新的放在最前面):
//  <版本号> <修改日期>, <修改人员>: <修改功能概述>
//========================================================

#ifndef __IES_IMTYPES_H__
#define __IES_IMTYPES_H__

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

//========================================================
//========================================================

	typedef unsigned					BITS;
	typedef unsigned  char      		BOOL8;
	typedef unsigned  short     		BOOL16;
	typedef unsigned  int               BOOL32;
	typedef unsigned  long long 		DDWORD;
	typedef unsigned  short     		*PBOOL16;
	
	typedef signed  char       			 INT8;
	typedef short	int          		 INT16;
	typedef int                			 INT32;
	typedef signed   long long			 INT64;

	typedef unsigned char			BYTE;
	typedef unsigned short			WORD;
	typedef unsigned int			DWORD;
	typedef unsigned char			BOOLEAN;
	typedef unsigned				BITS;

	typedef unsigned char			INT8U;
	typedef 		 char			INT8S;
	typedef unsigned short			INT16U;
	typedef 		 short			INT16S;
	typedef unsigned int			INT32U;
	typedef 		 int			INT32S;
	typedef long	 long			INT64;

	typedef unsigned  char     	 	UINT8;
	typedef unsigned  short     	UINT16;
	typedef unsigned  int       	UINT32;
	typedef unsigned  long long	    UINT64;


	typedef signed    long long 	SINT64;
	typedef float               	FLOAT32;
	typedef int                		 SINT32;

     #ifndef BOOL
        #define BOOL        BYTE
	 #endif

	#ifndef FALSE
	    #define FALSE               0
	#endif
	
	#ifndef TRUE
	    #define TRUE                1
	#endif

	#ifndef NULL
	    #define NULL	            0
	#endif

	#ifndef NULLPTR
	    #define NULLPTR 	 ((void*)0) 		//空指针
	#endif
	
	#ifndef ERROR
	    #define ERROR				(-1)
	#endif


	typedef void	 *PVOID;				//无类型指针
	typedef BYTE(*byFunction)(void);		//返回值为BYTE的函数指针
	typedef void (*vFunction)(void);		//无返回值的函数指针
	typedef unsigned short int VarCheck;	//自检标志
	
#ifdef __cplusplus
		typedef int (*PFUNC)(...);
#else
		typedef int (*PFUNC)();
#endif

#ifdef  __cplusplus
	typedef int (*FUNCPTR)(...);                            /* ptr to function returning int */
#else
	typedef int (*FUNCPTR)();                               /* ptr to function returning int */
#endif


#ifdef  __cplusplus
	typedef void (*VOIDFUNCPTR)(...);                       /* ptr to function returning void */
#else
	typedef void (*VOIDFUNCPTR)();                          /* ptr to function returning void */
#endif


#ifdef  __cplusplus
	typedef double(*DBLFUNCPTR)(...);                       /* ptr to function returning double */
#else
	typedef double(*DBLFUNCPTR)();                          /* ptr to function returning double */
#endif


#ifdef  __cplusplus
	typedef float(*FLTFUNCPTR)(...);                        /* ptr to function returning float */
#else
	typedef float(*FLTFUNCPTR)();                           /* ptr to function returning float */
#endif


#endif //__IES_IMTYPES_H__

