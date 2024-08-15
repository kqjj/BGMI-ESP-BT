#include "Includes.h"
#include ".\Utility\Utility.h"
#include ".\Esp\Esp.h"
#include "Driver.h"
#include ".\Settings\Settings.h"
#include ".\icon.h"
#include ".\Data\Data.h"
#include ".\Aimbot\Aimbot.h"
#include ".\Memory.h"
#include ".\resource.h"
#include ".\font.h"
#include ".\tahoma.h"
#include ".\ImguiNotify\imgui_notify.h"
#include <GUI/gui.h>
#include <screenshot/ScreenshotSaver.h>
#include <discord/Discord.h>
#include <wwcd/wwcd.h>

#define XTREME_DRIVER_FILE  "Animetone.sys"
#define XTREME_SERVICE_NAME "Animetone"
#define XTREME_DEVICE_NAME  "\\Device\\Animetone"
DRIVER* m_drv = nullptr;

//Discord* g_Discord;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	char Buffer[1000];
	GetClassNameA(hWnd, Buffer, 1000);

	string WindowClassName = Buffer;
	if (Emulator::IsSmartGaGa == TRUE)
	{
		if (WindowClassName.find("TitanRenderWindowClass") != string::npos)
		{
			wchar_t Name[1000];
			GetWindowTextW(hWnd, Name, 1000);
			Game::hWindow = FindWindowW(L"TitanRenderWindowClass", Name);
		}
	}
	else if (Emulator::IsGameLoop == TRUE)
	{
		if (WindowClassName.find("TXGuiFoundation") != string::npos)
		{
			wchar_t Name[1000];
			GetWindowTextW(hWnd, Name, 1000);
			Game::hWindow = FindWindowW(L"TXGuiFoundation", Name);
		}
	}
	else if (Emulator::IsGameLoop7 == TRUE)
	{
		if (WindowClassName.find("TXGuiFoundation") != string::npos)
		{
			wchar_t Name[1000];
			GetWindowTextW(hWnd, Name, 1000);
			Game::hWindow = FindWindowW(L"TXGuiFoundation", Name);
			if (!Game::hWindow)
			{
				Game::hWindow = FindWindowEx(NULL, NULL, "TXGuiFoundation", "Gameloop【Turbo AOW Engine-7.1 Beta】");
			}

		}
	}
	return TRUE;
	//return 0;
}



void WriteResToDisk(std::string PathFile, LPCSTR File_WITHARG)
{
	HRSRC myResource = ::FindResource(NULL, File_WITHARG, RT_RCDATA);
	unsigned int myResourceSize = ::SizeofResource(NULL, myResource);
	HGLOBAL myResourceData = ::LoadResource(NULL, myResource);
	void* pMyExecutable = ::LockResource(myResourceData);
	std::ofstream f(PathFile, std::ios::out | std::ios::binary);
	f.write((char*)pMyExecutable, myResourceSize);
	f.close();
}

