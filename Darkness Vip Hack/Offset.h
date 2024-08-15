#pragma once

#include "Includes.h"

namespace Offset
{

	/// <summary>
	namespace Data {
		const DWORD PersistentLevel = 0x20; //Level* PersistentLevel;
		const DWORD NetDriver = 0x24;//NetDriver* NetDriver;
		const DWORD ServerConnection = 0x60; //NetConnection* ServerConnection;
		const DWORD PlayerController = 0x20; //PlayerController* PlayerController; //Class: Player.Object
		const DWORD AcknowledgedPawn = 0x390; // PlayerController.Controller.Actor.Object Pawn* AcknowledgedPawn;//[Offset:
		const DWORD EntityList = 0x70;
		const DWORD EntityCount = 0x74; //EntityList + 0x4; //
		const DWORD GameState = 0x13c; //Class: World.Object //GameStateBase* GameState;//[Off
		const DWORD RootComponent = 0x158; // SceneComponent* RootComponent;//[Offset:
	}

	//Class: STExtraPlayerCharacter.STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object

	namespace STExtraPlayerCharacter {
		constexpr auto STPlayerController = 0x3194; // STExtraPlayerController* STPlayerController;//[Offset: 0x3184, Size: 4]
	}


	////////////GOD VIEW/////////////
	const DWORD SceneComponent = 0x12c0; // SceneComponent* MeshContainer;//[Offset:
	const DWORD CustomSpringArmComponent = 0x1440; // CustomSpringArmComponent* SpringArmComp

	extern struct Vector2 {
		float x = 0;
		float y = 0;
	};
	extern struct Vector3 {
		float x = 0;
		float y = 0;
		float z = 0;
	};
	extern struct Vector4 {
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};
	extern struct D3DMatrix {
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};
	struct playerData
	{
		DWORD Address, Pose, World;
		Vector3 Position;
		int Status, TeamID, Health, Distance;
		int AlivePlayers = 0;
		int TimeRemind = 0;
		int AliveTeams = 0;
		int RealPls = 0;
		int ZoneID = 0;
		int MyTeamID = 0;
		int GameID = 0;
		bool IsRobot;
		bool IsDead;
		std::string Name, Type, weapon, Nation;
	};

	struct Item {
		DWORD Address;
		std::string displayName;
		Vector3 Position;
		int color;
		int picid;
	};

	struct Specl {
		DWORD Address;
		std::string displayName;
	};

	struct ItmInfo {
		std::string name;
		int color;
	};

	struct AimInfo {
		Vector3 Head, Chest;
		Vector2 Screen;
	};
	struct Lootbox {
		Vector3 Position;

		std::vector<Item> boxitem;
		int picid;
	};

	struct Vehicle {
		DWORD Address, VehicleComm;
		std::string displayName;
		Vector3 Position;
		int picid;
		int MaxHP, MaxFuel;
		int HP, Fuel;
	};
	struct Vehicle2 {
		DWORD Address, VehicleComm2;
		std::string displayName;
		Vector3 Position;
		int picid;

	};

	struct Vehicle3 {
		DWORD Address, VehicleComm3;
		std::string displayName;
		Vector3 Position;
		int picid;

	};
	//struct Lootbox {
	//    Vector3 Position;
	//    std::string itemname;
	//};
	struct Vehicle4 {
		DWORD Address, VehicleComm4;
		std::string displayName;
		Vector3 Position;
		int picid;

	};

	namespace Hacks {
		const DWORD ConfigCollisionDistSqAngles = 0x120; //	OpenCollisionLODAngle[] ConfigCollisionDistSqAngles;//[Offset: 0x120, Size: 12]  //Class: PartHitComponent.ActorComponent.Object
		const DWORD PartHitComponent = 0xc14;	//PartHitComponent* PartHitComponent;//[Offset: 0xc24, Size: 4]
		const DWORD FastRun = 0x2280;			//CharacterOverrideAttrs CharacterOverrideAttrs;//[Offset: //need update  for 3.2
		// Instant hit
		const DWORD CurrentReloadWeapon = 0x2278;//STExtraWeapon* CurrentReloadWeapon;//[Offset:
		const DWORD CurShootIntervalMode = 0xcc4; //enum CurShootIntervalMode;//[Offset: 
		//show dmg
		const DWORD GameReplayType = 0x750; //int GameReplayType;//[Offset:
		//////SPEED OFFSETS/////
		const DWORD CharacterOverrideAttrs = 0x2280; //CharacterOverrideAttrs CharacterOverrideAttrs; //need update  for 3.2
		//repid fire
		const DWORD ShootInterval = 0x44c; /// Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object float ShootInterval;//[Offset:
		//no spread
		const DWORD GameDeviationFactor = 0x984; ////********* float GameDeviationFactor Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
		const DWORD ShotGunVerticalSpread = 0x97c; //Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object float ShotGunVerticalSpread
		const DWORD ShotGunHorizontalSpread = 0x980; ///********* float ShotGunHorizontalSpread
	
		 
		
