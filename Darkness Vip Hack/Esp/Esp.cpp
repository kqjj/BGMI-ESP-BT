#define STB_IMAGE_IMPLEMENTATION
#pragma warning(disable : 4996)
#include ".\Settings\Settings.h"
#include <D3DX11tex.h>
#define LOADER_BRAND "Loader base"
#include "..\iconcpp.h"

#include "Esp.h"
#include <iostream>
#include <fstream>
#include "..\Data\Data.h"
#include "auth.hpp"
#include "..\SimpleIni.h"
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
#include ".\\discord\\Discord.h"
#include "..\Memory.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <Psapi.h>
#include <cstring>
#include <array>
#include <thread>
#include <iterator>
#include "..\Images\Images.h"
#include <math.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <stdexcept>
#include <filesystem>
#include <stdio.h>
#include "ImagesInclude.hpp"
#include <sstream> 
#include <chrono>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <future>
#include "urlmon.h"
#include <exception>
#include <vector>
#include <imgui_notify.h>
#include <tahoma.h>
#include <cmath> // For std::cos, std::sin, and std::atan2
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <GUI/gui.h>
#include <loader/LoaderUpdater.h>

#define ICON_FA_HOME "\xef\x80\x95"  // U+f015
#define ICON_FA_CROSSHAIRS "\xef\x81\x9b"  // U+f05b
#define ICON_FA_GUN "\xef\x8b\x88"  // Example, replace with actual
#define ICON_FA_COG "\xef\x80\x93"  // U+f013

// Map to store grenade paths and set to track active grenades
std::map<const Item*, std::vector<VECTOR3>> grenadePaths;
std::set<const Item*> activeGrenades;

FLOAT animationSpeed = 5.0f;     // Speed of the animation
FLOAT animationRange = 5.0f;     // Range of animation movement
// Calculate animation offset based on time or frame count
static FLOAT animationTime = 0.0f;

//Discord* g_Discord;
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace KeyAuth;

std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
std::string name = "animetone";
std::string ownerid = "XQFamIACDQ";
std::string secret = "955f685ad87f6d07aa4dd227ddace442be789b7a6a3db32963510b90f64db0aa";
std::string version = "1.0";
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting

//std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
//std::string name = "ravanfree";
//std::string ownerid = "iz7KyVuIQW";
//std::string secret = "e817e807dd2fadf9f56842d69981c7edb6fc23a15336f1303cb3417cddc496aa";
//std::string version = "1.0";
//std::string url = "https://api.eternityhax.com/api/1.2/"; // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url,"");
string exeversion = "8.0";
LoaderUpdater updater(exeversion, "https://pastebin.com/raw/HqqYZw5t", "https://pastebin.com/raw/BDYLR0YL");

void cmdd(string text)
{
	string prim = "/c " + text;
	const char* primm = prim.c_str();
	ShellExecute(0, "open", "cmd.exe", (LPCSTR)primm, 0, SW_HIDE);
}
void InitImages() {
	D3DX11_IMAGE_LOAD_INFO info;
	ID3DX11ThreadPump* pump{ nullptr };
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, LOGO, sizeof(LOGO), &info, pump, &Logo, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, RedZone, sizeof(RedZone), &info, pump, &RedZoneImage, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, ASWSAw, sizeof(ASWSAw), &info, pump, &BRU, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, SM44, sizeof(SM44), &info, pump, &Smk, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, GN1, sizeof(GN1), &info, pump, &GN2, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, AirDropHex, sizeof(AirDropHex), &info, pump, &AirDropImage, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, AkmHex, sizeof(AkmHex), &info, pump, &AkmImage, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, ScarHex, sizeof(ScarHex), &info, pump, &ScarImage, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, ShopTokenHex, sizeof(ShopTokenHex), &info, pump, &ShopTokenImage, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, M416Hex, sizeof(M416Hex), &info, pump, &M416Image, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, M762Hex, sizeof(M762Hex), &info, pump, &M762Image, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, Ammo5Hex, sizeof(Ammo5Hex), &info, pump, &Ammo5Image, 0);
	D3DX11CreateShaderResourceViewFromMemory(DX11::pDevice, Ammo7Hex, sizeof(Ammo7Hex), &info, pump, &Ammo7Image, 0);
}
#pragma endregion
ImVec4 to_vec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}


void DrawImage(ID3D11ShaderResourceView* img, int x, int y, int sizex, int sizey)
{
	ImGui::GetOverlayDrawList()->AddImage(img, ImVec2(x, y), ImVec2(x + sizex, y + sizey));
}


VECTOR3 GetMyLoc() {
	DWORD Rootcomp = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Data::RootComponent);
	return Utility::ReadMemoryEx<VECTOR3>(Rootcomp + Offset::Position);
}

FRotator GetMyRot() {
	DWORD Rootcomp = Utility::ReadMemoryEx<DWORD>(Data::LocalPlayer + Offset::Data::RootComponent);
	return Utility::ReadMemoryEx<FRotator>(Rootcomp + Offset::RelativeRotation);
}




static auto Flags21 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
static auto Flags2 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;




void DrawRadarHUD(FRotator MyRotation, AActor Player, int Distance, int xAxis, int yAxis, int width, int height, ImVec4 color)
{
	const int RadarSize = 175;  // Set the radar size
	const float Padding = 8.0f; // Define padding to ensure circles stay inside the radar box
	const float CenterCircleRadius = 20.0f;  // Radius of the center circle
	const float MiddleCircleRadius = 40.0f;  // Radius of the middle circle
	const float OuterCircleRadius = 70.0f;   // Radius of the outer circle
	const float ArrowSize = 8.0f; // Height of the arrow
	const float ArrowOffset = 12.0f; // Offset for the arrow
	const float LargerArrowScale = 4.5f; // Scale factor for larger arrow

	ImGui::SetNextWindowSize(ImVec2(RadarSize, RadarSize));
	ImGuiIO& Io = ImGui::GetIO();

	// Set a lighter background color for better visibility
	ImVec4 radarBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.3f); // Black background with 70% transparency

	ImGui::PushStyleColor(ImGuiCol_WindowBg, radarBackgroundColor);
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.5f)); // Transparent black border
	ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x - 100, (Io.DisplaySize.y / 2) + 100), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));

	if (ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
	{
		ImVec2 wind = ImGui::GetWindowSize();
		ImVec2 wind2 = ImGui::GetWindowPos();

		bool out = false;
		VECTOR3 siz;
		siz.X = wind.x;
		siz.Y = wind.y;
		VECTOR3 pos;
		pos.X = wind2.x;
		pos.Y = wind2.y;
		float RadarCenterX = pos.X + (siz.X / 2);
		float RadarCenterY = pos.Y + (siz.Y / 2);

		// Calculate player position on radar
		VECTOR3 radarSize;
		radarSize.X = siz.X;
		radarSize.Y = siz.Y;
		radarSize.Z = 0;

		VECTOR3 radarPosition = Algorithm::WorldToRadarM(MyRotation.Yaw, Player.Position, /*Data::CameraCache.POV.Location */ GetMyLoc(), pos.X, pos.Y, radarSize, out);

	

		// Ensure the position is within the radar box with padding
		radarPosition.X = std::clamp(radarPosition.X, pos.X + Padding, pos.X + siz.X - Padding);
		radarPosition.Y = std::clamp(radarPosition.Y, pos.Y + Padding, pos.Y + siz.Y - Padding);

		// Draw player position on radar first with outline
		ImVec4 outlineColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black color for outline
		float outlineThickness = 1.0f;

	

		if (!Player.CurrentVehcile) {

			DX11::ImGui_DX11::DrawCircle(radarPosition.X, radarPosition.Y, 3.5 + outlineThickness, outlineColor, 6.5f + outlineThickness);
			DX11::ImGui_DX11::DrawCircle(radarPosition.X, radarPosition.Y, 3.5, color, 6.5f);
		}
		else {
			// Calculate position to center the icon
			ImVec2 iconPos(radarPosition.X - 3.5 * 2.0f / 4, radarPosition.Y - 3.5 * 2.0f / 2);

			// Draw the FontAwesome vehicle icon (e.g., ICON_FA_CAR)
			ImGui::SetCursorScreenPos(iconPos);
			ImGui::TextColored(ImColor(color), ICON_FA_CAR);

		}
	

		// Draw radar crosshairs with the specified color
		ImVec4 lineColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray color with full opacity
		DX11::ImGui_DX11::DrawLine(RadarCenterX, RadarCenterY, pos.X, pos.Y, lineColor, 1.0f);
		DX11::ImGui_DX11::DrawLine(RadarCenterX, RadarCenterY, pos.X + siz.X, pos.Y, lineColor, 1.0f);
		DX11::ImGui_DX11::DrawLine(pos.X, RadarCenterY, pos.X + siz.X, RadarCenterY, lineColor, 1.0f);
		DX11::ImGui_DX11::DrawLine(RadarCenterX, RadarCenterY, RadarCenterX, pos.Y + siz.Y, lineColor, 1.0f);

		// Draw text indicating distance below each circle
		string distanceText = "50M";
		string distanceText2 = "150M";

		// Draw text below each circle
		ImVec2 textPos1 = ImVec2(RadarCenterX - 20, RadarCenterY + CenterCircleRadius + 3);
		ImVec2 textPos2 = ImVec2(RadarCenterX - 23, RadarCenterY + MiddleCircleRadius + 5);

		DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 15, distanceText, textPos1.x, textPos1.y, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), false);
		DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 15, distanceText2, textPos2.x, textPos2.y, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), false);

		
		// Draw enemy direction arrows
		float enemyYawRadians = (Player.RelativeRotation.Yaw * (3.14159265358979323846f / 180.0f)); // Adjust rotation

		// Original arrow for enemy direction
		ImVec2 enemyDirectionArrow[3] = {
			ImVec2(radarPosition.X + std::cos(enemyYawRadians) * ArrowOffset, radarPosition.Y + std::sin(enemyYawRadians) * ArrowOffset),  // Player position with offset
			ImVec2(radarPosition.X + std::cos(enemyYawRadians - 0.5f) * ArrowSize, radarPosition.Y + std::sin(enemyYawRadians - 0.5f) * ArrowSize),  // Tip of the arrow
			ImVec2(radarPosition.X + std::cos(enemyYawRadians + 0.5f) * ArrowSize, radarPosition.Y + std::sin(enemyYawRadians + 0.5f) * ArrowSize)   // Base of the arrow
		};

		// Larger arrow (upside-down) for enemy direction
		ImVec2 largerEnemyDirectionArrow[3] = {
			ImVec2(radarPosition.X, radarPosition.Y), // Start from the same position as the original arrow
			ImVec2(radarPosition.X + std::cos(enemyYawRadians - 0.5f) * ArrowSize * LargerArrowScale, radarPosition.Y + std::sin(enemyYawRadians - 0.5f) * ArrowSize * LargerArrowScale),  // Tip of the larger arrow
			ImVec2(radarPosition.X + std::cos(enemyYawRadians + 0.5f) * ArrowSize * LargerArrowScale, radarPosition.Y + std::sin(enemyYawRadians + 0.5f) * ArrowSize * LargerArrowScale)   // Base of the larger arrow
		};

		// Draw original arrow indicating enemy direction
		ImVec4 arrowColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White arrow color
		ImU32 arrowColorU32 = ImGui::GetColorU32(arrowColor);


		// Draw own character direction arrow
		float playerYawRadians = /*Data::CameraCache.POV.Rotation.Yaw*/ GetMyRot().Yaw * (3.14159265358979323846f / 180.0f); // Convert degrees to radians and adjust rotation
		ImVec2 playerDirectionArrow[3] = {
			ImVec2(RadarCenterX + std::cos(playerYawRadians) * ArrowOffset, RadarCenterY + std::sin(playerYawRadians) * ArrowOffset),  // Player position with offset
			ImVec2(RadarCenterX + std::cos(playerYawRadians - 0.5f) * ArrowSize, RadarCenterY + std::sin(playerYawRadians - 0.5f) * ArrowSize),  // Tip of the arrow
			ImVec2(RadarCenterX + std::cos(playerYawRadians + 0.5f) * ArrowSize, RadarCenterY + std::sin(playerYawRadians + 0.5f) * ArrowSize)   // Base of the arrow
		};


		// Larger arrow (upside-down) for own character direction
	//ImVec2 largerPlayerDirectionArrow[3] = {
	//	ImVec2(RadarCenterX, RadarCenterY), // Start from the same position as the original arrow
	//	ImVec2(RadarCenterX + std::cos(playerYawRadians - 0.5f) * ArrowSize * LargerArrowScale, RadarCenterY + std::sin(playerYawRadians - 0.5f) * ArrowSize * LargerArrowScale),  // Tip of the larger arrow
	//	ImVec2(RadarCenterX + std::cos(playerYawRadians + 0.5f) * ArrowSize * LargerArrowScale, RadarCenterY + std::sin(playerYawRadians + 0.5f) * ArrowSize * LargerArrowScale)   // Base of the larger arrow
	//};


		if (!Player.CurrentVehcile) {

			ImGui::GetWindowDrawList()->AddTriangleFilled(enemyDirectionArrow[0], enemyDirectionArrow[1], enemyDirectionArrow[2], arrowColorU32);

			// Draw larger arrow (upside-down) for enemy direction
			ImGui::GetWindowDrawList()->AddTriangleFilled(largerEnemyDirectionArrow[0], largerEnemyDirectionArrow[1], largerEnemyDirectionArrow[2], ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.1f)));

		}

		// Draw arrow indicating own character direction
		ImGui::GetWindowDrawList()->AddTriangleFilled(playerDirectionArrow[0], playerDirectionArrow[1], playerDirectionArrow[2], arrowColorU32);

		// Draw larger arrow (upside-down) for own character direction
		//ImGui::GetWindowDrawList()->AddTriangleFilled(largerPlayerDirectionArrow[0], largerPlayerDirectionArrow[1], largerPlayerDirectionArrow[2], ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.1f)));

		// Draw own character position at the center of the radar
		DX11::ImGui_DX11::DrawCircle(RadarCenterX, RadarCenterY, 3.5 + outlineThickness, outlineColor, 6.5f + outlineThickness);
		DX11::ImGui_DX11::DrawCircle(RadarCenterX, RadarCenterY, 3.5, DX11::ImGui_DX11::Color::Yellow, 6.5f);
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}


void DrawCrosshair(float centerX, float centerY, float length, float thickness, ImColor color) {
	// Draw horizontal line
	DX11::ImGui_DX11::DrawLine(centerX - length, centerY, centerX + length, centerY, color, thickness);
	// Draw vertical line
	DX11::ImGui_DX11::DrawLine(centerX, centerY - length, centerX, centerY + length, color, thickness);
}


// Function to draw a line with optional random blinking effect
void DrawLine(VECTOR2 point1, VECTOR2 point2, ImColor color, float thickness, bool enableBlinking, float blinkInterval) {
	ImDrawList* pImGuiDraw = ImGui::GetBackgroundDrawList();

	// Blinking logic
	if (enableBlinking) {
		static bool blinkState = true;
		static auto lastBlinkTime = std::chrono::steady_clock::now();
		static ImColor randomColor = color;

		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsedTime = currentTime - lastBlinkTime;

		if (elapsedTime.count() >= blinkInterval) {
			// Toggle blink state and generate a new random color
			blinkState = !blinkState;
			lastBlinkTime = currentTime;

			if (blinkState) {
				// Generate random color
				randomColor = ImColor(rand() % 256, rand() % 256, rand() % 256);
			}
		}

		// Set color based on blink state
		color = blinkState ? randomColor : color;
	}

	pImGuiDraw->AddLine(ImVec2(point1.X, point1.Y), ImVec2(point2.X, point2.Y), color, thickness);
}

void DrawCircle3D(VECTOR3 center, float radius, ImColor color, float thickness, bool enableBlinking, float blinkInterval, D3DMATRIX ViewMatrix) {
	const int numSegments = 32;
	float angleIncrement = 2 * M_PI / numSegments;

	for (int i = 0; i < numSegments; ++i) {
		float angle1 = i * angleIncrement;
		float angle2 = (i + 1) * angleIncrement;

		// Calculate points on the circle in 3D space
		VECTOR3 point1 = { center.X + radius * cos(angle1), center.Y + radius * sin(angle1), center.Z };
		VECTOR3 point2 = { center.X + radius * cos(angle2), center.Y + radius * sin(angle2), center.Z };

		// Project 3D points to 2D screen space
		VECTOR2 screenPoint1, screenPoint2;
		int distance1, distance2;
		if (Algorithm::WorldToScreenBone(ViewMatrix, point1, screenPoint1, &distance1) && Algorithm::WorldToScreenBone(ViewMatrix, point2, screenPoint2, &distance2)) {
			DrawLine(screenPoint1, screenPoint2, color, thickness, enableBlinking, blinkInterval);
		}
	}
}

bool IsPointInCircle3D(VECTOR3 point, VECTOR3 center, float radius) {
	// Calculate the squared distance between the point and the center
	float distSquared = (point.X - center.X) * (point.X - center.X) +
		(point.Y - center.Y) * (point.Y - center.Y) +
		(point.Z - center.Z) * (point.Z - center.Z);

	// Calculate the squared radius
	float radiusSquared = radius * radius;

	// Check if the point is inside the circle
	return distSquared <= radiusSquared;
}

inline void AddUnderLine(ImColor col_)
{
	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();
	min.y = max.y;
	ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
}

inline void HyperLink(const char* name_, std::string URL_, uint8_t SameLineBefore_, uint8_t SameLineAfter_)
{
	if (1 == SameLineBefore_) { ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x); }
	ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
	ImGui::TextColored(ImVec4(0.090f, 0.509f, 0.921f, 1.000f), name_);
	ImGui::PopStyleColor();
	if (ImGui::IsItemHovered())
	{
		if (ImGui::IsMouseClicked(0))
		{
			string StartCode = "/C start " + URL_;

			ShellExecuteA(NULL, "open", "cmd.exe", StartCode.c_str(), 0, SW_HIDE);

		}
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
		ImGui::SetTooltip(ICON_FA_LINK "  Open in browser\n%s", name_);
	}
	else
	{
		AddUnderLine(ImGui::GetStyle().Colors[ImGuiCol_Button]);
	}
	if (1 == SameLineAfter_) { ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x); }
}

bool ProcessInlineHexColor(const char* start, const char* end, ImVec4& color)
{
	const int hexCount = (int)(end - start);
	if (hexCount == 6 || hexCount == 8)
	{
		char hex[9];
		strncpy(hex, start, hexCount);
		hex[hexCount] = 0;

		unsigned int hexColor = 0;
		if (sscanf(hex, "%x", &hexColor) > 0)
		{
			color.x = static_cast<float>((hexColor & 0x00FF0000) >> 16) / 255.0f;
			color.y = static_cast<float>((hexColor & 0x0000FF00) >> 8) / 255.0f;
			color.z = static_cast<float>((hexColor & 0x000000FF)) / 255.0f;
			color.w = 1.0f;

			if (hexCount == 8)
			{
				color.w = static_cast<float>((hexColor & 0xFF000000) >> 24) / 255.0f;
			}

			return true;
		}
	}

	return false;
}

const char ColorMarkerStart = '{';
const char ColorMarkerEnd = '}';
void TextWithColors(const char* fmt, ...)
{
	char tempStr[4096];

	va_list argPtr;
	va_start(argPtr, fmt);
	_vsnprintf(tempStr, sizeof(tempStr), fmt, argPtr);
	va_end(argPtr);
	tempStr[sizeof(tempStr) - 1] = '\0';

	bool pushedColorStyle = false;
	const char* textStart = tempStr;
	const char* textCur = tempStr;
	while (textCur < (tempStr + sizeof(tempStr)) && *textCur != '\0')
	{
		if (*textCur == ColorMarkerStart)
		{
			// Print accumulated text
			if (textCur != textStart)
			{
				ImGui::TextUnformatted(textStart, textCur);
				ImGui::SameLine(0.0f, 0.0f);
			}

			// Process color code
			const char* colorStart = textCur + 1;
			do
			{
				++textCur;
			} while (*textCur != '\0' && *textCur != ColorMarkerEnd);

			// Change color
			if (pushedColorStyle)
			{
				ImGui::PopStyleColor();
				pushedColorStyle = false;
			}

			ImVec4 textColor;
			if (ProcessInlineHexColor(colorStart, textCur, textColor))
			{
				ImGui::PushStyleColor(ImGuiCol_Text, textColor);
				pushedColorStyle = true;
			}

			textStart = textCur + 1;
		}
		else if (*textCur == '\n')
		{
			// Print accumulated text an go to next line
			ImGui::TextUnformatted(textStart, textCur);
			textStart = textCur + 1;
		}

		++textCur;
	}

	if (textCur != textStart)
	{
		ImGui::TextUnformatted(textStart, textCur);
	}
	else
	{
		ImGui::NewLine();
	}

	if (pushedColorStyle)
	{
		ImGui::PopStyleColor();
	}
}



