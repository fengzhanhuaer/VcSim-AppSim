#ifndef HMIGRIDWND_H
#define HMIGRIDWND_H
namespace spt
{
	typedef const char* (*HmiGridWndDataMapCellToStr)(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	typedef int32(*HmiGridWndDataMapCellEidt)(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell);//返回0，表示成功
	struct HmiGridWndDataMapCell
	{
		bool8 isEnable;
		bool8 isCanSelect;
		bool8 isFromRight;
		uint8 dotLen;
		uint8 dataLen;
		uint8 unitLen;
		uint8 fullLen;
		uint16 row;
		uint16 col;
		uint16 page;
		st64value dataSur;//供应用使用
		st64value dataExInfo;//供应用使用
		st64value dataEdit;//供应用使用与界面共用
		st64value dataDisp;//供界面使用，缓存数据
		int64 editMax;
		int64 editMin;
		const char* unit;
		struct HmiGridWndDataMapRow* pRow;
		HmiGridWndDataMapCellToStr toStr;
		HmiGridWndDataMapCellEidt edit;
		void ResetStatus();
	};
	//字符串显示
	const char* HmiGridWndDataMapCellStrDisp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号32位显示
	const char* HmiGridWndDataMapCellPU32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号16位显示
	const char* HmiGridWndDataMapCellPU16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号8位显示
	const char* HmiGridWndDataMapCellPU8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//有符号32位显示
	const char* HmiGridWndDataMapCellPI32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//有符号16位显示
	const char* HmiGridWndDataMapCellPI16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//有符号8位显示
	const char* HmiGridWndDataMapCellPI8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号32位HEX显示
	const char* HmiGridWndDataMapCellPHex32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号16位HEX显示
	const char* HmiGridWndDataMapCellPHex16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号8位HEX显示
	const char* HmiGridWndDataMapCellPHex8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号32位ENUM显示
	const char* HmiGridWndDataMapCellPEDUM32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号16位ENUM显示
	const char* HmiGridWndDataMapCellPEDUM16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//无符号8位ENUM显示
	const char* HmiGridWndDataMapCellPEDUM8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//状态量显示
	const char* HmiGridWndDataMapCellStatusFmt1Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//状态量时间显示
	const char* HmiGridWndDataMapCellStatusTimeDisp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//数据编辑
	//0 is ok
	//-1 is err
	int32 HmiGridWndDataMapCellEdit(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell);
	const uint32  CN_Max_Hmi_Grid_Page = 20;
	const uint32  CN_Max_Hmi_Grid_Page_Row = 13;
	const uint32  CN_Max_Hmi_Grid_Page_Row_Cell = 10;
	/// <summary>
	/// 表格显示单行数据映射结构
	/// </summary>
	struct HmiGridWndDataMapRow
	{
		bool8 isEnable;
		bool8 isCanSelect;
		uint16 row;
		uint16 cellNum;
		uint16 page;
		HmiGridWndDataMapCell cell[CN_Max_Hmi_Grid_Page_Row_Cell];
		void SetName(const char* Name);
		void SetName(const char* Name, HmiGridWndDataMapCellEidt edit);
		void SetCfgData(CfgDataBase* DataCfg);
		void SetColDataCfg(uint32 Col, HmiGridWndDataMapCellToStr toStr, HmiGridWndDataMapCellEidt edit, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, bool8 isFromRight);
		/// <summary>
		/// 设置列属性
		/// </summary>
		/// <param name="Col">列号</param>
		/// <param name="IsEditAble">是否可编辑</param>
		/// <param name="Type">E_SalValType 必须为指针型数据</param>
		/// <param name="Len">显示位宽</param>
		/// <param name="DotLen">小数位数</param>
		/// <param name="Unit">单位</param>
		void SetColDataCfg(uint32 Col, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, const char* Unit, bool8 isFromRight = 1);
		/// <summary>
		/// 设置列属性
		/// </summary>
		/// <param name="Col">列号</param>
		/// <param name="IsEditAble">是否可编辑</param>
		/// <param name="Type">E_SalValType 必须为指针型数据</param>
		/// <param name="Len">显示位宽</param>
		/// <param name="DotLen">小数位数</param>
		void SetColDataCfg(uint32 Col, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, bool8 isFromRight = 1);
		void SetColDataRange(uint32 Col, int64 Max, int64 Min);
		void SetColData(uint32 Col, const uint32* Ptr);
		/// <summary>
		/// 双点数据显示
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		void SetColDataDp(uint32 Col, const uint8* Ptr);
		void SetColData(uint32 Col, const uint16* Ptr);
		void SetColData(uint32 Col, const uint8* Ptr);
		void SetColData(uint32 Col, const int32* Ptr);
		void SetColData(uint32 Col, const int16* Ptr);
		/// <summary>
		/// 设置列为参数型定值
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Edit"></param>
		/// <param name="Ptr"></param>
		/// <param name="Len"></param>
		void SetColData(uint32 Col, bool8 Edit, SalParaEditCell* Ptr, uint8 Len);
		/// <summary>
		/// 显示状态量
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		/// <param name="Len"></param>
		void SetColData(uint32 Col, SalStatus* Ptr, uint8 Len);
		/// <summary>
		/// 显示状态量时间
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		/// <param name="Len"></param>
		/// <param name="Type">对应汉字时间格式的样式1/2/3</param> 
		void SetColStatusTime(uint32 Col, const SalStatus* Ptr, uint8 Len, uint8 Type);
		void SetColStrData(uint32 Col, const char* Ptr, bool8 IsFromRight);
		/// <summary>
		/// 枚举型显示
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		/// <param name="Des"></param>
		/// <param name="Total"></param>
		void SetColData(uint32 Col, const uint32* Ptr, const struct SalEnumDes* Des, uint32 Total);
		void SetColData(uint32 Col, const uint16* Ptr, const struct SalEnumDes* Des, uint32 Total);
		void SetColData(uint32 Col, const uint8* Ptr, const struct SalEnumDes* Des, uint32 Total);
		void SetColData(uint32 Col, const uint32* Ptr, const struct SalBitDes* Des);
		void SetColData(uint32 Col, const uint16* Ptr, const struct SalBitDes* Des);
		void SetColData(uint32 Col, const uint8* Ptr, const struct SalBitDes* Des);
		void SetColData(uint32 Col, const int8* Ptr);
		st64value* GetDataSur(uint32 Col);//供应用使用
		st64value* GetDataExInfo(uint32 Col);//供应用使用
		st64value* GetDataEdit(uint32 Col);//供应用使用与界面共用
		struct HmiGridWndDataMapPage* pPage;
		void ResetStatus();
	};
	struct HmiGridWndDataMapPage
	{
		bool8 isEnable;
		bool8 isCanSelect;
		uint16 rowNum;
		uint16 page;
		HmiGridWndDataMapRow* pRow[CN_Max_Hmi_Grid_Page_Row];
		void ResetStatus();
		struct HmiGridWndDataMap* pMap;
	};
	struct HmiGridWndDataMap
	{
		uint16 pageNum;
		uint16 rowNum;
		uint16 rowCellLen[CN_Max_Hmi_Grid_Page_Row_Cell];
		uint16 rowCellDataLen[CN_Max_Hmi_Grid_Page_Row_Cell];
		uint16 rowCellUnitLen[CN_Max_Hmi_Grid_Page_Row_Cell];
		uint16 cellCol[CN_Max_Hmi_Grid_Page_Row_Cell];
		uint16 maxRowCellNum;
		HmiGridWndDataMapRow row[CN_Max_Hmi_Grid_Page_Row * CN_Max_Hmi_Grid_Page];
		HmiGridWndDataMapPage page[CN_Max_Hmi_Grid_Page];
		void ResetStatus();
	};
	struct HmiGridTitleCol
	{
		char str[15];
		uint16 strlen;
		uint16 displen;
		uint16 col;
		bool8 isFromRight;
	};
	typedef int32(*HmiGridWndUpdateData)(class HmiGridWnd* Wnd, struct HmiGridWndDataMap* Map, HmiKey Key);
	class HmiGridWnd :public HmiWidTextWnd
	{
	public:
		HmiGridWnd();
		int32 Show();
		int32 Edit();
		void SetColTitle(const char* Title1, const char* Title2, const char* Title3, const char* Title4, const char* Title5, const char* Title6, const char* Title7, const char* Title8, const char* Title9, const char* Title10);
	protected:
		void AutoLayerOut();
		virtual int32 ShowSelf();
		virtual int32 ShowPeriod();
		int32 FindFirstEditCell();
		int32 FindLastEditCell();
		int32 Go2LastEditCell();
		int32 Go2NextEditCell();
	protected:
		HmiGridWndUpdateData updateData;
		HmiGridTitleCol colTitle[CN_Max_Hmi_Grid_Page_Row_Cell];
		HmiGridWndDataMapCell* selectCell;
		uint8 titleNum;
		bool8 isEditCellMode;
		bool8 isEditData;
		bool8 isDataChange;
		static HmiGridWndDataMap map;
	};
}
#endif
