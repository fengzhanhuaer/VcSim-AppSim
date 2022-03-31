#include "InstResource.h"
bool8 FuncMenuTest(ApiMenu* Menu)
{
	SjUsrLogRecord.CreatRecord("Hmi", "ddddd", "管理员功能", "拒绝访问", "用户没有管理员权限", 0, 0);
	return 1;
}