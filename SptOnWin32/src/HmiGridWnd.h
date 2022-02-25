#ifndef HMIGRIDWND_H
#define HMIGRIDWND_H
namespace spt
{
	typedef const char* (*HmiGridWndDataMapCellToStr)(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	typedef int32(*HmiGridWndDataMapCellEidt)(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell);//����0����ʾ�ɹ�
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
		st64value dataSur;//��Ӧ��ʹ��
		st64value dataExInfo;//��Ӧ��ʹ��
		st64value dataEdit;//��Ӧ��ʹ������湲��
		st64value dataDisp;//������ʹ�ã���������
		int64 editMax;
		int64 editMin;
		const char* unit;
		struct HmiGridWndDataMapRow* pRow;
		HmiGridWndDataMapCellToStr toStr;
		HmiGridWndDataMapCellEidt edit;
		void ResetStatus();
	};
	//�ַ�����ʾ
	const char* HmiGridWndDataMapCellStrDisp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���32λ��ʾ
	const char* HmiGridWndDataMapCellPU32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���16λ��ʾ
	const char* HmiGridWndDataMapCellPU16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���8λ��ʾ
	const char* HmiGridWndDataMapCellPU8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�з���32λ��ʾ
	const char* HmiGridWndDataMapCellPI32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�з���16λ��ʾ
	const char* HmiGridWndDataMapCellPI16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�з���8λ��ʾ
	const char* HmiGridWndDataMapCellPI8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���32λHEX��ʾ
	const char* HmiGridWndDataMapCellPHex32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���16λHEX��ʾ
	const char* HmiGridWndDataMapCellPHex16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���8λHEX��ʾ
	const char* HmiGridWndDataMapCellPHex8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���32λENUM��ʾ
	const char* HmiGridWndDataMapCellPEDUM32Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���16λENUM��ʾ
	const char* HmiGridWndDataMapCellPEDUM16Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//�޷���8λENUM��ʾ
	const char* HmiGridWndDataMapCellPEDUM8Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//״̬����ʾ
	const char* HmiGridWndDataMapCellStatusFmt1Disp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//״̬��ʱ����ʾ
	const char* HmiGridWndDataMapCellStatusTimeDisp(SalString& Str, struct HmiGridWndDataMapCell* Cell);
	//���ݱ༭
	//0 is ok
	//-1 is err
	int32 HmiGridWndDataMapCellEdit(bool8& isDataChange, struct HmiGridWndDataMapCell* Cell);
	const uint32  CN_Max_Hmi_Grid_Page = 20;
	const uint32  CN_Max_Hmi_Grid_Page_Row = 13;
	const uint32  CN_Max_Hmi_Grid_Page_Row_Cell = 10;
	/// <summary>
	/// �����ʾ��������ӳ��ṹ
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
		/// ����������
		/// </summary>
		/// <param name="Col">�к�</param>
		/// <param name="IsEditAble">�Ƿ�ɱ༭</param>
		/// <param name="Type">E_SalValType ����Ϊָ��������</param>
		/// <param name="Len">��ʾλ��</param>
		/// <param name="DotLen">С��λ��</param>
		/// <param name="Unit">��λ</param>
		void SetColDataCfg(uint32 Col, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, const char* Unit, bool8 isFromRight = 1);
		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="Col">�к�</param>
		/// <param name="IsEditAble">�Ƿ�ɱ༭</param>
		/// <param name="Type">E_SalValType ����Ϊָ��������</param>
		/// <param name="Len">��ʾλ��</param>
		/// <param name="DotLen">С��λ��</param>
		void SetColDataCfg(uint32 Col, bool8 IsEditAble, uint16 Type, uint16 Len, uint16 DotLen, bool8 isFromRight = 1);
		void SetColDataRange(uint32 Col, int64 Max, int64 Min);
		void SetColData(uint32 Col, const uint32* Ptr);
		/// <summary>
		/// ˫��������ʾ
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		void SetColDataDp(uint32 Col, const uint8* Ptr);
		void SetColData(uint32 Col, const uint16* Ptr);
		void SetColData(uint32 Col, const uint8* Ptr);
		void SetColData(uint32 Col, const int32* Ptr);
		void SetColData(uint32 Col, const int16* Ptr);
		/// <summary>
		/// ������Ϊ�����Ͷ�ֵ
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Edit"></param>
		/// <param name="Ptr"></param>
		/// <param name="Len"></param>
		void SetColData(uint32 Col, bool8 Edit, SalParaEditCell* Ptr, uint8 Len);
		/// <summary>
		/// ��ʾ״̬��
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		/// <param name="Len"></param>
		void SetColData(uint32 Col, SalStatus* Ptr, uint8 Len);
		/// <summary>
		/// ��ʾ״̬��ʱ��
		/// </summary>
		/// <param name="Col"></param>
		/// <param name="Ptr"></param>
		/// <param name="Len"></param>
		/// <param name="Type">��Ӧ����ʱ���ʽ����ʽ1/2/3</param> 
		void SetColStatusTime(uint32 Col, const SalStatus* Ptr, uint8 Len, uint8 Type);
		void SetColStrData(uint32 Col, const char* Ptr, bool8 IsFromRight);
		/// <summary>
		/// ö������ʾ
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
		st64value* GetDataSur(uint32 Col);//��Ӧ��ʹ��
		st64value* GetDataExInfo(uint32 Col);//��Ӧ��ʹ��
		st64value* GetDataEdit(uint32 Col);//��Ӧ��ʹ������湲��
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
