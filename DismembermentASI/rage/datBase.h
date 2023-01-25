#pragma once

namespace rage
{
	struct BlockMap;

	class datBase //0x0-0x8
	{
	public:
		virtual ~datBase() {}
	}; static_assert(sizeof(datBase) == 0x8, "datBase is of wrong size");

	typedef __m128 CVector;

	struct Matrix34
	{
		CVector right;
		CVector forward;
		CVector up;
	};

	struct Matrix44
	{
		CVector right;
		CVector forward;
		CVector up;
		CVector pos;
	};
}
