#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class MaterialShaderQualitySettings.MaterialShaderQualitySettings
// 0x003C (0x0058 - 0x001C)
class UMaterialShaderQualitySettings : public UObject
{
public:
	unsigned char                                      UnknownData00[0x3C];                                      // 0x001C(0x003C) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class MaterialShaderQualitySettings.MaterialShaderQualitySettings");
		return pStaticClass;
	}

};


// Class MaterialShaderQualitySettings.ShaderPlatformQualitySettings
// 0x001C (0x0038 - 0x001C)
class UShaderPlatformQualitySettings : public UObject
{
public:
	unsigned char                                      UnknownData00[0x1C];                                      // 0x001C(0x001C) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class MaterialShaderQualitySettings.ShaderPlatformQualitySettings");
		return pStaticClass;
	}

};


}

