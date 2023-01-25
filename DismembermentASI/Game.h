#pragma once

typedef rage::CEntity* CEntity;

namespace Game {

	bool InititalizeGame();

	inline BYTE* GetScriptGuidForEntityIndex(int handle)
	{
		return ((BYTE*(__fastcall*)(int))
			(*g_addresses.get("game"))["getScriptGuidForEntityIndex"].addr)(handle);
	}

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

	inline int GetLastSiblingBoneIndex(rage::fragCache* fragCache, uint16_t boneId)
	{
		return ((int(__fastcall*)(rage::fragCache*, uint16_t))
			(*g_addresses.get("game"))["getLastSiblingBoneIndex"].addr)(fragCache, boneId);
	}
}
