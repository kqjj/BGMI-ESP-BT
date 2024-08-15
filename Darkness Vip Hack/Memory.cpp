
#include "Memory.h"
#include "Aimbot\Aimbot.h"
#include <thread>
#include <imgui_notify.h>
#include <imgui_notify.h>
#include <random>
#include <vector>

//this shell code needs update

BYTE MagicBulletShell[60]//old
{
	0xC7, 0x45, 0x78, 0x00, 0x00, 0x00, 0x00,
	0x83, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x74, 0x0E,
	0x60,
	0x8B, 0x5D, 0x50,
	0x8B, 0x53, 0x18,
	0x8A, 0x02,
	0x3C, 0x88, //need update
	0x74, 0x02,
	0x61,
	0xC3,
	0x8A, 0x42, 0x01,
	0x3C, 0xF4,  //need update
	0x75, 0x14,
	0xC7, 0x83, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xC7, 0x83, 0x84, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xEB, 0xE1

};

BYTE MagicBulletSearch1[] =   { 0x66, 0x0F, 0x7E, '?', 0x80, 0x02, 0x00, 0x00, 0xC7, 0x45, 0x78, 0x20 };

//BYTE BTSearch[] = { 0x66, 0x0F, 0x7E, '?', 0x80, 0x02, 0x00, 0x00, 0xC7, 0x45 };

//SEARCH BYTE :- 0x66, 0x0F, '?', '?', '?', 0x02, 0x00, 0x00, 0xC7, '?', '?', '?', 0xEE

DWORD MagicBulletAddress = 0;
vector<DWORD_PTR> MagicBulletList = {};
INT MagicBulletHook = 0;
BYTE RealByteCode[7];
bool  Memory::IsMagicInitialized = false;

// New global variables for bullet tracking percentage
bool bTrackBullets = false;
std::vector<bool> BulletTrackList;
int BulletCountInClip = 0;
int CurrentBulletIndex = 0;

VECTOR3 Subtract(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result;
	Result.X = Src.X - Dst.X;
	Result.Y = Src.Y - Dst.Y;
	Result.Z = Src.Z - Dst.Z;
	return Result;
}

FRotator ToRotator(VECTOR3 local, VECTOR3 target) {
	VECTOR3 rotation = Subtract(local, target);

	FRotator newViewAngle = { 0 };

	float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

	newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float)3.14159265358979323846);
	newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float)3.14159265358979323846);
	newViewAngle.Roll = (float)0.f;

	if (rotation.X >= 0.f)
		newViewAngle.Yaw += 180.0f;

	return newViewAngle;
}

VECTOR3 FRotatorToVector(FRotator ft)
{
	FLOAT angle, sr, sp, sy, cr, cp, cy;

	angle = ft.Yaw * (3.1415926535897f * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);

	angle = ft.Pitch * (3.1415926535897f * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);

	angle = ft.Roll * (3.1415926535897f * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);
	VECTOR3 dd;
	dd.X = cp * cy;
	dd.Y = cp * sy;
	dd.Z = -sp;

	return dd;
}

VECTOR3 MULTIPLYVECT(VECTOR3 ve, float value)
{
	VECTOR3 vec;
	vec.X = ve.X * value;
	vec.Y = ve.Y * value;
	vec.Z = ve.Z * value;
	return vec;

}
VECTOR3 ADDVECTORS(VECTOR3 ve, VECTOR3 ve2)
{
	VECTOR3 vec;
	vec.X = ve.X + ve2.X;
	vec.Y = ve.Y + ve2.Y;
	vec.Z = ve.Z + ve2.Z;
	return vec;

}

VECTOR2 static ClampAngle(VECTOR2 qaAng)
{
	VECTOR2 ret;
	ret.X = qaAng.X;
	ret.Y = qaAng.Y;

	if (qaAng.X > 89.0f && qaAng.X <= 180.0f)
		ret.X = 89.0f;

	if (qaAng.X > 180.0f)
		ret.X = qaAng.X - 360.0f;

	if (qaAng.X < -89.0f)
		ret.X = -89.0f;

	if (qaAng.Y > 180.0f)
		ret.Y = qaAng.Y - 360.0f;

	if (qaAng.Y < -180.0f)
		ret.Y = qaAng.Y + 360.0f;

	//ret.Z = 0;

	return ret;
}

