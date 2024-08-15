#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "ImguiPP.h"
#include "Iconcpp.h"
#include "Font.h"
#include "Icon.h"
#include "Includes/obfuscate.h"
#include "fake_dlfcn.h"
#include "Includes.h"
#include "plthook.h"
#include "json.hpp" // JSON library
#include "Items.h"
#include "StrEnc.h"
#include "Spoof.h"
#include "SDK.hpp"
#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>// For POSIX functions like `open`
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "KittyMemory/MemoryPatch.h"
#include "Rect.h"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "MemoryTools.h"
#include "Macros.h"
#include "Substrate/SubstrateHook.h"
#include "foxcheats/include/ScanEngine.hpp"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "fontch.h"
#define targetLibName OBFUSCATE("libUE4.so")
#include "Includes/Macros.h"
#include "Colors.h"
#include <string>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sys/stat.h> // For file permission constants

bool Godzillasuit = false;


bool WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

template<typename T>
void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}


bool ReadAddr(void *addr, void *buffer, size_t length) {
    // Get the system page size
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    // Calculate the aligned address and size
    uintptr_t page_start = (uintptr_t)addr & ~(page_size - 1);
    size_t size = (uintptr_t)addr - page_start + length;

    // Change memory protection to allow read
    if (mprotect((void *)page_start, size, PROT_READ) != 0) {
        return false;
    }

    // Copy the memory content to the buffer
    memcpy(buffer, addr, length);

    // Restore the original protection (optional but good practice)
    mprotect((void *)page_start, size, PROT_READ | PROT_EXEC);

    return true;
}

template<typename T>
T Read(uintptr_t addr) {
    T value;
    if (ReadAddr((void *)addr, &value, sizeof(T))) {
        return value;
    } else {
        // Handle the error case as appropriate
        return T(); // Return a default-constructed T
    }
}

// Function to read a single byte from a memory address
uint8_t ReadByte(uintptr_t addr) {
    uint8_t value = 0;
    if (ReadAddr((void *)addr, &value, sizeof(uint8_t))) {
        return value;
    } else {
        // Handle the error case as appropriate
        return 0; // Return 0 or any appropriate default value
    }
}

using json = nlohmann::json;
using namespace SDK;
using namespace std;

#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

// ======================================================================== //
bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;
json mItemData;
time_t rng = 0;
std::string expiretime = "";
std::string g_Token, g_Auth;
bool bValid = false;
#define SLEEP_TIME 1000LL / 120LL
uintptr_t tersafe;
float countenemHeight = 49.290f;
float countenemWidth = 163.041f;
static int screepos = 20;
 float name = 13.0f;
 float Thickness = 1.5f;
static float imheight = 0.75f;
static float imwidth = 0.30f;

static int xsuit = 0;
static int skinm4 = 0;
static int skinakm = 0;
static int skinscar = 0;

bool ggxhit = false;
bool magic = false;
bool patchlimit = false;

int static posx = 0;
int static posy = 0;

float static ipadvalue = 120.0f;

#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))

#define PI 3.141592653589793238

uintptr_t g_UE4;
uintptr_t g_Anogs;
uintptr_t g_gcloud;
uintptr_t g_swappy;
uintptr_t g_TDataMaster;
uintptr_t g_anort;

uintptr_t AimBullet_Offset;
uintptr_t GWorld_Offset, GUObjectArray_Offset, SilentAim_Offset;
android_app *g_App = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;


#define GNames_Offset 0x424D560
#define GUObject_Offset 0x8816B78
#define GNativeAndroidApp_Offset 0x863EEE8
#define Actors_Offset 0x70
#define GetActorArray 0x5D4FCA8
#define ShortEvent_Offset 168 //BT/AimBot

int cross = 90,range = 120, curraim = 0;
bool bulletrack = false;

struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;



bool isObjectInvalid(UObject *obj) {
    if (!Tools::IsPtrValid(obj)) {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate)) {
        return true;
    }

    if (obj->InternalIndex <= 0) {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0) {
        return true;
    }

    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
        return true;
    }

    return false;
}



