#include "ApiProject.h"
using namespace spt;
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

void spt::SptIoProcess::PowerUpIni(int Para)
{
	const struct ApiAppCfg* cfg = SptMain::Instance().AppCfg();
	if (!cfg)
	{
		proCess = 0;
		return;
	}
	switch (cfg->platform.hardware)
	{
	case EH_GZKSAU:
	{
		proCess = new SptGzkMuIoProcess();
		proCess->PowerUpIni(Para);
		break;
	}
	default:
		proCess = 0;
		break;
	}
}

void spt::SptIoProcess::RecvNorIoMsg(void* Buf, uint16 Len)
{
	if (proCess)
	{
		proCess->RecvNorIoMsg(Buf, Len);
	}
}

void spt::SptIoProcess::RecvAngFrameMsg(void* Buf, uint16 Len)
{
	if (proCess)
	{
		proCess->RecvAngFrameMsg(Buf, Len);
	}
}

void spt::SptIoProcess::RecvGoPosFrameMsg(void* Buf, uint16 Len)
{
	if (proCess)
	{
		proCess->RecvGoPosFrameMsg(Buf, Len);
	}
}

void spt::SptIoProcess::RecvGoAngFrameMsg(void* Buf, uint16 Len)
{
	if (proCess)
	{
		proCess->RecvGoAngFrameMsg(Buf, Len);
	}
}

void spt::SptIoProcess::RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen)
{
	if (proCess)
	{
		proCess->RecSvInCbCheckStateMsg(Buf, BufLen);
	}
}

void spt::SptIoProcess::RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen)
{
	if (proCess)
	{
		proCess->RecGoInCbCheckStateMsg(Buf, BufLen);
	}
}

void spt::SptIoProcess::RecBoardInfoMsg(void* Buf, uint32 BufLen)
{
	if (proCess)
	{
		proCess->RecBoardInfoMsg(Buf, BufLen);
	}

}

void spt::SptIoProcess::RecLightInfoMsg(void* Buf, uint32 BufLen)
{
	if (proCess)
	{
		proCess->RecLightInfoMsg(Buf, BufLen);
	}
}
void spt::SptIoProcess::RecFpgaSlowMsg(void* Buf, uint32 BufLen)
{
	if (proCess)
	{
		proCess->RecFpgaSlowMsg(Buf, BufLen);
	}

}
void spt::SptIoProcess::ResetSubBoardState()
{
	if (proCess)
	{
		LogMsg.Stamp() << "ResetSubBoardState \n";
		proCess->ResetSubBoardState();
	}
}
void spt::SptIoProcess::RecBoardMsg(void* Buf, uint32 BufLen)
{
	if (proCess)
	{
		proCess->RecBoardMsg(Buf, BufLen);
	}
}

void spt::SptIoProcess::ProcIn()
{
	sptFlag.SptFlagProcess();
	if (proCess)
	{
		proCess->ProcIn();
	}
	if (appFlags.blFaceRevert)
	{
		if (!faceRevertStart.IsEnable())
		{
			faceRevertStart.UpCnt(200);
			faceRevertStart.Enable(1);
		}
	}
	if (faceRevertStart.IsEnable())
	{
		if (faceRevertStart.Status())
		{
			appFlags.blFaceRevert = 0;
			faceRevertStart.Enable(0);
		}
	}
	if (appFlags.blUnitRevert)
	{
		if (!revertStart.IsEnable())
		{
			revertStart.UpCnt(2000);
			revertStart.Enable(1);
		}
	}
	if (revertStart.IsEnable())
	{
		if (revertStart.Status())
		{
			appFlags.blUnitRevert = 0;
			revertStart.Enable(0);
		}
	}
}

void spt::SptIoProcess::ProcOut()
{
	if (proCess)
	{
		proCess->ProcOut();
	}
}

void spt::SptIoProcess::EnableSVSend(bool8 Enable)
{
	if (proCess)
	{
		proCess->EnableSVSend(Enable);
	}
}

void spt::SptIoProcess::EnableAngErrPointDeal(bool8 Enable)
{
	if (proCess)
	{
		proCess->EnableAngErrPointDeal(Enable);
	}
}

void spt::SptIoProcess::EnableGoSend(bool8 Enable)
{
	if (proCess)
	{
		proCess->EnableGoSend(Enable);
	}

}

