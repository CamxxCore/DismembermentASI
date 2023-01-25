#pragma once

//credits to Yimura and contributers for the classes https://github.com/Yimura/GTAV-Classes

enum class ePedBoneType
{
    HEAD,
    L_FOOT,
    R_FOOT,
    L_ANKLE,
    R_ANKLE,
    L_HAND,
    R_HAND,
    NECK,
    ABDOMEN
};

class CPedBoneInfo
{
public:
    rage::fvector3 modelCoords;
    char pad0[4];
};
static_assert(sizeof(CPedBoneInfo) == 0x10);


class CPedOxygenInfo
{
public:
    char m_unk0000[632]; //0x0000
    float m_oxygenTime; //0x0278
}; //Size: 0x027C
static_assert(sizeof(CPedOxygenInfo) == 0x27C);

enum class eGameState : int32_t
{
    Invalid = -1,
    Playing,
    Died,
    Arrested,
    FailedMission,
    LeftGame,
    Respawn,
    InMPCutscene
};

#pragma pack(push, 4)
class CPlayerInfo
{
public:
    char pad_0000[32]; //0x0000
    char pad_152[152]; //0x0020
    char pad_00B8[184]; //0x00B8
    float m_swimSpeed; //0x0170
    char pad_0174[20]; //0x0174
    uint32_t m_waterProof; //0x0188
    char pad_018C[76]; //0x018C
    eGameState m_gameState; //0x01D8
    char pad_01DC[12]; //0x01DC
    class CPed *m_ped; //0x01E8
    char pad_01F0[40]; //0x01F0
    uint32_t m_frameFlags; //0x0218
    char pad_021C[52]; //0x021C
    uint32_t m_player_controls; //0x0250
    char pad_0254[1256]; //0x0254
    float m_wanted_can_change; //0x073C
    char pad_0740[144]; //0x0740
    float m_wantedLevelDifficulty; //0x07D0 
    char pad_07D4[52]; //0x07D4
    float m_wantedLevelMultiplier; //0x0808
    char pad_080C[100]; //0x080C
    uint32_t m_npcIgnore; //0x0870
    char pad_0874[12]; //0x0874
    bool m_isWanted; //0x0880
    char pad_0881[7]; //0x0881
    uint32_t m_wantedLevel; //0x0888
    uint32_t m_wantedLevelDisplay; //0x088C
    char pad_0890[1120]; //0x0890
    float m_runSpeed; //0x0CF0
    float m_stamina; //0x0CF4
    float m_staminaRegen; //0x0CF8
    char pad_0CFC[16]; //0x0CFC
    float m_weaponDamageMultiplier; //0x0D0C
    float m_weaponDefenceMultiplier; //0x0D10
    char pad_0D14[4]; //0x0D14
    float m_meleeWeaponDamageMultiplier; //0x0D18
    float m_meleeDamageMultiplier; //0x0D1C
    float m_meleeDefenceMultiplier; //0x0D20
    char pad_0D24[8]; //0x0D24
    float m_meleeWeaponDefenceMultiplier; //0x0D2C
}; //Size: 0x0D30
static_assert(sizeof(CPlayerInfo) == 0xD30);
#pragma pack(pop)

#pragma pack(push, 1)
class CPed : public rage::CPhysical
{
public:
    char pad0[20];
    rage::fvector3 m_velocity; //0x0300
    char m_unk030C[260]; //0x030C
    CPedBoneInfo m_boneInfo[9]; //0x0410
    char m_unk04A0[2160]; //0x04A0
    void *m_vehicle; //0x0D10
    char m_unk0D18[896]; //0x0D18
    uint32_t m_pedType; //0x1098
    char m_unk109C[4]; //0x109C
    CPedOxygenInfo* m_oxygenInfo; //0x10A0
    CPlayerInfo *m_playerInfo; //0x10A8
    void* m_inventory; //0x10B0
    void *m_weaponManager; //0x10B8
    char m_unk10C0[892]; //0x10C0
    uint8_t m_seatbelt; //0x143C
    char m_unk143D[13]; //0x143D
    uint8_t m_canSwitchWeapon; //0x144A
    uint8_t m_pedTaskFlag; //0x144B
    char m_unk144C[4]; //0x144C
    uint8_t m_forcedAim; //0x1450 
    char m_unk1451[187]; //0x1451
    float m_armor; //0x150C
    float unk_healthThreshold; //0x1510
    float m_fatiguedHealthThreshold; //0x1514
    float m_injuredHealthThreshold; //0x1518
    float m_dyingHealthThreshold; //0x151C
    float m_hurtHealthThreshold; //0x1520
    char m_unk1524[240]; //0x1524
    uint16_t m_cash; //0x1614

    uint32_t getPedType() { return m_pedType << 11 >> 25; }

    rage::fvector3 GetBoneCoords(ePedBoneType type)
    {
        rage::fvector3 worldCoords;
        modelToWorld(m_boneInfo[(uint32_t)type].modelCoords, worldCoords);
        return worldCoords;
    }

}; //Size: 0x1616
static_assert(sizeof(CPed) == 0x1616, "CPed is of wrong Size!");
#pragma pack(pop)