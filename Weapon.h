#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <chrono>

class Weapon {
private:
    std::string name;
    bool isFiring;
    int attackFrame;

    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;
public:
    Weapon(std::string weaponName);

    void render() const;
    void update(bool isAttacking);
};

#endif 