void spt::SptIoProcess::CfgSendOver(bool8 Enable)
{
	if (proCess)
	{
		proCess->CfgSendOver(Enable);
	}
}

uint8 spt::SptIoProcess::GetFpagSlowFlags(uint16 Index)
{
	if (proCess)
	{
		proCess->GetFpagSlowFlags(Index);
	}

	return 0;
}

uint32 spt::SptIoProcess::BoardOnLineState()
{
	if (proCess)
	{
		return proCess->BoardOnLineState();
	}
	return 0;
}

bool8 spt::SptIoProcess::IsIoPowerUpOver()
{
	if (proCess)
	{
		return proCess->IsIoPowerUpOver();
	}
	return 0;
}

spt::SptIoProcess::SptIoProcess()
{
	proCess = 0;
}

bool8 spt::SptIedIoProcess::IsIoPowerUpOver()
{
	return isPowerUpOver;
}

spt::SptIedIoProcess::SptIedIoProcess()
{
	isPowerUpOver = 0;
}

bool8 spt::SptIedIoProcess::IsRecvBoardFrameMsgOk(void* Buf, uint16 Len)
{
	uint16 sum = 0;
	uint8* ptr = (uint8*)Buf;
	for (uint16 i = 0; i < Len; i++)
	{
		sum += *ptr++;
	}
	uint16 fsum = ptr[1];

	fsum = (fsum << 8) + ptr[0];

	return sum == fsum;
}



