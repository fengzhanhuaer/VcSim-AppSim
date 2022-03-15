/*================================================================================
 * 文件描述：版本配置配置
 * 文件版本: V1.00
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/
#ifndef _CONST_VERSION_H_
#define _CONST_VERSION_H_

/******************************************************/
// 软硬件版本划分
/******************************************************/
// 软件版本-CPU
#define CN_SOFT_CPU_STD       (0)  // 标准版本
#define CN_SOFT_CPU_TEST      (1)  // 调试版本
#define CN_SOFT_CPU_NANJING   (2)  // 南京版本
// 软件版本-BOOT0
#define CN_SOFT_CPU_BOOT0_V1  (0)  // 初始版本
// 软件版本-UBOOT
#define CN_SOFT_CPU_UBOOT_V1  (0)  // 初始版本
// 软件版本-BSP
#define CN_SOFT_CPU_BSP_V1    (0)  // 初始版本
#define CN_SOFT_CPU_BSP_V2    (1)  // 初始版本
// 软件版本-FPGA1
#define CN_SOFT_FPGA1_V1      (0)  // 初始版本
#define CN_SOFT_FPGA1_V2      (1)  // V1.17增加双AD可控功能,采用模拟量大表挑数Bit8(0x0080)
#define CN_SOFT_FPGA1_V3      (2)  // V1.22新CPU板程序,增加直流补偿,GOOSE优化,主频监视等
// 软件版本-FPGA2
#define CN_SOFT_FPGA2_V1      (0)  // 初始版本
#define CN_SOFT_FPGA2_V2      (1)  // 
// 软件版本-MCU
#define CN_SOFT_MCU_V1        (0)  // V1.00 初始版本
#define CN_SOFT_MCU_V2        (1)  // V1.01 DO增加24V、30V电源监视
// 软件版本-LED
#define CN_SOFT_LED_V1        (0)  // 初始版本

// 硬件版本-CPU
#define CN_HARDWARE_MCPU_V1   (0)  // 初始版本
#define CN_HARDWARE_MCPU_V2   (1)  // 修正AD基准全部为5V,串口默认发送使能,20211227
// 硬件版本-CPU_AUX
#define CN_HARDWARE_MCPU_AUX_V1 (0) // 初始版本
#define CN_HARDWARE_MCPU_AUX_V2 (1) // 去掉指示灯 20220110
// 硬件版本-PTCT1
#define CN_HARDWARE_PTCT1_V1  (0)  // 初始版本
#define CN_HARDWARE_PTCT1_V2  (1)  // 与CPU接线优化 20211107
// 硬件版本-PTCT2
#define CN_HARDWARE_PTCT2_V1  (0)  // 初始版本
#define CN_HARDWARE_PTCT2_V2  (1)  // 测量电流为2A 20211107
// 硬件版本-DC
#define CN_HARDWARE_DC_V1     (0)  // 初始版本20210825
// 硬件版本-DO
#define CN_HARDWARE_DO_V1     (0)  // 初始版本20210803
#define CN_HARDWARE_DO_V2     (1)  // 增加24V、30V电源监视 20211221
// 硬件版本-DIO
#define CN_HARDWARE_DIO_V1    (0)  // 初始版本
#define CN_HARDWARE_DIO_V2    (1)  // 增加24V、30V电源监视20220106
// 硬件版本-OPB
#define CN_HARDWARE_OPB_V1    (0)  // 初始版本20210917
// 硬件版本-DI
#define CN_HARDWARE_DI_V1     (0)  // 初始版本
#define CN_HARDWARE_DI_V2     (1)  // 20220106
// 硬件版本-POW
#define CN_HARDWARE_POW_V1    (0)  // 初始版本
// 硬件版本-母板
#define CN_HARDWARE_MB_V1     (0)  // 初始版本
#define CN_HARDWARE_MB_V2     (1)  // 系统测试版本,调整AD通道映射
#define CN_HARDWARE_MB_V3     (2)  // AD通道映射调整为正常,增加24V、30V电源继电器监视
// 硬件版本-LED
#define CN_HARDWARE_LED_V1    (0)  // 初始版本20210825

