#include "InstResource.h"

ApiSjRecordGroup SjUsrLogRecord;//�û���¼��¼
ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni()
{
	SjUsrLogRecord.PowerUpIni("�û���¼", "SjRunRecord", CN_SJRECORD_MAX_POOLLEN);
	HmiSjRecordViewPool.PowerUpIni(CN_SJRECORD_MAX_POOLLEN);
}