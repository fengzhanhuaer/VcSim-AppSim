/*================================================================================
 * 文件描述：系统资源变量定义
 * 文件版本: V1.00
 * 定版时间:
 * 版本修订:
 * 修订人员:
 *================================================================================*/

#include "IES_IMsrc.h"
/*================================================================================*/
// 应用侧全局数据区
/*================================================================================*/
tagDevInfor   g_tDevInfor;                // 版本信息
tagAna        g_tagAna;                   // 模拟量数据
tagIO         g_tagIO;                    // IO数据
tagDC         g_tagDC;                    // 直流数据
tagPara       g_tagPara;                  // 参数
tagRamScan    g_tagRamScan;               // 内存扫描结构体
tagPub        g_tagPub;                   // 公共数据
BOOL          g_bFlag[CN_NUM_FLAG+1];     // 全局布尔变量标志定义
INT32         g_iInter[CN_NUM_INTER+1];   // 全局内部数据定义
tagActState   g_tActState;                // GOOSE命令事件实时状态
tagAlmState   g_tAlmState;                // 告警事件实时状态
tagChkState   g_tChkState;                // 自检事件实时状态
// 事项队列
tagActQueue     g_tActQueue;              // GOOSE命令事件缓冲队列
tagAlmQueue     g_tAlmQueue;              // 告警事件缓冲队列
tagChkQueue     g_tChkQueue;              // 自检事件缓冲队列
tagDiQueue      g_tDiQueue;               // 硬开入单点SOE缓冲队列
tagDpiQueue     g_tDpiQueue;              // 硬开入双点SOE缓冲队列
tagDoQueue      g_tDoQueue;               // 硬开出SOE缓冲队列
tagGoInQueue    g_tGoInQueue;             // GOOSE订阅SOE缓冲队列
tagGoOutQueue   g_tGoOutQueue;            // GOOSE发布SOE缓冲队列
tagLedQueue     g_tLedQueue;              // 指示灯SOE缓冲队列


