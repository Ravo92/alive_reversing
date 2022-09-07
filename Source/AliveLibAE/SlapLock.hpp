#pragma once

#include "BaseAliveGameObject.hpp"
#include "Path.hpp"

enum class SlapLockStates : s16
{
    eShaking_0 = 0,
    eIdle_1 = 1,
    eSlapped_2 = 2,
    eBroken_3 = 3,
    eEmitInvisibilityPowerupRing_4 = 4,
    eFlickerHero_5 = 5,
    eGiveInvisibilityFromFlicker_6 = 6,
    eGiveInvisibility_7 = 7,
};

struct SlapLock_State final
{
    AETypes mType;
    s16 mAnimRender;
    Guid mTlvInfo;
    s8 mTlvState;
    s8 padding;
    SlapLockStates mState;
    s32 mTimer1;
    Guid mAbilityRingId;
    s32 mShinyParticleTimer;
};
//ALIVE_ASSERT_SIZEOF_ALWAYS(SlapLock_State, 0x18);

class SlapLock final : public BaseAliveGameObject
{
public:
    SlapLock(relive::Path_SlapLock* pTlv, const Guid& tlvId);
    ~SlapLock();

    virtual void VUpdate() override;
    
    virtual void VScreenChanged() override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;
    virtual s16 VTakeDamage(BaseGameObject* pFrom) override;

    static s32 CreateFromSaveState(const u8* pBuffer);

private:
    void GiveInvisibility();
    void SetInvisibilityTarget();

private:
    relive::Path_SlapLock* mSlapLockTlv = nullptr;
    Guid mTlvInfo;
    SlapLockStates mState = SlapLockStates::eShaking_0;
    s32 mTimer1 = 0;
    relive::reliveChoice mHasGhost = relive::reliveChoice::eNo;
    Guid mAbilityRingId;
    Guid mPossessionFlickerId;
    s32 mShinyParticleTimer = 0;
};
ALIVE_ASSERT_SIZEOF(SlapLock, 0x140);
