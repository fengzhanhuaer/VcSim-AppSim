#include "InstResource.h"

ApiSjRecordGroup SjUsrLogRecord; // �û���¼���¼
ApiSjRecordGroup SjUsrAdmRecord; // �û������¼
ApiSjRecordGroup SjContrlRecord; // �������¼
//ApiSjRecordGroup SjSystemRecord; // ϵͳ���¼
ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni()
{
	SjUsrLogRecord.PowerUpIni("�û���¼",        "SjUsrLogRecord", CN_SJRECORD_MAX_POOLLEN);
	SjUsrAdmRecord.PowerUpIni("�û�����",        "SjUsrAdmRecord", CN_SJRECORD_MAX_POOLLEN);
	SjContrlRecord.PowerUpIni("������",          "SjContrlRecord", CN_SJRECORD_MAX_POOLLEN);
//	SjSystemRecord.PowerUpIni("ϵͳ��",          "SjSystemRecord", CN_SJRECORD_MAX_POOLLEN);
	HmiSjRecordViewPool.PowerUpIni(CN_SJRECORD_MAX_POOLLEN);
}
