#include "ScreenshotSaver.h"
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

ScreenshotSaver::ScreenshotSaver() : hScreenDC(NULL), hMemoryDC(NULL), hBitmap(NULL), hOldBitmap(NULL), gdiplusToken(0) {
    // Initialize GDI+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

ScreenshotSaver::~ScreenshotSaver() {
    Cleanup();
    // Shut down GDI+
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

bool ScreenshotSaver::CaptureAndSaveScreenshot(const std::wstring& filePath) {
    if (CaptureScreenshot()) {
        return SaveScreenshot(filePath);
    }
    return false;
}

bool ScreenshotSaver::CaptureScreenshot() {
    // Get the primary monitor's device context
    hScreenDC = GetDC(NULL);
    if (hScreenDC == NULL) {
        std::cerr << "Failed to get the device context." << std::endl;
        return false;
    }

    // Get the dimensions of the primary monitor
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);

    // Create a compatible DC for capturing the screen
    hMemoryDC = CreateCompatibleDC(hScreenDC);
    if (hMemoryDC == NULL) {
        std::cerr << "Failed to create compatible DC." << std::endl;
        ReleaseDC(NULL, hScreenDC);
        return false;
    }

    // Create a compatible bitmap to hold the screenshot
    hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    if (hBitmap == NULL) {
        std::cerr << "Failed to create compatible bitmap." << std::endl;
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return false;
    }

    // Select the bitmap into the memory DC
    hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    // Copy the screen contents to the memory DC
    if (!BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY)) {
        std::cerr << "Failed to BitBlt." << std::endl;
        Cleanup();
        return false;
    }

    return true;
}

bool ScreenshotSaver::SaveScreenshot(const std::wstring& filePath) {
    if (hMemoryDC == NULL || hBitmap == NULL) {
        std::cerr << "No screenshot captured." << std::endl;
        return false;
    }

    // Convert HBITMAP to GDI+ Bitmap
    Gdiplus::Bitmap bitmap(hBitmap, NULL);

    // Save the Bitmap as a PNG file
    CLSID pngClsid;
    if (GetEncoderClsid(L"image/png", &pngClsid) == -1) {
        std::cerr << "Failed to get PNG encoder CLSID." << std::endl;
        Cleanup();
        return false;
    }

    Gdiplus::Status status = bitmap.Save(filePath.c_str(), &pngClsid, NULL);
    if (status != Gdiplus::Ok) {
        std::cerr << "Failed to save screenshot as PNG." << std::endl;
        Cleanup();
        return false;
    }

    Cleanup(); // Clean up resources after saving

    std::wcout << L"Screenshot saved to: " << filePath << std::endl;
    return true;
}

void ScreenshotSaver::Cleanup() {
    if (hMemoryDC) {
        if (hOldBitmap) SelectObject(hMemoryDC, hOldBitmap);
        if (hBitmap) DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        hMemoryDC = NULL;
    }
    if (hScreenDC) {
        ReleaseDC(NULL, hScreenDC);
        hScreenDC = NULL;
    }
}

int ScreenshotSaver::GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0;
    UINT size = 0;

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0) return -1;

    Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL) return -1;

    Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }

    free(pImageCodecInfo);
    return -1;
}
