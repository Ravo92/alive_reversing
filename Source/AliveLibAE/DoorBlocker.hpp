#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAliveGameObject.hpp"

namespace relive
{
    struct Path_DoorBlocker;
}

class DoorBlocker final : public BaseAliveGameObject
{
public:
    DoorBlocker(relive::Path_DoorBlocker* pTlv, const Guid& tlvId);
    ~DoorBlocker();

    void LoadAnimations();
    virtual void VUpdate() override;

private:
    s16 field_118_bDone = 0;
    s16 field_11A_switch_id = 0;
    Guid field_11C_tlvInfo;
};