void ClampAngles(FRotator& angles) {
	if (angles.Pitch > 180)
		angles.Pitch -= 360;
	if (angles.Pitch < -180)
		angles.Pitch += 360;

	if (angles.Pitch < -75.f)
		angles.Pitch = -75.f;
	else if (angles.Pitch > 75.f)
		angles.Pitch = 75.f;

	while (angles.Yaw < -180.0f)
		angles.Yaw += 360.0f;
	while (angles.Yaw > 180.0f)
		angles.Yaw -= 360.0f;
}

VOID GetMagicAddress()
{
	std::vector<DWORD_PTR> FoundedBase;
	{
		Utility::MemSearch(MagicBulletSearch1, sizeof(MagicBulletSearch1), 0x0D000000, 0x10000000, 0, 0, FoundedBase);
	}

	for (int i = 0; i < FoundedBase.size(); i++)
	{
		if (Utility::ReadMemoryEx<BYTE>(FoundedBase[i] + 0xC) == 0xEE) // Need update // 0x3F
		{
			MagicBulletList.push_back(FoundedBase[i]);
			MagicBulletAddress = FoundedBase[i];
		}
	}

	FoundedBase.resize(0);
}

VOID InitializeMagic()
{
	INT Addv = MagicBulletAddress;

	if (Addv > 0) {
		MagicBulletHook = (INT)VirtualAllocEx(Game::hProcess, 0, 500, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!MagicBulletHook) return;


		WriteProcessMemory(Game::hProcess, (LPVOID)MagicBulletHook, &MagicBulletShell, sizeof(MagicBulletShell), 0);

		Utility::WriteMemoryEx<BYTE>(MagicBulletHook + 0x13, 0x50);


		Utility::WriteMemoryEx<INT>(MagicBulletHook + 9, MagicBulletHook + 0x5E);
		ReadProcessMemory(Game::hProcess, (LPCVOID)(Addv + 0x8), &RealByteCode, sizeof(RealByteCode), 0);
		WriteProcessMemory(Game::hProcess, (LPVOID)(MagicBulletHook), &RealByteCode, sizeof(RealByteCode), 0);
	}
}

VOID HookCall(INT Address, INT HookAdress)
{
	BYTE Shell[7] = { 0xE8, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90 };
	*(INT*)(Shell + 1) = (INT)(HookAdress - Address - 5);
	WriteProcessMemory(Game::hProcess, (LPVOID)Address, &Shell, sizeof(Shell), 0);
}

bool IsEqual(BYTE Array1[], BYTE Array2[])
{
	for (int i = 0; i < 6; i++)
	{
		if (Array1[i] != Array2[i])
		{
			return false;
		}
	}

	return true;
}

bool Hooked(int Address)
{
	unsigned char Tmp[7];
	ReadProcessMemory(Game::hProcess, (LPCVOID)(Address + 0x8), &Tmp, sizeof(Tmp), 0);

	if ((Tmp[0] == 0xE8 && Tmp[5] == 0x90 && Tmp[6] == 0x90))
	{
		return true;
	}

	return false;
}

VOID HookMagic()
{
	if (MagicBulletList.size() != NULL)
	{
		for (DWORD_PTR& Addv : MagicBulletList)
		{
			BYTE Tmp[7];
			ReadProcessMemory(Game::hProcess, (LPCVOID)((int)Addv + 0x8), &Tmp, sizeof(Tmp), 0);

			if (IsEqual(Tmp, RealByteCode))
			{
				HookCall((INT)(Addv + 0x8), (INT)MagicBulletHook);
			}
		}
	}
}

