#include "Data.h"
#include<thread>
#include <Memory.cpp>
#include <unordered_map>

using namespace std;
using namespace Utility;
using namespace Data;
using namespace Algorithm;


Espp* g_pEsp = new Espp();
DWORD Data::ViewMatrixBase;
DWORD Data::UWorld = 0;
BYTE ViewMatrixSearch[] =
{
	0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01
};

DWORD Data::GetViewMatrixBase(DWORD StartAddress, DWORD EndAddress)
{
	DWORD ViewMatrixBase = 0;
	std::vector<DWORD_PTR> FoundedBase;
	MemSearch(ViewMatrixSearch, sizeof(ViewMatrixSearch), StartAddress, EndAddress, 0, 0, FoundedBase);

	for (int i = 0; i < FoundedBase.size(); i++)
	{
		DWORD Cand = FoundedBase[i] - 0x20;
		DWORD Eng = ReadMemoryEx<DWORD>(Cand) + 0x20;
		DWORD Tmp = ReadMemoryEx<DWORD>(Eng) + 0x200;

		float v1, v2, v3, v4;
		v1 = ReadMemoryEx<float>(Tmp + 0x8);
		v2 = ReadMemoryEx<float>(Tmp + 0x18);
		v3 = ReadMemoryEx<float>(Tmp + 0x28);
		v4 = ReadMemoryEx<float>(Tmp + 0x38);

		if (v1 == 0 && v2 == 0 && v3 == 0 && v4 >= 3)
		{
			ViewMatrixBase = Cand;
			FoundedBase.resize(0);
			break;
		}
	}

	FoundedBase.resize(0);
	return ViewMatrixBase;
}

string GetString(DWORD BaseAddress)
{
	char* String = new char[34];
	for (int i = 0; i < 34; i++)
	{
		String[i] = Utility::ReadMemoryEx<char>(BaseAddress + i);
	}

	string Result = String;

	delete[] String;
	return Result;
}


DWORD libUE4Base;



struct ObjectName
{
	char Data[64];
};

BOOL IsPlayer(string EntityType)
{
	
	if (EntityType.find("BP_PlayerPawn") != string::npos || EntityType.find("BP_PlayerCharacter") != string::npos || EntityType.find("PlanET_FakePlayer") != string::npos || EntityType.find("PlayerPawn_Infec") != string::npos)
	{
		//filtering dead player esp
		//if (EntityType.find("PaintDecalDetectLine1")) return false;

		return TRUE;
	}

	return FALSE;
}



// Predefined set of bone indices
const std::vector<int> predefinedBoneIndices = { 5, 4, 1, 11, 32, 12, 33, 63, 62, 52, 56, 53, 57, 54, 58 };
std::vector<int> weightedBoneIndices = predefinedBoneIndices;

// Function to generate a random bone index from the weighted set
int GetRandomBonePosWithPriority() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, weightedBoneIndices.size() - 1);
	return weightedBoneIndices[dis(gen)];
}

// Function to set or unset priority for a specific bone index
void SetBonePriority(int boneIndex, bool setPriority, int weightFactor) {
	if (setPriority) {
		weightedBoneIndices.clear();
		weightedBoneIndices.reserve(predefinedBoneIndices.size() + weightFactor); // Adjust reserve size if needed
		for (const auto& index : predefinedBoneIndices) {
			weightedBoneIndices.push_back(index); // Normal addition for all indices
			if (index == boneIndex) {
				for (int i = 1; i < weightFactor; ++i) {
					weightedBoneIndices.push_back(index); // Increase weight for priority index
				}
			}
		}
	}
	else {
		weightedBoneIndices = predefinedBoneIndices; // Reset to default
	}
}



