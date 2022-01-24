#ifndef InstSjRecord_H
#define InstSjRecord_H


const uint32 CN_SJRECORD_MAX_POOLLEN = 1024;

extern ApiSjRecordGroup SjUsrLogRecord; // 用户登录类记录
extern ApiSjRecordGroup SjUsrAdmRecord; // 用户管理记录
extern ApiSjRecordGroup SjContrlRecord; // 控制类记录
//extern ApiSjRecordGroup SjSystemRecord; // 控制类记录
extern ApiSjRecordViewPool HmiSjRecordViewPool;

void AppSjRecordPowerUpIni();

#endif
