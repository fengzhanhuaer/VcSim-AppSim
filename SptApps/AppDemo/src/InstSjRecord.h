#ifndef InstSjRecord_H
#define InstSjRecord_H


const uint32 CN_SJRECORD_MAX_POOLLEN = 2096;


extern ApiSjRecordGroup SjUsrLogRecord;
extern ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni();

#endif