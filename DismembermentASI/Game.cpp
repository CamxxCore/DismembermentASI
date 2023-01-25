#include "stdafx.h"
#include "Game.h"

AddressMgr g_addresses;

bool Game::InititalizeGame()
{
	auto addresses = g_addresses.getOrCreate("game");

	#pragma region getBoneIndexForId

	auto pattern = BytePattern("BA ? ? ? ? 48 8B CE E8 ? ? ? ? 8B D0");

	if ( !pattern.bSuccess ) {

		LOG("Failed to find getBoneIndexForId pattern.");
		return false;
	}

	auto result = pattern.rip(9);

	addresses->insert("getBoneIndexForId", result);

	#pragma endregion

	#pragma region getEntityFragCache

	pattern = BytePattern("0F BA 77 ? ? 44 8B D3");

	if ( !pattern.bSuccess ) {

		LOG("Failed to find getEntityFragCache pattern.");
		return false;
	}

	result = pattern.rip(-4);

	addresses->insert("getEntityFragCache", result);

	#pragma endregion

	#pragma region getLastSiblingBoneIndex

	pattern = BytePattern("33 D2 45 0F BF 48 ?");

	if (!pattern.bSuccess) {

		LOG("Failed to find getLastSiblingBoneIndex pattern.");
		return false;
	}

	result = pattern.get(-0x15);

	addresses->insert("getLastSiblingBoneIndex", result);

	#pragma endregion

	return true;
}
