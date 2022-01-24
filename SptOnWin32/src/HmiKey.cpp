#include "SptProject.h"
using namespace spt;


void spt::HmiKeyService::Push(HmiKey Key)
{
#ifdef GZK_LCD
	LcdKeyMsg msg;
	msg.type = E_KeyMsg;
	msg.key1 = (uint8)Key.Key1;
	msg.key2 = (uint8)Key.Key2;
	msg.key3 = (uint8)Key.Key3;
	msg.key4 = (uint8)Key.Key4;
	msg.len = (uint16)(sizeof(msg));
	HmiLcdCmm::Instance().Send((LcdMsgContext*)&msg);
#else 
	keyBuf.Push(&Key);
	if ((Key.Key2 == EK_F1) && (Key.Key1 == EK1_KEYVALUE))
	{
		SptIoProcess::Instance().AppFlags().blFaceRevert = 1;
	}
#endif // !LCDMAIN_H
}

HmiKeyService& spt::HmiKeyService::Instance()
{
	static HmiKeyService inst;
	return inst;
}

bool8 spt::HmiKeyService::Pop(HmiKey& Key)
{
#ifdef GZK_LCD
	return keyBuf.Pop(&Key);
#else 
	bool8 res = keyBuf.Pop(&Key);
	if (res)
	{
		lastKeyPutTime = SptMsInt::Instance().MsCnt32();
		escTimer.Enable(0);
		forceEscTime = 0;
	}
	else if (escTimer.Status())
	{
		//²úÉúÐéÄâ°´¼ü
		HmiKey key = { EK1_KEYVALUE, EK_MD_STOP };
		if (forceEscTime < 30)
		{
			forceEscTime++;
			Key = key;
			return 1;
		}
	}
	else if (!escTimer.IsEnable())
	{
		uint32 data = SalUserMng::Instance().UsrCfg.AutoExitTime.Data();
		if (data && (data < 100))
		{
			escTimer.UpCnt(escTimer.Mt1Minute * data);
		}
		else
		{
			escTimer.UpCnt(escTimer.Mt1Minute * 5);
		}
		escTimer.Enable(1);
		forceEscTime = 0;
	}
	return res;
#endif // !LCDMAIN_H
}

uint32 spt::HmiKeyService::SinceLastKeyPutIn()
{
	return SptMsInt::Instance().MsCnt32() - lastKeyPutTime;
}

spt::HmiKeyService::HmiKeyService()
{
	keyBuf.SetBuf(keyrambuf, sizeof(keyrambuf[0]), M_ArrLen(keyrambuf));
}
