#pragma once

#include "../relive_lib/BaseGameObject.hpp"
#include "Slurg.hpp"

struct Slurg_Spawner_Path_Data final
{
    s16 field_8_spawn_delay_between_slurgs;
    s16 field_A_max_slurgs;
    s16 field_C_switch_id;
    s16 field_E_padding;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Slurg_Spawner_Path_Data, 0x8);

struct Path_SlurgSpawner final : public Path_Slurg
{
    Slurg_Spawner_Path_Data field_18_spawner_data;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_SlurgSpawner, 0x20);

// NOTE: Apparently this object is never used - would kind of make sense as it reads
// the slurg spawned count from the TLV but never updates it.
// Also it hasn't got quiksave support.
class SlurgSpawner final : public BaseGameObject
{
public:
    SlurgSpawner(Path_SlurgSpawner* pTlv, s32 tlvInfo);
    
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

private:
    s32 field_20_tlvInfo = 0;
    Path_SlurgSpawner* field_24_slurg_tlv = nullptr;
    Slurg_Spawner_Path_Data field_28_path_data = {};
    s16 field_3E_delay_counter = 0;
    u8 field_40_spawned_count = 0;
};
ALIVE_ASSERT_SIZEOF(SlurgSpawner, 0x3C);
