#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAliveGameObject.hpp"

class PlatformBase : public BaseAliveGameObject
{
public:
    PlatformBase();
    ~PlatformBase();

    virtual void VAdd(BaseAliveGameObject* pObj);
    virtual void VRemove(BaseAliveGameObject* pObj);

    // TODO: New virtuals

protected:
    void AddDynamicCollision(AnimId animId, u8** ppAnimData, Path_TLV* pTlv, s32 tlvInfo);

    void SyncCollisionLinePosition();
    void vRemoveCount(BaseAliveGameObject* pObj);

    void vAddCount(BaseAliveGameObject* pObj);

protected:
    s32 mPlatformBaseCount = 0;
    s16 mPlatformBaseXOffset = 0;
    s16 mPlatformBaseWidthOffset = 0;
    s16 mPlatformBaseYOffset = 0;
    s16 mPlatformBaseHeightOffset = 0;
    PathLine* field_124_pCollisionLine = nullptr;
    s32 mPlatformBaseTlvInfo = 0;
};
ALIVE_ASSERT_SIZEOF(PlatformBase, 0x12C);
