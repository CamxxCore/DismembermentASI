#pragma once

class Utility
{
public:
	static HMODULE GetActiveModule();

	static std::string GetModuleName(HMODULE hModule);

	static std::string GetWorkingDirectory();

	static std::string GetShortTimeString();

	static bool FileExists(std::string fileName);

	static void SplitString(std::string str, std::string splitBy, std::vector<std::string>& tokens);

	template<typename ... Args>
	static std::string FormatString(const std::string& format, Args ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1);
	}
};
