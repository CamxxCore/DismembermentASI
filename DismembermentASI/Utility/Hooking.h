#pragma once

template <typename T>
class Hook
{
public:
	Hook(PBYTE pbTarget, T func) : address(pbTarget), fn(func) { }
	virtual ~Hook();
	virtual void remove() = 0;
	PBYTE address;
	T fn;
};

template <typename T>
Hook<T>::~Hook()
{
}

template <typename T>
class CallHook : public Hook<T>
{
public:
	CallHook(PBYTE addr, T func) : Hook<T>(addr, func) { }
	~CallHook();
	void remove() override;
};

template <typename T>
void CallHook<T>::remove()
{
	*reinterpret_cast<int32_t*>(address + 1) = static_cast<int32_t>((intptr_t)fn - (intptr_t)address - 5);
}

template <typename T>
CallHook<T>::~CallHook()
{
	CallHook<T>::remove();
}

template <typename T>
class VirtualHook : public Hook<T>
{
public:
	VirtualHook(PBYTE pbTarget, T func) : Hook<T>(pbTarget, func) { }
	~VirtualHook();
	void remove() override;
};

template <typename T>
void VirtualHook<T>::remove()
{
	*reinterpret_cast<PBYTE*>(address) = (PBYTE)fn;
}

template <typename T>
VirtualHook<T>::~VirtualHook()
{
	remove();
}

class HookManager
{
public:
	template <typename T>
	static CallHook<T> *SetCall(PBYTE address, T target)
	{
		T orig = reinterpret_cast<T>(*reinterpret_cast<int *>(address + 1) + (address + 5));

		HMODULE hModule = GetModuleHandle(NULL);

		auto pFunc = AllocateFunctionStub(hModule, (void*)target, 0);

		*reinterpret_cast<BYTE*>(address) = 0xE8;

		*reinterpret_cast<int32_t*>(address + 1) = static_cast<int32_t>((intptr_t)pFunc - (intptr_t)address - 5);

		return new CallHook<T>(address, orig);
	}

	template <typename T>
	static VirtualHook<T> *HookVirtual(PBYTE address, T target)
	{
		T orig = *reinterpret_cast<T*>(address);

		HMODULE hModule = GetModuleHandle(NULL);

		auto pFunc = AllocateFunctionStub(hModule, (void*)target, 0);

		*reinterpret_cast<void**>(address) = pFunc;

		return new VirtualHook<T>(address, orig);
	}

	static PVOID AllocateFunctionStub(PVOID origin, PVOID function, int type);

	static LPVOID FindPrevFreeRegion(LPVOID pAddress, LPVOID pMinAddr, DWORD dwAllocationGranularity);
};
