#include "InstResource.h"


int32 T860CCDLinkDataSet()
{
	uint8 bygoEna = 0;
	SptGoSvInfo& gosvInfo = SptCcdFile::Instance().GoSvInfo();
	uint32 tt = gosvInfo.ParseInfo.svSubNum;
	uint8  byPortMax,k=0;
	byPortMax = g_tCardTab[CN_BOARD_CPU].byPortNum;

#if(CN_DEV_CPU1)
	for (uint32 i = 0; i < tt; i++)
	{
		if (gosvInfo.ParseInfo.svcbSub[i].linked)
		{
			continue;
		}
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.svcbSub[i].connect.PortEnableNum; j++)
		{
			uint8 Card = gosvInfo.ParseInfo.svcbSub[i].connect.Card_Port[j] >> 8;
			uint8 Port = (uint8)gosvInfo.ParseInfo.svcbSub[i].connect.Card_Port[j]&0xff;
			// 判断是否CPU1板,SV仅CPU1板订阅
			if ((Card != EN_CARD_CPU1) || (Port >byPortMax)||(Port==0))
			{
				G_Set_Inter(EN_INTER_SVSUB_PORT,TRUE);
				continue;
			}
			// 应用应在此处判断板卡号与端口号的正确性
			gosvInfo.ParseInfo.svcbSub[i].connect.InnerPortIndex[j] = Port-1;
			if (k < M_ArrLen(VirSvBoard))
			{
				SptSvInDataSet* dataset = (SptSvInDataSet*)&VirSvBoard[k++];
				// 配置异常不再进行下发
				if((gosvInfo.ParseInfo.svcbSub[i].parseErr)
				||(gosvInfo.ParseInfo.svcbSub[i].sAddrErr)
				||(gosvInfo.ParseInfo.svcbSub[i].cfgErr)
				)
				{
					// 参数异常
					if(gosvInfo.ParseInfo.svcbSub[i].parseErr)
					{
						G_Set_Inter(EN_INTER_SVSUB_PARAERR,TRUE);
					}
					// 短地址异常
					if(gosvInfo.ParseInfo.svcbSub[i].sAddrErr)
					{
						G_Set_Inter(EN_INTER_SVSUB_ADRERR,TRUE);
					}
					// 配置异常
					if(gosvInfo.ParseInfo.svcbSub[i].cfgErr)
					{
						G_Set_Inter(EN_INTER_SVSUB_CFGERR,TRUE);
					}
				}
				else if (dataset->SetSvCbCfg(&gosvInfo.ParseInfo.svcbSub[i], j, gosvInfo.ParseInfo.svEnableSubNum))
				{
					gosvInfo.ParseInfo.svEnableSubNum++;
				}
				else
				{
					G_Set_Inter(EN_INTER_SVSUB_CFGERR,TRUE);
				}
				
			}
			else
			{
				G_Set_Inter(EN_INTER_SVSUB_NUMERR,TRUE);
			}
		}
		if(gosvInfo.ParseInfo.svcbSub[i].connect.PortEnableNum==0)
		{
			G_Set_Inter(EN_INTER_SVSUB_PORT,TRUE);
		}
		gosvInfo.ParseInfo.svcbSub[i].linked = 1;
	}
	g_tagAna.bySvCbSubNum  = k;
	k=0;
