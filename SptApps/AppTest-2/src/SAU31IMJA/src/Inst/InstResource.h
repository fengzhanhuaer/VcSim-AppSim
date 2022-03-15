#ifndef INSTRESOURCE_H
#define INSTRESOURCE_H

#include"ApiProject.h"
// 应用侧数据调用
#include "IES_IMInterFace.h"
using namespace spt;
#include "InstPara.h"
#include "InstEvent.h"
#include "InstAngIn.h"
#include "InstAngOut.h"
#include "InstDispCfg.h"
#include "InstHmiLed.h"
#include "InstMenu.h"
#include "InstAppFlags.h"
#include "InstInterFace.h"
#include "InstStateIn.h"
#include "InstStateOut.h"
#include "InstSjRecord.h"
#include "InstAppCmm.h"
#include "InstT860Scl.h"
#include "InstCheck.h"

extern ApiSampAppTask sampAppArr[1];
extern ApiAppCfg AppRunTimeCfg;


#endif // !INSTRESOURCE_H
