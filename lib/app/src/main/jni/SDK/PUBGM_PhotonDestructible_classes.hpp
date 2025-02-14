#pragma once

// Pubgm BGMI-32bit (3.3.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

namespace SDK
{
//---------------------By BangJO---------------------------
//Classes
//---------------------By BangJO---------------------------

// Class PhotonDestructible.FracturedStaticMeshActor
// 0x0028 (0x0360 - 0x0338)
class AFracturedStaticMeshActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0338(0x0004) MISSED OFFSET
	class UFracturedStaticMeshComponent*               FracturedStaticMeshComponent;                             // 0x033C(0x0004) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	float                                              SingleFragmentHP;                                         // 0x0340(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      EnableImpactDamage : 1;                                   // 0x0344(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0345(0x0003) MISSED OFFSET
	float                                              ImpactDamageValue;                                        // 0x0348(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFStaticMeshNetData                         FSMNetData;                                               // 0x034C(0x0010) (Net)
	unsigned char                                      UnknownData02[0x4];                                       // 0x035C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedStaticMeshActor");
		return pStaticClass;
	}


	void Server_OnActorRadiusHitAction(class AActor* SelfActor, class AActor* OtherActor, const struct FVector& WorldImpactPoint, float Radius);
	void Server_OnActorHitAction(class AActor* SelfActor, class AActor* OtherActor, const struct FVector& NormalImpulse, const struct FHitResult& Hit);
	void OnRep_FSMNetData();
	void Client_OnFragmentsHPChanged(TArray<int> FragmentsIndex, TArray<float> FragmentsChangedHP, const struct FVector& WorldImpactPoint, float Radius);
	void Client_OnFragmentHPChanged(int FragmentIndex, float FragmentHP, const struct FVector& WorldImpactPoint);
};


// Class PhotonDestructible.PhotonDestructibleSurfaceComponent
// 0x0050 (0x0850 - 0x0800)
class UPhotonDestructibleSurfaceComponent : public UStaticMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0800(0x0004) MISSED OFFSET
	TEnumAsByte<enum EFracturedAxis>                   MaskUAxis;                                                // 0x0804(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum EFracturedAxis>                   MaskVAxis;                                                // 0x0805(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0806(0x0002) MISSED OFFSET
	class UTexture2D*                                  MaskTexture2D;                                            // 0x0808(0x0004) (Edit, ZeroConstructor, Transient, EditConst, IsPlainOldData)
	struct FPDSurfaceNetData                           SurfaceNetData;                                           // 0x080C(0x0010) (Net)
	struct FGuid                                       TargetPuppetGUID;                                         // 0x081C(0x0010) (Edit, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData02[0x24];                                      // 0x082C(0x0024) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleSurfaceComponent");
		return pStaticClass;
	}


	void Server_ProcessHit(const struct FPhotonDestructibleSurfaceHitData& HitData);
	void OnRep_SurfaceNetData();
	void Client_OnProcessHit(const struct FPhotonDestructibleSurfaceHitData& HitData);
};


// Class PhotonDestructible.PhotonDestructibleInstancedSurfaceComponent
// 0x0040 (0x0A00 - 0x09C0)
class UPhotonDestructibleInstancedSurfaceComponent : public UHierarchicalInstancedStaticMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x09C0(0x0004) MISSED OFFSET
	TEnumAsByte<enum EFracturedAxis>                   MaskUAxis;                                                // 0x09C4(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum EFracturedAxis>                   MaskVAxis;                                                // 0x09C5(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x09C6(0x0002) MISSED OFFSET
	class UMaterialInterface*                          Texture2DArrayMaterial;                                   // 0x09C8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          AtlasMaterial;                                            // 0x09CC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FPDSurfaceNetData                           SurfaceNetData;                                           // 0x09D0(0x0010) (Net)
	TArray<struct FGuid>                               TargetPuppetGUID;                                         // 0x09E0(0x000C) (Edit, ZeroConstructor, EditConst)
	unsigned char                                      UnknownData02[0x14];                                      // 0x09EC(0x0014) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleInstancedSurfaceComponent");
		return pStaticClass;
	}


	void Server_ProcessHit(const struct FPhotonDestructibleSurfaceHitData& HitData);
	void OnRep_SurfaceNetData();
	void Client_OnProcessHit(const struct FPhotonDestructibleSurfaceHitData& HitData);
};


