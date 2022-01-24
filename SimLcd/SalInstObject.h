#ifndef SALINSTOBJECT_H
#define SALINSTOBJECT_H

namespace spt
{
	enum InstObjectType
	{
		EIOT_NULL = 0,
		EIOT_STATUS,
		EIOT_EVENT,
		EIOT_PARA,
		EIOT_HMILED,
		EIOT_TASK,
		EIOT_LOG,
	};


	class InstObject
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  InstObjectGroup* Group, uint32 IOTYPE, uint32 GroupId, uint32 InstId);
		uint32 InstObjectType();
		uint32 GroupId();
		uint32 InstId();
		const char* Name();
		const char* DesName();
	protected:
		class  InstObjectGroup* group;
		uint32 ioType;
		uint32 groupId;
		uint32 instId;
		char name[40];
		char desName[32];
	};

	class InstObjectGroup :public InstObject
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IOTYPE, uint32 ElementNum);
		void RgsObject(InstObject* Object);
		InstObject* GetObject(uint32 InstId);
		uint32 InstNum();
		uint32 DesBufNum();
	protected:
		uint32 instNum;
		uint32 elementNum;
		ArrayBuf desBuf;
	};

	class InstObjectRoot :public InstObjectGroup
	{
	public:
		void PowerUpOver(int32 Para);
		bool8 IsPowerUpOver();
		static InstObjectRoot& Instance();
		uint32 GetGroupNum();
		uint32 GetGroupNum(uint32 IOTYPE);
		InstObjectGroup* GetGroup(uint32 IOTYPE);
		InstObjectGroup* GetGroup(uint32 IOTYPE, uint32 Num);
	protected:
		InstObjectRoot();
		bool8 powerUpOver;
	};


}

#endif