string GetItemType(string Name) {




	if (Settings::Akm) if (Name == "BP_Rifle_AKM_Wrapper_C") return "Akm";
	if (Settings::M16A4) if (Name == "BP_Rifle_M16A4_Wrapper_C") return "M16A4";
	if (Settings::SCARL)if (Name == "BP_Rifle_SCAR_Wrapper_C") return "SCARL";
	if (Settings::M416)if (Name == "BP_Rifle_M416_Wrapper_C") return "M416";
	if (Settings::GROZA)if (Name == "BP_Rifle_Groza_Wrapper_C") return "GROZA";
	if (Settings::AUG)if (Name == "BP_Rifle_AUG_Wrapper_C") return "AUG";
	if (Settings::QBZ)if (Name == "BP_Rifle_QBZ_Wrapper_C") return "QBZ";
	if (Settings::M762)if (Name == "BP_Rifle_M762_Wrapper_C") return "M762";
	if (Settings::MK47)if (Name == "BP_Rifle_Mk47_Wrapper_C") return "MK47";
	if (Settings::G36C)if (Name == "BP_Rifle_G36_Wrapper_C") return "G36C";
	if (Settings::HONEY)if (Name == "BP_Rifle_HoneyBadger_Wrapper_C") return "HONEY";
	if (Settings::FAMAS)if (Name == "BP_Rifle_FAMAS_Wrapper_C") return "FAMAS";
	if (Settings::KAR98)if (Name == "BP_Sniper_Kar98k_Wrapper_C") return "KAR98";
	if (Settings::M24)if (Name == "BP_Sniper_M24_Wrapper_C") return "M24";
	if (Settings::AWM)if (Name == "BP_Sniper_AWM_Wrapper_C") return "AWM";
	if (Settings::WIN94)if (Name == "BP_Sniper_Win94_Wrapper_C") return "WIN94";
	if (Settings::MOSIN)if (Name == "BP_Sniper_MOSIN_Wrapper_C") return "MOSIN";
	if (Settings::AMR)if (Name == "BP_Sniper_AMR_Wrapper_C") return "AMR";
	if (Settings::SKS)if (Name == "BP_Sniper_SKS_Wrapper_C") return "SKS";
	if (Settings::VSS)if (Name == "BP_Sniper_VSS_Wrapper_C") return "VSS";
	if (Settings::MINI14)if (Name == "BP_Sniper_Mini14_Wrapper_C") return "MINI14";
	if (Settings::MK14)if (Name == "BP_Sniper_MK14_Wrapper_C") return "MK14";
	if (Settings::SLR)if (Name == "BP_Sniper_SLR_Wrapper_C") return "SLR";
	if (Settings::QBU)if (Name == "BP_Sniper_QBU_Wrapper_C") return "QBU";
	if (Settings::MK12)if (Name == "BP_Other_MK12_Wrapper_C") return "MK12";
	if (Settings::UZI)if (Name == "BP_MachineGun_Uzi_Wrapper_C") return "UZI";
	if (Settings::UMP45)if (Name == "BP_MachineGun_UMP9_Wrapper_C" || Name == "BP_MachineGun_UMP45_Wrapper_C") return "UMP45";
	if (Settings::VECTOR)if (Name == "BP_MachineGun_Vector_Wrapper_C") return "VECTOR";
	if (Settings::THOMPSON)if (Name == "BP_MachineGun_THOMPSON_Wrapper_C") return "THOMPSON";
	if (Settings::BIZON)if (Name == "BP_MachineGun_Bizon_Wrapper_C") return "BIZON";
	if (Settings::MP5K)if (Name == "BP_MachineGun_MP5K_Wrapper_C") return "MP5K";
	if (Settings::P90)if (Name == "BP_MachineGun_P90_Wrapper_C") return "P90";
	if (Settings::S686)if (Name == "BP_ShotGun_S686_Wrapper_C") return "S686";
	if (Settings::S1897)if (Name == "BP_ShotGun_S1897_Wrapper_C") return "S1897";
	if (Settings::S12K)if (Name == "BP_ShotGun_S12K_Wrapper_C") return "S12K";
	if (Settings::DBS)if (Name == "BP_ShotGun_DBS_Wrapper_C") return "DBS";
	if (Settings::M1014)if (Name == "BP_ShotGun_M1014_Wrapper_C") return "M1014";
	if (Settings::NS2000)if (Name == "BP_ShotGun_NS2000_Wrapper_C") return "NS2000";
	if (Settings::M249)if (Name == "BP_Other_M249_Wrapper_C") return "M249";
	if (Settings::DP28)if (Name == "BP_Other_DP28_Wrapper_C") return "DP28";
	if (Settings::MG3)if (Name == "BP_Other_MG3_Wrapper_C") return "MG3";

	if (Settings::FLARE)if (Name == "BP_Pistol_Flaregun_Wrapper_C") return "FLARE";

	if (Settings::FRAG)if (Name == "BP_Grenade_Shoulei_Weapon_Wrapper_C") return "FRAG";
	if (Settings::SMOKE)if (Name == "BP_Grenade_Smoke_Weapon_Wrapper_C") return "SMOKE";
	if (Settings::MOLOTOF)if (Name == "BP_Grenade_Burn_Weapon_Wrapper_C") return "MOLOTOF";

	if (Settings::MedKit)if (Name == "FirstAidbox_Pickup_C") return "MedKit";
	if (Settings::FirstAidKit)if (Name == "Firstaid_Pickup_C") return "FirstAidKit";
	if (Settings::Painkiller)if (Name == "Pills_Pickup_C") return "Painkiller";
	if (Settings::EnergyDrink)if (Name == "Drink_Pickup_C") return "EnergyDrink";
	if (Settings::Adrenalin)if (Name == "Injection_Pickup_C") return "Adrenalin";


	if (Settings::Bag1)if (Name.find("PickUp_BP_Bag_Lv1") != string::npos) return "Bag1";
	if (Settings::Bag2)if (Name.find("PickUp_BP_Bag_Lv2") != string::npos) return "Bag2";
	if (Settings::Bag3)if (Name.find("PickUp_BP_Bag_Lv3") != string::npos) return "Bag3";
	if (Settings::Helmet1)if (Name.find("PickUp_BP_Helmet_Lv1") != string::npos) return "Helmet1";
	if (Settings::Helmet2)if (Name.find("PickUp_BP_Helmet_Lv2") != string::npos) return "Helmet2";
	if (Settings::Helmet3)if (Name.find("PickUp_BP_Helmet_Lv3") != string::npos) return "Helmet3";
	if (Settings::Armor1)if (Name.find("PickUp_BP_Armor_Lv1") != string::npos) return "Armor1";
	if (Settings::Armor2)if (Name.find("PickUp_BP_Armor_Lv2") != string::npos) return "Armor2";
	if (Settings::Armor3)if (Name.find("PickUp_BP_Armor_Lv3") != string::npos) return "Armor3";


	if (Settings::a762mm)if (Name == "BP_Ammo_762mm_Pickup_C") return "7.62mm";
	if (Settings::a556mm)if (Name == "BP_Ammo_556mm_Pickup_C") return "5.56mm";
	if (Settings::a9mm)if (Name == "BP_Ammo_9mm_Pickup_C") return "9mm";
	if (Settings::a45ACP)if (Name == "BP_Ammo_45ACP_Pickup_C") return "45ACP";
	if (Settings::a12Gauege)if (Name == "BP_Ammo_12Gauege_Pickup_C") return "12Gauege";
	if (Settings::AwmAmmo)if (Name == "BP_Ammo_300Magnum_Pickup_C") return "AwmAmmo";
	if (Settings::AmrAmmo)if (Name == "BP_Ammo_50BMG_Pickup_C") return "AmrAmmo";
	if (Settings::Scope_x2)if (Name == "BP_MZJ_2X_Pickup_C") return "Scope_x2";
	if (Settings::Scope_x3)if (Name == "BP_MZJ_3X_Pickup_C") return "Scope_x3";
	if (Settings::Scope_x4)if (Name == "BP_MZJ_4X_Pickup_C") return "Scope_x4";
	if (Settings::Scope_x6)if (Name == "BP_MZJ_6X_Pickup_C") return "Scope_x6";
	if (Settings::Scope_x8)if (Name == "BP_MZJ_8X_Pickup_C") return "Scope_x8";


	if (Settings::ShopToken)if (Name.find("GoldenTokenWrapper_C") != string::npos) return "Shop Token";
	if (Settings::ExtendedMac)if (Name.find("BP_DJ_Large_E_Pickup_C") != string::npos) return "Extended Mac";
	if (Settings::Supressor) if (Name.find("BP_QK_Large_Suppressor_Pickup_C") != std::string::npos) return "Suppressor (AR)";
	if (Settings::Supressor) if (Name.find("BP_QK_Sniper_Suppressor_Pickup_C") != std::string::npos) return "Suppressor (Sniper)";
	if (Settings::Supressor) if (Name.find("BP_QK_Mid_Suppressor_Pickup_C") != std::string::npos) return "Suppressor (SMG)";

	if(Settings::AirDrop) if (Name.find("AirDropListWrapperActor") != string::npos) return "Air Drop";
	if(Settings::AirDrop) if (Name.find("BP_AirDropBox_C") != string::npos) return "Air Drop";
	if(Settings::AirDrop) if (Name.find("BP_AirDropBox_New_C") != string::npos) return "Air Drop";

	if (Name.find("PickUp_BP_FlyingArmor_C") != string::npos) return "JetPack";
	if (Name.find("BP_MagneticGun_Wrapper_C") != string::npos) return "MagnetGun";
	if(Settings::Redzone)if (Name.find("BP_radiation") != string::npos) return "SafeZone";

	//return Name;
	return "Unknown";

}


