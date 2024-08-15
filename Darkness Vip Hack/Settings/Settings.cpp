#include "../Settings/Settings.h"

bool Settings::sendscreenshot = false;
bool Settings::Login = false;
bool Settings::FightMode = false;
bool Settings::ShowMenu = true;
bool Settings::ShowMenu2 = true;
bool Settings::Injected = false;
int Settings::Mode = 0;
int Settings::SecondMenuMode = 0;
int Settings::curraim = 0;

//aim
int Settings::macroval = 0;
int Settings::currentBoneIndex = -1;
int Settings::weight = 1;
bool Settings::isPrioritySet = false;
int Settings::MaxAimDistence = 250;
int Settings::AimKey = false;
bool Settings::SkipBots = false;
bool Settings::AimBot = false;
bool Settings::knocked = true;
bool Settings::Legitrack = false;
bool Settings::MagicBullet = false;
bool Settings::Fovbased = true;
int Settings::aimbotmode = 0;
//bool Settings::FovShow = false;
bool Settings::FovShow = true;
float Settings::fovcircleredus = 100;
float Settings::AimSpeed = 3.5;
int Settings::bulletrackMode = 0;
bool Settings::crosshair = false;
ImVec4 Settings::FovColor = { 0.942f, 0.300f, 0.073f, 1.000f };

string Settings::notifysate = "";


ImVec4 Settings::colorcode;

bool Settings::BypassFovLimit = false;
bool Settings::visbulletcheck = false;

int Settings::prediction = 0;


int Settings::AlivePlayers;
int Settings::TimeRemind;
int Settings::AliveTeams;
int Settings::RealPls;
int Settings::ZoneID;
int Settings::MyTeamID;
int Settings::GameID;
string Settings::MyName;
int Settings::Tab = 1;
string Settings::GameState;

bool Settings::log = false;

//Memory 
bool Settings::AntiStream = false;
bool Settings::IpadView = false;
bool Settings::NoRecoil = false;
bool Settings::ForceTpp = false;
bool Settings::Xeffect = false;
bool Settings::InstantHit = false;
bool Settings::NoSpread = false;
bool Settings::FastSwitch = false;
bool Settings::RepidFire = false;
bool Settings::ModSKin = false;
bool Settings::Magic360 = false;
int Settings::IpadValue = 320;
int Settings::InstantValue = 1000;
float Settings::RepidFireValue = 0.2;
float Settings::percentage = 0.0f;
bool Settings::carsex = false;
int Settings::carsexkey = false;
bool Settings::internalTrack = false;
int Settings::rangeinternal = 120;
int Settings::fovinternal = 90;
//setting
int Settings::UpdateTick = 20; //90fps
int Settings::UpdateFps = 23; //60fps

//Esp
bool Settings::visibilitycheck = false;
bool Settings::grenadePath = false;
bool Settings::peekdetect = true;
bool Settings::YourInfo = true;
bool Settings::GameInfo = false;
bool Settings::PlayerName = true;
bool Settings::PlayerSkeleton = true;
bool Settings::PlayerLine = true;
bool Settings::PlayerDistance = true;
bool Settings::PlayerHealth = true;
bool Settings::PlayerWeapon = true;
bool Settings::PlayerFlag = false;
bool Settings::PlayerBox = true;
bool Settings::PlayerState = false;
bool Settings::Items = true;
bool Settings::TotalEnemy = true;
bool Settings::Vehicle = true;
bool Settings::Lootbox = false;
bool Settings::LootboxItems = true;
bool Settings::AirDrop = true;
bool Settings::AirDropItems = true;
bool Settings::GrandeWarning = true;
bool Settings::AimWarning = true;
bool Settings::Redzone = true;
bool Settings::Dots = false;
bool Settings::Radar = false;

