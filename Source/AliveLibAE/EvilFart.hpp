#pragma once

#include "BaseAliveGameObject.hpp"
#include "../AliveLibCommon/Function.hpp"

enum class EReliveLevelIds : s16;

enum class FartStates : s16
{
    eIdle_0 = 0,
    eFlying_1 = 1,
    eDechanting_2 = 2
};

struct EvilFart_State final
{
    AETypes field_0_type;
    s16 mRed;
    s16 mGreen;
    s16 mBlue;
    s16 mCurrentPath;
    LevelIds mCurrentLevel;
    FP mXPos;
    FP mYPos;
    FP mVelX;
    FP mVelY;
    FP mSpriteScale;
    s16 mCurrentFrame;
    s16 mFrameChangeCounter;
    s8 mAnimRender;
    s8 mDrawable;
    LevelIds mAbeLevel;
    s16 mAbePath;
    s16 mAbeCamera;

    enum Flags_2C
    {
        eBit1_bControlled = 0x1,
        eBit2_FartExploded = 0x2,
    };
    BitField16<Flags_2C> field_2C;

    s16 mPossessedAliveTimer;
    FartStates mState;
    s16 field_32_padding;
    s32 mUnpossessionTimer;
    s32 mBackToAbeTimer;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(EvilFart_State, 60);

class EvilFart final : public BaseAliveGameObject
{
public:
    EvilFart();

    virtual void VUpdate() override;
    virtual s16 VTakeDamage(BaseGameObject* pFrom) override;
    virtual void VPossessed() override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;

    static s32 CreateFromSaveState(const u8* pBuffer);

private:
    void InputControlFart();
    void ResetFartColour();
    void CalculateFartColour();
    void BlowUp();

private:
    s16 mFartExploded = 0;
    bool mPossessed = false;
    s16 mPossessedAliveTimer = 0;
    s16 mAbePath = 0;
    EReliveLevelIds mAbeLevel = EReliveLevelIds::eNone;
    s16 mAbeCamera = 0;
    FartStates mState = FartStates::eIdle_0;
    s32 mUnpossessionTimer = 0;
    s32 mBackToAbeTimer = 0;
    s32 mSoundChannels = 0;
};
