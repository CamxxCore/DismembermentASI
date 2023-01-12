#pragma once

namespace rage
{
	struct BlockMap;

	class datBase //0x0-0x8
	{
	public:
		virtual ~datBase() {}
	};

	typedef float CVector[4];

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
