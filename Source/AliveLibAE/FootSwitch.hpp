#pragma once

#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Path.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "SwitchStates.hpp"

enum class FootSwitchTriggerBy : s16
{
    eAbe_0 = 0,
    eAnyone_1 = 1,
};

struct Path_FootSwitch final : public Path_TLV
{
    s16 field_10_switch_id;
    Scale_short field_12_scale;
    SwitchOp field_14_action;
    FootSwitchTriggerBy field_16_trigger_by;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_FootSwitch, 0x18);

struct FootSwitch_Data final
{
    s32 field_0_frameTableOffset;
    s32 field_4_frameTableOffset;
    s16 field_8_maxH;
    s16 field_A_frameTableOffset;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(FootSwitch_Data, 0xC);


class FootSwitch final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    FootSwitch(Path_FootSwitch* pTlv, s32 tlvInfo);
    ~FootSwitch();
    
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

private:
    BaseAliveGameObject* WhoIsStoodOnMe();

private:
    s32 field_F4_tlvInfo = 0;
    enum class States : s16
    {
        eWaitForStepOnMe_0 = 0,
        eWaitForGetOffMe_1 = 1,
    };
    States field_F8_state = States::eWaitForStepOnMe_0;
    s16 field_FA_switch_id = 0;
    SwitchOp field_FC_action = SwitchOp::eSetTrue_0;
    FootSwitchTriggerBy field_FE_trigger_by = FootSwitchTriggerBy::eAbe_0;
    s32 field_100_obj_id = 0;
    s16 field_104_bCreateSparks = 0;
    s16 field_106_bFindStander = 0;
};
ALIVE_ASSERT_SIZEOF(FootSwitch, 0x108);