static UEngine *GEngine = 0;
UWorld *GetWorld() {
    while (!GEngine) {
        GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1");
        sleep(1);
    }
    if (GEngine) {
        auto ViewPort = GEngine->GameViewport;
        if (ViewPort) {
            return ViewPort->World;
        }
    }
    return 0;
}



TNameEntryArray *GetGNames() {
    return ((TNameEntryArray *(*)()) (g_UE4 + GNames_Offset))();
}

std::vector<AActor *> getActors() {
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();

    struct GovnoArray {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };
    static thread_local GovnoArray Actors{};

    Actors = *(((GovnoArray*(*)(uintptr_t))(g_UE4 + GetActorArray))(reinterpret_cast<uintptr_t>(PersistentLevel)));

    if (Actors.count <= 0) {
        return {};
    }

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.count; i++) {
        auto Actor = *(uintptr_t *) (Actors.base + (i * sizeof(uintptr_t)));
        if (Actor) {
            actors.push_back(reinterpret_cast<AActor *const>(Actor));
        }
    }
    return actors;
}



SDK::FVector SubtractVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;
    result.Z = a.Z - b.Z;
    return result;
}

FRotator ToRotator(FVector local, FVector target) {
    FVector Lund = SubtractVectors(target, local);
    FRotator newViewAngle = {0};
    newViewAngle.Pitch =
            -std::atan2(Lund.Z, std::sqrt(Lund.X * Lund.X + Lund.Y * Lund.Y)) * (180.f / M_PI);
    newViewAngle.Yaw = std::atan2(Lund.Y, Lund.X) * (180.f / M_PI);
    newViewAngle.Roll = 0.f;
    if (newViewAngle.Yaw < 0.f) {
        newViewAngle.Yaw += 180.f;
    }
    return newViewAngle;

}


FRotator ToRotatorForCar(FVector local, FVector target) {
    FVector difference = SubtractVectors(target, local);

    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -std::atan2(difference.Z, std::sqrt(difference.X * difference.X + difference.Y * difference.Y)) * (180.f / M_PI);
    newViewAngle.Yaw = std::atan2(difference.Y, difference.X) * (180.f / M_PI);
    newViewAngle.Roll = 0.f;

    if (newViewAngle.Yaw < 0.f) {
        newViewAngle.Yaw += 360.f; // Corrected to add 360 degrees instead of 180
    }

    return newViewAngle;
}


bool isInsideCircle(float x, float y, float rad) {

    if(!rad) return false;
    float circle_x = (float) glWidth / 2;
    float circle_y = (float) glHeight / 2;

    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

auto protect(uintptr_t addr, size_t len, int32_t prot) {
    static_assert(PAGE_SIZE == 4096);
    constexpr size_t page_size = static_cast<size_t>(PAGE_SIZE);
    void* start = reinterpret_cast<void*>(addr & -page_size);
    uintptr_t end = (addr + len + page_size - 1) & -page_size;
    return mprotect(start, end - reinterpret_cast<uintptr_t>(start), prot);
}

#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(g_LocalController, w, true, s)



//=====BukketTrack======//


auto GetTargetByPussy() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = getActors();

    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto Player = (ASTExtraPlayerCharacter *) Actor;

                int Distance = localPlayer->GetDistanceTo(Player) / 100.0f;
                if (Distance > range)
                    continue;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                auto Head = Player->GetBonePos("Head", {});

                FVector2D HeadSc;
                if (W2S(Head, &HeadSc)) {
                    if (isInsideCircle(HeadSc.X, HeadSc.Y,
                                       (float) cross)) {
                        float Distance = FVector2D::Distance(
                                FVector2D((float) (glWidth / 2), (float) (glHeight / 2)),
                                HeadSc);
                        if (Distance < max) {
                            max = Distance;
                            result = Player;
                        }
                    }
                }
            }
        }
    }

    return result;
}




