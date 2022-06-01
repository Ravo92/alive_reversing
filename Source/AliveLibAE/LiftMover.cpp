#include "stdafx.h"
#include "LiftMover.hpp"
#include "Function.hpp"
#include "BaseAliveGameObject.hpp"
#include "LiftPoint.hpp"
#include "Events.hpp"
#include "SwitchStates.hpp"
#include "ObjectIds.hpp"
#include "stdlib.hpp"

LiftMover::LiftMover(Path_LiftMover* pTlv, s32 tlvInfo)
    : BaseGameObject(TRUE, 0)
{
    field_24_tlvInfo = tlvInfo;
    field_28_lift_id = -1;
    SetType(AETypes::eLiftMover_9);

    field_20_lift_mover_switch_id = pTlv->field_10_lift_mover_switch_id;
    field_22_target_lift_point_id = pTlv->field_12_target_lift_point_id;

    if (pTlv->field_14_move_direction == Path_LiftMover::YDirection::eUp_1)
    {
        field_2C_speed = FP_FromInteger(-4);
    }
    else
    {
        field_2C_speed = FP_FromInteger(4);
    }

    field_30_state = LiftMoverStates::eInactive_0;
    field_32_bMoveInProgress = FALSE;
}

s32 LiftMover::CreateFromSaveState(const u8* pData)
{
    auto pState = reinterpret_cast<const LiftMover_State*>(pData);

    Path_LiftMover* pTlv = static_cast<Path_LiftMover*>(sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam_4DB770(pState->field_4_tlvInfo));
    auto pLiftMover = ae_new<LiftMover>(pTlv, pState->field_4_tlvInfo);
    if (pLiftMover)
    {
        if (pState->field_8_state != LiftMoverStates::eInactive_0)
        {
            pLiftMover->field_32_bMoveInProgress = TRUE;
        }
        pLiftMover->field_30_state = pState->field_8_state;
    }

    return sizeof(LiftMover_State);
}

void LiftMover::VUpdate()
{
    vUpdate_40CE20();
}

s32 LiftMover::VGetSaveState(u8* pSaveBuffer)
{
    return vGetSaveState_40D240(reinterpret_cast<LiftMover_State*>(pSaveBuffer));
}

void LiftMover::vUpdate_40CE20()
{
    LiftPoint* pLift = static_cast<LiftPoint*>(sObjectIds.Find(field_28_lift_id, AETypes::eLiftPoint_78));
    if (field_32_bMoveInProgress)
    {
        pLift = GetLiftPoint_40D0F0();
        if (!pLift)
        {
            return;
        }
        field_32_bMoveInProgress = FALSE;
    }

    if (pLift && pLift->mFlags.Get(BaseGameObject::eDead))
    {
        // Set extra dead for good measure
        mFlags.Set(BaseGameObject::eDead);
        field_28_lift_id = -1;
    }
    else
    {
        switch (field_30_state)
        {
            case LiftMoverStates::eInactive_0:
                if (SwitchStates_Get_466020(field_20_lift_mover_switch_id))
                {
                    if (!pLift)
                    {
                        pLift = GetLiftPoint_40D0F0();
                    }

                    if (pLift)
                    {
                        field_28_lift_id = pLift->field_8_object_id;
                        field_30_state = LiftMoverStates::eStartMovingDown_1;
                    }
                }
                break;

            case LiftMoverStates::eStartMovingDown_1:
                if (!pLift)
                {
                    return;
                }

                if (!pLift->vOnAnyFloor_461920())
                {
                    field_30_state = LiftMoverStates::eMovingDown_2;
                    pLift->vKeepOnMiddleFloor_461870();
                }
                else
                {
                    pLift->vMove_4626A0(FP_FromInteger(0), field_2C_speed, 0);
                    if ((field_2C_speed > FP_FromInteger(0) && pLift->vOnBottomFloor_4618F0()) || (field_2C_speed < FP_FromInteger(0) && pLift->vOnTopFloor_461890()))
                    {
                        field_30_state = LiftMoverStates::eMovingDown_2;
                    }
                }
                break;

            case LiftMoverStates::eMovingDown_2:
                if (!pLift)
                {
                    return;
                }

                if (!pLift->vOnAFloorLiftMoverCanUse_461960())
                {
                    pLift->vMove_4626A0(FP_FromInteger(0), field_2C_speed, 0);
                }
                else
                {
                    pLift->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
                    field_30_state = LiftMoverStates::eMovingDone_5;
                }
                break;

            case LiftMoverStates::eStartMovingUp_3:
                if (!pLift)
                {
                    return;
                }

                if (pLift->vOnAFloorLiftMoverCanUse_461960())
                {
                    pLift->vMove_4626A0(FP_FromInteger(0), field_2C_speed, 0);
                    if (field_2C_speed < FP_FromInteger(0))
                    {
                        if (pLift->vOnTopFloor_461890())
                        {
                            field_30_state = LiftMoverStates::eMovingDown_2;
                        }
                    }

                    if (field_2C_speed > FP_FromInteger(0))
                    {
                        if (pLift->vOnBottomFloor_4618F0())
                        {
                            field_30_state = LiftMoverStates::eMovingDown_2;
                        }
                    }
                }
                else
                {
                    field_30_state = LiftMoverStates::eMovingUp_4;
                    pLift->vKeepOnMiddleFloor_461870();
                }
                break;

            case LiftMoverStates::eMovingUp_4:
                if (!pLift)
                {
                    return;
                }

                if (pLift->vOnAFloorLiftMoverCanUse_461960())
                {
                    pLift->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);

                    field_30_state = LiftMoverStates::eInactive_0;
                    field_2C_speed = -field_2C_speed;
                }
                else
                {
                    pLift->vMove_4626A0(FP_FromInteger(0), field_2C_speed, 0);
                }
                break;

            case LiftMoverStates::eMovingDone_5:
                if (!SwitchStates_Get_466020(field_20_lift_mover_switch_id))
                {
                    field_30_state = LiftMoverStates::eStartMovingUp_3;
                    field_2C_speed = -field_2C_speed;
                }
                break;

            default:
                break;
        }

        if (Event_Get_422C00(kEventDeathReset))
        {
            mFlags.Set(BaseGameObject::eDead);
        }
    }
}

LiftMover::~LiftMover()
{
    Path::TLV_Reset_4DB8E0(field_24_tlvInfo, -1, 0, 0);
}

s32 LiftMover::vGetSaveState_40D240(LiftMover_State* pState)
{
    pState->field_0_type_id = AETypes::eLiftMover_9;
    pState->field_4_tlvInfo = field_24_tlvInfo;
    pState->field_8_state = field_30_state;
    return sizeof(LiftMover_State);
}

LiftPoint* LiftMover::GetLiftPoint_40D0F0()
{
    for (s32 i = 0; i < gBaseAliveGameObjects_5C1B7C->Size(); i++)
    {
        BaseAliveGameObject* pObj = gBaseAliveGameObjects_5C1B7C->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->Type() == AETypes::eLiftPoint_78)
        {
            LiftPoint* pLift = static_cast<LiftPoint*>(pObj);
            if (field_22_target_lift_point_id == pLift->field_278_lift_point_id)
            {
                field_28_lift_id = pObj->field_8_object_id;
                return pLift;
            }
        }
    }
    return nullptr;
}
