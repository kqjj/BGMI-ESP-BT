#include "LoaderUpdater.h"
#include <iostream>
#include <random>
#include <algorithm>

LoaderUpdater::LoaderUpdater(const std::string& loaderVersion, const std::string& versionUrl, const std::string& loaderUrl)
    : loaderVersion(loaderVersion), versionUrl(versionUrl), loaderUrl(loaderUrl) {}

bool LoaderUpdater::updateLoader() {
    if (loaderVersion.empty()) {
        exit(0);
    }

    std::string versionme = readTextFromURL(versionUrl);
    std::cout << "[+] Your Version: " << loaderVersion << std::endl;
    std::cout << "[+] Current Version: " << versionme << std::endl;
  //  Settings::notifysate = versionme;

    if (versionme.find(loaderVersion) != std::string::npos) {
        std::cout << "[+] No Update needed" << std::endl;
    }
    else {
      //  system("cls");
        std::cout << "Updating Loader.." << std::endl;

        std::string str = readTextFromURL(loaderUrl); //error
        std::string dwnld_URL = str.c_str();
        std::string savepath = "AnimeTone" + randomString() + "(" + versionme + ")" + ".exe";

        URLDownloadToFileA(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);
        std::cout << "Update Is Done.. Relaunch Me";
        MessageBox(NULL, "New Update Found", "AnimeTone", MB_OKCANCEL);
        Sleep(2000);
      //  selfDelete();
        exit(0);
    }

    return true;
}

std::string LoaderUpdater::randomString() {
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(characters.begin(), characters.end(), generator);
    return characters.substr(0, 10);
}

std::string LoaderUpdater::aReplaceAll(std::string subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

std::string LoaderUpdater::downloadURL(const std::string& URL) {
    HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
    if (interwebs == NULL) {
        std::cerr << "InternetOpenA failed with error: " << GetLastError() << std::endl;
        return "";
    }

    HINTERNET urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
    if (urlFile == NULL) {
        std::cerr << "InternetOpenUrlA failed with error: " << GetLastError() << std::endl;
        InternetCloseHandle(interwebs);
        return "";
    }

    std::string rtn;
    char buffer[2000];
    DWORD bytesRead;
    do {
        if (InternetReadFile(urlFile, buffer, sizeof(buffer), &bytesRead) == FALSE) {
            std::cerr << "InternetReadFile failed with error: " << GetLastError() << std::endl;
            break;
        }
        rtn.append(buffer, bytesRead);
    } while (bytesRead > 0);

    InternetCloseHandle(urlFile);
    InternetCloseHandle(interwebs);

    return aReplaceAll(rtn, "|n", "\r\n");
}

std::string LoaderUpdater::readTextFromURL(const std::string& url) {
    std::string command = "curl -s " + url;
    std::string content;
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to execute curl command" << std::endl;
        return "";
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        content += buffer;
    }

    _pclose(pipe);

    return content;
}

BOOL LoaderUpdater::selfDelete() {
    char szFile[MAX_PATH], szCmd[MAX_PATH];

    if ((GetModuleFileNameA(0, szFile, MAX_PATH) != 0) &&
        (GetShortPathNameA(szFile, szFile, MAX_PATH) != 0)) {
        strcpy(szCmd, "/c del ");
        strcat(szCmd, szFile);
        strcat(szCmd, " >> NUL");

        if ((GetEnvironmentVariableA("ComSpec", szFile, MAX_PATH) != 0) &&
            ((INT)ShellExecuteA(0, 0, szFile, szCmd, 0, SW_HIDE) > 32))
            return TRUE;
    }

    return FALSE;
}
