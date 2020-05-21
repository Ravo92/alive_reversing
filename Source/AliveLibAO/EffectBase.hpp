#pragma once

#include "BaseGameObject.hpp"
#include "Primitives.hpp"
#include "FunctionFwd.hpp"

START_NS_AO

class EffectBase : public BaseGameObject
{
public:
    EXPORT EffectBase *ctor_461550(__int16 layer, char abr);

protected:

    __int16 field_10_path_id;
    __int16 field_12_level_id;
    Prim_Tile field_14_tile[2];
    Prim_SetTPage field_3C_tPage[2];
    __int16 field_5C_layer;
    __int16 field_5E_r;
    __int16 field_60_g;
    __int16 field_62_b;
    __int16 field_64_bSemiTrans;
    __int16 field_66_pad;
};
ALIVE_ASSERT_SIZEOF(EffectBase, 0x68);

END_NS_AO
