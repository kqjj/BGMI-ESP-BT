// bullet_simulator.cpp

#include "bullet_simulator.h"
#include <cstdlib>
#include <ctime>

BulletSimulator::BulletSimulator() {
    srand(time(0)); // Seed the random number generator
}

void BulletSimulator::setTotalBullets(int totalBullets) {
    this->totalBullets = totalBullets;
}

void BulletSimulator::setHitPercentage(double hitPercentage) {
    this->hitPercentage = hitPercentage;
}

int BulletSimulator::willItHit() {
    // Generate a random number between 0 and 1
    double randomness = (double)rand() / RAND_MAX;

    // If the random number is less than the specified hitPercentage, return 1 (hit); otherwise, return 0 (miss)
    if (randomness < hitPercentage) {
        return 1;
    } else {
        return 0;
    }
}

int BulletSimulator::loseBullets() {
    // Calculate the number of bullets to lose (30% of total bullets)
    int bulletsToLose = totalBullets * hitPercentage;

    // Update the total number of bullets after losing 30%
    totalBullets -= bulletsToLose;

    // Return the new total number of bullets
    return totalBullets;
}

int BulletSimulator::getTotalBullets() const {
    return totalBullets;
}
