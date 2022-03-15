/*================================================================================
 * �ļ��������汾��������
 * �ļ��汾: V1.00
 * ����ʱ��:
 * �汾�޶�:
 * �޶���Ա:
 *================================================================================*/
#ifndef _CONST_VERSION_H_
#define _CONST_VERSION_H_

/******************************************************/
// ��Ӳ���汾����
/******************************************************/
// ����汾-CPU
#define CN_SOFT_CPU_STD       (0)  // ��׼�汾
#define CN_SOFT_CPU_TEST      (1)  // ���԰汾
#define CN_SOFT_CPU_NANJING   (2)  // �Ͼ��汾
// ����汾-BOOT0
#define CN_SOFT_CPU_BOOT0_V1  (0)  // ��ʼ�汾
// ����汾-UBOOT
#define CN_SOFT_CPU_UBOOT_V1  (0)  // ��ʼ�汾
// ����汾-BSP
#define CN_SOFT_CPU_BSP_V1    (0)  // ��ʼ�汾
#define CN_SOFT_CPU_BSP_V2    (1)  // ��ʼ�汾
// ����汾-FPGA1
#define CN_SOFT_FPGA1_V1      (0)  // ��ʼ�汾
#define CN_SOFT_FPGA1_V2      (1)  // V1.17����˫AD�ɿع���,����ģ�����������Bit8(0x0080)
#define CN_SOFT_FPGA1_V3      (2)  // V1.22��CPU�����,����ֱ������,GOOSE�Ż�,��Ƶ���ӵ�
// ����汾-FPGA2
#define CN_SOFT_FPGA2_V1      (0)  // ��ʼ�汾
#define CN_SOFT_FPGA2_V2      (1)  // 
// ����汾-MCU
#define CN_SOFT_MCU_V1        (0)  // V1.00 ��ʼ�汾
#define CN_SOFT_MCU_V2        (1)  // V1.01 DO����24V��30V��Դ����
// ����汾-LED
#define CN_SOFT_LED_V1        (0)  // ��ʼ�汾

// Ӳ���汾-CPU
#define CN_HARDWARE_MCPU_V1   (0)  // ��ʼ�汾
#define CN_HARDWARE_MCPU_V2   (1)  // ����AD��׼ȫ��Ϊ5V,����Ĭ�Ϸ���ʹ��,20211227
// Ӳ���汾-CPU_AUX
#define CN_HARDWARE_MCPU_AUX_V1 (0) // ��ʼ�汾
#define CN_HARDWARE_MCPU_AUX_V2 (1) // ȥ��ָʾ�� 20220110
// Ӳ���汾-PTCT1
#define CN_HARDWARE_PTCT1_V1  (0)  // ��ʼ�汾
#define CN_HARDWARE_PTCT1_V2  (1)  // ��CPU�����Ż� 20211107
// Ӳ���汾-PTCT2
#define CN_HARDWARE_PTCT2_V1  (0)  // ��ʼ�汾
#define CN_HARDWARE_PTCT2_V2  (1)  // ��������Ϊ2A 20211107
// Ӳ���汾-DC
#define CN_HARDWARE_DC_V1     (0)  // ��ʼ�汾20210825
// Ӳ���汾-DO
#define CN_HARDWARE_DO_V1     (0)  // ��ʼ�汾20210803
#define CN_HARDWARE_DO_V2     (1)  // ����24V��30V��Դ���� 20211221
// Ӳ���汾-DIO
#define CN_HARDWARE_DIO_V1    (0)  // ��ʼ�汾
#define CN_HARDWARE_DIO_V2    (1)  // ����24V��30V��Դ����20220106
// Ӳ���汾-OPB
#define CN_HARDWARE_OPB_V1    (0)  // ��ʼ�汾20210917
// Ӳ���汾-DI
#define CN_HARDWARE_DI_V1     (0)  // ��ʼ�汾
#define CN_HARDWARE_DI_V2     (1)  // 20220106
// Ӳ���汾-POW
#define CN_HARDWARE_POW_V1    (0)  // ��ʼ�汾
// Ӳ���汾-ĸ��
#define CN_HARDWARE_MB_V1     (0)  // ��ʼ�汾
#define CN_HARDWARE_MB_V2     (1)  // ϵͳ���԰汾,����ADͨ��ӳ��
#define CN_HARDWARE_MB_V3     (2)  // ADͨ��ӳ�����Ϊ����,����24V��30V��Դ�̵�������
// Ӳ���汾-LED
#define CN_HARDWARE_LED_V1    (0)  // ��ʼ�汾20210825

