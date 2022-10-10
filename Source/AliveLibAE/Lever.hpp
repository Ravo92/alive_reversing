#pragma once

#include "../relive_lib/BaseAnimatedWithPhysicsGameObject.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "SwitchStates.hpp"

enum class LeverState : s16
{
    eWaiting_0 = 0,
    ePulled_1 = 1,
    eFinished_2 = 2
};

class Lever final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    Lever(relive::Path_Lever* pTlv, const Guid& tlvId);
    ~Lever();

    void LoadAnimations();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual s16 VPull(s16 bLeftDirection);

private:
    s16 field_F4_switch_id = 0;
    LeverState field_F8_state = LeverState::eWaiting_0;
    Guid field_FC_tlvInfo;
    enum Flags_100
    {
        eBit1_lever_anim_left_direction = 0x1,
        eBit2_persist_offscreen = 0x2,
    };
    BitField16<Flags_100> field_100_flags = {};
    relive::reliveSwitchOp field_102_action = relive::reliveSwitchOp::eSetTrue;
    relive::Path_Lever::LeverSoundType field_104_on_sound = relive::Path_Lever::LeverSoundType::eNone;
    relive::Path_Lever::LeverSoundType field_106_off_sound = relive::Path_Lever::LeverSoundType::eNone;
    relive::Path_Lever::LeverSoundDirection field_108_sound_direction = relive::Path_Lever::LeverSoundDirection::eLeftAndRight;
};
