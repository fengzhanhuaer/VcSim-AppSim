#ifndef SALVERSION_H
#define SALVERSION_H

namespace spt
{
	struct SptVersion
	{
		uint64 progOk;//У���־0x5a5a5a5aa5a5a5a5
		uint64 preamble;//ǰ����0x12fa990
		uint32 binSize;//bin���ݴ�С
		uint32 fileSize;//bin�ļ���С
		uint32 crc;//����bin���ݽ��е�crc_modbusУ��
		uint32 major;//���汾�ţ�����ܸ���ʱ�䶯
		uint32 minor;//��Ҫ�汾�ţ����ܵ�������ʱ�䶯
		uint32 reversion;//�����汾�ţ�����bugʱ�䶯
		int64 datetimeus;//��Ԫ1��1��1�� 00:00:00�����us��
		char programName[35];//��������
		char publisher[35];//���򷢲���
		void FillInfo(uint32 fileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, const char* DateTime);
		void FillInfo(uint32 fileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, int64 DateTime);
		void FillInfo(uint16 Major, uint16 Minor, uint16 Reversion, const char* Publisher, const char* Date, const char* Time);
		void ToStr(SalString& Str)const;
		void SetOk(bool8 ok);
		bool8 IsProgOk()const;
	};

	union SptVersionFile
	{
		SptVersion version;
		char buf[4096];
		void Fill(SptVersion& Version);
	};

	class ProgBinFile
	{
	public:
		static bool8 CreatBin(const char* FileName, SptVersion& Version);
		static bool8 GetVersion(const char* FileName, SptVersion& Version);
	};
	struct SalComVersion
	{
		/// <summary>
		/// ��ʽ1:10234��ʾΪ1.02.34��дΪ2.34
		/// 1 ��Ӳ��ƽ̨�汾������ARM�����X86�����
		/// 02 ��ʾ���ܰ汾,��������GOOSE���͹��ܰ汾�汾��Ӧ���б䶯
		/// 34 ��ʾ�����汾�������޸�GOOSE�����쳣��ĳBug
		/// ��ʽ2:0114560234��ʾΪ14.56.01.02.34��дΪ2.34
		/// 01 ��Ӳ��ƽ̨�汾������ARM�����X86�����(0~42)
		/// 14 Ӧ����������ĸ�ߡ���ѹ��
		/// 56 �������������԰汾��ĳʡ�ݰ汾������汾��
		/// 02 ��ʾ���ܰ汾,��������GOOSE���͹��ܰ汾�汾��Ӧ���б䶯
		/// 34 ��ʾ�����汾�������޸�GOOSE�����쳣��ĳBug
		/// </summary>
		uint32 ProgVersion;//ͨ�Ź����п��԰���16λ��32λ����
		uint32 ProgCrc;//У����,ͨ�Ź����п��԰���16λ��32λ����
		/// <summary>
		/// ��������
		/// format 0x19900816
		/// </summary>
		uint32 ProgDate;
		uint32 RtCrc;//����ʵʱУ����,ͨ�Ź����п��԰���16λ��32λ����
		char programName[16];//��������
		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="Name"></param>
		void SetName(const char* Name);
		/// <summary>
		/// ��ʽ������ַ���
		/// V1.00 19900816 A6B0C9D8
		/// </summary>
		/// <param name="Str"></param>
		/// <returns></returns>
		int32 RtInfoStrFmt2(SalString& Str)const;
		/// <summary>
		/// ��ʽ������ַ���
		/// V1.23.15.1.00 19900816 A6B0C9D8
		/// </summary>
		/// <param name="Str"></param>
		/// <returns></returns>
		int32 RtInfoStrFmt1(SalString& Str)const;
		void ToStr1(SalString& Str)const;
		void ToStr2(SalString& Str)const;
	};
}

#endif // !SALVERSION_H