bool Save_Settings(std::string Path)
{
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) { std::cout << "File not found"; };

	
	// player

	ini.SetDoubleValue("Colors", "FovColor_R", Settings::FovColor.x);
	ini.SetDoubleValue("Colors", "FovColor_G", Settings::FovColor.y);
	ini.SetDoubleValue("Colors", "FovColor_B", Settings::FovColor.z);
	ini.SetDoubleValue("Colors", "FovColor_A", Settings::FovColor.w);

	ini.SetDoubleValue("Colors", "PlayerNameColor_R", Settings::PlayerNameColor.x);
	ini.SetDoubleValue("Colors", "PlayerNameColor_G", Settings::PlayerNameColor.y);
	ini.SetDoubleValue("Colors", "PlayerNameColor_B", Settings::PlayerNameColor.z);
	ini.SetDoubleValue("Colors", "PlayerNameColor_A", Settings::PlayerNameColor.w);

	ini.SetDoubleValue("Colors", "PlayerSkeletonColor_R", Settings::PlayerSkeletonColor.x);
	ini.SetDoubleValue("Colors", "PlayerSkeletonColor_G", Settings::PlayerSkeletonColor.y);
	ini.SetDoubleValue("Colors", "PlayerSkeletonColor_B", Settings::PlayerSkeletonColor.z);
	ini.SetDoubleValue("Colors", "PlayerSkeletonColor_A", Settings::PlayerSkeletonColor.w);

	ini.SetDoubleValue("Colors", "PlayerLineColor_R", Settings::PlayerLineColor.x);
	ini.SetDoubleValue("Colors", "PlayerLineColor_G", Settings::PlayerLineColor.y);
	ini.SetDoubleValue("Colors", "PlayerLineColor_B", Settings::PlayerLineColor.z);
	ini.SetDoubleValue("Colors", "PlayerLineColor_A", Settings::PlayerLineColor.w);

	ini.SetDoubleValue("Colors", "PlayerBoxColor_R", Settings::PlayerBoxColor.x);
	ini.SetDoubleValue("Colors", "PlayerBoxColor_G", Settings::PlayerBoxColor.y);
	ini.SetDoubleValue("Colors", "PlayerBoxColor_B", Settings::PlayerBoxColor.z);
	ini.SetDoubleValue("Colors", "PlayerBoxColor_A", Settings::PlayerBoxColor.w);

	ini.SetDoubleValue("Colors", "PlayerStateColor_R", Settings::PlayerStateColor.x);
	ini.SetDoubleValue("Colors", "PlayerStateColor_G", Settings::PlayerStateColor.y);
	ini.SetDoubleValue("Colors", "PlayerStateColor_B", Settings::PlayerStateColor.z);
	ini.SetDoubleValue("Colors", "PlayerStateColor_A", Settings::PlayerStateColor.w);

	ini.SetDoubleValue("Colors", "VehicleColor_R", Settings::VehicleColor.x);
	ini.SetDoubleValue("Colors", "VehicleColor_G", Settings::VehicleColor.y);
	ini.SetDoubleValue("Colors", "VehicleColor_B", Settings::VehicleColor.z);
	ini.SetDoubleValue("Colors", "VehicleColor_A", Settings::VehicleColor.w);

	//items
	ini.SetDoubleValue("Colors", "AkmColor_R", Settings::AkmColor.x);
	ini.SetDoubleValue("Colors", "AkmColor_G", Settings::AkmColor.y);
	ini.SetDoubleValue("Colors", "AkmColor_B", Settings::AkmColor.z);
	ini.SetDoubleValue("Colors", "AkmColor_A", Settings::AkmColor.w);

	ini.SetDoubleValue("Colors", "M16A4Color_R", Settings::M16A4Color.x);
	ini.SetDoubleValue("Colors", "M16A4Color_G", Settings::M16A4Color.y);
	ini.SetDoubleValue("Colors", "M16A4Color_B", Settings::M16A4Color.z);
	ini.SetDoubleValue("Colors", "M16A4Color_A", Settings::M16A4Color.w);

	ini.SetDoubleValue("Colors", "SCARLColor_R", Settings::SCARLColor.x);
	ini.SetDoubleValue("Colors", "SCARLColor_G", Settings::SCARLColor.y);
	ini.SetDoubleValue("Colors", "SCARLColor_B", Settings::SCARLColor.z);
	ini.SetDoubleValue("Colors", "SCARLColor_A", Settings::SCARLColor.w);

	ini.SetDoubleValue("Colors", "M416Color_R", Settings::M416Color.x);
	ini.SetDoubleValue("Colors", "M416Color_G", Settings::M416Color.y);
	ini.SetDoubleValue("Colors", "M416Color_B", Settings::M416Color.z);
	ini.SetDoubleValue("Colors", "M416Color_A", Settings::M416Color.w);

	ini.SetDoubleValue("Colors", "GROZAColor_R", Settings::GROZAColor.x);
	ini.SetDoubleValue("Colors", "GROZAColor_G", Settings::GROZAColor.y);
	ini.SetDoubleValue("Colors", "GROZAColor_B", Settings::GROZAColor.z);
	ini.SetDoubleValue("Colors", "GROZAColor_A", Settings::GROZAColor.w);

	ini.SetDoubleValue("Colors", "AUGColor_R", Settings::AUGColor.x);
	ini.SetDoubleValue("Colors", "AUGColor_G", Settings::AUGColor.y);
	ini.SetDoubleValue("Colors", "AUGColor_B", Settings::AUGColor.z);
	ini.SetDoubleValue("Colors", "AUGColor_A", Settings::AUGColor.w);

	ini.SetDoubleValue("Colors", "QBZColor_R", Settings::QBZColor.x);
	ini.SetDoubleValue("Colors", "QBZColor_G", Settings::QBZColor.y);
	ini.SetDoubleValue("Colors", "QBZColor_B", Settings::QBZColor.z);
	ini.SetDoubleValue("Colors", "QBZColor_A", Settings::QBZColor.w);

	ini.SetDoubleValue("Colors", "M762Color_R", Settings::M762Color.x);
	ini.SetDoubleValue("Colors", "M762Color_G", Settings::M762Color.y);
	ini.SetDoubleValue("Colors", "M762Color_B", Settings::M762Color.z);
	ini.SetDoubleValue("Colors", "M762Color_A", Settings::M762Color.w);

	ini.SetDoubleValue("Colors", "MK47Color_R", Settings::MK47Color.x);
	ini.SetDoubleValue("Colors", "MK47Color_G", Settings::MK47Color.y);
	ini.SetDoubleValue("Colors", "MK47Color_B", Settings::MK47Color.z);
	ini.SetDoubleValue("Colors", "MK47Color_A", Settings::MK47Color.w);

	ini.SetDoubleValue("Colors", "G36CColor_R", Settings::G36CColor.x);
	ini.SetDoubleValue("Colors", "G36CColor_G", Settings::G36CColor.y);
	ini.SetDoubleValue("Colors", "G36CColor_B", Settings::G36CColor.z);
	ini.SetDoubleValue("Colors", "G36CColor_A", Settings::G36CColor.w);

	ini.SetDoubleValue("Colors", "HONEYColor_R", Settings::HONEYColor.x);
	ini.SetDoubleValue("Colors", "HONEYColor_G", Settings::HONEYColor.y);
	ini.SetDoubleValue("Colors", "HONEYColor_B", Settings::HONEYColor.z);
	ini.SetDoubleValue("Colors", "HONEYColor_A", Settings::HONEYColor.w);


	ini.SetDoubleValue("Colors", "FAMASColor_R", Settings::FAMASColor.x);
	ini.SetDoubleValue("Colors", "FAMASColor_G", Settings::FAMASColor.y);
	ini.SetDoubleValue("Colors", "FAMASColor_B", Settings::FAMASColor.z);
	ini.SetDoubleValue("Colors", "FAMASColor_A", Settings::FAMASColor.w);

	ini.SetDoubleValue("Colors", "KAR98Color_R", Settings::KAR98Color.x);
	ini.SetDoubleValue("Colors", "KAR98Color_G", Settings::KAR98Color.y);
	ini.SetDoubleValue("Colors", "KAR98Color_B", Settings::KAR98Color.z);
	ini.SetDoubleValue("Colors", "KAR98Color_A", Settings::KAR98Color.w);

	ini.SetDoubleValue("Colors", "M24Color_R", Settings::M24Color.x);
	ini.SetDoubleValue("Colors", "M24Color_G", Settings::M24Color.y);
	ini.SetDoubleValue("Colors", "M24Color_B", Settings::M24Color.z);
	ini.SetDoubleValue("Colors", "M24Color_A", Settings::M24Color.w);

	ini.SetDoubleValue("Colors", "AWMColor_R", Settings::AWMColor.x);
	ini.SetDoubleValue("Colors", "AWMColor_G", Settings::AWMColor.y);
	ini.SetDoubleValue("Colors", "AWMColor_B", Settings::AWMColor.z);
	ini.SetDoubleValue("Colors", "AWMColor_A", Settings::AWMColor.w);

	ini.SetDoubleValue("Colors", "WIN94Color_R", Settings::WIN94Color.x);
	ini.SetDoubleValue("Colors", "WIN94Color_G", Settings::WIN94Color.y);
	ini.SetDoubleValue("Colors", "WIN94Color_B", Settings::WIN94Color.z);
	ini.SetDoubleValue("Colors", "WIN94Color_A", Settings::WIN94Color.w);

	ini.SetDoubleValue("Colors", "MOSINColor_R", Settings::MOSINColor.x);
	ini.SetDoubleValue("Colors", "MOSINColor_G", Settings::MOSINColor.y);
	ini.SetDoubleValue("Colors", "MOSINColor_B", Settings::MOSINColor.z);
	ini.SetDoubleValue("Colors", "MOSINColor_A", Settings::MOSINColor.w);

	ini.SetDoubleValue("Colors", "AMRColor_R", Settings::AMRColor.x);
	ini.SetDoubleValue("Colors", "AMRColor_G", Settings::AMRColor.y);
	ini.SetDoubleValue("Colors", "AMRColor_B", Settings::AMRColor.z);
	ini.SetDoubleValue("Colors", "AMRColor_A", Settings::AMRColor.w);

	ini.SetDoubleValue("Colors", "SKSColor_R", Settings::SKSColor.x);
	ini.SetDoubleValue("Colors", "SKSColor_G", Settings::SKSColor.y);
	ini.SetDoubleValue("Colors", "SKSColor_B", Settings::SKSColor.z);
	ini.SetDoubleValue("Colors", "SKSColor_A", Settings::SKSColor.w);

	ini.SetDoubleValue("Colors", "VSSColor_R", Settings::VSSColor.x);
	ini.SetDoubleValue("Colors", "VSSColor_G", Settings::VSSColor.y);
	ini.SetDoubleValue("Colors", "VSSColor_B", Settings::VSSColor.z);
	ini.SetDoubleValue("Colors", "VSSColor_A", Settings::VSSColor.w);

	ini.SetDoubleValue("Colors", "MINI14Color_R", Settings::MINI14Color.x);
	ini.SetDoubleValue("Colors", "MINI14Color_G", Settings::MINI14Color.y);
	ini.SetDoubleValue("Colors", "MINI14Color_B", Settings::MINI14Color.z);
	ini.SetDoubleValue("Colors", "MINI14Color_A", Settings::MINI14Color.w);

	ini.SetDoubleValue("Colors", "MK14Color_R", Settings::MK14Color.x);
	ini.SetDoubleValue("Colors", "MK14Color_G", Settings::MK14Color.y);
	ini.SetDoubleValue("Colors", "MK14Color_B", Settings::MK14Color.z);
	ini.SetDoubleValue("Colors", "MK14Color_A", Settings::MK14Color.w);

	ini.SetDoubleValue("Colors", "SLRColor_R", Settings::SLRColor.x);
	ini.SetDoubleValue("Colors", "SLRColor_G", Settings::SLRColor.y);
	ini.SetDoubleValue("Colors", "SLRColor_B", Settings::SLRColor.z);
	ini.SetDoubleValue("Colors", "SLRColor_A", Settings::SLRColor.w);

	ini.SetDoubleValue("Colors", "QBUColor_R", Settings::QBUColor.x);
	ini.SetDoubleValue("Colors", "QBUColor_G", Settings::QBUColor.y);
	ini.SetDoubleValue("Colors", "QBUColor_B", Settings::QBUColor.z);
	ini.SetDoubleValue("Colors", "QBUColor_A", Settings::QBUColor.w);

	ini.SetDoubleValue("Colors", "MK12Color_R", Settings::MK12Color.x);
	ini.SetDoubleValue("Colors", "MK12Color_G", Settings::MK12Color.y);
	ini.SetDoubleValue("Colors", "MK12Color_B", Settings::MK12Color.z);
	ini.SetDoubleValue("Colors", "MK12Color_A", Settings::MK12Color.w);

	ini.SetDoubleValue("Colors", "UZIColor_R", Settings::UZIColor.x);
	ini.SetDoubleValue("Colors", "UZIColor_G", Settings::UZIColor.y);
	ini.SetDoubleValue("Colors", "UZIColor_B", Settings::UZIColor.z);
	ini.SetDoubleValue("Colors", "UZIColor_A", Settings::UZIColor.w);

	ini.SetDoubleValue("Colors", "UMP45Color_R", Settings::UMP45Color.x);
	ini.SetDoubleValue("Colors", "UMP45Color_G", Settings::UMP45Color.y);
	ini.SetDoubleValue("Colors", "UMP45Color_B", Settings::UMP45Color.z);
	ini.SetDoubleValue("Colors", "UMP45Color_A", Settings::UMP45Color.w);

	ini.SetDoubleValue("Colors", "VECTORColor_R", Settings::VECTORColor.x);
	ini.SetDoubleValue("Colors", "VECTORColor_G", Settings::VECTORColor.y);
	ini.SetDoubleValue("Colors", "VECTORColor_B", Settings::VECTORColor.z);
	ini.SetDoubleValue("Colors", "VECTORColor_A", Settings::VECTORColor.w);

	ini.SetDoubleValue("Colors", "THOMPSONColor_R", Settings::THOMPSONColor.x);
	ini.SetDoubleValue("Colors", "THOMPSONColor_G", Settings::THOMPSONColor.y);
	ini.SetDoubleValue("Colors", "THOMPSONColor_B", Settings::THOMPSONColor.z);
	ini.SetDoubleValue("Colors", "THOMPSONColor_A", Settings::THOMPSONColor.w);

	ini.SetDoubleValue("Colors", "BIZONColor_R", Settings::BIZONColor.x);
	ini.SetDoubleValue("Colors", "BIZONColor_G", Settings::BIZONColor.y);
	ini.SetDoubleValue("Colors", "BIZONColor_B", Settings::BIZONColor.z);
	ini.SetDoubleValue("Colors", "BIZONColor_A", Settings::BIZONColor.w);

	ini.SetDoubleValue("Colors", "MP5KColor_R", Settings::MP5KColor.x);
	ini.SetDoubleValue("Colors", "MP5KColor_G", Settings::MP5KColor.y);
	ini.SetDoubleValue("Colors", "MP5KColor_B", Settings::MP5KColor.z);
	ini.SetDoubleValue("Colors", "MP5KColor_A", Settings::MP5KColor.w);

	ini.SetDoubleValue("Colors", "P90Color_R", Settings::P90Color.x);
	ini.SetDoubleValue("Colors", "P90Color_G", Settings::P90Color.y);
	ini.SetDoubleValue("Colors", "P90Color_B", Settings::P90Color.z);
	ini.SetDoubleValue("Colors", "P90Color_A", Settings::P90Color.w);

	ini.SetDoubleValue("Colors", "S686Color_R", Settings::S686Color.x);
	ini.SetDoubleValue("Colors", "S686Color_G", Settings::S686Color.y);
	ini.SetDoubleValue("Colors", "S686Color_B", Settings::S686Color.z);
	ini.SetDoubleValue("Colors", "S686Color_A", Settings::S686Color.w);

	ini.SetDoubleValue("Colors", "S1897Color_R", Settings::S1897Color.x);
	ini.SetDoubleValue("Colors", "S1897Color_G", Settings::S1897Color.y);
	ini.SetDoubleValue("Colors", "S1897Color_B", Settings::S1897Color.z);
	ini.SetDoubleValue("Colors", "S1897Color_A", Settings::S1897Color.w);

	ini.SetDoubleValue("Colors", "S12KColor_R", Settings::S12KColor.x);
	ini.SetDoubleValue("Colors", "S12KColor_G", Settings::S12KColor.y);
	ini.SetDoubleValue("Colors", "S12KColor_B", Settings::S12KColor.z);
	ini.SetDoubleValue("Colors", "S12KColor_A", Settings::S12KColor.w);

	ini.SetDoubleValue("Colors", "DBSColor_R", Settings::DBSColor.x);
	ini.SetDoubleValue("Colors", "DBSColor_G", Settings::DBSColor.y);
	ini.SetDoubleValue("Colors", "DBSColor_B", Settings::DBSColor.z);
	ini.SetDoubleValue("Colors", "DBSColor_A", Settings::DBSColor.w);

	ini.SetDoubleValue("Colors", "M1014Color_R", Settings::M1014Color.x);
	ini.SetDoubleValue("Colors", "M1014Color_G", Settings::M1014Color.y);
	ini.SetDoubleValue("Colors", "M1014Color_B", Settings::M1014Color.z);
	ini.SetDoubleValue("Colors", "M1014Color_A", Settings::M1014Color.w);

	ini.SetDoubleValue("Colors", "NS2000Color_R", Settings::NS2000Color.x);
	ini.SetDoubleValue("Colors", "NS2000Color_G", Settings::NS2000Color.y);
	ini.SetDoubleValue("Colors", "NS2000Color_B", Settings::NS2000Color.z);
	ini.SetDoubleValue("Colors", "NS2000Color_A", Settings::NS2000Color.w);

	ini.SetDoubleValue("Colors", "M249Color_R", Settings::M249Color.x);
	ini.SetDoubleValue("Colors", "M249Color_G", Settings::M249Color.y);
	ini.SetDoubleValue("Colors", "M249Color_B", Settings::M249Color.z);
	ini.SetDoubleValue("Colors", "M249Color_A", Settings::M249Color.w);

	ini.SetDoubleValue("Colors", "DP28Color_R", Settings::DP28Color.x);
	ini.SetDoubleValue("Colors", "DP28Color_G", Settings::DP28Color.y);
	ini.SetDoubleValue("Colors", "DP28Color_B", Settings::DP28Color.z);
	ini.SetDoubleValue("Colors", "DP28Color_A", Settings::DP28Color.w);

	ini.SetDoubleValue("Colors", "MG3Color_R", Settings::MG3Color.x);
	ini.SetDoubleValue("Colors", "MG3Color_G", Settings::MG3Color.y);
	ini.SetDoubleValue("Colors", "MG3Color_B", Settings::MG3Color.z);
	ini.SetDoubleValue("Colors", "MG3Color_A", Settings::MG3Color.w);

	ini.SetDoubleValue("Colors", "FLAREColor_R", Settings::FLAREColor.x);
	ini.SetDoubleValue("Colors", "FLAREColor_G", Settings::FLAREColor.y);
	ini.SetDoubleValue("Colors", "FLAREColor_B", Settings::FLAREColor.z);
	ini.SetDoubleValue("Colors", "FLAREColor_A", Settings::FLAREColor.w);

	ini.SetDoubleValue("Colors", "FRAGColor_R", Settings::FRAGColor.x);
	ini.SetDoubleValue("Colors", "FRAGColor_G", Settings::FRAGColor.y);
	ini.SetDoubleValue("Colors", "FRAGColor_B", Settings::FRAGColor.z);
	ini.SetDoubleValue("Colors", "FRAGColor_A", Settings::FRAGColor.w);

	ini.SetDoubleValue("Colors", "SMOKEColor_R", Settings::SMOKEColor.x);
	ini.SetDoubleValue("Colors", "SMOKEColor_G", Settings::SMOKEColor.y);
	ini.SetDoubleValue("Colors", "SMOKEColor_B", Settings::SMOKEColor.z);
	ini.SetDoubleValue("Colors", "SMOKEColor_A", Settings::SMOKEColor.w);

	ini.SetDoubleValue("Colors", "MOLOTOFColor_R", Settings::MOLOTOFColor.x);
	ini.SetDoubleValue("Colors", "MOLOTOFColor_G", Settings::MOLOTOFColor.y);
	ini.SetDoubleValue("Colors", "MOLOTOFColor_B", Settings::MOLOTOFColor.z);
	ini.SetDoubleValue("Colors", "MOLOTOFColor_A", Settings::MOLOTOFColor.w);

	ini.SetDoubleValue("Colors", "MedKitColor_R", Settings::MedKitColor.x);
	ini.SetDoubleValue("Colors", "MedKitColor_G", Settings::MedKitColor.y);
	ini.SetDoubleValue("Colors", "MedKitColor_B", Settings::MedKitColor.z);
	ini.SetDoubleValue("Colors", "MedKitColor_A", Settings::MedKitColor.w);

	ini.SetDoubleValue("Colors", "FirstAidKitColor_R", Settings::FirstAidKitColor.x);
	ini.SetDoubleValue("Colors", "FirstAidKitColor_G", Settings::FirstAidKitColor.y);
	ini.SetDoubleValue("Colors", "FirstAidKitColor_B", Settings::FirstAidKitColor.z);
	ini.SetDoubleValue("Colors", "FirstAidKitColor_A", Settings::FirstAidKitColor.w);

	ini.SetDoubleValue("Colors", "PainkillerColor_R", Settings::PainkillerColor.x);
	ini.SetDoubleValue("Colors", "PainkillerColor_G", Settings::PainkillerColor.y);
	ini.SetDoubleValue("Colors", "PainkillerColor_B", Settings::PainkillerColor.z);
	ini.SetDoubleValue("Colors", "PainkillerColor_A", Settings::PainkillerColor.w);

	ini.SetDoubleValue("Colors", "EnergyDrinkColor_R", Settings::EnergyDrinkColor.x);
	ini.SetDoubleValue("Colors", "EnergyDrinkColor_G", Settings::EnergyDrinkColor.y);
	ini.SetDoubleValue("Colors", "EnergyDrinkColor_B", Settings::EnergyDrinkColor.z);
	ini.SetDoubleValue("Colors", "EnergyDrinkColor_A", Settings::EnergyDrinkColor.w);

	ini.SetDoubleValue("Colors", "AdrenalinColor_R", Settings::AdrenalinColor.x);
	ini.SetDoubleValue("Colors", "AdrenalinColor_G", Settings::AdrenalinColor.y);
	ini.SetDoubleValue("Colors", "AdrenalinColor_B", Settings::AdrenalinColor.z);
	ini.SetDoubleValue("Colors", "AdrenalinColor_A", Settings::AdrenalinColor.w);

	ini.SetDoubleValue("Colors", "Bag1Color_R", Settings::Bag1Color.x);
	ini.SetDoubleValue("Colors", "Bag1Color_G", Settings::Bag1Color.y);
	ini.SetDoubleValue("Colors", "Bag1Color_B", Settings::Bag1Color.z);
	ini.SetDoubleValue("Colors", "Bag1Color_A", Settings::Bag1Color.w);

	ini.SetDoubleValue("Colors", "Bag2Color_R", Settings::Bag2Color.x);
	ini.SetDoubleValue("Colors", "Bag2Color_G", Settings::Bag2Color.y);
	ini.SetDoubleValue("Colors", "Bag2Color_B", Settings::Bag2Color.z);
	ini.SetDoubleValue("Colors", "Bag2Color_A", Settings::Bag2Color.w);

	ini.SetDoubleValue("Colors", "Bag3Color_R", Settings::Bag3Color.x);
	ini.SetDoubleValue("Colors", "Bag3Color_G", Settings::Bag3Color.y);
	ini.SetDoubleValue("Colors", "Bag3Color_B", Settings::Bag3Color.z);
	ini.SetDoubleValue("Colors", "Bag3Color_A", Settings::Bag3Color.w);

	ini.SetDoubleValue("Colors", "Helmet1Color_R", Settings::Helmet1Color.x);
	ini.SetDoubleValue("Colors", "Helmet1Color_G", Settings::Helmet1Color.y);
	ini.SetDoubleValue("Colors", "Helmet1Color_B", Settings::Helmet1Color.z);
	ini.SetDoubleValue("Colors", "Helmet1Color_A", Settings::Helmet1Color.w);

	ini.SetDoubleValue("Colors", "Helmet2Color_R", Settings::Helmet2Color.x);
	ini.SetDoubleValue("Colors", "Helmet2Color_G", Settings::Helmet2Color.y);
	ini.SetDoubleValue("Colors", "Helmet2Color_B", Settings::Helmet2Color.z);
	ini.SetDoubleValue("Colors", "Helmet2Color_A", Settings::Helmet2Color.w);

	ini.SetDoubleValue("Colors", "Helmet3Color_R", Settings::Helmet3Color.x);
	ini.SetDoubleValue("Colors", "Helmet3Color_G", Settings::Helmet3Color.y);
	ini.SetDoubleValue("Colors", "Helmet3Color_B", Settings::Helmet3Color.z);
	ini.SetDoubleValue("Colors", "Helmet3Color_A", Settings::Helmet3Color.w);

	ini.SetDoubleValue("Colors", "Armor1Color_R", Settings::Armor1Color.x);
	ini.SetDoubleValue("Colors", "Armor1Color_G", Settings::Armor1Color.y);
	ini.SetDoubleValue("Colors", "Armor1Color_B", Settings::Armor1Color.z);
	ini.SetDoubleValue("Colors", "Armor1Color_A", Settings::Armor1Color.w);

	ini.SetDoubleValue("Colors", "Armor2Color_R", Settings::Armor2Color.x);
	ini.SetDoubleValue("Colors", "Armor2Color_G", Settings::Armor2Color.y);
	ini.SetDoubleValue("Colors", "Armor2Color_B", Settings::Armor2Color.z);
	ini.SetDoubleValue("Colors", "Armor2Color_A", Settings::Armor2Color.w);

	ini.SetDoubleValue("Colors", "Armor3Color_R", Settings::Armor3Color.x);
	ini.SetDoubleValue("Colors", "Armor3Color_G", Settings::Armor3Color.y);
	ini.SetDoubleValue("Colors", "Armor3Color_B", Settings::Armor3Color.z);
	ini.SetDoubleValue("Colors", "Armor3Color_A", Settings::Armor3Color.w);

	ini.SetDoubleValue("Colors", "a762mmColor_R", Settings::a762mmColor.x);
	ini.SetDoubleValue("Colors", "a762mmColor_G", Settings::a762mmColor.y);
	ini.SetDoubleValue("Colors", "a762mmColor_B", Settings::a762mmColor.z);
	ini.SetDoubleValue("Colors", "a762mmColor_A", Settings::a762mmColor.w);

	ini.SetDoubleValue("Colors", "a556mmColor_R", Settings::a556mmColor.x);
	ini.SetDoubleValue("Colors", "a556mmColor_G", Settings::a556mmColor.y);
	ini.SetDoubleValue("Colors", "a556mmColor_B", Settings::a556mmColor.z);
	ini.SetDoubleValue("Colors", "a556mmColor_A", Settings::a556mmColor.w);

	ini.SetDoubleValue("Colors", "a9mmColor_R", Settings::a9mmColor.x);
	ini.SetDoubleValue("Colors", "a9mmColor_G", Settings::a9mmColor.y);
	ini.SetDoubleValue("Colors", "a9mmColor_B", Settings::a9mmColor.z);
	ini.SetDoubleValue("Colors", "a9mmColor_A", Settings::a9mmColor.w);

	ini.SetDoubleValue("Colors", "a45ACPColor_R", Settings::a45ACPColor.x);
	ini.SetDoubleValue("Colors", "a45ACPColor_G", Settings::a45ACPColor.y);
	ini.SetDoubleValue("Colors", "a45ACPColor_B", Settings::a45ACPColor.z);
	ini.SetDoubleValue("Colors", "a45ACPColor_A", Settings::a45ACPColor.w);

	ini.SetDoubleValue("Colors", "a12GauegeColor_R", Settings::a12GauegeColor.x);
	ini.SetDoubleValue("Colors", "a12GauegeColor_G", Settings::a12GauegeColor.y);
	ini.SetDoubleValue("Colors", "a12GauegeColor_B", Settings::a12GauegeColor.z);
	ini.SetDoubleValue("Colors", "a12GauegeColor_A", Settings::a12GauegeColor.w);

	ini.SetDoubleValue("Colors", "AwmAmmoColor_R", Settings::AwmAmmoColor.x);
	ini.SetDoubleValue("Colors", "AwmAmmoColor_G", Settings::AwmAmmoColor.y);
	ini.SetDoubleValue("Colors", "AwmAmmoColor_B", Settings::AwmAmmoColor.z);
	ini.SetDoubleValue("Colors", "AwmAmmoColor_A", Settings::AwmAmmoColor.w);

	ini.SetDoubleValue("Colors", "AmrAmmoColor_R", Settings::AmrAmmoColor.x);
	ini.SetDoubleValue("Colors", "AmrAmmoColor_G", Settings::AmrAmmoColor.y);
	ini.SetDoubleValue("Colors", "AmrAmmoColor_B", Settings::AmrAmmoColor.z);
	ini.SetDoubleValue("Colors", "AmrAmmoColor_A", Settings::AmrAmmoColor.w);

	ini.SetDoubleValue("Colors", "Scope_x2Color_R", Settings::Scope_x2Color.x);
	ini.SetDoubleValue("Colors", "Scope_x2Color_G", Settings::Scope_x2Color.y);
	ini.SetDoubleValue("Colors", "Scope_x2Color_B", Settings::Scope_x2Color.z);
	ini.SetDoubleValue("Colors", "Scope_x2Color_A", Settings::Scope_x2Color.w);

	ini.SetDoubleValue("Colors", "Scope_x3Color_R", Settings::Scope_x3Color.x);
	ini.SetDoubleValue("Colors", "Scope_x3Color_G", Settings::Scope_x3Color.y);
	ini.SetDoubleValue("Colors", "Scope_x3Color_B", Settings::Scope_x3Color.z);
	ini.SetDoubleValue("Colors", "Scope_x3Color_A", Settings::Scope_x3Color.w);

	ini.SetDoubleValue("Colors", "Scope_x4Color_R", Settings::Scope_x4Color.x);
	ini.SetDoubleValue("Colors", "Scope_x4Color_G", Settings::Scope_x4Color.y);
	ini.SetDoubleValue("Colors", "Scope_x4Color_B", Settings::Scope_x4Color.z);
	ini.SetDoubleValue("Colors", "Scope_x4Color_A", Settings::Scope_x4Color.w);

	ini.SetDoubleValue("Colors", "Scope_x6Color_R", Settings::Scope_x6Color.x);
	ini.SetDoubleValue("Colors", "Scope_x6Color_G", Settings::Scope_x6Color.y);
	ini.SetDoubleValue("Colors", "Scope_x6Color_B", Settings::Scope_x6Color.z);
	ini.SetDoubleValue("Colors", "Scope_x6Color_A", Settings::Scope_x6Color.w);

	ini.SetDoubleValue("Colors", "Scope_x8Color_R", Settings::Scope_x8Color.x);
	ini.SetDoubleValue("Colors", "Scope_x8Color_G", Settings::Scope_x8Color.y);
	ini.SetDoubleValue("Colors", "Scope_x8Color_B", Settings::Scope_x8Color.z);
	ini.SetDoubleValue("Colors", "Scope_x8Color_A", Settings::Scope_x8Color.w);

	ini.SetDoubleValue("Colors", "ExtendedMacColor_R", Settings::ExtendedMacColor.x);
	ini.SetDoubleValue("Colors", "ExtendedMacColor_G", Settings::ExtendedMacColor.y);
	ini.SetDoubleValue("Colors", "ExtendedMacColor_B", Settings::ExtendedMacColor.z);
	ini.SetDoubleValue("Colors", "ExtendedMacColor_A", Settings::ExtendedMacColor.w);

	ini.SetDoubleValue("Colors", "SupressorColor_R", Settings::SupressorColor.x);
	ini.SetDoubleValue("Colors", "SupressorColor_G", Settings::SupressorColor.y);
	ini.SetDoubleValue("Colors", "SupressorColor_B", Settings::SupressorColor.z);
	ini.SetDoubleValue("Colors", "SupressorColor_A", Settings::SupressorColor.w);

	ini.SetDoubleValue("Colors", "visColor_R", Settings::visColor.x);
	ini.SetDoubleValue("Colors", "visColor_G", Settings::visColor.y);
	ini.SetDoubleValue("Colors", "visColor_B", Settings::visColor.z);
	ini.SetDoubleValue("Colors", "visColor_A", Settings::visColor.w);

	ini.SetDoubleValue("Floats", "fovcircleredus", Settings::fovcircleredus);
	ini.SetDoubleValue("Floats", "AimSpeed", Settings::AimSpeed);
	ini.SetDoubleValue("Floats", "RepidFireValue", Settings::RepidFireValue);
	ini.SetDoubleValue("Floats", "percentage", Settings::percentage);
	ini.SetDoubleValue("Floats", "linethickness", Settings::linethickness);
	ini.SetDoubleValue("Floats", "skeletonthickness", Settings::skeletonthickness);

	ini.SetLongValue("Ints", "currentBoneIndex", Settings::currentBoneIndex);
	ini.SetLongValue("Ints", "weight", Settings::weight);
	ini.SetBoolValue("Bools", "isPrioritySet", Settings::isPrioritySet ? true : false);

	ini.SetLongValue("Ints", "IpadValue", Settings::IpadValue);
	ini.SetLongValue("Ints", "InstantValue", Settings::InstantValue);
	ini.SetLongValue("Ints", "UpdateTick", Settings::UpdateTick);
	ini.SetLongValue("Ints", "UpdateFps", Settings::UpdateFps);
	ini.SetLongValue("Ints", "PlayerNameSize", Settings::PlayerNameSize);
	ini.SetLongValue("Ints", "PlayerStateSize", Settings::PlayerStateSize);
	ini.SetLongValue("Ints", "VehicleSize", Settings::VehicleSize);
	ini.SetLongValue("Ints", "RadarSize", Settings::RadarSize);
	ini.SetLongValue("Ints", "DotsSize", Settings::DotsSize);
	ini.SetLongValue("Ints", "PlayerSkeletonMode", Settings::PlayerSkeletonMode);
	ini.SetLongValue("Ints", "PlayerLineMode", Settings::PlayerLineMode);
	ini.SetLongValue("Ints", "MaxAimDistence", Settings::MaxAimDistence);
	ini.SetLongValue("Ints", "AimKey", Settings::AimKey);
	ini.SetLongValue("Ints", "macro", Settings::macroval);
	ini.SetLongValue("Ints", "carsexkey", Settings::carsexkey);

	ini.SetLongValue("Ints", "curraim", Settings::curraim);
	ini.SetLongValue("Ints", "prediction", Settings::prediction);

	ini.SetLongValue("Ints", "aimbotmode", Settings::aimbotmode);
	ini.SetLongValue("Ints", "bulletrackMode", Settings::bulletrackMode);
	ini.SetBoolValue("Bools", "visbulletcheck", Settings::visbulletcheck ? true : false);

	ini.SetBoolValue("Bools", "crosshair", Settings::crosshair ? true : false);
	ini.SetBoolValue("Bools", "BypassFovLimit", Settings::BypassFovLimit ? true : false);
	ini.SetBoolValue("Bools", "visibilitycheck", Settings::visibilitycheck? true : false);
	ini.SetBoolValue("Bools", "sendscreenshot", Settings::sendscreenshot ? true : false);
	ini.SetBoolValue("Bools", "grenadePath", Settings::grenadePath ? true : false);
	ini.SetBoolValue("Bools", "SkipBots", Settings::SkipBots ? true : false);
	ini.SetBoolValue("Bools", "knocked", Settings::knocked ? true : false);
	ini.SetBoolValue("Bools", "AimBot", Settings::AimBot ? true : false);
	ini.SetBoolValue("Bools", "Legitrack", Settings::Legitrack ? true : false);
	ini.SetBoolValue("Bools", "MagicBullet", Settings::MagicBullet ? true : false);
	ini.SetBoolValue("Bools", "Fovbased", Settings::Fovbased ? true : false);
	ini.SetBoolValue("Bools", "peekdetect", Settings::peekdetect ? true : false);
	ini.SetBoolValue("Bools", "FovShow", Settings::FovShow ? true : false);
	ini.SetBoolValue("Bools", "AntiStream", Settings::AntiStream ? true : false);
	ini.SetBoolValue("Bools", "IpadView", Settings::IpadView ? true : false);
	ini.SetBoolValue("Bools", "NoRecoil", Settings::NoRecoil ? true : false);
	ini.SetBoolValue("Bools", "ForceTpp", Settings::ForceTpp ? true : false);
	ini.SetBoolValue("Bools", "Xeffect", Settings::Xeffect ? true : false);
	ini.SetBoolValue("Bools", "InstantHit", Settings::InstantHit ? true : false);
	ini.SetBoolValue("Bools", "NoSpread", Settings::NoSpread ? true : false);
	ini.SetBoolValue("Bools", "FastSwitch", Settings::FastSwitch ? true : false);
	ini.SetBoolValue("Bools", "RepidFire", Settings::RepidFire ? true : false);
	ini.SetBoolValue("Bools", "YourInfo", Settings::YourInfo ? true : false);
	ini.SetBoolValue("Bools", "GameInfo", Settings::GameInfo ? true : false);
	ini.SetBoolValue("Bools", "PlayerName", Settings::PlayerName ? true : false);
	ini.SetBoolValue("Bools", "PlayerSkeleton", Settings::PlayerSkeleton ? true : false);
	ini.SetBoolValue("Bools", "PlayerLine", Settings::PlayerLine ? true : false);
	ini.SetBoolValue("Bools", "PlayerDistance", Settings::PlayerDistance ? true : false);
	ini.SetBoolValue("Bools", "PlayerHealth", Settings::PlayerHealth ? true : false);
	ini.SetBoolValue("Bools", "PlayerWeapon", Settings::PlayerWeapon ? true : false);
	ini.SetBoolValue("Bools", "PlayerFlag", Settings::PlayerFlag ? true : false);
	ini.SetBoolValue("Bools", "PlayerBox", Settings::PlayerBox ? true : false);
	ini.SetBoolValue("Bools", "PlayerState", Settings::PlayerState ? true : false);
	ini.SetBoolValue("Bools", "Items", Settings::Items ? true : false);
	ini.SetBoolValue("Bools", "TotalEnemy", Settings::TotalEnemy ? true : false);
	ini.SetBoolValue("Bools", "Vehicle", Settings::Vehicle ? true : false);
	ini.SetBoolValue("Bools", "Lootbox", Settings::Lootbox ? true : false);
	ini.SetBoolValue("Bools", "LootboxItems", Settings::LootboxItems ? true : false);
	ini.SetBoolValue("Bools", "AirDrop", Settings::AirDrop ? true : false);
	ini.SetBoolValue("Bools", "AirDropItems", Settings::AirDropItems ? true : false);
	ini.SetBoolValue("Bools", "GrandeWarning", Settings::GrandeWarning ? true : false);
	ini.SetBoolValue("Bools", "AimWarning", Settings::AimWarning ? true : false);
	ini.SetBoolValue("Bools", "carsex", Settings::carsex ? true : false);

	ini.SetBoolValue("Bools", "Redzone", Settings::Redzone ? true : false);
	ini.SetBoolValue("Bools", "Dots", Settings::Dots ? true : false);
	ini.SetBoolValue("Bools", "Radar", Settings::Radar ? true : false);
	ini.SetBoolValue("Bools", "Akm", Settings::Akm ? true : false);
	ini.SetBoolValue("Bools", "M16A4", Settings::M16A4 ? true : false);
	ini.SetBoolValue("Bools", "SCARL", Settings::SCARL ? true : false);
	ini.SetBoolValue("Bools", "M416", Settings::M416 ? true : false);
	ini.SetBoolValue("Bools", "GROZA", Settings::GROZA ? true : false);
	ini.SetBoolValue("Bools", "AUG", Settings::AUG ? true : false);
	ini.SetBoolValue("Bools", "QBZ", Settings::QBZ ? true : false);
	ini.SetBoolValue("Bools", "M762", Settings::M762 ? true : false);
	ini.SetBoolValue("Bools", "MK47", Settings::MK47 ? true : false);
	ini.SetBoolValue("Bools", "G36C", Settings::G36C ? true : false);
	ini.SetBoolValue("Bools", "HONEY", Settings::HONEY ? true : false);
	ini.SetBoolValue("Bools", "FAMAS", Settings::FAMAS ? true : false);
	ini.SetBoolValue("Bools", "KAR98", Settings::KAR98 ? true : false);
	ini.SetBoolValue("Bools", "M24", Settings::M24 ? true : false);
	ini.SetBoolValue("Bools", "AWM", Settings::AWM ? true : false);
	ini.SetBoolValue("Bools", "WIN94", Settings::WIN94 ? true : false);
	ini.SetBoolValue("Bools", "MOSIN", Settings::MOSIN ? true : false);
	ini.SetBoolValue("Bools", "AMR", Settings::AMR ? true : false);
	ini.SetBoolValue("Bools", "SKS", Settings::SKS ? true : false);
	ini.SetBoolValue("Bools", "VSS", Settings::VSS ? true : false);
	ini.SetBoolValue("Bools", "MINI14", Settings::MINI14 ? true : false);
	ini.SetBoolValue("Bools", "MK14", Settings::MK14 ? true : false);
	ini.SetBoolValue("Bools", "SLR", Settings::SLR ? true : false);
	ini.SetBoolValue("Bools", "QBU", Settings::QBU ? true : false);
	ini.SetBoolValue("Bools", "MK12", Settings::MK12 ? true : false);
	ini.SetBoolValue("Bools", "UZI", Settings::UZI ? true : false);
	ini.SetBoolValue("Bools", "UMP45", Settings::UMP45 ? true : false);
	ini.SetBoolValue("Bools", "VECTOR", Settings::VECTOR ? true : false);
	ini.SetBoolValue("Bools", "THOMPSON", Settings::THOMPSON ? true : false);
	ini.SetBoolValue("Bools", "BIZON", Settings::BIZON ? true : false);
	ini.SetBoolValue("Bools", "MP5K", Settings::MP5K ? true : false);
	ini.SetBoolValue("Bools", "P90", Settings::P90 ? true : false);
	ini.SetBoolValue("Bools", "S686", Settings::S686 ? true : false);
	ini.SetBoolValue("Bools", "S1897", Settings::S1897 ? true : false);
	ini.SetBoolValue("Bools", "S12K", Settings::S12K ? true : false);
	ini.SetBoolValue("Bools", "DBS", Settings::DBS ? true : false);
	ini.SetBoolValue("Bools", "M1014", Settings::M1014 ? true : false);
	ini.SetBoolValue("Bools", "NS2000", Settings::NS2000 ? true : false);
	ini.SetBoolValue("Bools", "M249", Settings::M249 ? true : false);
	ini.SetBoolValue("Bools", "DP28", Settings::DP28 ? true : false);
	ini.SetBoolValue("Bools", "MG3", Settings::MG3 ? true : false);
	ini.SetBoolValue("Bools", "FLARE", Settings::FLARE ? true : false);
	ini.SetBoolValue("Bools", "FRAG", Settings::FRAG ? true : false);
	ini.SetBoolValue("Bools", "SMOKE", Settings::SMOKE ? true : false);
	ini.SetBoolValue("Bools", "MOLOTOF", Settings::MOLOTOF ? true : false);
	ini.SetBoolValue("Bools", "MedKit", Settings::MedKit ? true : false);
	ini.SetBoolValue("Bools", "FirstAidKit", Settings::FirstAidKit ? true : false);
	ini.SetBoolValue("Bools", "Painkiller", Settings::Painkiller ? true : false);
	ini.SetBoolValue("Bools", "EnergyDrink", Settings::EnergyDrink ? true : false);
	ini.SetBoolValue("Bools", "Adrenalin", Settings::Adrenalin ? true : false);
	ini.SetBoolValue("Bools", "Bag1", Settings::Bag1 ? true : false);
	ini.SetBoolValue("Bools", "Bag2", Settings::Bag2 ? true : false);
	ini.SetBoolValue("Bools", "Bag3", Settings::Bag3 ? true : false);
	ini.SetBoolValue("Bools", "Helmet1", Settings::Helmet1 ? true : false);
	ini.SetBoolValue("Bools", "Helmet2", Settings::Helmet2 ? true : false);
	ini.SetBoolValue("Bools", "Helmet3", Settings::Helmet3 ? true : false);
	ini.SetBoolValue("Bools", "Armor1", Settings::Armor1 ? true : false);
	ini.SetBoolValue("Bools", "Armor2", Settings::Armor2 ? true : false);
	ini.SetBoolValue("Bools", "Armor3", Settings::Armor3 ? true : false);
	ini.SetBoolValue("Bools", "a762mm", Settings::a762mm ? true : false);
	ini.SetBoolValue("Bools", "a556mm", Settings::a556mm ? true : false);
	ini.SetBoolValue("Bools", "a9mm", Settings::a9mm ? true : false);
	ini.SetBoolValue("Bools", "a45ACP", Settings::a45ACP ? true : false);
	ini.SetBoolValue("Bools", "a12Gauege", Settings::a12Gauege ? true : false);
	ini.SetBoolValue("Bools", "AwmAmmo", Settings::AwmAmmo ? true : false);
	ini.SetBoolValue("Bools", "AmrAmmo", Settings::AmrAmmo ? true : false);
	ini.SetBoolValue("Bools", "Scope_x2", Settings::Scope_x2 ? true : false);
	ini.SetBoolValue("Bools", "Scope_x3", Settings::Scope_x3 ? true : false);
	ini.SetBoolValue("Bools", "Scope_x4", Settings::Scope_x4 ? true : false);
	ini.SetBoolValue("Bools", "Scope_x6", Settings::Scope_x6 ? true : false);
	ini.SetBoolValue("Bools", "Scope_x8", Settings::Scope_x8 ? true : false);
	ini.SetBoolValue("Bools", "ShopToken", Settings::ShopToken ? true : false);
	ini.SetBoolValue("Bools", "ExtendedMac", Settings::ExtendedMac ? true : false);
	ini.SetBoolValue("Bools", "Supressor", Settings::Supressor ? true : false);
	if (ini.SaveFile(Path.c_str()) < 0)
	{
		return false;
	}
	return true;
}
void Load_Settings(std::string Path) {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) { std::cout << "File not found"; };


	// FovColor
	Settings::FovColor.x = ini.GetDoubleValue("Colors", "FovColor_R", Settings::FovColor.x);
	Settings::FovColor.y = ini.GetDoubleValue("Colors", "FovColor_G", Settings::FovColor.y);
	Settings::FovColor.z = ini.GetDoubleValue("Colors", "FovColor_B", Settings::FovColor.z);
	Settings::FovColor.w = ini.GetDoubleValue("Colors", "FovColor_A", Settings::FovColor.w);

	// PlayerNameColor
	Settings::PlayerNameColor.x = ini.GetDoubleValue("Colors", "PlayerNameColor_R", Settings::PlayerNameColor.x);
	Settings::PlayerNameColor.y = ini.GetDoubleValue("Colors", "PlayerNameColor_G", Settings::PlayerNameColor.y);
	Settings::PlayerNameColor.z = ini.GetDoubleValue("Colors", "PlayerNameColor_B", Settings::PlayerNameColor.z);
	Settings::PlayerNameColor.w = ini.GetDoubleValue("Colors", "PlayerNameColor_A", Settings::PlayerNameColor.w);

	// PlayerSkeletonColor
	Settings::PlayerSkeletonColor.x = ini.GetDoubleValue("Colors", "PlayerSkeletonColor_R", Settings::PlayerSkeletonColor.x);
	Settings::PlayerSkeletonColor.y = ini.GetDoubleValue("Colors", "PlayerSkeletonColor_G", Settings::PlayerSkeletonColor.y);
	Settings::PlayerSkeletonColor.z = ini.GetDoubleValue("Colors", "PlayerSkeletonColor_B", Settings::PlayerSkeletonColor.z);
	Settings::PlayerSkeletonColor.w = ini.GetDoubleValue("Colors", "PlayerSkeletonColor_A", Settings::PlayerSkeletonColor.w);

	// PlayerLineColor
	Settings::PlayerLineColor.x = ini.GetDoubleValue("Colors", "PlayerLineColor_R", Settings::PlayerLineColor.x);
	Settings::PlayerLineColor.y = ini.GetDoubleValue("Colors", "PlayerLineColor_G", Settings::PlayerLineColor.y);
	Settings::PlayerLineColor.z = ini.GetDoubleValue("Colors", "PlayerLineColor_B", Settings::PlayerLineColor.z);
	Settings::PlayerLineColor.w = ini.GetDoubleValue("Colors", "PlayerLineColor_A", Settings::PlayerLineColor.w);

	// PlayerBoxColor
	Settings::PlayerBoxColor.x = ini.GetDoubleValue("Colors", "PlayerBoxColor_R", Settings::PlayerBoxColor.x);
	Settings::PlayerBoxColor.y = ini.GetDoubleValue("Colors", "PlayerBoxColor_G", Settings::PlayerBoxColor.y);
	Settings::PlayerBoxColor.z = ini.GetDoubleValue("Colors", "PlayerBoxColor_B", Settings::PlayerBoxColor.z);
	Settings::PlayerBoxColor.w = ini.GetDoubleValue("Colors", "PlayerBoxColor_A", Settings::PlayerBoxColor.w);

	// PlayerStateColor
	Settings::PlayerStateColor.x = ini.GetDoubleValue("Colors", "PlayerStateColor_R", Settings::PlayerStateColor.x);
	Settings::PlayerStateColor.y = ini.GetDoubleValue("Colors", "PlayerStateColor_G", Settings::PlayerStateColor.y);
	Settings::PlayerStateColor.z = ini.GetDoubleValue("Colors", "PlayerStateColor_B", Settings::PlayerStateColor.z);
	Settings::PlayerStateColor.w = ini.GetDoubleValue("Colors", "PlayerStateColor_A", Settings::PlayerStateColor.w);

	// VehicleColor
	Settings::VehicleColor.x = ini.GetDoubleValue("Colors", "VehicleColor_R", Settings::VehicleColor.x);
	Settings::VehicleColor.y = ini.GetDoubleValue("Colors", "VehicleColor_G", Settings::VehicleColor.y);
	Settings::VehicleColor.z = ini.GetDoubleValue("Colors", "VehicleColor_B", Settings::VehicleColor.z);
	Settings::VehicleColor.w = ini.GetDoubleValue("Colors", "VehicleColor_A", Settings::VehicleColor.w);

	// Read from INI file and assign values to Settings variables

	// AkmColor
	Settings::AkmColor.x = ini.GetDoubleValue("Colors", "AkmColor_R", Settings::AkmColor.x);
	Settings::AkmColor.y = ini.GetDoubleValue("Colors", "AkmColor_G", Settings::AkmColor.y);
	Settings::AkmColor.z = ini.GetDoubleValue("Colors", "AkmColor_B", Settings::AkmColor.z);
	Settings::AkmColor.w = ini.GetDoubleValue("Colors", "AkmColor_A", Settings::AkmColor.w);

	// M16A4Color
	Settings::M16A4Color.x = ini.GetDoubleValue("Colors", "M16A4Color_R", Settings::M16A4Color.x);
	Settings::M16A4Color.y = ini.GetDoubleValue("Colors", "M16A4Color_G", Settings::M16A4Color.y);
	Settings::M16A4Color.z = ini.GetDoubleValue("Colors", "M16A4Color_B", Settings::M16A4Color.z);
	Settings::M16A4Color.w = ini.GetDoubleValue("Colors", "M16A4Color_A", Settings::M16A4Color.w);

	// SCARLColor
	Settings::SCARLColor.x = ini.GetDoubleValue("Colors", "SCARLColor_R", Settings::SCARLColor.x);
	Settings::SCARLColor.y = ini.GetDoubleValue("Colors", "SCARLColor_G", Settings::SCARLColor.y);
	Settings::SCARLColor.z = ini.GetDoubleValue("Colors", "SCARLColor_B", Settings::SCARLColor.z);
	Settings::SCARLColor.w = ini.GetDoubleValue("Colors", "SCARLColor_A", Settings::SCARLColor.w);

	// M416Color
	Settings::M416Color.x = ini.GetDoubleValue("Colors", "M416Color_R", Settings::M416Color.x);
	Settings::M416Color.y = ini.GetDoubleValue("Colors", "M416Color_G", Settings::M416Color.y);
	Settings::M416Color.z = ini.GetDoubleValue("Colors", "M416Color_B", Settings::M416Color.z);
	Settings::M416Color.w = ini.GetDoubleValue("Colors", "M416Color_A", Settings::M416Color.w);

	// GROZAColor
	Settings::GROZAColor.x = ini.GetDoubleValue("Colors", "GROZAColor_R", Settings::GROZAColor.x);
	Settings::GROZAColor.y = ini.GetDoubleValue("Colors", "GROZAColor_G", Settings::GROZAColor.y);
	Settings::GROZAColor.z = ini.GetDoubleValue("Colors", "GROZAColor_B", Settings::GROZAColor.z);
	Settings::GROZAColor.w = ini.GetDoubleValue("Colors", "GROZAColor_A", Settings::GROZAColor.w);

	// AUGColor
	Settings::AUGColor.x = ini.GetDoubleValue("Colors", "AUGColor_R", Settings::AUGColor.x);
	Settings::AUGColor.y = ini.GetDoubleValue("Colors", "AUGColor_G", Settings::AUGColor.y);
	Settings::AUGColor.z = ini.GetDoubleValue("Colors", "AUGColor_B", Settings::AUGColor.z);
	Settings::AUGColor.w = ini.GetDoubleValue("Colors", "AUGColor_A", Settings::AUGColor.w);

	// QBZColor
	Settings::QBZColor.x = ini.GetDoubleValue("Colors", "QBZColor_R", Settings::QBZColor.x);
	Settings::QBZColor.y = ini.GetDoubleValue("Colors", "QBZColor_G", Settings::QBZColor.y);
	Settings::QBZColor.z = ini.GetDoubleValue("Colors", "QBZColor_B", Settings::QBZColor.z);
	Settings::QBZColor.w = ini.GetDoubleValue("Colors", "QBZColor_A", Settings::QBZColor.w);

	// M762Color
	Settings::M762Color.x = ini.GetDoubleValue("Colors", "M762Color_R", Settings::M762Color.x);
	Settings::M762Color.y = ini.GetDoubleValue("Colors", "M762Color_G", Settings::M762Color.y);
	Settings::M762Color.z = ini.GetDoubleValue("Colors", "M762Color_B", Settings::M762Color.z);
	Settings::M762Color.w = ini.GetDoubleValue("Colors", "M762Color_A", Settings::M762Color.w);

	// MK47Color
	Settings::MK47Color.x = ini.GetDoubleValue("Colors", "MK47Color_R", Settings::MK47Color.x);
	Settings::MK47Color.y = ini.GetDoubleValue("Colors", "MK47Color_G", Settings::MK47Color.y);
	Settings::MK47Color.z = ini.GetDoubleValue("Colors", "MK47Color_B", Settings::MK47Color.z);
	Settings::MK47Color.w = ini.GetDoubleValue("Colors", "MK47Color_A", Settings::MK47Color.w);

	// G36CColor
	Settings::G36CColor.x = ini.GetDoubleValue("Colors", "G36CColor_R", Settings::G36CColor.x);
	Settings::G36CColor.y = ini.GetDoubleValue("Colors", "G36CColor_G", Settings::G36CColor.y);
	Settings::G36CColor.z = ini.GetDoubleValue("Colors", "G36CColor_B", Settings::G36CColor.z);
	Settings::G36CColor.w = ini.GetDoubleValue("Colors", "G36CColor_A", Settings::G36CColor.w);

	// HONEYColor
	Settings::HONEYColor.x = ini.GetDoubleValue("Colors", "HONEYColor_R", Settings::HONEYColor.x);
	Settings::HONEYColor.y = ini.GetDoubleValue("Colors", "HONEYColor_G", Settings::HONEYColor.y);
	Settings::HONEYColor.z = ini.GetDoubleValue("Colors", "HONEYColor_B", Settings::HONEYColor.z);
	Settings::HONEYColor.w = ini.GetDoubleValue("Colors", "HONEYColor_A", Settings::HONEYColor.w);


	// Example for M24Color
	Settings::M24Color.x = ini.GetDoubleValue("Colors", "M24Color_R", Settings::M24Color.x);
	Settings::M24Color.y = ini.GetDoubleValue("Colors", "M24Color_G", Settings::M24Color.y);
	Settings::M24Color.z = ini.GetDoubleValue("Colors", "M24Color_B", Settings::M24Color.z);
	Settings::M24Color.w = ini.GetDoubleValue("Colors", "M24Color_A", Settings::M24Color.w);

	// Example for AWMColor
	Settings::AWMColor.x = ini.GetDoubleValue("Colors", "AWMColor_R", Settings::AWMColor.x);
	Settings::AWMColor.y = ini.GetDoubleValue("Colors", "AWMColor_G", Settings::AWMColor.y);
	Settings::AWMColor.z = ini.GetDoubleValue("Colors", "AWMColor_B", Settings::AWMColor.z);
	Settings::AWMColor.w = ini.GetDoubleValue("Colors", "AWMColor_A", Settings::AWMColor.w);

	// Example for WIN94Color
	Settings::WIN94Color.x = ini.GetDoubleValue("Colors", "WIN94Color_R", Settings::WIN94Color.x);
	Settings::WIN94Color.y = ini.GetDoubleValue("Colors", "WIN94Color_G", Settings::WIN94Color.y);
	Settings::WIN94Color.z = ini.GetDoubleValue("Colors", "WIN94Color_B", Settings::WIN94Color.z);
	Settings::WIN94Color.w = ini.GetDoubleValue("Colors", "WIN94Color_A", Settings::WIN94Color.w);

	// Example for MOSINColor
	Settings::MOSINColor.x = ini.GetDoubleValue("Colors", "MOSINColor_R", Settings::MOSINColor.x);
	Settings::MOSINColor.y = ini.GetDoubleValue("Colors", "MOSINColor_G", Settings::MOSINColor.y);
	Settings::MOSINColor.z = ini.GetDoubleValue("Colors", "MOSINColor_B", Settings::MOSINColor.z);
	Settings::MOSINColor.w = ini.GetDoubleValue("Colors", "MOSINColor_A", Settings::MOSINColor.w);

	// Example for AMRColor
	Settings::AMRColor.x = ini.GetDoubleValue("Colors", "AMRColor_R", Settings::AMRColor.x);
	Settings::AMRColor.y = ini.GetDoubleValue("Colors", "AMRColor_G", Settings::AMRColor.y);
	Settings::AMRColor.z = ini.GetDoubleValue("Colors", "AMRColor_B", Settings::AMRColor.z);
	Settings::AMRColor.w = ini.GetDoubleValue("Colors", "AMRColor_A", Settings::AMRColor.w);

	// Example for SKSColor
	Settings::SKSColor.x = ini.GetDoubleValue("Colors", "SKSColor_R", Settings::SKSColor.x);
	Settings::SKSColor.y = ini.GetDoubleValue("Colors", "SKSColor_G", Settings::SKSColor.y);
	Settings::SKSColor.z = ini.GetDoubleValue("Colors", "SKSColor_B", Settings::SKSColor.z);
	Settings::SKSColor.w = ini.GetDoubleValue("Colors", "SKSColor_A", Settings::SKSColor.w);

	// Example for VSSColor
	Settings::VSSColor.x = ini.GetDoubleValue("Colors", "VSSColor_R", Settings::VSSColor.x);
	Settings::VSSColor.y = ini.GetDoubleValue("Colors", "VSSColor_G", Settings::VSSColor.y);
	Settings::VSSColor.z = ini.GetDoubleValue("Colors", "VSSColor_B", Settings::VSSColor.z);
	Settings::VSSColor.w = ini.GetDoubleValue("Colors", "VSSColor_A", Settings::VSSColor.w);

	// Example for MINI14Color
	Settings::MINI14Color.x = ini.GetDoubleValue("Colors", "MINI14Color_R", Settings::MINI14Color.x);
	Settings::MINI14Color.y = ini.GetDoubleValue("Colors", "MINI14Color_G", Settings::MINI14Color.y);
	Settings::MINI14Color.z = ini.GetDoubleValue("Colors", "MINI14Color_B", Settings::MINI14Color.z);
	Settings::MINI14Color.w = ini.GetDoubleValue("Colors", "MINI14Color_A", Settings::MINI14Color.w);

	// Example for MK14Color
	Settings::MK14Color.x = ini.GetDoubleValue("Colors", "MK14Color_R", Settings::MK14Color.x);
	Settings::MK14Color.y = ini.GetDoubleValue("Colors", "MK14Color_G", Settings::MK14Color.y);
	Settings::MK14Color.z = ini.GetDoubleValue("Colors", "MK14Color_B", Settings::MK14Color.z);
	Settings::MK14Color.w = ini.GetDoubleValue("Colors", "MK14Color_A", Settings::MK14Color.w);

	// Example for SLRColor
	Settings::SLRColor.x = ini.GetDoubleValue("Colors", "SLRColor_R", Settings::SLRColor.x);
	Settings::SLRColor.y = ini.GetDoubleValue("Colors", "SLRColor_G", Settings::SLRColor.y);
	Settings::SLRColor.z = ini.GetDoubleValue("Colors", "SLRColor_B", Settings::SLRColor.z);
	Settings::SLRColor.w = ini.GetDoubleValue("Colors", "SLRColor_A", Settings::SLRColor.w);

	// Example for QBUColor
	Settings::QBUColor.x = ini.GetDoubleValue("Colors", "QBUColor_R", Settings::QBUColor.x);
	Settings::QBUColor.y = ini.GetDoubleValue("Colors", "QBUColor_G", Settings::QBUColor.y);
	Settings::QBUColor.z = ini.GetDoubleValue("Colors", "QBUColor_B", Settings::QBUColor.z);
	Settings::QBUColor.w = ini.GetDoubleValue("Colors", "QBUColor_A", Settings::QBUColor.w);

	// Example for MK12Color
	Settings::MK12Color.x = ini.GetDoubleValue("Colors", "MK12Color_R", Settings::MK12Color.x);
	Settings::MK12Color.y = ini.GetDoubleValue("Colors", "MK12Color_G", Settings::MK12Color.y);
	Settings::MK12Color.z = ini.GetDoubleValue("Colors", "MK12Color_B", Settings::MK12Color.z);
	Settings::MK12Color.w = ini.GetDoubleValue("Colors", "MK12Color_A", Settings::MK12Color.w);

	// Example for UZIColor
	Settings::UZIColor.x = ini.GetDoubleValue("Colors", "UZIColor_R", Settings::UZIColor.x);
	Settings::UZIColor.y = ini.GetDoubleValue("Colors", "UZIColor_G", Settings::UZIColor.y);
	Settings::UZIColor.z = ini.GetDoubleValue("Colors", "UZIColor_B", Settings::UZIColor.z);
	Settings::UZIColor.w = ini.GetDoubleValue("Colors", "UZIColor_A", Settings::UZIColor.w);

	// Example for UMP45Color
	Settings::UMP45Color.x = ini.GetDoubleValue("Colors", "UMP45Color_R", Settings::UMP45Color.x);
	Settings::UMP45Color.y = ini.GetDoubleValue("Colors", "UMP45Color_G", Settings::UMP45Color.y);
	Settings::UMP45Color.z = ini.GetDoubleValue("Colors", "UMP45Color_B", Settings::UMP45Color.z);
	Settings::UMP45Color.w = ini.GetDoubleValue("Colors", "UMP45Color_A", Settings::UMP45Color.w);

	// Example for VECTORColor
	Settings::VECTORColor.x = ini.GetDoubleValue("Colors", "VECTORColor_R", Settings::VECTORColor.x);
	Settings::VECTORColor.y = ini.GetDoubleValue("Colors", "VECTORColor_G", Settings::VECTORColor.y);
	Settings::VECTORColor.z = ini.GetDoubleValue("Colors", "VECTORColor_B", Settings::VECTORColor.z);
	Settings::VECTORColor.w = ini.GetDoubleValue("Colors", "VECTORColor_A", Settings::VECTORColor.w);

	// Example for THOMPSONColor
	Settings::THOMPSONColor.x = ini.GetDoubleValue("Colors", "THOMPSONColor_R", Settings::THOMPSONColor.x);
	Settings::THOMPSONColor.y = ini.GetDoubleValue("Colors", "THOMPSONColor_G", Settings::THOMPSONColor.y);
	Settings::THOMPSONColor.z = ini.GetDoubleValue("Colors", "THOMPSONColor_B", Settings::THOMPSONColor.z);
	Settings::THOMPSONColor.w = ini.GetDoubleValue("Colors", "THOMPSONColor_A", Settings::THOMPSONColor.w);

	// Example for BIZONColor
	Settings::BIZONColor.x = ini.GetDoubleValue("Colors", "BIZONColor_R", Settings::BIZONColor.x);
	Settings::BIZONColor.y = ini.GetDoubleValue("Colors", "BIZONColor_G", Settings::BIZONColor.y);
	Settings::BIZONColor.z = ini.GetDoubleValue("Colors", "BIZONColor_B", Settings::BIZONColor.z);
	Settings::BIZONColor.w = ini.GetDoubleValue("Colors", "BIZONColor_A", Settings::BIZONColor.w);

	// Example for MP5KColor
	Settings::MP5KColor.x = ini.GetDoubleValue("Colors", "MP5KColor_R", Settings::MP5KColor.x);
	Settings::MP5KColor.y = ini.GetDoubleValue("Colors", "MP5KColor_G", Settings::MP5KColor.y);
	Settings::MP5KColor.z = ini.GetDoubleValue("Colors", "MP5KColor_B", Settings::MP5KColor.z);
	Settings::MP5KColor.w = ini.GetDoubleValue("Colors", "MP5KColor_A", Settings::MP5KColor.w);

	// Example for P90Color
	Settings::P90Color.x = ini.GetDoubleValue("Colors", "P90Color_R", Settings::P90Color.x);
	Settings::P90Color.y = ini.GetDoubleValue("Colors", "P90Color_G", Settings::P90Color.y);
	Settings::P90Color.z = ini.GetDoubleValue("Colors", "P90Color_B", Settings::P90Color.z);
	Settings::P90Color.w = ini.GetDoubleValue("Colors", "P90Color_A", Settings::P90Color.w);

	// Example for S686Color
	Settings::S686Color.x = ini.GetDoubleValue("Colors", "S686Color_R", Settings::S686Color.x);
	Settings::S686Color.y = ini.GetDoubleValue("Colors", "S686Color_G", Settings::S686Color.y);
	Settings::S686Color.z = ini.GetDoubleValue("Colors", "S686Color_B", Settings::S686Color.z);
	Settings::S686Color.w = ini.GetDoubleValue("Colors", "S686Color_A", Settings::S686Color.w);

	// Example for S1897Color
	Settings::S1897Color.x = ini.GetDoubleValue("Colors", "S1897Color_R", Settings::S1897Color.x);
	Settings::S1897Color.y = ini.GetDoubleValue("Colors", "S1897Color_G", Settings::S1897Color.y);
	Settings::S1897Color.z = ini.GetDoubleValue("Colors", "S1897Color_B", Settings::S1897Color.z);
	Settings::S1897Color.w = ini.GetDoubleValue("Colors", "S1897Color_A", Settings::S1897Color.w);

	// Example for S12KColor
	Settings::S12KColor.x = ini.GetDoubleValue("Colors", "S12KColor_R", Settings::S12KColor.x);
	Settings::S12KColor.y = ini.GetDoubleValue("Colors", "S12KColor_G", Settings::S12KColor.y);
	Settings::S12KColor.z = ini.GetDoubleValue("Colors", "S12KColor_B", Settings::S12KColor.z);
	Settings::S12KColor.w = ini.GetDoubleValue("Colors", "S12KColor_A", Settings::S12KColor.w);

	// Example for DBSColor
	Settings::DBSColor.x = ini.GetDoubleValue("Colors", "DBSColor_R", Settings::DBSColor.x);
	Settings::DBSColor.y = ini.GetDoubleValue("Colors", "DBSColor_G", Settings::DBSColor.y);
	Settings::DBSColor.z = ini.GetDoubleValue("Colors", "DBSColor_B", Settings::DBSColor.z);
	Settings::DBSColor.w = ini.GetDoubleValue("Colors", "DBSColor_A", Settings::DBSColor.w);

	// Example for M1014Color
	Settings::M1014Color.x = ini.GetDoubleValue("Colors", "M1014Color_R", Settings::M1014Color.x);
	Settings::M1014Color.y = ini.GetDoubleValue("Colors", "M1014Color_G", Settings::M1014Color.y);
	Settings::M1014Color.z = ini.GetDoubleValue("Colors", "M1014Color_B", Settings::M1014Color.z);
	Settings::M1014Color.w = ini.GetDoubleValue("Colors", "M1014Color_A", Settings::M1014Color.w);

	// Example for NS2000Color
	Settings::NS2000Color.x = ini.GetDoubleValue("Colors", "NS2000Color_R", Settings::NS2000Color.x);
	Settings::NS2000Color.y = ini.GetDoubleValue("Colors", "NS2000Color_G", Settings::NS2000Color.y);
	Settings::NS2000Color.z = ini.GetDoubleValue("Colors", "NS2000Color_B", Settings::NS2000Color.z);
	Settings::NS2000Color.w = ini.GetDoubleValue("Colors", "NS2000Color_A", Settings::NS2000Color.w);

	// Example for M249Color
	Settings::M249Color.x = ini.GetDoubleValue("Colors", "M249Color_R", Settings::M249Color.x);
	Settings::M249Color.y = ini.GetDoubleValue("Colors", "M249Color_G", Settings::M249Color.y);
	Settings::M249Color.z = ini.GetDoubleValue("Colors", "M249Color_B", Settings::M249Color.z);
	Settings::M249Color.w = ini.GetDoubleValue("Colors", "M249Color_A", Settings::M249Color.w);

	// Example for DP28Color
	Settings::DP28Color.x = ini.GetDoubleValue("Colors", "DP28Color_R", Settings::DP28Color.x);
	Settings::DP28Color.y = ini.GetDoubleValue("Colors", "DP28Color_G", Settings::DP28Color.y);
	Settings::DP28Color.z = ini.GetDoubleValue("Colors", "DP28Color_B", Settings::DP28Color.z);
	Settings::DP28Color.w = ini.GetDoubleValue("Colors", "DP28Color_A", Settings::DP28Color.w);

	// Example for MG3Color
	Settings::MG3Color.x = ini.GetDoubleValue("Colors", "MG3Color_R", Settings::MG3Color.x);
	Settings::MG3Color.y = ini.GetDoubleValue("Colors", "MG3Color_G", Settings::MG3Color.y);
	Settings::MG3Color.z = ini.GetDoubleValue("Colors", "MG3Color_B", Settings::MG3Color.z);
	Settings::MG3Color.w = ini.GetDoubleValue("Colors", "MG3Color_A", Settings::MG3Color.w);

	// Example for FLAREColor
	Settings::FLAREColor.x = ini.GetDoubleValue("Colors", "FLAREColor_R", Settings::FLAREColor.x);
	Settings::FLAREColor.y = ini.GetDoubleValue("Colors", "FLAREColor_G", Settings::FLAREColor.y);
	Settings::FLAREColor.z = ini.GetDoubleValue("Colors", "FLAREColor_B", Settings::FLAREColor.z);
	Settings::FLAREColor.w = ini.GetDoubleValue("Colors", "FLAREColor_A", Settings::FLAREColor.w);

	// Example for FRAGColor
	Settings::FRAGColor.x = ini.GetDoubleValue("Colors", "FRAGColor_R", Settings::FRAGColor.x);
	Settings::FRAGColor.y = ini.GetDoubleValue("Colors", "FRAGColor_G", Settings::FRAGColor.y);
	Settings::FRAGColor.z = ini.GetDoubleValue("Colors", "FRAGColor_B", Settings::FRAGColor.z);
	Settings::FRAGColor.w = ini.GetDoubleValue("Colors", "FRAGColor_A", Settings::FRAGColor.w);

	// Example for SMOKEColor
	Settings::SMOKEColor.x = ini.GetDoubleValue("Colors", "SMOKEColor_R", Settings::SMOKEColor.x);
	Settings::SMOKEColor.y = ini.GetDoubleValue("Colors", "SMOKEColor_G", Settings::SMOKEColor.y);
	Settings::SMOKEColor.z = ini.GetDoubleValue("Colors", "SMOKEColor_B", Settings::SMOKEColor.z);
	Settings::SMOKEColor.w = ini.GetDoubleValue("Colors", "SMOKEColor_A", Settings::SMOKEColor.w);

	// Example for MOLOTOFColor
	Settings::MOLOTOFColor.x = ini.GetDoubleValue("Colors", "MOLOTOFColor_R", Settings::MOLOTOFColor.x);
	Settings::MOLOTOFColor.y = ini.GetDoubleValue("Colors", "MOLOTOFColor_G", Settings::MOLOTOFColor.y);
	Settings::MOLOTOFColor.z = ini.GetDoubleValue("Colors", "MOLOTOFColor_B", Settings::MOLOTOFColor.z);
	Settings::MOLOTOFColor.w = ini.GetDoubleValue("Colors", "MOLOTOFColor_A", Settings::MOLOTOFColor.w);

	// Example for MedKitColor
	Settings::MedKitColor.x = ini.GetDoubleValue("Colors", "MedKitColor_R", Settings::MedKitColor.x);
	Settings::MedKitColor.y = ini.GetDoubleValue("Colors", "MedKitColor_G", Settings::MedKitColor.y);
	Settings::MedKitColor.z = ini.GetDoubleValue("Colors", "MedKitColor_B", Settings::MedKitColor.z);
	Settings::MedKitColor.w = ini.GetDoubleValue("Colors", "MedKitColor_A", Settings::MedKitColor.w);

	// Example for FirstAidKitColor
	Settings::FirstAidKitColor.x = ini.GetDoubleValue("Colors", "FirstAidKitColor_R", Settings::FirstAidKitColor.x);
	Settings::FirstAidKitColor.y = ini.GetDoubleValue("Colors", "FirstAidKitColor_G", Settings::FirstAidKitColor.y);
	Settings::FirstAidKitColor.z = ini.GetDoubleValue("Colors", "FirstAidKitColor_B", Settings::FirstAidKitColor.z);
	Settings::FirstAidKitColor.w = ini.GetDoubleValue("Colors", "FirstAidKitColor_A", Settings::FirstAidKitColor.w);

	// Example for PainkillerColor
	Settings::PainkillerColor.x = ini.GetDoubleValue("Colors", "PainkillerColor_R", Settings::PainkillerColor.x);
	Settings::PainkillerColor.y = ini.GetDoubleValue("Colors", "PainkillerColor_G", Settings::PainkillerColor.y);
	Settings::PainkillerColor.z = ini.GetDoubleValue("Colors", "PainkillerColor_B", Settings::PainkillerColor.z);
	Settings::PainkillerColor.w = ini.GetDoubleValue("Colors", "PainkillerColor_A", Settings::PainkillerColor.w);

	// Example for EnergyDrinkColor
	Settings::EnergyDrinkColor.x = ini.GetDoubleValue("Colors", "EnergyDrinkColor_R", Settings::EnergyDrinkColor.x);
	Settings::EnergyDrinkColor.y = ini.GetDoubleValue("Colors", "EnergyDrinkColor_G", Settings::EnergyDrinkColor.y);
	Settings::EnergyDrinkColor.z = ini.GetDoubleValue("Colors", "EnergyDrinkColor_B", Settings::EnergyDrinkColor.z);
	Settings::EnergyDrinkColor.w = ini.GetDoubleValue("Colors", "EnergyDrinkColor_A", Settings::EnergyDrinkColor.w);

	// Example for AdrenalinColor
	Settings::AdrenalinColor.x = ini.GetDoubleValue("Colors", "AdrenalinColor_R", Settings::AdrenalinColor.x);
	Settings::AdrenalinColor.y = ini.GetDoubleValue("Colors", "AdrenalinColor_G", Settings::AdrenalinColor.y);
	Settings::AdrenalinColor.z = ini.GetDoubleValue("Colors", "AdrenalinColor_B", Settings::AdrenalinColor.z);
	Settings::AdrenalinColor.w = ini.GetDoubleValue("Colors", "AdrenalinColor_A", Settings::AdrenalinColor.w);

	// Example for Bag1Color
	Settings::Bag1Color.x = ini.GetDoubleValue("Colors", "Bag1Color_R", Settings::Bag1Color.x);
	Settings::Bag1Color.y = ini.GetDoubleValue("Colors", "Bag1Color_G", Settings::Bag1Color.y);
	Settings::Bag1Color.z = ini.GetDoubleValue("Colors", "Bag1Color_B", Settings::Bag1Color.z);
	Settings::Bag1Color.w = ini.GetDoubleValue("Colors", "Bag1Color_A", Settings::Bag1Color.w);

	// Example for Bag2Color
	Settings::Bag2Color.x = ini.GetDoubleValue("Colors", "Bag2Color_R", Settings::Bag2Color.x);
	Settings::Bag2Color.y = ini.GetDoubleValue("Colors", "Bag2Color_G", Settings::Bag2Color.y);
	Settings::Bag2Color.z = ini.GetDoubleValue("Colors", "Bag2Color_B", Settings::Bag2Color.z);
	Settings::Bag2Color.w = ini.GetDoubleValue("Colors", "Bag2Color_A", Settings::Bag2Color.w);

	// Example for Bag3Color
	Settings::Bag3Color.x = ini.GetDoubleValue("Colors", "Bag3Color_R", Settings::Bag3Color.x);
	Settings::Bag3Color.y = ini.GetDoubleValue("Colors", "Bag3Color_G", Settings::Bag3Color.y);
	Settings::Bag3Color.z = ini.GetDoubleValue("Colors", "Bag3Color_B", Settings::Bag3Color.z);
	Settings::Bag3Color.w = ini.GetDoubleValue("Colors", "Bag3Color_A", Settings::Bag3Color.w);

	// Example for Helmet1Color
	Settings::Helmet1Color.x = ini.GetDoubleValue("Colors", "Helmet1Color_R", Settings::Helmet1Color.x);
	Settings::Helmet1Color.y = ini.GetDoubleValue("Colors", "Helmet1Color_G", Settings::Helmet1Color.y);
	Settings::Helmet1Color.z = ini.GetDoubleValue("Colors", "Helmet1Color_B", Settings::Helmet1Color.z);
	Settings::Helmet1Color.w = ini.GetDoubleValue("Colors", "Helmet1Color_A", Settings::Helmet1Color.w);

	// Example for Helmet2Color
	Settings::Helmet2Color.x = ini.GetDoubleValue("Colors", "Helmet2Color_R", Settings::Helmet2Color.x);
	Settings::Helmet2Color.y = ini.GetDoubleValue("Colors", "Helmet2Color_G", Settings::Helmet2Color.y);
	Settings::Helmet2Color.z = ini.GetDoubleValue("Colors", "Helmet2Color_B", Settings::Helmet2Color.z);
	Settings::Helmet2Color.w = ini.GetDoubleValue("Colors", "Helmet2Color_A", Settings::Helmet2Color.w);

	// Example for Helmet3Color
	Settings::Helmet3Color.x = ini.GetDoubleValue("Colors", "Helmet3Color_R", Settings::Helmet3Color.x);
	Settings::Helmet3Color.y = ini.GetDoubleValue("Colors", "Helmet3Color_G", Settings::Helmet3Color.y);
	Settings::Helmet3Color.z = ini.GetDoubleValue("Colors", "Helmet3Color_B", Settings::Helmet3Color.z);
	Settings::Helmet3Color.w = ini.GetDoubleValue("Colors", "Helmet3Color_A", Settings::Helmet3Color.w);

	// Example for Armor1Color
	Settings::Armor1Color.x = ini.GetDoubleValue("Colors", "Armor1Color_R", Settings::Armor1Color.x);
	Settings::Armor1Color.y = ini.GetDoubleValue("Colors", "Armor1Color_G", Settings::Armor1Color.y);
	Settings::Armor1Color.z = ini.GetDoubleValue("Colors", "Armor1Color_B", Settings::Armor1Color.z);
	Settings::Armor1Color.w = ini.GetDoubleValue("Colors", "Armor1Color_A", Settings::Armor1Color.w);

	// Example for Armor2Color
	Settings::Armor2Color.x = ini.GetDoubleValue("Colors", "Armor2Color_R", Settings::Armor2Color.x);
	Settings::Armor2Color.y = ini.GetDoubleValue("Colors", "Armor2Color_G", Settings::Armor2Color.y);
	Settings::Armor2Color.z = ini.GetDoubleValue("Colors", "Armor2Color_B", Settings::Armor2Color.z);
	Settings::Armor2Color.w = ini.GetDoubleValue("Colors", "Armor2Color_A", Settings::Armor2Color.w);

	// Example for Armor3Color
	Settings::Armor3Color.x = ini.GetDoubleValue("Colors", "Armor3Color_R", Settings::Armor3Color.x);
	Settings::Armor3Color.y = ini.GetDoubleValue("Colors", "Armor3Color_G", Settings::Armor3Color.y);
	Settings::Armor3Color.z = ini.GetDoubleValue("Colors", "Armor3Color_B", Settings::Armor3Color.z);
	Settings::Armor3Color.w = ini.GetDoubleValue("Colors", "Armor3Color_A", Settings::Armor3Color.w);

	// Example for a762mmColor
	Settings::a762mmColor.x = ini.GetDoubleValue("Colors", "a762mmColor_R", Settings::a762mmColor.x);
	Settings::a762mmColor.y = ini.GetDoubleValue("Colors", "a762mmColor_G", Settings::a762mmColor.y);
	Settings::a762mmColor.z = ini.GetDoubleValue("Colors", "a762mmColor_B", Settings::a762mmColor.z);
	Settings::a762mmColor.w = ini.GetDoubleValue("Colors", "a762mmColor_A", Settings::a762mmColor.w);

	// Example for a556mmColor
	Settings::a556mmColor.x = ini.GetDoubleValue("Colors", "a556mmColor_R", Settings::a556mmColor.x);
	Settings::a556mmColor.y = ini.GetDoubleValue("Colors", "a556mmColor_G", Settings::a556mmColor.y);
	Settings::a556mmColor.z = ini.GetDoubleValue("Colors", "a556mmColor_B", Settings::a556mmColor.z);
	Settings::a556mmColor.w = ini.GetDoubleValue("Colors", "a556mmColor_A", Settings::a556mmColor.w);

	// Example for a9mmColor
	Settings::a9mmColor.x = ini.GetDoubleValue("Colors", "a9mmColor_R", Settings::a9mmColor.x);
	Settings::a9mmColor.y = ini.GetDoubleValue("Colors", "a9mmColor_G", Settings::a9mmColor.y);
	Settings::a9mmColor.z = ini.GetDoubleValue("Colors", "a9mmColor_B", Settings::a9mmColor.z);
	Settings::a9mmColor.w = ini.GetDoubleValue("Colors", "a9mmColor_A", Settings::a9mmColor.w);

	// Example for a45ACPColor
	Settings::a45ACPColor.x = ini.GetDoubleValue("Colors", "a45ACPColor_R", Settings::a45ACPColor.x);
	Settings::a45ACPColor.y = ini.GetDoubleValue("Colors", "a45ACPColor_G", Settings::a45ACPColor.y);
	Settings::a45ACPColor.z = ini.GetDoubleValue("Colors", "a45ACPColor_B", Settings::a45ACPColor.z);
	Settings::a45ACPColor.w = ini.GetDoubleValue("Colors", "a45ACPColor_A", Settings::a45ACPColor.w);

	// Example for a12GauegeColor
	Settings::a12GauegeColor.x = ini.GetDoubleValue("Colors", "a12GauegeColor_R", Settings::a12GauegeColor.x);
	Settings::a12GauegeColor.y = ini.GetDoubleValue("Colors", "a12GauegeColor_G", Settings::a12GauegeColor.y);
	Settings::a12GauegeColor.z = ini.GetDoubleValue("Colors", "a12GauegeColor_B", Settings::a12GauegeColor.z);
	Settings::a12GauegeColor.w = ini.GetDoubleValue("Colors", "a12GauegeColor_A", Settings::a12GauegeColor.w);

	// Example for AwmAmmoColor
	Settings::AwmAmmoColor.x = ini.GetDoubleValue("Colors", "AwmAmmoColor_R", Settings::AwmAmmoColor.x);
	Settings::AwmAmmoColor.y = ini.GetDoubleValue("Colors", "AwmAmmoColor_G", Settings::AwmAmmoColor.y);
	Settings::AwmAmmoColor.z = ini.GetDoubleValue("Colors", "AwmAmmoColor_B", Settings::AwmAmmoColor.z);
	Settings::AwmAmmoColor.w = ini.GetDoubleValue("Colors", "AwmAmmoColor_A", Settings::AwmAmmoColor.w);

	// Example for AmrAmmoColor
	Settings::AmrAmmoColor.x = ini.GetDoubleValue("Colors", "AmrAmmoColor_R", Settings::AmrAmmoColor.x);
	Settings::AmrAmmoColor.y = ini.GetDoubleValue("Colors", "AmrAmmoColor_G", Settings::AmrAmmoColor.y);
	Settings::AmrAmmoColor.z = ini.GetDoubleValue("Colors", "AmrAmmoColor_B", Settings::AmrAmmoColor.z);
	Settings::AmrAmmoColor.w = ini.GetDoubleValue("Colors", "AmrAmmoColor_A", Settings::AmrAmmoColor.w);


	// Example for Scope_x2Color
	Settings::Scope_x2Color.x = ini.GetDoubleValue("Colors", "Scope_x2Color_R", Settings::Scope_x2Color.x);
	Settings::Scope_x2Color.y = ini.GetDoubleValue("Colors", "Scope_x2Color_G", Settings::Scope_x2Color.y);
	Settings::Scope_x2Color.z = ini.GetDoubleValue("Colors", "Scope_x2Color_B", Settings::Scope_x2Color.z);
	Settings::Scope_x2Color.w = ini.GetDoubleValue("Colors", "Scope_x2Color_A", Settings::Scope_x2Color.w);

	// Example for Scope_x3Color
	Settings::Scope_x3Color.x = ini.GetDoubleValue("Colors", "Scope_x3Color_R", Settings::Scope_x3Color.x);
	Settings::Scope_x3Color.y = ini.GetDoubleValue("Colors", "Scope_x3Color_G", Settings::Scope_x3Color.y);
	Settings::Scope_x3Color.z = ini.GetDoubleValue("Colors", "Scope_x3Color_B", Settings::Scope_x3Color.z);
	Settings::Scope_x3Color.w = ini.GetDoubleValue("Colors", "Scope_x3Color_A", Settings::Scope_x3Color.w);

	// Example for Scope_x4Color
	Settings::Scope_x4Color.x = ini.GetDoubleValue("Colors", "Scope_x4Color_R", Settings::Scope_x4Color.x);
	Settings::Scope_x4Color.y = ini.GetDoubleValue("Colors", "Scope_x4Color_G", Settings::Scope_x4Color.y);
	Settings::Scope_x4Color.z = ini.GetDoubleValue("Colors", "Scope_x4Color_B", Settings::Scope_x4Color.z);
	Settings::Scope_x4Color.w = ini.GetDoubleValue("Colors", "Scope_x4Color_A", Settings::Scope_x4Color.w);

	// Example for Scope_x6Color
	Settings::Scope_x6Color.x = ini.GetDoubleValue("Colors", "Scope_x6Color_R", Settings::Scope_x6Color.x);
	Settings::Scope_x6Color.y = ini.GetDoubleValue("Colors", "Scope_x6Color_G", Settings::Scope_x6Color.y);
	Settings::Scope_x6Color.z = ini.GetDoubleValue("Colors", "Scope_x6Color_B", Settings::Scope_x6Color.z);
	Settings::Scope_x6Color.w = ini.GetDoubleValue("Colors", "Scope_x6Color_A", Settings::Scope_x6Color.w);

	// Example for Scope_x8Color
	Settings::Scope_x8Color.x = ini.GetDoubleValue("Colors", "Scope_x8Color_R", Settings::Scope_x8Color.x);
	Settings::Scope_x8Color.y = ini.GetDoubleValue("Colors", "Scope_x8Color_G", Settings::Scope_x8Color.y);
	Settings::Scope_x8Color.z = ini.GetDoubleValue("Colors", "Scope_x8Color_B", Settings::Scope_x8Color.z);
	Settings::Scope_x8Color.w = ini.GetDoubleValue("Colors", "Scope_x8Color_A", Settings::Scope_x8Color.w);

	// Example for shoptoken Color
	Settings::ShopTokenColor.x = ini.GetDoubleValue("Colors", "ShopTokenColor_R", Settings::ShopTokenColor.x);
	Settings::ShopTokenColor.y = ini.GetDoubleValue("Colors", "ShopTokenColor_G", Settings::ShopTokenColor.y);
	Settings::ShopTokenColor.z = ini.GetDoubleValue("Colors", "ShopTokenColor_B", Settings::ShopTokenColor.z);
	Settings::ShopTokenColor.w = ini.GetDoubleValue("Colors", "ShopTokenColor_A", Settings::ShopTokenColor.w);

	// Example for mac Color
	Settings::ExtendedMacColor.x = ini.GetDoubleValue("Colors", "ExtendedMacColor_R", Settings::ExtendedMacColor.x);
	Settings::ExtendedMacColor.y = ini.GetDoubleValue("Colors", "ExtendedMacColor_G", Settings::ExtendedMacColor.y);
	Settings::ExtendedMacColor.z = ini.GetDoubleValue("Colors", "ExtendedMacColor_B", Settings::ExtendedMacColor.z);
	Settings::ExtendedMacColor.w = ini.GetDoubleValue("Colors", "ExtendedMacColor_A", Settings::ExtendedMacColor.w);

	// Example for supressor Color
	Settings::SupressorColor.x = ini.GetDoubleValue("Colors", "SupressorColor_R", Settings::SupressorColor.x);
	Settings::SupressorColor.y = ini.GetDoubleValue("Colors", "SupressorColor_G", Settings::SupressorColor.y);
	Settings::SupressorColor.z = ini.GetDoubleValue("Colors", "SupressorColor_B", Settings::SupressorColor.z);
	Settings::SupressorColor.w = ini.GetDoubleValue("Colors", "SupressorColor_A", Settings::SupressorColor.w);

	// Example for vis Color
	Settings::visColor.x = ini.GetDoubleValue("Colors", "visColor_R", Settings::visColor.x);
	Settings::visColor.y = ini.GetDoubleValue("Colors", "visColor_G", Settings::visColor.y);
	Settings::visColor.z = ini.GetDoubleValue("Colors", "visColor_B", Settings::visColor.z);
	Settings::visColor.w = ini.GetDoubleValue("Colors", "visColor_A", Settings::visColor.w);


	Settings::fovcircleredus = ini.GetDoubleValue("Floats", "fovcircleredus", Settings::fovcircleredus);
	Settings::AimSpeed = ini.GetDoubleValue("Floats", "AimSpeed", Settings::AimSpeed);
	Settings::RepidFireValue = ini.GetDoubleValue("Floats", "RepidFireValue", Settings::RepidFireValue);
	Settings::percentage = ini.GetDoubleValue("Floats", "percentage", Settings::percentage);
	Settings::linethickness = ini.GetDoubleValue("Floats", "linethickness", Settings::linethickness);
	Settings::skeletonthickness = ini.GetDoubleValue("Floats", "skeletonthickness", Settings::skeletonthickness);
	



	Settings::IpadValue = ini.GetLongValue("Ints", "IpadValue", Settings::IpadValue);
	Settings::InstantValue = ini.GetLongValue("Ints", "InstantValue", Settings::InstantValue);
	Settings::UpdateTick = ini.GetLongValue("Ints", "UpdateTick", Settings::UpdateTick);
	Settings::UpdateFps = ini.GetLongValue("Ints", "UpdateFps", Settings::UpdateFps);
	Settings::PlayerNameSize = ini.GetLongValue("Ints", "PlayerNameSize", Settings::PlayerNameSize);
	Settings::PlayerStateSize = ini.GetLongValue("Ints", "PlayerStateSize", Settings::PlayerStateSize);
	Settings::VehicleSize = ini.GetLongValue("Ints", "VehicleSize", Settings::VehicleSize);
	Settings::RadarSize = ini.GetLongValue("Ints", "RadarSize", Settings::RadarSize);
	Settings::DotsSize = ini.GetLongValue("Ints", "DotsSize", Settings::DotsSize);
	Settings::PlayerSkeletonMode = ini.GetLongValue("Ints", "PlayerSkeletonMode", Settings::PlayerSkeletonMode);
	Settings::PlayerLineMode = ini.GetLongValue("Ints", "PlayerLineMode", Settings::PlayerLineMode);
	Settings::MaxAimDistence = ini.GetLongValue("Ints", "MaxAimDistence", Settings::MaxAimDistence);
	Settings::AimKey = ini.GetLongValue("Ints", "AimKey", Settings::AimKey);
	Settings::macroval = ini.GetLongValue("Ints", "macro", Settings::macroval);

	Settings::weight = ini.GetLongValue("Ints", "weight", Settings::weight);
	Settings::currentBoneIndex = ini.GetLongValue("Ints", "currentBoneIndex", Settings::currentBoneIndex);

	Settings::carsexkey = ini.GetLongValue("Ints", "carsexkey", Settings::carsexkey);

	Settings::curraim = ini.GetLongValue("Ints", "curraim", Settings::curraim);
	Settings::aimbotmode = ini.GetLongValue("Ints", "aimbotmode", Settings::aimbotmode);
	Settings::bulletrackMode = ini.GetLongValue("Ints", "bulletrackMode", Settings::bulletrackMode);
	Settings::prediction = ini.GetLongValue("Ints", "prediction", Settings::prediction);

	Settings::visbulletcheck = ini.GetBoolValue("Bools", "visbulletcheck", Settings::visbulletcheck ? true : false);

	Settings::carsex = ini.GetBoolValue("Bools", "carsex", Settings::carsex ? true : false);

	Settings::crosshair = ini.GetBoolValue("Bools", "crosshair", Settings::crosshair ? true : false);
	Settings::BypassFovLimit = ini.GetBoolValue("Bools", "BypassFovLimit", Settings::BypassFovLimit ? true : false);
	Settings::visibilitycheck = ini.GetBoolValue("Bools", "visibilitycheck", Settings::visibilitycheck ? true : false);
	Settings::isPrioritySet = ini.GetBoolValue("Bools", "isPrioritySet", Settings::isPrioritySet ? true : false);
	Settings::sendscreenshot = ini.GetBoolValue("Bools", "sendscreenshot", Settings::sendscreenshot ? true : false);
	Settings::grenadePath = ini.GetBoolValue("Bools", "grenadePath", Settings::grenadePath ? true : false);
	Settings::SkipBots = ini.GetBoolValue("Bools", "SkipBots", Settings::SkipBots ? true : false);
	Settings::knocked = ini.GetBoolValue("Bools", "knocked", Settings::knocked ? true : false);
	Settings::AimBot = ini.GetBoolValue("Bools", "AimBot", Settings::AimBot ? true : false);
	Settings::Legitrack = ini.GetBoolValue("Bools", "Legitrack", Settings::Legitrack ? true : false);
	Settings::MagicBullet = ini.GetBoolValue("Bools", "MagicBullet", Settings::MagicBullet ? true : false);
	Settings::Fovbased = ini.GetBoolValue("Bools", "Fovbased", Settings::Fovbased ? true : false);
	Settings::peekdetect = ini.GetBoolValue("Bools", "peekdetect", Settings::peekdetect ? true : false);
	Settings::FovShow = ini.GetBoolValue("Bools", "FovShow", Settings::FovShow ? true : false);
	Settings::AntiStream = ini.GetBoolValue("Bools", "AntiStream", Settings::AntiStream ? true : false);
	Settings::IpadView = ini.GetBoolValue("Bools", "IpadView", Settings::IpadView ? true : false);
	Settings::NoRecoil = ini.GetBoolValue("Bools", "NoRecoil", Settings::NoRecoil ? true : false);
	Settings::ForceTpp = ini.GetBoolValue("Bools", "ForceTpp", Settings::ForceTpp ? true : false);
	Settings::Xeffect = ini.GetBoolValue("Bools", "Xeffect", Settings::Xeffect ? true : false);
	Settings::InstantHit = ini.GetBoolValue("Bools", "InstantHit", Settings::InstantHit ? true : false);
	Settings::NoSpread = ini.GetBoolValue("Bools", "NoSpread", Settings::NoSpread ? true : false);
	Settings::FastSwitch = ini.GetBoolValue("Bools", "FastSwitch", Settings::FastSwitch ? true : false);
	Settings::RepidFire = ini.GetBoolValue("Bools", "RepidFire", Settings::RepidFire ? true : false);
	Settings::YourInfo = ini.GetBoolValue("Bools", "YourInfo", Settings::YourInfo ? true : false);
	Settings::GameInfo = ini.GetBoolValue("Bools", "GameInfo", Settings::GameInfo ? true : false);
	Settings::PlayerName = ini.GetBoolValue("Bools", "PlayerName", Settings::PlayerName ? true : false);
	Settings::PlayerSkeleton = ini.GetBoolValue("Bools", "PlayerSkeleton", Settings::PlayerSkeleton ? true : false);
	Settings::PlayerLine = ini.GetBoolValue("Bools", "PlayerLine", Settings::PlayerLine ? true : false);
	Settings::PlayerDistance = ini.GetBoolValue("Bools", "PlayerDistance", Settings::PlayerDistance ? true : false);
	Settings::PlayerHealth = ini.GetBoolValue("Bools", "PlayerHealth", Settings::PlayerHealth ? true : false);
	Settings::PlayerWeapon = ini.GetBoolValue("Bools", "PlayerWeapon", Settings::PlayerWeapon ? true : false);
	Settings::PlayerFlag = ini.GetBoolValue("Bools", "PlayerFlag", Settings::PlayerFlag ? true : false);
	Settings::PlayerBox = ini.GetBoolValue("Bools", "PlayerBox", Settings::PlayerBox ? true : false);
	Settings::PlayerState = ini.GetBoolValue("Bools", "PlayerState", Settings::PlayerState ? true : false);
	Settings::Items = ini.GetBoolValue("Bools", "Items", Settings::Items ? true : false);
	Settings::TotalEnemy = ini.GetBoolValue("Bools", "TotalEnemy", Settings::TotalEnemy ? true : false);
	Settings::Vehicle = ini.GetBoolValue("Bools", "Vehicle", Settings::Vehicle ? true : false);
	Settings::Lootbox = ini.GetBoolValue("Bools", "Lootbox", Settings::Lootbox ? true : false);
	Settings::LootboxItems = ini.GetBoolValue("Bools", "LootboxItems", Settings::LootboxItems ? true : false);
	Settings::AirDrop = ini.GetBoolValue("Bools", "AirDrop", Settings::AirDrop ? true : false);
	Settings::AirDropItems = ini.GetBoolValue("Bools", "AirDropItems", Settings::AirDropItems ? true : false);
	Settings::GrandeWarning = ini.GetBoolValue("Bools", "GrandeWarning", Settings::GrandeWarning ? true : false);
	Settings::AimWarning = ini.GetBoolValue("Bools", "AimWarning", Settings::AimWarning ? true : false);
	Settings::Redzone = ini.GetBoolValue("Bools", "Redzone", Settings::Redzone ? true : false);
	Settings::Dots = ini.GetBoolValue("Bools", "Dots", Settings::Dots ? true : false);
	Settings::Radar = ini.GetBoolValue("Bools", "Radar", Settings::Radar ? true : false);
	Settings::Akm = ini.GetBoolValue("Bools", "Akm", Settings::Akm ? true : false);
	Settings::M16A4 = ini.GetBoolValue("Bools", "M16A4", Settings::M16A4 ? true : false);
	Settings::SCARL = ini.GetBoolValue("Bools", "SCARL", Settings::SCARL ? true : false);
	Settings::M416 = ini.GetBoolValue("Bools", "M416", Settings::M416 ? true : false);
	Settings::GROZA = ini.GetBoolValue("Bools", "GROZA", Settings::GROZA ? true : false);
	Settings::AUG = ini.GetBoolValue("Bools", "AUG", Settings::AUG ? true : false);
	Settings::QBZ = ini.GetBoolValue("Bools", "QBZ", Settings::QBZ ? true : false);
	Settings::M762 = ini.GetBoolValue("Bools", "M762", Settings::M762 ? true : false);
	Settings::MK47 = ini.GetBoolValue("Bools", "MK47", Settings::MK47 ? true : false);
	Settings::G36C = ini.GetBoolValue("Bools", "G36C", Settings::G36C ? true : false);
	Settings::HONEY = ini.GetBoolValue("Bools", "HONEY", Settings::HONEY ? true : false);
	Settings::FAMAS = ini.GetBoolValue("Bools", "FAMAS", Settings::FAMAS ? true : false);
	Settings::KAR98 = ini.GetBoolValue("Bools", "KAR98", Settings::KAR98 ? true : false);
	Settings::M24 = ini.GetBoolValue("Bools", "M24", Settings::M24 ? true : false);
	Settings::AWM = ini.GetBoolValue("Bools", "AWM", Settings::AWM ? true : false);
	Settings::WIN94 = ini.GetBoolValue("Bools", "WIN94", Settings::WIN94 ? true : false);
	Settings::MOSIN = ini.GetBoolValue("Bools", "MOSIN", Settings::MOSIN ? true : false);
	Settings::AMR = ini.GetBoolValue("Bools", "AMR", Settings::AMR ? true : false);
	Settings::SKS = ini.GetBoolValue("Bools", "SKS", Settings::SKS ? true : false);
	Settings::VSS = ini.GetBoolValue("Bools", "VSS", Settings::VSS ? true : false);
	Settings::MINI14 = ini.GetBoolValue("Bools", "MINI14", Settings::MINI14 ? true : false);
	Settings::MK14 = ini.GetBoolValue("Bools", "MK14", Settings::MK14 ? true : false);
	Settings::SLR = ini.GetBoolValue("Bools", "SLR", Settings::SLR ? true : false);
	Settings::QBU = ini.GetBoolValue("Bools", "QBU", Settings::QBU ? true : false);
	Settings::MK12 = ini.GetBoolValue("Bools", "MK12", Settings::MK12 ? true : false);
	Settings::UZI = ini.GetBoolValue("Bools", "UZI", Settings::UZI ? true : false);
	Settings::UMP45 = ini.GetBoolValue("Bools", "UMP45", Settings::UMP45 ? true : false);
	Settings::VECTOR = ini.GetBoolValue("Bools", "VECTOR", Settings::VECTOR ? true : false);
	Settings::THOMPSON = ini.GetBoolValue("Bools", "THOMPSON", Settings::THOMPSON ? true : false);
	Settings::BIZON = ini.GetBoolValue("Bools", "BIZON", Settings::BIZON ? true : false);
	Settings::MP5K = ini.GetBoolValue("Bools", "MP5K", Settings::MP5K ? true : false);
	Settings::P90 = ini.GetBoolValue("Bools", "P90", Settings::P90 ? true : false);
	Settings::S686 = ini.GetBoolValue("Bools", "S686", Settings::S686 ? true : false);
	Settings::S1897 = ini.GetBoolValue("Bools", "S1897", Settings::S1897 ? true : false);
	Settings::S12K = ini.GetBoolValue("Bools", "S12K", Settings::S12K ? true : false);
	Settings::DBS = ini.GetBoolValue("Bools", "DBS", Settings::DBS ? true : false);
	Settings::M1014 = ini.GetBoolValue("Bools", "M1014", Settings::M1014 ? true : false);
	Settings::NS2000 = ini.GetBoolValue("Bools", "NS2000", Settings::NS2000 ? true : false);
	Settings::M249 = ini.GetBoolValue("Bools", "M249", Settings::M249 ? true : false);
	Settings::DP28 = ini.GetBoolValue("Bools", "DP28", Settings::DP28 ? true : false);
	Settings::MG3 = ini.GetBoolValue("Bools", "MG3", Settings::MG3 ? true : false);
	Settings::FLARE = ini.GetBoolValue("Bools", "FLARE", Settings::FLARE ? true : false);
	Settings::FRAG = ini.GetBoolValue("Bools", "FRAG", Settings::FRAG ? true : false);
	Settings::SMOKE = ini.GetBoolValue("Bools", "SMOKE", Settings::SMOKE ? true : false);
	Settings::MOLOTOF = ini.GetBoolValue("Bools", "MOLOTOF", Settings::MOLOTOF ? true : false);
	Settings::MedKit = ini.GetBoolValue("Bools", "MedKit", Settings::MedKit ? true : false);
	Settings::FirstAidKit = ini.GetBoolValue("Bools", "FirstAidKit", Settings::FirstAidKit ? true : false);
	Settings::Painkiller = ini.GetBoolValue("Bools", "Painkiller", Settings::Painkiller ? true : false);
	Settings::EnergyDrink = ini.GetBoolValue("Bools", "EnergyDrink", Settings::EnergyDrink ? true : false);
	Settings::Adrenalin = ini.GetBoolValue("Bools", "Adrenalin", Settings::Adrenalin ? true : false);
	Settings::Bag1 = ini.GetBoolValue("Bools", "Bag1", Settings::Bag1 ? true : false);
	Settings::Bag2 = ini.GetBoolValue("Bools", "Bag2", Settings::Bag2 ? true : false);
	Settings::Bag3 = ini.GetBoolValue("Bools", "Bag3", Settings::Bag3 ? true : false);
	Settings::Helmet1 = ini.GetBoolValue("Bools", "Helmet1", Settings::Helmet1 ? true : false);
	Settings::Helmet2 = ini.GetBoolValue("Bools", "Helmet2", Settings::Helmet2 ? true : false);
	Settings::Helmet3 = ini.GetBoolValue("Bools", "Helmet3", Settings::Helmet3 ? true : false);
	Settings::Armor1 = ini.GetBoolValue("Bools", "Armor1", Settings::Armor1 ? true : false);
	Settings::Armor2 = ini.GetBoolValue("Bools", "Armor2", Settings::Armor2 ? true : false);
	Settings::Armor3 = ini.GetBoolValue("Bools", "Armor3", Settings::Armor3 ? true : false);
	Settings::a762mm = ini.GetBoolValue("Bools", "a762mm", Settings::a762mm ? true : false);
	Settings::a556mm = ini.GetBoolValue("Bools", "a556mm", Settings::a556mm ? true : false);
	Settings::a9mm = ini.GetBoolValue("Bools", "a9mm", Settings::a9mm ? true : false);
	Settings::a45ACP = ini.GetBoolValue("Bools", "a45ACP", Settings::a45ACP ? true : false);
	Settings::a12Gauege = ini.GetBoolValue("Bools", "a12Gauege", Settings::a12Gauege ? true : false);
	Settings::AwmAmmo = ini.GetBoolValue("Bools", "AwmAmmo", Settings::AwmAmmo ? true : false);
	Settings::AmrAmmo = ini.GetBoolValue("Bools", "AmrAmmo", Settings::AmrAmmo ? true : false);
	Settings::Scope_x2 = ini.GetBoolValue("Bools", "Scope_x2", Settings::Scope_x2 ? true : false);
	Settings::Scope_x3 = ini.GetBoolValue("Bools", "Scope_x3", Settings::Scope_x3 ? true : false);
	Settings::Scope_x4 = ini.GetBoolValue("Bools", "Scope_x4", Settings::Scope_x4 ? true : false);
	Settings::Scope_x6 = ini.GetBoolValue("Bools", "Scope_x6", Settings::Scope_x6 ? true : false);
	Settings::Scope_x8 = ini.GetBoolValue("Bools", "Scope_x8", Settings::Scope_x8 ? true : false);
	Settings::ShopToken = ini.GetBoolValue("Bools", "ShopToken", Settings::ShopToken ? true : false);
	Settings::ExtendedMac = ini.GetBoolValue("Bools", "ExtendedMac", Settings::ExtendedMac ? true : false);
	Settings::Supressor = ini.GetBoolValue("Bools", "Supressor", Settings::Supressor ? true : false);


}