int main() {
	
	if (FreeConsole() == 0) {
		std::cerr << "FreeConsole failed with error: " << GetLastError() << std::endl;
	}

	if (AllocConsole() == 0) {
		std::cerr << "AllocConsole failed with error: " << GetLastError() << std::endl;
	}

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow == nullptr) {
		std::cerr << "GetConsoleWindow failed with error: " << GetLastError() << std::endl;
	}
	else {
		ShowWindow(consoleWindow, 0);
	}
	

	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);

	WriteResToDisk("C:\\Animetone.sys", (LPCSTR)MAKEINTRESOURCE(DriverDarkness));
	WriteResToDisk("C:\\X.ttf", (LPCSTR)MAKEINTRESOURCE(FontDarkness));

	system(("sc create Animetone binpath=C:\\Animetone.sys type=kernel >nul"));
	system(("sc start Animetone >nul"));

	m_drv = new DRIVER(XTREME_DRIVER_FILE, XTREME_DEVICE_NAME, XTREME_SERVICE_NAME, Driver, DriverSize);
	
	if (m_drv->Load()) {
		std::cout << "[+] Driver Loaded" << std::endl;
		//MessageBox(NULL, "Driver Loaded", "AnimeTone", MB_OKCANCEL);
	}
	else {
	//	std::cout << "Failed to load Driver" << std::endl;
		MessageBox(NULL, "Failed to load Driver", "AnimeTone", MB_OKCANCEL);
	}

	TCHAR procid[256] = "aow_exe.exe";
	Game::Id = Utility::GetTrueProcessId(procid);
	if (Game::Id > 0)
	{
		Emulator::IsGameLoop = TRUE;
	}

	if (Game::Id == 0)
	{
		m_drv->Unload();
		MessageBox(NULL, "Can't Find Game Id", "AnimeTone VIP", MB_OKCANCEL);
		system("pause >nul");
		ExitProcess(0);
	}

	Game::hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Game::Id);

	if (Game::hProcess == 0)
	{
		m_drv->Unload();
		MessageBox(NULL, "Can't Find Game Process", "AnimeTone VIP", MB_OKCANCEL);
		system("pause >nul");
		ExitProcess(0);
	}

	if (Emulator::IsGameLoop == true)
	{
		EnumWindows(EnumWindowsProc, 0);
		if (IsIconic(Game::hWindow) != 0) ShowWindow(Game::hWindow, SW_RESTORE);
		Game::hWindow = FindWindowExW(Game::hWindow, 0, L"AEngineRenderWindowClass", L"AEngineRenderWindow");
		if (Game::hWindow == 0)
		{
			Game::hWindow = FindWindowA("TXGuiFoundation", "Gameloop");
			if (Game::hWindow == 0) {
				Game::hWindow = FindWindowA("TXGuiFoundation", "Gameloop(64beta)");
			}
		}
	}
	if (Game::hWindow == 0)
	{
		m_drv->Unload();
		MessageBox(NULL,"Can't Find Game Window", "AnimeTone VIP", MB_OKCANCEL);
		system("pause >nul");
		ExitProcess(0);
	}

	int scrWidthh = GetSystemMetrics(SM_CXSCREEN);
	int scrHeightt = GetSystemMetrics(SM_CYSCREEN);
	RECT Rect;
	GetWindowRect(Game::hWindow, &Rect);
    if (Rect.left < 0 || Rect.top < 0 || Rect.right < 0 || Rect.bottom < 0)
    {
    
    	RECT tSize;
    	GetWindowRect(Game::hWindow, &tSize);
    	scrWidthh = tSize.right - tSize.left;
    	scrHeightt = tSize.bottom - tSize.top;
    
    	SetWindowPos(DX11Window::hWindow, HWND_TOPMOST, tSize.left, tSize.top, scrWidthh, scrHeightt, SWP_NOMOVE | SWP_NOSIZE);
    }
    if (Emulator::IsGameLoop == true)
	{
		//Data::ViewMatrixBase = Data::GetViewMatrixBase(0x45000000, 0x65000000);

	//	Data::ViewMatrixBase = Data::GetViewMatrixBase(0x40000000, 0x70000000);



		//Data::ViewMatrixBase = Data::GetViewMatrixBase(0x3D000000, 0x65000000);
		//Data::ViewMatrixBase = Data::GetViewMatrixBase(0x25000000, 0x35000000);
		//Data::ViewMatrixBase = Data::GetViewMatrixBase(0x50000000, 0x70000000);
		
	}

	if (Data::ViewMatrixBase == 0)
	{
		//m_drv->Unload();
	
		//MessageBox(NULL, "Can't Find ViewMatrixBase V1 Initiating V2", "AnimeTone VIP", MB_OKCANCEL);
		
	//	ExitProcess(0);

	}


	string MainFontPath = ("C:\\X.ttf");
	string RenderFontPath = ("C:\\X.ttf");

	//scrWidthh = Rect.right - Rect.left;
	//scrHeightt = Rect.bottom - Rect.top;
	DX11Window::Instantiate(Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top);
	DX11::Instantiate(DX11Window::hWindow, DX11Window::Width, DX11Window::Height);

	ImGui::CreateContext();

	ui::styles();
	ui::colors();

	ImGuiIO& Io = ImGui::GetIO();
	Io.WantSaveIniSettings = true;

	// Global Scale
