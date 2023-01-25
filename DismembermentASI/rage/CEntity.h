#pragma once

//credits to Yimura and contributers for the classes https://github.com/Yimura/GTAV-Classes

namespace rage
{
#pragma pack(push, 1)
    class CNavigation
    {
    public:
        char pad_0000[16]; //0x0000
        void* m_damp; //0x0010
        char pad_0018[8]; //0x0018
        fmatrix44 m_transformationMatrix;

        fvector3* get_position()
        {
            return reinterpret_cast<rage::fvector3*>(&m_transformationMatrix.rows[3]);
        }

        void model_to_world(const rage::fvector3& model_coords, rage::fvector3& worldCoords)
        {
            worldCoords.x = model_coords.x * m_transformationMatrix.data[0][0] + model_coords.y * m_transformationMatrix.data[1][0] + model_coords.z * m_transformationMatrix.data[2][0] + m_transformationMatrix.data[3][0];
            worldCoords.y = model_coords.x * m_transformationMatrix.data[0][1] + model_coords.y * m_transformationMatrix.data[1][1] + model_coords.z * m_transformationMatrix.data[2][1] + m_transformationMatrix.data[3][1];
            worldCoords.z = model_coords.x * m_transformationMatrix.data[0][2] + model_coords.y * m_transformationMatrix.data[1][2] + model_coords.z * m_transformationMatrix.data[2][2] + m_transformationMatrix.data[3][2];
        }
    }; //Size: 0x0060
    static_assert(sizeof(CNavigation) == 0x60);

    template <class T>
    class fwRefAwareBaseImpl : public T
    {
    private:
        void *m_ref; // 0x08
    };

    class fwRefAwareBase : public fwRefAwareBaseImpl<datBase>
    {
    };
    static_assert(sizeof(fwRefAwareBase) == 0x10);

    class fwExtensibleBase : public fwRefAwareBase
    {
    public:
        virtual bool is_of_type(std::uint32_t hash) = 0;
        virtual uint32_t const &get_type() = 0;

        void* m_extensionContainer; // 0x0010
        void *m_extensibleUnk; // 0x0018

    }; //Size: 0x0020
    static_assert(sizeof(fwExtensibleBase) == 0x20);

#pragma pack(push, 4)
    class fwDrawData
    {
    public:
        std::uint64_t m_unk0;
        std::uint64_t m_unk8;
        char pad10[8];
        std::uint32_t m_unk18;
        std::uint32_t m_unk1C;
        std::uint64_t m_unk20;
        std::uint32_t m_unk28;
    };
    static_assert(sizeof(fwDrawData) == 0x2C);
#pragma pack(pop)

#pragma pack(push, 1)
    class fwEntity : public fwExtensibleBase
    {
    public:
        CBaseModelInfo* m_modelInfo; //0x0020
        char pad28; //0x0028
        uint8_t m_entityType; //0x0029
        char pad2A[2]; //0x002A
        uint8_t m_invisible; //0x002C
        char pad2D[3]; //0x002D
        CNavigation *m_navigation; //0x0030
        char pad38[16]; //0x0038
        fwDrawData* m_drawData; //0x0048
        char pad50[16]; //0x0050
        fmatrix44 m_transformationMatrix; //0x0060
        uint64_t m_unkA0; //0x00A0
        uint32_t m_unkA8; //0x00A8
        uint32_t m_unkAC; //0x00AC
        uint32_t m_unkB0; //0x00B0
        char padB4[4]; //0x00B4
        uint8_t byteB8; //0x00B8

        fvector3* GetPosition()
        {
            return reinterpret_cast<fvector3*>(&m_transformationMatrix.rows[3]);
        }

        void modelToWorld(const fvector3& model_coords, fvector3& worldCoords)
        {
            worldCoords.x = model_coords.x * m_transformationMatrix.data[0][0] + model_coords.y * m_transformationMatrix.data[1][0] + model_coords.z * m_transformationMatrix.data[2][0] + m_transformationMatrix.data[3][0];
            worldCoords.y = model_coords.x * m_transformationMatrix.data[0][1] + model_coords.y * m_transformationMatrix.data[1][1] + model_coords.z * m_transformationMatrix.data[2][1] + m_transformationMatrix.data[3][1];
            worldCoords.z = model_coords.x * m_transformationMatrix.data[0][2] + model_coords.y * m_transformationMatrix.data[1][2] + model_coords.z * m_transformationMatrix.data[2][2] + m_transformationMatrix.data[3][2];
        }
    };
    static_assert(sizeof(fwEntity) == 0xB9);
#pragma pack(pop)

    class CEntity : public fwEntity
    {
    public:
        char padB9[7];
        uint32_t m_unkC0;
        uint32_t m_unkC4;
        uint32_t m_unkC8;
        uint32_t m_unkCC;
    };
    static_assert(sizeof(CEntity) == 0xD0, "CEntity is of Wrong size!");

    class CDynamicEntity : public CEntity
    {
    public:
        void *m_netObject; //0x00D0
        char padD8[16];
        uint64_t m_unkE8;
    };
    static_assert(sizeof(CDynamicEntity) == 0xF0);
    
#pragma pack(push, 1)
    class CPhysical : public CDynamicEntity
    {
    public:
        char pad0[144];
        uint64_t m_unk180;
        uint32_t m_damage_bits; //0x0188
        uint8_t m_hostility; //0x018C
        char pad18D[3];
        uint8_t byte190;
        char pad191[3];
        uint32_t m_unk194;
        char pad198[232];
        float m_health; //0x0280
        float m_maxhealth; //0x0284
        void* m_attackers;
        char pad2B0[72];
        uint64_t m_unk2F8;
        uint64_t m_unk300;
        uint32_t m_unk308;
    };
    static_assert(sizeof(CPhysical) == 0x2EC);
#pragma pack(pop)
}