void TextWithColors2(const char* text) {
	auto& style = ImGui::GetStyle();
	ImVec4 mainTextColor = style.Colors[ImGuiCol_Text];

	// Parse the color from the input string (assuming your format is {RRGGBB}Text)
	char colorCode[7];
	if (sscanf(text, "{%6s}", colorCode) == 1) {
		unsigned int r, g, b;
		sscanf(colorCode, "%2x%2x%2x", &r, &g, &b);
		mainTextColor = ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	}

	// Extract the actual text content after the color code
	const char* actualText = strchr(text, '}') + 1;

	// Black color for the border
	ImVec4 borderColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Offsets for creating a border effect
	float offsets[8][2] = {
		{-1.0f, -1.0f}, {1.0f, -1.0f}, {-1.0f, 1.0f}, {1.0f, 1.0f}, // Corners
		{-1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, -1.0f}, {0.0f, 1.0f}    // Sides
	};

	// Draw text border
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImGui::PushStyleColor(ImGuiCol_Text, borderColor);
	for (int i = 0; i < 8; i++) {
		ImGui::SetCursorScreenPos(ImVec2(pos.x + offsets[i][0], pos.y + offsets[i][1]));
		ImGui::TextUnformatted(actualText);
	}
	ImGui::PopStyleColor();

	// Draw the main text
	ImGui::SetCursorScreenPos(pos);
	ImGui::PushStyleColor(ImGuiCol_Text, mainTextColor);
	ImGui::PushItemWidth(-1); // Make text width fill the available space
	ImGui::TextUnformatted(actualText);
	ImGui::PopItemWidth();
	ImGui::PopStyleColor();
}


