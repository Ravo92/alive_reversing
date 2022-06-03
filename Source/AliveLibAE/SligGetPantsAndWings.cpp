#include "stdafx.h"
#include "SligGetPantsAndWings.hpp"
#include "Function.hpp"
#include "Events.hpp"
#include "stdlib.hpp"
#include "FixedPoint.hpp"
#include "Game.hpp"
#include "Sfx.hpp"
#include "Slig.hpp"

SligGetPantsAndWings::SligGetPantsAndWings(Path_TLV* pTlv, s32 tlvInfo)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(AETypes::eSligGetPantsOrWings_80);
    field_F8_tlvInfo = tlvInfo;

    const AnimRecord& rec = AnimRec(AnimId::CrawlingSligLocker_Closed);
    u8** ppRes = Add_Resource(ResourceManager::Resource_Animation, rec.mResourceId);
    Animation_Init(rec.mFrameTableOffset, rec.mMaxW, rec.mMaxH, ppRes, 1, 1);

    // HACK: See header for details
    auto pHack = static_cast<Path_Slig*>(pTlv);
    if (pHack->field_10_scale == Scale_short::eHalf_1)
    {
        field_CC_sprite_scale = FP_FromDouble(0.5);
        field_D6_scale = 0;
        field_20_animation.mRenderLayer = Layer::eLayer_BeforeShadow_Half_6;
    }
    else if (pHack->field_10_scale == Scale_short::eFull_0)
    {
        field_20_animation.mRenderLayer = Layer::eLayer_BeforeShadow_25;
    }

    field_B8_xpos = FP_FromInteger((pTlv->field_8_top_left.field_0_x + pTlv->field_C_bottom_right.field_0_x) / 2);
    field_BC_ypos = FP_FromInteger(pTlv->field_C_bottom_right.field_2_y);
}

void SligGetPantsAndWings::VUpdate()
{
    Path_TLV* pTlv = sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam(field_F8_tlvInfo);
    if (Event_Get(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    switch (field_F4_state)
    {
        case State::eWaiting_0:
            if (pTlv->field_1_tlv_state)
            {
                field_F4_state = State::eActive_1;
                field_FC_timer = sGnFrame_5C1B84 + 8;
            }
            break;

        case State::eActive_1:
            if (static_cast<s32>(sGnFrame_5C1B84) > field_FC_timer)
            {
                field_F4_state = State::eFinished_2;
                SFX_Play_Mono(SoundEffect::NakedSligTransformEnd_92, 0);
                const AnimRecord& rec = AnimRec(AnimId::CrawlingSligLocker_Open);
                field_20_animation.Set_Animation_Data(rec.mFrameTableOffset, nullptr);
            }
            break;

        case State::eFinished_2:
            if (field_20_animation.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_F4_state = State::eWaiting_0;
                const AnimRecord& rec = AnimRec(AnimId::CrawlingSligLocker_Closed);
                field_20_animation.Set_Animation_Data(rec.mFrameTableOffset, nullptr);
                pTlv->field_1_tlv_state = 0;
            }
            break;
    }
}

void SligGetPantsAndWings::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

SligGetPantsAndWings::~SligGetPantsAndWings()
{
    Path::TLV_Reset(field_F8_tlvInfo, 0, 0, 0);
}
