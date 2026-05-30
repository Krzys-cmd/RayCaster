#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <chrono>
#include <vector>
#include "zombie.h"

class Weapon {
protected:
    std::string name;
    bool isFiring;
    int attackFrame;

    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;
public:
    Weapon(std::string weaponName);

    void render() const;
    void update(bool isAttacking);

   friend class Pocisk;
};

struct DanePocisku {
    float x;
    float dystans;
    float maxDystans;
    int klatkaWybuchu;
    bool aktywna;
};

class Pocisk {
    std::vector<DanePocisku> kule;
    float obra;

public:
    Pocisk(float obrazenia);

    void RysujKule(const DanePocisku& k);
    void Strzal(const Weapon& bron, std::vector<ZombieStruk>& listaZombie);
    void RysujWybuch(const DanePocisku& k);
    void Aktualizuj(std::vector<ZombieStruk>& listaZombie);
    void Renderuj();
};
#endif
