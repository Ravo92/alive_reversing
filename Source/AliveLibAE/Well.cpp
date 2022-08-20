#include "stdafx.h"
#include "Well.hpp"
#include "Function.hpp"
#include "Leaf.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "Path.hpp"
#include "../relive_lib/Events.hpp"
#include "stdlib.hpp"
#include "SwitchStates.hpp"

ALIVE_VAR(1, 0x563aa0, u32, sWellRndSeed_563AA0, 4);

Well::Well(Path_WellBase* pTlv, FP xpos, FP ypos, s32 tlvInfo)
    : BaseGameObject(TRUE, 0)
{
    mTlvInfo = tlvInfo;
    SetType(ReliveTypes::eWell);

    if (pTlv->mTlvType32 == TlvTypes::LocalWell_8)
    {
        WellLocal_Init(static_cast<Path_WellLocal*>(pTlv), xpos, ypos);
    }
    else
    {
        WellExpress_Init(static_cast<Path_WellExpress*>(pTlv), xpos, ypos);
    }
}

void Well::WellExpress_Init(Path_WellExpress* pTlv, FP /*xpos*/, FP ypos)
{
    if (pTlv->mScale != Scale_short::eFull_0)
    {
        mLeafScale = FP_FromDouble(0.5);
    }
    else
    {
        mLeafScale = FP_FromInteger(1);
    }

    mSwitchId = pTlv->mSwitchId;

    mExitX = FP_FromInteger(pTlv->field_18_exit_x) / FP_FromInteger(100);
    mExitY = FP_FromInteger(pTlv->field_1A_exit_y) / FP_FromInteger(100);

    mEmitLeaves = pTlv->mEmitLeaves;
    if (mEmitLeaves == Choice_short::eYes_1)
    {
        PSX_Point abeSpawnPos = {};
        gMap.Get_Abe_Spawn_Pos(&abeSpawnPos);

        mLeafX = FP_FromInteger(pTlv->mLeafX);
        if (pTlv->mLeafX > 0)
        {
            mLeafX += FP_FromInteger(abeSpawnPos.x);
        }
        else
        {
            const s32 pos = (PsxToPCX(pTlv->mBottomRight.x - pTlv->mTopLeft.x) / 2) + pTlv->mTopLeft.x;
            mLeafX = FP_FromInteger(pos);
        }

        mLeafY = FP_FromInteger(pTlv->mLeafY);
        if (pTlv->mLeafY > 0)
        {
            mLeafY += FP_FromInteger(abeSpawnPos.y);
        }
        else
        {
            mLeafY = ypos;
        }
    }
}

void Well::WellLocal_Init(Path_WellLocal* pTlv, FP /*xpos*/, FP ypos)
{
    if (pTlv->mScale != Scale_short::eFull_0)
    {
        mLeafScale = FP_FromDouble(0.5);
    }
    else
    {
        mLeafScale = FP_FromInteger(1);
    }

    mSwitchId = pTlv->mSwitchId;

    mEmitLeaves = pTlv->mEmitLeaves;
    if (mEmitLeaves == Choice_short::eYes_1)
    {
        PSX_Point abeSpawnPos = {};
        gMap.Get_Abe_Spawn_Pos(&abeSpawnPos);
        mLeafX = FP_FromInteger(pTlv->mLeafX);

        if (pTlv->mLeafX > 0)
        {
            mLeafX += FP_FromInteger(abeSpawnPos.x);
        }
        else
        {
            const s32 pos = (PsxToPCX(pTlv->mBottomRight.x - pTlv->mTopLeft.x) / 2) + pTlv->mTopLeft.x;
            mLeafX = FP_FromInteger(pos);
        }

        mLeafY = FP_FromInteger(pTlv->mLeafY);
        if (pTlv->mLeafY > 0)
        {
            mLeafY += FP_FromInteger(abeSpawnPos.y);
        }
        else
        {
            mLeafY = ypos;
        }
    }
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

static s16 Well_NextRandom()
{
    const auto curRand = sRandomBytes_546744[sWellRndSeed_563AA0];
    sWellRndSeed_563AA0++;

    if (sWellRndSeed_563AA0 > 255)
    {
        sWellRndSeed_563AA0 = 0;
    }

    return curRand;
}

void Well::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        // Reset well state when Abe dies.
        Path::TLV_Reset(mTlvInfo, -1, 0, 0);
    }

    if (mEmitLeaves == Choice_short::eYes_1)
    {
        // Always on or has been enabled?
        if (mSwitchId == 0 || SwitchStates_Get(mSwitchId))
        {
            // Random chance of leaves emitting.
            if (Well_NextRandom() < 10)
            {
                relive_new Leaf(mLeafX,
                                          mLeafY,
                                          FP_FromInteger(2),
                                          FP_FromInteger(-20),
                                          mLeafScale);
            }
        }
    }
}
