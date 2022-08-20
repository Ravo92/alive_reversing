#include "stdafx_ao.h"
#include "Function.hpp"
#include "Well.hpp"
#include "Math.hpp"
#include "stdlib.hpp"
#include "ResourceManager.hpp"
#include "SwitchStates.hpp"
#include "Leaf.hpp"
#include "../relive_lib/Events.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "DDCheat.hpp"

namespace AO {

ALIVE_VAR(1, 0x4D1488, u8, sWellRndSeed_4D1488, 4);

static s16 Well_NextRandom()
{
    return sRandomBytes_4BBE30[sWellRndSeed_4D1488++];
}

Well::~Well()
{
    if (mTlvInfo != -1)
    {
        Path::TLV_Reset(mTlvInfo, -1, 0, 0);
    }
}

void Well::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

void Well::VRender(PrimHeader** ppOt)
{
    mXPos += FP_FromInteger(gTweak_X_5076D8);
    mYPos += FP_FromInteger(gTweak_Y_5076DC);
    BaseAnimatedWithPhysicsGameObject::VRender(ppOt);
    mXPos -= FP_FromInteger(gTweak_X_5076D8);
    mYPos -= FP_FromInteger(gTweak_Y_5076DC);
}

void Well::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        Path::TLV_Reset(mTlvInfo, -1, 0, 0);
    }

    if (mEmitLeaves == Choice_short::eYes_1)
    {
        // Always on or has been enabled?
        if (!mSwitchId || SwitchStates_Get(mSwitchId))
        {
            // Random chance of leaves emitting
            if (Well_NextRandom() < 10)
            {
                auto pLeaf = relive_new Leaf(
                    mLeafX,
                    mLeafY,
                    mExitX,
                    mExitY,
                    mLeafScale);

                if (mExitY > FP_FromInteger(0))
                {
                    if (pLeaf)
                    {
                        if (mLeafScale == FP_FromDouble(0.5))
                        {
                            pLeaf->mAnim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
                        }
                        else
                        {
                            pLeaf->mAnim.mRenderLayer = Layer::eLayer_BeforeWell_22;
                        }
                    }
                }
            }
        }
    }
}

void Well::WellExpress_Init(Path_WellExpress* pTlv, FP /*xpos*/, FP ypos)
{
    //u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, pTlv->field_1E_anim_id, 1, 0);
    //auto pHeader = reinterpret_cast<AnimHeader*>(*ppRes);
    //LOG_INFO("frametableoffset: " << pHeader->field_4_frame_table_offset << " anim id: " << pTlv->field_1E_anim_id << " max w: " << pHeader->field_0_max_w << " max h: " << pHeader->field_2_max_h);

    const BgAnimRecord& anim = AO::BgAnimRec(pTlv->mAnimId);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, anim.mBgAnimId, 1, 0);
    if (ppRes)
    {
        Animation_Init(anim.mFrameTableOffset, anim.mMaxW, anim.mMaxH, ppRes);
        mAnim.mFlags.Clear(AnimFlags::eBit15_bSemiTrans);
        mVisualFlags.Clear(VisualFlags::eApplyShadowZoneColour);
    }
    else
    {
        mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
        mBaseGameObjectFlags.Clear(Options::eDrawable_Bit4);
    }

    if (pTlv->mScale == Scale_short::eHalf_1)
    {
        mAnim.mRenderLayer = Layer::eLayer_Well_Half_4;
        mLeafScale = FP_FromDouble(0.5);
    }
    else
    {
        mAnim.mRenderLayer = Layer::eLayer_Well_23;
        mLeafScale = FP_FromInteger(1);
    }

    mSwitchId = pTlv->mSwitchId;
    mExitX = FP_FromInteger(pTlv->mExitX) / FP_FromInteger(100);
    mExitY = FP_FromInteger(pTlv->mExitY) / FP_FromInteger(100);

    mEmitLeaves = pTlv->mEmitLeaves;

    if (mEmitLeaves == Choice_short::eYes_1)
    {
        mLeafX = FP_FromInteger(pTlv->mLeafX);
        if (!FP_GetExponent(mLeafX))
        {
            mLeafX = FP_FromInteger(pTlv->mTopLeft.x
                                                + (PsxToPCX(pTlv->mBottomRight.x - pTlv->mTopLeft.x, +11)
                                                   / 2));
        }

        mLeafY = FP_FromInteger(pTlv->mLeafY);
        if (!FP_GetExponent(mLeafY))
        {
            mLeafY = ypos;
        }
    }
}

void Well::WellLocal_Init(Path_WellLocal* pTlv, FP /*xpos*/, FP ypos)
{
    //u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, pTlv->field_1E_anim_id, 1, 0);
    //auto pHeader = reinterpret_cast<AnimHeader*>(*ppRes);
    //LOG_INFO("frametableoffset: " << pHeader->field_4_frame_table_offset << " anim id: " << pTlv->field_1E_anim_id << " max w: " << pHeader->field_0_max_w << " max h: " << pHeader->field_2_max_h);

    const BgAnimRecord& anim = AO::BgAnimRec(pTlv->mAnimId);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, anim.mBgAnimId, 1, 0);
    if (ppRes)
    {
        Animation_Init(anim.mFrameTableOffset, anim.mMaxW, anim.mMaxH, ppRes);
        mAnim.mFlags.Clear(AnimFlags::eBit15_bSemiTrans);
        mVisualFlags.Clear(VisualFlags::eApplyShadowZoneColour);
    }
    else
    {
        mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
        mBaseGameObjectFlags.Clear(Options::eDrawable_Bit4);
    }

    if (pTlv->mScale == Scale_short::eHalf_1)
    {
        mAnim.mRenderLayer = Layer::eLayer_Well_Half_4;
        mLeafScale = FP_FromDouble(0.5);
        mScale = Scale::Bg;
    }
    else
    {
        mAnim.mRenderLayer = Layer::eLayer_Well_23;
        mLeafScale = FP_FromInteger(1);
        mScale = Scale::Fg;
    }

    mSwitchId = pTlv->mSwitchId;
    mExitX = FP_FromInteger(pTlv->mExitX) / FP_FromInteger(100);
    mExitY = FP_FromInteger(pTlv->mExitY) / FP_FromInteger(100);

    mEmitLeaves = pTlv->mEmitLeaves;

    if (mEmitLeaves == Choice_short::eYes_1)
    {
        mLeafX = FP_FromInteger(pTlv->mLeafX);
        if (!FP_GetExponent(mLeafX))
        {
            mLeafX = FP_FromInteger(pTlv->mTopLeft.x + (PsxToPCX(pTlv->mBottomRight.x - pTlv->mTopLeft.x, 11) / 2));
        }

        mLeafY = FP_FromInteger(pTlv->mLeafY);
        if (!FP_GetExponent(mLeafY))
        {
            mLeafY = ypos;
        }
    }
}

Well::Well(Path_WellBase* pTlv, FP xpos, FP ypos, s32 tlvInfo)
{
    mTlvInfo = tlvInfo;
    mBaseGameObjectTypeId = ReliveTypes::eWell;

    mRGB.SetRGB(128, 128, 128);

    mYPos = ypos;
    mXPos = xpos;

    if (pTlv->mTlvType32 == TlvTypes::WellLocal_11)
    {
        WellLocal_Init(static_cast<Path_WellLocal*>(pTlv), xpos, ypos);
    }
    else
    {
        WellExpress_Init(static_cast<Path_WellExpress*>(pTlv), xpos, ypos);
    }
}

} // namespace AO
