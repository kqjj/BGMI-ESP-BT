#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class EventTrackEx.MovieSceneXTEventSection
// 0x00C0 (0x0150 - 0x0090)
class UMovieSceneXTEventSection : public UMovieSceneSection
{
public:
	unsigned char                                      UnknownData00[0x48];                                      // 0x0090(0x0048) MISSED OFFSET
	struct FMovieSceneXTEventSectionData               EventData;                                                // 0x00D8(0x0018)
	unsigned char                                      UnknownData01[0x60];                                      // 0x00F0(0x0060) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class EventTrackEx.MovieSceneXTEventSection");
		return pStaticClass;
	}

};


// Class EventTrackEx.MovieSceneXTEventTrack
// 0x0018 (0x0060 - 0x0048)
class UMovieSceneXTEventTrack : public UMovieSceneNameableTrack
{
public:
	TArray<struct FMovieSceneObjectBindingID>          EventReceivers;                                           // 0x0048(0x000C) (Edit, ZeroConstructor)
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0054(0x000C) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class EventTrackEx.MovieSceneXTEventTrack");
		return pStaticClass;
	}

};


}

