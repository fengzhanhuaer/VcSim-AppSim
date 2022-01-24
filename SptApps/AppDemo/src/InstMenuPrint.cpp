#include"InstResource.h"

bool8 PrintAllEvent2Txt(ApiMenu* Menu)
{
	SptEventPublishTask::Instance().SaveEventText(60);

	return 1;
}