std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}




VOID DrawMenu2()
{
	ImGuiIO& Io = ImGui::GetIO();

	// Set the style to remove borders and make the background semi-transparent black
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.7f)); // Adjust alpha value for transparency
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

	ImGui::SetNextWindowSize(ImVec2(150.0f, 180.0f));
	ImGui::GetStyle().ItemSpacing = ImVec2(8, 4);

	static auto FlagsMenu = ImDrawListFlags_AntiAliasedFill | ImDrawListFlags_AntiAliasedLines | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowPos(ImVec2(10, (DX11Window::Height / 2.0f) - 80));
	
	ImGui::Begin("AnimeTone", 0, FlagsMenu);
	{
		if (!Settings::notifysate.empty()) {
			ImGui::InsertNotification({ ImGuiToastType_Info, 3000, Settings::notifysate.c_str()});
			Settings::notifysate = "";
		}

		const float colPos = 220.0f;
		bool P = false;
		ImGui::Text;
		std::string Title;
		Title += "ANIMETONE";
		// Calculate text width and set cursor position
		float windowWidth2 = ImGui::GetWindowSize().x;
		float textWidth2 = ImGui::CalcTextSize(Title.c_str()).x;
		ImGui::SetCursorPosX((windowWidth2 - textWidth2) * 0.4f);

		
		TextWithColors2("{cc99ff} ANIMETONE");
		ImGui::Spacing();
		ImGui::Separator();
		Settings::FightMode ? TextWithColors2("{74ff03}F4   FIGHT MODE") : TextWithColors2("{C0C0C0}F4  FIGHT MODE");
		ImGui::Spacing();
		string bttext = "{74ff03}F5   BULLET TRACK [";
		bttext += to_string(Settings::MaxAimDistence);
		bttext += "]";
		Settings::MagicBullet ? TextWithColors2(bttext.c_str()) : TextWithColors2("{C0C0C0}F5   BULLET TRACK");
		ImGui::Spacing();
		Settings::Legitrack ? TextWithColors2("{74ff03}F6   LEGIT TRACK") : TextWithColors2("{C0C0C0}F6   LEGIT TRACK");
		ImGui::Spacing();
		Settings::Items ? TextWithColors2("{74ff03}F7   ITEMS ESP") : TextWithColors2("{C0C0C0}F7   ITEMS ESP");
		ImGui::Spacing();
		Settings::Vehicle ? TextWithColors2("{74ff03}F8   VEHICLE ESP") : TextWithColors2("{C0C0C0}F8   VEHICLE ESP");
		ImGui::Spacing();
		ImGui::Separator();
		// Centering Aim Text
		std::string aimText;
		if (Settings::Legitrack) {
			aimText = "{C0C0C0}Aim : Legit ";
		}
		else {
			switch (Settings::curraim) {
			case 0: aimText = "{ff0000}Aim : Head "; break;
			case 1: aimText = "{74ff03}Aim : Chest "; break;
			case 2: aimText = "{74ff03}Aim : Pelvis "; break;
			}
		}
		// Calculate text width and set cursor position
		float windowWidth = ImGui::GetWindowSize().x;
		float textWidth = ImGui::CalcTextSize(aimText.c_str()).x;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.8f);

		TextWithColors2(aimText.c_str());

		//ImGui::SetCursorPos(ImVec2(20.f, 200.0f));

		ImGui::End();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
	}

	// Restore styles and handle key events
	ImGui::PopStyleColor(2);  // Pop both the window background and border color
	ImGui::PopStyleVar();     // Pop the window border size

	if (GetAsyncKeyState(VK_F6) & 1) {
		Settings::Legitrack = !Settings::Legitrack;
	}
	if (GetAsyncKeyState(VK_F8) & 1) {
		Settings::Vehicle = !Settings::Vehicle;
	}
	if (GetAsyncKeyState(VK_F7) & 1) {
		Settings::Items = !Settings::Items;
	}
	if (GetAsyncKeyState(VK_F4) & 1) {
		Settings::FightMode = !Settings::FightMode;
	}
	if (GetAsyncKeyState(VK_F5) & 1) {
		Settings::MagicBullet = !Settings::MagicBullet;
	}
	if (GetAsyncKeyState('T') & 1) {
		if (Settings::curraim == 2)
			Settings::curraim = 0;
		else
			Settings::curraim++;
	}
}


