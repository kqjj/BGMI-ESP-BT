#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Script Structs
//---------------------By BangJO---------------------------

// ScriptStruct SpinePlugin.SpineAnimationStateMixData
// 0x001C
struct FSpineAnimationStateMixData
{
	struct FString                                     from;                                                     // 0x0000(0x000C) (Edit, BlueprintVisible, ZeroConstructor)
	struct FString                                     to;                                                       // 0x000C(0x000C) (Edit, BlueprintVisible, ZeroConstructor)
	float                                              Mix;                                                      // 0x0018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct SpinePlugin.SpineEvent
// 0x0024
struct FSpineEvent
{
	struct FString                                     Name;                                                     // 0x0000(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
	struct FString                                     StringValue;                                              // 0x000C(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
	int                                                IntValue;                                                 // 0x0018(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              FloatValue;                                               // 0x001C(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              Time;                                                     // 0x0020(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

}

