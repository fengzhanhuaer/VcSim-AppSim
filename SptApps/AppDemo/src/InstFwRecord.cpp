#include "InstResource.h"


ApiFwDigital FwDigital[10];
ApiFwAnalog FwAnalog[5];
ApiFwEvent FwProtEvent[5];
ApiFwRecordGroup FwGroupPub;
ApiFwRecordGroup FwGroupPrivate;

void AppFwRecordPowerUpIni()
{
	SalFwRecordGroup::uFlags f1;
	f1.u32 = 0;
	f1.st.is2t860 = 1;
	FwGroupPub.PowerUpIni("FwGroupPub", "FwGroupPub", 50, 80, 2048, 24, 48, 10, 10, 5, f1.u32);
	FwGroupPub.SetParaGroup(0, &ProtParaGroup);
	SalFwWaveCfgCell::uFlags f2;
	f2.u32 = 0;
	f2.st.isDatDigCfg = 1;
	f2.st.isHdrDig = 1;
	f2.st.isMidDig = 1;
	FwDigital[0].PowerUpIni("test1", "test1", FwGroupPub, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 3, 4, 3, 4, 1);
	FwDigital[1].PowerUpIni("test2", "test2", FwGroupPub, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 4, 3, 2, 1, 1);
	FwDigital[2].PowerUpIni("test3", "test3", FwGroupPub, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 5, 4, 4, 0, 1);
	FwDigital[3].PowerUpIni("test4", "test4", FwGroupPub, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 6, 6, 0, 4, 1);
	f2.u32 = 0;
	f2.st.isDatAngCfg = 1;
	FwAnalog[0].PowerUpIni("atest1", "atest1", FwGroupPub, E_Ang_Phase::EAP_Null, "", Unit_A, 0, 1, 0, 1, 1, 0, f2.u32, 1);
	FwAnalog[1].PowerUpIni("atest2", "atest2", FwGroupPub, E_Ang_Phase::EAP_Null, "", Unit_A, 0, 1, 0, 1, 1, 0, f2.u32, 1);
	f2.u32 = 0;
	f2.st.isMidAng = 1;
	FwAnalog[2].PowerUpIni("atest3", "atest3", FwGroupPub, E_Ang_Phase::EAP_Null, "", Unit_A, 0, 1, 0, 1, 1, 0, f2.u32, 1);
	FwAnalog[3].PowerUpIni("atest4", "atest4", FwGroupPub, E_Ang_Phase::EAP_Null, "", Unit_A, 0, 1, 0, 1, 1, 0, f2.u32, 1);
	f2.u32 = 0;
	f2.st.isDatDigCfg = 1;
	f2.st.isEvent = 1;
	f2.st.isMidDig = 1;
	FwProtEvent[1].PowerUpIni("etest1", "etest1", AppEventWarn[0], FwGroupPub, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 0, 21, 1, 0, 1);
	FwProtEvent[2].PowerUpIni("etest2", "etest2", AppEventWarn[1], FwGroupPub, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 0, 1, 21, 0, 1);

	f1.u32 = 0;
	f1.st.isPrivate = 1;
	FwGroupPrivate.PowerUpIni("FwGroupPrivate", "FwGroupPrivate", 50, 80, 512, 12, 24, 0, 10, 5, f1.u32);
	f2.u32 = 0;
	FwDigital[7].PowerUpIni("test7", "test7", FwGroupPrivate, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 3, 3, 0, 0, 1);
	f2.u32 = 0;
	f2.st.isDatDigCfg = 1;
	f2.st.isEvent = 1;
	f2.st.isMidDig = 1;
	FwProtEvent[3].PowerUpIni("etest3", "etest3", AppEventWarn[0], FwGroupPrivate, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 0, 1, 2, 3, 1);
	FwProtEvent[4].PowerUpIni("etest4", "etest4", AppEventWarn[1], FwGroupPrivate, E_Ang_Phase::EAP_Null, "", 0, f2.u32, 0, 1, 4, 2, 1);
}


void AppFwUpdate()
{
	SalDateStamp stamp;
	stamp.Now();
	uint32 us = (uint32)(stamp.Us() / 10000);
	for (uint32 i = 0; i < 7; i++)
	{
		FwDigital[i].Update((us & (0x01 << i)) == 0);
	}
	for (uint32 i = 0; i < 2; i++)
	{
		AppEventWarn[i].Update((us & (0x80 << i)) == 0);
	}
	uint64 sampStamp = SptSampAppTaskScheduler::Instance().PowerUpSampStamp();
	FwAnalog[0].Update((float32)(sampStamp >> 0));
	FwAnalog[1].Update((float32)(sampStamp >> 5));
	FwAnalog[2].Update((float32)(sampStamp >> 8));
	FwAnalog[3].Update((float32)(sampStamp >> 12));
	FwGroupPub.RecordOnePoint(stamp, sampStamp);
	FwGroupPrivate.RecordOnePoint(stamp, sampStamp);
}
