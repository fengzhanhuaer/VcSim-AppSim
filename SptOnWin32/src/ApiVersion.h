#ifndef APIVERSION_H
#define APIVERSION_H
namespace spt
{
	class ApiVersionInfo
	{
	public:
		void Print();
		void UpdateInfo();
		SptVersion& AppVersion() { return appVersion; }
		const SptVersion& ApiVersion() { return apiVersion; }
		SalComVersion& LcdVersion() { return lcdVersion; }
		SalComVersion& VirLcdVersion() { return virlcdVersion; }
		SptVersion& CmmLiteVersion() { return cmmLiteVer; }
		SalComVersion& OtherChipVersion(uint32 Index) { if (Index < M_ArrLen(other)) { return other[Index]; } else { return other[M_ArrLen(other) - 1]; } }
		SptVersion& Boot0Version() { return boot0; };
		SptVersion& UbootVersion() { return uboot; };
		SptVersion& MainSysVersion() { return mainSys; };
		SptVersion& BakSysVersion() { return bakSys; };
	public:
		static ApiVersionInfo& Instance();
	public:
	protected:
		ApiVersionInfo();
	private:
		SptVersion apiVersion;
		SptVersion appVersion;
		SalComVersion lcdVersion;
		SalComVersion virlcdVersion;
		SptVersion cmmLiteVer;
		SalComVersion other[20];
		SptVersion boot0;
		SptVersion uboot;
		SptVersion mainSys;
		SptVersion bakSys;
	};
}

#endif // !APIVERSION_H
