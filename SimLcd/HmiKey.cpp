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
		escTimer.Restart();
	}
	else if(escTimer.Status())
	{
		//²úÉúÐéÄâ°´¼ü
		HmiKey key = { EK_MD_STOP };
		Push(key);
	}
	else if (!escTimer.IsEnable())
	{
		escTimer.UpCnt(escTimer.Mt1Minute*5);
		escTimer.Enable(1);
	}

	return res;
#endif // !LCDMAIN_H
}

spt::HmiKeyService::HmiKeyService()
{
	keyBuf.SetBuf(keyrambuf, sizeof(keyrambuf[0]), M_ArrLen(keyrambuf));
}
