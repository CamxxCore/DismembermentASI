#pragma once

struct MemAddr
{
	MemAddr() : MemAddr(nullptr) {}

	MemAddr(uintptr_t address) : addr(address) {}

	MemAddr(void * obj) : MemAddr(reinterpret_cast<uintptr_t>(obj)) {}

	uintptr_t addr;

	MemAddr add(MemAddr m) const
	{
		return MemAddr(addr + m.addr);
	}

	operator uintptr_t() const
	{
		return addr;
	}
};