ImVec4 Settings::PlayerNameColor = { 1.000f, 1.000f, 0.000f, 1.000f };
ImVec4 Settings::PlayerSkeletonColor = { 0.980, 0.990, 0.990,1.0 };
ImVec4 Settings::PlayerLineColor = { 0.211, 0.960, 0.923,1.0 };
ImVec4 Settings::PlayerBoxColor = { 0.890, 0.890, 0.899,1.0 };
ImVec4 Settings::PlayerStateColor = { 1.0, 0.0, 0.0, 1.0 };
ImVec4 Settings::VehicleColor = { 0.837, 0.850, 0.0680,1.0 };
ImVec4 Settings::visColor = { 0.0f, 1.0f, 0.0f, 1.0f };

int Settings::PlayerNameSize = 17;
int Settings::PlayerStateSize = 13;
int Settings::VehicleSize = 17;
int Settings::DotsSize = 50;
int Settings::RadarSize = 150;
int Settings::PlayerLineMode = 0;
int Settings::PlayerSkeletonMode = 0;

float Settings::skeletonthickness = 1.0f;
float Settings::linethickness = 1.0f;

#pragma region Items
bool Settings::Akm = true;
bool Settings::M16A4 = false;
bool Settings::SCARL = true;
bool Settings::M416 = true;
bool Settings::GROZA = true;
bool Settings::AUG = true;
bool Settings::QBZ = true;
bool Settings::M762 = true;
bool Settings::MK47 = false;
bool Settings::G36C = true;
bool Settings::HONEY = true;
bool Settings::FAMAS = false;
bool Settings::KAR98 = true;
bool Settings::M24 = true;
bool Settings::AWM = true;
bool Settings::WIN94 = true;
bool Settings::MOSIN = true;
bool Settings::AMR = true;
bool Settings::SKS = false;
bool Settings::VSS = false;
bool Settings::MINI14 = false;
bool Settings::MK14 = true;
bool Settings::SLR = false;
bool Settings::QBU = true;
bool Settings::MK12 = true;
bool Settings::UZI = true;
bool Settings::UMP45 = false;
bool Settings::VECTOR = false;
bool Settings::THOMPSON = false;
bool Settings::BIZON = false;
bool Settings::MP5K = false;
bool Settings::P90 = false;
bool Settings::S686 = false;
bool Settings::S1897 = false;
bool Settings::S12K = false;
bool Settings::DBS = false;
bool Settings::M1014 = true;
bool Settings::NS2000 = true;
bool Settings::M249 = true;
bool Settings::DP28 = true;
bool Settings::MG3 = true;
bool Settings::FLARE = true;
bool Settings::FRAG = true;
bool Settings::SMOKE = true;
bool Settings::MOLOTOF = true;
bool Settings::MedKit = true;
bool Settings::FirstAidKit = true;
bool Settings::Painkiller = true;
bool Settings::EnergyDrink = true;
bool Settings::Adrenalin = true;
bool Settings::Bag1 = false;
bool Settings::Bag2 = false;
bool Settings::Bag3 = true;
bool Settings::Helmet1 = false;
bool Settings::Helmet2 = false;
bool Settings::Helmet3 = true;
bool Settings::Armor1 = false;
bool Settings::Armor2 = false;
bool Settings::Armor3 = true;
bool Settings::a762mm = true;
bool Settings::a556mm = true;
bool Settings::a9mm = false;
bool Settings::a45ACP = false;
bool Settings::a12Gauege = false;
bool Settings::AwmAmmo = true;
bool Settings::AmrAmmo = true;
bool Settings::Scope_x2 = true;
bool Settings::Scope_x3 = true;
bool Settings::Scope_x4 = true;
bool Settings::Scope_x6 = true;
bool Settings::Scope_x8 = true;
bool Settings::ShopToken = true;
bool Settings::ExtendedMac = true;
bool Settings::Supressor = true;

