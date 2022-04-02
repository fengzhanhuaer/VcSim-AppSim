#include "SptProject.h"
using namespace spt;
void spt::SalCmmMsgBufCtrl::PowerUpIni(uint32 BufSize)
{
	if (BufSize > (sizeof(SalCmmTemplateHeader) + 2))
	{
		buf = (SalCmmTemplateHeader*)Calloc(1, BufSize);
	}
	else
	{
		buf = 0;
	}

	bufSize = BufSize;
	isCheckOk = 0;
	isUsed = 0;
	if (buf)
	{
		isFree = 1;
	}
	else
	{
		isFree = 0;
		bufSize = 0;
	}
	state = 0;
	pool = 0;
	ctxLen = 0;
}

void spt::SalCmmMsgBufCtrl::FreeBuf()
{
	if (pool)
	{
		pool->FreeBuf(this);
	}
	else
	{
		state = E_SCS_Inied;
	}
}

void spt::SalCmmMsgBufCtrl::SetFlag(uint32 Flag)
{
	state |= Flag;
}

void spt::SalCmmMsgBufCtrl::UnSetFlag(uint32 Flag)
{
	state &= ~Flag;
}

void spt::SalCmmMsgBufCtrl::SetWrited()
{
	SetFlag(E_SCS_Writing | E_SCS_Writed);
}

void spt::SalCmmMsgBufCtrl::SetReaded()
{
	SetFlag(E_SCS_Reading | E_SCS_Readed);
}

uint16 spt::SalCmmMsgBufCtrl::CalcCrc()
{
	uint16 sum = 0;

	sum = Crc16ModBus.CalCrc(buf, buf->header.len);

	return sum;
}

uint16 spt::SalCmmMsgBufCtrl::AddCrc()
{
	return  Crc16ModBus.AddCrc(buf, buf->header.len + 2);
}

uint16 spt::SalCmmMsgBufCtrl::IsCrcOk()
{
	return Crc16ModBus.IsCrcOk(buf, buf->header.len + 2);
}

void spt::SalCmmMsgCtrlPool::PowerUpIni(uint32 BufNum, uint32 BufSize)
{
	usedNum = reader = writer = 0;
	if (BufNum)
	{
		Ctrl = (SalCmmMsgBufCtrl*)Calloc(BufNum, sizeof(SalCmmMsgBufCtrl));
		if (!Ctrl)
		{
			bufNum = 0;
			return;
		}
		bufNum = BufNum;
		for (uint32 i = 0; i < BufNum; i++)
		{
			Ctrl[i].PowerUpIni(BufSize);
			Ctrl[i].pool = this;
		}
	}
	else
	{
		Ctrl = 0;
	}
}

SalCmmMsgBufCtrl* spt::SalCmmMsgCtrlPool::GetNextWriteBuf()
{
	if (reader == writer)
	{
		if (usedNum >= bufNum)
		{
			outPut.getWriteBufErrCnt++;
			return 0;
		}
	}
	uint32 w = writer % bufNum;
	uint32 r = reader % bufNum;
	if (Ctrl)
	{
		if ((Ctrl[w].state == E_SCS_Inied))
		{
			Ctrl[w].state = E_SCS_Alloced;
			usedNum++;
			writer = (w + 1) % bufNum;
			outPut.writeCnt++;
			return &Ctrl[w];
		}
		w = (w + 1) % bufNum;
		if (w != r)
		{
			if ((Ctrl[w].state == E_SCS_Inied))
			{
				Ctrl[w].state = E_SCS_Alloced;
				usedNum++;
				writer = (w + 1) % bufNum;
				outPut.writeCnt++;
				return &Ctrl[w];
			}
		}
	}
	outPut.getWriteBufErrCnt++;
	return 0;
}

SalCmmMsgBufCtrl* spt::SalCmmMsgCtrlPool::GetNextReadBuf()
{
	if (reader == writer)
	{
		return 0;
	}
	uint32 w = writer % bufNum;
	uint32 r = reader % bufNum;
	while (r != w)
	{
		if ((Ctrl[r].state == E_SCS_Inied))
		{
			return 0;
		}
		if ((Ctrl[r].state & E_SCS_Writed) && (!(Ctrl[r].state & E_SCS_Readed)))
		{
			Ctrl[r].state |= E_SCS_Reading;
			return &Ctrl[r];
		}
		r = (r + 1) % bufNum;
	}
	return 0;
}