#endif
	tt = gosvInfo.ParseInfo.svPubNum;
	for (uint32 i = 0; i < tt; i++)
	{
	
		bygoEna=0;
		if (gosvInfo.ParseInfo.svcbPub[i].linked)
		{
			continue;
		}
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.svcbPub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性
			uint8 Card = gosvInfo.ParseInfo.svcbPub[i].connect.Card_Port[j] >> 8;
			uint8 Port = (uint8)gosvInfo.ParseInfo.svcbPub[i].connect.Card_Port[j]&0xff;
			// 间隔采执仅CPU1、CPU2发布
			if ((Card != CN_BOARD_CPU)&&(Card != CN_BOARD_CPU_OTH))
			{
				G_Set_Inter(EN_INTER_SVPUB_PORT,TRUE);
			}
			if (Card!=CN_BOARD_CPU)
			{
				continue;
			}
			if((Port >byPortMax)||(Port==0))
			{
				G_Set_Inter(EN_INTER_SVPUB_PORT,TRUE);
				continue;
			}
			
			gosvInfo.ParseInfo.svcbPub[i].connect.InnerPortIndex[j] = Port-1;
			bygoEna =1;
		}
		if (((k <1)&&(bygoEna))||(gosvInfo.ParseInfo.svcbPub[i].connect.PortEnableNum==0))
		{
			SptSvOutDataSet* dataset = (SptSvOutDataSet*)&virSvSendDateSet;
			k++;
			if((gosvInfo.ParseInfo.svcbPub[i].parseErr)
			||(gosvInfo.ParseInfo.svcbPub[i].sAddrErr)
			||(gosvInfo.ParseInfo.svcbPub[i].cfgErr)
			||(gosvInfo.ParseInfo.svcbPub[i].connect.PortEnableNum==0)
			)
			{
				// 参数异常
				if(gosvInfo.ParseInfo.svcbPub[i].parseErr)
				{
					G_Set_Inter(EN_INTER_SVPUB_PARAERR,TRUE);
				}
				// 短地址异常
				if(gosvInfo.ParseInfo.svcbPub[i].sAddrErr)
				{
					G_Set_Inter(EN_INTER_SVPUB_ADRERR,TRUE);
				}
				// 配置异常
				if(gosvInfo.ParseInfo.svcbPub[i].cfgErr)
				{
					G_Set_Inter(EN_INTER_SVPUB_CFGERR,TRUE);
				}
				if(gosvInfo.ParseInfo.svcbPub[i].connect.PortEnableNum==0)
				{
					G_Set_Inter(EN_INTER_SVPUB_PORT,TRUE);
				}
			}
			else if (dataset->SetSvCbCfg(&gosvInfo.ParseInfo.svcbPub[i], gosvInfo.ParseInfo.svEnablePubNum))
			{
				gosvInfo.ParseInfo.svEnablePubNum++;
			}
			else
			{
				G_Set_Inter(EN_INTER_SVPUB_CFGERR,TRUE);
			}
		}
		else if(bygoEna)
		{
			G_Set_Inter(EN_INTER_SVPUB_NUMERR,TRUE);
		}
		gosvInfo.ParseInfo.svcbPub[i].linked = 1;
	}
	g_tagAna.bySvCbPubNum  = k;
	k=0;
	tt = gosvInfo.ParseInfo.goSubNum;
	for (uint32 i = 0; i < tt; i++)
	{
	
		if (gosvInfo.ParseInfo.gocbSub[i].linked)
		{
			continue;
		}
		//应用应在此处决定是否允许一个控制块从多个口进入
		for (uint32 j = 0; j < gosvInfo.ParseInfo.gocbSub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性(不能完全剔除)
			uint8 Card = gosvInfo.ParseInfo.gocbSub[i].connect.ACard_Port[j] >> 8;
			uint8 Port = (uint8)gosvInfo.ParseInfo.gocbSub[i].connect.ACard_Port[j]&0xff;
			// 判断是否CPU1板
			if ((Card != CN_BOARD_CPU) && (Card != CN_BOARD_CPU_OTH))
			{
				G_Set_Inter(EN_INTER_GOSUB_PORT, TRUE);
			}
			if (Card != CN_BOARD_CPU)
			{
				continue;
			}
			if ((Port >byPortMax)||(Port==0))
			{
				G_Set_Inter(EN_INTER_GOSUB_PORT,TRUE);
				continue;
			}
			gosvInfo.ParseInfo.gocbSub[i].connect.AInnerPortIndex[j] = Port-1;;
			
			Card = gosvInfo.ParseInfo.gocbSub[i].connect.BCard_Port[j] >> 8;
			Port = (uint8)gosvInfo.ParseInfo.gocbSub[i].connect.BCard_Port[j]&0xff;

			if ((Card == CN_BOARD_CPU) &&(Port<byPortMax)&&(Port!=0))
			{
				gosvInfo.ParseInfo.gocbSub[i].connect.BInnerPortIndex[j] = Port-1;
			}
			if (k< M_ArrLen(GoInCB))
			{
				SptGooseDataSetIn* dataset = (SptGooseDataSetIn*)&GoInCB[k++];
				if((gosvInfo.ParseInfo.gocbSub[i].parseErr)
				||(gosvInfo.ParseInfo.gocbSub[i].sAddrErr)
				||(gosvInfo.ParseInfo.gocbSub[i].cfgErr)
				)
				{
					// 参数异常
					if(gosvInfo.ParseInfo.gocbSub[i].parseErr)
					{
						G_Set_Inter(EN_INTER_GOSUB_PARAERR,TRUE);
					}
					// 短地址异常
					if(gosvInfo.ParseInfo.gocbSub[i].sAddrErr)
					{
						G_Set_Inter(EN_INTER_GOSUB_ADRERR,TRUE);
					}
					// 配置异常
					if(gosvInfo.ParseInfo.gocbSub[i].cfgErr)
					{
						G_Set_Inter(EN_INTER_GOSUB_CFGERR,TRUE);
					}
				}
				else if (dataset->SetGoCbCfg(&gosvInfo.ParseInfo.gocbSub[i], j, gosvInfo.ParseInfo.goEnableSubNum))
				{
					gosvInfo.ParseInfo.goEnableSubNum++;
				}
				else
				{
					G_Set_Inter(EN_INTER_GOSUB_CFGERR,TRUE);
				}
			}
			else
			{
				G_Set_Inter(EN_INTER_GOSUB_NUMERR,TRUE);
			}
		}
		if(gosvInfo.ParseInfo.gocbSub[i].connect.PortEnableNum==0)
		{
			G_Set_Inter(EN_INTER_GOSUB_PORT,TRUE);
		}
		gosvInfo.ParseInfo.gocbSub[i].linked = 1;
	}
	g_tagIO.byGoCbSubNum  = k;
	k=0;
	tt = gosvInfo.ParseInfo.goPubNum;
	for (uint32 i = 0; i < tt; i++)
	{
		bygoEna=0;
		//应用应在此处决定是否允许一个控制块从多个口进入
		if (gosvInfo.ParseInfo.gocbPub[i].linked)
		{
			continue;
		}
		for (uint32 j = 0; j < gosvInfo.ParseInfo.gocbPub[i].connect.PortEnableNum; j++)
		{
			// 应用应在此处判断板卡号与端口号的正确性
			uint8 Card = gosvInfo.ParseInfo.gocbPub[i].connect.ACard_Port[j] >> 8;
			uint8 Port = (uint8)gosvInfo.ParseInfo.gocbPub[i].connect.ACard_Port[j]&0xff;
			if ((Card != CN_BOARD_CPU) && (Card != CN_BOARD_CPU_OTH))
			{
				G_Set_Inter(EN_INTER_GOPUB_PORT, TRUE);
			}
			// 判断是否CPU板
			if (Card != CN_BOARD_CPU)
			{
				continue;
			}
			if((Port >byPortMax)||(Port==0))
			{
				G_Set_Inter(EN_INTER_GOPUB_PORT,TRUE);
				continue;
			}
			gosvInfo.ParseInfo.gocbPub[i].connect.AInnerPortIndex[j] = Port-1;
			bygoEna =1;
		}
		if (((k < M_ArrLen(GoDataSetOut))&&(bygoEna))||(gosvInfo.ParseInfo.gocbPub[i].connect.PortEnableNum==0))
		{
			SptGooseDataSetOut* dataset = (SptGooseDataSetOut*)&GoDataSetOut[k++];
			if((gosvInfo.ParseInfo.gocbPub[i].parseErr)
			||(gosvInfo.ParseInfo.gocbPub[i].sAddrErr)
			||(gosvInfo.ParseInfo.gocbPub[i].cfgErr)
			||(gosvInfo.ParseInfo.gocbPub[i].connect.PortEnableNum==0)
			)
			{
				// 参数异常
				if(gosvInfo.ParseInfo.gocbPub[i].parseErr)
				{
					G_Set_Inter(EN_INTER_GOPUB_PARAERR,TRUE);
				}
				// 短地址异常
				if(gosvInfo.ParseInfo.gocbPub[i].sAddrErr)
				{
					G_Set_Inter(EN_INTER_GOPUB_ADRERR,TRUE);
				}
				// 配置异常
				if(gosvInfo.ParseInfo.gocbPub[i].cfgErr)
				{
					G_Set_Inter(EN_INTER_GOPUB_CFGERR,TRUE);
				}
				if(gosvInfo.ParseInfo.gocbPub[i].connect.PortEnableNum==0)
				{
					G_Set_Inter(EN_INTER_GOPUB_PORT,TRUE);
				}
			}
			else if (dataset->SetGoCbCfg(&gosvInfo.ParseInfo.gocbPub[i], gosvInfo.ParseInfo.goEnablePubNum))
			{
				gosvInfo.ParseInfo.goEnablePubNum++;
			}
			else
			{
				G_Set_Inter(EN_INTER_GOPUB_CFGERR,TRUE);
			}
		}
		else if(bygoEna)
		{
			G_Set_Inter(EN_INTER_GOPUB_NUMERR,TRUE);
		}
		gosvInfo.ParseInfo.gocbPub[i].linked = 1;
	}
	g_tagIO.byGoCbPubNum  = k;
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
	SptCcdFile::Instance().PowerUpIni(CN_NUM_GOCB_SUB, CN_NUM_GOCB_PUB, CN_NUM_SVCB_SUB, CN_NUM_SVCB_PUB);
	T860CCDLinkDataSet();
	return 0;
}

int32 T860SclMain()
{
	return 0;
}