float GetBulletGravity()
{
    // Read the necessary memory addresses to retrieve the bullet gravity
    DWORD CharacterWeaponManagerComponent = *(DWORD*)((uintptr_t) g_LocalPlayer + 0x1ae0); /////CharacterWeaponManagerComponent* WeaponManagerComponent;//[Offset:
    DWORD CurrentWeaponReplicated = *(DWORD*)((uintptr_t)CharacterWeaponManagerComponent + 0x40c); ///STExtraWeapon* CurrentWeaponReplicated;
    DWORD ShootWeaponEntity = *(DWORD*)((uintptr_t)CurrentWeaponReplicated + 0xcb8); /// ShootWeaponEntity* ShootWeaponEntityComp;//[Offset:
    uintptr_t BulletTemplate = *(uintptr_t*)((uintptr_t)ShootWeaponEntity + 0x41c); /// class STExtraShootWeaponBulletBase* BulletTemplate
    float LaunchGravityScale = *(float*)((uintptr_t)ShootWeaponEntity + 0x414); /// float LaunchGravityScale

    // Return the bullet gravity
    return LaunchGravityScale;
}

FVector KinematicEquationPrediction(float distance, const FVector& headPos, const FVector& velocity, float bulletSpeed, float gravity) {
    FVector predictedPos = headPos;

    if (bulletSpeed > 0) {
        float bulletTravelTime = distance / (bulletSpeed / 100.f);

        predictedPos.X += velocity.X * bulletTravelTime;
        predictedPos.Y += velocity.Y * bulletTravelTime;
        predictedPos.Z += velocity.Z * bulletTravelTime + 0.5f * gravity * bulletTravelTime * bulletTravelTime;
    }

    return predictedPos;
}


void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector CameraPovLoc, FRotator aimRotation, void *unk1, int unk2) = 0;

void shoot_event(USTExtraShootWeaponComponent *thiz, FVector CameraPovLoc, FRotator aimRotation, ASTExtraShootWeapon *weapon, int unk1) {
    if (bulletrack) {
        ASTExtraPlayerCharacter *Target = GetTargetByPussy();
        if (Target) {
            if (g_LocalPlayer->bIsWeaponFiring) {
                FVector targetAimPos;

                // Determine aim position based on current aim mode
                switch (curraim) {
                    case 0:
                        targetAimPos = Target->GetBonePos("neck_01", {});
                        targetAimPos.Z += 15.0f; // Adjust for head position
                        break;
                    case 1:
                        targetAimPos = Target->GetBonePos("spine_02", {});
                        break;
                    case 2:
                        targetAimPos = Target->GetBonePos("Pelvis", {});
                        break;
                    default:
                        targetAimPos = Target->GetBonePos("neck_01", {});
                        targetAimPos.Z += 15.0f; // Default to head position adjustment
                        break;
                }

                // Get the ShootWeaponEntityComponent and retrieve bullet parameters
                UShootWeaponEntity *ShootWeaponEntityComponent = thiz->ShootWeaponEntityComponent;
                if (ShootWeaponEntityComponent) {
                    auto BulletFireSpeed = *(float*)((uintptr_t)ShootWeaponEntityComponent + 0x420); // Read bullet fire speed
                    FVector TargetVelocity = (Target->CurrentVehicle) ? Target->CurrentVehicle->ReplicatedMovement.LinearVelocity : Target->GetVelocity();
                    float gravity = GetBulletGravity();
                    float dist = g_LocalPlayer->GetDistanceTo(Target);

                    // Calculate the time for the bullet to travel the distance
                    auto timeToTravel = dist / BulletFireSpeed;
                    // Adjust target aim position considering the target's velocity
                    targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(TargetVelocity, timeToTravel));

                    // Calculate bullet drop
                    float bulletDrop = 0.5f * gravity * timeToTravel * timeToTravel;
                    targetAimPos.Z -= bulletDrop; // Adjust aim position for bullet drop

                    // Calculate firing direction and adjust aim rotation
                    FVector firingDirection = UKismetMathLibrary::Subtract_VectorVector(targetAimPos, CameraPovLoc);
                    FRotator my_Rotation = UKismetMathLibrary::Conv_VectorToRotator(firingDirection);
                    aimRotation = my_Rotation;
                }
            }
        }
    }
    // Call the original shoot event with modified parameters
    return orig_shoot_event(thiz, CameraPovLoc, aimRotation, weapon, unk1);
}