void spt::SptGzkMuIoProcess::PowerUpIni(int Para)
{
	isPowerUpOver = 0;
	SlowCmdCnt = 0;
	ProcInSerialBoardBuf.Alloc(sizeof(void*), 20);
	ProcOutSerialBoardBuf.Alloc(sizeof(void*), 20);
	NorDiSerialBoardBuf.Alloc(sizeof(void*), 20);
	NorDiAddrBoardBuf.Alloc(sizeof(void*), 20);
	NorDoSerialBoardBuf.Alloc(sizeof(void*), 20);
	NorDoAddrBoardBuf.Alloc(sizeof(void*), 20);
	VirEnabledSvDataSetInBuf.Alloc(sizeof(void*), 30);
	VirEnabledSvDataSetOutBuf.Alloc(sizeof(void*), 30);
	VirEnabledGoDataSetInBuf.Alloc(sizeof(void*), 40);
	VirEnabledGoDataSetOutBuf.Alloc(sizeof(void*), 40);
	NorDcSerialBoardBuf.Alloc(sizeof(void*), 20);
	NorDcAddrBoardBuf.Alloc(sizeof(void*), 20);
	VirSvFrameInSerialBuf.Alloc(sizeof(void*), 5);
	VirGoFrameInSerialBuf.Alloc(sizeof(void*), 4);
	VirGoSvStateBoardBuf.Alloc(sizeof(void*), 10);
	InstObjectRoot& root = InstObjectRoot::Instance();
	InstObjectGroupParent* groupP = root.GetGroupParent(EIOT_HalIo);
	if (groupP)
	{
		InstObjectGroup* g;
		HalBoard* Board;
		uint32 num = groupP->InstNum();
		for (uint32 i = 0; i < num; i++)
		{
			g = groupP->GetGroup(i);
			if (g->InstObjectType() != EIOT_HalIo)
			{
				LogErr.Stamp() << "IniHwIo GroupType is Err.\n";
				break;
			}
			Board = (HalBoard*)g;
			if ((Board->IoType() == Board->E_Board_YX32Pin_1))
			{
				NorDiSerialBoardBuf.Push(&Board);
				ProcInSerialBoardBuf.Push(&Board);
				NorDiAddrBoardBuf.SetAddrElement(Board->CardAddr(), Board);
			}
			else if ((Board->IoType() == Board->E_Board_DIO_YX14_1))
			{
				NorDiSerialBoardBuf.Push(&Board);
				ProcInSerialBoardBuf.Push(&Board);
				NorDiAddrBoardBuf.SetAddrElement(Board->CardAddr(), Board);
			}
			else if ((Board->IoType() == Board->E_Board_OPB_YX_1))
			{
				NorDiSerialBoardBuf.Push(&Board);
				ProcInSerialBoardBuf.Push(&Board);
				NorDiAddrBoardBuf.SetAddrElement(Board->CardAddr(), Board);
			}
			else if ((Board->IoType() == Board->E_Board_Do32Pin_1))
			{
				NorDoSerialBoardBuf.Push(&Board);
				ProcInSerialBoardBuf.Push(&Board);
				NorDoAddrBoardBuf.SetAddrElement(Board->CardAddr(), Board);
			}
			else if ((Board->IoType() == Board->E_Board_DIO_DO7_1))
			{
				NorDoSerialBoardBuf.Push(&Board);
				ProcInSerialBoardBuf.Push(&Board);
				NorDoAddrBoardBuf.SetAddrElement(Board->CardAddr(), Board);
			}
			else if ((Board->IoType() == Board->E_Vir_Board_AngIn_1))
			{
				VirSvFrameInSerialBuf.Push(&Board);
				ProcInSerialBoardBuf.Push(&Board);
				ProcOutSerialBoardBuf.Push(&Board);
			}
			else if ((Board->IoType() == Board->E_Vir_Board_SV_DataSetIn1))
			{
				int32 res = Board->ProcIni();
				if (res == 0)
				{
					VirEnabledSvDataSetInBuf.Push(&Board);
				}
			}
			else if ((Board->IoType() == Board->E_Board_Dc32Pin_1))
			{
				NorDcSerialBoardBuf.Push(&Board);
				NorDcAddrBoardBuf.SetAddrElement(Board->CardAddr(), Board);
			}
			else if ((Board->IoType() == Board->E_Vir_Board_SV_DataSetOut1))
			{
				int32 res = Board->ProcIni();
				if (res == 0)
				{
					VirEnabledSvDataSetOutBuf.Push(&Board);
					ProcOutSerialBoardBuf.Push(&Board);
				}
			}
			else if ((Board->IoType() == Board->E_Vir_BoardCMM_SV_DataSetOut1))
			{
				int32 res = Board->ProcIni();
				if (res == 0)
				{
					VirEnabledSvDataSetOutBuf.Push(&Board);
					ProcOutSerialBoardBuf.Push(&Board);
				}
			}
			else if ((Board->IoType() == Board->E_Vir_Board_GoOut_1))
			{
				int32 res = Board->ProcIni();
				if (res == 0)
				{
					VirEnabledGoDataSetOutBuf.Push(&Board);
					ProcOutSerialBoardBuf.Push(&Board);
				}
			}
			else if ((Board->IoType() == Board->E_Vir_Board_GoIn_1))
			{
				int32 res = Board->ProcIni();
				if (res == 0)
				{
					VirEnabledGoDataSetInBuf.Push(&Board);
				}
			}
			else if ((Board->IoType() == Board->E_Vir_Board_FrameGoIn_1))
			{
				VirGoFrameInSerialBuf.Push(&Board);
			}
			else if ((Board->IoType() == Board->E_Vir_Board_FrameGoOut_1))
			{

			}
			else if ((Board->IoType() == Board->E_Board_GoSv_1))
			{
				VirGoSvStateBoardBuf.SetAddrElement(Board->FrameIndex(), Board);
			}
		}
	}
	SendGoSvSelFrame();
	SptIoProcess::Instance().CfgSendOver(1);
	isPowerUpOver = 1;
}