// Class PhotonDestructible.FracturedMesh
// 0x003C (0x0058 - 0x001C)
class UFracturedMesh : public UObject
{
public:
	unsigned char                                      UnknownData00[0xC];                                       // 0x001C(0x000C) MISSED OFFSET
	int                                                ClipPlaneMaterialIndex;                                   // 0x0028(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum EFracturedAxis>                   FracturedClipAxis;                                        // 0x002C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2B];                                      // 0x002D(0x002B) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedMesh");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FracturedMeshSettings
// 0x0004 (0x0020 - 0x001C)
class UFracturedMeshSettings : public UObject
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedMeshSettings");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FracturedSkeletalMesh
// 0x0060 (0x02E0 - 0x0280)
class UFracturedSkeletalMesh : public USkeletalMesh
{
public:
	unsigned char                                      GenerateNormalSimplifiedLOD : 1;                          // 0x0280(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0281(0x0003) MISSED OFFSET
	TArray<struct FKConvexElem>                        NormalConvexElemForCollision;                             // 0x0284(0x000C) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x50];                                      // 0x0290(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedSkeletalMesh");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FracturedSkeletalMeshActor
// 0x0048 (0x0380 - 0x0338)
class AFracturedSkeletalMeshActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0338(0x0004) MISSED OFFSET
	class UFracturedSkinnedMeshComponent*              FracturedSkinnedMeshComponent;                            // 0x033C(0x0004) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	float                                              SingleFragmentHP;                                         // 0x0340(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      EnableImpactDamage : 1;                                   // 0x0344(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0345(0x0003) MISSED OFFSET
	float                                              ImpactDamageValue;                                        // 0x0348(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ImpactImpulseForce;                                       // 0x034C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFSkeletalMeshNetData                       FSMNetData;                                               // 0x0350(0x0030) (Net)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedSkeletalMeshActor");
		return pStaticClass;
	}


	void Server_OnActorHitAction(class AActor* SelfActor, class AActor* OtherActor, const struct FVector& NormalImpulse, const struct FHitResult& Hit);
	void OnRep_FSMNetData();
	void Client_OnImpact(int FragmentIndex, const struct FVector& ImpactWorldPos, const struct FVector& ImpactWorldDir, float ImpulseForce, float InFirstImpactTime);
};


// Class PhotonDestructible.FracturedSkinnedMeshComponent
// 0x0090 (0x08F0 - 0x0860)
class UFracturedSkinnedMeshComponent : public USkinnedMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x40];                                      // 0x0860(0x0040) MISSED OFFSET
	TEnumAsByte<enum EFracturedMeshDestructibleAction> DestructibleAction;                                       // 0x08A0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum EFracturedImpactEffType>          ImpactEffType;                                            // 0x08A1(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x08A2(0x0002) MISSED OFFSET
	float                                              ImpactEffSpreadOutFactor;                                 // 0x08A4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowFracturedMaxDistance;                                 // 0x08A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowFracturedMaxDistanceBuffer;                           // 0x08AC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowFracturedTime;                                        // 0x08B0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      RemovePhysicsIfFragmentHidden : 1;                        // 0x08B4(0x0001) (Edit)
	unsigned char                                      UnknownData02[0x3];                                       // 0x08B5(0x0003) MISSED OFFSET
	class UFracturedSkeletalMesh*                      FracturedMesh;                                            // 0x08B8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class UBodySetup*                                  BodySetup;                                                // 0x08BC(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData03[0x30];                                      // 0x08C0(0x0030) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedSkinnedMeshComponent");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FracturedStaticMesh
