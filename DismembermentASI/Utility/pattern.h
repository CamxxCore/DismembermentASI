#pragma once

template <class T>
class Pattern
{
public:
	inline Pattern(const std::string_view pattern) : pattern(pattern.data())
	{
		bSuccess = getPattern();
	}

	inline T get(ptrdiff_t offset = 0)
	{
		return pResult + offset;
	}
	inline T rip(ptrdiff_t offset = 0)
	{
		auto pReloffset = *reinterpret_cast<int32_t*>(pResult + offset) + sizeof(int32_t);
		return pResult + offset + pReloffset;
	}

	bool bSuccess;

private:
	bool getPattern()
	{
		const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(GetModuleHandle(nullptr));
		const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<uintptr_t>(dosHeader) + dosHeader->e_lfanew);

		static const uintptr_t moduleBase = static_cast<uintptr_t>(ntHeaders->OptionalHeader.ImageBase);
		static const uintptr_t moduleEnd = moduleBase + static_cast<uintptr_t>(ntHeaders->OptionalHeader.SizeOfImage);

		uintptr_t address = FindPattern(moduleBase, moduleEnd, pattern);
		if (address != NULL)
		{
			pResult = reinterpret_cast<T>(address);
			return true;
		}

		pResult = NULL;
		return false;
	}

	static uintptr_t FindPattern(uintptr_t startAddress, uintptr_t endAddress, const char* mask)
	{
		std::vector<std::pair<uint8_t, bool>> pattern;

		for (size_t i = 0; i < strlen(mask);)
		{
			if (mask[i] != '?')
			{
				pattern.emplace_back(static_cast<uint8_t>(strtoul(&mask[i], nullptr, 16)), false);
				i += 3;
			}
			else
			{
				pattern.emplace_back(0x00, true);
				i += 2;
			}
		}

		const auto dataStart = reinterpret_cast<const uint8_t*>(startAddress);
		const auto dataEnd = dataStart + endAddress + 1;

		auto sig = std::search(dataStart, dataEnd, pattern.begin(), pattern.end(),
			[](uint8_t currentByte, std::pair<uint8_t, bool> Pattern)
			{
				return Pattern.second || (currentByte == Pattern.first);
			});

		if (sig == dataEnd)
			return NULL;

		return std::distance<const uint8_t*>(dataStart, sig) + startAddress;
	}

	const char* pattern;
	T pResult;
};

class BytePattern : public Pattern<BYTE*>
{
public:
	inline BytePattern(const std::string_view pattern) : Pattern<BYTE*>(pattern.data()) {}
};
