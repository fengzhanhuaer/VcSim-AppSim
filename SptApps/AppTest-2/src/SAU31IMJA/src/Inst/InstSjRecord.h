#ifndef InstSjRecord_H
#define InstSjRecord_H


const uint32 CN_SJRECORD_MAX_POOLLEN = 1024;

extern ApiSjRecordGroup SjUsrLogRecord; // �û���¼���¼
extern ApiSjRecordGroup SjUsrAdmRecord; // �û������¼
extern ApiSjRecordGroup SjContrlRecord; // �������¼
//extern ApiSjRecordGroup SjSystemRecord; // �������¼
extern ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni();

#endif
