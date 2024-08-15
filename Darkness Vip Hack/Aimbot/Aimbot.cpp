#include "Aimbot.h"
#include"Memory.h"
#include<thread>



bool Aimbot::InsideFov(float OverlayScreenWidth, float OverlayScreenHeight, VECTOR2 PlayerW2SBone, float FovRadius)
{
	VECTOR2 Cenpoint;
	Cenpoint.X = PlayerW2SBone.X - (OverlayScreenWidth / 2);
	Cenpoint.Y = PlayerW2SBone.Y - (OverlayScreenHeight / 2);

	if (Cenpoint.X * Cenpoint.X + Cenpoint.Y * Cenpoint.Y <= FovRadius * FovRadius)
	{
		return true;
	}


	return false;
}

VECTOR3 GetmyPosition()
{
	VECTOR3 MyPosition{ 0, 0, 0 }; // Default position

	DWORD MeshAddv = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Bone::Mesh);
	DWORD BodyAddv = MeshAddv + Offset::Bone::BodyAddv;
	DWORD BoneAddv = Utility::ReadMemoryEx<DWORD>(MeshAddv + Offset::Bone::MinLOD) + 48;
	MyPosition = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48);

	return MyPosition;
}

float GetbulletSpeed()
{
	// Read the necessary memory addresses to retrieve the bullet speed
	DWORD CharacterWeaponManagerComponent = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Hacks::WeaponManagerComponent);
	DWORD CurrentWeaponReplicated = Utility::ReadMemoryEx<DWORD>(CharacterWeaponManagerComponent + Offset::Hacks::CurrentWeaponReplicated);
	DWORD ShootWeaponEntity = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::ShootWeaponEntity);
	float BulletSpeed = Utility::ReadMemoryEx<FLOAT>(ShootWeaponEntity + Offset::Hacks::BulletFireSpeed);

	// Return the bullet speed
	return BulletSpeed;
}

float GetBulletGravityA()
{
	// Read the necessary memory addresses to retrieve the bullet speed
	DWORD CharacterWeaponManagerComponent = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Hacks::WeaponManagerComponent);
	DWORD CurrentWeaponReplicated = Utility::ReadMemoryEx<DWORD>(CharacterWeaponManagerComponent + Offset::Hacks::CurrentWeaponReplicated);
	DWORD ShootWeaponEntity = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::ShootWeaponEntity);
	uintptr_t  BulletTemplate = Utility::ReadMemoryEx<uintptr_t>(ShootWeaponEntity + 0x41c); //class STExtraShootWeaponBulletBase* BulletTemplate;//[Offset: 0x41c, Size: 4] //Class: ShootWeaponEntity.WeaponEntity.WeaponLogicBaseComponent.ActorComponent.Object
	float LaunchGravityScale = Utility::ReadMemoryEx<FLOAT>(ShootWeaponEntity + 0x414); //float LaunchGravityScale;//[Offset: 0x414, Size: 4] //Class: STExtraShootWeaponBulletBase.LuaActor.Actor.Object

	// Return the bullet speed
	return LaunchGravityScale;
}

VECTOR3 Getvelocity(const AActor& actor)
{
	uint32_t curVehicle = Utility::ReadMemoryEx<uint32_t>(actor.Address + Offset::CurrentVehicle);
	if (curVehicle)
	{
		return Utility::ReadMemoryEx<VECTOR3>(curVehicle + Offset::ReplicatedMovement);
	}
	else
	{
		return actor.Velocity;
	}
}

VECTOR3 subtract(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result;
	Result.X = Src.X - Dst.X;
	Result.Y = Src.Y - Dst.Y;
	Result.Z = Src.Z - Dst.Z;
	return Result;
}

float magnitude(VECTOR3 Vec)
{
	return sqrtf(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z);
}

float getDistance(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result = subtract(Src, Dst);
	return magnitude(Result);
}


bool IsweaponFiring(DWORD AActorAddress) {
	return Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::bIsWeaponFiring); // bool bIsWeaponFiring;
}

bool Isscoping(DWORD AActorAddress) {
	return Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::bIsGunADS); 	//bool bIsGunADS;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0xc29, Size: 1]
}