// Define the structure to hold weapon settings
struct WeaponSetting {
	const char* name;
	bool* enabled;
	ImVec4* color;
};

// Categorize weapon settings
std::vector<WeaponSetting> ammoSettings = {
	{"762MM", &Settings::a762mm, &Settings::a762mmColor},
	{"556MM", &Settings::a556mm, &Settings::a556mmColor},
	{"9MM", &Settings::a9mm, &Settings::a9mmColor},
	{"45ACP", &Settings::a45ACP, &Settings::a45ACPColor},
	{"12GAUEGE", &Settings::a12Gauege, &Settings::a12GauegeColor},
	{"AWMAMMO", &Settings::AwmAmmo, &Settings::AwmAmmoColor},
	{"AMRAMMO", &Settings::AmrAmmo, &Settings::AmrAmmoColor},
};

std::vector<WeaponSetting> gunSettings = {
	{"Akm", &Settings::Akm, &Settings::AkmColor},
	{"M16A4", &Settings::M16A4, &Settings::M16A4Color},
	{"SCARL", &Settings::SCARL, &Settings::SCARLColor},
	{"M416", &Settings::M416, &Settings::M416Color},
	{"GROZA", &Settings::GROZA, &Settings::GROZAColor},
	{"AUG", &Settings::AUG, &Settings::AUGColor},
	{"QBZ", &Settings::QBZ, &Settings::QBZColor},
	{"M762", &Settings::M762, &Settings::M762Color},
	{"MK47", &Settings::MK47, &Settings::MK47Color},
	{"G36C", &Settings::G36C, &Settings::G36CColor},
	{"HONEY", &Settings::HONEY, &Settings::HONEYColor},
	{"FAMAS", &Settings::FAMAS, &Settings::FAMASColor},
	{"KAR98", &Settings::KAR98, &Settings::KAR98Color},
	{"M24", &Settings::M24, &Settings::M24Color},
	{"AWM", &Settings::AWM, &Settings::AWMColor},
	{"WIN94", &Settings::WIN94, &Settings::WIN94Color},
	{"MOSIN", &Settings::MOSIN, &Settings::MOSINColor},
	{"AMR", &Settings::AMR, &Settings::AMRColor},
	{"SKS", &Settings::SKS, &Settings::SKSColor},
	{"VSS", &Settings::VSS, &Settings::VSSColor},
	{"MINI14", &Settings::MINI14, &Settings::MINI14Color},
	{"MK14", &Settings::MK14, &Settings::MK14Color},
	{"SLR", &Settings::SLR, &Settings::SLRColor},
	{"QBU", &Settings::QBU, &Settings::QBUColor},
	{"MK12", &Settings::MK12, &Settings::MK12Color},
	{"UZI", &Settings::UZI, &Settings::UZIColor},
	{"UMP45", &Settings::UMP45, &Settings::UMP45Color},
	{"VECTOR", &Settings::VECTOR, &Settings::VECTORColor},
	{"THOMPSON", &Settings::THOMPSON, &Settings::THOMPSONColor},
	{"BIZON", &Settings::BIZON, &Settings::BIZONColor},
	{"MP5K", &Settings::MP5K, &Settings::MP5KColor},
	{"P90", &Settings::P90, &Settings::P90Color},
	{"S686", &Settings::S686, &Settings::S686Color},
	{"S1897", &Settings::S1897, &Settings::S1897Color},
	{"S12K", &Settings::S12K, &Settings::S12KColor},
	{"DBS", &Settings::DBS, &Settings::DBSColor},
	{"M1014", &Settings::M1014, &Settings::M1014Color},
	{"NS2000", &Settings::NS2000, &Settings::NS2000Color},
	{"M249", &Settings::M249, &Settings::M249Color},
	{"DP28", &Settings::DP28, &Settings::DP28Color},
	{"MG3", &Settings::MG3, &Settings::MG3Color},
	{"FLARE", &Settings::FLARE, &Settings::FLAREColor},
};

