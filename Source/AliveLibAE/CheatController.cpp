#include "stdafx.h"
#include "CheatController.hpp"
#include "Function.hpp"
#include "stdlib.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "MainMenu.hpp"
#include "QuikSave.hpp"

CheatController* pCheatController_5BC120 = nullptr;

const InputCommands::Enum sCheatKeyArray_MovieSelect_5515C0[8] = {
    InputCommands::Enum::eUp,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eDown};

const InputCommands::Enum sCheatKeyArray_LevelSelect_5515D0[8] = {
    InputCommands::Enum::eDown,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eUp};

const InputCommands::Enum sCheatKeyArray_PathSkip_5515E8[6] = {
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight,
    InputCommands::Enum::eUp,
    InputCommands::Enum::eDown,
    InputCommands::Enum::eLeft,
    InputCommands::Enum::eRight};

void CheatController_Cheat_FMV_421AD0()
{
    if (gMap.mCurrentCamera == 1)
    {
        sEnableCheatFMV_5C1BEC = !sEnableCheatFMV_5C1BEC;
    }
}

void CheatController_Cheat_LevelSelect_421B00()
{
    if (gMap.mCurrentCamera == 1)
    {
        sEnableCheatLevelSelect_5C1BEE = !sEnableCheatLevelSelect_5C1BEE;
    }
}

void CheatController_Cheat_PathSkip_421B30()
{
    char_type nameBuffer[20];

    DestroyObjects_4A1F20();
    sprintf(nameBuffer, "NXTP%04d.SAV", sActiveQuicksaveData.field_204_world_info.mSaveFileId);

    //memcpy(&sActiveQuicksaveData, res.data(), sizeof(sActiveQuicksaveData));
    sActiveQuicksaveData.field_200_accumulated_obj_count = 1024;
    Quicksave_LoadActive();
}

CheatEntry sCheatArray_5515F8[] = {
    {1u, ALIVE_COUNTOF(sCheatKeyArray_MovieSelect_5515C0), sCheatKeyArray_MovieSelect_5515C0, 0, &CheatController_Cheat_FMV_421AD0},
    {1u, ALIVE_COUNTOF(sCheatKeyArray_LevelSelect_5515D0), sCheatKeyArray_LevelSelect_5515D0, 0, &CheatController_Cheat_LevelSelect_421B00},
    {0xFFFFFFFE, ALIVE_COUNTOF(sCheatKeyArray_PathSkip_5515E8), sCheatKeyArray_PathSkip_5515E8, 0, &CheatController_Cheat_PathSkip_421B30}};


CheatController::CheatController()
    : BaseGameObject(TRUE, 0)
{
    mBaseGameObjectFlags.Set(BaseGameObject::eSurviveDeathReset_Bit9);
    SetType(ReliveTypes::eNone);
    field_20 = 0;
}

CheatController::~CheatController()
{
    pCheatController_5BC120 = nullptr;
}

void CheatController::VUpdate()
{
    auto held = Input().mPads[sCurrentControllerIndex].mHeld;

    if (held)
    {
        // Only do cheat code check if shift is held
        if (Input().mPads[sCurrentControllerIndex].mPressed & InputCommands::Enum::eRun)
        {
            for (auto& cheatEntry : sCheatArray_5515F8)
            {
                // Bit shift current level for level mask.
                if ((1 << static_cast<s32>(MapWrapper::ToAE(gMap.mCurrentLevel))) & cheatEntry.field_0_level_mask)
                {
                    if (held == cheatEntry.field_8_cheat_code_ary[cheatEntry.field_C_success_idx])
                    {
                        cheatEntry.field_C_success_idx++;

                        // Check if we've successfully entered all cheat code keys.
                        if (cheatEntry.field_C_success_idx >= cheatEntry.field_4_cheat_code_length)
                        {
                            cheatEntry.field_C_success_idx = 0;
                            cheatEntry.field_10_callback();
                        }
                    }
                    else
                    {
                        cheatEntry.field_C_success_idx = 0;
                    }
                }
            }
        }
    }
}

void CheatController::VRender(PrimHeader** /*ppOt*/)
{
    // NULL
}

void CheatController::VScreenChanged()
{
    // NULL
}