/******************************************************/
// ��ǰʹ�ð汾
/******************************************************/
// ���CPU�汾����
#define CN_SOFT_VER_CPU          (CN_SOFT_CPU_STD)
#define CN_SOFT_VER_CPU_BOOT0    (CN_SOFT_CPU_BOOT0_V1)
#define CN_SOFT_VER_CPU_UBOOT    (CN_SOFT_CPU_UBOOT_V1)
#define CN_SOFT_VER_CPU_BSP      (CN_SOFT_CPU_BSP_V2)
// ���FPGA1�汾����
#define CN_SOFT_VER_FPGA1        (CN_SOFT_FPGA1_V3)
// ���FPGA2�汾����
#define CN_SOFT_VER_FPGA2        (CN_SOFT_FPGA2_V2)
// ���MCU�汾����
#define CN_SOFT_VER_MCU          (CN_SOFT_MCU_V2)
// ���LED�汾����
#define CN_SOFT_VER_LED          (CN_SOFT_LED_V1)
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
// Ӳ��CPU��汾
#define CN_HARDWARE_MCPU         (CN_HARDWARE_MCPU_V1)
#define CN_HARDWARE_MCPU_AUX     (CN_HARDWARE_MCPU_AUX_V1)
// Ӳ��PTCT1��汾
#define CN_HARDWARE_PTCT1        (CN_HARDWARE_PTCT1_V1)
// Ӳ��PTCT2��汾
#define CN_HARDWARE_PTCT2        (CN_HARDWARE_PTCT2_V1)
// Ӳ��DC��汾
#define CN_HARDWARE_DC           (CN_HARDWARE_DC_V1)
// Ӳ��DO��汾
#define CN_HARDWARE_DO           (CN_HARDWARE_DO_V1)
// Ӳ��DIO��汾
#define CN_HARDWARE_DIO          (CN_HARDWARE_DIO_V1)
// Ӳ��OPB��汾
#define CN_HARDWARE_OPB          (CN_HARDWARE_OPB_V1)
// Ӳ��DI��汾
#define CN_HARDWARE_DI           (CN_HARDWARE_DI_V1)
// Ӳ��POW��汾
#define CN_HARDWARE_POW          (CN_HARDWARE_POW_V1)
// Ӳ��MB��汾
#define CN_HARDWARE_MB           (CN_HARDWARE_MB_V1)
// Ӳ��LED��汾
#define CN_HARDWARE_LED          (CN_HARDWARE_LED_V1)
#else
// Ӳ��CPU��汾
#define CN_HARDWARE_MCPU         (CN_HARDWARE_MCPU_V2)
#define CN_HARDWARE_MCPU_AUX     (CN_HARDWARE_MCPU_AUX_V2)
// Ӳ��PTCT1��汾
#define CN_HARDWARE_PTCT1        (CN_HARDWARE_PTCT1_V2)
// Ӳ��PTCT2��汾
#define CN_HARDWARE_PTCT2        (CN_HARDWARE_PTCT2_V2)
// Ӳ��DC��汾
#define CN_HARDWARE_DC           (CN_HARDWARE_DC_V1)
// Ӳ��DO��汾
#define CN_HARDWARE_DO           (CN_HARDWARE_DO_V2)
// Ӳ��DIO��汾
#define CN_HARDWARE_DIO          (CN_HARDWARE_DIO_V2)
// Ӳ��OPB��汾
#define CN_HARDWARE_OPB          (CN_HARDWARE_OPB_V1)
// Ӳ��DI��汾
#define CN_HARDWARE_DI           (CN_HARDWARE_DI_V2)
// Ӳ��POW��汾
#define CN_HARDWARE_POW          (CN_HARDWARE_POW_V1)
// Ӳ��MB��汾
#define CN_HARDWARE_MB           (CN_HARDWARE_MB_V3)
// Ӳ��LED��汾
#define CN_HARDWARE_LED          (CN_HARDWARE_LED_V1)
#endif
/******************************************************/
// ��Ӳ���汾����
/******************************************************/
// ����汾-CPU APP
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_STD)
#define CN_SOFT_VER_CPU_NAME      "��׼�汾"
#elif(CN_SOFT_VER_CPU==CN_SOFT_CPU_TEST)
#define CN_SOFT_VER_CPU_NAME      "���԰汾"
#elif(CN_SOFT_VER_CPU==CN_SOFT_CPU_NANJING)
#define CN_SOFT_VER_CPU_NAME      "�Ͼ���ģ�汾"
#endif
// ����汾-CPU BOOT0
#if(CN_SOFT_VER_CPU_BOOT0==CN_SOFT_CPU_BOOT0_V1)
#define CN_SOFT_VER_CPU_BOOT0_NAME "V2.02"
#endif
// ����汾-CPU UBOOT
#if(CN_SOFT_VER_CPU_UBOOT==CN_SOFT_CPU_UBOOT_V1)
#define CN_SOFT_VER_CPU_UBOOT_NAME "V2.02"
#endif
// ����汾-CPU BSP
#if(CN_SOFT_VER_CPU_BSP==CN_SOFT_CPU_BSP_V1)
#define CN_SOFT_VER_CPU_BSP_NAME  "V1.73"
#else
#define CN_SOFT_VER_CPU_BSP_NAME  "V1.75"
#endif
// ����汾-FPGA1
#if(CN_SOFT_VER_FPGA1==CN_SOFT_FPGA1_V1)
#define CN_SOFT_VER_FPGA1_NAME    "V1.17��ǰ�汾"
#elif(CN_SOFT_VER_FPGA1==CN_SOFT_FPGA1_V2)
#define CN_SOFT_VER_FPGA1_NAME    "V1.17-V1.21�汾"
#elif(CN_SOFT_VER_FPGA1==CN_SOFT_FPGA1_V3)
#define CN_SOFT_VER_FPGA1_NAME    "V1.30�����ϰ汾"
#endif
// ����汾-FPGA2
#if(CN_SOFT_VER_FPGA2==CN_SOFT_FPGA2_V1)
#define CN_SOFT_VER_FPGA2_NAME    "V1.10��ǰ�汾"
#else
#define CN_SOFT_VER_FPGA2_NAME    "V1.11"
#endif
// CPUӲ���汾����
#if(CN_HARDWARE_MCPU==CN_HARDWARE_MCPU_V1)
#define CN_HARDWARE_MCPU_NAME     "MCPU1-20210803"
#elif(CN_HARDWARE_MCPU==CN_HARDWARE_MCPU_V2)
#define CN_HARDWARE_MCPU_NAME     "MCPU1-20211227"
#endif
// CPU����Ӳ���汾����
#if(CN_HARDWARE_MCPU_AUX==CN_HARDWARE_MCPU_AUX_V1)
#define CN_HARDWARE_MCPU_AUX_NAME     "OPT1-20220110��ǰ�汾"
#elif(CN_HARDWARE_MCPU_AUX==CN_HARDWARE_MCPU_AUX_V2)
#define CN_HARDWARE_MCPU_AUX_NAME     "OPT1-20220110"
#endif
// PTCT1
#if(CN_HARDWARE_PTCT1==CN_HARDWARE_PTCT1_V1)
#define CN_HARDWARE_PTCT1_NAME     "PTCT1-20211107��ǰ�汾"
#elif(CN_HARDWARE_PTCT1==CN_HARDWARE_PTCT1_V2)
#define CN_HARDWARE_PTCT1_NAME     "PTCT1-20211107-"
#endif
// PTCT2
#if(CN_HARDWARE_PTCT2==CN_HARDWARE_PTCT2_V1)
#define CN_HARDWARE_PTCT2_NAME     "PTCT2-20211107��ǰ�汾"
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
#define CN_HARDWARE_DIO_NAME       "DIO1-20220106��ǰ�汾"
#elif(CN_HARDWARE_DIO==CN_HARDWARE_DIO_V2)
#define CN_HARDWARE_DIO_NAME       "DIO1-20220106-"
#endif
// OPB
#if(CN_HARDWARE_OPB==CN_HARDWARE_OPB_V1)
#define CN_HARDWARE_OPB_NAME       "OPB1-20210917-"
#endif
// DI
#if(CN_HARDWARE_DI==CN_HARDWARE_DI_V1)
#define CN_HARDWARE_DI_NAME        "DI1-20220106��ǰ�汾"
#elif(CN_HARDWARE_DI==CN_HARDWARE_DI_V2)
#define CN_HARDWARE_DI_NAME        "DI1-20220106-"
#endif
// MB�汾
#if(CN_HARDWARE_MB==CN_HARDWARE_MB_V1)
#define CN_HARDWARE_MB_NAME     "MBL1-20211115��ǰ�汾"
#elif(CN_HARDWARE_MB==CN_HARDWARE_MB_V2)
#define CN_HARDWARE_MB_NAME     "MBL1-20211115"
#elif(CN_HARDWARE_MB==CN_HARDWARE_MB_V3)
#define CN_HARDWARE_MB_NAME     "MBL1-20211225"
#endif

