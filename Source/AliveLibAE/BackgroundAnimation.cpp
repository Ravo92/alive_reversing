#include "stdafx.h"
#include "BackgroundAnimation.hpp"
#include "Function.hpp"
#include "stdlib.hpp"
#include "Events.hpp"
#include "DDCheat.hpp"

BackgroundAnimation::BackgroundAnimation(Path_BackgroundAnimation* pTlv, TlvItemInfoUnion tlvInfo)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(AETypes::eBackgroundAnimation_7);
    field_F8_tlvInfo = tlvInfo;

    const BgAnimRecord& anim = BgAnimRec(pTlv->field_10_anim_id);
    field_F4_res = reinterpret_cast<AnimHeader**>(Add_Resource(ResourceManager::Resource_Animation, anim.mBgAnimId));
    if (!field_F4_res)
    {
        mFlags.Clear(BaseGameObject::eDrawable_Bit4);
        mFlags.Set(BaseGameObject::eDead);
        return;
    }

    field_B8_xpos = FP_FromInteger(pTlv->field_8_top_left.field_0_x);
    field_BC_ypos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);

    field_FC_animXPos = FP_FromInteger(pTlv->field_8_top_left.field_0_x);
    field_100_animYPos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);

    Animation_Init(
        anim.mFrameTableOffset,
        anim.mMaxW,
        anim.mMaxH,
        reinterpret_cast<u8**>(field_F4_res),
        1,
        1u);

    field_20_animation.field_4_flags.Set(AnimFlags::eBit15_bSemiTrans, pTlv->field_12_is_semi_trans == Choice_short::eYes_1);
    field_20_animation.field_4_flags.Set(AnimFlags::eBit16_bBlending);

    field_20_animation.field_B_render_mode = pTlv->field_14_semi_trans_mode;

    if (pTlv->field_1A_layer > Layer::eLayer_0)
    {
        const s32 translatedLayer = static_cast<s32>(pTlv->field_1A_layer) - 1;
        if (!translatedLayer)
        {
            field_20_animation.field_C_render_layer = Layer::eLayer_Above_FG1_Half_20;
        }
        if (translatedLayer == 1)
        {
            field_20_animation.field_C_render_layer = Layer::eLayer_Above_FG1_39;
        }
    }
    else
    {
        field_20_animation.field_C_render_layer = Layer::eLayer_1;
    }
}

void BackgroundAnimation::VUpdate()
{
    if (Event_Get(kEventDeathReset))
    {
        mFlags.Set(BaseGameObject::eDead);
    }
    else
    {
        field_B8_xpos = FP_FromInteger(sTweakX_5C1BD0) + field_FC_animXPos;
        field_BC_ypos = FP_FromInteger(sTweakY_5C1BD4) + field_100_animYPos;
    }
}

void BackgroundAnimation::VScreenChanged()
{
    mFlags.Set(BaseGameObject::eDead);
}

BackgroundAnimation::~BackgroundAnimation()
{
    Path::TLV_Reset(field_F8_tlvInfo.all, -1, 0, 0);
}