		// NoRecoil offsets
		const DWORD AccessoriesVRecoilFactor = 0x91c; //Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object float AccessoriesVRecoilFactor;//[Offset: 0x924, Size: 4]
		const DWORD AccessoriesHRecoilFactor = 0x920; //float AccessoriesHRecoilFactor;//[Offset:
		const DWORD AccessoriesRecoveryFactor = 0x924; //float AccessoriesRecoveryFactor;//[Offset:
		//car speed 
		const DWORD bIsEngineStarted = 0x7b4;//bool bIsEngineStarted;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset:
		//FastSwitch
		const DWORD SwitchWeaponSpeedScale = 0x1f3c; ///Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object float SwitchWeaponSpeedScale;//[Offset:
		//Fast Land
		const DWORD CharacterParachuteComponent = 0x1068; //CharacterParachuteComponent* ParachuteComponent
		const DWORD CurrentFallSpeed = 0x14c; //CurrentFallSpeed;//[Offset: Class: CharacterParachuteComponent.LuaInstancedActorComponent.ActorComponent.Object

		const DWORD bHasSingleFireMode = 0x498;//bool bHasSingleFireMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset:
		const DWORD bHasAutoFireMode = 0x499;//bool bHasAutoFireMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset:
		const DWORD BulletFireSpeed = 0x420; //Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object float BulletFireSpeed
		const DWORD IsFPPGameMode = 0x6dc;//IsFPPGameMode;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset:

		const DWORD BulletRange = 0x564; //float BulletRange;//[Offset: 0x560, Size: 4]

		const DWORD WeaponManagerComponent = 0x1ae0; /////CharacterWeaponManagerComponent* WeaponManagerComponent;//[Offset:

		const DWORD ShootWeaponEntity = 0xcb8; // ShootWeaponEntity* ShootWeaponEntityComp;//[Offset: 
		//Class: WeaponManagerComponent.ActorComponent.Object
		const DWORD  CurrentWeaponReplicated = 0x40c;//STExtraWeapon* CurrentWeaponReplicated;

		const DWORD  BulletTrackDistanceFix = 0x704;//float BulletTrackDistanceFix;//[Offset: 0x704, Size: 4]

		const DWORD UploadInterval = 0x108;//float UploadInterval
		const DWORD CurBulletNumInClip = 0xb90; //int CurBulletNumInClip;//[Offset: 0xbd0, Size: 4]
		const DWORD CurMaxBulletNumInOneClip = 0xba4;//	int CurMaxBulletNumInOneClip;//[Offset: 0xbe4, Size: 4]
		const DWORD bIsWeaponFiring = 0x1074; // bool bIsWeaponFiring;
		const DWORD bIsGunADS = 0xc19; //bool bIsGunADS;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0xc29, Size: 1]
	}


	// AActor
	namespace Player {
		const DWORD CurrentStates = 0xb78;// uint64 CurrentStates;//[Offset: //Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
		const DWORD Kills = 0x520;  //   {"Class: UAEPlayerState.LuaPlayerState.PlayerState.Info.Actor.Object", "int Kills;//[Offset:", "PlayerKills"},
		const DWORD IsDead = 0xa54;//bool bDead;//(ByteOffset: 0, ByteMask: 1, FieldMask: 1)[Offset: Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
		const DWORD TeamId = 0x6d4; //Class: UAECharacter.Character.Pawn.Actor.Object int TeamID;//[Offset:
		const DWORD PoseState = 0x1084; //Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object byte PoseState;//[Offset:
		const DWORD IsBot = 0x76d; // bool bEnsure
		const DWORD Name = 0x6a0; //Class: UAECharacter.Character.Pawn.Actor.Object FString PlayerName;//[Offset:
		//const DWORD Status = 0xaf8; // Class: UAECharacter.Character.Pawn.Actor.Object FString PlayerName;//[Offset:
		const DWORD Nation = 0x6ac; //FString Nation;//[Offset: 
		const DWORD Health = 0xa3c; // float Health;//[Offset:Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
		const DWORD HealthMax = 0xa40; // float HealthMax;//[Offset:Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
		const DWORD KnockHealth = 0x1324;		// float NearDeathBreath;//[Offset: Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
		const DWORD weaponOffset = 0x2278; //STExtraWeapon* CurrentReloadWeapon;//[Offset: 0x221c, Size: 4]

	}

	///updated till here 

	// Lot BOX
//Class: PickUpListWrapperActor.PickUpWrapperActor.UAENetActor.LuaActor.Actor.Object
	namespace LootBox {
		const DWORD PickUpItemData = 0x6f8; // PickUpItemData[] PickUpDataList;//[Offset: 
		const DWORD boxItemsCount = 0x6f8; // PickUpItemData[] PickUpDataList;//[Offset:   + 0x4
		const DWORD itemBase = 0x6f8; // PickUpItemData[] PickUpDataList;//[Offset:   
	}