bool IsMyPlayerHoldingGun(DWORD AActorAddress) {
	DWORD CharacterWeaponManagerComponent = Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::WeaponManagerComponent);
	if (CharacterWeaponManagerComponent) {
		DWORD CurrentWeaponReplicated = Utility::ReadMemoryEx<DWORD>(CharacterWeaponManagerComponent + Offset::Hacks::CurrentWeaponReplicated);
		if (CurrentWeaponReplicated) {
			INT totalBullets = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::CurBulletNumInClip); //int CurBulletNumInClip;//[Offset: 0xbd0, Size: 4]
			//	INT CurMaxBulletNumInOneClip = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + 0xbe4); //	int CurMaxBulletNumInOneClip;//[Offset: 0xbe4, Size: 4]
			DWORD ShootWeaponEntity = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::ShootWeaponEntity);
			if (ShootWeaponEntity) {
				if (totalBullets <= 150 && totalBullets > 0) {
					return true;
				}
			}
		}
	}
	return false;
}

// Function to calculate the predicted position
auto calculatePredictedPosition = [&](const AActor& actor, VECTOR3& targetPos) {
	VECTOR3 myPosition = GetmyPosition();
	float bulletSpeed = GetbulletSpeed();
	float gravity = GetBulletGravityA();

	if (bulletSpeed > 0) {
		VECTOR3 velocity = Getvelocity(actor);
		float distance = getDistance(myPosition, targetPos) / 100.0f;
		float bulletTravelTime = distance / (bulletSpeed / 100.f);
		float zAssist = 1.0f;

		targetPos.X += velocity.X * bulletTravelTime;
		targetPos.Y += velocity.Y * bulletTravelTime;
		//targetPos.Z += velocity.Z * bulletTravelTime * zAssist + 50.5f * 5.72f * bulletTravelTime * bulletTravelTime;
		targetPos.Z += velocity.Z * bulletTravelTime + 0.5f * gravity * bulletTravelTime * bulletTravelTime;
	}
};

VECTOR2 Aimbot::GetClosestEnemy()
{
	static int lockedTargetIndex = -1; // Index of the locked target in the actor list
	static VECTOR2 lockedTargetCoordinates = { 0, 0 }; // Screen coordinates of the locked target

	if (Settings::aimbotmode == 1) {
		// Locked target mode
		if (lockedTargetIndex >= 0 && lockedTargetIndex < Data::AActorList.size()) {
			const AActor& lockedActor = Data::AActorList[lockedTargetIndex];

			// Check if the locked target is still valid
			if (!(lockedActor.IsBot && Settings::SkipBots) && (lockedActor.Health > 0 || Settings::knocked)) {
				VECTOR3 targetPos;
				switch (Settings::curraim) {
				case 0:
					targetPos = lockedActor.HeadPos;
					targetPos.Z += 7;
					break;
				case 1:
					targetPos = lockedActor.ChestPos;
					break;
				case 2:
					targetPos = lockedActor.PelvisPos;
					break;
				default:
					targetPos = lockedActor.HeadPos;
					targetPos.Z += 7;
					break;
				}

				// Apply bullet tracking prediction
				calculatePredictedPosition(lockedActor, targetPos);

				VECTOR2 screen;
				int dist; // Initialize dist variable

				// Calculate screen coordinates and distance
				if (Algorithm::WorldToScreenBone(Esp::ViewMatrix, targetPos, screen, &dist)) {
					// Skip locked target if it goes outside maximum aim distance or FOV if FOV-based aiming is enabled
					if (dist <= Settings::MaxAimDistence && (!Settings::Fovbased || Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, screen, Settings::fovcircleredus))) {
						// Update locked target coordinates and return
						lockedTargetCoordinates = screen;
						return lockedTargetCoordinates;
					}
					else {
						// Reset locked target if it's no longer valid
						lockedTargetIndex = -1;
					}
				}
			}
		}
	}

	// Closest enemy mode or no valid locked target
	float targetDistance = 9999.0f;
	VECTOR2 targetCoordinates = { 0, 0 };

	if (Data::AActorList.empty())
		return targetCoordinates;

	VECTOR3 myPosition = GetmyPosition();
	float bulletSpeed = GetbulletSpeed();

	for (int i = 0; i < Data::AActorList.size(); i++) {
		const AActor& actor = Data::AActorList[i];

		// Skip bots or knocked enemies based on settings
		if ((actor.IsBot && Settings::SkipBots) || (actor.Health <= 0 && !Settings::knocked))
			continue; // Skip this actor and move to the next one

		// Calculate screen coordinates of the enemy's position
		VECTOR2 screen;
		int dist; // Initialize dist variable

		// Calculate screen coordinates and distance
		if (!Algorithm::WorldToScreenBone(Esp::ViewMatrix, actor.Position, screen, &dist))
			continue; // Skip this actor and move to the next one if WorldToScreenBone fails

		// Skip enemies outside maximum aim distance or not in FOV if FOV-based aiming is enabled
		if (dist > Settings::MaxAimDistence || (Settings::Fovbased && !Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, screen, Settings::fovcircleredus)))
			continue; // Skip this actor and move to the next one

		if (Settings::visbulletcheck && !actor.IsVisible)
			continue;

		// Calculate distance from crosshair
		float crossDist = sqrt(pow(screen.X - DX11Window::Width / 2, 2) + pow(screen.Y - DX11Window::Height / 2, 2));

		// Update closest enemy if this one is closer
		if (crossDist < targetDistance) {
			VECTOR3 targetPos;
			switch (Settings::curraim) {
			case 0:
				targetPos = actor.HeadPos;
				targetPos.Z += 7;
				break;
			case 1:
				targetPos = actor.ChestPos;
				break;
			case 2:
				targetPos = actor.PelvisPos;
				break;
			default:
				targetPos = actor.HeadPos;
				targetPos.Z += 7;
				break;
			}

			// Bullet tracking prediction
			calculatePredictedPosition(actor, targetPos);

			// Convert world coordinates to screen coordinates
			VECTOR2 predictedScreen;
			if (Algorithm::WorldToScreenBone(Esp::ViewMatrix, targetPos, predictedScreen, &dist)) {
				targetCoordinates = predictedScreen;
				targetDistance = crossDist;

				if (Settings::aimbotmode == 1) {
					// Lock onto this target
					lockedTargetIndex = i;
					lockedTargetCoordinates = predictedScreen;
				}
			}
		}
	}

	if (Settings::aimbotmode == 0) {
		// Reset locked target when switching to closest mode
		lockedTargetIndex = -1;
	}

	return targetCoordinates;
}



