#pragma once

#include "BaseAliveGameObject.hpp"
#include "Path.hpp"
#include "../AliveLibCommon/Function.hpp"

struct Path_MovingBomb final : public Path_TLV
{
    u16 field_10_speed;
    s16 field_12_start_moving_switch_id;
    Choice_short field_14_bTriggered_by_alarm;
    Scale_short field_16_scale;
    s16 field_18_max_rise; // seems unused
    s16 field_1A_disabled_resources;
    u16 field_1C_start_speed;
    Choice_short field_1E_persist_offscreen;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_MovingBomb, 0x20);

struct Path_MovingBombStopper final : public Path_TLV
{
    s16 field_10_min;
    s16 field_12_max;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_MovingBombStopper, 0x14);

class MovingBomb final : public BaseAliveGameObject
{
public:
    MovingBomb(Path_MovingBomb* pTlv, s32 tlvInfo);
    ~MovingBomb();
    
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VOnThrowableHit(BaseGameObject* pFrom) override;
    virtual s16 VTakeDamage(BaseGameObject* pFrom) override;
    virtual void VScreenChanged() override;

private:
    void BlowUp();
    void FollowLine();
    s16 HitObject();

private:
    enum class States : s16
    {
        eTriggeredByAlarm_0 = 0,
        eTriggeredBySwitch_1 = 1,
        eMoving_2 = 2,
        eStopMoving_3 = 3,
        eWaitABit_4 = 4,
        eToMoving_5 = 5,
        eBlowingUp_6 = 6,
        eKillMovingBomb_7 = 7
    };
    States field_118_state = States::eTriggeredByAlarm_0;
    s32 field_11C_tlvInfo = 0;
    s32 field_120_timer = 0;
    FP field_124_speed = {};
    s16 field_128_start_moving_switch_id = 0;
    s16 field_12A_min = 0;
    s16 field_12C_max = 0;
    s32 field_130_sound_channels = 0;
    s16 field_134_disabled_resources = 0;
    Choice_short field_136_persist_offscreen = Choice_short::eNo_0;
};
ALIVE_ASSERT_SIZEOF(MovingBomb, 0x138);
