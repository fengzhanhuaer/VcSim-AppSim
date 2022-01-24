#include "InstResource.h"


int32 T860CCDLinkDataSet()
{
	SptGoSvInfo& gosvInfo = SptCcdFile::Instance().GoSvInfo();
	uint32 tt = gosvInfo.ParseInfo.svSubNum;
	for (uint32 i = 0; i < tt; i++)
	{
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.svcbSub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性
			gosvInfo.ParseInfo.svcbSub[i].connect.InnerPortIndex[j] = gosvInfo.ParseInfo.svcbSub[i].connect.Card_Port[j] & 0xff;
			if (gosvInfo.ParseInfo.svEnableSubNum < M_ArrLen(VirSvBoard))
			{
				SptSvInDataSet* dataset = (SptSvInDataSet*)&VirSvBoard[gosvInfo.ParseInfo.svEnableSubNum];
				if (dataset->SetSvCbCfg(&gosvInfo.ParseInfo.svcbSub[i], j, gosvInfo.ParseInfo.svEnableSubNum))
				{
					gosvInfo.ParseInfo.svEnableSubNum++;
				}
			}
		}
		gosvInfo.ParseInfo.svcbSub[i].linked = 1;
	}
	tt = gosvInfo.ParseInfo.svPubNum;
	for (uint32 i = 0; i < tt; i++)
	{
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.svcbPub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性
			gosvInfo.ParseInfo.svcbPub[i].connect.InnerPortIndex[j] = gosvInfo.ParseInfo.svcbPub[i].connect.Card_Port[j] & 0xff;
		}
		if (gosvInfo.ParseInfo.svEnablePubNum < M_ArrLen(virSvSendDateSet))
		{
			SptSvOutDataSet* dataset = (SptSvOutDataSet*)&virSvSendDateSet[gosvInfo.ParseInfo.svEnablePubNum];
			if (dataset->SetSvCbCfg(&gosvInfo.ParseInfo.svcbPub[i], gosvInfo.ParseInfo.svEnablePubNum))
			{
				gosvInfo.ParseInfo.svEnablePubNum++;
			}
		}
		gosvInfo.ParseInfo.svcbPub[i].linked = 1;
	}
	tt = gosvInfo.ParseInfo.goSubNum;
	for (uint32 i = 0; i < tt; i++)
	{
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.gocbSub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性
			gosvInfo.ParseInfo.gocbSub[i].connect.AInnerPortIndex[j] = gosvInfo.ParseInfo.gocbSub[i].connect.ACard_Port[j] & 0xff;
			gosvInfo.ParseInfo.gocbSub[i].connect.BInnerPortIndex[j] = gosvInfo.ParseInfo.gocbSub[i].connect.BCard_Port[j] & 0xff;
			if (gosvInfo.ParseInfo.goEnableSubNum < M_ArrLen(GoInCB))
			{
				SptGooseDataSetIn* dataset = (SptGooseDataSetIn*)&GoInCB[gosvInfo.ParseInfo.goEnableSubNum];
				if (dataset->SetGoCbCfg(&gosvInfo.ParseInfo.gocbSub[i], j, gosvInfo.ParseInfo.goEnableSubNum))
				{
					gosvInfo.ParseInfo.goEnableSubNum++;
				}
			}
		}
		gosvInfo.ParseInfo.gocbSub[i].linked = 1;
	}
	tt = gosvInfo.ParseInfo.goPubNum;
	for (uint32 i = 0; i < tt; i++)
	{
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.gocbPub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性
			gosvInfo.ParseInfo.gocbPub[i].connect.AInnerPortIndex[j] = gosvInfo.ParseInfo.gocbPub[i].connect.ACard_Port[j] & 0xff;
		}
		if (gosvInfo.ParseInfo.goEnablePubNum < M_ArrLen(GoDataSetOut))
		{
			SptGooseDataSetOut* dataset = (SptGooseDataSetOut*)&GoDataSetOut[gosvInfo.ParseInfo.goEnablePubNum];
			if (dataset->SetGoCbCfg(&gosvInfo.ParseInfo.gocbPub[i], gosvInfo.ParseInfo.goEnablePubNum))
			{
				gosvInfo.ParseInfo.goEnablePubNum++;
			}
		}
		gosvInfo.ParseInfo.gocbPub[i].linked = 1;
	}
	return 0;
}
void GetT860Version()
{
#if 0
	uint32 version;
	char* url;
	char* date;
	SptVersion& T860Ver = ApiVersionInfo::Instance().ApiT860Version();
	ieslab_get_version(&version, &url, &date);
	SalDate sdate;
	sdate.FromStrFmt2(date);
	T860Ver.SetOk(1);
	StrNCpy(T860Ver.programName, "T860Lite", sizeof(T860Ver.programName));
	T860Ver.datetimeus = sdate.Stamp();
	T860Ver.major = version / 100 % 10;
	T860Ver.minor = version / 10 % 10;
	T860Ver.reversion = version % 10;
#endif // SYLIX_GZK
}
int32 T860PowerUpIni()
{
	GetT860Version();
	SptT860Info::Instance().CheckOutputDataSet();
	SptCcdFile::Instance().PowerUpIni(20, 10, 20, 5);
	T860CCDLinkDataSet();
	return 0;
}

int32 T860SclMain()
{


	return 0;
}
