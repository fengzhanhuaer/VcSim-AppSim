#include "InstResource.h"

ApiSjRecordGroup SjUsrLogRecord;//用户登录记录
ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni()
{
	SjUsrLogRecord.PowerUpIni("用户登录", "SjRunRecord", CN_SJRECORD_MAX_POOLLEN);
	HmiSjRecordViewPool.PowerUpIni(CN_SJRECORD_MAX_POOLLEN);
}