VOID Aimbot::AimbotThread()
{
	INT Num = 0;
	INT Num2 = 0;
	//	FLOAT Setting::Aimspeed = 0;
	FLOAT Num4 = 0;
	FLOAT Num5 = 0;
	VECTOR2 MagicCoordinate;

	VECTOR2 Head;
	Head.X = 0;
	Head.Y = 0;
	FLOAT X = 0;
	FLOAT Y = 0;

	while (true)
	{

		//Sleep(10);
		if (Settings::AimBot && !Settings::ShowMenu)
		{
			if (Data::AActorList.size() != 0)
			{

				if ((GetAsyncKeyState(Settings::AimKey) & 0x8000) && IsMyPlayerHoldingGun(Data::LocalPlayer)) // Left Mouse button
				{
					Head = GetClosestEnemy();
					if ((Head.X > 0 && Head.Y > 0))
					{
						Num = DX11Window::Width / 2;
						Num2 = DX11Window::Height / 2;
						//Setting::Aimspeed = 11;  // Aim speed
						Num4 = 0.0f;
						Num5 = 0.0f;

						X = Head.X;
						Y = Head.Y;

						if (X > 0)
						{
							if (X > (float)Num)
							{
								Num4 = -((float)Num - X);
								Num4 /= Settings::AimSpeed;
								if (Num4 + (float)Num > (float)(Num * 2))
								{
									Num4 = 0.0f;
								}
							}

							if (X < (float)Num)
							{
								Num4 = X - (float)Num;
								Num4 /= Settings::AimSpeed;
								if (Num4 + (float)Num < 0.0f)
								{
									Num4 = 0.0f;
								}
							}
						}

						if (Y > 0)
						{
							if (Y > (float)Num2)
							{
								Num5 = -((float)Num2 - Y);
								Num5 /= Settings::AimSpeed;
								if (Num5 + (float)Num2 > (float)(Num2 * 2))
								{
									Num5 = 0.0f;
								}
							}

							if (Y < (float)Num2)
							{
								Num5 = Y - (float)Num2;
								Num5 /= Settings::AimSpeed;
								if (Num5 + (float)Num2 < 0.0f)
								{
									Num5 = 0.0f;
								}
							}
						}

						if (Settings::macroval > 0 && IsweaponFiring(Data::LocalPlayer)) {

							Num5 += Settings::macroval;
						}
						
						mouse_event(1U, (int)Num4, (int)Num5, NULL, NULL);
					}
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(25));
		}
		else {
			std::this_thread::sleep_for(std::chrono::seconds(3)); // Sleeps for 3 seconds
		}
	}
}