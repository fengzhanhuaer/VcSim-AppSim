#ifndef INSTMENUCCDDISP_H
#define INSTMENUCCDDISP_H
#if(CN_DEV_CPU1)
bool8 DispCcdSvSub(ApiMenu* Menu);
#endif
bool8 DispCcdSvPub(ApiMenu* Menu);
bool8 DispCcdGooseSub(ApiMenu* Menu);
bool8 DispCcdGoosePub(ApiMenu* Menu);
//bool8 DispCcdToFPGA(ApiMenu* Menu);
#endif // !INSTMENUCCDDISP_H