VOID Memory::RestoreHook()
{
	if (MagicBulletList.size() != NULL)
	{
		for (DWORD_PTR& Addv : MagicBulletList)
		{
			if (Hooked(Addv))
			{
				WriteProcessMemory(Game::hProcess, (LPVOID)(Addv + 0x8), &RealByteCode, sizeof(RealByteCode), 0);
			}
		}
	}
}




// Function to initialize bullet tracking list based on percentage
void InitializeBulletTracking(int totalBullets, float percentage) {
	BulletTrackList.clear();
	BulletCountInClip = totalBullets;
	int bulletsToTrack = static_cast<int>(totalBullets * percentage);

	// Initialize all bullets to false (not tracked)
	BulletTrackList.resize(totalBullets, false);

	// Randomly set a number of bullets to true (tracked) based on the percentage
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, totalBullets - 1);

	for (int i = 0; i < bulletsToTrack; ++i) {
		int index;
		do {
			index = dis(gen);
		} while (BulletTrackList[index]); // Ensure we don't set the same bullet twice

		BulletTrackList[index] = true;
	}

	CurrentBulletIndex = 0;
}


// Check if the current bullet should be tracked
bool ShouldTrackCurrentBullet() {


	if (CurrentBulletIndex < BulletTrackList.size()) {
		return BulletTrackList[CurrentBulletIndex++];
	}
	return false;
	
}

float Magnitude(VECTOR3 Vec)
{
	return sqrtf(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z);
}

float GetDistance(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result = Subtract(Src, Dst);
	return Magnitude(Result);
}

VECTOR3 NormalizeVec(VECTOR3 Vector)
{
	float Length = Magnitude(Vector);

	Vector.X /= Length;
	Vector.Y /= Length;
	Vector.Z /= Length;

	return Vector;
}
float Distance(VECTOR3 myPos, VECTOR3 enPos)
{
	return sqrt((myPos.X - enPos.X) * (myPos.X - enPos.X) + (myPos.Y - enPos.Y) * (myPos.Y - enPos.Y) + (myPos.Z - enPos.Z) * (myPos.Z - enPos.Z));
}
float BulletDrop(float TravelTime)
{
	return (TravelTime * TravelTime * 980 / 2);
}
bool Fov(float OverlayScreenWidth, float OverlayScreenHeight, VECTOR2 PlayerW2SBone, float FovRadius)
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

std::string playerstatus(int GetEnemyState)
{
	switch (GetEnemyState)
	{
	case 9:
		return "Walking";
		break;
	case 1680:
	case 1672:
	case 1673:
	case 1032:
	case 1544:
	case 1545:
	case 1033:
		return "Peek";
		break;
	case 11:
		return "Running";
		break;
	case 4194304:
		return "Swimming";
		break;
	case 32784:
		return "Reviving";
		break;
	case 16777224:
		return "Climbing";
		break;
	case 16:
	case 17:
	case 19:
		return "Crouch";
		break;
	case 32:
	case 33:
	case 35:
	case 5445:
	case 762:
		return "Snake";
		break;
	case 72:
	case 73:
	case 75:
		return "Jumping";
		break;
	case 131070:
	case 131071:
	case 131072:
	case 131073:
	case 131075:
	case 131074:
		return "Knocked";
		break;
	case 33554440:
	case 524296:
	case 1048584:
	case 524288:
		return "Driving";
		break;
	default:
		return "";
		break;
	}
}

