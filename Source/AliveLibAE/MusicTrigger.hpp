#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Path.hpp"
#include "MusicController.hpp"

class MusicTrigger final : public BaseGameObject
{
public:
    MusicTrigger(relive::Path_MusicTrigger* pTlv, const Guid& tlvId);
    MusicTrigger(relive::Path_MusicTrigger::MusicTriggerMusicType musicType, relive::Path_MusicTrigger::TriggeredBy triggeredBy, s32 /*not_used*/, s32 delay);
    ~MusicTrigger();

    void Init(relive::Path_MusicTrigger::MusicTriggerMusicType musicType, relive::Path_MusicTrigger::TriggeredBy triggeredBy, s16 delay);
    
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

private:
    Guid field_20_tlvInfo;
    enum Flags_24
    {
        e24_Bit1_TriggeredByTouching = 0x1,
        e24_Bit2_TriggeredByTimer = 0x2,
        e24_Bit3_SetMusicToNoneOnDtor = 0x4,
    };
    BitField16<Flags_24> field_24_flags = {};
    MusicController::MusicTypes field_26_music_type = MusicController::MusicTypes::eNone_0;
    s32 field_28_counter = 0;
    PSX_Point field_2C_tl = {};
    PSX_Point field_30_br = {};
};
ALIVE_ASSERT_SIZEOF(MusicTrigger, 0x34);
