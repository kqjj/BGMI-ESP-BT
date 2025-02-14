#pragma once

#include "Includes.h"
#include "Utility\Utility.h"
#include "Settings\Settings.h"
#include "Algorithm\Algorithm.h"
#include "..\Offset.h"
#include "Global\Global.h"
struct AActor
{
	bool isAimingAtMe;
	FRotator ToRotatorToMe;
	FRotator RelativeRotation;
	VECTOR3 RelativeLocation;
	bool IsBot;
	bool IsVisible;
	uint32_t CurrentVehcile;
	VECTOR3 Position;
	FLOAT IsDead;
	FLOAT Health;
	FLOAT HealthMax;
	FLOAT KnockedHealth;
	string Name;
	string weapon;
	string weapon2;
	string Nation;
	INT TeamId;
	DWORD Address;
	VECTOR3 Velocity;
	FLOAT PlayerDead;
	INT PlayerSt;
	int status;
	int kills;
	VECTOR3 HeadPos;
	VECTOR3 RandomPos;
	VECTOR3 ChestPos;
	VECTOR3 PelvisPos;
	VECTOR3 lSholderPos;
	VECTOR3 rSholderPos;
	VECTOR3 lElbowPos;
	VECTOR3 rElbowPos;
	VECTOR3 lWristPos;
	VECTOR3 rWristPos;
	VECTOR3 lThighPos;
	VECTOR3 rThighPos;
	VECTOR3 lKneePos;
	VECTOR3 rKneePos;
	VECTOR3 lAnklePos;
	VECTOR3 rAnklePos;
};


struct Item
{
	string Name;
	VECTOR3 Position;
};

struct Vehicle
{
	float oil;
	float hp;
	float hpmax;
	float oilmax;
	string Name;
	VECTOR3 Position;
	bool driving;
};

struct Itemb {
	std::string Displayname;
	ImVec4 colorcod;

};
struct Airdrop
{
	int picidm;
	std::vector<Itemb> boxitemm;
	string Name;
	VECTOR3 Position;

};
struct Deadbox
{
	int picid;
	std::vector<Itemb> boxitem;
	string Name;
	VECTOR3 Position;
};



class Espp {
public:

	std::string airdropstring;
	std::vector<Deadbox> lootbox, lootboxr;
	VECTOR3 mypos;
	DWORD myadd;
	std::vector<Airdrop> AirDropBox, AirDropBoxr;

	Airdrop lboxx;
	Deadbox lbox;
};
extern Espp* g_pEsp;
namespace Data
{
	extern DWORD uLevel;
	extern CameraCacheEntry CameraCache;

	extern DWORD LocalController;
	extern uint32_t ActorsPointerAddress;
	extern DWORD ViewMatrixBase;
	extern DWORD libUE4Base;
	extern DWORD UWorld;
	extern DWORD PlayerCameraManager;
	extern bool InLobby;
	extern DWORD NetDriver;
	extern DWORD LocalPlayer;
	extern DWORD PlayerController;
	extern DWORD EntityAddress;
	extern string Map;

	extern vector<AActor> AActorList;
	extern vector<Item> ItemList;
	extern vector<Vehicle> VehicleList;

	extern int PlayerTeamID;
	extern int PlayerLevel;
	extern int PlayerTotalKills;
	extern string PlayerUID;
	extern FLOAT PlayerTravelDistance;
	extern FLOAT PlayerHealth;
	extern string PlayerNation;
	extern string PlayerPlayerName;
	extern VECTOR3 AimingCoordinates;

	DWORD GetViewMatrixBase(DWORD StartAddress, DWORD EndAddress);
	DWORD GetUE4BaseAddress();
	VOID InjectLibrary();
	VOID QueryThread();
};