FVector CalculateLinearVelocity(float cameraYaw, float speed) {
    // Convert yaw to radians
    float yawInRadians = cameraYaw * (M_PI / 180.0f); // Degrees to radians

    FVector linearVelocity;
    linearVelocity.X = speed * std::cos(yawInRadians);
    linearVelocity.Y = speed * std::sin(yawInRadians);
    linearVelocity.Z = 0.0f; // Ensure no vertical movement

    return linearVelocity;
}


// Helper function to normalize a vector and scale it to a desired length
FVector CapVelocity(const FVector& velocity, float maxSpeed) {
    float speed = velocity.Size(); // Get the current speed
    if (speed > maxSpeed) {
        FVector normalizedVelocity = velocity / speed; // Normalize
        return normalizedVelocity * maxSpeed; // Scale to maxSpeed
    }
    return velocity; // Return original velocity if within speed limit
}

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{

    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    if (glWidth <= 0 || glHeight <= 0)
        return eglSwapBuffers(dpy, surface);

    if (!g_App)
        return eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = (float) AConfiguration_getDensity(g_App->config);

    if (density == 0)
        return eglSwapBuffers(dpy, surface);

    auto GWorld = GetWorld();

    if (GWorld)
    {
        UNetDriver *NetDriver = GWorld->NetDriver;
        if (NetDriver) {

            UNetConnection *ServerConnection = NetDriver->ServerConnection;
            ASTExtraPlayerCharacter *localPlayer = 0;
            ASTExtraPlayerController *localController = 0;

            if (ServerConnection) {

                localController = (ASTExtraPlayerController *) ServerConnection->PlayerController;

            }

            if (localController) {

                auto Actors = getActors();


                for (int i = 0; i < Actors.size(); i++) {
                    auto Actor = Actors[i];
                    if (isObjectInvalid(Actor))
                        continue;

                    if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
                    {
                        if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey ==localController->PlayerKey) {
                            localPlayer = (ASTExtraPlayerCharacter *) Actor;
                            break;
                        }
                    }
                }



                if (localPlayer) {


                    uint8_t crazycar = ReadByte(g_UE4 + 0xB0);
                    cross = Read<float>(g_UE4 + 0x70);
                    range = Read<float>(g_UE4 + 0x130);
                    curraim = Read<float>(g_UE4 + 0x80);
                    uint8_t BulletTrack = ReadByte(g_UE4 + 0xD0);

                 //  LOGI("BulletTrack real val: %02x", BulletTrack);
                 //  LOGI("FOV : %d",cross);
                 //  LOGI("Range : %d",range);
                 //  LOGI("curraim : %d",curraim);


                    if(BulletTrack == 0x01){

                        bulletrack = true;
                    //    LOGI("BT IS ON %d", bulletrack);
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;

                                    if (ShootWeaponComponent) {

                                        int shoot_event_idx = 168;
                                        auto VTable = (void **) ShootWeaponComponent->VTable;
                                        if (VTable && (VTable[shoot_event_idx] != shoot_event)) {
                                            orig_shoot_event = decltype(orig_shoot_event)(
                                                    VTable[shoot_event_idx]);

                                            protect((uintptr_t) (&VTable[shoot_event_idx]),
                                                    sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                            VTable[shoot_event_idx] = (void *) shoot_event;
                                        }
                                    }
                                }
                            }
                        }
                    }else if(BulletTrack != 0x01){ bulletrack = false; }

                    if(crazycar == 0x01){

                        if (localPlayer->CurrentVehicle) {
                            auto CurrentVehicle = localPlayer->CurrentVehicle;
                            auto RootComponent = static_cast<UPrimitiveComponent*>(CurrentVehicle->K2_GetRootComponent());

                            const float MaxSpeed = 60.0f;
                            float cameraYaw = localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw;
                            float coeff = CurrentVehicle->GetMoveForwardRate() > 0 ? (60.0f * 60.0f) * 2.0f * 0.01 : (60.0f * 60.0f) * 8.0f * 0.01 ; // limit speed till 80
                            FVector desiredVelocity = CalculateLinearVelocity(cameraYaw, coeff);
                            if(!(CurrentVehicle->GetMoveForwardRate() > 0)){
                                desiredVelocity = CapVelocity(desiredVelocity, MaxSpeed); // Cap speed
                            }
                            RootComponent->SetAllPhysicsLinearVelocity(desiredVelocity, true);
                        }
                    }

                    for (int i = 0; i < Actors.size(); i++) {
                        auto Actor = Actors[i];

                        if (isObjectInvalid(Actor))
                            continue;

                        if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                            auto Player = (ASTExtraPlayerCharacter *) Actor;
                            bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);

                            if (Player->bDead)
                                continue;

                            if (Player->PlayerKey == localController->PlayerKey)
                                continue;

                            if (Player->TeamID == localController->TeamID)
                                continue;


                            int* PlayerLineOfSightTo = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(Player) + 0x1D2);
                            *PlayerLineOfSightTo = 0;

                            ASTExtraVehicleBase * CurrentVehiclea = Player->CurrentVehicle;
                            if (CurrentVehiclea)
                            {
                                *PlayerLineOfSightTo = IsVisible;

                            }else{
                                APlayerCameraManager* PlayerCameraManager = localController->PlayerCameraManager;
                                if (PlayerCameraManager)
                                {
                                    FVector ViewPointFromCamera = PlayerCameraManager->GetCameraLocation();
                                    float SizeSquared = ViewPointFromCamera.X * ViewPointFromCamera.X +
                                                        ViewPointFromCamera.Y * ViewPointFromCamera.Y +
                                                        ViewPointFromCamera.Z * ViewPointFromCamera.Z;
                                    if (SizeSquared > 0)
                                    {
                                        bool bHasLineOfSight = localController->LineOfSightTo(Player, ViewPointFromCamera, true);
                                        if (bHasLineOfSight)
                                        {
                                            *PlayerLineOfSightTo = 1;
                                        }
                                    }
                                }
                            }

                        }

                    }

                }

            }

            g_LocalPlayer = localPlayer;
            g_LocalController = localController;
        }

    }
    return orig_eglSwapBuffers(dpy, surface);
}