	/// </summary>
	//Class: Character.Pawn.Actor.Object
	const DWORD CharacterMovement = 0x380; // CharacterMovementComponent* CharacterMovement;//[Offset:
	const DWORD LastUpdateVelocity = 0x260; // Vector LastUpdateVelocity;//[Offset: //Class: CharacterMovementComponent.PawnMovementComponent.NavMovementComponent.MovementComponent.ActorComponent.Object
	const DWORD Velocity = 0xd0; // Vector Velocity;//[Offset: Class: MovementComponent.ActorComponent.Object

//Class: SceneComponent.ActorComponent.Object
	const DWORD RelativeLocation = 0x120; // Vector RelativeLocation;//[Offset: 0x120,
	const DWORD RelativeRotation = 0x12c; // Rotator RelativeRotation;//[Offset: 0x12c,
	const DWORD Position = 0x160; // doesnt need update 
	const DWORD IsVisible = 0x21c;///SceneComponent.ActorComponent.Object , bool bVisible;//(ByteOffset: 0, ByteMask: 1, FieldMask: 1)[Offset:
	// Bone
	namespace Bone {
		const DWORD Mesh = 0x37c; // SkeletalMeshComponent* Mesh;//[Offset: 0x320, / tmpOffset Class: Character.Pawn.Actor.Object
		//dont touch body it doesnt need update
		const DWORD BodyAddv = 0x150; //SceneComponent* HomingTargetComponent //Class: ProjectileMovementComponent.MovementComponent.ActorComponent.Object ??
		const DWORD MinLOD = 0x6e4; // int MinLOD;//[Offset: 0x5b0, / boneOffset Class: StaticMeshComponent.MeshComponent.PrimitiveComponent.SceneComponent.ActorComponent.Object
	}

	// Camera
	namespace Camera {
		const DWORD LocalController = 0x3194; //STExtraPlayerController* STPlayerController;//[Offset
		const DWORD PlayerCameraManager = 0x3a0;// Class: PlayerController.Controller.Actor.Object -> PlayerCameraManager* PlayerCameraManager;//[Offset: 0x340,
		const DWORD CameraCache = 0x3a0; // Class: PlayerCameraManager.Actor.Object -> CameraCacheEntry CameraCache;//[Offset: 0x350,
		const DWORD POV = 0x10; // Class: CameraCacheEntry -> MinimalViewInfo POV;//[Offset: 0x10,
		const DWORD Location = 0x0; // Class: MinimalViewInfo -> Vector Location;//[Offset: 0x0,
		const DWORD Rotation = 0x18; // Class: MinimalViewInfo -> Rotator Rotation;//[Offset: 0x18,
		const DWORD FOV = 0x24; // Class: MinimalViewInfo -> float FOV;//[Offset: 0x24,
	}


	///////
	const DWORD bEnablePlayerPickUpAnim = 0x18c4;//float voiceCheckShowCD;//[Offset:Class: STExtraBaseCharacter.STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
	//Game Status
	const DWORD GameStateBase = 0x13c; //Class: World.Object   GameStateBase* GameState;//[Offset:
	const DWORD AlivePlayerNum = 0x814; //Class: STExtraGameStateBase.UAEGameState.LuaGameState.GameState.GameStateBase.Info.Actor.Object  int AlivePlayerNum;//[Offset:
	const DWORD ElapsedTime = 0x378; //Class: GameState.GameStateBase.Info.Actor.Object -> int ElapsedTime;//[Offset:
	const DWORD AliveTeamNum = 0x818; //int AliveTeamNum;//[Offset:
	const DWORD PlayerNum = 0xb0c; // int PlayerNumPerTeam;//[Offset: 0xb0c, Size: 4]//[Offset: Class: STExtraGameStateBase.UAEGameState.LuaGameState.GameState.GameStateBase.Info.Actor.Object
	const DWORD CurCircleWave = 0x7a0; //int CurCircleWave;//[Offset:
	const DWORD GameModeID = 0xc18; //Class: STExtraGameStateBase.UAEGameState.LuaGameState.GameState.GameStateBase.Info.Actor.Object  ->  FString GameModeID;//[Offset:




	//Class: Actor.Object
	const DWORD ReplicatedMovement = 0x80;//RepMovement ReplicatedMovement;

	////vehicle
		//Class: STExtraCharacter.UAECharacter.Character.Pawn.Actor.Object
	const DWORD CurrentVehicle = 0xa74;//STExtraVehicleBase* CurrentVehicle;

	//Class: VehicleCommonComponent.VehicleComponent.LuaActorComponent.ActorComponent.Object
	namespace vehicle {
		const DWORD VehicleCommon = 0x7d0; // VehicleCommonComponent* VehicleCommon;//[Offset:
		const  DWORD lastForwardSpeed = 0x800;  // 2.4
		const DWORD bIsEngineStarted = 0x7b4;//bool bIsEngineStarted;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0x77d, Size: 1]

		//Class: VehicleCommonComponent.VehicleComponent.LuaActorComponent.ActorComponent.Object
		const DWORD HP = 0x200; // Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float HP;//[Offset: 0x11c, Size: 4]
		const DWORD HPMax = 0x1fc; // Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float HPMax;//[Offset: 0x118,
		const DWORD FuelMax = 0x258; // Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float FuelMax;//[Offset: 0x130,
		const DWORD Fuel = 0x25c; // Class: VehicleCommonComponent.VehicleComponent.ActorComponent.Object -> float Fuel;//[Offset: 0x134,
	}

}