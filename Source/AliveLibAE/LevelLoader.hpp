#pragma once

#include "../relive_lib/BaseGameObject.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "Path.hpp"
#include "../relive_lib/MapWrapper.hpp"

enum class LevelIds : s16;

struct Path_LevelLoader final : public Path_TLV
{
    s16 field_10_switch_id;
    LevelIds field_12_dest_level;
    s16 field_14_dest_path;
    s16 field_16_dest_camera;
    s16 field_18_movie_id;
    s16 field_1A_pad;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_LevelLoader, 0x1C);

class LevelLoader final : public BaseGameObject
{
public:
    LevelLoader(Path_LevelLoader* pTlv, u32 tlvInfo);

    virtual void VUpdate() override;

private:
    s16 field_20_switch_id = 0;
    enum class States : s16
    {
        eIdle_0 = 0,
        eFadingOut_1 = 1,
        eDone_2 = 2,
    };
    States field_22_state = States::eIdle_0;
    EReliveLevelIds field_24_level = EReliveLevelIds::eNone;
    s16 field_26_path = 0;
    s16 field_28_camera = 0;
    s16 field_2A_movie_id = 0;
    u32 field_2C_tlvInfo = 0;
    s32 field_30_fade_id = 0;
};
ALIVE_ASSERT_SIZEOF(LevelLoader, 0x34);
