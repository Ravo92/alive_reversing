#pragma once

#include "../relive_lib/BaseGameObject.hpp"
#include "../AliveLibAE/Slurg.hpp"
#include "../relive_lib/data_conversion/PathTlvsAE.hpp"

// it reads the slurg spawned count from the TLV but never updates it.
// Also it hasn't got quiksave support.
// https://github.com/AliveTeam/alive_reversing/issues/1526

class SlurgSpawner final : public BaseGameObject
{
public:
    SlurgSpawner(relive::Path_SlurgSpawner* pTlv, const Guid& tlvId);
    
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

private:
    Guid mTlvInfo;
    relive::Path_SlurgSpawner* mSlurgTlv = nullptr;
    Slurg_Spawner_Path_Data mSlurgPathData = {};
    s16 mSpawnCounter = 0;
    u8 mSpawnedCount = 0;
};