bool IsAirDrop(std::string classname)
{
	if (classname.find("BP_AirDropBox_C") != string::npos || classname.find("AirDropListWrapperActor") != string::npos)

		return true;
	else
		return false;
	return false;
}

bool IsBox(string classname)
{
	if (classname.find("PlayerDeadInventoryBox") != string::npos || classname.find("PickUpListWrapperActor") != string::npos)
		return true;
	else
		return false;
	return false;
}
string GetVehicleType(string Name)
{
	if (Name.find("BRDM") != string::npos) return "BRDM";
	if (Name.find("Scooter") != string::npos) return "Scooter";
	if (Name.find("Motorcycle") != string::npos) return "Motorcycle";
	if (Name.find("Snowmobile") != string::npos) return "Snowmobile";
	if (Name.find("Tuk") != string::npos) return "Tuk";
	if (Name.find("Buggy") != string::npos) return "Buggy";
	if (Name.find("open") != string::npos) return "Sports";
	if (Name.find("close") != string::npos) return "Sportsa";
	if (Name.find("Dacia") != string::npos) return "Dacia";
	if (Name.find("Monster Truck") != string::npos) return "Monster Truck";
	if (Name.find("Rony") != string::npos) return "Rony";
	if (Name.find("UAZ") != string::npos) return "UAZ";
	if (Name.find("MiniBus") != string::npos) return "Minibus";
	if (Name.find("PG117") != string::npos) return "PG117";
	if (Name.find("AquaRail") != string::npos) return "Aquarail";
	if (Name.find("CoupeRB") != string::npos) return "Coupe";
	if (Name.find("ModelY") != string::npos) return "Tesla";
	if (Name.find("G-38Anti-GravityMotorcycle") != string::npos) return "Gravity";
	if (Name.find("Glider") != string::npos) return "Glider";
	if (Name.find("VH_UTV_C") != string::npos) return "UTV";
	if (Name.find("BP_VH_Bigfoot_C") != string::npos) return "MONSTER";
	if (Name.find("ATV1_C") != string::npos) return "Quad";
	if (Name.find("ATV2_C") != string::npos) return "Quad";
	if (Name.find("ATV3_C") != string::npos) return "Quad";
	if (Name.find("ATV4_C") != string::npos) return "Quad";
	if (Name.find("ATV5_C") != string::npos) return "Quad";
	if (Name.find("ATV6_C") != string::npos) return "Quad";
	//new
	if (Name.find("Motorglider") != string::npos) return "Glider";
	if (Name.find("Snowbike") != string::npos) return "SnowBike";
	if (Name.find("PickUp_07_C") != string::npos) return "Pickup Vehcile";
	//if (Name.find("Bike") != string::npos) return "cycle";
	if (Name.find("wing") != string::npos) return "Helicopter";
	if (Name.find("MechaVehicle") != string::npos) return "Danav";
	if (Name.find("CombinedHovering") != string::npos) return "Danav Copter";
	if (Name.find("CombinedMechailPlaceColor") != string::npos) return "Big Danav";
	if (Name.find("CombMechaMissile") != string::npos) return "Danav";

	return "Unknown";
}

std::string getWeapon(int id) {
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


// Function to retrieve weapon name based on player's current weapon
std::string RetrieveWeaponName(DWORD AActorAddress) {
	DWORD CharacterWeaponManagerComponent = Utility::ReadMemoryEx<DWORD>(AActorAddress + Offset::Hacks::WeaponManagerComponent);
	if (CharacterWeaponManagerComponent) {
		DWORD CurrentWeaponReplicated = Utility::ReadMemoryEx<DWORD>(CharacterWeaponManagerComponent + Offset::Hacks::CurrentWeaponReplicated);
		if (CurrentWeaponReplicated) {
			INT CurBulletNumInClip = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::CurBulletNumInClip); //int CurBulletNumInClip;//[Offset: 0xbd0, Size: 4]
			INT CurMaxBulletNumInOneClip = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::CurMaxBulletNumInOneClip); //	int CurMaxBulletNumInOneClip;//[Offset: 0xbe4, Size: 4]
			DWORD ShootWeaponEntity = Utility::ReadMemoryEx<DWORD>(CurrentWeaponReplicated + Offset::Hacks::ShootWeaponEntity);
			if (ShootWeaponEntity) {
				float id = Utility::ReadMemoryEx<DWORD>(ShootWeaponEntity + Offset::Hacks::UploadInterval); //float UploadInterval
				if (id != NULL) {

					string Weaponinfo = getWeapon(id);
					if(CurBulletNumInClip >= 0 && CurBulletNumInClip <= 150){
					
						Weaponinfo += " [ ";
						Weaponinfo += to_string(CurBulletNumInClip);
						Weaponinfo += " / ";
						Weaponinfo += to_string(CurMaxBulletNumInOneClip);
						Weaponinfo += " ] ";

					}
				
					return Weaponinfo;

				}
			}
			// it becomes true when enemy is holding weapon 
		}
	}
	return "Fist";
}