/******************************************************/
// 当前使用版本
/******************************************************/
// 软件CPU版本类型
#define CN_SOFT_VER_CPU          (CN_SOFT_CPU_STD)
#define CN_SOFT_VER_CPU_BOOT0    (CN_SOFT_CPU_BOOT0_V1)
#define CN_SOFT_VER_CPU_UBOOT    (CN_SOFT_CPU_UBOOT_V1)
#define CN_SOFT_VER_CPU_BSP      (CN_SOFT_CPU_BSP_V2)
// 软件FPGA1版本类型
#define CN_SOFT_VER_FPGA1        (CN_SOFT_FPGA1_V3)
// 软件FPGA2版本类型
#define CN_SOFT_VER_FPGA2        (CN_SOFT_FPGA2_V2)
// 软件MCU版本类型
#define CN_SOFT_VER_MCU          (CN_SOFT_MCU_V2)
// 软件LED版本类型
#define CN_SOFT_VER_LED          (CN_SOFT_LED_V1)
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
// 硬件CPU板版本
#define CN_HARDWARE_MCPU         (CN_HARDWARE_MCPU_V1)
#define CN_HARDWARE_MCPU_AUX     (CN_HARDWARE_MCPU_AUX_V1)
// 硬件PTCT1板版本
#define CN_HARDWARE_PTCT1        (CN_HARDWARE_PTCT1_V1)
// 硬件PTCT2板版本
#define CN_HARDWARE_PTCT2        (CN_HARDWARE_PTCT2_V1)
// 硬件DC板版本
#define CN_HARDWARE_DC           (CN_HARDWARE_DC_V1)
// 硬件DO板版本
#define CN_HARDWARE_DO           (CN_HARDWARE_DO_V1)
// 硬件DIO板版本
#define CN_HARDWARE_DIO          (CN_HARDWARE_DIO_V1)
// 硬件OPB板版本
#define CN_HARDWARE_OPB          (CN_HARDWARE_OPB_V1)
// 硬件DI板版本
#define CN_HARDWARE_DI           (CN_HARDWARE_DI_V1)
// 硬件POW板版本
#define CN_HARDWARE_POW          (CN_HARDWARE_POW_V1)
// 硬件MB板版本
#define CN_HARDWARE_MB           (CN_HARDWARE_MB_V1)
// 硬件LED板版本
#define CN_HARDWARE_LED          (CN_HARDWARE_LED_V1)
#else
// 硬件CPU板版本
#define CN_HARDWARE_MCPU         (CN_HARDWARE_MCPU_V2)
#define CN_HARDWARE_MCPU_AUX     (CN_HARDWARE_MCPU_AUX_V2)
// 硬件PTCT1板版本
#define CN_HARDWARE_PTCT1        (CN_HARDWARE_PTCT1_V2)
// 硬件PTCT2板版本
#define CN_HARDWARE_PTCT2        (CN_HARDWARE_PTCT2_V2)
// 硬件DC板版本
#define CN_HARDWARE_DC           (CN_HARDWARE_DC_V1)
// 硬件DO板版本
#define CN_HARDWARE_DO           (CN_HARDWARE_DO_V2)
// 硬件DIO板版本
#define CN_HARDWARE_DIO          (CN_HARDWARE_DIO_V2)
// 硬件OPB板版本
#define CN_HARDWARE_OPB          (CN_HARDWARE_OPB_V1)
// 硬件DI板版本
#define CN_HARDWARE_DI           (CN_HARDWARE_DI_V2)
// 硬件POW板版本
#define CN_HARDWARE_POW          (CN_HARDWARE_POW_V1)
// 硬件MB板版本
#define CN_HARDWARE_MB           (CN_HARDWARE_MB_V3)
// 硬件LED板版本
#define CN_HARDWARE_LED          (CN_HARDWARE_LED_V1)
#endif
/******************************************************/
// 软硬件版本描述
/******************************************************/
// 软件版本-CPU APP
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_STD)
#define CN_SOFT_VER_CPU_NAME      "标准版本"
#elif(CN_SOFT_VER_CPU==CN_SOFT_CPU_TEST)
#define CN_SOFT_VER_CPU_NAME      "调试版本"
#elif(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
#define CN_SOFT_VER_CPU_NAME      "南京动模版本"
#endif
// 软件版本-CPU BOOT0
#if(CN_SOFT_VER_CPU_BOOT0==CN_SOFT_CPU_BOOT0_V1)
#define CN_SOFT_VER_CPU_BOOT0_NAME "V2.02"
#endif
// 软件版本-CPU UBOOT
#if(CN_SOFT_VER_CPU_UBOOT==CN_SOFT_CPU_UBOOT_V1)
#define CN_SOFT_VER_CPU_UBOOT_NAME "V2.02"
#endif
// 软件版本-CPU BSP
#if(CN_SOFT_VER_CPU_BSP==CN_SOFT_CPU_BSP_V1)
#define CN_SOFT_VER_CPU_BSP_NAME  "V1.73"
#else
#define CN_SOFT_VER_CPU_BSP_NAME  "V1.75"
#endif
// 软件版本-FPGA1
#if(CN_SOFT_VER_FPGA1==CN_SOFT_FPGA1_V1)
#define CN_SOFT_VER_FPGA1_NAME    "V1.17以前版本"
#elif(CN_SOFT_VER_FPGA1==CN_SOFT_FPGA1_V2)
#define CN_SOFT_VER_FPGA1_NAME    "V1.17-V1.21版本"
#elif(CN_SOFT_VER_FPGA1==CN_SOFT_FPGA1_V3)
#define CN_SOFT_VER_FPGA1_NAME    "V1.30及以上版本"
#endif
// 软件版本-FPGA2
#if(CN_SOFT_VER_FPGA2==CN_SOFT_FPGA2_V1)
#define CN_SOFT_VER_FPGA2_NAME    "V1.10以前版本"
#else
#define CN_SOFT_VER_FPGA2_NAME    "V1.11"
#endif
// CPU硬件版本类型
#if(CN_HARDWARE_MCPU==CN_HARDWARE_MCPU_V1)
#define CN_HARDWARE_MCPU_NAME     "MCPU1-20210803"
#elif(CN_HARDWARE_MCPU==CN_HARDWARE_MCPU_V2)
#define CN_HARDWARE_MCPU_NAME     "MCPU1-20211227"
#endif
// CPU背板硬件版本类型
#if(CN_HARDWARE_MCPU_AUX==CN_HARDWARE_MCPU_AUX_V1)
#define CN_HARDWARE_MCPU_AUX_NAME     "OPT1-20220110以前版本"
#elif(CN_HARDWARE_MCPU_AUX==CN_HARDWARE_MCPU_AUX_V2)
#define CN_HARDWARE_MCPU_AUX_NAME     "OPT1-20220110"
#endif
// PTCT1
#if(CN_HARDWARE_PTCT1==CN_HARDWARE_PTCT1_V1)
#define CN_HARDWARE_PTCT1_NAME     "PTCT1-20211107以前版本"
#elif(CN_HARDWARE_PTCT1==CN_HARDWARE_PTCT1_V2)
#define CN_HARDWARE_PTCT1_NAME     "PTCT1-20211107-"
#endif
// PTCT2
#if(CN_HARDWARE_PTCT2==CN_HARDWARE_PTCT2_V1)
#define CN_HARDWARE_PTCT2_NAME     "PTCT2-20211107以前版本"
#elif(CN_HARDWARE_PTCT2==CN_HARDWARE_PTCT2_V2)
#define CN_HARDWARE_PTCT2_NAME     "PTCT2-20211107-"
#endif
// DC
#if(CN_HARDWARE_DC==CN_HARDWARE_DC_V1)
#define CN_HARDWARE_DC_NAME        "DC1-20210825"
#endif
// DO
#if(CN_HARDWARE_DO==CN_HARDWARE_DO_V1)
#define CN_HARDWARE_DO_NAME        "DO1-20210803"
#elif(CN_HARDWARE_DO==CN_HARDWARE_DO_V2)
#define CN_HARDWARE_DO_NAME        "DO1-20211221-"
#endif
// DIO
#if(CN_HARDWARE_DIO==CN_HARDWARE_DIO_V1)
#define CN_HARDWARE_DIO_NAME       "DIO1-20220106以前版本"
#elif(CN_HARDWARE_DIO==CN_HARDWARE_DIO_V2)
#define CN_HARDWARE_DIO_NAME       "DIO1-20220106-"
#endif
// OPB
#if(CN_HARDWARE_OPB==CN_HARDWARE_OPB_V1)
#define CN_HARDWARE_OPB_NAME       "OPB1-20210917-"
#endif
// DI
#if(CN_HARDWARE_DI==CN_HARDWARE_DI_V1)
#define CN_HARDWARE_DI_NAME        "DI1-20220106以前版本"
#elif(CN_HARDWARE_DI==CN_HARDWARE_DI_V2)
#define CN_HARDWARE_DI_NAME        "DI1-20220106-"
#endif
// MB版本
#if(CN_HARDWARE_MB==CN_HARDWARE_MB_V1)
#define CN_HARDWARE_MB_NAME     "MBL1-20211115以前版本"
#elif(CN_HARDWARE_MB==CN_HARDWARE_MB_V2)
#define CN_HARDWARE_MB_NAME     "MBL1-20211115"
#elif(CN_HARDWARE_MB==CN_HARDWARE_MB_V3)
#define CN_HARDWARE_MB_NAME     "MBL1-20211225"
#endif

