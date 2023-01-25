#include "..\stdafx.h"
#include <locale>

HMODULE Utility::GetActiveModule()
{
	HMODULE hModule = NULL;

	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		reinterpret_cast<LPCSTR>(&GetActiveModule),
		&hModule);

	return hModule;
}

std::string Utility::GetModuleName(HMODULE hModule)
{
	TCHAR inBuf[MAX_PATH];

	if (!hModule)
		hModule = GetActiveModule();

	GetModuleFileName(hModule, inBuf, sizeof inBuf);

	auto str = std::string(inBuf);

	auto seperator = str.find_last_of("\\");

	if (seperator != std::string::npos)
		seperator += 1;

	return str.substr(seperator, str.find_last_of(".") - seperator);
}

std::string Utility::GetWorkingDirectory()
{
	TCHAR inBuf[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, inBuf);

	return std::string(inBuf);
}

std::string Utility::GetShortTimeString()
{
	time_t t = time(NULL);

	struct tm timeinfo;

	localtime_s(&timeinfo, &t);

	return FormatString("%02d:%02d:%02d",
		timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
}

bool Utility::FileExists(std::string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void Utility::SplitString(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
	tokens.push_back(str);

	auto splitLen = splitBy.size();

	while (true)
	{
		auto frag = tokens.back();

		auto splitAt = frag.find(splitBy);

		if (splitAt == std::string::npos)
		{
			break;
		}

		tokens.back() = frag.substr(0, splitAt);

		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}
