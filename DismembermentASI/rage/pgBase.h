/*
* This file is part of the CitizenFX project - http://citizen.re/
*
* See LICENSE and MENTIONS in the root of the source tree for information
* regarding licensing.
*/

#pragma once
namespace rage
{
	struct pgPtrRepresentation
	{
		uint64_t pointer : 60;
		uint64_t blockType : 4;
	};

	struct BlockMap;

	template<typename T, bool Physical = false>
	class pgPtr
	{
		union
		{
			pgPtrRepresentation on_disk;
			T* pointer;
		};

	public:
		pgPtr()
		{
			pointer = nullptr;
		}

		T* operator->() const
		{
			return pointer;
		}

		T* operator*() const
		{
			return pointer;
		}

		T operator[](int idx) const
		{
			return pointer[idx];
		}

		pgPtr operator=(T* other)
		{
			pointer = other;
			return *this;
		}

		pgPtr(const pgPtr& from)
		{
			on_disk = from.on_disk;
		}

		bool IsNull()
		{
			return (pointer == nullptr);
		}

		T* get(int index)
		{
			return &pointer[index];
		}
	};

	struct BlockMap
	{
		uint16_t virtualLen;
		uint16_t physicalLen;

		struct BlockInfo
		{
			uint32_t offset;
			void* data;
			uint32_t size;
		} blocks[128];
	};

	class pgBase : public datBase //0x0-0x10
	{
		pgPtr<BlockMap> m_blockMap;

	public:
		void SetBlockMap() { m_blockMap; }

		pgBase()
		{
			SetBlockMap();
		}

		virtual ~pgBase() { }
	}; static_assert(sizeof(pgBase) == 0x10, "pgBase is of wrong size");
}
