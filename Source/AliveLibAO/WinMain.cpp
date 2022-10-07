#include "stdafx_ao.h"
#include "WinMain.hpp"
#include "Function.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "Game.hpp"
#include "Alarm.hpp"
#include "RollingBallShaker.hpp"
#include "Blood.hpp"
#include "Paramite.hpp"
#include "Scrab.hpp"
#include "Slog.hpp"
#include "Mudokon.hpp"
#include "SlingMudokon.hpp"
#include "HintFly.hpp"
#include "ZapLine.hpp"
#include "ScreenWave.hpp"
#include "GameEnderController.hpp"
#include "Spark.hpp"
#include "Sys.hpp"

namespace AO {

void WinMain_ForceLink()
{
}

void ForceLinks()
{
    RollingBallShaker_ForceLink();
    Blood_ForceLink();
    Paramite_ForceLink();
    Scrab_ForceLink();
    Slog_ForceLink();
    Mud_ForceLink();
    SlingMud_ForceLink();
    HintFly_ForceLink();
    ZapLine_ForceLink();
    Forcelink_ScreenWave();
    GameEnderController_ForceLink();
    Spark_ForceLink();
    Alarm_ForceLink();
}


ALIVE_VAR(1, 0x9F7734, s32, sExitCode_9F7734, 0);
ALIVE_VAR(1, 0x9F7784, HINSTANCE, sPrevInstance_9F7784, 0);

s32 CALLBACK WinMain_48EF50(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nShowCmd)
{
    LOG_INFO("Main enter");
    ForceLinks();
    AO_Sys_Main(hInstance, lpCmdLine, nShowCmd);
    sPrevInstance_9F7784 = hPrevInstance;
    Game_Main();
    LOG_INFO("Main exit");
    return sExitCode_9F7734;
}

} // namespace AO
