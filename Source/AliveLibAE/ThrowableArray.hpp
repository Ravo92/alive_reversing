#pragma once

#include "../AliveLibCommon/FunctionFwd.hpp"
#include "BaseGameObject.hpp"

enum class LevelIds : s16;

EXPORT void CCSTD FreeResourceArray_49AEC0(DynamicArrayT<u8*>* pArray);
EXPORT void CC LoadRockTypes_49AB30(LevelIds levelNumber, u16 pathNumber);

class ThrowableArray final : public BaseGameObject
{
public:
    struct ThrowableArray_SaveState final
    {
        s16 field_0_unused;
        s16 field_2_item_count;
    };
    ALIVE_ASSERT_SIZEOF_ALWAYS(ThrowableArray_SaveState, 0x4);

    ThrowableArray();
    ~ThrowableArray();

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;
    virtual void VScreenChanged() override;

    static s32 CreateFromSaveState(const u8* pState);

    void Remove_49AA00(s16 count);
    void VScreenChanged();
    void Add_49A7A0(s16 count);

public:
    s16 field_20_count;

private:
    enum Flags_22
    {
        eBit1_Unknown = 0x1,
        eBit2_Unknown = 0x2,
        eBit3_Unknown = 0x4,
    };
    BitField16<Flags_22> field_22_flags;
    DynamicArrayT<u8*> field_24_throwables;
};
ALIVE_ASSERT_SIZEOF(ThrowableArray, 0x30);

ALIVE_VAR_EXTERN(ThrowableArray*, gpThrowableArray_5D1E2C);
