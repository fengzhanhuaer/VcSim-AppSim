#ifndef SALVERSION_H
#define SALVERSION_H

namespace spt
{
	struct SptVersion
	{
		uint64 progOk;//У���־0x5a5a5a5aa5a5a5a5
		uint64 preamble;//ǰ����
		uint32 binSize;//bin���ݴ�С
		uint32 fileSize;//bin�ļ���С
		uint16 crc;//����bin���ݽ��е�crc_modbusУ��
		uint16 major;//���汾�ţ�����ܸ���ʱ�䶯
		uint16 minor;//��Ҫ�汾�ţ����ܵ�������ʱ�䶯
		uint16 reversion;//�����汾�ţ�����bugʱ�䶯
		int64 datetimeus;//��Ԫ1��1��1�� 00:00:00�����us��
		char programName[35];//��������
		char publisher[35];//���򷢲���
		void FillInfo(uint32 fileSize, uint16 Major, uint16 Minor, uint16 Reversion, const char* ProName, const char* Publisher, const char* DateTime);
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

}

#endif // !SALVERSION_H