std::vector<WeaponSetting> healthKitSettings = {
	{"MEDKIT", &Settings::MedKit, &Settings::MedKitColor},
	{"FIRSTAIDKIT", &Settings::FirstAidKit, &Settings::FirstAidKitColor},
	{"PAINKILLER", &Settings::Painkiller, &Settings::PainkillerColor},
	{"ENERGYDRINK", &Settings::EnergyDrink, &Settings::EnergyDrinkColor},
	{"ADRENALIN", &Settings::Adrenalin, &Settings::AdrenalinColor},
};

std::vector<WeaponSetting> backpackSettings = {
	{"BAG1", &Settings::Bag1, &Settings::Bag1Color},
	{"BAG2", &Settings::Bag2, &Settings::Bag2Color},
	{"BAG3", &Settings::Bag3, &Settings::Bag3Color},
};

std::vector<WeaponSetting> gearSettings = {
	{"HELMET1", &Settings::Helmet1, &Settings::Helmet1Color},
	{"HELMET2", &Settings::Helmet2, &Settings::Helmet2Color},
	{"HELMET3", &Settings::Helmet3, &Settings::Helmet3Color},
	{"ARMOR1", &Settings::Armor1, &Settings::Armor1Color},
	{"ARMOR2", &Settings::Armor2, &Settings::Armor2Color},
	{"ARMOR3", &Settings::Armor3, &Settings::Armor3Color},
};

std::vector<WeaponSetting> scopeSettings = {
	{"SCOPE_X2", &Settings::Scope_x2, &Settings::Scope_x2Color},
	{"SCOPE_X3", &Settings::Scope_x3, &Settings::Scope_x3Color},
	{"SCOPE_X4", &Settings::Scope_x4, &Settings::Scope_x4Color},
	{"SCOPE_X6", &Settings::Scope_x6, &Settings::Scope_x6Color},
	{"SCOPE_X8", &Settings::Scope_x8, &Settings::Scope_x8Color},
};

std::vector<WeaponSetting> grenadeSettings = {
	{"FRAG", &Settings::FRAG, &Settings::FRAGColor},
	{"SMOKE", &Settings::SMOKE, &Settings::SMOKEColor},
	{"MOLOTOF", &Settings::MOLOTOF, &Settings::MOLOTOFColor},
};

std::vector<WeaponSetting> tokenSettings = {
	{"SHOP_TOKEN", &Settings::ShopToken, &Settings::ShopTokenColor},
	{"MAC", &Settings::ExtendedMac, &Settings::ExtendedMacColor},
	{"Supressor", &Settings::Supressor, &Settings::SupressorColor},
};

// Function to render settings
void RenderSettings(const std::vector<WeaponSetting>& settings) {
	for (const auto& item : settings) {
		ImGui::Checkbox(item.name, item.enabled);
		ImGui::SameLine();
		ImGui::ColorEdit4(("###"+std::string(item.name) + " Color").c_str(), reinterpret_cast<float*>(item.color), ImGuiColorEditFlags_NoInputs);
	}
}



static char sgasg[25] = "";

// Predefined set of bone indices for head, chest, and pelvis
const std::vector<std::pair<int, std::string>> priorityBoneIndices = {
	{5, "Head"},
	{4, "Chest"},
	{1, "Pelvis"}
};

std::string getBoneName(int index) {
	for (const auto& pair : priorityBoneIndices) {
		if (pair.first == index) {
			return pair.second;
		}
	}
	return "Unknown";
}



void DrawImGuiMenu3() {

	//tabs
	ui::tabs = {

	{ ICON_FA_HOME, "      VISUALS", {} },
	{ ICON_FA_CROSSHAIRS, "     BULLETS", {} },
	{ ICON_FA_COG, "  CONFIG", {} },
	{ ICON_FA_INFO_CIRCLE, "      ABOUT", {} }

	};


	//pages
	ui::add_page(0, []() {

		// Begin first group (left side)
		ImGui::BeginGroup();
		{
			ui::begin_child(ICON_FA_HEARTBEAT" ESP", ImVec2(230, -1));
			{
			
				
			
				ImGui::Checkbox("Player Name", &Settings::PlayerName);
				ImGui::SameLine();
				ImGui::ColorEdit4("##Name color", (float*)&Settings::PlayerNameColor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Player Skeleton", &Settings::PlayerSkeleton);
				ImGui::SameLine();
				ImGui::ColorEdit4("##skeletoncolor", (float*)&Settings::PlayerSkeletonColor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Player Line", &Settings::PlayerLine);
				ImGui::SameLine();
				ImGui::ColorEdit4("##Line color", (float*)&Settings::PlayerLineColor, ImGuiColorEditFlags_NoInputs);
				//ImGui::Checkbox("Player Distance", &Settings::PlayerDistance);
				ImGui::Checkbox("Player Health", &Settings::PlayerHealth);
				ImGui::Checkbox("Player Weapon", &Settings::PlayerWeapon);
				//	ImGui::Checkbox("Player Flag", &Settings::PlayerFlag);
				ImGui::Checkbox("Player Box", &Settings::PlayerBox);
				ImGui::SameLine();
				ImGui::ColorEdit4("##Box color", (float*)&Settings::PlayerBoxColor, ImGuiColorEditFlags_NoInputs);

				//ImGui::Checkbox("Player State", &Settings::PlayerState);
				ImGui::Checkbox("Items", &Settings::Items);
				ImGui::Checkbox("Total Enemy", &Settings::TotalEnemy);
				ImGui::Checkbox("Vehicle", &Settings::Vehicle);
				ImGui::SameLine();
				ImGui::ColorEdit4("##Vehicle color", (float*)&Settings::VehicleColor, ImGuiColorEditFlags_NoInputs);

				if (ImGui::Checkbox("Visibility", &Settings::visibilitycheck)) {
					//Data::InjectLibrary();
				}
				ImGui::SameLine();
				ImGui::ColorEdit4("##vis color", (float*)&Settings::visColor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Lootbox", &Settings::Lootbox);
				ImGui::Checkbox("AirDrop", &Settings::AirDrop);
			//	ImGui::Checkbox("Grande Warning", &Settings::GrandeWarning);
				ImGui::Checkbox("Aim Warning", &Settings::AimWarning);

				ImGui::Checkbox("GameInfo", &Settings::GameInfo); // causing ue4 base not found

				ImGui::Checkbox("Zone Prediction", &Settings::Redzone);
				ImGui::Checkbox("Dots", &Settings::Dots);
				ImGui::Checkbox("Radar", &Settings::Radar);
				ImGui::Checkbox("Grenade Path", &Settings::grenadePath);
				ImGui::Checkbox("Chicken Shot", &Settings::sendscreenshot);
			}
			ui::end_child();
		}
		ImGui::EndGroup();

		// Ensure the next element is placed on the same line
		ImGui::SameLine();

		// Begin second group (right side)
		ImGui::BeginGroup();
		{
			ui::begin_child(ICON_FA_TOOLBOX" SIZE SETTINGS", ImVec2(230, -1));
			{
				//ImGui::Spacing();

					// Calculate sizes for slider and expanded clickable area
				ImVec2 sliderSize(50, ImGui::GetTextLineHeight());
				ImVec2 expandedArea(160, ImGui::GetTextLineHeight());

				// Adjust the item width to include the expanded area
				ImGui::PushItemWidth(160 + ImGui::GetStyle().ItemSpacing.x);


				if (Settings::PlayerName) {
					ImGui::Text("Name Size :");
					ImGui::SliderInt("###pname", &Settings::PlayerNameSize, 10, 30);
				}

				if (Settings::PlayerSkeleton) {

					ImGui::Text("Skeleton Thickness :");
					ImGui::SliderFloat("###skethickness", &Settings::skeletonthickness, 0.01f, 15.0f);
				}

				if (Settings::PlayerLine) {

					ImGui::Text("Line Thickness :");
					ImGui::SliderFloat("###thickness", &Settings::linethickness, 0.01f, 15.0f);
				}

				if (Settings::Vehicle) {

					ImGui::Text("Vehicle Size :");
					ImGui::SliderInt("###Vehicle", &Settings::VehicleSize, 10, 30);
				}

				ImGui::PopItemWidth();
			}
			ui::end_child();
		}
		ImGui::EndGroup();
		
		ImGui::SameLine();
	
		ImGui::BeginGroup();
		{
			ui::begin_child(ICON_FA_ADJUST" COLOR SETTINGS", ImVec2(230, -1));
			{
	
				if (Settings::PlayerName) {

					ImGui::Text(" Player Name : ");
					ImGui::Combo("a", &Settings::PlayerLineMode, "Team Id\0Custom Color");
				}
	
				if (Settings::PlayerSkeleton) {
	
					ImGui::Text(" Skeleton : ");
					ImGui::Combo("b", &Settings::PlayerSkeletonMode, "Team Id\0Custom Color");
				}
			}
			ui::end_child();
		}
		ImGui::EndGroup();
		
		if (Settings::Items) {
			ImGui::Spacing();
			ImGui::BeginGroup();
			{
				ui::begin_child(ICON_FA_TOOLBOX " Equipment", ImVec2(230,350));
				{
					RenderSettings(healthKitSettings);
					RenderSettings(backpackSettings);
					RenderSettings(gearSettings);
					RenderSettings(scopeSettings);
					RenderSettings(grenadeSettings);
					RenderSettings(tokenSettings);
				}
				ui::end_child();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				ui::begin_child(ICON_FA_SHIELD_ALT " Weapons", ImVec2(230, 350));
				{

					RenderSettings(gunSettings);
				}
				ui::end_child();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				ui::begin_child(ICON_FA_BOX " Ammunition", ImVec2(230, 350));
				{
					RenderSettings(ammoSettings);
				}
				ui::end_child();
			}
			ImGui::EndGroup();


		}

	});

	ui::add_page(1, []() {

		// Begin first group (left side)
		ImGui::BeginGroup();
		{
			ui::begin_child(ICON_FA_LIST_ALT " SETTINGS", ImVec2(200, -1));
			{
				ImGui::Checkbox("Aim Bot", &Settings::AimBot);
				ImGui::Checkbox("Bullet Track", &Settings::MagicBullet);
				ImGui::Checkbox("Internal Track", &Settings::internalTrack);
				ImGui::Checkbox("Legit Track", &Settings::Legitrack);
				//ImGui::Checkbox("Camera Track", &Settings::Magic360);
				ImGui::Checkbox("AIM Knocked", &Settings::knocked);
				ImGui::Checkbox("Visibility", &Settings::visbulletcheck);
				ImGui::Checkbox("SKIP Bots ", &Settings::SkipBots);
				ImGui::Checkbox("Unlock Limit", &Settings::BypassFovLimit);
				ImGui::Checkbox("Show Fov ", &Settings::FovShow);
				ImGui::Checkbox("Fov Based Tracking ", &Settings::Fovbased);
				ImGui::Checkbox("Peek Detect ", &Settings::peekdetect);
				ImGui::Checkbox("Draw Crosshair ", &Settings::crosshair);
				//	ImGui::Checkbox("BT Logs", &Settings::log);
			}
			ui::end_child();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		// Begin first group (left side)
		ImGui::BeginGroup();
		{
			ui::begin_child(ICON_FA_WRENCH " CONFIGURATION", ImVec2(-1, -1));
			{
				if (ImGui::BeginTabBar("##12"))
				{

					if (ImGui::BeginTabItem(ICON_FA_CIRCLE" Aim Settings"))
					{
						ImGui::Text("Fov Size :");
						ImGui::SameLine();
						ImGui::SliderFloat("###fovFOVsize", &Settings::fovcircleredus, 1.0f, 500.0f);
						ImGui::Text("Fov Color :");
						ImGui::SameLine();
						ImGui::ColorEdit4(" Fov color", (float*)&Settings::FovColor, ImGuiColorEditFlags_NoLabel);

						ImGui::Text("Max Aim Distence");
						ImGui::SameLine();
						ImGui::SliderInt("###MaxAimDistence", &Settings::MaxAimDistence, 1.0f, 400.0f);

						ImGui::Text("Aim Positon :");
						ImGui::SameLine();
						ImGui::Combo(" ", &Settings::curraim, "Head\0Cheast\0Pelvis");

						ImGui::EndTabItem();
					}


					if (Settings::AimBot) {
						if (ImGui::BeginTabItem(ICON_FA_CIRCLE" Aimbot"))
						{
							ImGui::Text("Aimbot Key :");
							ImGui::SameLine();
							ImGui::Hotkey("##AimbotKey ", &Settings::AimKey, ImVec2(180.0f, 24));
							ImGui::Text("Aim Speed :");
							ImGui::SameLine();
							ImGui::SliderFloat("###aimspped", &Settings::AimSpeed, 0.0f, 30.0f);

							ImGui::Text("Macro Speed :");
							ImGui::SameLine();
							ImGui::SliderInt("##macro", &Settings::macroval, 0, 50); // Adjust range as needed

							ImGui::Text("Aim Mode :");
							ImGui::SameLine();
							ImGui::Combo(" ", &Settings::aimbotmode, "Crosshair\0Locked ON");

							ImGui::EndTabItem();
						}
					}

					if (Settings::MagicBullet) {
						if (ImGui::BeginTabItem(ICON_FA_CIRCLE" BulletTrack"))
						{
							ImGui::Text("Bullet Hit Percentage :");
							ImGui::SliderFloat("##BThit", &Settings::percentage, 0.0f, 1.0f, "%.2f");
							ImGui::EndTabItem();

							ImGui::Text("Screen Cordinations :");
							ImGui::SameLine();
							ImGui::Combo("ascreen", &Settings::bulletrackMode, "External Calculation\0Internal Calculation");

							ImGui::Text("Prediction :");
							ImGui::SameLine();
							ImGui::Combo("aprediction", &Settings::prediction, "Kinematic Prediction\0Sphere-Line Prediction");
						}
					}

					if (Settings::Legitrack) {
						if (ImGui::BeginTabItem(ICON_FA_CIRCLE" LegitTrack"))
						{

							ImGui::Checkbox("Bone Priority", &Settings::isPrioritySet);

							if (Settings::isPrioritySet) {
								// Dropdown menu for bone priority options

									// Show current weight (optional)
								ImGui::Text("Current Weight: %d", Settings::weight);

								ImGui::SliderInt("##Weight", &Settings::weight, 1, 10); // Adjust range as needed



								if (ImGui::BeginCombo("Select Bone Priority", Settings::currentBoneIndex == -1 ? "None" : getBoneName(Settings::currentBoneIndex).c_str())) {
									for (int i = 0; i < priorityBoneIndices.size(); ++i) {
										bool isSelected = (Settings::currentBoneIndex == priorityBoneIndices[i].first);
										if (ImGui::Selectable(priorityBoneIndices[i].second.c_str(), isSelected)) {
											Settings::currentBoneIndex = priorityBoneIndices[i].first;
										}
									}
									ImGui::EndCombo();
								}
							}

							ImGui::EndTabItem();
						}
					}

					ImGui::EndTabBar();
				}
			}
			ui::end_child();
		}
		ImGui::EndGroup();

	});

	ui::add_page(2, []() {

		// Begin first group (left side)
		ImGui::BeginGroup();
		{
		
				
			ui::begin_child(ICON_FA_COG " Configuration", ImVec2(230, 250));
			{
					
					ImGui::Text("Game FPS  |  FPS: ");
					ImVec2 sliderSize(50, ImGui::GetTextLineHeight());
					ImVec2 expandedArea(160, ImGui::GetTextLineHeight());

					// Adjust the item width to include the expanded area
					ImGui::PushItemWidth(160 + ImGui::GetStyle().ItemSpacing.x);
					ImGui::SliderInt("####1", &Settings::UpdateFps, 11, 100, "%.0fms");
					ImGui::PopItemWidth();
					if (ImGui::Button("Save menu", { 173.f,21.f }))
					{
						//Settings::btrefreshstatus = "Settings Have Been Saved!";
						Save_Settings("C:\\AnimeTone_Config.ini");
						ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Settings Have Been Saved!" });

					}
					
					if (ImGui::Button("Load menu", { 173.f,21.f }))
					{
						//Settings::btrefreshstatus = "Setttings Have Been Loaded!";
						Load_Settings("C:\\AnimeTone_Config.ini");
						ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Setttings Have Been Loaded!" });

					}

			}
			ui::end_child();
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		{


			ui::begin_child(ICON_FA_COG " Memory", ImVec2(230, 250));
			{
				ImGui::Checkbox("Car Sex", &Settings::carsex);

				ImGui::Hotkey("##carsexkey ", &Settings::carsexkey, ImVec2(180.0f, 24));

			}
			ui::end_child();
		}
		ImGui::EndGroup();



	});

	ui::add_page(3, []() {
		// Begin first group (left side)
		ImGui::BeginGroup();
		{
			ui::begin_child(ICON_FA_INFO_CIRCLE " About Us", ImVec2(-1, -1));
			{
				ImGui::TextWrapped("Welcome to AnimeTone!\n\n"
					"At AnimeTone, we specialize in developing and selling high-quality game software. "
					"Our mission is to deliver the best gaming experiences to our customers through innovative and engaging products.\n\n"
					"Founded by a team of passionate gamers and software developers, AnimeTone strives to stay at the forefront of the gaming industry. "
					"We are committed to excellence and dedicated to pushing the boundaries of what is possible in game development.\n\n"
					"Thank you for choosing AnimeTone. We look forward to serving you with our exceptional game software.\n\n"
					);

				ImGui::Spacing();

				ImGui::Text("Follow us on:");
				ImGui::BulletText("Discord:");
				//ImGui::SameLine();
				HyperLink("https://discord.gg/TPQjcZzFcf", "https://discord.gg/TPQjcZzFcf", 1, 1);

				ImGui::BulletText("Telegram:");
				//ImGui::SameLine();
				HyperLink("https://t.me/animetonee", "https://t.me/animetonee", 1, 1);

				ImGui::Spacing();

				ImGui::Separator();
				ImGui::Spacing();

				ImGui::Text("Expiry Date:");
				ImGui::SameLine();

				for (int i = 0; i < KeyAuthApp.user_data.subscriptions.size(); i++) {
					auto sub = KeyAuthApp.user_data.subscriptions.at(i);
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", tm_to_readable_time(timet_to_tm(string_to_timet(sub.expiry))).c_str());
				}
				


				ImGui::Text("Current Version:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", exeversion);

				ImGui::Spacing();
				


			}
			ui::end_child();
		}
		ImGui::EndGroup();
	});

	//render everything here
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	ImGui::Begin("UI", 0, ImGuiWindowFlags_NoDecoration);
	{
		ImGui::PopStyleVar();
		ImGui::SetWindowSize(ui::size);

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, GImGui->Style.WindowRounding);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		ImGui::BeginChild("header", { -1, 60 }, ImGuiWindowFlags_AlwaysAutoResize);
		{
			for (int i = 0; i < ui::tabs.size(); ++i) {
				ui::tab(i);
				ImGui::SameLine(0, 0);
			}
		}
		ImGui::EndChild();
		ImGui::PopStyleVar(2);

		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ui::content_anim);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 20, 20 });
		ImGui::BeginChild("content", ImVec2(-1, -1), 0, ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
		{
			ImGui::PopStyleVar();

			ui::render_page();
		}
		ImGui::EndChild();

		ImGui::PopStyleVar();
	}

	ImGui::End();

	ui::handle_alpha_anim();
}


// Method to display the game information window
void DisplayGameInfoWindow() {
	ImGui::SetNextWindowSize(ImVec2(250.0f, 70.0f));
	ImGuiIO& io = ImGui::GetIO();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f)); // Semi-transparent black background
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // Remove the border

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.65, io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.15f, 0.1f));

	if (ImGui::Begin("gameInfo", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar)) {
		TextWithColors(("{ffffff} Alive Players : {05d5ff} " + std::to_string(Settings::AlivePlayers)).c_str());
		ImGui::SameLine();
		TextWithColors(("{ffffff} With Alive Teams : {05d5ff} " + std::to_string(Settings::AliveTeams)).c_str());

		// Uncomment the following line if Match Real Players needs to be displayed
		// TextWithColors(("{ffffff} Match Real Players : {05d5ff} " + std::to_string(settings.RealPls)).c_str());

		TextWithColors(("{ffffff} Zone ID : {05d5ff} " + std::to_string(Settings::ZoneID)).c_str());
		ImGui::SameLine();
		TextWithColors(("{ffffff} Game ID : {05d5ff} " + std::to_string(Settings::GameID)).c_str());
		
		TextWithColors(("{ffffff} My Team : {05d5ff} " + std::to_string(Settings::MyTeamID)).c_str());
		ImGui::SameLine();
		TextWithColors(("{ffffff} Elapsed Time : {05d5ff} " + std::to_string(Settings::TimeRemind)).c_str());

		ImGui::End();
	}
	// Restore styles
	ImGui::PopStyleVar();    // Pop the window border size
	ImGui::PopStyleColor();  // Pop the window background color
}