void spt::SptGzkMuIoProcess::RecvNorIoMsg(void* Buf, uint16 Len)
{
	if (!isPowerUpOver)
	{
		return;
	}
	if (Len < 16)
	{
		return;
	}
	Len -= 2;
	uint8 frameLen = 0;
	uint8* uPtr = (uint8*)Buf;
	uint16 cnt = 0;
	MemCpy(&cnt, uPtr, sizeof(cnt));
	uPtr += sizeof(cnt);
	if (cnt != (DioMsgCnt))
	{
		//	LogErr.Stamp() << "HalIoProcess::RecvDioMsg Cnt jump <<" << DioMsgCnt << "!=" << cnt << "\n";
	}
	DioMsgCnt = cnt + 1;
	SalStdUtcStamp utc;
	MemCpy(&utc, uPtr, sizeof(utc));
	SalDateStamp stmp;
#ifdef WIN32_SIM
	uint64 us = utc.uSec;
	us = (us << 32) | utc.u_Fra_Q;
	stmp.Set(us);
	stmp.q.q = 0;
#else
	stmp.fromPriUtcCode(utc.uSec, utc.u_Fra_Q);
#endif // WIN32_SIM
	uPtr += sizeof(utc);
	uint16 bdstate;
	MemCpy(&bdstate, uPtr, sizeof(bdstate));
	boardOnLineState = bdstate;
	uPtr += sizeof(bdstate);
	uint16 inNum;
	MemCpy(&inNum, uPtr, sizeof(inNum));
	uPtr += sizeof(inNum);
	uint16 Type;
	uint8 Addr;
	bool8 log = 0;
	uint16 ctxLen = Len - (uPtr - (uint8*)Buf);
	uint16 dealLen = 0;
	while (dealLen < ctxLen)
	{
		if (uPtr[dealLen + 0] != 0x5d)
		{
			dealLen++;
			if (!log)
			{
				log = 1;
				LogErr.Stamp() << "HalIoProcess::RecvMsg Frame Header is err\n";
			}
			continue;
		}
		frameLen = uPtr[dealLen + 1];
		if (!IsRecvBoardFrameMsgOk(&uPtr[dealLen + 0], frameLen))
		{
			if (!log)
			{
				log = 1;
				LogErr.Stamp() << "HalIoProcess::RecvMsg Frame sum is err\n";
			}
			boardFrameSumErr++;
			dealLen++;
			continue;
		}
		Type = (uPtr[dealLen + 2] & 0xf0) >> 4;
		Addr = uPtr[dealLen + 2] & 0x0f;
		HalBoard* hb = 0;
		switch (Type)
		{
		case E_Board_DIO_1:
		{
			hb = (HalBoard*)NorDiAddrBoardBuf.GetAddrElement(Addr);
			if (hb)
			{
				SptNormalStateInBoard* Board = (SptNormalStateInBoard*)hb;
				if (Board->CmmType() != E_Board_DIO_1)
				{
					if (Board->OutStatus().recvFrameErrCnt == 0)
					{
						LogErr.Stamp() << "DIO板卡通信类型异常，Addr Is " << Board->CardAddr() << " Cmm type is " << E_Board_DIO_1 << "Board type is " << Board->CmmType() << "\n";
					}
					Board->OutStatus().recvFrameErrCnt++;
					break;
				}
				Board->RecvMsg(stmp, (GzkBoardCmmIoNorDIFrame*)&uPtr[dealLen]);
			}
			else
			{
				LogErr.Stamp() << "PowerUpOver " << isPowerUpOver << "RecvNorIoMsg err1\n" << Addr << "\n";
			}
			hb = (HalBoard*)NorDoAddrBoardBuf.GetAddrElement(Addr);
			if (hb)
			{
				SptNormalStateOutBoard* b = (SptNormalStateOutBoard*)hb;
				if (b->CmmType() != E_Board_DIO_1)
				{
					if (b->OutStatus().recvFrameErrCnt == 0)
					{
						LogErr.Stamp() << "DIO板卡通信类型异常，Addr Is " << b->CardAddr() << " Cmm type is " << E_Board_DIO_1 << "Board type is " << b->CmmType() << "\n";
					}
					b->OutStatus().recvFrameErrCnt++;
					break;
				}
				b->RecvMsg(stmp, (GzkBoardCmmIoNorDIFrame*)&uPtr[dealLen]);
			}
			else
			{
				LogErr.Stamp() << "PowerUpOver " << isPowerUpOver << "RecvNorIoMsg err2\n";
			}
			break;
		}
		case E_Board_OPB_YX_1:
		case E_Board_YX_1:
		{
			hb = (HalBoard*)NorDiAddrBoardBuf.GetAddrElement(Addr);
			if (hb)
			{
				SptNormalStateInBoard* Board;
				Board = (SptNormalStateInBoard*)hb;
				if (Board->CmmType() == E_Board_YX_1)
				{
					Board->RecvMsg(stmp, (GzkBoardCmmIoNorDIFrame*)&uPtr[dealLen]);
					break;
				}
				else if (Board->CmmType() == E_Board_OPB_YX_1)
				{
					Board->RecvMsg(stmp, (GzkBoardCmmIoNorDIFrame*)&uPtr[dealLen]);
					break;
				}
				else
				{
					if (Board->OutStatus().recvFrameErrCnt == 0)
					{
						LogErr.Stamp() << "DIO板卡通信类型异常，Addr Is " << Board->CardAddr() << " Cmm type is " << E_Board_YX_1 << "Board type is " << Board->CmmType() << "\n";
					}
					Board->OutStatus().recvFrameErrCnt++;
				}
			}
			else
			{
				LogErr.Stamp() << "PowerUpOver " << isPowerUpOver << " RecvNorIoMsg err3\n";
			}
			break;
		}
		case E_Board_Do_1:
		{
			hb = (SptNormalStateOutBoard*)(HalBoard*)NorDoAddrBoardBuf.GetAddrElement(Addr);
			if (hb)
			{
				SptNormalStateOutBoard* Board = (SptNormalStateOutBoard*)hb;
				if (Board->CmmType() != E_Board_Do_1)
				{
					if (Board->OutStatus().recvFrameErrCnt == 0)
					{
						LogErr.Stamp() << "DIO板卡通信类型异常，Addr Is " << Board->CardAddr() << " Cmm type is " << E_Board_Do_1 << "Board type is " << Board->CmmType() << "\n";
					}
					Board->OutStatus().recvFrameErrCnt++;
					break;
				}
				Board->RecvMsg(stmp, &uPtr[dealLen]);
			}
			else
			{
				LogErr.Stamp() << "PowerUpOver " << isPowerUpOver << "RecvNorIoMsg err4\n";
			}
			break;
		}
		case E_Board_Dc_1:
		{
			hb = (HalBoard*)NorDcSerialBoardBuf.GetAddrElement(Addr);
			if (hb)
			{
				SptNormalDcInBoard* Board = (SptNormalDcInBoard*)hb;
				if (Board->CmmType() != E_Board_Dc_1)
				{
					if (Board->OutStatus().recvFrameErrCnt == 0)
					{
						LogErr.Stamp() << "DIO板卡通信类型异常，Addr Is " << Board->CardAddr() << " Cmm type is " << E_Board_Dc_1 << "Board type is " << Board->CmmType() << "\n";
					}
					Board->OutStatus().recvFrameErrCnt++;
					break;
				}
				Board->RecvMsg(stmp, &uPtr[dealLen]);
			}
			else
			{
				LogErr.Stamp() << "PowerUpOver " << isPowerUpOver << "RecvNorIoMsg err5\n";
			}
			break;
		}
		default:
			break;
		}
		dealLen += 2 + frameLen;
	}
}

