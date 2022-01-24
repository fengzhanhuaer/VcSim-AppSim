#include "ApiProject.h"
using namespace spt;

bool8 spt::ApiAppCfg::IsHardWare(E_HARDWARE hd)const
{
	return this && (platform.hardware == hd);
}

bool8 spt::ApiAppCfg::IsSoftWare(E_SOFTWARE st)const
{
	return this && (platform.software == st);
}

bool8 spt::ApiAppCfg::IsDevice(E_DEVTYPE dev)const
{
	return this && (platform.devtype == dev);
}
