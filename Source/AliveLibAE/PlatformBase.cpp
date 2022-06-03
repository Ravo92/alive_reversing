#include "stdafx.h"
#include "PlatformBase.hpp"
#include "Function.hpp"
#include "Path.hpp"
#include "Collisions.hpp"
#include "Game.hpp"
#include "stdlib.hpp"

PlatformBase::PlatformBase()
    : BaseAliveGameObject(0)
{

}



void PlatformBase::VAdd(BaseAliveGameObject* pObj)
{
    vAddCount(pObj);
}

void PlatformBase::VRemove(BaseAliveGameObject* pObj)
{
    vRemoveCount(pObj);
}

void PlatformBase::AddDynamicCollision(s32 frameTableOffset, s32 maxW, u16 maxH, u8** ppAnimData, Path_TLV* pTlv, Map* /*pMap*/, s32 tlvInfo)
{
    field_B8_xpos = FP_FromInteger(pTlv->field_8_top_left.field_0_x);
    field_BC_ypos = FP_FromInteger(pTlv->field_8_top_left.field_2_y);

    mPlatformBaseTlvInfo = tlvInfo;

    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);

    mPlatformBaseCount = 0;
    Animation_Init(
        frameTableOffset,
        maxW,
        maxH,
        ppAnimData,
        1,
        1);

    if (field_CC_sprite_scale == FP_FromInteger(1))
    {
        field_20_animation.mRenderLayer = Layer::eLayer_BeforeShadow_25;
        field_D6_scale = 1;
    }
    else
    {
        field_20_animation.mRenderLayer = Layer::eLayer_BeforeShadow_Half_6;
        field_D6_scale = 0;
    }

    FrameInfoHeader* pFrameHeader = field_20_animation.Get_FrameHeader(0);
    field_BC_ypos += FP_NoFractional(FP_FromInteger(-pFrameHeader->field_8_data.points[1].y) * field_CC_sprite_scale);
    field_B8_xpos = FP_FromInteger((pTlv->field_8_top_left.field_0_x + pTlv->field_C_bottom_right.field_0_x) / 2);

    field_124_pCollisionLine = sCollisions_DArray_5C1128->Add_Dynamic_Collision_Line(
        pTlv->field_8_top_left.field_0_x,
        pTlv->field_8_top_left.field_2_y,
        pTlv->field_C_bottom_right.field_0_x,
        pTlv->field_8_top_left.field_2_y,
        32);

    mPlatformBaseXOffset = FP_GetExponent(FP_FromInteger(pTlv->field_8_top_left.field_0_x) - field_B8_xpos);
    mPlatformBaseWidthOffset = FP_GetExponent(FP_FromInteger(pTlv->field_C_bottom_right.field_0_x) - field_B8_xpos);
    mPlatformBaseYOffset = FP_GetExponent(FP_FromInteger(pTlv->field_8_top_left.field_2_y) - field_BC_ypos);
    mPlatformBaseHeightOffset = FP_GetExponent(FP_FromInteger(pTlv->field_8_top_left.field_2_y) - field_BC_ypos);

    if (!ObjList_5C1B78->Push_Back(this))
    {
        mBaseGameObjectFlags.Set(Options::eListAddFailed_Bit1);
    }
}

PlatformBase::~PlatformBase()
{
    ObjList_5C1B78->Remove_Item(this);

    if (field_124_pCollisionLine)
    {
        if (gMap.mCurrentLevel == field_C2_lvl_number && gMap.mCurrentPath == field_C0_path_number)
        {
            Rect_Clear(&field_124_pCollisionLine->field_0_rect);
        }
    }
}

void PlatformBase::SyncCollisionLinePosition()
{
    field_124_pCollisionLine->field_0_rect.x = FP_GetExponent(FP_FromInteger(mPlatformBaseXOffset) + field_B8_xpos);
    field_124_pCollisionLine->field_0_rect.w = FP_GetExponent(FP_FromInteger(mPlatformBaseWidthOffset) + field_B8_xpos);
    field_124_pCollisionLine->field_0_rect.y = FP_GetExponent(field_BC_ypos + FP_FromInteger(mPlatformBaseYOffset));
    field_124_pCollisionLine->field_0_rect.h = FP_GetExponent(field_BC_ypos + FP_FromInteger(mPlatformBaseHeightOffset));
}

void PlatformBase::vRemoveCount(BaseAliveGameObject* /*pObj*/)
{
    --mPlatformBaseCount;
}

void PlatformBase::vAddCount(BaseAliveGameObject* /*pObj*/)
{
    ++mPlatformBaseCount;
    if (field_124_pCollisionLine)
    {
        SyncCollisionLinePosition();
    }
}
