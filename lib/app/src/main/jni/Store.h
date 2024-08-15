#ifndef STORE_H
#define STORE_H

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Store {
private:
    std::vector<std::string> boneInventory;
    std::vector<std::string> availableBones;

public:
    Store(const std::vector<std::string>& inventory) : boneInventory(inventory) {}

    void updateAvailability(const std::string& content);
    std::string getRandomAvailableBone();
    void clearAvailableBoneArray();
};

#endif
