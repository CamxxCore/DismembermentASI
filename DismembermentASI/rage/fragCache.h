#pragma once

namespace rage
{
	struct fragCache
	{
		crSkeletonData * m_skeleton; //0x0-0x8
		Matrix44 * m_pUnkMatrices; //0x8-0x10
		Matrix44 * m_pPoseMatrices; //0x10-0x18
		Matrix44 * m_pDefaults; //0x18-0x20
		int m_boneCount;
	private:
		char pad0[0x8];
	public:
		int m_unk; // hash or something?

		fragCache()
		{
			memset(this, 0x0, sizeof(fragCache));
		}
	};
}
