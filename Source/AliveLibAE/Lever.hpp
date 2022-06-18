#pragma once

#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Path.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "SwitchStates.hpp"

enum class LeverState : s16
{
    eWaiting_0 = 0,
    ePulled_1 = 1,
    eFinished_2 = 2
};

enum class LeverSoundType : s16
{
    eNone = 0,
    eWell_1 = 1,
    eUnknown_2 = 2,
    eDoor_3 = 3,
    eElectricWall_4 = 4,
    eSecurityOrb_5 = 5,
    eLift_6 = 6
};

enum class LeverSoundDirection : s16
{
    eLeftAndRight_0 = 0,
    eLeft_1 = 1,
    eRight_2 = 2,
};

struct Path_Lever final : public Path_TLV
{
    SwitchOp field_10_action;
    Scale_short field_12_scale;
    LeverSoundType field_14_on_sound;
    LeverSoundType field_16_off_sound;
    LeverSoundDirection field_18_sound_direction;
    s16 field_1A_switch_id;
    Choice_short field_1C_persist_offscreen;
    s16 field_1E_padding;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_Lever, 0x20);

class Lever final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    Lever(Path_Lever* pTlv, u32 tlvInfo);
    ~Lever();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual s16 VPull(s16 bLeftDirection);

private:
    s16 field_F4_switch_id = 0;
    LeverState field_F8_state = LeverState::eWaiting_0;
    s32 field_FC_tlvInfo = 0;
    enum Flags_100
    {
        eBit1_lever_anim_left_direction = 0x1,
        eBit2_persist_offscreen = 0x2,
    };
    BitField16<Flags_100> field_100_flags = {};
    SwitchOp field_102_action = SwitchOp::eSetTrue_0;
    LeverSoundType field_104_on_sound = LeverSoundType::eNone;
    LeverSoundType field_106_off_sound = LeverSoundType::eNone;
    LeverSoundDirection field_108_sound_direction = LeverSoundDirection::eLeftAndRight_0;
};
ALIVE_ASSERT_SIZEOF(Lever, 0x10C);