int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);

int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent) {
    if (initImGui) {
        ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});
    }
    return orig_onInputEvent(app, inputEvent);
}



void* loadClonedLibrary(const std::string& newLibraryPath) {
    void* handle = dlopen(newLibraryPath.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        LOGI("Failed to load library: %s", dlerror());
    } else {
        LOGI("library loaded successfully: %s", newLibraryPath.c_str());
    }
    return handle;
}



void *main_thread(void *) {
    sleep(5);
    g_UE4 = Tools::GetBaseAddress("libUE4.so");

    while (!g_UE4) {
        g_UE4 = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }

    g_gcloud = Tools::GetBaseAddress("libhdmpve.so");
    g_Anogs = Tools::GetBaseAddress("libanogs.so");

    while (!g_App) {
        g_App = *(android_app **) (g_UE4 + GNativeAndroidApp_Offset);
        sleep(1);
    }

    FName::GNames = GetGNames();
    while (!FName::GNames) {
        FName::GNames = GetGNames();
        sleep(1);
    }
    UObject::GUObjectArray = (FUObjectArray *) (g_UE4 + GUObject_Offset);


    orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
    g_App->onInputEvent = onInputEvent;

   // Config.BulletTracking.Cross = 500.0f;
    Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libandroid_runtime.so"), OBFUSCATE("eglSwapBuffers")), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);





  LOGI("HOOKED_UE4 done (XREF) %p", g_UE4);
  LOGI("HOOKED_Anogs done (XREF) %p", g_Anogs);

  loadClonedLibrary("libbypass.so");

    return 0;
}


__attribute__((constructor)) void _init() 
{

    pthread_t t;

    pthread_create(&t, 0, main_thread, 0);
}