struct ActorsEncryption {
	uint32_t Enc_1, Enc_2;
	uint32_t Enc_3, Enc_4;
};
uint32_t Data::ActorsPointerAddress;
std::string result;


std::string GetEntityType3(UINT gNames, UINT id)
{

	auto gname = ReadMemoryEx<UINT>(gNames);
	if (id > 0 && id < 2000000)
	{
		auto page = id / 16384;
		DWORD index = id % 16384;
		auto secPartAddv = ReadMemoryEx<UINT>(gname + page * 4);
		if (secPartAddv > 0)
		{
			auto nameAddv = ReadMemoryEx<UINT>(secPartAddv + index * 4);

			if (nameAddv > 0)
			{
				ObjectName pBuffer = ReadMemoryEx<ObjectName>(nameAddv + 0x8);
				return pBuffer.Data;
			}
		}
	}
	return std::string("");
}

string GetEntityType(LONG GNames, LONG Id)
{
	DWORD GName = Utility::ReadMemoryEx<DWORD>(GNames);
	DWORD NamePtr = Utility::ReadMemoryEx<DWORD>(GName + int(Id / 16384) * 0x4);
	DWORD Name = Utility::ReadMemoryEx<DWORD>(NamePtr + int(Id % 16384) * 0x4);
	ObjectName pBuffer = Utility::ReadMemoryEx<ObjectName>(Name + 0x8);

	return string(pBuffer.Data);
}
struct Encryption_Chunk {
	uint32_t val_1, val_2;
	uint32_t val_3, val_4;
};


std::string GetBoxItems(int code)
{
	if (code == 101008)
	{
		Settings::colorcode = Settings::M762Color;
		return "M762";

	}
	else if (code == 306001)
	{
		Settings::colorcode = Settings::AwmAmmoColor;
		return "AWM Ammo";
	}

	else if (code == 101003)
	{
		Settings::colorcode = Settings::SCARLColor;
		return "SCAR-L";
	}
	else if (code == 302001)
	{

		Settings::colorcode = Settings::a762mmColor;
		return "7.62";
	}
	else if (code == 303001)
	{

		Settings::colorcode = Settings::a556mmColor;
		return "5.56";
	}
	else if (code == 602004)
	{
		Settings::colorcode = Settings::FRAGColor;

		return "Grenade";
	}
	else if (code == 601006)
	{
		Settings::colorcode = Settings::MedKitColor;

		return "Medkit";
	}
	else if (code == 101004)
	{
		Settings::colorcode = Settings::M416Color;
		return "M416";
	}
	else if (code == 102001)
	{
		Settings::colorcode = Settings::UZIColor;
		return "UZI";
	}
	else if (code == 101010)
	{
		Settings::colorcode = Settings::G36CColor;
		return "G36";
	}

	else if (code == 101006)
	{
		Settings::colorcode = Settings::AUGColor;
		return "AUG";
	}


	else if (code == 101001)
	{
		Settings::colorcode = Settings::AkmColor;
		return "AKM";
	}

	else if (code == 101005)
	{
		Settings::colorcode = Settings::GROZAColor;
		return "Groza";
	}

	else if (code == 103003)
	{
		Settings::colorcode = Settings::AWMColor;
		return "AWM";
	}

	else if (code == 103002)
	{
		Settings::colorcode = Settings::M24Color;
		return "M24";
	}

	else if (code == 103001)
	{
		Settings::colorcode = Settings::KAR98Color;
		return "Kar98k";
	}

	else if (code == 103011)
	{
		Settings::colorcode = Settings::MOSINColor;
		return "Mosin";
	}

	else if (code == 502002)
	{
		Settings::colorcode = Settings::Helmet2Color;
		return "Helmet Lv.2";
	}

	else if (code == 502003)
	{
		Settings::colorcode = Settings::Helmet3Color;
		return "Helmet Lv.3";
	}

	else if (code == 503002)
	{
		Settings::colorcode = Settings::Armor2Color;
		return "Armour Lv.2";
	}

	else if (code == 503003)
	{
		Settings::colorcode = Settings::Armor3Color;
		return "Armour Lv.3";
	}

	else if (code == 501006)
	{
		Settings::colorcode = Settings::Bag3Color;
		return "Bag Lv.3";
	}

	else if (code == 501005)
	{
		Settings::colorcode = Settings::Bag2Color;
		return "Bag Lv.2";
	}

	else if (code == 203014)
	{
		Settings::colorcode = Settings::Scope_x3Color;
		return "3X";

	}
	else if (code == 103007)
	{
		Settings::colorcode = Settings::AWMColor;
		return "MK14";

	}
	else if (code == 203004)
	{
		Settings::colorcode = Settings::Scope_x4Color;
		return "4x";
	}

	else if (code == 203015)
	{
		Settings::colorcode = Settings::Scope_x6Color;
		return "6x";
	}

	else if (code == 203005)
	{
		Settings::colorcode = Settings::Scope_x8Color;
		return "8x";
	}

	else if (code == 106007)
	{
		Settings::colorcode = Settings::FLAREColor;
		return "Flaregun";
	}

	else if (code == 105001)
	{
		Settings::colorcode = Settings::M249Color;
		return "M249";
	}

	else if (code == 105002)
	{
		Settings::colorcode = Settings::DP28Color;
		return "DP28";
	}

	else if (code == 105010)
	{
		Settings::colorcode = Settings::MG3Color;
		return "MG3";
	}

	return "tatti";
}

bool Data::InLobby = true;

string GetGrenadeType(string classname)
{
	if(Settings::SMOKE)if (classname.find("BP_Grenade_Smoke_C") != std::string::npos)
		return "Smoke";
	if(Settings::MOLOTOF)if (classname.find("BP_Grenade_Burn_C") != string::npos)
		return  "Burn";
	if (classname.find("BP_Grenade_Stun_C") != std::string::npos)
		return "Flash Granade";
	if (Settings::FRAG) if (classname.find("BP_Grenade_Shoulei_C") != string::npos)
		return "Frag";
	if(Settings::Redzone) if (classname.find("AirAttackBomb_Livik_C") != std::string::npos || classname.find("AirAttackBomb_C") != std::string::npos) return "Redzone";

	return "Unknown";
}