// 0x0058 (0x01C0 - 0x0168)
class UFracturedStaticMesh : public UStaticMesh
{
public:
	class UFracturedMesh*                              FracturedMesh;                                            // 0x0168(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UseUnDestructedTriangle : 1;                              // 0x016C(0x0001)
	unsigned char                                      DistanceFieldEightBit : 1;                                // 0x016C(0x0001)
	unsigned char                                      UnknownData00[0x53];                                      // 0x016D(0x0053) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedStaticMesh");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FracturedStaticMeshComponent
// 0x00A0 (0x08A0 - 0x0800)
class UFracturedStaticMeshComponent : public UStaticMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x35];                                      // 0x0800(0x0035) MISSED OFFSET
	TEnumAsByte<enum EFracturedMeshConnectionType>     CheckConnectionType;                                      // 0x0835(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0836(0x0002) MISSED OFFSET
	class UFracturedStaticMesh*                        FracturedMesh;                                            // 0x0838(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum ECollisionEnabled>                NormalCollisionEnabled;                                   // 0x083C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x083D(0x0003) MISSED OFFSET
	struct FName                                       NormalCollisionProfileName;                               // 0x0840(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<enum ECollisionEnabled>                AllBrokenCollisionEnabled;                                // 0x0848(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0849(0x0007) MISSED OFFSET
	struct FName                                       AllBrokenCollisionProfileName;                            // 0x0850(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowFracturedMaxDistance;                                 // 0x0858(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowFracturedMaxDistanceBuffer;                           // 0x085C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      EnableFracturedMeshDecal : 1;                             // 0x0860(0x0001) (Edit)
	unsigned char                                      UnknownData04[0x3];                                       // 0x0861(0x0003) MISSED OFFSET
	float                                              FracturedMeshDecalFactor;                                 // 0x0864(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                FracturedMeshDecalMaterialIndex;                          // 0x0868(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          FracturedMeshDecalMaterial;                               // 0x086C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          FracturedMeshDecalNormalMaterial;                         // 0x0870(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowDecalMaxDistance;                                     // 0x0874(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShowDecalMaxDistanceBuffer;                               // 0x0878(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	class UBodySetup*                                  ThisBodySetup;                                            // 0x087C(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData05[0x20];                                      // 0x0880(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedStaticMeshComponent");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FEdgeData
// 0x0004 (0x0020 - 0x001C)
class UFEdgeData : public UObject
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FEdgeData");
		return pStaticClass;
	}

};


// Class PhotonDestructible.FracturedFragmentInfo
// 0x0044 (0x0060 - 0x001C)
class UFracturedFragmentInfo : public UObject
{
public:
	unsigned char                                      UnknownData00[0xC];                                       // 0x001C(0x000C) MISSED OFFSET
	struct FVector                                     centerPoint;                                              // 0x0028(0x000C) (IsPlainOldData)
	TArray<int>                                        neighbors;                                                // 0x0034(0x000C) (ZeroConstructor)
	TArray<struct FPlane>                              FacePlaneData;                                            // 0x0040(0x000C) (ZeroConstructor)
	TArray<struct FVector>                             PolygonVertex;                                            // 0x004C(0x000C) (ZeroConstructor)
	unsigned char                                      CanDestroy : 1;                                           // 0x0058(0x0001) (Edit)
	unsigned char                                      HasTriangle : 1;                                          // 0x0058(0x0001) (Edit, EditConst)
	unsigned char                                      IsBorder : 1;                                             // 0x0058(0x0001) (Edit, EditConst)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0059(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.FracturedFragmentInfo");
		return pStaticClass;
	}

};


// Class PhotonDestructible.MaterialExpressionObjectLocalPosition
// 0x0000 (0x0048 - 0x0048)
class UMaterialExpressionObjectLocalPosition : public UMaterialExpression
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.MaterialExpressionObjectLocalPosition");
		return pStaticClass;
	}

};


// Class PhotonDestructible.MaterialExpressionGetPDInstancedSurfaceMask
// 0x0000 (0x0048 - 0x0048)
class UMaterialExpressionGetPDInstancedSurfaceMask : public UMaterialExpression
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.MaterialExpressionGetPDInstancedSurfaceMask");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleAtlasPool
// 0x0008 (0x00D0 - 0x00C8)
class UPhotonDestructibleAtlasPool : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x00C8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleAtlasPool");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleMgr
// 0x0018 (0x0350 - 0x0338)
class APhotonDestructibleMgr : public AActor
{
public:
	class UPhotonDestructibleTexturePool*              TexturePool;                                              // 0x0338(0x0004) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	class UPhotonDestructibleAtlasPool*                AtlasPool;                                                // 0x033C(0x0004) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	class UPhotonDestructibleTexture2DArrayManager*    Texture2DArrayManager;                                    // 0x0340(0x0004) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	class UPhotonDestructibleSurfaceConfig*            SurfaceConfig;                                            // 0x0344(0x0004) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	class UPhotonDestructiblePuppetMgr*                PuppetMgr;                                                // 0x0348(0x0004) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x034C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleMgr");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructiblePuppet
// 0x0010 (0x02E0 - 0x02D0)
class UPhotonDestructiblePuppet : public USceneComponent
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x02D0(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructiblePuppet");
		return pStaticClass;
	}


