#pragma once

#include "../relive_lib/BaseAnimatedWithPhysicsGameObject.hpp"
#include "Path.hpp"
#include "../AliveLibCommon/Function.hpp"

class GlukkonSwitch final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    GlukkonSwitch(relive::Path_GlukkonSwitch* pTlv, const Guid& tlvId);
    ~GlukkonSwitch();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

private:
    s16 PlayerNearMe();

private:
    Guid field_F4_tlvInfo;
    s16 field_F8_state = 0;
    s16 field_FA_ok_switch_id = 0;
    s16 field_FC_fail_switch_id = 0;
    s16 field_FE = 0;
    s32 field_100_last_event_idx = 0;
    s16 field_104 = 0;
    s16 field_106 = 0;
    s16 field_108 = 0;
    s16 field_10A = 0;
    s16 field_10C = 0;
    s16 field_10E = 0;
    s16 field_110 = 0;
    s16 field_112 = 0;
    s16 field_114 = 0;
    s16 field_116 = 0;
    PSX_Point field_118_top_left = {};
    PSX_Point field_11C_bottom_right = {};
    s32 field_120_timer = 0;
};
ALIVE_ASSERT_SIZEOF(GlukkonSwitch, 0x124);
