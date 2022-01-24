#include "SptProject.h"
using namespace spt;
#include "stdio.h"
namespace spt
{
	SptLog LogReal("LogReal", 512 * 1024, 0, 0, 0);
	SptLog LogMsg("LogMsg", 512 * 1024, 1, 1, 0);
	SptLog LogWarn("LogWarn", 512 * 1024, 1, 1, 1);
	SptLog LogErr("LogErr", 512 * 1024, 1, 1, 1);
	SptLog LogTest("LogTest", 512 * 1024, 0, 0, 0);
	SptLog LogApp("LogApp", 512 * 1024, 1, 1, 0);
	SptLog LogAct("LogAct", 512 * 1024, 1, 1, 0);
	SptLog LogLoad("LogLoad", 512 * 1024, 1, 1, 1);
}

SptLog& spt::SptLog::PrintLine(const char* Msg)
{
	*this << Msg << "\n";
	return *this;
}

SptLog& spt::SptLog::Stamp()
{
#ifndef GZK_LCD
	SalRtc rtc;
	SalDateStamp cstamp;
	cstamp.Now();
	rtc.FromStamp(&cstamp);
	String200B str;
	rtc.ToStrFmt3(str);
	str << " ";
	str.FormatHex((uint8)cstamp.q.q);
	str << " ";
	return *this << str;
#else 
	return *this;
#endif

}

SptLog& spt::SptLog::Print(const char* Msg)
{
	return (*this) << Msg;
}

SptLog& spt::SptLog::EndLine()
{
	return (*this) << "\n";
}

SptLog& spt::SptLog::NotEqual(const char* Name, int32 Data1, int32 Data2)
{
	String200B str;
	str = Name;
	str << " " << Data1 << "!=" << Data2 << " ";
	*this << str;
	return *this;
}

SptLog& spt::SptLog::operator<<(const char* Msg)
{
	log(Msg);
	return *this;
}

SptLog& spt::SptLog::operator<<(int32 Msg)
{
	String20B msg;
	msg << Msg << " ";
	log(msg.Str());
	return *this;
}

SptLog& spt::SptLog::operator<<(uint32 Msg)
{
	String20B msg;
	msg << Msg << " ";
	log(msg.Str());
	return *this;
}
SptLog& spt::SptLog::operator<<(SalString& Msg)
{
	log(Msg.Str());
	return *this;
}

SptLog& spt::SptLog::operator<<(SalDateStamp& Stamp)
{
	String40B msg;
	Stamp.ToStrHzFmt3(msg);
	msg << " ";
	log(msg.Str());
	return *this;
}

spt::SptLog::SptLog(const char* Name, uint32 BufSize, bool8 LocalPrint, bool8 FilePrint, bool8 NetPrint)
{
	String100B str;
	str = Name;
	str << "本地打印";
	localPrint.SetName(str.Str());
	localPrint.SetData(LocalPrint);
	str = Name;
	str << "文件打印";
	filePrint.SetName(str.Str());
	filePrint.SetData(FilePrint);
	str = Name;
	str << "网络打印";
	netPrint.SetName(str.Str());
	netPrint.SetData(NetPrint);
	AllocBuf loc(0);
	loc.Alloc(1, 32 * 1024);
	saveBuf.SetBuf(&loc);
	fileMaxSize = BufSize;
	StrNCpy(name, Name, sizeof(name));
}
int32 spt::SptLog::log(const char* Msg)
{
	isLogIng = 1;
	saveBuf.Write((void*)Msg, StrLen(Msg) + 1);
	saveBuf.WriterAdd(-1);
	isLogIng = 0;
	return 0;
}

void spt::SptLog::Save2File()
{
	if (!filePrint.Data())
	{
		return;
	}
	if (saveBuf.IsEmpty())
	{
		return;
	}
	SalFile file;
	file.Path().Set(CN_LOG_FILE_ROOT);
	String100B fileName;
	fileName << name;
	fileName << ".log";
	file.Name().Set(fileName.Str());
	uint32 size = file.Size();
	String100B fullName;
	file.FullName(fullName);
	if (size > fileMaxSize)
	{
		String100B newfullName;
		newfullName << fullName << ".bak";
		Rename(fullName.Str(), newfullName.Str());
	}
	file.Open("ab+");
	if (!file.IsOpened())
	{
		file.Path().Creat();
		file.Open("ab+");
		if (!file.IsOpened())
		{
			return;
		}
	}
	file.Write(saveBuf.BufBase(), saveBuf.Top());
}

void spt::SptLog::Save2Net()
{
	if (!netPrint.Data())
	{
		return;
	}
	if (saveBuf.IsEmpty())
	{
		return;
	}
}