void spt::SptGzkMuIoProcess::RecvAngFrameMsg(void* Buf, uint16 Len)
{
	HalBoard* hb = (HalBoard*)VirSvFrameInSerialBuf.GetAddrElement(0);
	SptAngVirInputBoard* Baord = (SptAngVirInputBoard*)hb;
	if (hb)
	{
		Baord->RecMsg(Buf, Len);
	}
}

void spt::SptGzkMuIoProcess::RecSvInCbCheckStateMsg(void* Buf, uint32 BufLen)
{
	HalBoard* hb = (HalBoard*)VirSvFrameInSerialBuf.GetAddrElement(0);
	SptAngVirInputBoard* Baord = (SptAngVirInputBoard*)hb;
	if (hb)
	{
		Baord->RecSvInCbCheckStateMsg(Buf, BufLen);
	}
}

void spt::SptGzkMuIoProcess::RecGoInCbCheckStateMsg(void* Buf, uint32 BufLen)
{
	HalBoard* hb = (HalBoard*)VirGoFrameInSerialBuf.GetAddrElement(0);
	SptGooseFrameIn* Baord = (SptGooseFrameIn*)hb;
	if (hb)
	{
		Baord->RecGoInCbCheckStateMsg(Buf, BufLen);
	}
}

void spt::SptGzkMuIoProcess::RecBoardInfoMsg(void* Buf, uint32 BufLen)
{
	uint32 reader = 0;
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b + reader);
	reader += sizeof(frameno);
	uint16 BoardNo = GetLittleEndian16Bit(b + reader);
	reader += sizeof(BoardNo);
	HalBoard* hb = (HalBoard*)VirGoSvStateBoardBuf.GetAddrElement(BoardNo);
	SptGoSvStateBoard* Board = (SptGoSvStateBoard*)hb;
	if (hb)
	{
		Board->RecBoardState(b, BufLen);
	}
}

