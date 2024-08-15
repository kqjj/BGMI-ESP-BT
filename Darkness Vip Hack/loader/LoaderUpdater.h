#ifndef LOADER_UPDATER_H
#define LOADER_UPDATER_H

#include <string>
#include <windows.h>
#include <wininet.h>
#include "Settings\Settings.h"

#pragma comment(lib, "wininet.lib")


class LoaderUpdater {
public:
    LoaderUpdater(const std::string& loaderVersion, const std::string& versionUrl, const std::string& loaderUrl);
    bool updateLoader();

private:
    std::string loaderVersion;
    std::string versionUrl;
    std::string loaderUrl;
    std::string readTextFromURL(const std::string& url);
    std::string randomString();
    std::string aReplaceAll(std::string subject, const std::string& search, const std::string& replace);
    std::string downloadURL(const std::string& URL);
    BOOL selfDelete();
};

#endif // LOADER_UPDATER_H