void spt::SalCmmMsgCtrlPool::UpdateReader()
{
	if (!Ctrl)
	{
		return;
	}
	uint32 w = writer % bufNum;
	uint32 r = reader % bufNum;
	do
	{
		if (Ctrl[r].state == E_SCS_Inied)
		{
			if (usedNum)
			{
				usedNum--;
			}
			if (r == w)
			{
				break;
			}
			r = (r + 1) % bufNum;
		}
		else if (Ctrl[r].state & E_SCS_Readed)
		{
			Ctrl[r].state = E_SCS_Inied;
			if (usedNum)
			{
				usedNum--;
			}
			r = (r + 1) % bufNum;
			outPut.readCnt++;
		}
		else
		{
			break;
		}
	} while (r != w);
	reader = r;
}

void spt::SalCmmMsgCtrlPool::FreeBuf(SalCmmMsgBufCtrl* Ctrl)
{
	if (Ctrl)
	{
		if (usedNum)
		{
			usedNum--;
		}
		Ctrl->state = E_SCS_Inied;
	}
}

void spt::SalCmmMsgCtrlPool::FreeAllBuf()
{
	for (uint32 i = 0; i < bufNum; i++)
	{
		Ctrl[i].FreeBuf();
	}
	reader = writer = usedNum = 0;
}

uint16 spt::SalCmmMsgHeader::CalcCrc()
{
	uint16 sum = 0;

	sum = Crc16ModBus.CalCrc(&header, len);

	return sum;
}

uint16 spt::SalCmmMsgHeader::AddCrc()
{
	return  Crc16ModBus.AddCrc(&header, len + 2);
}

uint16 spt::SalCmmMsgHeader::IsCrcOk()
{
	return Crc16ModBus.IsCrcOk(&header, len + 2);
}

spt::SalCmmChannel::SalCmmChannel()
{
	StrNCpy(name, "Channel", sizeof(name));
}
void spt::SalTransCmm::PowerUpIni(uint32 AppSendBufLen, uint32 AppSendBufNum, uint32 AppRecvBufLen, uint32 AppRecvBufNum, uint32 HalSendBufLen, uint32 HalRecvBufLen)
{
	frameBufLen = HalSendBufLen;
	appSendMsgPool.PowerUpIni(AppSendBufNum, AppSendBufLen);
	appRecMsgPool.PowerUpIni(AppRecvBufNum, AppRecvBufLen);
	halSendPool.Alloc(HalSendBufLen, 1);
	halRecvPool.Alloc(HalRecvBufLen, 1);
}

int32 spt::SalTransCmm::SendMsg(uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	return SendMsgTo(frmHeader.dst, UnPackIndex, Type, DataLen, Data);
}

int32 spt::SalTransCmm::SendMsgTo(uint16 Dst, uint32 UnPackIndex, uint16 Type, uint16 DataLen, void* Data)
{
	return -1;
}

spt::SalTransCmm::SalTransCmm()
{
	frmHeader.header = 0x5a55;
	StrNCpy(name, "SalTransCmm", sizeof(name));
}

spt::SalTransProtocol::SalTransProtocol(AdtBufDes& recMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver)
	:recMsg(recMsg)
{
	logStep = 0;
	infoFunc = 0;
	result = E_RecvErr;
	cmm = (SalTransCmm*)Cmm;
	dst = Dst;
	driver = Driver;
}
int32 spt::SalTransProtocol::Recv(CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	if (Header->len < recMsg.bufLen)
	{
		MemCpy(recMsg.buf, Header, Header->len);
		recOk = 1;
	}
	return 0;
}
int32 spt::SalTransProtocol::SendMsg(uint16 DataLen, void* Data)
{
	driver->SendMsgCnt++;
	return cmm->SendMsgTo(dst, driver->Index, driver->Type, DataLen, Data);
}
int32 spt::SalTransProtocol::WaitMsg(uint32 Type, int32 Ms)
{
	MsTimer timer;
	timer.UpCnt(Ms);
	timer.Enable(1);
	while (!timer.Status())
	{
		if (recOk)
		{
			SalTransFrame* frame = (SalTransFrame*)recMsg.buf;
			CharStreamReader buf(frame->data, frame->Header.dataLen);
			uint32 u32 = 0;
			buf.Read(u32);
			if (u32 == Type)
			{
				recOk = 0;
				return 0;
			}
		}
		MsSleep(1);
	}
	recOk = 0;
	return E_RecvOverTime;
}
int32 spt::SalTransProtocol::WaitMsgOk(uint32 Type, int32 Ms)
{
	int32 res = WaitMsg(Type, Ms);
	if (res == 0)
	{
		SalTransFrame* frame = (SalTransFrame*)recMsg.buf;
		CharStreamReader buf(frame->data, frame->Header.dataLen);
		uint32 u32 = 0;
		buf.Read(u32);
		buf.Read(u32);
		return u32;
	}
	return res;
}
int32 spt::SalTransProtocol::WaitMsgOk(uint32 Type, int32*& Info, int32 Ms)
{
	Info = 0;
	int32 res = WaitMsg(Type, Ms);
	if (res == 0)
	{
		SalTransFrame* frame = (SalTransFrame*)recMsg.buf;
		CharStreamReader buf(frame->data, frame->Header.dataLen);
		uint32 u32 = 0;
		buf.Read(u32);
		buf.Read(u32);
		Info = (int32*)buf.Top();
		return u32;
	}
	return res;
}