void spt::SptGzkMuIoProcess::RecLightInfoMsg(void* Buf, uint32 BufLen)
{
	uint32 reader = 0;
	uint8* b = (uint8*)Buf;
	uint16 frameno = GetLittleEndian16Bit(b + reader);
	reader += sizeof(frameno);
	uint16 BoardNo = GetLittleEndian16Bit(b + reader);
	reader += sizeof(BoardNo);
	HalBoard* hb = (HalBoard*)VirGoSvStateBoardBuf.GetAddrElement(BoardNo);
	SptGoSvStateBoard* Board = (SptGoSvStateBoard*)hb;
	if (hb)
	{
		Board->RecNetState(b, BufLen);
	}
}

void spt::SptGzkMuIoProcess::RecBoardMsg(void* Buf, uint32 BufLen)
{
	SalCmmMsgHeader* header = (SalCmmMsgHeader*)Buf;
	if (header->type == SCT_AppFastCmm)
	{
		SptAppFastCmm* inst = (SptAppFastCmm*)&ApiAppFastCmm::Instance();
		inst->RecvFromHal(BufLen, Buf);
	}
	else if (header->type == SCT_AppSlowCmm)
	{
		SptAppCmmTask::Instance().RecvFromHal(BufLen, Buf);
	}
}

void spt::SptGzkMuIoProcess::RecFpgaSlowMsg(void* Buf, uint32 BufLen)
{
	if (BufLen <= sizeof(fpgaSlowFlags))
	{
		MemCpy(fpgaSlowFlags, Buf, sizeof(fpgaSlowFlags));
	}
}

void spt::SptGzkMuIoProcess::RecvGoPosFrameMsg(void* Buf, uint16 Len)
{
	HalBoard* hb = (HalBoard*)VirGoFrameInSerialBuf.GetAddrElement(0);
	SptGooseFrameIn* Baord = (SptGooseFrameIn*)hb;
	if (hb)
	{
		Baord->RecPosMsg(Buf, Len);
	}
}

void spt::SptGzkMuIoProcess::RecvGoAngFrameMsg(void* Buf, uint16 Len)
{
	HalBoard* hb = (HalBoard*)VirGoFrameInSerialBuf.GetAddrElement(0);
	SptGooseFrameIn* Baord = (SptGooseFrameIn*)hb;
	if (hb)
	{
		Baord->RecAngMsg(Buf, Len);
	}
}

void spt::SptGzkMuIoProcess::ProcIn()
{
	if (!isPowerUpOver)
	{
		return;
	}
	HalBoard* Board;
	uint32 len = ProcInSerialBoardBuf.Top();
	for (uint32 i = 0; i < len; i++)
	{
		Board = (HalBoard*)ProcInSerialBoardBuf.GetAddrElement(i);
		if (Board)
		{
			Board->ProcIn();
		}
	}
}

void spt::SptGzkMuIoProcess::ProcOut()
{
	if (!isPowerUpOver)
	{
		return;
	}
	HalBoard* Board;
	uint32 len = NorDoSerialBoardBuf.Top();
	for (uint32 i = 0; i < len; i++)
	{
		Board = (HalBoard*)NorDoSerialBoardBuf.GetAddrElement(i);
		SptNormalStateOutBoard* b = (SptNormalStateOutBoard*)Board;
		b->ProcOut();
		SetNorDo(Board->FrameIndex(), b->GetValue(0));
	}
	SendNorDoFrame();
	len = ProcOutSerialBoardBuf.Top();
	for (uint32 i = 0; i < len; i++)
	{
		Board = (HalBoard*)ProcOutSerialBoardBuf.GetAddrElement(i);
		//	Board->OutStatus().runInfo.RunStart();
		Board->ProcOut();
		//	Board->OutStatus().runInfo.RunEnd();
	}
	SendCtrlFrame();
}

void spt::SptGzkMuIoProcess::EnableSVSend(bool8 Enable)
{
	updateCtrlFlags = 1;
	if (Enable)
	{
		usedCtrlFlags.svSendEnable = 0xaaaa;
	}
	else
	{
		usedCtrlFlags.svSendEnable = 0x5555;
	}
}

void spt::SptGzkMuIoProcess::EnableAngErrPointDeal(bool8 Enable)
{
	updateCtrlFlags = 1;
	if (Enable)
	{
		usedCtrlFlags.angErrPointDeal = 0xaa;
	}
	else
	{
		usedCtrlFlags.angErrPointDeal = 0x55;
	}
}

