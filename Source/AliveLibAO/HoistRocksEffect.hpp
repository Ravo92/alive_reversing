#pragma once

#include "../AliveLibCommon/FunctionFwd.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Map.hpp"

namespace AO {

struct Path_Hoist final : public Path_TLV
{
    enum class Type : s16
    {
        eNextFloor = 0,
        eNextEdge = 1,
        eOffScreen = 2,
    };
    Type field_18_hoist_type;

    enum class GrabDirection : s16
    {
        eFacingLeft = 0,
        eFacingRight = 1,
        eFacingAnyDirection = 2,
    };
    GrabDirection field_1A_grab_direction;

    s16 field_1C_switch_id;

    s16 field_1E_pad;
};
ALIVE_ASSERT_SIZEOF(Path_Hoist, 0x20);

class HoistParticle final : public BaseAnimatedWithPhysicsGameObject
{
public:
    HoistParticle(FP xpos, FP ypos, FP scale, s32 frameTableOffset);

    virtual void VUpdate() override;

    EXPORT void VUpdate_431BD0();

    s32 field_D4[4];
    s16 field_E4_bHitGround;
    s16 field_E6_pad;
};
ALIVE_ASSERT_SIZEOF(HoistParticle, 0xE8);

class HoistRocksEffect final : public BaseGameObject
{
public:
    HoistRocksEffect(Path_Hoist* pTlv, s32 tlvInfo);
    ~HoistRocksEffect();

    virtual void VScreenChanged() override;

    EXPORT void VScreenChanged_431AF0();

    virtual void VUpdate() override;

    EXPORT void VUpdate_431860();

    FP field_10_xpos;
    FP field_14_ypos;
    s32 field_18_tlvInfo;
    s32 field_1C_never_used[4];
};
ALIVE_ASSERT_SIZEOF(HoistRocksEffect, 0x2C);

} // namespace AO