std::string getMyPlayerWeapon(int id) {
	switch (id) {
	case 101006: return "AUG";
	case 101008: return "M762";
	case 101003: return "SCAR-L";
	case 101004: return "M416";
	case 101002: return "M16A4";
	case 101009: return "MK47";
	case 101010: return "G36C";
	case 101007: return "QBZ";
	case 101001: return "AKM";
	case 101005: return "Groza";
	case 102005: return "Bizon";
	case 102004: return "TommyGun";
	case 102007: return "MP5K";
	case 102002: return "UMP";
	case 102003: return "Vector";
	case 102001: return "Uzi";
	case 105002: return "DP28";
	case 105001: return "M249";
	case 103003: return "AWM";
	case 103010: return "QBU";
	case 103009: return "SLR";
	case 103004: return "SKS";
	case 103006: return "Mini14";
	case 103002: return "M24";
	case 103001: return "Kar98k";
	case 103005: return "VSS";
	case 103008: return "Win94";
	case 103007: return "Mk14";
	case 104003: return "S12K";
	case 104004: return "DBS";
	case 104001: return "S686";
	case 104002: return "S1897";
	case 108003: return "Sickle";
	case 108001: return "Machete";
	case 108002: return "Crowbar";
	case 107001: return "CrossBow";
	case 108004: return "Pan";
	case 106006: return "SawedOff";
	case 106003: return "R1895";
	case 106008: return "Vz61";
	case 106001: return "P92";
	case 106004: return "P18C";
	case 106005: return "R45";
	case 106002: return "P1911";
	case 106010: return "DesertEagle";
	case 103011: return "Mosin";
	case 107005: return "PanzerFaust";
	default: return "Weapon";
	}
}

struct fireSpeed {
	char encrypted[5];
};

float DecryptBulletFireSpeed(DWORD shootWeaponEntityComp) {
	DWORD bulletFireSpeedEncAddr = Utility::ReadMemoryEx<DWORD>(shootWeaponEntityComp + Offset::Hacks::BulletFireSpeed + 0x4);
	fireSpeed speed = Utility::ReadMemoryEx<fireSpeed>(bulletFireSpeedEncAddr + 6 * Utility::ReadMemoryEx<unsigned char>(bulletFireSpeedEncAddr + 0x30));

	speed.encrypted[0] ^= speed.encrypted[4];
	speed.encrypted[1] ^= speed.encrypted[4];
	speed.encrypted[2] ^= speed.encrypted[4];
	speed.encrypted[3] ^= speed.encrypted[4];

	float decryptedSpeed;
	std::memcpy(&decryptedSpeed, speed.encrypted, sizeof(float));
	return decryptedSpeed;
}

float Distance(const VECTOR2& p1, const VECTOR2& p2) {
	return sqrt(pow(p1.X - p2.X, 2) + pow(p1.Y - p2.Y, 2));
}

float internalDistance(const VECTOR3& p1, const VECTOR3& p2) {
	return std::sqrt(std::pow(p1.X - p2.X, 2) + std::pow(p1.Y - p2.Y, 2) + std::pow(p1.Z - p2.Z, 2));
}


VECTOR3 GetMyPosition()
{
	VECTOR3 MyPosition{ 0, 0, 0 }; // Default position

	DWORD MeshAddv = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Bone::Mesh);
	DWORD BodyAddv = MeshAddv + Offset::Bone::BodyAddv;
	DWORD BoneAddv = Utility::ReadMemoryEx<DWORD>(MeshAddv + Offset::Bone::MinLOD) + 48;
	MyPosition = Algorithm::GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48);

	return MyPosition;
}

float GetBulletSpeed()
{
	// Read the necessary memory addresses to retrieve the bullet speed
	DWORD CharacterWeaponManagerComponent = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Hacks::WeaponManagerComponent);
	DWORD CurrentWeaponReplicated = Utility::ReadMemoryEx<DWORD>(CharacterWeaponManagerComponent + Offset::Hacks::CurrentWeaponReplicated);
	DWORD ShootWeaponEntity = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::ShootWeaponEntity);
	float BulletSpeed = Utility::ReadMemoryEx<FLOAT>(ShootWeaponEntity + Offset::Hacks::BulletFireSpeed);

	// Return the bullet speed
	return BulletSpeed;
}

float GetBulletGravity()
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

VECTOR3 GetVelocity(const AActor& actor)
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

