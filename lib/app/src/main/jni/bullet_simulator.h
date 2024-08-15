// bullet_simulator.h

#ifndef BULLET_SIMULATOR_H
#define BULLET_SIMULATOR_H

class BulletSimulator {
public:
    BulletSimulator(); // Constructor
    void setTotalBullets(int totalBullets);
    void setHitPercentage(double hitPercentage);
    int willItHit();
    int loseBullets();
    int getTotalBullets() const;

private:
    int totalBullets;
    double hitPercentage;
};

#endif // BULLET_SIMULATOR_H