char CharKey[60] = "";

bool checking;
inline bool FileExist(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
void Esp::LoadConfig(std::string Path) {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	//	if (rc < 0) { std::cout << "File not found"; };
	if (FileExist(Path))
	{
		bool State = ini.GetBoolValue("Key", "UserKeyState");
		if (State == true)
		{
			std::string Key = ini.GetValue("Key", "UserKey");
			if (Key != "")
			{
				strcpy(CharKey, Key.c_str());
			}

		}

	}

}
void WriteConfig(std::string Path, std::string Key, bool State) {
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile(Path.c_str());
	if (rc < 0) {
		//	std::cout << "File not found";
	};
	if (State == true)
	{
		ini.SetBoolValue("Key", "UserKeyState", true);
	}
	else
	{
		ini.SetBoolValue("Key", "UserKeyState", false);
	}
	ini.SetValue("Key", "UserKey", Key.c_str());

	ini.SaveFile(Path.c_str());
}

void Loginn() {
	//LOGIN CODES . SET UR KEYAUTH AND THEN UN COMMAND THIS CODES
	KeyAuthApp.init();
	KeyAuthApp.license(CharKey);

	if (!KeyAuthApp.response.success) {
		MessageBoxA(0, KeyAuthApp.response.message.c_str(), "Error", MB_ICONERROR);
		Sleep(1500);
		std::exit(0);
	}

	updater.updateLoader();

	Settings::Login = true;
	checking = false;
	WriteConfig("C:\\AnimeTone.lic", CharKey, true);
 
	//auto result = KeyAuthApp.download("666779");
	//if (!KeyAuthApp.response.success) Settings::notifysate = "Unable to download external librarry !";
	//std::ofstream file("C:\\libhax.so", std::ios::binary);
	//file.write(reinterpret_cast<const char*>(result.data()), result.size());
	//if(!file) Settings::notifysate = "Unable to place external librarry !";
}
std::string random_string1(int len)
{
	std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);
	return str.substr(0, len);
}
void getlink(string link) {
	IStream* stream;
	HRESULT result = URLOpenBlockingStream(0, (link.c_str()), &stream, 0, 0);
	if (result != 0)
	{
		return;
	}
	char buffer[100];
	unsigned long bytesRead;
	std::stringstream ss;
	stream->Read(buffer, 100, &bytesRead);
	while (bytesRead > 0U)
	{
		ss.write(buffer, (long long)bytesRead);
		stream->Read(buffer, 100, &bytesRead);
	}
	stream->Release();
}

VECTOR3 Subtrac(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result;
	Result.X = Src.X - Dst.X;
	Result.Y = Src.Y - Dst.Y;
	Result.Z = Src.Z - Dst.Z;
	return Result;
}

float Magnitud(VECTOR3 Vec)
{
	return sqrtf(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z);
}

float GetDist(VECTOR3 Src, VECTOR3 Dst)
{
	VECTOR3 Result = Subtrac(Src, Dst);
	return Magnitud(Result);
}

ImColor GenerateTeamColor(int teamId) {
	int r = (teamId * 61) % 256;  // Adjusted Red component
	int g = (teamId * 113) % 256; // Adjusted Green component
	int b = (teamId * 157) % 256; // Adjusted Blue component

	// Ensure the color is extremely deep and vibrant by adding an even higher base value
	r = (r < 220) ? r + 36 : r;  // Ensuring a higher minimum value for deeper colors
	g = (g < 220) ? g + 36 : g;  // Ensuring a higher minimum value for deeper colors
	b = (b < 220) ? b + 36 : b;  // Ensuring a higher minimum value for deeper colors

	return ImColor(r, g, b, 255); // Alpha component set to 255 for full opacity
}


float CalculateFontSize(float distance, float minFontSize, float maxFontSize, float maxDistance) {
	// Calculate the scaling factor
	float scalingFactor = 1.0f - (distance / maxDistance);
	scalingFactor = std::clamp(scalingFactor, 0.0f, 1.0f); // Clamp between 0 and 1

	// Calculate the new font size
	return minFontSize + (scalingFactor * (maxFontSize - minFontSize));
}

// Function to get the precomputed color for a team
ImColor GetTeamColor(int teamId) {
	return GenerateTeamColor(teamId);
}

int teamids;
ImVec4 linescolors;// = { 1.0f,1.0f,1.0f,1.0f };
ImVec4 salahcolor;
int botcount;
int playercount;
D3DMATRIX Esp::ViewMatrix;


std::string playerstatus2(int GetEnemyState)
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

ImVec4 GetteamColor(int teamids) {
	ImVec4 color;

	switch (teamids) {
	case 1:
		color = { 1.000f, 0.033f, 0.129f, 1.000f };
		break;
	case 2:
		color = { 1.000f, 1.000f, 0.000f, 1.000f };
		break;
	case 3:
		color = { 0.866f, 0.128f, 0.081f, 1.000f };
		break;
	case 4:
		color = { 0.844f, 0.066f, 1.000f, 1.000f };
		break;
	case 5:
		color = { 0.737f, 1.000f, 0.000f, 1.000f };
		break;
	case 6:
		color = { 0.000f, 1.000f, 0.964f, 1.000f };
		break;
	case 7:
		color = { 0.610f, 0.190f, 1.000f, 1.000f };
		break;
	case 8:
		color = { 1.000f, 0.100f, 0.401f, 1.000f };
		break;
	case 9:
		color = { 0.126f, 0.430f, 1.000f, 1.000f };
		break;
	case 10:
		color = { 0.033f, 0.696f, 1.000f, 1.000f };
		break;
	case 11:
		color = { 0.033f, 1.000f, 0.952f, 1.000f };
		break;
	case 12:
		color = { 0.033f, 1.000f, 0.535f, 1.000f };
		break;
	case 13:
		color = { 0.044f, 1.000f, 0.033f, 1.000f };
		break;
	case 14:
		color = { 0.428f, 1.000f, 0.033f, 1.000f };
		break;
	case 15:
		color = { 0.749f, 1.000f, 0.033f, 1.000f };
		break;
	case 16:
		color = { 0.941f, 1.000f, 0.033f, 1.000f };
		break;
	case 17:
		color = { 1.000f, 0.866f, 0.033f, 1.000f };
		break;
	case 18:
		color = { 1.000f, 0.642f, 0.033f, 1.000f };
		break;
	case 19:
		color = { 1.000f, 0.386f, 0.033f, 1.000f };
		break;
	case 20:
		color = { 1.000f, 0.033f, 0.033f, 1.000f };
		break;
	case 21:
		color = { 0.126f, 0.430f, 0.670f, 1.000f };
		break;
	case 22:
		color = { 0.639f, 0.879f, 0.008f, 1.000f };
		break;
	case 23:
		color = { 1.000f, 0.859f, 0.251f, 1.000f };
		break;
	case 24:
		color = { 0.053f, 0.355f, 1.000f, 1.000f };
		break;
	case 25:
		color = { 0.802f, 0.267f, 0.077f, 1.000f };
		break;
	case 26:
		color = { 0.129f, 0.774f, 0.986f, 1.000f };
		break;
	case 27:
		color = { 0.168f, 0.792f, 0.792f, 1.000f };
		break;
	case 28:
		color = { 1.000f, 0.237f, 0.945f, 1.000f };
		break;
	case 29:
		color = { 0.973f, 0.033f, 1.000f, 1.000f };
		break;
	case 30:
		color = { 0.033f, 0.375f, 1.000f, 1.000f };
		break;
	case 31:
		color = { 0.941f, 0.196f, 0.172f, 1.000f };
		break;
	case 32:
		color = { 0.000f, 0.541f, 0.293f, 1.000f };
		break;
	case 33:
		color = { 0.805f, 0.890f, 0.039f, 1.000f };
		break;
	case 34:
		color = { 0.466f, 0.674f, 0.188f, 1.000f };
		break;
	case 35:
		color = { 0.839f, 0.330f, 0.266f, 1.000f };
		break;
	case 36:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 37:
		color = { 0.678f, 0.847f, 0.902f, 1.000f };
		break;
	case 38:
		color = { 1.000f, 0.894f, 0.882f, 1.000f };
		break;
	case 39:
		color = { 0.929f, 0.510f, 0.933f, 1.000f };
		break;
	case 40:
		color = { 0.596f, 0.984f, 0.596f, 1.000f };
		break;
	case 41:
		color = { 0.333f, 0.420f, 0.184f, 1.000f };
		break;
	case 42:
		color = { 0.800f, 0.600f, 0.600f, 1.000f };
		break;
	case 43:
		color = { 1.000f, 0.388f, 0.278f, 1.000f };
		break;
	case 44:
		color = { 0.800f, 0.361f, 0.361f, 1.000f };
		break;
	case 45:
		color = { 0.961f, 0.961f, 0.863f, 1.000f };
		break;
	case 46:
		color = { 0.000f, 0.000f, 0.502f, 1.000f };
		break;
	case 47:
		color = { 0.502f, 0.000f, 0.000f, 1.000f };
		break;
	case 48:
		color = { 0.502f, 0.502f, 0.000f, 1.000f };
		break;
	case 49:
		color = { 0.000f, 0.502f, 0.502f, 1.000f };
		break;
	case 50:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 51:
		color = { 0.184f, 0.310f, 0.310f, 1.000f };
		break;
	case 52:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	case 53:
		color = { 0.000f, 1.000f, 1.000f, 1.000f };
		break;
	case 54:
		color = { 1.000f, 0.647f, 0.000f, 1.000f };
		break;
	case 55:
		color = { 0.647f, 0.165f, 0.165f, 1.000f };
		break;
	case 56:
		color = { 0.000f, 0.502f, 0.502f, 1.000f };
		break;
	case 57:
		color = { 0.502f, 0.502f, 0.000f, 1.000f };
		break;
	case 58:
		color = { 0.502f, 0.502f, 1.000f, 1.000f };
		break;
	case 59:
		color = { 0.729f, 0.333f, 0.827f, 1.000f };
		break;
	case 60:
		color = { 0.333f, 0.420f, 0.184f, 1.000f };
		break;
	case 61:
		color = { 0.255f, 0.412f, 0.882f, 1.000f };
		break;
	case 62:
		color = { 0.000f, 0.392f, 0.000f, 1.000f };
		break;
	case 63:
		color = { 0.502f, 0.000f, 0.000f, 1.000f };
		break;
	case 64:
		color = { 0.000f, 0.333f, 0.000f, 1.000f };
		break;
	case 65:
		color = { 0.333f, 0.000f, 0.333f, 1.000f };
		break;
	case 66:
		color = { 0.502f, 0.502f, 1.000f, 1.000f };
		break;
	case 67:
		color = { 0.333f, 0.333f, 0.000f, 1.000f };
		break;
	case 68:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 69:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	case 70:
		color = { 0.000f, 1.000f, 1.000f, 1.000f };
		break;
	case 71:
		color = { 1.000f, 0.647f, 0.000f, 1.000f };
		break;
	case 72:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 73:
		color = { 0.333f, 0.333f, 0.333f, 1.000f };
		break;
	case 74:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	case 75:
		color = { 1.000f, 0.714f, 0.757f, 1.000f };
		break;
	case 76:
		color = { 0.255f, 0.412f, 0.882f, 1.000f };
		break;
	case 77:
		color = { 0.333f, 0.420f, 0.184f, 1.000f };
		break;
	case 78:
		color = { 0.255f, 0.412f, 0.882f, 1.000f };
		break;
	case 79:
		color = { 0.000f, 0.502f, 0.502f, 1.000f };
		break;
	case 80:
		color = { 0.502f, 0.502f, 0.000f, 1.000f };
		break;
	case 81:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 82:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	case 83:
		color = { 1.000f, 0.714f, 0.757f, 1.000f };
		break;
	case 84:
		color = { 0.255f, 0.412f, 0.882f, 1.000f };
		break;
	case 85:
		color = { 0.333f, 0.420f, 0.184f, 1.000f };
		break;
	case 86:
		color = { 0.502f, 0.000f, 0.000f, 1.000f };
		break;
	case 87:
		color = { 0.000f, 0.333f, 0.000f, 1.000f };
		break;
	case 88:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 89:
		color = { 0.333f, 0.333f, 0.000f, 1.000f };
		break;
	case 90:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	case 91:
		color = { 0.255f, 0.412f, 0.882f, 1.000f };
		break;
	case 92:
		color = { 0.333f, 0.420f, 0.184f, 1.000f };
		break;
	case 93:
		color = { 0.502f, 0.000f, 0.000f, 1.000f };
		break;
	case 94:
		color = { 0.502f, 0.502f, 0.000f, 1.000f };
		break;
	case 95:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 96:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	case 97:
		color = { 0.000f, 0.502f, 0.502f, 1.000f };
		break;
	case 98:
		color = { 1.000f, 0.647f, 0.000f, 1.000f };
		break;
	case 99:
		color = { 0.502f, 0.000f, 0.502f, 1.000f };
		break;
	case 100:
		color = { 0.502f, 0.502f, 0.502f, 1.000f };
		break;
	default:
		color = GetTeamColor(teamids);
		break;
	}

	return color;
}




// Function to update grenade paths
void UpdateGrenadePaths() {
	// Clear the set of active grenades
	activeGrenades.clear();

	// Update paths and track active grenades
	for (Item& item : Data::ItemList) {
		if (item.Name == "Frag" || item.Name == "Smoke" || item.Name == "Molotof" || item.Name == "Burn") {
			const Item* grenadePointer = &item;
			if (grenadePaths.find(grenadePointer) == grenadePaths.end()) {
				// Initialize a new path for a new grenade
				grenadePaths[grenadePointer] = std::vector<VECTOR3>();
			}
			grenadePaths[grenadePointer].push_back(item.Position);
			activeGrenades.insert(grenadePointer);
		}
	}

	// Remove paths for grenades that are no longer active
	for (auto it = grenadePaths.begin(); it != grenadePaths.end(); ) {
		if (activeGrenades.find(it->first) == activeGrenades.end()) {
			it = grenadePaths.erase(it); // Remove the path and get the next iterator
		}
		else {
			++it;
		}
	}
}

// Function to draw grenade paths
void DrawGrenadePaths(const D3DMATRIX& ViewMatrix) {
	for (const auto& entry : grenadePaths) {
		const std::vector<VECTOR3>& path = entry.second;
		VECTOR3 screenStart, screenEnd;
		int distanceStart, distanceEnd;

		for (size_t i = 1; i < path.size(); ++i) {
			// Convert world positions to screen coordinates
			if (Algorithm::WorldToScreen(path[i - 1], screenStart, &distanceStart, ViewMatrix) &&
				Algorithm::WorldToScreen(path[i], screenEnd, &distanceEnd, ViewMatrix)) {
				// Draw a line on the screen
				DX11::ImGui_DX11::DrawLine(screenStart.X, screenStart.Y, screenEnd.X, screenEnd.Y, DX11::ImGui_DX11::Color::White, 2.0f); // White color
			}
		}
	}
}



void DrawBlinkingCircle(float x, float y, bool isAimingAtMe) {
	// Define blinking colors

	static const ImVec4 blinkingColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // Red color (example)
	static const ImVec4 defaultColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // Default white color

	// Define blinking interval (in frames or time)
	static const int blinkIntervalFrames = 15;  // Example: Change color every 30 frames

	// Static variables for optimization
	static int blinkCounter = 0;
	static bool isBlinkColorGreen = false;  // Start with default color

	// Update logic
	blinkCounter = (blinkCounter + 1) % blinkIntervalFrames;
	if (blinkCounter == 0) {
		isBlinkColorGreen = !isBlinkColorGreen;  // Toggle between colors every blinkIntervalFrames
	}

	// Determine current color based on the toggle state and aiming status
	ImVec4 currentColor = isAimingAtMe && isBlinkColorGreen ? blinkingColor : defaultColor;

	// Draw circle with the current color
	DX11::ImGui_DX11::DrawCircle(x, y, 5.0f, currentColor, 5.0f);
}



VOID DrawFilledUpwardArrowWithBorder(FLOAT X, FLOAT Y, FLOAT Size, ImColor fillColor, ImColor borderColor, FLOAT borderThickness, FLOAT animationOffset)
{
	// Calculate the vertices of the arrow with animation offset
	FLOAT halfSize = Size / 2.0f;
	FLOAT arrowHeight = Size;

	ImVec2 p1 = ImVec2(X, Y + arrowHeight - animationOffset);    // Bottom vertex of the arrow with animation offset
	ImVec2 p2 = ImVec2(X - halfSize, Y - animationOffset);       // Top-left vertex of the arrow with animation offset
	ImVec2 p3 = ImVec2(X + halfSize, Y - animationOffset);       // Top-right vertex of the arrow with animation offset

	// Get the ImGui drawing context
	ImDrawList* pImGuiDraw = ImGui::GetBackgroundDrawList();

	// Draw the filled triangle forming the arrow
	pImGuiDraw->AddTriangleFilled(p1, p2, p3, fillColor);

	// Draw the border lines on the edges of the triangle
	pImGuiDraw->AddLine(p1, p2, borderColor, borderThickness);
	pImGuiDraw->AddLine(p2, p3, borderColor, borderThickness);
	pImGuiDraw->AddLine(p3, p1, borderColor, borderThickness);
}



// Helper function to interpolate between two colors
ImU32 InterpolateColor(const ImVec4& color1, const ImVec4& color2, float factor) {
	ImVec4 result = {
		color1.x + (color2.x - color1.x) * factor,
		color1.y + (color2.y - color1.y) * factor,
		color1.z + (color2.z - color1.z) * factor,
		color1.w + (color2.w - color1.w) * factor
	};
	return ImGui::ColorConvertFloat4ToU32(result);
}

template <typename T>
T myespMax(T a, T b) {
	return (a > b) ? a : b;
}

template <typename T>
T myespMin(T a, T b) {
	return (a < b) ? a : b;
}