void spt::SptGzkMuIoProcess::EnableGoSend(bool8 Enable)
{
	updateCtrlFlags = 1;
	if (Enable)
	{
		usedCtrlFlags.goSendEnable = 0xaaaa;
	}
	else
	{
		usedCtrlFlags.goSendEnable = 0x5555;
	}
}

void spt::SptGzkMuIoProcess::CfgSendOver(bool8 Enable)
{
	updateCtrlFlags = 1;
	if (Enable)
	{
		usedCtrlFlags.cfgSendOver = 0xaaaa;
	}
	else
	{
		usedCtrlFlags.cfgSendOver = 0x5555;
	}
}

uint8 spt::SptGzkMuIoProcess::GetFpagSlowFlags(uint16 Index)
{
	if (Index < sizeof(fpgaSlowFlags))
	{
		return fpgaSlowFlags[Index];
	}
	return 0;
}

void spt::SptGzkMuIoProcess::ResetSubBoardState()
{
	SlowCmdCnt = 0;
	slowCmdstep = SptIedIoProcess::E_DICfgCmd;
}

void spt::SptGzkMuIoProcess::SendGoSvSelFrame()
{
	uint32 num = VirSvFrameInSerialBuf.Top();
	for (uint32 i = 0; i < num; i++)
	{
		HalBoard* b = (HalBoard*)VirSvFrameInSerialBuf.GetAddrElement(i);
		b->ProcIni();
	}
	num = VirGoFrameInSerialBuf.Top();
	for (uint32 i = 0; i < num; i++)
	{
		HalBoard* b = (HalBoard*)VirGoFrameInSerialBuf.GetAddrElement(i);
		b->ProcIni();
	}
}

void spt::SptGzkMuIoProcess::SetNorDo(uint32 Index, uint32 Do)
{
	if (Index < 6)
	{
		uint8* dst = &editDoFrame.board0L;
		uint8* sur = (uint8*)&Do;
		dst[Index * 2 + 0] = *sur++;
		dst[Index * 2 + 1] = *sur;
	}
}

void spt::SptGzkMuIoProcess::SendNorDoFrame()
{
	if (SptMain::Instance().IsHardWare(EH_GZKSAU))
	{
		if (SptMain::Instance().IsDevice(ED_SAU31))
		{
			rtDoFrame.type_addr = (E_Board_Do_1 << 4) | 0x00;
		}
		else
		{
			rtDoFrame.type_addr = (E_Board_Do_1 << 4) | 0x01;
		}
	}
	else
	{
		return;
	}
	uint8* dst = &rtDoFrame.board0L;
	uint8* sur = &editDoFrame.board0L;
	bool8 ch = 0;
	for (uint32 i = 0; i < 12; i++)
	{
		if (dst[i] != sur[i])
		{
			dst[i] = sur[i];
			ch = 1;
		}
	}
	rtDoFrame.frm_header = 0x5d;
	rtDoFrame.frm_len = (uint8)(&rtDoFrame.frm_sumL - &rtDoFrame.frm_header);

	if (rtDoFrame.start != editDoFrame.start)
	{
		rtDoFrame.start = editDoFrame.start;
		ch = 1;
	}
	if (ch == 1)
	{
		rtDoFrame.frm_st++;
		rtDoFrame.frm_sq = 0;
	}
	else
	{
		rtDoFrame.frm_sq++;
	}
	SendSlowCmd();
	rtDoFrame.crc = Crc8MAXIM.CalCrc(&rtDoFrame.frm_header, &rtDoFrame.crc - &rtDoFrame.frm_header);
	uint16 sum = 0;
	sum = SumCheck::CalcSum16(&rtDoFrame.frm_header, rtDoFrame.frm_len);
	rtDoFrame.frm_sumL = (uint8)(sum);
	rtDoFrame.frm_sumH = (uint8)(sum >> 8);
	SptSendSerialData(E_HSPN_DO_CMM, &rtDoFrame, sizeof(rtDoFrame));
}

