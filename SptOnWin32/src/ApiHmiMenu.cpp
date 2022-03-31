#include "ApiProject.h"
using namespace spt;

const uint32 spt::MenuDisp = 1;
const uint32 spt::MenuUnDisp = 0;
const char* spt::EndOfInst = "EndOfInst";

spt::ApiMenu::ApiMenu(const char* Name)
{
	SetMenu(Name, 0, 0, 0, 0, &MenuUnDisp);
}
spt::ApiMenu::ApiMenu(const char* Name, ApiMenu* ChildMenu)
{
	SetMenu(Name, ChildMenu, 0, 0, 0, &MenuDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, ApiMenu* ChildMenu, IsOkMenuFunction ExitFunction)
{
	SetMenu(Name, ChildMenu, AllowFunction, 0, ExitFunction, &MenuDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, ApiMenu* ChildMenu, const uint32* PDisp)
{
	SetMenu(Name, ChildMenu, 0, 0, 0, PDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, ApiMenu* ChildMenu, IsOkMenuFunction ExitFunction, const uint32* PDisp)
{
	SetMenu(Name, ChildMenu, AllowFunction, 0, ExitFunction, PDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, IsOkMenuFunction Function)
{
	SetMenu(Name, 0, 0, Function, 0, &MenuDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction)
{
	SetMenu(Name, 0, AllowFunction, Function, ExitFunction, &MenuDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, IsOkMenuFunction Function, const uint32* pDisp)
{
	SetMenu(Name, 0, 0, Function, 0, pDisp);
}

spt::ApiMenu::ApiMenu(const char* Name, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction, const uint32* pDisp)
{
	SetMenu(Name, 0, AllowFunction, Function, ExitFunction, pDisp);
}

const char* spt::ApiMenu::Name()
{
	return name.Str();
}




