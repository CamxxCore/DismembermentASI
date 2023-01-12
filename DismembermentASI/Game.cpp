#include "stdafx.h"
#include "Game.h"

AddressMgr g_addresses;

bool Game::InititalizeGame()
{
	auto addresses = g_addresses.getOrCreate("game");

	#pragma region getScriptEntityIndex

	auto pattern = BytePattern((BYTE*)"\x49\x2B\x00\x49\x63\x48\x14", "xxxxxxx");

	if ( !pattern.bSuccess ) {

		LOG("Failed to find getScriptEntityIndex pattern.");
		return false;
	}

	auto result = pattern.get(-95);

	addresses->insert("getScriptEntityIndex", result);

	#pragma endregion

	#pragma region getBoneIndexForId

	pattern = BytePattern((BYTE*)"\xBA\x00\x00\x00\x00\x48\x8B\xCE\xE8\x00\x00\x00\x00\x8B\xD0", "x????xxxx????xx");

	if ( !pattern.bSuccess ) {

		LOG("Failed to find getBoneIndexForId pattern.");
		return false;
	}

	result = pattern.get(9);

	addresses->insert("getBoneIndexForId", result + *(int32_t*)result + 4);

	#pragma endregion

	#pragma region getEntityFragCache

	pattern = BytePattern((BYTE*)"\x0F\xBA\x77\x00\x00\x44\x8B\xD3", "xxx??xxx");

	if ( !pattern.bSuccess ) {

		LOG("Failed to find getEntityFragCache pattern.");
		return false;
	}

	result = pattern.get(-4);

	addresses->insert("getEntityFragCache", result + *(int32_t*)result + 4);

	#pragma endregion

	#pragma region getLastSiblingBoneIndex

	pattern = BytePattern((BYTE*)"\x33\xD2\x45\x0F\xBF\x48\x00", "xxxxxx?");

	if (!pattern.bSuccess) {

		LOG("Failed to find getLastSiblingBoneIndex pattern.");
		return false;
	}

	result = pattern.get(-21);

	addresses->insert("getLastSiblingBoneIndex", result);

	#pragma endregion

	return true;
}
