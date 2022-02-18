#ifndef HmiMenu_H
#define HmiMenu_H


namespace spt
{
	typedef bool8(*IsOkMenuFunction)(class ApiMenu* Menu);
	class HmiMenu
	{
	public:
		void SetMenu(const char* Name, HmiMenu* ChildMenu, IsOkMenuFunction AllowFunction, IsOkMenuFunction Function, IsOkMenuFunction ExitFunction, const uint32* PDisp);
		void SetName(const char* Name);
		void SetDisp(const uint32* pDisp);
		SalString& Name();
		bool8 IsDisp();
		bool8 IsEnd();
		void Disp(HmiPos pos, bool8 Selected);
	protected:
		GraphicDevice* gd;
		IsOkMenuFunction function;
		IsOkMenuFunction allowFunction;
		IsOkMenuFunction exitFunction;
		uint16 Id;
		uint16 strLen;
		String40B name;
		const uint32* pDisp;
		HmiMenu* child;
		friend class HmiMenuBar;
		friend class HmiMenuService;
	};
	extern const uint32 MenuDisp;
	extern const uint32 MenuUnDisp;
	extern const char* EndOfInst;

	class HmiMenuBar
	{
	public:
		void StartService(HmiMenu* Childs, uint16 BarId, HmiMenuBar* Parent);
		uint16 MaxMenuBuf();
		void Clear();
		void Disp();
		void SelectChg();
		void UnDisp();
		const HmiRect& Rect() { return rect; }
	protected:
		void SetPos(HmiPos Pos);
		void SetPos(int16 x, int16 y);
		void SetChilds(HmiMenu* Childs);
		void InsertMenu(HmiMenu* Child);
		HmiMenu* CascadeChild();
		bool8 IsCascade();
		bool8 AllowExit();
		bool8 AllowEnter();
		bool8 DoFunc();
	private:
		GraphicDevice* gd;
		int16 currentMenu;
		int16 lastMenu;
		int16 maxChildStrLen;
		HmiRect rect;
		HmiMenuBar* parent;
		uint16 Id;
		uint16 totalChild;
		HmiMenu* child[10];
		friend class HmiMenuService;
	};

	class HmiMenuService :public WidRect
	{
	public:
		enum TaskStep
		{
			E_PowerUp,
			E_DispAll,
			E_WaitKey,
			E_DispCurMenu,
			E_SelectChg,
		};
		uint16 MaxMenuBarBuf();
	public:
		static HmiMenuService& Instance();
	public:
		void StartService(HmiMenu* MenuRoot);
		void StartService(HmiMenu* MenuRoot, IsOkMenuFunction AllowFunction, IsOkMenuFunction ExitFunction);
	protected:
		HmiMenuService();
	protected:
		MsStampTimer stampTimer;
		IsOkMenuFunction allowFunction;
		IsOkMenuFunction exitFunction;
		HmiMenuBar* leftMenu;
		HmiMenuBar* curMenu;
		HmiMenuBar menuBar[10];
		class HmiMain* hmiMain;
		uint32 taskStep;
	};

}



#endif // !HmiMenu_H

