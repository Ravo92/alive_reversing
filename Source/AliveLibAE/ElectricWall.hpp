#pragma once

#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Path.hpp"
#include "../AliveLibCommon/Function.hpp"

enum ElectricWallStartState : s16
{
    eOff_0 = 0,
    eOn_1 = 1,
};

struct Path_ElectricWall final : public Path_TLV
{
    Scale_short field_10_scale;
    s16 field_12_switch_id;
    ElectricWallStartState field_14_start_state;
    s16 field_16_pad;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_ElectricWall, 0x18);

class ElectricWall final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    ElectricWall(Path_ElectricWall* pTlv, s32 tlvInfo);
    ~ElectricWall();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

private:
    s32 field_F4_tlvInfo = 0;
    s16 field_F8_switch_id = 0;
    ElectricWallStartState field_FA_start_state = ElectricWallStartState::eOff_0;
    s32 field_FC_sound_timer = 0;
};
ALIVE_ASSERT_SIZEOF(ElectricWall, 0x100);