string GetPlayerName(DWORD BaseAddress)
{
	char* String = new char[34];
	for (int i = 0; i < 34; i++)
	{
		String[i] = ReadMemoryEx<char>(BaseAddress + i * 2);
	}

	return String;
}

// Function to remove untranslatable characters from a string
std::string FilterInvalidCharacters(const std::string& str)
{
	std::string filteredString;
	for (char c : str)
	{
		// Filter out characters outside the printable ASCII range and '?'
		if (c >= 32 && c <= 126 && c != '?')
		{
			filteredString += c;
		}
	}
	return filteredString;
}

std::string ConvertFromUtf16ToUtf8(const std::wstring& wstr)
{
	std::string convertedString;
	int requiredSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, 0, 0, 0, 0);
	if (requiredSize > 0)
	{
		std::vector<char> buffer(requiredSize);
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buffer[0], requiredSize, 0, 0);
		convertedString.assign(buffer.begin(), buffer.end() - 1);
	}
	return convertedString;
}

struct ObjectNameU
{
	wchar_t data[64];
};

std::string GetPlayerNameUTF(ULONG Address)
{
	ObjectNameU pBuffer = ReadMemoryEx<ObjectNameU>(ReadMemoryEx<UINT>(Address));
	const auto player_name = std::wstring(pBuffer.data);
	if (player_name.empty())
	{
		return "Player";
	}

//	return ConvertFromUtf16ToUtf8(player_name);
	std::string utf8Name = ConvertFromUtf16ToUtf8(player_name);
	return FilterInvalidCharacters(utf8Name);
}

namespace Decryption
{
	// pubg 2.4 32bit
	//32bit
	//00 20 90 E5 E0 10 94 E5 0C 20 92 E5

	struct ActorsEncryption {
		uint32_t Enc_1; //0x0340 
		uint32_t Enc_2; //0x0344 
		uint32_t Enc_3; //0x0348 
		uint32_t Enc_4; //0x034C 
	};
	struct Encryption_Chunk {
		uint32_t val_1, val_2, val_3, val_4;
	};
	uint32_t DecryptActorsArray(uint32_t uLevel, int Actors_Offset, int EncryptedActors_Offset)
	{
		if (uLevel < 0x10000000)
			return 0;

		if (ReadMemoryEx<uint32_t>(uLevel + Actors_Offset) > 0)
			return uLevel + Actors_Offset;
		else
		{
			std::cout << "Try Find Next Decryption Address 1" << std::endl;

		}

		if (ReadMemoryEx<uint32_t>(uLevel + EncryptedActors_Offset) > 0)
			return uLevel + EncryptedActors_Offset;
		else
		{
			std::cout << "Try Find Next Decryption Address 2" << std::endl;

		}
		auto Encryption = ReadMemoryEx<ActorsEncryption>(uLevel + EncryptedActors_Offset + 0x0C);

		if (Encryption.Enc_1 > 0)
		{
			auto Enc = ReadMemoryEx<Encryption_Chunk>(Encryption.Enc_1 + 0x80);

			return ((ReadMemoryEx<unsigned __int8>(Encryption.Enc_1 + Enc.val_1))
				| ((ReadMemoryEx<unsigned __int8>(Encryption.Enc_1 + Enc.val_2)) << 8)
				| ((ReadMemoryEx<unsigned __int8>(Encryption.Enc_1 + Enc.val_3)) << 16)
				| ((ReadMemoryEx<unsigned __int8>(Encryption.Enc_1 + Enc.val_4)) << 24));
		} //ok
		else if (Encryption.Enc_2 > 0)
		{
			auto Encrypted_Actors = ReadMemoryEx<uint32_t>(Encryption.Enc_2);
			if (Encrypted_Actors > 0)
			{
				return (Encrypted_Actors - 0x4000000) & 0xFF000000
					| (Encrypted_Actors + 0xFC0000) & 0xFF0000
					| ((unsigned __int16)Encrypted_Actors - 0x400) & 0xFF00
					| (unsigned __int8)(Encrypted_Actors - 4);
			}
		} //ok
		else if (Encryption.Enc_3 > 0)
		{
			auto Encrypted_Actors = ReadMemoryEx<uint32_t>(Encryption.Enc_3);
			if (Encrypted_Actors > 0)
				return (Encrypted_Actors >> 0x18) | (Encrypted_Actors << (32 - 0x18));
		}
		else if (Encryption.Enc_4 > 0)
		{
			auto Encrypted_Actors = ReadMemoryEx<uint32_t>(Encryption.Enc_4);
			if (Encrypted_Actors > 0)
				return Encrypted_Actors ^ 0xCDCD00;
		}
		else
		{
			std::cout << "Cant Find Decryption Address" << std::endl;
		}
		return 0;
	}
}

BYTE ue4e[] =
{
	0x7F, 0x45, 0x4C, 0x46, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x28, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0xF0, 0xD8, 0x01, 0x34, 0x00, 0x00, 0x00, 0x38, 0x99, 0x64, 0x08, 0x00, 0x02, 0x00, 0x05, 0x34, 0x00,
	0x20, 0x00, 0x0D, 0x00, 0x28, 0x00, 0x19, 0x00
};

DWORD Data::GetUE4BaseAddress() {

	std::vector<DWORD_PTR> FBase;
	MemSearch(ue4e, sizeof(ue4e), (DWORD)0x30000000, (DWORD)0x60000000, 0, 0, FBase);
	//MemSearch(ue4e, sizeof(ue4e), (DWORD)0x20000000, (DWORD)0xA0000000, 0, 0, FBase);

	if (FBase.size() > 0)
	{
		return FBase[0];
	}


}


#define shell_writeoffset 0x3E267A8
//libfizz.so

