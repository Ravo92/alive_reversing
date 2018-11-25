#pragma once

#include "FunctionFwd.hpp"
#include "DynamicArray.hpp"
#include "BitField.hpp"

class BaseGameObject
{
public:
    enum Types : __int16
    {
        eNone = 0,
        eScreenManager = 6,
        eBackgroundAnimation = 7,
        eTimedMine = 10,
        eBrewMachine = 13,
        eDDCheat = 19,
        eGrinder = 30,
        eLaughingGas = 31,
        eDoor = 33,
        eDoorLock = 34,
        eBird = 35,
        eGameSpeak = 38,
        eElectrocute = 39,
        eType_45 = 45,
        eBaseBomb = 46,
        eRockSpawner = 48,
        eFleech = 50,
        eItemCount = 53,
        eFlyingSlig = 54,
        eLockedSoul = 61,
        eGreeter = 64,
        eGlukkon_67 = 67,
        eHelpPhone = 68,
        eGrenadeMachine_66 = 66,
        eType_Abe = 69,
        eType_75 = 75,
        ePulley = 76,
        eType_78 = 78,
        eResourceManager = 79,
        eAntiChant = 83,
        eMeat = 84,
        eMeatSack = 85,
        eText = 87,
        eMine = 88,
        eGreeterBody = 91,
        eMusicController = 93,
        eMusicTrigger = 94,
        ePauseMenu = 95,
        eParamite = 96,
        eFG1 = 101, 
        ePullRope = 103,
        eRock = 105,
        eRockSack = 106,
        eMudokon_110 = 110,
        eRedLaser = 111,
        eScrab_112 = 112,
        eScreenClipper = 114,
        eMainMenuTransistion = 116,
        eScreenShake = 118,
        eGate = 122,
        eSnoozParticle = 124,
        eSlig_125 = 125,
        eSlog = 126,
        eSlurg = 129,
        eParticle = 134,
        eLever = 139,
        eTrapDoor = 142,
        eUXB = 143,
        eWeb = 146,
        eType_148 = 148,
        eCameraSwapper = 149,


        eDebugHelper = 1001, // NOTE: Not part of the original game - a debug helper only
        eDebugConsole = 1002,
        eDebugPathRenderer = 1003,
    };

    enum Options
    {
        // bit 00 = 0x001 = BaseGameObject couldn't add to list / it unsets inverse of 0xF80A / 0b1111100000001010
        eListAddFailed = 0x001,

        // bit 01 = 0x002 = do update ?
        eUpdatable = 0x002,

        // bit 02 = 0x004 = dead
        eDead = 0x004,

        // bit 03 = 0x008 = render
        eDrawable = 0x008,

        // bit 04 = 0x010 = set by BaseAnimatedWithPhysicsGameObject
        eIsBaseAnimatedWithPhysicsObj = 0x010,

        // bit 05 = 0x020 = set by BaseAliveGameObject
        eIsBaseAliveGameObject = 0x020,

        // bit 06 = 0x040 = set by ChantSuppressor::ctor_466350 / MovingBomb::ctor_46FD40 - explodable?
        eCanExplode = 0x040,

        // bit 07 = 0x080 = set by Uxb::ctor_4DE9A0 = pressable ?
        eInteractive = 0x080,

        // bit 08 = 0x100 = ?
        eBit08 = 0x100,

        // bit 09 = 0x200 = still update when the camera is changing
        eUpdateDuringCamSwap = 0x200,

        // bit 10 = 0x400 = can never be removed
        eCantKill = 0x400,

        // bit 11 = 0x800 = ?
        eBit11 = 0x800,

        // bit 12 = 0x1000 = ?
        eBit12 = 0x1000,

    };

    // Order must match VTable
    virtual void VDestructor(signed int) = 0; // Not an actual dtor because the generated compiler code has the param to determine if heap allocated or not
    virtual void VUpdate();
    virtual void VRender(int** pOrderingTable);
    virtual void VScreenChanged();
    virtual void vnullsub_4DC0F0();
    virtual int GetSaveState_4DC110(BYTE* pSaveBuffer);

    EXPORT void ScreenChanged_4DC0A0();

    EXPORT BYTE** Add_Resource_4DC130(DWORD type, int resourceID);
    EXPORT void BaseGameObject_ctor_4DBFA0(__int16 bAddToObjectList, signed __int16 resourceArraySize);
    EXPORT void BaseGameObject_dtor_4DBEC0();

    EXPORT static int __stdcall Find_Flags_4DC170(int objectId);
public:
    Types field_4_typeId;
    BitField16<Options> field_6_flags;
    int field_8_object_id;
    int field_C_objectId;
    DynamicArrayT<BYTE*> field_10_resources_array;
    int field_1C_update_delay;
};
ALIVE_ASSERT_SIZEOF(BaseGameObject, 0x20);

ALIVE_VAR_EXTERN(DynamicArrayT<BaseGameObject>*, gBaseGameObject_list_BB47C4);