/******************************************************/
// 调试功能宏定义
/******************************************************/
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_TEST)
#define CN_TEST_TIME     (0x0001)
#define CN_TEST_2AD      (0x0002)
#define CN_TEST_SAMLOCL  (0x0004)
#define CN_TEST_MENUDBG  (0x0008)
#define CN_TEST_TCOMP    (0x0010)   // 温度补偿可投退
#define CN_TEST_BAK06    (0x0020)   // 备用测试功能06
#define CN_TEST_BAK07    (0x0040)   // 备用测试功能07
#define CN_TEST_BAK08    (0x0080)   // 备用测试功能08
#define CN_TEST_BAK09    (0x0100)   // 备用测试功能09
#define CN_TEST_BAK10    (0x0200)   // 备用测试功能10
#define CN_TEST_BAK11    (0x0400)   // 备用测试功能11
#define CN_TEST_BAK12    (0x0800)   // 备用测试功能12
#define CN_TEST_BAK13    (0x1000)   // 备用测试功能13
#define CN_TEST_BAK14    (0x2000)   // 备用测试功能14
#define CN_TEST_BAK15    (0x4000)   // 备用测试功能15
#define CN_TEST_BAK16    (0x8000)   // 备用测试功能16

#define CN_SOFT_CPU_TEST_CFG           (CN_TEST_SAMLOCL+CN_TEST_TCOMP)//调试功能投退
#define CN_SOFT_CPU_TEST_GET(Index)    ((CN_SOFT_CPU_TEST_CFG&(Index))!=0)
#else
#define CN_SOFT_CPU_TEST_GET(Index)    (0)
#endif

#endif  /* _CONST_EQUIP_H_ */