std::string HasMyPlayerGun(DWORD AActorAddress) {
	DWORD CharacterWeaponManagerComponent = Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::WeaponManagerComponent);
	if (CharacterWeaponManagerComponent) {
		DWORD CurrentWeaponReplicated = Utility::ReadMemoryEx<DWORD>(CharacterWeaponManagerComponent + Offset::Hacks::CurrentWeaponReplicated);
		if (CurrentWeaponReplicated) {
			INT totalBullets = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated +  Offset::Hacks::CurBulletNumInClip); //int CurBulletNumInClip;//[Offset: 0xbd0, Size: 4]
		//	INT CurMaxBulletNumInOneClip = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + 0xbe4); //	int CurMaxBulletNumInOneClip;//[Offset: 0xbe4, Size: 4]
			DWORD ShootWeaponEntity = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::ShootWeaponEntity);
			if (ShootWeaponEntity) {

				float id = Utility::ReadMemoryEx<DWORD>(ShootWeaponEntity + Offset::Hacks::UploadInterval); //float UploadInterval

				if (totalBullets <= 150 && totalBullets > 0) {


					InitializeBulletTracking(totalBullets, Settings::percentage); //0.5f; // Default to 50%

				}

				if (id != NULL) {
					return getMyPlayerWeapon(id);
				}
			
			}

		}
	}
	return "Fist";
}

bool IsWeaponFiring(DWORD AActorAddress) {
	return Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::bIsWeaponFiring); // bool bIsWeaponFiring;
}

bool IsScoping(DWORD AActorAddress) {
	return Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::bIsGunADS); 	//bool bIsGunADS;//(ByteOffset: 0, ByteMask: 1, FieldMask: 255)[Offset: 0xc29, Size: 1]
}

void BypassFov() {

	auto PartHitComponent1 = Utility::ReadMemoryEx<uintptr_t>(Data::LocalPlayer + Offset::Hacks::PartHitComponent);

	if (PartHitComponent1)
	{
		int ConfigCollisionDistSqAngles1 = Utility::ReadMemoryEx<int>(PartHitComponent1 + Offset::Hacks::ConfigCollisionDistSqAngles);

		for (int i = 0; i < 0xC; i++)
		{
			int toMultiply = (i * 0x4);
			Utility::WriteMemoryEx<float>(ConfigCollisionDistSqAngles1 + toMultiply, 180.0f);
		}
	}

}

// Define a Result structure for the quadratic solver
struct Result {
	bool hasResult;
	float a, b;
};

// Quadratic Solver
Result MidnightSolver(float a, float b, float c) {
	double subsquare = b * b - 4 * a * c;
	if (subsquare < 0)
		return { false, 0.0f, 0.0f };
	return { true,
			(float)((-b + std::sqrt(subsquare)) / (2 * a)),
			(float)((-b - std::sqrt(subsquare)) / (2 * a)) };
}


std::optional<VECTOR3> SphereLinePrediction(const VECTOR3& me, const VECTOR3& target, const VECTOR3& targetSpeed, float bulletSpeed, float gravity) {
	VECTOR3 relativePos = Subtract(me, target);

	float a = (targetSpeed.X * targetSpeed.X) + (targetSpeed.Y * targetSpeed.Y) + (targetSpeed.Z * targetSpeed.Z) - (bulletSpeed * bulletSpeed);
	float b = (-2 * relativePos.X * targetSpeed.X) + (-2 * relativePos.Y * targetSpeed.Y) + (-2 * relativePos.Z * targetSpeed.Z);
	float c = (relativePos.X * relativePos.X) + (relativePos.Y * relativePos.Y) + (relativePos.Z * relativePos.Z);

	Result r = MidnightSolver(a, b, c);

	if (r.hasResult) {
		float t = -1.0f;
		if (r.a >= 0 && (r.b < 0 || r.a < r.b)) {
			t = r.a;
		}
		else if (r.b >= 0) {
			t = r.b;
		}

		if (t >= 0) {
			VECTOR3 hitPos = ADDVECTORS(target, MULTIPLYVECT(targetSpeed, t));

			// Adjust for bullet drop due to gravity
			hitPos.Z -= 0.5f * gravity * t * t;

			return hitPos;
		}
	}
	return std::nullopt;
}