bool InjectSharedLibrary(uint32_t libUE4) {
	BYTE __stb[] = {
		0xF0, 0x4F, 0x2D, 0xE9, // push {r4, r5, r6, r7, r8, sb, sl, fp, lr}
		0x10, 0x00, 0x9F, 0xE5, // ldr r0, [pc, #0x10]
		0x01, 0x10, 0xA0, 0xE3, // mov r1, #1
		0x00, 0x00, 0x8F, 0xE0, // add r0, pc, r0
		0x5E, 0xFD, 0xD5, 0xEB, // bl #0xFF57F580
		0x00, 0x00, 0xA0, 0xE3, // mov r0, #0
		0xF0, 0x8F, 0xBD, 0xE8, // pop {r4, r5, r6, r7, r8, sb, sl, fp, pc}
		0x0C, 0x00, 0x00, 0x00, // andeq r0, r0, ip
		0x6C, 0x69, 0x62, 0x66,
		0x69, 0x7A, 0x7A, 0x2E,
		0x73, 0x6F, 0x00, 0x00
	};

	//lib name libfizz.so
	uint32_t hook_buffer = libUE4 + shell_writeoffset;

	// Write the byte array to the specified memory offset

	Utility::WriteProtectedMemoryEx<BYTE[sizeof(__stb)]>(hook_buffer, __stb);

	return true;
}

//dlopen call
BYTE patch[] = {
	0xF0, 0x4F, 0x2D, 0xE9, 0x1C, 0xB0, 0x8D, 0xE2,
	0x14, 0xD0, 0x4D, 0xE2, 0x00, 0xA0, 0xA0, 0xE1,
	0x44, 0x05, 0x9F, 0xE5, 0x01, 0x80, 0xA0, 0xE1,
	0x00, 0x60, 0xA0, 0xE3, 0x00, 0x00, 0x9F, 0xE7,
	0x00, 0x00, 0xD0, 0xE5, 0x00, 0x00, 0x50, 0xE3,
	0x37, 0x01, 0x00, 0x0A
};

VOID Data::InjectLibrary() {

	DWORD libUE4Base = GetUE4BaseAddress();
	if (InjectSharedLibrary(libUE4Base)) {
		Utility::WriteProtectedMemoryEx<BYTE[sizeof(patch)]>(libUE4Base + shell_writeoffset, patch);
		//writeoffsetbyte(libUE4Base + shell_writeoffset, patch, sizeof(patch));
	}
}


template <typename T>
T myMax(T a, T b) {
	return (a > b) ? a : b;
}

template <typename T>
T myMin(T a, T b) {
	return (a < b) ? a : b;
}

CameraCacheEntry Data::CameraCache;
DWORD Data::NetDriver;
DWORD Data::LocalPlayer;
DWORD Data::PlayerCameraManager;
DWORD Data::PlayerController;

vector<AActor> Data::AActorList = {};
vector<Item> Data::ItemList = {};
vector<Vehicle> Data::VehicleList = {};

string Data::Map;
string Data::PlayerPlayerName = "";
string Data::PlayerNation = "";
string Data::PlayerUID = "";

int Data::PlayerTotalKills;
int Data::PlayerTeamID;
int Data::PlayerLevel;
FLOAT Data::PlayerHealth;
FLOAT Data::PlayerTravelDistance;

