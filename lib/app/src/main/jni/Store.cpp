#include "Store.h"
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <cassert>  // Include the assert header

void Store::updateAvailability(const std::string& content) {
    for (const auto& item : boneInventory) {
        if (content == item) {
            availableBones.push_back(item);
        }
    }
}

std::string Store::getRandomAvailableBone() {
    if (!availableBones.empty()) {
        std::random_device rd;  // Non-deterministic random number generator
        std::uniform_int_distribution<int> dist(0, availableBones.size() - 1);
        int index = dist(rd);  // Generate a random index directly
        if(index < 0 || index >= availableBones.size()){
            //LOGI("Error encountered index num out of range");
            index = rand() % availableBones.size();
        }
        //LOGI("Array Size : %d", availableBones.size());
        //LOGI("rand %d", index);
        return availableBones[index];
    }
    return "";
}

void Store::clearAvailableBoneArray() {
    availableBones.clear();  // Explicitly clears the available items array
}