VECTOR3 KinematicEquationPrediction(const VECTOR3& myPosition, const VECTOR3& headPos, const VECTOR3& velocity, float bulletSpeed, float gravity) {
	VECTOR3 predictedPos = headPos;

	if (bulletSpeed > 0) {
		float distance = GetDistance(myPosition, headPos) / 100.0f;
		float bulletTravelTime = distance / (bulletSpeed / 100.f);
	//	float zAssist = 1.0f;

		predictedPos.X += velocity.X * bulletTravelTime;
		predictedPos.Y += velocity.Y * bulletTravelTime;
	//	predictedPos.Z += velocity.Z * bulletTravelTime * zAssist + 50.5f * 5.72f * bulletTravelTime * bulletTravelTime;
		predictedPos.Z += velocity.Z* bulletTravelTime + 0.5f * gravity * bulletTravelTime * bulletTravelTime;
		
	}

	return predictedPos;
}

void Memory::RefreshMagic()
{
	Memory::RestoreHook();
	MagicBulletList.clear();
	VirtualFreeEx(Game::hProcess, (LPVOID)MagicBulletHook, 0, MEM_RELEASE);
	MagicBulletAddress = 0;
	MagicBulletHook = 0;
	ZeroMemory(RealByteCode, sizeof(RealByteCode));
	Memory::IsMagicInitialized = false;
}


void WriteMagicCoordinates(FLOAT x, FLOAT y) {

	Utility::WriteMemoryEx<FLOAT>(MagicBulletHook + 44, x); //2c
	Utility::WriteMemoryEx<FLOAT>(MagicBulletHook + 54, y); //36

}

VECTOR2 FindMagicTarget()
{
	VECTOR2 TargetCoordinates;
	TargetCoordinates.X = 0;
	TargetCoordinates.Y = 0;
	FLOAT TargetDistance = 9999.0f;
	VECTOR2 Screen;
	INT Distance4 = 0;

	if (Data::AActorList.empty())
		return TargetCoordinates;


	VECTOR3 MyPosition = GetMyPosition(); // Get player's position
	FLOAT BulletSpeed = GetBulletSpeed(); // Get bullet speed of the local player
	FLOAT bulletGravity = GetBulletGravity(); // Get bulletGravity of the local player

	for (const AActor& AActor : Data::AActorList)
	{

		if ((AActor.IsBot && Settings::SkipBots) || (AActor.Health <= 0 && !Settings::knocked))
			continue;


		if (!Algorithm::WorldToScreenBone(Esp::ViewMatrix, AActor.Position, Screen, &Distance4)) {
			continue;
		}

		if (Distance4 > Settings::MaxAimDistence)
			continue;

		if (Settings::Fovbased && !Aimbot::InsideFov(DX11Window::Width, DX11Window::Height, Screen, Settings::fovcircleredus))
			continue;

		if (Settings::visbulletcheck && !AActor.IsVisible)
			continue;

	
		HookMagic();
		FLOAT CrossDist;

		if(Settings::bulletrackMode == 0){

			CrossDist = Distance(Screen, VECTOR2{(float)(DX11Window::Width / 2), (float)(DX11Window::Height / 2)});
		
		}
		else if (Settings::bulletrackMode == 1) {

			//CrossDist = sqrt(pow(Data::CameraCache.POV.Location.X - AActor.Position.X, 2) + pow(Data::CameraCache.POV.Location.Y - AActor.Position.Y, 2) + pow(Data::CameraCache.POV.Location.Z - AActor.Position.Z, 2));
			//CrossDist = CrossDist / 1000.0f;

			CrossDist = internalDistance({ (float)(DX11Window::Width / 2), (float)(DX11Window::Height / 2) },/*Data::CameraCache.POV.Location,*/ AActor.Position);
			CrossDist = CrossDist / 1000.0f;

		}
		
		

		if (CrossDist < TargetDistance) // Assuming TargetDistance is initialized with 9999.0f
		{
			VECTOR3 HeadPos = { 0 };
			VECTOR3 Velocity = { 0 };

			if (Settings::Legitrack) {

				HeadPos = AActor.RandomPos;
			}
			else {
				switch (Settings::curraim)
				{
				case 0:
					HeadPos = AActor.HeadPos;
					HeadPos.Z += 15;
				//	HeadPos.Y += 5;
					break;
				case 1:
					HeadPos = AActor.ChestPos;
					break;
				case 2:
					HeadPos = AActor.PelvisPos;
					break;
				default:
					HeadPos = AActor.HeadPos;
					HeadPos.Z += 7;
					break;
				}
			}

		

			if (playerstatus(AActor.status) == "Peek" && Settings::peekdetect)
			{
				HeadPos = AActor.HeadPos;
				HeadPos.Z += 15;
				HeadPos.Y += 5;

			}

			TargetDistance = CrossDist;
			Velocity = GetVelocity(AActor);


			if (BulletSpeed > 0)
			{
				std::optional<VECTOR3> aimPosition;

				if (Settings::prediction == 0) {
					aimPosition = KinematicEquationPrediction(MyPosition, HeadPos, Velocity, BulletSpeed, bulletGravity/*588.6f*/);
				}
				else if (Settings::prediction == 1) {
					aimPosition = SphereLinePrediction(MyPosition, HeadPos, Velocity, BulletSpeed, bulletGravity/*588.6f*/);
				}
			
				if (aimPosition) {
				
					VECTOR3 AimPos = aimPosition.value();
					float xDif = AimPos.X - MyPosition.X;
					float yDif = AimPos.Y - MyPosition.Y;
					float zDif = AimPos.Z - MyPosition.Z;
					float Hyp = std::sqrt(xDif * xDif + yDif * yDif);

					TargetCoordinates.X = std::atan2(zDif, Hyp) * 180.0f / 3.1415926535897f;
					TargetCoordinates.Y = std::atan2(yDif, xDif) * 180.0f / 3.1415926535897f;
				}

			}
		}
	}


	return TargetCoordinates.X == 0 && TargetCoordinates.Y == 0 ? TargetCoordinates : ClampAngle(TargetCoordinates);
}