	void TriggerPuppetEvent(int EventID);
};


// Class PhotonDestructible.PhotonDestructiblePuppetContainer
// 0x0020 (0x02F0 - 0x02D0)
class UPhotonDestructiblePuppetContainer : public USceneComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x02D0(0x0008) MISSED OFFSET
	TArray<struct FString>                             TargetsName;                                              // 0x02D8(0x000C) (Edit, ZeroConstructor, EditConst)
	unsigned char                                      UnknownData01[0xC];                                       // 0x02E4(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructiblePuppetContainer");
		return pStaticClass;
	}


	void TriggerPuppetEvent(const struct FString& ObjectName, int EventID);
};


// Class PhotonDestructible.PhotonDestructiblePuppetMgr
// 0x0038 (0x0100 - 0x00C8)
class UPhotonDestructiblePuppetMgr : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x38];                                      // 0x00C8(0x0038) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructiblePuppetMgr");
		return pStaticClass;
	}


	void Client_TriggerPuppetEvent(const struct FGuid& PuppetGUID, int EventID);
};


// Class PhotonDestructible.PhotonDestructiblePuppetTarget
// 0x0000 (0x0020 - 0x0020)
class UPhotonDestructiblePuppetTarget : public UInterface
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructiblePuppetTarget");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleSurfaceActor
// 0x0008 (0x0340 - 0x0338)
class APhotonDestructibleSurfaceActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0338(0x0004) MISSED OFFSET
	class UPhotonDestructibleSurfaceComponent*         SurfaceComponent;                                         // 0x033C(0x0004) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleSurfaceActor");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleInstancedSurfaceActor
// 0x0008 (0x0340 - 0x0338)
class APhotonDestructibleInstancedSurfaceActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0338(0x0004) MISSED OFFSET
	class UPhotonDestructibleInstancedSurfaceComponent* InstancedSurfaceComponent;                                // 0x033C(0x0004) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleInstancedSurfaceActor");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleSurfaceActorBase
// 0x0000 (0x0020 - 0x0020)
class UPhotonDestructibleSurfaceActorBase : public UInterface
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleSurfaceActorBase");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleInstancedSurfaceActorBase
// 0x0000 (0x0020 - 0x0020)
class UPhotonDestructibleInstancedSurfaceActorBase : public UInterface
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleInstancedSurfaceActorBase");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleSurfaceBase
// 0x0000 (0x0020 - 0x0020)
class UPhotonDestructibleSurfaceBase : public UInterface
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleSurfaceBase");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleSurfaceConfig
// 0x0008 (0x00D0 - 0x00C8)
class UPhotonDestructibleSurfaceConfig : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x00C8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleSurfaceConfig");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleSurfaceMask
// 0x001C (0x0038 - 0x001C)
class UPhotonDestructibleSurfaceMask : public UObject
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	struct FIntPoint                                   MaskSize;                                                 // 0x0020(0x0008) (IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0028(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleSurfaceMask");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleTexture2DArrayManager
// 0x0018 (0x00E0 - 0x00C8)
class UPhotonDestructibleTexture2DArrayManager : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x00C8(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleTexture2DArrayManager");
		return pStaticClass;
	}

};


// Class PhotonDestructible.PhotonDestructibleTexturePool
// 0x0018 (0x00E0 - 0x00C8)
class UPhotonDestructibleTexturePool : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x00C8(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class PhotonDestructible.PhotonDestructibleTexturePool");
		return pStaticClass;
	}

};


}