ImVec4 Settings::AkmColor = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::M16A4Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::SCARLColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::M416Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::GROZAColor = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::AUGColor = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::QBZColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::M762Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::MK47Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::G36CColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::HONEYColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::FAMASColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::KAR98Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::M24Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::AWMColor = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::WIN94Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::MOSINColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::AMRColor = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::SKSColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::VSSColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::MINI14Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::MK14Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::SLRColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::QBUColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::MK12Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::UZIColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::UMP45Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::VECTORColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::THOMPSONColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::BIZONColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::MP5KColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::P90Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::S686Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::S1897Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::S12KColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::DBSColor = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::M1014Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::NS2000Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::M249Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::DP28Color = { 1.000f, 0.695f, 0.323f, 1.000f };
ImVec4 Settings::MG3Color = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::FLAREColor = { 1.00, 0.0400, 0.104,1.000f };

ImVec4 Settings::FRAGColor = { 1.000, 0.000, 0.000, 1.000f }; // Red
ImVec4 Settings::SMOKEColor = { 1.000, 1.000, 1.000, 1.000f }; // White
ImVec4 Settings::MOLOTOFColor = { 1.000, 1.000, 0.000, 1.000f }; // Yellow


ImVec4 Settings::MedKitColor = { 0.0486, 0.810, 0.125,1.000f };
ImVec4 Settings::FirstAidKitColor = { 0.0486, 0.810, 0.125,1.000f };
ImVec4 Settings::PainkillerColor = { 0.0486, 0.810, 0.125,1.000f };
ImVec4 Settings::EnergyDrinkColor = { 0.0486, 0.810, 0.125,1.000f };
ImVec4 Settings::AdrenalinColor = { 0.0486, 0.810, 0.125,1.000f };
ImVec4 Settings::Bag1Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Bag2Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Bag3Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Helmet1Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Helmet2Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Helmet3Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Armor1Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Armor2Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::Armor3Color = { 0.734, 0.0486, 0.810,1.000f };
ImVec4 Settings::a762mmColor = { 0.680, 0.624, 0.0136,1.000f };
ImVec4 Settings::a556mmColor = { 0.236, 0.680, 0.0136,1.000f };
ImVec4 Settings::a9mmColor = { 0.680, 0.0136, 0.558,1.000f };
ImVec4 Settings::a45ACPColor = { 0.680, 0.0136, 0.558,1.000f };
ImVec4 Settings::a12GauegeColor = { 0.680, 0.0136, 0.558,1.000f };
ImVec4 Settings::AwmAmmoColor = { 1.00, 0.0400, 0.104,1.000f };
ImVec4 Settings::AmrAmmoColor = { 1.00, 0.0400, 0.104,1.000f };


ImVec4 Settings::Scope_x2Color = { 0.00, 1.00, 0.950,1.0 };
ImVec4 Settings::Scope_x3Color = { 0.00, 1.00, 0.950,1.0 };
ImVec4 Settings::Scope_x4Color = { 0.00, 1.00, 0.950,1.0 };
ImVec4 Settings::Scope_x6Color = { 0.00, 1.00, 0.950,1.0 };
ImVec4 Settings::Scope_x8Color = { 0.00, 1.00, 0.950,1.0 };
ImVec4 Settings::ShopTokenColor = { 0.680, 0.0136, 0.558,1.000f };
ImVec4 Settings::ExtendedMacColor = { 0.680, 0.0136, 0.558,1.000f };
ImVec4 Settings::SupressorColor = { 0.680, 0.0136, 0.558,1.000f };
#pragma endregion



int ModSkin::Suit = 0;
int ModSkin::Helmet = 0;
int ModSkin::BackBack = 0;
int ModSkin::Akm = 0;
int ModSkin::M16a4 = 0;
int ModSkin::Scar = 0;
int ModSkin::M416 = 0;
int ModSkin::M762 = 0;
int ModSkin::Ump = 0;
int ModSkin::Kar98 = 0;
int ModSkin::M24 = 0;
int ModSkin::AWM = 0;
int ModSkin::SKS = 0;
int ModSkin::Mini14 = 0;
int ModSkin::S12k = 0;
int ModSkin::M249 = 0;
int ModSkin::Pan = 0;
int ModSkin::UZI = 0;
int ModSkin::Vector = 0;
int ModSkin::DP28 = 0;