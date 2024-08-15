#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include "../SDK.hpp"

namespace SDK
{
//---------------------By BangJO---------------------------
//Parameters
//---------------------By BangJO---------------------------

// Function ZLevel.ZLevelData.ReBindLevelDataComponent
struct AZLevelData_ReBindLevelDataComponent_Params
{
};

// Function ZLevel.ZLevelData.CheckMonsterSpotIsOnLand
struct AZLevelData_CheckMonsterSpotIsOnLand_Params
{
	class UZMonsterSpot*                               MonsterSpot;                                              // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UZMonsterSpotGroup*                          SpotGroup;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