VOID Data::QueryThread()
{
	DWORD GWorld;
	DWORD GName;
	DWORD libUE4Base = GetUE4BaseAddress();
	//Data::libUE4Base = libUE4Base;

	//DWORD libUE4Base = Utility::ReadMemoryEx<DWORD>(0XE0C36E0);

	if (libUE4Base == 0) {
		MessageBox(NULL, "Can't Find ue4base", "AnimeTone VIP", MB_OKCANCEL);

		ExitProcess(0);
	}
	
	  if (Data::ViewMatrixBase == 0) {
		Data::ViewMatrixBase = libUE4Base + 0x89B1AB0; //3.3
	    GWorld = Utility::ReadMemoryEx<DWORD>(libUE4Base + 0x89CA794) + 0x3C; //60 //3.3
	    GName = Utility::ReadMemoryEx<DWORD>(libUE4Base + 0x863F524) + 0x88; //136 //3.3
	  }
	  else {
	  
	  	GWorld = Utility::ReadMemoryEx<DWORD>(Data::ViewMatrixBase + 112780) + 60; //need to update for 3.2
	  	GName = Utility::ReadMemoryEx<DWORD>(Data::ViewMatrixBase - 5452104) + 136; //need toupdate for 3.2
	  
	  }

	if (Data::ViewMatrixBase == 0) {
		//m_drv->Unload();
	
		MessageBox(NULL, "Can't Find ViewMatrix V2", "AnimeTone VIP", MB_OKCANCEL);
	
		ExitProcess(0);
	}
    
	

	DWORD PersistentLevel = 0;
	DWORD ServerConnection = 0;
	DWORD EntityList = 0;
	INT EntityCount = 0;
	DWORD LocalController;
	DWORD EntityStruct = 0;
	string EntityType = "";
	DWORD EntityAddress;
	DWORD RootComponent = 0;
	INT MyTeamId = 0;
	DWORD MeshAddv;
	DWORD BodyAddv;
	DWORD BoneAddv;
	string wep = "";

	string ItemType = "";
	string VehicleType = "";
	string airdroptype = "";
	string deadboxtype = "";
	DWORD gnameget;
	vector<AActor> AActorListtt = {};
	vector<Vehicle> VehicleList = {};
	vector<Item> ItemList = {};

	DWORD PlayerStateBASE;
	DWORD GameStateBASE;
	uint32_t ActorsPointerAddress;
	DWORD  count;

	DWORD veh;
	float HP;
	float Fuel;
	float HPMax;
	float FuelMax;

	long itemBase;
	long itemAddv;
	while (true)
	{
		UWorld = ReadMemoryEx<DWORD>(GWorld);
		PersistentLevel = ReadMemoryEx<DWORD>(UWorld + Offset::Data::PersistentLevel);
		NetDriver = ReadMemoryEx<DWORD>(UWorld + Offset::Data::NetDriver);

		if (Data::NetDriver > 0)
		{
			Data::InLobby = false;
		}
		else
		{
			Data::InLobby = true;
		}

		if (UWorld != 0 ) {

			gnameget = ReadMemoryEx<DWORD>(GName);
			ServerConnection = ReadMemoryEx<DWORD>(NetDriver + Offset::Data::ServerConnection);
			PlayerController = ReadMemoryEx<DWORD>(ServerConnection + Offset::Data::PlayerController);
			LocalPlayer = ReadMemoryEx<DWORD>(PlayerController + Offset::Data::AcknowledgedPawn);
			LocalController = ReadMemoryEx<DWORD>(LocalPlayer + Offset::Camera::LocalController);
			PlayerCameraManager = ReadMemoryEx<DWORD>(LocalController + Offset::Camera::PlayerCameraManager);
			CameraCache = ReadMemoryEx<CameraCacheEntry>(PlayerCameraManager + Offset::Camera::CameraCache);

			if (PersistentLevel != 0)
			{

				ActorsPointerAddress = Decryption::DecryptActorsArray(PersistentLevel, 0x70, 0x334);//--Actors //;//Player* Player; //const DWORD EntityList = 0x70; // 0x334
				EntityList = ReadMemoryEx<uint32_t>(ActorsPointerAddress);
				EntityCount = ReadMemoryEx<int>(ActorsPointerAddress + 0x4); //EntityList + 0x4;

				GameStateBASE = ReadMemoryEx<DWORD>(UWorld + Offset::GameStateBase);

				//	if (Settings::GameInfo)
				//	{
				Settings::AlivePlayers = ReadMemoryEx<INT>(GameStateBASE + Offset::AlivePlayerNum);
				Settings::TimeRemind = ReadMemoryEx<INT>(GameStateBASE + Offset::ElapsedTime);
				Settings::AliveTeams = ReadMemoryEx<INT>(GameStateBASE + Offset::AliveTeamNum);
				Settings::RealPls = ReadMemoryEx<INT>(GameStateBASE + Offset::PlayerNum);
				Settings::ZoneID = ReadMemoryEx<INT>(GameStateBASE + Offset::CurCircleWave) + 2;
				Settings::MyTeamID = ReadMemoryEx<INT>(LocalPlayer + Offset::Player::TeamId);
				Settings::GameID = ReadMemoryEx<INT>(GameStateBASE + Offset::GameModeID) * -1;
				Settings::MyName = GetPlayerNameUTF(LocalPlayer + Offset::Player::Name);
				Data::PlayerTravelDistance = ReadMemoryEx<FLOAT>(GameStateBASE + 0xc80);//	float BroadcastClientDistance;//[Offset: 0xc60, Size: 4]

				//	}

				for (int i = 0; i < EntityCount; ++i)
				{
					EntityAddress = ReadMemoryEx<DWORD>(EntityList + i * 4);
					if (!EntityAddress)
						continue;

					if (EntityAddress == (DWORD)nullptr || EntityAddress == -1 || EntityAddress == NULL)
						continue;

					EntityStruct = ReadMemoryEx<DWORD>(EntityAddress + 0x10);
					{

						EntityType = GetEntityType(GName, EntityStruct);
						if (EntityType == "None" || EntityType == " " || EntityType == "") continue;

						{
							RootComponent = ReadMemoryEx<DWORD>(EntityAddress + Offset::Data::RootComponent);
							if (IsPlayer(EntityType))
							{
								AActor AActor;


								AActor.Position = ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);
								AActor.RelativeLocation = ReadMemoryEx<VECTOR3>(RootComponent + Offset::RelativeLocation);
								AActor.RelativeRotation = ReadMemoryEx<FRotator>(RootComponent + Offset::RelativeRotation);
								//AActor.IsVisible = ReadMemoryEx<bool>(RootComponent + Offset::IsVisible);

								AActor.IsDead = ReadMemoryEx<bool>(EntityAddress + Offset::Player::IsDead);
								if (AActor.IsDead)  continue;
								AActor.TeamId = ReadMemoryEx<int>(EntityAddress + Offset::Player::TeamId);
								if (MyTeamId == AActor.TeamId)  continue;

								AActor.Address = EntityAddress;

								if (AActor.Address == LocalPlayer)
								{
									MyTeamId = AActor.TeamId;
									continue;
								}

								if (Settings::PlayerWeapon)
								{
									AActor.weapon = RetrieveWeaponName(AActor.Address);

								}

								AActor.IsBot = ReadMemoryEx<bool>(EntityAddress + Offset::Player::IsBot);

								if (!AActor.IsBot)
								{
									//	AActor.Nation = GetPlayerName(ReadMemoryEx<DWORD>(EntityAddress + Offset::Player::Nation));
									AActor.Name = GetPlayerNameUTF(EntityAddress + Offset::Player::Name);
									AActor.status = ReadMemoryEx<int>(EntityAddress + Offset::Player::CurrentStates);
									AActor.IsVisible = ReadMemoryEx<int>(EntityAddress + Offset::Player::Kills);

								}
								else
								{
									AActor.Name = "BOT";
									AActor.Nation = "Country";
								}

								if (Settings::visibilitycheck || Settings::visbulletcheck) {

									AActor.IsVisible = ReadMemoryEx<bool>(EntityAddress + 0x1D2); //offset from lib	
								}
								
								AActor.CurrentVehcile = ReadMemoryEx<uint32_t>(EntityAddress + Offset::CurrentVehicle);
								AActor.Health = ReadMemoryEx<float>(EntityAddress + Offset::Player::Health);
								AActor.HealthMax = ReadMemoryEx<float>(EntityAddress + Offset::Player::HealthMax);
								AActor.Velocity = ReadMemoryEx<VECTOR3>(ReadMemoryEx<DWORD>(AActor.Address + Offset::CharacterMovement) + Offset::LastUpdateVelocity);
								AActor.KnockedHealth = ReadMemoryEx<FLOAT>(EntityAddress + Offset::Player::KnockHealth);
							

								MeshAddv = ReadMemoryEx<DWORD>(AActor.Address + Offset::Bone::Mesh);
								BodyAddv = MeshAddv + Offset::Bone::BodyAddv;
								BoneAddv = ReadMemoryEx<DWORD>(MeshAddv + Offset::Bone::MinLOD) + 48;
								AActor.HeadPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 5 * 48); //previous val 5 
								AActor.ChestPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 4 * 48);
								AActor.PelvisPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 1 * 48);

								if (Settings::Legitrack) {

									SetBonePriority(Settings::currentBoneIndex, Settings::isPrioritySet, Settings::weight);
									AActor.RandomPos = GetBoneWorldPosition(BodyAddv, BoneAddv + GetRandomBonePosWithPriority() * 48);

								}


								if (Settings::PlayerSkeleton || Settings::MagicBullet)
								{

									AActor.lSholderPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 11 * 48);
									AActor.rSholderPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 32 * 48);
									AActor.lElbowPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 12 * 48);
									AActor.rElbowPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 33 * 48);
									AActor.lWristPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 63 * 48);
									AActor.rWristPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 62 * 48);
									AActor.lThighPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 52 * 48);
									AActor.rThighPos = GetBoneWorldPosition(BodyAddv, BoneAddv + 56 * 48);
									AActor.lKneePos = GetBoneWorldPosition(BodyAddv, BoneAddv + 53 * 48);
									AActor.rKneePos = GetBoneWorldPosition(BodyAddv, BoneAddv + 57 * 48);
									AActor.lAnklePos = GetBoneWorldPosition(BodyAddv, BoneAddv + 54 * 48);
									AActor.rAnklePos = GetBoneWorldPosition(BodyAddv, BoneAddv + 58 * 48);
								}
								if (Settings::AimWarning) {


									FRotator RelativeRotation = Utility::ReadMemoryEx<FRotator>(RootComponent + Offset::RelativeRotation);
									ClampAngles(RelativeRotation);
									DWORD LocalRoot = Utility::ReadMemoryEx<DWORD>(LocalPlayer + Offset::Data::RootComponent);
									VECTOR3 MyPositionnnn = Utility::ReadMemoryEx<VECTOR3>(LocalRoot + Offset::Position);
									VECTOR3 MyHEad = MyPositionnnn;
									VECTOR3 EnemyHed = AActor.Position;

									auto Angle = ToRotator(EnemyHed, MyHEad);
									ClampAngles(Angle);

									float num = abs(RelativeRotation.Pitch - Angle.Pitch);
									float num2 = abs(RelativeRotation.Yaw - Angle.Yaw);
									bool num3 = (num + num2) <= 6.f;

									AActor.isAimingAtMe = false;
									if (num3 == true) {
										AActor.isAimingAtMe = true;
									}

								}

								AActorListtt.push_back(AActor);
							}
							else {
								ItemType = GetGrenadeType(EntityType);
								if (ItemType != "Unknown")
								{

									Item Item;
									Item.Name = ItemType;
									Item.Position = ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);

									ItemList.push_back(Item);
								}

								if (Settings::Lootbox && IsBox(EntityType))
								{

									g_pEsp->lootbox.push_back(g_pEsp->lbox);
									count = ReadMemoryEx<DWORD>(EntityAddress + Offset::LootBox::boxItemsCount);
									if (count > 30)
										count = 30;
									g_pEsp->lbox.boxitem.resize(0);
									if (count > 0)

									{
										itemBase = ReadMemoryEx<DWORD>(EntityAddress + Offset::LootBox::itemBase);
										itemAddv;

										for (int t = 0; t < count; t++)
										{
											itemAddv = itemBase + t * 48;
											string bitm = GetBoxItems(ReadMemoryEx<DWORD>(itemAddv + 0x4));
											if (bitm.find("tatti") == string::npos)
											{
												Itemb temo;
												bitm.append("  :  ").append(to_string(ReadMemoryEx<DWORD>(itemAddv + 0x18)));
												g_pEsp->lbox.Position = ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);
												temo.colorcod = Settings::colorcode;
												temo.Displayname = bitm;
												g_pEsp->lbox.boxitem.push_back(temo);
											}
										}
									}


								}

								else {

									if (Settings::Items)
									{
										ItemType = GetItemType(EntityType);
										if (ItemType.find("Unknown") == string::npos)
										{

											Item Item;
											Item.Name = ItemType;
											Item.Position = ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);

											ItemList.push_back(Item);
										}
									}

									if (Settings::Vehicle)
									{
										VehicleType = GetVehicleType(EntityType);
										if (VehicleType.find("Unknown") == string::npos)
										{
											Vehicle Vehicle;
											Vehicle.Name = VehicleType;
											Vehicle.Position = ReadMemoryEx<VECTOR3>(RootComponent + Offset::Position);

											DWORD veh = ReadMemoryEx<DWORD>(EntityAddress + Offset::vehicle::VehicleCommon);
											float HP = ReadMemoryEx<float>(veh + Offset::vehicle::HP);
											float HPMax = ReadMemoryEx<float>(veh + Offset::vehicle::HPMax);
											float Fuel = ReadMemoryEx<float>(veh + Offset::vehicle::Fuel);
											float FuelMax = ReadMemoryEx<float>(veh + Offset::vehicle::FuelMax);

											// Ensure values are within valid ranges
											Vehicle.hp = myMax(0.0f, myMin(HP, HPMax));
											Vehicle.hpmax = myMax(0.0f, HPMax);
											Vehicle.oil = myMax(0.0f, myMin(Fuel, FuelMax));
											Vehicle.oilmax = myMax(0.0f, FuelMax);
											Vehicle.driving = ReadMemoryEx<DWORD>(EntityAddress + Offset::vehicle::bIsEngineStarted);

											VehicleList.push_back(Vehicle);
										}
									}
								}


							}
						}

					}

				}
			}
		}
		Data::AActorList.resize(0);
		Data::ItemList.resize(0);
		Data::VehicleList.resize(0);
		g_pEsp->lootboxr.resize(0);

		Data::AActorList = AActorListtt;
		Data::ItemList = ItemList;
		Data::VehicleList = VehicleList;
		g_pEsp->lootboxr = g_pEsp->lootbox;

		AActorListtt.resize(0);
		ItemList.resize(0);
		VehicleList.resize(0);

		g_pEsp->lootbox.resize(0);
		g_pEsp->lootbox.resize(0);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	}
}
