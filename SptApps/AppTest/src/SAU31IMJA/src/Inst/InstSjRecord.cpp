#include "InstResource.h"

ApiSjRecordGroup SjUsrLogRecord; // 用户登录类记录
ApiSjRecordGroup SjUsrAdmRecord; // 用户管理记录
ApiSjRecordGroup SjContrlRecord; // 控制类记录
//ApiSjRecordGroup SjSystemRecord; // 系统类记录
ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni()
{
	SjUsrLogRecord.PowerUpIni("用户登录",        "SjUsrLogRecord", CN_SJRECORD_MAX_POOLLEN);
	SjUsrAdmRecord.PowerUpIni("用户管理",        "SjUsrAdmRecord", CN_SJRECORD_MAX_POOLLEN);
	SjContrlRecord.PowerUpIni("控制类",          "SjContrlRecord", CN_SJRECORD_MAX_POOLLEN);
//	SjSystemRecord.PowerUpIni("系统类",          "SjSystemRecord", CN_SJRECORD_MAX_POOLLEN);
	HmiSjRecordViewPool.PowerUpIni(CN_SJRECORD_MAX_POOLLEN);
}
