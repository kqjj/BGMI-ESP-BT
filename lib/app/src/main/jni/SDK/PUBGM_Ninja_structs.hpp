#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Script Structs
//---------------------By BangJO---------------------------

// ScriptStruct Ninja.CircleMoveInfo
// 0x0024
struct FCircleMoveInfo
{
	struct FVector                                     StartCircle;                                              // 0x0000(0x000C) (BlueprintVisible, IsPlainOldData)
	struct FVector                                     EndCircle;                                                // 0x000C(0x000C) (BlueprintVisible, IsPlainOldData)
	bool                                               bMove;                                                    // 0x0018(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0019(0x0003) MISSED OFFSET
	float                                              EndTimeStamp;                                             // 0x001C(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              StartTimeStamp;                                           // 0x0020(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

