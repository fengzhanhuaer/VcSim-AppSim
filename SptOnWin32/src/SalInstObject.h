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
		EIOT_HalIo,
		EIOT_AngRms,
		EIOT_SJRecord,
		EIOT_FrRecord,
		EIOT_Total,
	};


	class InstObject
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  InstObjectGroup* Group, uint32 IOTYPE, uint32 GroupId, uint32 InstId);
		void PowerUpIni(const char* Name, const char* DesName, class  InstObjectGroup* Group, class  InstObjectGroup* NoDirGroup, uint32 IOTYPE, uint32 GroupId, uint32 InstId);
		uint32 InstObjectType()const;
		uint32 GroupId()const;
		uint32 InstId()const;
		const char* Name()const;
		const char* DesName()const;
		virtual void SaveIds(void* Ele);
	protected:
		class  InstObjectGroup* group;
		uint32 ioType;
		uint32 groupId;
		uint32 instId;
		char name[40];
		char desName[40];
	};

	class InstObjectGroup :public InstObject
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, uint32 IOTYPE, uint32 ElementNum);
		void RgsObject(InstObject* Object);
		void RgsSignleDirObject(InstObject* Object);
		InstObject* GetObject(uint32 InstId);
		InstObject* GetObject(const char* sAddr);
		uint32 InstNum();
		uint32 DesBufNum();
		virtual void SaveIds(void* Ele);
	protected:
		uint32 instNum;
		uint32 elementNum;
		ArrayBuf desBuf;
	};
	class InstObjectGroupParent :public InstObjectGroup
	{
	public:
		void PowerUpIni(const char* Name, const char* DesName, class  InstObjectGroup* group, uint32 IOTYPE, uint32 ElementNum);
		InstObjectGroup* GetGroup(uint32 InstId);
		InstObjectGroup* GetGroup(const char* sAddr);
		InstObject* GetObject(const char* sAddr);
	};
	class InstObjectRoot :public InstObjectGroupParent
	{
	public:
		void PowerUpOver(int32 Para);
		bool8 IsPowerUpOver();
		static InstObjectRoot& Instance();
		uint32 GetGroupParentNum();
		uint32 GetGroupNum(uint32 IOTYPE);
		InstObjectGroup* GetGroup(uint32 IOTYPE);
		InstObjectGroup* GetGroup(uint32 IOTYPE, uint32 Num);
		InstObjectGroup* GetGroup(uint32 IOTYPE, const char* sAddr);
		InstObjectGroupParent* GetGroupParent(uint32 IOTYPE);
		const char* IoTypeName(uint32 IOTYPE);
	protected:
		int32 UpdateIds();
		InstObjectRoot();
		bool8 powerUpOver;

	};


}

#endif
