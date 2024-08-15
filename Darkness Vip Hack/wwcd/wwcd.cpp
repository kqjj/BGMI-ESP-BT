
#include "wwcd.h"
#include <thread>
#include <winapifamily.h>
#include <Windows.h>
#include <cstdint>
#include <screenshot/ScreenshotSaver.h>
#include <iomanip>
#include <sstream>
#include <algorithm> // for std::replace
#include <cstdlib>  // For system function
#include <cstdio>   // For popen, pclose
#include <memory>   // For std::unique_ptr
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;
using namespace wwcd;

const string botToken = "7073204909:AAHtrbmX-dijQy2SC_OV7FmCVJleJcZQXsA";

//https://t.me/animetonee
//const string chatId = "@infominiaa";
const string chatId = "@animetonee";

const string cmd1p1 = "curl -i -H \"Accept: application/json\" -H \"Content-Type:application/json\" -X POST --data \"{\\\"content\\\": \\\"";
const string cmd1p2 = "\\\"}\" ";

const string cmd2p1 = "curl -F \"file1=@";
ScreenshotSaver saver;

int system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		return -1;

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);

	return rv;
}

//////////////////discord///////////////////////////////////////////

void SendText(string text, string webhook_url) {
	//ShowWindow(GetConsoleWindow(), HIDE_WINDOW());

	string cmd = cmd1p1 + text + cmd1p2 + webhook_url;

	system_no_output(cmd.c_str());
	system_no_output("cls");
}

void SendFile(string path, string webhook_url) {
//	ShowWindow(GetConsoleWindow(), HIDE_WINDOW());

	string cmd = cmd2p1 + path + "\" " + webhook_url;

	system_no_output(cmd.c_str());
	system_no_output("cls");


}

void SendFileWithCaption(const string& path, const string& caption, const string& webhook_url) {
	// Constructing the command for sending a file with a caption
	string payload_json = "{\"content\": \"" + caption + "\"}";
	string cmd = "curl -F \"payload_json=" + payload_json + "\" -F \"file1=@" + path + "\" " + webhook_url;

	// Print the command for debugging
	//cout << "Sending file with command: " << cmd << endl;

	// Execute the command
	system_no_output(cmd.c_str());
	system_no_output("cls"); // Clear the screen (optional)
}

//////////////////////////////////telegram//////////////////////////////////////

// Function to send a photo with a caption to a Telegram chat using curl
void SendPhotoToTelegramwcap(const string& filePath, const string& caption) {
	string cmd = "curl -F photo=@" + filePath + " -F caption=\"" + caption + "\" https://api.telegram.org/bot" + botToken + "/sendPhoto?chat_id=" + chatId;
	system_no_output(cmd);
	system_no_output("cls");
}

// Function to send a photo to a Telegram chat using curl
void SendPhotoToTelegram(const string& filePath) {
	
	string cmd = "curl -F photo=@" + filePath + " https://api.telegram.org/bot" + botToken + "/sendPhoto?chat_id=" + chatId;
	
	system_no_output(cmd);
	system_no_output("cls");

}

// Function to send a text message to a Telegram chat using a bot
void SendMessageToTelegram(const string& message) {
	//ShowWindow(GetConsoleWindow(), HIDE_WINDOW());

	string url = "https://api.telegram.org/bot" + botToken + "/sendMessage";
	string cmd = "curl -d \"chat_id=" + chatId + "&text=" + message + "\" " + url;

	system_no_output(cmd.c_str());
	system_no_output("cls");
}

///////////////////////////END////////////////////////////////////////////

std::string ConvertToTimeFormat(int seconds) {
	int hours = seconds / 3600;
	int minutes = (seconds % 3600) / 60;
	int secs = seconds % 60;

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << hours << ":"
		<< std::setw(2) << std::setfill('0') << minutes << ":"
		<< std::setw(2) << std::setfill('0') << secs;
	return oss.str();
}

VOID wwcd::wwcdThread()
{
	while (true)
	{
		if (Settings::sendscreenshot) {
			if (Settings::AliveTeams == 1 || Settings::AlivePlayers == 1)
			{
				Sleep(2600);

				saver.CaptureAndSaveScreenshot(L"C:\\WINS.png");

				Sleep(1000);

				SendText("Name : " + (Settings::MyName), "https://discord.com/api/webhooks/1256111040312250369/851HNM4K0YAcb1FUhO6gdzGth0vLOr_zTmNChHIZxpE-z2-RBQjCgnUsN0_Ghyg3DHa-");
				SendText("Game Time : " + (ConvertToTimeFormat(Settings::TimeRemind)), "https://discord.com/api/webhooks/1256111040312250369/851HNM4K0YAcb1FUhO6gdzGth0vLOr_zTmNChHIZxpE-z2-RBQjCgnUsN0_Ghyg3DHa-");

				SendFile("C:\\WINS.png", "https://discord.com/api/webhooks/1256111040312250369/851HNM4K0YAcb1FUhO6gdzGth0vLOr_zTmNChHIZxpE-z2-RBQjCgnUsN0_Ghyg3DHa-");
			//	SendFileWithCaption("C:\\WINS.png", "Name :" + Settings::MyName + " | GameTime : " + ConvertToTimeFormat(Settings::TimeRemind), "https://discord.com/api/webhooks/1256111040312250369/851HNM4K0YAcb1FUhO6gdzGth0vLOr_zTmNChHIZxpE-z2-RBQjCgnUsN0_Ghyg3DHa-");

				SendPhotoToTelegramwcap("C:\\WINS.png", "Name :" + Settings::MyName + " | GameTime : " + ConvertToTimeFormat(Settings::TimeRemind));

				Sleep(100);
				remove("C:\\WINS.png");
				Settings::notifysate = "Winner Winner Screen Posted";
				std::this_thread::sleep_for(std::chrono::milliseconds(500000));
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}
}