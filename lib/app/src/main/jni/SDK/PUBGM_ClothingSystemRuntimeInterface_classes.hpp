#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class ClothingSystemRuntimeInterface.ClothingAssetBase
// 0x001C (0x0038 - 0x001C)
class UClothingAssetBase : public UObject
{
public:
	unsigned char                                      UnknownData00[0xC];                                       // 0x001C(0x000C) MISSED OFFSET
	struct FGuid                                       AssetGuid;                                                // 0x0028(0x0010) (IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class ClothingSystemRuntimeInterface.ClothingAssetBase");
		return pStaticClass;
	}

};


// Class ClothingSystemRuntimeInterface.ClothingSimulationFactory
// 0x0004 (0x0020 - 0x001C)
class UClothingSimulationFactory : public UObject
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class ClothingSystemRuntimeInterface.ClothingSimulationFactory");
		return pStaticClass;
	}

};


}