//	Io.FontGlobalScale = 1.5f; // Increase global scale for better rendering on high-DPI displays


	static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
	ImFontConfig icons_config;

	ImFontConfig CustomFont;
	CustomFont.FontDataOwnedByAtlas = false;
	


	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.OversampleH = 3; //2.5
	icons_config.OversampleV = 3; //2.5




	//Io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &CustomFont);



	//Io.IniFilename = nullptr; 
	//Io.Fonts->AddFontFromFileTTF(MainFontPath.c_str(), 15.0f);
	Io.Fonts->AddFontFromMemoryTTF((void*)Custom, sizeof(Custom), 15.0f);
//	Io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 15.0f);


	Io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 15.0f, &icons_config, icons_ranges);




	ImGui::MergeIconsWithLatestFont(16.f, false);
	ImGui_ImplWin32_Init(DX11Window::hWindow);
	ImGui_ImplDX11_Init(DX11::pDevice, DX11::pImmediateContext);
	DX11::ImGui_DX11::special = Io.Fonts->AddFontFromFileTTF(MainFontPath.c_str(), 32.0f);
	DX11::ImGui_DX11::pRegularFont = Io.Fonts->AddFontFromFileTTF(RenderFontPath.c_str(), 32.0f);
	DX11::ImGui_DX11::pIconFont = Io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 40.0f, &icons_config, icons_ranges);


	
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Data::QueryThread, 0, 0, 0));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Esp::EspThread, 0, 0, 0));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Aimbot::AimbotThread, 0, 0, 0));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Memory::MemoryThread, 0, 0, 0));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)wwcd::wwcdThread, 0, 0, 0));
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Memory::AllMemoryHacks, 0, 0, 0));

	MSG Message;

	//g_Discord->Intialize();

	while (true)
	{


		if (PeekMessage(&Message, DX11Window::hWindow, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	
		
		if (DX11Window::hWindow) {
			RECT Rect;
			//RECT wndRc;
			//GetWindowRect(DX11Window::hWindow, &wndRc); //modified
			GetWindowRect(Game::hWindow, &Rect);
			DX11Window::Left = Rect.left;
			DX11Window::Top = Rect.top;
			DX11Window::Width = Rect.right - Rect.left;
			DX11Window::Height = Rect.bottom - Rect.top;
			MoveWindow(DX11Window::hWindow, DX11Window::Left, DX11Window::Top, DX11Window::Width, DX11Window::Height, true);
		}
	

		if (Settings::ShowMenu)
		{
			SetForegroundWindow(DX11Window::hWindow);
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			if (DX11Window::IsClickable == true)
			{
				Utility::ChangeClickability(FALSE, DX11Window::hWindow);
				DX11Window::IsClickable = !DX11Window::IsClickable;
				Settings::ShowMenu = !Settings::ShowMenu;
			}
			else
			{
				Utility::ChangeClickability(TRUE, DX11Window::hWindow);
				DX11Window::IsClickable = !DX11Window::IsClickable;
				Settings::ShowMenu = !Settings::ShowMenu;
			}
		}
		if (GetAsyncKeyState(VK_HOME) & 1)
		{
			Settings::ShowMenu2 = !Settings::ShowMenu2;
		}

		if (GetAsyncKeyState(VK_END) & 1)
		{
			Memory::RestoreHook();
			Sleep(200);
			m_drv->Unload();
			ExitProcess(1);
		}
		Sleep(10);

	}

	return EXIT_SUCCESS;
}