void spt::SptGzkMuIoProcess::SendSlowCmd()
{
	switch (slowCmdstep)
	{
	case spt::SptIedIoProcess::E_POWERUPINI:
	{
		slowCmdstep = SptIedIoProcess::E_DICfgCmd;
		break;
	}
	case spt::SptIedIoProcess::E_DICfgCmd:
		if (lastSendIndex < NorDiSerialBoardBuf.Top())
		{
			uint32 loopend = NorDiSerialBoardBuf.Top();
			HalBoard* board;
			for (uint32 i = lastSendIndex; i < loopend; i++)
			{
				board = (HalBoard*)NorDiSerialBoardBuf.GetAddrElement(i);
				lastSendIndex++;
				if (board)
				{
					rtDoFrame.frm_status_type = SptIedIoProcess::E_DOWN_BOARD_OFFSET_SET;
					rtDoFrame.frm_status1 = (uint8)(board->CmmType() << 4) | (board->CardAddr() & 0x0f);
					rtDoFrame.frm_status2 = (uint8)(board->FrameIndex());
					SlowCmdCnt++;
					break;
				}
			}
		}
		else
		{
			lastSendIndex = 0;
			slowCmdstep = SptIedIoProcess::E_DOCfgCmd;
		}
		break;
	case spt::SptIedIoProcess::E_DOCfgCmd:
		if (lastSendIndex < NorDoSerialBoardBuf.Top())
		{
			uint32 loopend = NorDoSerialBoardBuf.Top();
			HalBoard* board;
			for (uint32 i = lastSendIndex; i < loopend; i++)
			{
				board = (HalBoard*)NorDoSerialBoardBuf.GetAddrElement(i);
				lastSendIndex++;
				if (board)
				{
					rtDoFrame.frm_status_type = SptIedIoProcess::E_DOWN_BOARD_OFFSET_SET;
					rtDoFrame.frm_status1 = (uint8)(board->CmmType() << 4) | (board->CardAddr() & 0x0f);
					rtDoFrame.frm_status2 = (uint8)(board->FrameIndex());
					SlowCmdCnt++;
					break;
				}
			}
		}
		else
		{
			lastSendIndex = 0;
			slowCmdstep = SptIedIoProcess::E_DCCfgCmd;
		}
		break;
	case spt::SptIedIoProcess::E_DCCfgCmd:
		if (lastSendIndex < NorDcSerialBoardBuf.Top())
		{
			uint32 loopend = NorDcSerialBoardBuf.Top();
			HalBoard* board;
			for (uint32 i = lastSendIndex; i < loopend; i++)
			{
				board = (HalBoard*)NorDcSerialBoardBuf.GetAddrElement(i);
				lastSendIndex++;
				if (board)
				{
					rtDoFrame.frm_status_type = SptIedIoProcess::E_DOWN_BOARD_OFFSET_SET;
					rtDoFrame.frm_status1 = (uint8)(board->CmmType() << 4) | (board->CardAddr() & 0x0f);
					rtDoFrame.frm_status2 = (uint8)(board->FrameIndex());
					SlowCmdCnt++;
					break;
				}
			}
		}
		else
		{
			lastSendIndex = 0;
			if (SlowCmdCnt > 10000)
			{
				slowCmdstep = SptIedIoProcess::E_WORK;
			}
			else
			{
				slowCmdstep = SptIedIoProcess::E_DICfgCmd;
			}
		}
		break;
	case spt::SptIedIoProcess::E_WORK:
		rtDoFrame.frm_status_type = 0;
		rtDoFrame.frm_status1 = 0;
		rtDoFrame.frm_status2 = 0;
		if (SptIoProcess::Instance().AppFlags().blUnitRevert)
		{
			ApiIoGlobalFlag::Instance().ResetSubBoardState();
		}
		break;
	default:
		break;
	}

}

void spt::SptGzkMuIoProcess::SendCtrlFrame()
{
	if (SptIoProcess::Instance().AppFlags().unitTestState)
	{
		rtCrtlFlags.IedTest = 0xaaaa;
	}
	else
	{
		rtCrtlFlags.IedTest = 0x5555;
	}
	if (rtCrtlFlags.IedTest != usedCtrlFlags.IedTest)
	{
		usedCtrlFlags.IedTest = rtCrtlFlags.IedTest;
		updateCtrlFlags = 1;
	}
	if (updateCtrlFlags)
	{
		updateCtrlFlags = 0;
		usedCtrlFlags.frameNo++;
		CpuFpgaCmmMsgBuf msg;
		msg.Write(&usedCtrlFlags, sizeof(usedCtrlFlags));
		msg.IntSend(0, FpgaMsgProc::E_CPU_FPGA_CfgCtrl);
	}
}



