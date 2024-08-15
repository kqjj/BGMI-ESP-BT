#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class TableResInclude.BaseTableResMap
// 0x0044 (0x0060 - 0x001C)
class UBaseTableResMap : public UObject
{
public:
	unsigned char                                      UnknownData00[0x40];                                      // 0x001C(0x0040) MISSED OFFSET
	class UScriptStruct*                               DataStruct;                                               // 0x005C(0x0004) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class TableResInclude.BaseTableResMap");
		return pStaticClass;
	}

};


// Class TableResInclude.EvoBaseMapUIMarkTableMap
// 0x0000 (0x0060 - 0x0060)
class UEvoBaseMapUIMarkTableMap : public UBaseTableResMap
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class TableResInclude.EvoBaseMapUIMarkTableMap");
		return pStaticClass;
	}


	void TraversTable(class UUAEDataTable* TableData, const struct FName& Key);
};


// Class TableResInclude.EvoBaseModTableTestTableMap
// 0x0000 (0x0060 - 0x0060)
class UEvoBaseModTableTestTableMap : public UBaseTableResMap
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class TableResInclude.EvoBaseModTableTestTableMap");
		return pStaticClass;
	}


	void TraversTable(class UUAEDataTable* TableData, const struct FName& Key);
};


}