VOID Memory::MemoryThread()
{
	static bool magicResetForFist = false; // Declare magicResetForFist
	static bool magicRefreshedForWeapon = false; // Declare magicRefreshedForWeapon
	static bool magicRefreshedForAds = false; //bisgunads
	static bool magicRefreshedForCross = false; //bisguncross
	VECTOR2 MagicCoordinate;
	VECTOR3 AimRotation{};

	while (true)
	{

		if (Data::NetDriver > 0)
		{
			if (Settings::MagicBullet)
			{
				
				if (IsMagicInitialized == false)
				{
					GetMagicAddress();
					InitializeMagic();
					IsMagicInitialized = true;
				}


				if (IsMagicInitialized) {

					std::string weapon = HasMyPlayerGun(Data::LocalPlayer);

					if (weapon != "Fist") {

						if (Settings::BypassFovLimit) {

							BypassFov();
						}
						
						MagicCoordinate = FindMagicTarget();

						if (MagicCoordinate.X != 0.000000 || MagicCoordinate.Y != 0.000000) {
						
							if (Settings::percentage > 0.0f) {
						
								if (ShouldTrackCurrentBullet()) {
						
									WriteMagicCoordinates(MagicCoordinate.X, MagicCoordinate.Y);
									
									
								}
								else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									RestoreHook();
								}
						
							}
							else {
								WriteMagicCoordinates(MagicCoordinate.X, MagicCoordinate.Y);
							//	Settings::notifysate = "hello";
							}
						
						}
						else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							RestoreHook();
						}
					}


					// Refresh magic if player has a weapon
					if (weapon != "Fist" && !magicRefreshedForWeapon)
					{
						RefreshMagic();
						magicRefreshedForWeapon = true; // Set tracking flag
						magicResetForFist = false; // Reset the fist flag
						//Settings::notifysate = "Magic Refreshed : Weapon";
					//	Settings::notifysate = "Prediction: "+to_string(GetBulletGravity());
					}
					// Reset magic if player has "Fist"
					else if (weapon == "Fist" && !magicResetForFist)
					{
						RefreshMagic();
						magicResetForFist = true; // Set tracking flag
						magicRefreshedForWeapon = false; // Reset the weapon flag
						//Settings::notifysate = "Magic Refreshed : Fist";
					}

					//Refresh Magic while ADS 
					if (IsScoping(Data::LocalPlayer) && !magicRefreshedForAds) {

						RefreshMagic();
						magicRefreshedForCross = false;
						magicRefreshedForAds = true;
						//Settings::notifysate = "Magic Refreshed : ADS";
					}
					else if (!IsScoping(Data::LocalPlayer) && !magicRefreshedForCross) {

						RefreshMagic();
						magicRefreshedForCross = true;
						magicRefreshedForAds = false;
						//Settings::notifysate = "Magic Refreshed : NADS";
					}

					// Refresh magic
					if (GetAsyncKeyState(0x52) & 1)
					{

						RefreshMagic();
					}
				}

			}
			else if (Settings::MagicBullet == false && IsMagicInitialized == true)
			{
				RefreshMagic();
				magicRefreshedForWeapon = false; // Set tracking flag
				magicResetForFist = false; // Reset the fist flag
				magicRefreshedForAds = false; 
				magicRefreshedForCross = false;
				//Settings::btrefreshstatus = "Magic Has Been Refreshed : BT Deactivated!";
			}
			else {
				//putting it to deep sleep when bt not true
				std::this_thread::sleep_for(std::chrono::seconds(3)); // Sleeps for 3 seconds
			}

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void Memory::AllMemoryHacks() {

	DWORD libUE4Base = Data::GetUE4BaseAddress();
	if (libUE4Base == 0) {
		MessageBox(NULL, "Can't find base address", "AnimeTone VIP", MB_OKCANCEL);
		return; // Exit the function if base address is not found
	}

	BYTE backupcarsexval = 0;
	bool isbackuptaken = false;

	BYTE backupInternalTrack = 0;
	bool isbackupinternaltaken = false;

	while (true) {

		//car sex
		if (Settings::carsex && (GetAsyncKeyState(Settings::carsexkey) & 0x8000)) {
			if (!isbackuptaken) {
				backupcarsexval = Utility::ReadMemoryEx<BYTE>(libUE4Base + 0xB0); // Ensure the type is BYTE
				isbackuptaken = true;
			}
			Utility::WriteProtectedMemoryEx<BYTE>(libUE4Base + 0xB0, 0x01); // Change to BYTE for consistency
		}
		else if (isbackuptaken) {
			Utility::WriteProtectedMemoryEx<BYTE>(libUE4Base + 0xB0, backupcarsexval);
			isbackuptaken = false;
		}

		//internal track
		if (Settings::internalTrack) {
			if (!isbackupinternaltaken) {
				backupInternalTrack = Utility::ReadMemoryEx<BYTE>(libUE4Base + 0xD0); // Ensure the type is BYTE
				isbackupinternaltaken = true;
			}
			Utility::WriteProtectedMemoryEx<BYTE>(libUE4Base + 0xD0, 0x01);
			Utility::WriteProtectedMemoryEx<FLOAT>(libUE4Base + 0x70, Settings::fovcircleredus);
			Utility::WriteProtectedMemoryEx<FLOAT>(libUE4Base + 0x130, Settings::MaxAimDistence);
			Utility::WriteProtectedMemoryEx<FLOAT>(libUE4Base + 0x80, Settings::curraim);

		}
		else if (isbackupinternaltaken) {
			Utility::WriteProtectedMemoryEx<BYTE>(libUE4Base + 0xD0, backupInternalTrack);
			isbackupinternaltaken = false;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
