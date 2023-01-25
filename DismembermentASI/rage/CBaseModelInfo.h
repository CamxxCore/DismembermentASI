#pragma once

namespace rage
{
#pragma pack(push,8)
    class fwArchetypeDef
    {
    public:
        virtual ~fwArchetypeDef() = 0;
        virtual int GetTypeIdentifier() = 0;

        float m_lodDist; //0x0008
        uint32_t m_flags; //0x000C
        uint32_t m_specialAttribute; //0x0010
        char pad_0014[12]; //0x0014
        fvector4 m_boundingBoxMin; //0x0020
        fvector4 m_boundingBoxMax; //0x0030
        fvector4 m_boundingSphereCenter; //0x0040
        float m_boundingSphereRadius; //0x0050
        float m_hdTextureDistance; //0x0054
        uint32_t m_nameHash; //0x0058
        uint32_t m_textureDictionary; //0x005C
        uint32_t m_clipDictionaryHash; //0x0060
        uint32_t m_drawableDictionaryHash; //0x0064
        uint32_t m_physicsDictionaryHash; //0x0068
        enum eAssetType : uint32_t
        {
            ASSET_TYPE_UNINITIALIZED = 0,
            ASSET_TYPE_FRAGMENT = 1,
            ASSET_TYPE_DRAWABLE = 2,
            ASSET_TYPE_DRAWABLEDICTIONARY = 3,
            ASSET_TYPE_ASSETLESS = 4,
        } m_assetType; //0x006C
        uint32_t m_assetNameHash; //0x0070
        uint64_t* m_extensions; //0x0078
        uint16_t unk_0080; //0x0080
        char pad_0082[12]; //0x0082
    }; //Size: 0x0090
    static_assert(sizeof(fwArchetypeDef) == 0x90);
#pragma pack(pop)

#pragma pack(push,8)
    class fwArchetype : public datBase
    {
    public:
        virtual void Initialize() = 0;
        virtual void InitializeFromArchetypeDef(uint32_t mapTypeStoreIdx, fwArchetypeDef* archetypeDef, bool) = 0;
        virtual class fwEntity* CreateEntity() = 0;

        char pad_0008[16]; //0x0008
        int32_t m_hash; //0x0018
        char unk_001C[4]; //0x001C
        fvector3 m_boundingSphereCenter; //0x0020
        float m_boundingSphereRadius; //0x002C
        fvector3 m_AABBMin; //0x0030
        float m_lodDistance; //0x003C
        fvector3 m_AABBMax; //0x0040
        float m_hdTextureDistance; //0x004C
        uint32_t m_flags; //0x0050
        char unk_0054[4]; //0x0054
        uint64_t unk_0058; //0x0058
        char unk_0060[4]; //0x0060
        uint32_t m_assetIndex; //0x0064
        uint16_t unk_0068; //0x0068
        uint16_t unk_006A; //0x006A
    };
    static_assert(sizeof(fwArchetype) == 0x70);
#pragma pack(pop)
}
enum class eModelType : uint8_t
{
    Invalid,
    Object,
    MLO,
    Time,
    Weapon,
    Vehicle,
    Ped,
    Destructable,
    WorldObject = 33,
    Sprinkler = 35,
    Unk65 = 65,
    EmissiveLOD = 67,
    Plant = 129,
    LOD = 131,
    Unk132 = 132,
    Unk133 = 133,
    OnlineOnlyPed = 134,
    Building = 161,
    Unk193 = 193
};

#pragma pack(push, 8)
class CBaseModelInfo : public rage::fwArchetype
{
public:
    char pad_0070[8]; //0x0070
    uint64_t unk_0078; //0x0078
    uint64_t unk_0080; //0x0080
    char pad_0088[8]; //0x0088
    uint64_t unk_0090; //0x0090
    char pad_0098[5]; //0x0098
    eModelType m_modelType; //0x009D
    char pad_009E[6]; //0x009E
    uint64_t unk_00A8; //0x00A8
}; //Size: 0x00B0
static_assert(sizeof(CBaseModelInfo) == 0xB0, "CBaseModelInfo is of wrong size!");
#pragma pack(pop)