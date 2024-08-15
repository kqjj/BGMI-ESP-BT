#ifndef SCREENSHOT_SAVER_H
#define SCREENSHOT_SAVER_H

#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <iostream>
#include <fstream>

class ScreenshotSaver {
public:
    ScreenshotSaver();
    ~ScreenshotSaver();
    bool CaptureAndSaveScreenshot(const std::wstring& filePath);

private:
    bool CaptureScreenshot();
    bool SaveScreenshot(const std::wstring& filePath);
    void Cleanup();
    int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

    HDC hScreenDC;
    HDC hMemoryDC;
    HBITMAP hBitmap;
    HBITMAP hOldBitmap;
    int width;
    int height;
    ULONG_PTR gdiplusToken;
};

#endif // SCREENSHOT_SAVER_H
