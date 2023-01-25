#pragma once

typedef rage::CEntity* CEntity;

namespace Game {

	bool InititalizeGame();

	inline int GetBoneIndexForId(CEntity entity, uint16_t boneId) 
	{
		return ((int(__fastcall*)(CEntity, uint16_t))
			(*g_addresses.get("game"))["getBoneIndexForId"].addr)(entity, boneId);
	}

	inline rage::fragCache* GetEntityFragCache(CEntity entity) 
	{
		return ((rage::fragCache*(__fastcall*)(CEntity))
			(*g_addresses.get("game"))["getEntityFragCache"].addr)(entity);
	}

	inline int GetLastSiblingBoneIndex(rage::fragCache* fragCache, int boneId)
	{
		return ((int(__fastcall*)(rage::fragCache*, int))
			(*g_addresses.get("game"))["getLastSiblingBoneIndex"].addr)(fragCache, boneId);
	}
}