/******************************************************/
// ���Թ��ܺ궨��
/******************************************************/
#if(CN_SOFT_VER_CPU==CN_SOFT_CPU_TEST)
#define CN_TEST_TIME     (0x0001)
#define CN_TEST_2AD      (0x0002)
#define CN_TEST_SAMLOCL  (0x0004)
#define CN_TEST_MENUDBG  (0x0008)
#define CN_TEST_TCOMP    (0x0010)   // �¶Ȳ�����Ͷ��
#define CN_TEST_BAK06    (0x0020)   // ���ò��Թ���06
#define CN_TEST_BAK07    (0x0040)   // ���ò��Թ���07
#define CN_TEST_BAK08    (0x0080)   // ���ò��Թ���08
#define CN_TEST_BAK09    (0x0100)   // ���ò��Թ���09
#define CN_TEST_BAK10    (0x0200)   // ���ò��Թ���10
#define CN_TEST_BAK11    (0x0400)   // ���ò��Թ���11
#define CN_TEST_BAK12    (0x0800)   // ���ò��Թ���12
#define CN_TEST_BAK13    (0x1000)   // ���ò��Թ���13
#define CN_TEST_BAK14    (0x2000)   // ���ò��Թ���14
#define CN_TEST_BAK15    (0x4000)   // ���ò��Թ���15
#define CN_TEST_BAK16    (0x8000)   // ���ò��Թ���16

#define CN_SOFT_CPU_TEST_CFG           (CN_TEST_SAMLOCL+CN_TEST_TCOMP)//���Թ���Ͷ��
#define CN_SOFT_CPU_TEST_GET(Index)    ((CN_SOFT_CPU_TEST_CFG&(Index))!=0)
#else
#define CN_SOFT_CPU_TEST_GET(Index)    (0)
#endif

#endif  /* _CONST_EQUIP_H_ */
