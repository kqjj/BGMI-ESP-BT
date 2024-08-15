#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class GameRobotSync2.MyAutoTest3
// 0x002C (0x0048 - 0x001C)
class UMyAutoTest3 : public UObject
{
public:
	unsigned char                                      UnknownData00[0x2C];                                      // 0x001C(0x002C) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class GameRobotSync2.MyAutoTest3");
		return pStaticClass;
	}

};


}