VOID Esp::EspThread()
{
	InitImages();

	VECTOR3 Screen;
	INT Distance;
	INT EnemyCount;

	VECTOR3 HeadPos;
	VECTOR2 Head;
	VECTOR2 Chest;
	VECTOR2 Pelvis;
	VECTOR2 lSholder;
	VECTOR2 rSholder;
	VECTOR2 lElbow;
	VECTOR2 rElbow;
	VECTOR2 lWrist;
	VECTOR2 rWrist;
	VECTOR2 lThigh;
	VECTOR2 rThigh;
	VECTOR2 lKnee;
	VECTOR2 rKnee;
	VECTOR3 LeftLeg;
	VECTOR3 RightLeg;
	VECTOR2 lAnkle;
	VECTOR2 rAnkle;
	std::string temp = "";
	std::string dist = "";
	string Text = "";
	string weapon = "";
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	LoadConfig("C:\\AnimeTone.lic");


	while (true)
	{

		DX11::BeginDraw();
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();


		if (Settings::ShowMenu)
		{

			if (!Settings::Login)
			{
				ImGuiIO& Io = ImGui::GetIO();
				static auto loginn2 = ImDrawListFlags_AntiAliasedFill | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize;
				ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
				if (ImGui::Begin("AnimeTone VIP HACK", 0, loginn2))
				{

					ImGui::SetCursorPosX({ 8.f });
					ImGui::Text("Key:");
					ImGui::SameLine();
					ImGui::PushItemWidth(327);
					ImGui::InputTextWithHint(("###Key"), ("Key"), CharKey, IM_ARRAYSIZE(CharKey), ImGuiInputTextFlags_Password);
					ImGui::Spacing();
					ImGui::SetCursorPosX({ 8.f });
					if (ImGui::Button("Check", { 387.5f,22.0f }))
					{
						if (!checking) {
							thread(Loginn).detach();
							checking = true;
						}
					}

					if (checking) {
						ImGui::Text("Checking Key ...");
					}

					ImGui::End();
				}

			}
			else {

				

				//	DrawManu();
					DrawImGuiMenu3();

				//	DrawMenuAndTabs();

			}
		}
		if (Settings::Login) {

		//	g_Discord->Update();

			if (Settings::ShowMenu2) {
				DrawMenu2();
			}
			if (Data::InLobby)
				Settings::GameState = "In Lobby";
			else
				Settings::GameState = "Player Alive : " + std::to_string(Settings::AlivePlayers) + "   Team Alive : " + std::to_string(Settings::AliveTeams);

			if (Settings::TotalEnemy)
			{
				if(!Data::InLobby)
				{
					if (Data::AActorList.size() != 0)
					{

						botcount = 0;
						playercount = 0;
						for (int i = 0; i < Data::AActorList.size(); i++)
						{
							if (Data::AActorList[i].IsDead == false) {
								if (Data::AActorList[i].Name == "BOT")
								{
									botcount = botcount + 1;
								}
								else
								{
									playercount = playercount + 1;
								}
							}
						}


						ImGui::SetNextWindowSize(ImVec2(158.0f, 30.0f));

						ImGuiIO& Io = ImGui::GetIO();


						ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.8f, 0.6f, 1.0f, 1.0f));

						// Set background color to semi-transparent
//						ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f)); // Adjust the last value for transparency (0.0f is fully transparent, 1.0f is fully opaque)

						//ImGui::SetNextWindowSize(ImVec2(400.0f, 115.0f));
						ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));

						if (ImGui::Begin("clear", 0, Flags21))
						{
						//	int allplayerCount = botcount + playercount;
				
							Text = "  ";
							Text.append(ICON_FA_MALE" Player : " + (std::to_string(playercount)) + "  ");
							ImGui::Text(Text.c_str());
							ImGui::SameLine();
							Text = (ICON_FA_USER" Bot : " + (std::to_string(botcount)));

							ImGui::Text(Text.c_str());
							ImGui::End();
						}
						ImGui::PopStyleColor();
					}
					else
					{


						ImGui::SetNextWindowSize(ImVec2(175.0f, 30.0f));

						ImGuiIO& Io = ImGui::GetIO();
						ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.8f, 0.6f, 1.0f, 1.0f));

						//ImGui::SetNextWindowSize(ImVec2(400.0f, 115.0f));
						ImGui::SetNextWindowPos(ImVec2(Io.DisplaySize.x * 0.5f, Io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.1f));
						if (ImGui::Begin("clear", 0, Flags21))
						{
							//Text = "Total Enemies Around : 0";
						//	ImGui::Text(Text.c_str());
							TextWithColors("  {C0C0C0}NO ONE IS     {cc99ff} NEAR  TO YOU ");
							ImGui::End();
						}
						ImGui::PopStyleColor();

					}
				}
			}
			if (!Data::InLobby) {
				if (Settings::GameInfo)
				{
					DisplayGameInfoWindow();
				}

				ViewMatrix = Utility::ReadMemoryEx<D3DMATRIX>(Utility::ReadMemoryEx<DWORD>(Utility::ReadMemoryEx<DWORD>(Data::ViewMatrixBase) + 0x20) + 0x200);

				for (AActor& AActor : Data::AActorList)
				{
				//	linescolors = ImVec4(sin(5.f * teamids + 0.f) * 127 + 128 / 255.0f, sin(5.f * teamids + ((2.f * 3.14159265358979323846) / 3)) * 127 + 128 / 255.0f, sin(5.f * teamids + ((4.f * 3.14159265358979323846) / 3)) * 127 + 128 / 255.0f, 255 / 255.0f);

					//linescolors = GetTeamColor(AActor.TeamId);
					linescolors = GetteamColor(AActor.TeamId);
					//ImVec2 screenSize(1280, 720); // Example screen size, adjust as needed

					if (Settings::Dots)
				    {
				    
				    	salahcolor = linescolors;
				    	float S_height = DX11Window::Height;
				    	float S_width = DX11Window::Width;
				    	bool shit = false;
				    	VECTOR3 EntityPos = Algorithm::WorldToRadar(/*Data::CameraCache.POV.Rotation.Yaw*/ GetMyRot().Yaw, AActor.Position, /*Data::CameraCache.POV.Location*/ GetMyLoc(), NULL, NULL, Algorithm::ToVECTOR3(S_width, S_height, 0), shit);
				    
				    	int x, y;
				    	x = EntityPos.X;
				    	y = EntityPos.Y;
				    
				    	auto angle = VECTOR3();
				    	VECTOR3 temmp = Algorithm::ToVECTOR3((float)(S_width / 2) - x, (float)(S_height / 2) - y, 0.f);
				    
				    	Algorithm::VectorAnglesRadar(temmp, angle);
				    
				    	const auto angle_yaw_rad = DEG2RAD(angle.Y + 180.f);
				    	const auto new_point_x = (S_width / 2) + (Settings::fovcircleredus ) / 2 * 3 * cosf(angle_yaw_rad);
				    	const auto new_point_y = (S_height / 2) + (Settings::fovcircleredus ) / 2 * 3 * sinf(angle_yaw_rad);
				
				       if(AActor.isAimingAtMe) {

							DrawBlinkingCircle(new_point_x, new_point_y, AActor.isAimingAtMe);

						} else {

					        DX11::ImGui_DX11::DrawCircle(new_point_x, new_point_y, 5, linescolors, 5);

				       	}
				    }
				    if (Settings::Radar)
				    {
				    		DrawRadarHUD(GetMyRot(), AActor, Distance, 20, 50, 100, 200, linescolors);
				    }

					if (Settings::crosshair) {

						//drawing crosshair
						float screenWidth = (float)DX11Window::Width;
						float screenHeight = (float)DX11Window::Height;
						float centerX = screenWidth / 2.0f;
						float centerY = screenHeight / 2.0f;

						float crosshairLength = 20.0f; // Length of crosshair lines
						float crosshairThickness = 2.0f; // Thickness of crosshair lines
						ImColor crosshairColor = ImColor(255, 0, 0); // Red color
						DrawCrosshair(centerX, centerY, crosshairLength, crosshairThickness, crosshairColor);

					}

					if (!Algorithm::WorldToScreenPlayer(AActor.Position, Screen, &Distance, ViewMatrix)) {

						continue;
					}
					if (Distance < 400 && Distance > -1 && AActor.TeamId > 0)
					{
						if (Distance > 500 || Screen.Z < 0.001f || AActor.IsDead) continue;
					//	temp = playerstatus2(AActor.status);
					//	temp = AActor.Name.c_str();
					//	string TemID = std::to_string(teamids) + ". ";
						string HeadTxt = AActor.weapon;
						string RootText ="[ "+ to_string(AActor.TeamId) + " ] " + AActor.Name;
						string RootText2 = to_string(Distance) + "M";
						//string RootText3 = "[ KILLS : " + to_string(AActor.kills) + " ]";
					//	temp = to_string(AActor.TeamId) + " | " + AActor.Name.c_str();

						float MinFontSize = 14.0f;
						float MaxFontSize = Settings::PlayerNameSize; // Maximum font size
						float MaxDistance = 400.0f; // Example maximum distance

						// Calculate the new font size based on the distance
						float nameFontSize = CalculateFontSize(Distance, MinFontSize, MaxFontSize, MaxDistance);
						

						if (Settings::PlayerWeapon)
						{


							if (AActor.Health <= 0)
							{
								if (AActor.IsBot) {
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, HeadTxt, Screen.X - 2, Screen.Y - 18, DX11::ImGui_DX11::Color::Green, true);
								}
								else {
								//	DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Settings::PlayerNameSize, TemID, Screen.X - 50, Screen.Y - 50, DX11::ImGui_DX11::Color::Red, false);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, nameFontSize, HeadTxt, Screen.X - 4, Screen.Y - 18, DX11::ImGui_DX11::Color::Red, true);
								}
								
							}
							else
							{
					
								if (AActor.IsBot)
								{
		
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, HeadTxt, Screen.X - 2, Screen.Y - 22, DX11::ImGui_DX11::Color::Green, true);
					
								}
								else
								{
								//	DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Settings::PlayerNameSize, TemID, Screen.X - 50, Screen.Y - 50, DX11::ImGui_DX11::Color::Red, false);
									DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, nameFontSize, HeadTxt, Screen.X - 4, Screen.Y - 18, Settings::PlayerNameColor, true);
					
								}
							}
						}

						if (Settings::PlayerName)
						{
							
							// Calculate font size based on distance
							

							if (AActor.IsBot) {
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, RootText, Screen.X + 4, (Screen.Y + Screen.Z) + 3, DX11::ImGui_DX11::Color::Blue, true);
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, RootText2, Screen.X + 4, (Screen.Y + Screen.Z) + 15, DX11::ImGui_DX11::Color::White, true);
							}
							else {
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, RootText, Screen.X + 4, (Screen.Y + Screen.Z) + 3, Settings::PlayerNameColor, true);
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, RootText2, Screen.X + 4, (Screen.Y + Screen.Z) + 15, DX11::ImGui_DX11::Color::White, true);
							//	DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::pRegularFont, nameFontSize, RootText3, Screen.X + 4, (Screen.Y + Screen.Z) + 23, DX11::ImGui_DX11::Color::Red, true);
							}

						}
						if (Settings::PlayerHealth)
						{

							DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 6, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5), DX11::ImGui_DX11::Color::Black);

							if (AActor.Health > 70.0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 6, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Green);
							}
							else if (AActor.Health > 30.0 && AActor.Health <= 70.0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 6, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Yellow);
							}
							else if (AActor.Health > 0.0 && AActor.Health <= 30.0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 6, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.Health / AActor.HealthMax, DX11::ImGui_DX11::Color::Red);

							}
							else  if (AActor.Health <= 0)
							{
								DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 6, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5) * AActor.KnockedHealth / AActor.HealthMax, DX11::ImGui_DX11::Color::Red2);
								//DX11::ImGui_DX11::DrawFilledRectangle(Screen.X - (Screen.Z / 4) - 6, (Screen.Y - 5) + (Screen.Z + 5), 3, (Screen.Z + 5), DX11::ImGui_DX11::Color::Red);
							}

						}
						if (Settings::PlayerBox)
						{
							DX11::ImGui_DX11::CornerBox(Screen.X - Screen.Z / 4 - 3, Screen.Y - 5, (Screen.Z / 2) + 3, Screen.Z + 5, 0.7f, 0.5f / 2, Settings::PlayerBoxColor);
						}
						float Botlinescolors[] = { 255, 255, 255, 255 };
						if (Settings::PlayerLine)
						{
							if (AActor.IsBot && Settings::PlayerLineMode != 0)
							{
								DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, ImColor(Botlinescolors[0], Botlinescolors[1], Botlinescolors[2], Botlinescolors[3]), Settings::linethickness);
							}
							else if (Settings::PlayerLineMode == 0)
							{
								DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, linescolors, Settings::linethickness);
							}
							else {
								DX11::ImGui_DX11::DrawLine(DX11Window::Width / 2, 0, Screen.X, Screen.Y - 5, Settings::PlayerLineColor, Settings::linethickness);

							}

						}
						if (Settings::PlayerSkeleton)
						{
						
							HeadPos = AActor.HeadPos;
							HeadPos.Z += 7;
							//HeadPos.Y -= 30;

							if (!Algorithm::WorldToScreenBone(ViewMatrix, HeadPos, Head, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.ChestPos, Chest, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.PelvisPos, Pelvis, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lSholderPos, lSholder, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rSholderPos, rSholder, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lElbowPos, lElbow, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rElbowPos, rElbow, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lWristPos, lWrist, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rWristPos, rWrist, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lThighPos, lThigh, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rThighPos, rThigh, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lKneePos, lKnee, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rKneePos, rKnee, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lAnklePos, lAnkle, &Distance)) continue;
							if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rAnklePos, rAnkle, &Distance)) continue;

							
							ImColor bonescolors1;
						//	ImColor visbility(0.0f, 1.0f, 0.0f, 1.0f); // RGBA values for bright green


							
							if (Settings::PlayerSkeletonMode == 0) {
								bonescolors1 = linescolors;
							}
							else {
								bonescolors1 = Settings::PlayerSkeletonColor;
							}
								
							if (Settings::visibilitycheck && AActor.IsVisible) {
								bonescolors1 = Settings::visColor;
							}
								

								
							  DX11::ImGui_DX11::DrawCircle(Head.X, Head.Y, Screen.Z / 20 ,  bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, Pelvis.X, Pelvis.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, lSholder.X, lSholder.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(Chest.X, Chest.Y, rSholder.X, rSholder.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(lSholder.X, lSholder.Y, lElbow.X, lElbow.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(rSholder.X, rSholder.Y, rElbow.X, rElbow.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(lElbow.X, lElbow.Y, lWrist.X, lWrist.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(rElbow.X, rElbow.Y, rWrist.X, rWrist.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, lThigh.X, lThigh.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(Pelvis.X, Pelvis.Y, rThigh.X, rThigh.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(lThigh.X, lThigh.Y, lKnee.X, lKnee.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(rThigh.X, rThigh.Y, rKnee.X, rKnee.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(lKnee.X, lKnee.Y, lAnkle.X, lAnkle.Y, bonescolors1, Settings::skeletonthickness);
							  DX11::ImGui_DX11::DrawLine(rKnee.X, rKnee.Y, rAnkle.X, rAnkle.Y, bonescolors1, Settings::skeletonthickness);
						}
						

					}

					if (Settings::AimWarning) {

						if (AActor.isAimingAtMe)
						{
							string Aim = " !!! ENEMEY AIMING AT YOU!!! ";
							ImColor warncolor;
							int randomNum = (rand() % 2) + 1;
							if (randomNum == 1)
							{
								warncolor = DX11::ImGui_DX11::Color::Red;
							}
							if (randomNum == 2)
							{
								warncolor = DX11::ImGui_DX11::Color::Yellow;
							}


							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 30, Aim, DX11Window::Width / 2, DX11Window::Height / 100 * 14.5f, warncolor, true);
							string SIMI = "AIMING";
							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, Settings::PlayerStateSize, SIMI, Screen.X - 22, Screen.Y - 34, Settings::PlayerStateColor, false);
						}
					}

					if (AActor.IsBot) continue;

				}

				if (Settings::FovShow)
				{
					if (Data::AActorList.size() != 0)
					{
						DX11::ImGui_DX11::DrawCircle(DX11Window::Width / 2, DX11Window::Height / 2, Settings::fovcircleredus, Settings::FovColor);
					}
				}

				if (!Settings::FightMode) {
			
					if (Settings::Lootbox) {
						ImColor color;
						for (int i = 0; i < g_pEsp->lootboxr.size(); i++) {
							if (!Algorithm::WorldToScreen(g_pEsp->lootboxr[i].Position, Screen, &Distance, ViewMatrix)) {
								continue;
							}
							if (Distance > 50) {
								continue;
							}

							// Determine text size based on distance
							int baseTextSize = 17; // Base text size
							int maxSize = 14; // Maximum text size limit
							int textSize = baseTextSize - (Distance / 10); // Example: Decrease text size gradually with distance

							// Ensure textSize doesn't go below maxSize
							if (textSize < maxSize) {
								textSize = maxSize;
							}

							std::string dead = "[ Dead Box   " + to_string(Distance) + "M ]";
							DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, textSize, dead, Screen.X, Screen.Y + 18, ImVec4(0.737f, 1.000f, 0.000f, 1.000f), false);

							if (Settings::LootboxItems && Distance < 15) {
						
								for (int k = 0; k < g_pEsp->lootboxr[i].boxitem.size(); k++) {
									// Adjust item text size similarly
									int baseTextSize = 17; // Base text size
									int maxSize = 14; // Maximum text size limit
									int textSize = baseTextSize - (Distance / 10); // Example: Decrease text size gradually with distance
									if (textSize < maxSize) {
										textSize = maxSize;
									}

									color = g_pEsp->lootboxr[i].boxitem[k].colorcod;
									std::string text = g_pEsp->lootboxr[i].boxitem[k].Displayname;

									// Draw filled rectangle background
									//DX11::ImGui_DX11::DrawFilledRect(Screen.X - 10, Screen.Y - 15 * (k), 100, 15, ImColor(0.000f, 0.00f, 0.00f, 0.200f));

									// Draw corner box
									//DX11::ImGui_DX11::CornerBox(Screen.X - 10, Screen.Y - 15 * (k), 110, 15, 0.6f, 0.450f, ImVec4(0.000f, 1.000f, 0.964f, 1.000f));

									// Draw item text
									DX11::ImGui_DX11::DrawString(DX11::ImGui_DX11::special, textSize, text, Screen.X, Screen.Y - 15 * (k), g_pEsp->lootboxr[i].boxitem[k].colorcod, false);
								}

							}
						}
					}


					if (Settings::Items) {


						for (Item& Item : Data::ItemList)
						{
							if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, ViewMatrix)) continue;

							if (Distance < 0 || Distance > 30) {
								//error
								if (Item.Name != "Air Drop" && Item.Name != "Redzone" && Item.Name != "Frag" && Item.Name != "Burn"
									&& Item.Name != "Smoke" && Item.Name != "SafeZone") {
									continue;
								}
							}

							if (Item.Name == "Frag" || Item.Name == "Smoke" || Item.Name == "Molotof" || Item.Name == "Burn") {

								ImColor rcolor = ImColor(255, 0, 0); // Red color
								ImColor wcolor = ImColor(255, 255, 255); // white color
								float radius = 500.0f;
								float thickness = 2.0f;
								float mydistancefromgrenade = Distance;

								for (AActor& AActor : Data::AActorList) {
									if (!Algorithm::WorldToScreenPlayer(AActor.Position, Screen, &Distance, ViewMatrix)) continue;
									if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.lAnklePos, lAnkle, &Distance)) continue;
									if (!Algorithm::WorldToScreenBone(ViewMatrix, AActor.rAnklePos, rAnkle, &Distance)) continue;
									if (!Algorithm::WorldToScreen(Item.Position, Screen, &Distance, ViewMatrix)) continue;

									if (mydistancefromgrenade > 5.0f) {
										if (IsPointInCircle3D(AActor.lAnklePos, Item.Position, radius) || IsPointInCircle3D(AActor.rAnklePos, Item.Position, radius)) {
											DrawCircle3D(Item.Position, radius, rcolor, thickness, true, 0.001f, ViewMatrix);
										}
									}

								}

							}


							string Text = Item.Name + " " + "(" + to_string(Distance) + "m)";
							string air = Item.Name + " " + to_string(Distance) + "M";

							animationTime += ImGui::GetIO().DeltaTime * animationSpeed;
							FLOAT animationOffset = sinf(animationTime) * animationRange;

							if (Item.Name == "Air Drop")
							{
								

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 15, Text, Screen.X, Screen.Y + 15, DX11::ImGui_DX11::Color::Red, true);
								
								
							}
							else if (Item.Name == "Redzone")
							{
								

							    DrawFilledUpwardArrowWithBorder(Screen.X - 1, Screen.Y - 30, 20.0f, DX11::ImGui_DX11::Color::White, ImColor(0, 0, 0, 255), 0.7f, animationOffset);
							    DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 20, Text, Screen.X - 1, Screen.Y - 1, DX11::ImGui_DX11::Color::Red, true);
							    DrawCircle3D(Item.Position, 450.0f, DX11::ImGui_DX11::Color::Red, 1.0f, true, 0.001f, ViewMatrix);
								
								
							}
							else if (Item.Name == "SafeZone")
							{
								

								DrawFilledUpwardArrowWithBorder(Screen.X - 1, Screen.Y - 30, 20.0f, DX11::ImGui_DX11::Color::White, ImColor(0, 0, 0, 255), 0.7f, animationOffset);
								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 20, Text, Screen.X - 1, Screen.Y - 1, DX11::ImGui_DX11::Color::Green, true);

								

							}
							else if (Item.Name == "Frag")
							{

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 15, air, Screen.X, Screen.Y,Settings::FRAGColor, true);

							}
							else if (Item.Name == "Smoke")
							{

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 15, air, Screen.X, Screen.Y, Settings::SMOKEColor, true);
							}
							else if (Item.Name == "Burn")
							{

								DX11::ImGui_DX11::DrawBorderString(DX11::ImGui_DX11::special, 15, air, Screen.X, Screen.Y, Settings::MOLOTOFColor, true);
							}
							else if (Item.Name == "Akm")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AkmColor, true);
							}
							else if (Item.Name == "M16A4")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::M16A4Color, true);
							}
							else if (Item.Name == "SCARL")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::SCARLColor, true);
							}
							else if (Item.Name == "M416")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::M416Color, true);
							}
							else if (Item.Name == "GROZA")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::GROZAColor, true);
							}
							else if (Item.Name == "AUG")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AUGColor, true);
							}
							else if (Item.Name == "QBZ")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::QBZColor, true);
							}
							else if (Item.Name == "M762")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::M762Color, true);
							}
							else if (Item.Name == "MK47")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MK47Color, true);
							}
							else if (Item.Name == "G36C")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::G36CColor, true);
							}
							else if (Item.Name == "HONEY")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::HONEYColor, true);
							}
							else if (Item.Name == "FAMAS")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::FAMASColor, true);
							}
							else if (Item.Name == "KAR98")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::KAR98Color, true);
							}
							else if (Item.Name == "M24")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::M24Color, true);
							}
							else if (Item.Name == "AWM")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AWMColor, true);
							}
							else if (Item.Name == "WIN94")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::WIN94Color, true);
							}
							else if (Item.Name == "MOSIN")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MOSINColor, true);
							}
							else if (Item.Name == "AMR")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AMRColor, true);
							}
							else if (Item.Name == "SKS")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::SKSColor, true);
							}
							else if (Item.Name == "VSS")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::VSSColor, true);
							}
							else if (Item.Name == "MINI14")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MINI14Color, true);
							}
							else if (Item.Name == "MK14")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MK14Color, true);
							}
							else if (Item.Name == "SLR")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::SLRColor, true);
							}
							else if (Item.Name == "QBU")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::QBUColor, true);
							}
							else if (Item.Name == "MK12")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MK12Color, true);
							}
							else if (Item.Name == "UZI")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::UZIColor, true);
							}
							else if (Item.Name == "UMP45")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::UMP45Color, true);
							}
							else if (Item.Name == "VECTOR")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::VECTORColor, true);
							}
							else if (Item.Name == "THOMPSON")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::THOMPSONColor, true);
							}
							else if (Item.Name == "BIZON")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::BIZONColor, true);
							}
							else if (Item.Name == "MP5K")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MP5KColor, true);
							}
							else if (Item.Name == "P90")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::P90Color, true);
							}
							else if (Item.Name == "S686")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::S686Color, true);
							}
							else if (Item.Name == "S1897")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::S1897Color, true);
							}
							else if (Item.Name == "S12K")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::S12KColor, true);
							}
							else if (Item.Name == "DBS")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::DBSColor, true);
							}
							else if (Item.Name == "M1014")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::M1014Color, true);
							}
							else if (Item.Name == "NS2000")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::NS2000Color, true);
							}
							else if (Item.Name == "M249")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::M249Color, true);
							}
							else if (Item.Name == "DP28")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::DP28Color, true);
							}
							else if (Item.Name == "MG3")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MG3Color, true);
							}
							else if (Item.Name == "FLARE")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::FLAREColor, true);
							}
							else if (Item.Name == "FRAG")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::FRAGColor, true);
							}
							else if (Item.Name == "SMOKE")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::SMOKEColor, true);
							}
							else if (Item.Name == "MOLOTOF")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MOLOTOFColor, true);
							}
							else if (Item.Name == "MedKit")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::MedKitColor, true);
							}
							else if (Item.Name == "FirstAidKit")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::FirstAidKitColor, true);
							}
							else if (Item.Name == "Painkiller")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::PainkillerColor, true);
							}
							else if (Item.Name == "EnergyDrink")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::EnergyDrinkColor, true);
							}
							else if (Item.Name == "Adrenalin")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AdrenalinColor, true);
							}
							else if (Item.Name == "Bag1")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Bag1Color, true);
							}
							else if (Item.Name == "Bag2")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Bag2Color, true);
							}
							else if (Item.Name == "Bag3")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Bag3Color, true);
							}
							else if (Item.Name == "Helmet1")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Helmet1Color, true);
							}
							else if (Item.Name == "Helmet2")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Helmet2Color, true);
							}
							else if (Item.Name == "Helmet3")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Helmet3Color, true);
							}
							else if (Item.Name == "Armor1")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Armor1Color, true);
							}
							else if (Item.Name == "Armor2")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Armor2Color, true);
							}
							else if (Item.Name == "Armor3")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Armor3Color, true);
							}
							else if (Item.Name == "7.62mm")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::a762mmColor, true);
							}
							else if (Item.Name == "5.56mm")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::a556mmColor, true);
							}
							else if (Item.Name == "9mm")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::a9mmColor, true);
							}
							else if (Item.Name == "45ACP")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::a45ACPColor, true);
							}
							else if (Item.Name == "12Gauege")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::a12GauegeColor, true);
							}
							else if (Item.Name == "AwmAmmo")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AwmAmmoColor, true);
							}
							else if (Item.Name == "AmrAmmo")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::AmrAmmoColor, true);
							}
							else if (Item.Name == "Scope_x2")
							{

								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Scope_x2Color, true);
							}
							else if (Item.Name == "Scope_x3")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Scope_x3Color, true);
							}
							else if (Item.Name == "Scope_x4")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Scope_x4Color, true);
							}
							else if (Item.Name == "Scope_x6")
							{

								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Scope_x6Color, true);
							}
							else if (Item.Name == "Scope_x8")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::Scope_x8Color, true);
							}
							else if (Item.Name == "Shop Token")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::ShopTokenColor, true);
							}
							else if (Item.Name == "Extended Mac")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::ExtendedMacColor, true);
							}
							else if (Item.Name == "Suppressor (AR)" || Item.Name == "Suppressor (Sniper)" || Item.Name == "Suppressor (SMG)")
							{
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, Settings::SupressorColor, true);
							}
							else {
								DX11::ImGui_DX11::DrawBorderStringOpt(DX11::ImGui_DX11::special, 17, Text, Screen.X, Screen.Y, DX11::ImGui_DX11::Color::Red, true);
							}
						}

						// Draw grenade paths
						DrawGrenadePaths(ViewMatrix);
					}
					if (Settings::grenadePath) {

						// Update grenade paths
						UpdateGrenadePaths();
						// Draw grenade paths
						DrawGrenadePaths(ViewMatrix);
					}

					if (Settings::Vehicle) {
						for (Vehicle& vehicle : Data::VehicleList) {

							if (!Algorithm::WorldToScreen(vehicle.Position, Screen, &Distance, ViewMatrix)) {
								continue;
							}

							if (Distance > 400) continue;

							if (vehicle.driving && Distance < 10) continue;

							std::string vehicleText = vehicle.Name + " [" + std::to_string(Distance) + "m]";

							const float barWidth = 60.0f;
							const float barHeight = 5.0f;
							const float borderThickness = 1.0f;

							// Ensure the hp and oil values are within valid ranges
							float clampedHP = myespMax(0.0f, myespMin(vehicle.hp, vehicle.hpmax));
							float clampedOil = myespMax(0.0f, myespMin(vehicle.oil, vehicle.oilmax));

							// Calculate the width of the health and oil bars based on current values
							float healthBarWidth = (clampedHP / vehicle.hpmax) * barWidth;
							float oilBarWidth = (clampedOil / vehicle.oilmax) * barWidth;

							// Define color gradients
							ImVec4 healthColorFull = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green
							ImVec4 healthColorEmpty = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
							ImVec4 oilColorFull = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green
							ImVec4 oilColorEmpty = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow

							// Interpolate colors based on current values
							float healthFactor = (clampedHP > 0.0f && vehicle.hpmax > 0.0f) ? (clampedHP / vehicle.hpmax) : 0.0f;
							float oilFactor = (clampedOil > 0.0f && vehicle.oilmax > 0.0f) ? (clampedOil / vehicle.oilmax) : 0.0f;
							ImU32 healthColor = InterpolateColor(healthColorFull, healthColorEmpty, 1.0f - healthFactor);
							ImU32 oilColor = InterpolateColor(oilColorFull, oilColorEmpty, 1.0f - oilFactor);

							// Draw health and oil bars
							ImDrawList* drawList = ImGui::GetBackgroundDrawList();

							// Health bar background
							drawList->AddRectFilled(
								ImVec2(Screen.X, Screen.Y + 20),
								ImVec2(Screen.X + barWidth, Screen.Y + 20 + barHeight),
								IM_COL32(128, 0, 0, 255) // Deep red color background
							);

							// Health bar border
							drawList->AddRect(
								ImVec2(Screen.X - borderThickness, Screen.Y + 20 - borderThickness),
								ImVec2(Screen.X + barWidth + borderThickness, Screen.Y + 20 + barHeight + borderThickness),
								IM_COL32(0, 0, 0, 255)
							);

							// Health bar
							drawList->AddRectFilled(
								ImVec2(Screen.X, Screen.Y + 20),
								ImVec2(Screen.X + healthBarWidth, Screen.Y + 20 + barHeight),
								healthColor
							);

							// Oil bar background
							drawList->AddRectFilled(
								ImVec2(Screen.X, Screen.Y + 30),
								ImVec2(Screen.X + barWidth, Screen.Y + 30 + barHeight),
								IM_COL32(128, 0, 0, 255) // Deep red color background
							);

							// Oil bar border
							drawList->AddRect(
								ImVec2(Screen.X - borderThickness, Screen.Y + 30 - borderThickness),
								ImVec2(Screen.X + barWidth + borderThickness, Screen.Y + 30 + barHeight + borderThickness),
								IM_COL32(0, 0, 0, 255)
							);

							// Oil bar
							drawList->AddRectFilled(
								ImVec2(Screen.X, Screen.Y + 30),
								ImVec2(Screen.X + oilBarWidth, Screen.Y + 30 + barHeight),
								oilColor
							);

							// Draw the vehicle name and distance, with different colors based on whether it is being driven
							ImU32 vehicleColor = vehicle.driving ? IM_COL32(255, 0, 0, 255) : ImGui::ColorConvertFloat4ToU32(Settings::VehicleColor);
							DX11::ImGui_DX11::DrawBorderStringOpt(
								DX11::ImGui_DX11::pIconFont,
								Settings::VehicleSize,
								vehicleText,
								Screen.X,
								Screen.Y,
								vehicleColor,
								false
							);
						}
					}


				}

			}
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		DX11::EndDraw();
		std::this_thread::sleep_for(std::chrono::milliseconds(Settings::UpdateFps));
	}
}