void spt::SptLog::Save2Local()
{
	if (!localPrint.Data())
	{
		return;
	}
	if (saveBuf.IsEmpty())
	{
		return;
	}
	printf("%s", (const char*)saveBuf.BufBase());
}

void spt::SptLog::ClearBuf()
{
	saveBuf.Clear();
}

void spt::SptLog::Flush()
{
	if (isLogIng)
	{
		return;
	}
	if (SptLogTask::Instance().LogCfg().netPrint.Data() == 1)
	{
		Save2Net();
	}
	if (SptLogTask::Instance().LogCfg().localPrint.Data() == 1)
	{
		Save2Local();
	}
	if (SptLogTask::Instance().LogCfg().filePrint.Data() == 1)
	{
		Save2File();
	}
	ClearBuf();
}

int32 spt::SptLog::PowerUpIni(int32 Para, class SptLogCfg& File)
{
	File.AddCfgData(&localPrint);
	File.AddCfgData(&filePrint);
	File.AddCfgData(&netPrint);

	char Name[60];
	StrNCpy(Name, name, sizeof(Name));
	InstObject::PowerUpIni(Name, Name, &SptLogTask::Instance(), EIOT_LOG, ((InstObjectGroup)SptLogTask::Instance()).InstId(), SptLogTask::Instance().InstNum());
	return 0;
}


int32 spt::SptLogCfg::PowerUpIni(int32 Para, const char* CfgFileName)
{
	String100B str;
	str = "本地打印";
	localPrint.SetName(str.Str());
	localPrint.SetData(1);
	str = "文件打印";
	filePrint.SetName(str.Str());
	filePrint.SetData(1);
	str = "网络打印";
	netPrint.SetName(str.Str());
	netPrint.SetData(0);
	AddCfgData(&localPrint);
	AddCfgData(&filePrint);
	AddCfgData(&netPrint);

	path.Set(CN_CFG_FILE_ROOT);
	String100B fileName;
	fileName << CfgFileName;
	fileName << ".cfg";
	name.Set(fileName.Str());

	if ((uint32)ReadAll() != CfgDataNum())
	{
		if (SptMain::Instance().StartMode() == SptMain::E_Normal)
		{
			SaveAll();
		}
		if (!IsExist())
		{
			filePrint.SetData(0);
			LogErr.Stamp() << "log.Cfg文件生成失败\n";
		}
	}
	if (SptMain::Instance().StartMode() == SptMain::E_Factory)
	{
		filePrint.SetData(0);
	}
	return 0;
}

void spt::SptLogTask::LoadCfg()
{
	if ((uint32)logCfg.ReadAll() != logCfg.CfgDataNum())
	{
		logCfg.SaveAll();
	}
}

int32 spt::SptLogTask::PowerUpIni(int32 Para)
{
	Task::PowerUpIni(0);
	InstObjectGroup::PowerUpIni("LogGroup", "LogGroup", EIOT_LOG, 20);
	LogReal.PowerUpIni(0, logCfg);
	LogMsg.PowerUpIni(0, logCfg);
	LogWarn.PowerUpIni(0, logCfg);
	LogErr.PowerUpIni(0, logCfg);
	LogTest.PowerUpIni(0, logCfg);
	LogApp.PowerUpIni(0, logCfg);
	LogLoad.PowerUpIni(0, logCfg);
	LogAct.PowerUpIni(0, logCfg);
	logCfg.PowerUpIni(0, "Log");
	Start();
	SetSaveBlockPara();
	return 0;
}
int32 spt::SptLogTask::OneLoop()
{
	switch (taskStep)
	{
	case E_PowerUpIni:
	{
		taskStep = E_Work;
		break;
	}
	case E_Work:
	{
		MsSleep(50);
		if (SptIoProcess::Instance().SptFlag().IsPowerDownAtRange(saveLowLimit, saveHighLimit))
		{
			return 0;
		}
		if (!logTimer.Status())
		{
			if (!logTimer.IsEnable())
			{
				logTimer.UpCnt(100);
				logTimer.Enable(1);
			}
			break;
		}
		for (uint16 i = 0; i < InstNum(); i++)
		{
			InstObject* obj = GetObject(i);
			if (obj)
			{
				SptLog* log = (SptLog*)obj;
				log->Flush();
			}
		}
		break;
	}
	default:
		taskStep = E_PowerUpIni;
		break;
	}
	return 0;
}

SptLogCfg& spt::SptLogTask::LogCfg()
{
	return logCfg;
}

spt::SptLogTask::SptLogTask()
	:Task("tLogTask", TaskBasePriority - 10, 1024 * 1024, E_T_FLOAT, E_AuxCore)
{



}
