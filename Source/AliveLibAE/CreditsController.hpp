#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Path.hpp"

struct Path_CreditsController final : public Path_TLV
{
    // Empty
};

#pragma pack(push)
#pragma pack(2)
class CreditsController final : public BaseGameObject
{
public:
    
    virtual void VUpdate() override;

    CreditsController(Path_TLV* pTlv, s32 tlvInfo);
    ~CreditsController();

public:
    s32 field_20_next_cam_frame = 0;
    s16 field_24_camera_number = 0;
};
#pragma pack(pop)
ALIVE_ASSERT_SIZEOF(CreditsController, 0x26);

ALIVE_VAR_EXTERN(s16, sDoesCreditsControllerExist_5C1B90);