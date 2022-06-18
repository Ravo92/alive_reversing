#pragma once

#include "AnimationBase.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/DynamicArray.hpp"
#include "Psx.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "FixedPoint.hpp"

using TFrameCallBackType = s32(CC*)(BaseGameObject*, s16*);

extern TFrameCallBackType kAbe_Anim_Frame_Fns_55EF98[5];
extern TFrameCallBackType kSlig_Anim_Frame_Fns_55EFAC[4];
extern TFrameCallBackType kSlog_Anim_Frame_Fns_55EFBC[2];
extern TFrameCallBackType kFlyingSlig_Anim_Frames_Fns_55EFC4[3];
extern TFrameCallBackType kFleech_Anim_Frame_Fns_55EFD0[3];

struct AnimHeader final
{
    s16 field_0_max_w;
    s16 field_2_max_h;
    s32 field_4_frame_table_offset;
};
ALIVE_ASSERT_SIZEOF(AnimHeader, 0x8);


struct AnimationHeader final
{
    // Meta data - the offset where this record was read from
    u16 field_0_fps;        // Seems to be 0x1 or 0x2
    s16 field_2_num_frames; // Number of frames in the set

    // If loop flag set then this is the frame to loop back to
    s16 field_4_loop_start_frame;

    // These where reversed by editing data in memory on PSX version
    enum eFlags
    {
        eFlipXFlag = 0x4,
        eFlipYFlag = 0x8,
        eNeverUnload = 0x1,
        eLoopFlag = 0x2
    };
    u16 field_6_flags;
    u32 mFrameOffsets[1]; // Reading past 1 is UB.. will need to change this later (copy out the data or something)
};

enum class CompressionType : u8
{
    eType_0_NoCompression = 0,
    eType_1_NotUsed = 1,
    eType_2_ThreeToFourBytes = 2,
    eType_3_RLE_Blocks = 3,
    eType_4_RLE = 4,
    eType_5_RLE = 5,
    eType_6_RLE = 6,
    eType_7_NotUsed = 7,
    eType_8_NotUsed = 8,
};

struct FrameHeader final
{
    u32 field_0_clut_offset;
    u8 field_4_width;
    u8 field_5_height;
    u8 field_6_colour_depth;
    CompressionType field_7_compression_type;
    u16 field_8_width2;
    u16 mHeight2;
};

struct Point final
{
    s16 x = 0;
    s16 y = 0;
};


struct OffsetAndBoundingRect final
{
    Point mOffset;
    Point mMin;
    Point mMax;
};

union PointsUnion
{
    PointsUnion()
    { }
    OffsetAndBoundingRect offsetAndRect;
    Point points[3];
};

struct FrameInfoHeader final
{
    u32 field_0_frame_header_offset;
    s16 field_4_magic;
    s16 field_6_count;
    PointsUnion field_8_data;
};

class Animation final : public AnimationBase
{
public:
    
    void Animation_Pal_Free();
 
    void DecompressFrame();

    virtual void VDecode() override;

    virtual void VRender(s32 xpos, s32 ypos, PrimHeader** ppOt, s16 width, s32 height) override;
    s16 Set_Animation_Data(s32 frameTableOffset, u8** pAnimRes);
    void SetFrame(s16 newFrame);
    
    s16 Init(s32 frameTableOffset, DynamicArray* animList, BaseGameObject* pGameObj, u16 maxW, u16 maxH, u8** ppAnimData);
   
    u16 Get_Frame_Count();

    FrameInfoHeader* Get_FrameHeader(s16 frame);
    void LoadPal(u8** pAnimData, s32 palOffset);
    void Get_Frame_Rect(PSX_RECT* pRect);
   

    void Get_Frame_Width_Height(s16* pWidth, s16* pHeight);
    void Get_Frame_Offset(s16* pBoundingX, s16* pBoundingY);

    virtual void VCleanUp() override;

    bool DecodeCommon();

    void Invoke_CallBacks();
    bool EnsureDecompressionBuffer();
    void UploadTexture(const FrameHeader* pFrameHeader, const PSX_RECT& vram_rect, s16 width_bpp_adjusted);

    u16 field_10_frame_delay = 0;
    u16 field_12_scale = 0; // padding?
    FP field_14_scale = {};
    u32 field_18_frame_table_offset = 0;
    s32(CC** field_1C_fn_ptr_array)(BaseGameObject*, s16*) = nullptr;
    u8** field_20_ppBlock = nullptr; // pointer to a pointer which points to anim data
    u8** field_24_dbuf = nullptr;

    u32 field_28_dbuf_size = 0;
    Poly_FT4 field_2C_ot_data[2] = {};

    PSX_RECT field_84_vram_rect = {};
    PSX_Point field_8C_pal_vram_xy = {};

    s16 field_90_pal_depth = 0;
    s16 field_92_current_frame = 0;
    BaseGameObject* field_94_pGameObj = nullptr;
};
ALIVE_ASSERT_SIZEOF(Animation, 0x98);

inline bool IsLastFrame(const Animation* pAnim)
{
    const u8* pAnimData = (*pAnim->field_20_ppBlock);
    const auto pHeader = reinterpret_cast<const AnimationHeader*>(&pAnimData[pAnim->field_18_frame_table_offset]);
    return (pAnim->field_92_current_frame == pHeader->field_2_num_frames - 1);
}
