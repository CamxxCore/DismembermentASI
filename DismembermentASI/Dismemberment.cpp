#include "stdafx.h"
#include "Game.h"
#include <mutex>

using namespace Game;

#define ARR_SIZE 256

#define DLL_EXPORT extern "C" __declspec( dllexport )

typedef __int64 (__fastcall *fragCache__DrawSkeleton)(rage::fragCache*, void*, int, CBaseModelInfo*, int, __int64, uint8_t, uint8_t, short, short, float);

static std::vector<CallHook<fragCache__DrawSkeleton>*> g_drawFunctions;

struct DrawSkeletonInfo
{
	/**
	 * id of first bone in the skeleton that will be drawn.
	 */
	int startBoneId;

	/**
	 * id of last bone in hierarchy.
	 */
	int endBoneId;
};

std::map<Ped, DrawSkeletonInfo> g_pedList;

std::mutex g_mutex;

typedef CPed* Cped;

/**
 * Main function where the skeleton is drawn by the engine.
 */
__int64 fragCache__DrawSkeleton_Hook(rage::fragCache* fragCache, void * drawBuffer, int isFragment, CBaseModelInfo* modelInfo, int bUnk, __int64 unkBoneIndex, uint8_t unkIdx, uint8_t subFragCache, short startBoneIndex, short lastSiblingIndex, float drawScale)
{
	
	std::unique_lock<std::mutex> lock(g_mutex);

	for (auto it = g_pedList.begin(); it != g_pedList.end();)
	{
		auto pedAddress = (Cped)GetScriptGuidForEntityIndex(it->first);

		if (!pedAddress)
		{
			it = g_pedList.erase(it);
		}

		else
		{
			auto pedCache = GetEntityFragCache(pedAddress);

			if (pedCache && pedCache == fragCache)
			{
				if (it->second.startBoneId != -1) 
				{
					startBoneIndex = fragCache->m_skeleton->GetBoneIndexForId(it->second.startBoneId);
					
					if (it->second.endBoneId != -1)
						lastSiblingIndex = fragCache->m_skeleton->GetBoneIndexForId(it->second.endBoneId);

					else
						lastSiblingIndex = GetLastSiblingBoneIndex(fragCache, startBoneIndex);
				}

				drawScale = 0.0f;

				break;
			}

			++it;
		}
	}

	return g_drawFunctions[0]->fn(fragCache, drawBuffer, isFragment, modelInfo, bUnk, unkBoneIndex, unkIdx, subFragCache, startBoneIndex, lastSiblingIndex, drawScale);
}

void initialize() 
{

	if ( !InititalizeGame() ) {

		LOG("Failed to initialize game. Cannot continue.");
		return;
	}

	auto pattern = BytePattern("0F 18 ? 48 8B CA");

	if (!pattern.bSuccess) {

		LOG("Failed to find hook pattern (fragCache::DrawSkeleton). Cannot continue.");
		return;
	}

	auto address = pattern.get(0x170);


	g_drawFunctions.push_back(HookManager::SetCall<fragCache__DrawSkeleton>((PBYTE)address, fragCache__DrawSkeleton_Hook));

	pattern = BytePattern("44 88 44 24 ? 45 8B C4");

	if (!pattern.bSuccess) {

		LOG("Failed to find hook pattern (fragCache::DrawSkeleton #2). Cannot continue.");
		return;
	}

	g_drawFunctions.push_back(HookManager::SetCall<fragCache__DrawSkeleton>((PBYTE)pattern.get(-0x9B), fragCache__DrawSkeleton_Hook));

	g_drawFunctions.push_back(HookManager::SetCall<fragCache__DrawSkeleton>((PBYTE)pattern.get(11), fragCache__DrawSkeleton_Hook));

	g_drawFunctions.push_back(HookManager::SetCall<fragCache__DrawSkeleton>((PBYTE)pattern.get(0x7D), fragCache__DrawSkeleton_Hook));
}

DLL_EXPORT void AddBoneDraw(Ped handle, int start, int end)
{
	g_pedList[handle].startBoneId = start;
	g_pedList[handle].endBoneId = end;
}

DLL_EXPORT void RemoveBoneDraw(Ped handle)
{
	std::unique_lock<std::mutex> lock(g_mutex);

	auto pair = g_pedList.find( handle );

	if (pair != g_pedList.end())
	{
		g_pedList.erase( handle );
	}
}

#ifdef _DEBUG
void scriptMain()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			Ped peds[ARR_SIZE];

			auto count = worldGetAllPeds(peds, ARR_SIZE);

			for (int i = 0; i < count; i++)
			{
				AddBoneDraw(peds[i], SKEL_Pelvis, -1);
			}
		}

		WAIT(0);
	}
}
#endif

void unload() {

	for (auto & function : g_drawFunctions)
	{
		delete function;
	}
}