void spt::SalTransProtocol::LogInfo(SalString& Info, bool8 toPrc, bool8 toPrt)
{
	if (infoFunc && toPrc)
	{
		infoFunc(logStep, Info.Str());
	}
	if (toPrt)
	{
		LogMsg.Stamp() << Info << "\n";
	}
}

spt::SalFileTrans::SalFileTrans(AdtBufDes& recMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver)
	:SalTransProtocol(recMsg, Cmm, Dst, Driver)
{
	result = E_RecvErr;
	surFile = "";
	dstFile = "";
}

int32 spt::SalFileTrans::Recv(CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	if (Header->len < recMsg.bufLen)
	{
		SalTransFrame* frame = (SalTransFrame*)Header;
		if (frame->Header.type != E_FileTrans)
		{
			return -1;
		}
		CharStreamReader buf(frame->data, frame->Header.dataLen);
		uint32 u32 = 0;
		buf.Read(u32);
		if (u32 == E_SendStart)
		{
			fileSize = 0;
			buf.Read(fileSize);

			uint32 framMaxLen = cmm->FrameBufLen() - 40;
			if (framMaxLen > recMsg.bufLen)
			{
				framMaxLen = recMsg.bufLen - 40;
			}
			buf.Read(u32);
			if (framMaxLen > u32)
			{
				framMaxLen = u32;
			}

			uint32 fileLen = 0;
			buf.Read(fileLen);
			process = E_SendStartAck;
			if (fileLen == (uint32)StrLen((char*)buf.Top()))
			{
				dstFile = (char*)buf.Top();
			}
			else
			{
				SCharStream2kb sendbuf;
				uint32 u32 = process;
				sendbuf.Write(&u32, sizeof(u32));
				result = u32 = -1;
				sendbuf.Write(&u32, sizeof(u32));
				SendMsg(sendbuf.Top(), sendbuf.BufBase());
				return -1;
			}
			LogMsg.Stamp() << "file trans" << dstFile << "\n";
			SCharStream2kb sendbuf;
			uint32 u32 = process;
			sendbuf.Write(&u32, sizeof(u32));
			result = u32 = 0;
			sendbuf.Write(&u32, sizeof(u32));
			u32 = framMaxLen;
			sendbuf.Write(&u32, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else if (u32 == E_Trans)
		{
			uint32 offset;
			buf.Read(offset);
			uint32 len;
			buf.Read(len);
			SalFile file;
			file.SetFullName(dstFile.Str());
			file.Path().ToLocal();
			uint32 size = file.Size();
			SCharStream2kb sendbuf;
			process = E_TransAck;
			uint32 u32 = process;
			sendbuf.Write(&u32, sizeof(u32));
			if (offset == 0)
			{
				file.Creat();
				file.Write(buf.Top(), len);
				result = u32 = 0;
				sendbuf.Write(&u32, sizeof(u32));
			}
			else if (offset == size)
			{
				file.OpenAppend();
				file.Write(buf.Top(), len);
				result = u32 = 0;
				sendbuf.Write(&u32, sizeof(u32));
			}
			else if (offset < size)
			{
				file.OpenRw();
				file.Seek(file.E_SET, offset);
				file.Write(buf.Top(), len);
				result = u32 = 0;
				sendbuf.Write(&u32, sizeof(u32));
			}
			else
			{
				LogMsg.Stamp() << "file write err\n";
				result = u32 = -1;
				sendbuf.Write(&u32, sizeof(u32));
			}
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else if (u32 == E_TransErr)
		{
			uint32 offset;
			buf.Read(offset);
			uint32 len;
			buf.Read(len);
			SalFile file;
			file.SetFullName(dstFile.Str());
			file.Path().ToLocal();
			file.Delete();
			SCharStream2kb sendbuf;
			process = E_TransErrAck;
			uint32 u32 = process;
			sendbuf.Write(&u32, sizeof(u32));
			result = u32 = 0;
			sendbuf.Write(&u32, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else if (u32 == E_Check)
		{
			SalFile file;
			file.SetFullName(dstFile.Str());
			file.Path().ToLocal();
			file.OpenReadOnly();
			uint32 fcrc = file.GetCrc();
			uint32 crc;
			buf.Read(crc);
			SCharStream2kb sendbuf;
			process = E_CheckAck;
			uint32 u32 = process;
			sendbuf.Write(&u32, sizeof(u32));
			result = u32 = -1;
			if (fcrc == crc)
			{
				result = u32 = 0;
			}
			sendbuf.Write(&u32, sizeof(u32));
			sendbuf.Write(&fcrc, sizeof(fcrc));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else
		{
			SalTransProtocol::Recv(Driver, Header);
		}
	}
	return 0;
}

int32 spt::SalFileTrans::Send(int32(*Process)(int32 Step, const char* info), const char* SurFile, const char* DstFile)
{
	surFile = SurFile;
	dstFile = DstFile;
	logStep = 0;
	infoFunc = Process;
	String100B info;
	result = E_SendErr;
	process = E_Begin;
	SalFile file;
	file.SetFullName(surFile.Str());
	file.Path().ToLocal();
	if (!file.IsExist())
	{
		info = file.Name().Name();
		info << "文件不存在,按任意键继续";
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_NoExist;
		return result;
	}
	process = E_SendStart;
	SCharStream5kb sendbuf;
	uint32 u32 = E_SendStart;
	sendbuf.Write(&u32, sizeof(u32));
	fileSize = u32 = (uint32)file.Size();
	if (u32 > 128 * 1024 * 1024)
	{
		info = file.Name().Name();
		info << "文件过大,按任意键继续";
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_TooLarge;
		return result;
	}
	sendbuf.Write(&u32, sizeof(u32));
	uint32 framMaxLen = cmm->FrameBufLen() - 40;
	if (framMaxLen > recMsg.bufLen)
	{
		framMaxLen = recMsg.bufLen - 40;
	}
	u32 = framMaxLen;
	sendbuf.Write(&u32, sizeof(u32));
	u32 = dstFile.StrLen();
	sendbuf.Write(&u32, sizeof(u32));
	sendbuf.Write(dstFile.Str(), dstFile.StrLen() + 1);
	SendMsg(sendbuf.Top(), sendbuf.BufBase());
	sendbuf.Clear();
	info = file.Name().Name();
	info << "开始下发";
	LogInfo(info, 1, 1);
	logStep++;
	int32* pinfo = 0;
	if (WaitMsgOk(E_SendStartAck, pinfo, 500) != 0)
	{
		info = file.Name().Name();
		info << "文件信息确认超时,按任意键继续";
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_SendErr;
		return result;
	}
	if (pinfo)
	{
		if (framMaxLen > (uint32)pinfo[0])
		{
			framMaxLen = pinfo[0];
		}
	}
	file.OpenReadOnly();
	uint32 TransLen = 0;
	uint32 serial = 0;
	uint32 rtranCnt = 0;
	uint32 fileRtrans = 0;
	info = "文件发送中";
	uint32 lastPercent = ((TransLen * 100 / fileSize));
	info << lastPercent << "%";
	LogInfo(info, 1, 0);
	while (TransLen < fileSize)
	{
		sendbuf.Clear();
		u32 = E_Trans;
		sendbuf.Write(&u32, sizeof(u32));
		sendbuf.Write(&TransLen, sizeof(TransLen));
		uint32 len = fileSize - TransLen;
		if (len > framMaxLen)
		{
			len = framMaxLen;
		}
		sendbuf.Write(&len, sizeof(len));
		char buf[2048];
		file.Seek(file.E_SET, TransLen);
		int32 rl = file.Read(buf, len);
		if (rl == (int32)len)
		{
			//文件重传
			sendbuf.Write(buf, len);
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
			int32 res = WaitMsgOk(E_TransAck, 500);
			if (res == -1)
			{
				TransLen = 0;
				serial = 0;
				fileRtrans++;
				if (fileRtrans > 3)
				{
					logStep++;
					info = "文件发送异常,按任意键继续";
					result = E_SendErr;
					LogInfo(info, 1, 1);
					process = E_SendEnd;
					return result;
				}
				else
				{
					LogMsg.Stamp() << "file trans recv -1 fileRtrans" << fileRtrans << TransLen << "\n";
				}
			}
			else if (res != 0)
			{
				//帧重传
				rtranCnt++;
				if (rtranCnt > 3)
				{
					if (res == E_RecvOverTime)
					{
						logStep++;
						info = "文件发送确认消息等待超时,按任意键继续";
						result = E_RecvOverTime;
					}
					else
					{
						logStep++;
						info = "文件发送异常,按任意键继续";
						result = E_SendErr;
					}
					LogInfo(info, 1, 1);
					process = E_SendEnd;
					return result;
				}
				else
				{
					LogMsg.Stamp() << "file trans recv !=0 rtranCnt" << rtranCnt << TransLen << "\n";
				}
			}
			else
			{
				rtranCnt = 0;
				TransLen += len;
				serial++;
				uint32 tempPercent = ((TransLen * 100 / fileSize));

				if (tempPercent != lastPercent)
				{
					lastPercent = tempPercent;
					info = "文件发送中";
					info << tempPercent << "%";
					LogInfo(info, 1, 0);
				}
			}
		}
		else
		{
			sendbuf.Clear();
			u32 = E_TransErr;
			sendbuf.Write(&u32, sizeof(u32));
			u32 = 0;
			sendbuf.Write(&serial, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());

			if (WaitMsgOk(E_TransErrAck, 200) == 0)
			{
			}
			info = file.Name().Name();
			info << "文件读取异常,按任意键继续";
			LogInfo(info, 1, 1);
			process = E_SendEnd;
			result = E_ReadLenErr;
			return result;
		}
	}
	logStep++;
	info = "文件发送完成";
	LogInfo(info, 1, 1);
	logStep++;
	uint32 crc = file.GetCrc();
	sendbuf.Clear();
	u32 = E_Check;
	sendbuf.Write(&u32, sizeof(u32));
	sendbuf.Write(&crc, sizeof(crc));
	SendMsg(sendbuf.Top(), sendbuf.BufBase());
	if (WaitMsgOk(E_CheckAck, 500) == 0)
	{
		info = "文件校验成功(";
		info.FormatHex((uint16)crc) << ")";
		LogInfo(info, 1, 1);
		result = E_SendOk;
	}
	else
	{
		info = "文件校验失败(";
		info.FormatHex((uint16)crc) << "!=";
		SalTransFrame* frame = (SalTransFrame*)recMsg.buf;
		CharStreamReader buf(frame->data, frame->Header.dataLen);
		uint32 u32 = 0;
		buf.Read(u32);
		buf.Read(u32);
		buf.Read(u32);
		info.FormatHex((uint16)u32) << ")";
		LogInfo(info, 1, 1);
		result = E_CheckErr;
	}
	logStep++;
	info = "按任意键继续";
	LogInfo(info, 1, 1);
	process = E_SendEnd;
	return result;
}

spt::SalParaTrans::SalParaTrans(AdtBufDes& recMsg, AdtBufDes& editMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver)
	:SalTransProtocol(recMsg, Cmm, Dst, Driver), editMsg(editMsg)
{
	desFile = "";
}

int32 spt::SalParaTrans::Recv(CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	if (Header->len < editMsg.bufLen)
	{
		SalTransFrame* frame = (SalTransFrame*)Header;
		if (frame->Header.type != E_ParaTrans)
		{
			return -1;
		}
		CharStreamReader buf(frame->data, frame->Header.dataLen);
		uint32 u32 = 0;
		buf.Read(u32);
		if (u32 == E_SendStart)
		{
			buf.Read(zone);
			buf.Read(paraLen);
			uint32 framMaxLen = cmm->FrameBufLen() - 40;
			if (framMaxLen > recMsg.bufLen)
			{
				framMaxLen = recMsg.bufLen - 40;
			}
			buf.Read(u32);
			if (framMaxLen > u32)
			{
				framMaxLen = u32;
			}
			int32 strLen;
			buf.Read(strLen);
			desFile = (const char*)buf.Top();
			SCharStream2kb sendbuf;
			uint32 u32 = E_SendStartAck;
			sendbuf.Write(&u32, sizeof(u32));
			u32 = -1;
			if (strLen != desFile.StrLen())
			{
				paraGroup = 0;
			}
			else
			{
				InstObjectGroup* group = InstObjectRoot::Instance().GetGroup(EIOT_PARA, desFile.Str());
				if (group)
				{
					paraGroup = (SalParaGroup*)group;
					if (paraLen == paraGroup->DataGroup().Group(0)->SizeOfDataWithCrc())
					{
						u32 = 0;
					}
				}
				else
				{
					paraGroup = 0;
				}
			}
			sendbuf.Write(&u32, sizeof(u32));
			u32 = framMaxLen;
			sendbuf.Write(&u32, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else if (u32 == E_Trans)
		{
			uint32 offset;
			buf.Read(offset);
			uint32 len;
			buf.Read(len);
			SalFile file;
			if ((offset + len) < editMsg.bufLen)
			{
				MemCpy(((uint8*)editMsg.buf) + offset, buf.Top(), len);
			}
			SCharStream2kb sendbuf;
			uint32 u32 = E_TransAck;
			sendbuf.Write(&u32, sizeof(u32));
			u32 = -1;
			if ((offset + len) >= paraLen)
			{
				ParaGroupData data;
				data.data = (int32*)editMsg.buf;
				if (paraGroup)
				{
					data.header.elementNum = paraGroup->DataGroup().Group(0)->header.elementNum;
					if (data.IsCrcOk())
					{
						u32 = 0;
					}
				}
			}
			else
			{
				u32 = 0;
			}
			sendbuf.Write(&u32, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else if (u32 == E_TransErr)
		{
			paraGroup = 0;
			SCharStream2kb sendbuf;
			uint32 u32 = E_TransErrAck;
			sendbuf.Write(&u32, sizeof(u32));
			u32 = 0;
			sendbuf.Write(&u32, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else if (u32 == E_Check)
		{
			ParaGroupData data;
			data.data = (int32*)editMsg.buf;
			SCharStream2kb sendbuf;
			uint32 u32 = E_CheckAck;
			sendbuf.Write(&u32, sizeof(u32));
			u32 = -1;
			if (paraGroup)
			{
				data.header.elementNum = paraGroup->DataGroup().Group(0)->header.elementNum;
				if (data.IsCrcOk())
				{
					u32 = paraGroup->SavePara(editMsg.buf, editMsg.bufLen, zone);
				}
			}
			sendbuf.Write(&u32, sizeof(u32));
			SendMsg(sendbuf.Top(), sendbuf.BufBase());
		}
		else
		{
			SalTransProtocol::Recv(Driver, Header);
		}
	}
	return 0;
}

int32 spt::SalParaTrans::Send(int32(*Process)(int32 Step, const char* info), uint32 Zone, const char* DesFile)
{
	desFile = DesFile;
	logStep = 0;
	infoFunc = Process;
	String100B info;
	InstObjectGroup* group = InstObjectRoot::Instance().GetGroup(EIOT_PARA, desFile.Str());
	if (group)
	{
		paraGroup = (SalParaGroup*)group;
		if (Zone >= paraGroup->MaxZone())
		{
			info = "参数异常";
			info << desFile;
			LogInfo(info, 1, 1);
			process = E_SendEnd;
			result = E_InfoErr;
			return result;
		}
	}
	else
	{
		info = "参数不存在";
		info << desFile;
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_InfoErr;
		return result;
	}
	SCharStream5kb sendbuf;
	uint32 u32 = process = E_SendStart;
	sendbuf.Write(&u32, sizeof(u32));
	u32 = Zone;
	sendbuf.Write(&u32, sizeof(u32));
	uint32 paraLen = paraGroup->DataGroup().Group(0)->SizeOfDataWithCrc();
	sendbuf.Write(&paraLen, sizeof(u32));
	uint32 TransLen = 0;
	uint32 framMaxLen = cmm->FrameBufLen() - 40;
	if (framMaxLen > recMsg.bufLen)
	{
		framMaxLen = recMsg.bufLen - 40;
	}
	u32 = framMaxLen;
	sendbuf.Write(&u32, sizeof(u32));
	u32 = desFile.StrLen();
	sendbuf.Write(&u32, sizeof(u32));
	sendbuf.Write(desFile.Str(), u32 + 1);
	SendMsg(sendbuf.Top(), sendbuf.BufBase());
	sendbuf.Clear();
	info = paraGroup->Name();
	info << "开始下发";
	LogInfo(info, 1, 1);
	logStep++;
	int32* pinfo = 0;
	int32 res = WaitMsgOk(E_SendStartAck, pinfo, 500);
	if (res == E_RecvOverTime)
	{
		info = "信息确认超时,按任意键继续";
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_SendErr;
		return result;
	}
	else if (res == 0)
	{

	}
	else
	{
		info << "信息不匹配,按任意键继续";
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_InfoErr;
		return result;
	}
	if (pinfo)
	{
		if (framMaxLen > (uint32)pinfo[0])
		{
			framMaxLen = pinfo[0];
		}
	}
	logStep++;
	uint32 serial = 0;
	uint32 rtranCnt = 0;
	uint32 fileRtrans = 0;
	info = "发送中";
	uint32 lastPercent = ((TransLen * 100 / paraLen));
	info << lastPercent << "%";
	LogInfo(info, 1, 0);
	uint8 data[4096];
	MemCpy(data, paraGroup->DataGroup().Group(Zone)->AddrOf(0), paraLen);
	while (TransLen < paraLen)
	{
		sendbuf.Clear();
		u32 = E_Trans;
		sendbuf.Write(&u32, sizeof(u32));
		sendbuf.Write(&TransLen, sizeof(TransLen));
		uint32 len = paraLen - TransLen;
		if (len > framMaxLen)
		{
			len = framMaxLen;
		}
		sendbuf.Write(&len, sizeof(len));
		sendbuf.Write(&data[TransLen], len);
		SendMsg(sendbuf.Top(), sendbuf.BufBase());
		int32 res = WaitMsgOk(E_TransAck, 500);
		if (res == -1)
		{
			TransLen = 0;
			serial = 0;
			fileRtrans++;
			if (fileRtrans > 3)
			{
				logStep++;
				info = "发送异常,按任意键继续";
				result = E_SendErr;
				LogInfo(info, 1, 1);
				process = E_SendEnd;
				return result;
			}
			else
			{
				LogMsg.Stamp() << "para trans recv -1 fileRtrans" << fileRtrans << "\n";
			}
		}
		else if (res != 0)
		{
			rtranCnt++;
			if (rtranCnt > 3)
			{
				if (res == E_RecvOverTime)
				{
					logStep++;
					info = "发送确认消息等待超时,按任意键继续";
					result = E_RecvOverTime;
				}
				else
				{
					logStep++;
					info = "发送异常,按任意键继续";
					result = E_SendErr;
				}
				LogInfo(info, 1, 1);
				process = E_SendEnd;
				return result;
			}
			else
			{
				LogMsg.Stamp() << "para trans recv !=0 retrans" << rtranCnt << "\n";
			}
		}
		else
		{
			rtranCnt = 0;
			TransLen += len;
			serial++;
			uint32 tempPercent = ((TransLen * 100 / paraLen));
			if (tempPercent != lastPercent)
			{
				lastPercent = tempPercent;
				info = "文件发送中";
				info << tempPercent << "%";
				LogInfo(info, 1, 0);
			}
		}
	}
	logStep++;
	info = "发送完成";
	LogInfo(info, 1, 1);
	logStep++;
	uint32 crc = paraGroup->DataGroup().Group(Zone)->GetCrc();
	process = u32 = E_Check;
	sendbuf.Clear();
	sendbuf.Write(&u32, sizeof(u32));
	sendbuf.Write(&crc, sizeof(crc));
	SendMsg(sendbuf.Top(), sendbuf.BufBase());
	res = WaitMsgOk(E_CheckAck, 500);
	if (res == 0)
	{
		info = "校验成功(";
		info.FormatHex((uint16)crc) << ")";
		LogInfo(info, 1, 1);
		result = E_SendOk;
	}
	else if (res == E_RecvOverTime)
	{
		info = "信息确认超时,按任意键继续";
		LogInfo(info, 1, 1);
		process = E_SendEnd;
		result = E_CheckErr;
		return result;
	}
	else
	{
		info = "校验失败";
		LogInfo(info, 1, 1);
		result = E_CheckErr;
	}
	logStep++;
	info = "按任意键继续";
	LogInfo(info, 1, 1);
	process = E_SendEnd;
	return result;
}


spt::SalMsgTrans::SalMsgTrans(AdtBufDes& recMsg, SalCmmChannel* Cmm, uint16 Dst, struct CmmMsgDriver* Driver)
	:SalTransProtocol(recMsg, Cmm, Dst, Driver)
{
}

int32 spt::SalMsgTrans::WaitMsg(uint32 Type, Msg*& Msg, int32 Ms)
{
	MsTimer timer;
	timer.UpCnt(Ms);
	timer.Enable(1);
	Msg = 0;
	while (!timer.Status())
	{
		if (recOk)
		{
			SalTransFrame* frame = (SalTransFrame*)recMsg.buf;
			CharStreamReader buf(frame->data, frame->Header.dataLen);
			uint32 u32 = 0;
			buf.Read(u32);
			if (u32 == Type)
			{
				Msg = (SalMsgTrans::Msg*)frame->data;
				recOk = 0;
				return 0;
			}
		}
		MsSleep(1);
	}
	recOk = 0;
	return E_RecvOverTime;
}

int32 spt::SalMsgTrans::Recv(CmmMsgDriver* Driver, SalCmmMsgHeader* Header)
{
	if (Header->len < recMsg.bufLen)
	{
		SalTransFrame* frame = (SalTransFrame*)Header;
		if (frame->Header.type == E_MsgTrans)
		{
			SalTransProtocol::Recv(Driver, Header);
			return 0;
		}
	}
	return -1;
}

int32 spt::SalMsgTrans::Send(uint32 Type, int32 Para, uint8* Msg, uint32 MsgLen)
{
	SCharStream5kb sendbuf;
	sendbuf.Write(&Type, sizeof(Type));
	sendbuf.Write(&Para, sizeof(Para));
	sendbuf.Write(&MsgLen, sizeof(MsgLen));
	if (MsgLen)
	{
		sendbuf.Write(Msg, MsgLen);
	}
	SendMsg(sendbuf.Top(), sendbuf.BufBase());
	return 0;
}

spt::SalTransFrameCtrl::SalTransFrameCtrl(SalTransFrame* Frame, uint32 DataBufLen)
{
	frame = Frame;
	dataBufLen = DataBufLen;
	reader = writer = 0;
}

void spt::SalTransFrameCtrl::SetMsgIniInfo(uint32 Type, uint32 unPackIndex)
{
	frame->Header.SetHeader(Type, unPackIndex, 0);
	reader = writer = 0;
}

int32 spt::SalTransFrameCtrl::Write(void* Data, uint32 DataLen)
{
	uint32 w = writer + DataLen + 2;
	if (w > dataBufLen)
	{
		return -1;
	}
	MemCpy(frame->data + writer, Data, DataLen);
	frame->Header.dataLen = writer += DataLen;
	return DataLen;
}

int32 spt::SalTransFrameCtrl::Read(void* Data, uint32 DataBufLen)
{
	if (reader < frame->Header.dataLen)
	{
		uint32 len = Min(DataBufLen, frame->Header.dataLen - reader);
		MemCpy(Data, frame->data + reader, len);
		reader += len;
		return len;
	}
	return 0;
}

int32 spt::SalTransFrameCtrl::CopyCtx(SalCmmMsgHeader& Ctrl)
{
	if (dataBufLen >= Ctrl.len)
	{
		MemCpy(&frame->Header, &Ctrl, Ctrl.len);
		return Ctrl.len;
	}
	else
	{
		MemCpy(&frame->Header, &Ctrl, dataBufLen);
		return dataBufLen;
	}
	return -1;
}

int32 spt::SalTransHeader::SetHeader(uint16 Type, uint16 UnpackIndex, uint16 DataLen)
{
	type = Type;
	unPackIndex = UnpackIndex;
	dataLen = DataLen;
	res = 0;
	salHeader.len = DataLen + sizeof(SalTransHeader);
	return DataLen;
}
