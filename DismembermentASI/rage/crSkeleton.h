#pragma once

namespace rage
{
	struct crBone
	{
		int m_boneId; // unique hash ID for this bone
		int m_index; // index of this bone in the skeleton
	};

	struct crBoneData
	{
		Matrix34 m_offset; //0x0-0x30
		int16_t m_nextSiblingIndex; // 0x30-0x32
		int16_t m_parentBoneIndex; //0x32-0x34
		int m_unk; //0x34-0x38
		const char * m_boneName; //0x38-0x40
		int16_t m_unkIndex; // 0x40-0x42
		int16_t m_boneIndex; //0x42-0x44
		int16_t m_boneId; //0x44-0x48
		int32_t m_unk48; //0x48-0x4C
		int32_t m_unk4C; //0x4C-0x50

		crBoneData()
		{
			memset(this, 0x0, sizeof(crBoneData));
		}
	}; // sizeof=0x50

	class crSkeletonData : pgBase
	{
	public:
		virtual ~crSkeletonData() = 0;
		virtual __int64 m_xy() = 0;
		virtual void m_xz() = 0; // 'ERR_GEN_PAGE_1'

		pgPtr<crBone> m_boneMap; //0x10-0x18
		uint16_t m_size; //0x18-0x1A
		uint16_t m_count; //0x1A-0x1C
		uint32_t m_unk1C;//0x1C-0x20
		pgPtr<crBoneData> m_boneData; //0x20-0x28
		pgPtr<Matrix44> m_invertedTransforms; //0x28-0x30
		pgPtr<Matrix44> m_transformations; //0x30-0x38
		pgPtr<uint16_t> m_parentIndices; //0x38-0x40
		pgPtr<Matrix44> m_unkIndices; //0x40-0x48
		pgPtr<void> m_properties; //0x48-0x50 unk
		uint32_t m_unk50; //0x50-0x54
		uint32_t m_unk54; //0x54-0x58
		uint32_t m_unk58; //0x58-0x5C
		uint16_t m_unkCount; //0x5C
		uint16_t m_numBones; //0x5E-0x60
		uint16_t m_unkCount2; //0x60-0x62
		uint16_t m_unk62; //0x62-0x64
		uint32_t m_unk64; //0x64-0x68
		uint32_t m_unk68; //0x68-0x6C
		uint32_t m_unk6C; //0x6C-0x70

		const char * getBoneName(int boneIndex) const
		{
			if (boneIndex >= m_numBones) return 0;
			return m_boneData[boneIndex].m_boneName;
		}
	}; // sizeof=0x70
}
