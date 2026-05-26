#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <algorithm> // Dodano dla std::clamp


enum StanZombie {
    IDLE = 0,
    WALK = 1,
    ATTACK = 2
};

struct KolorRGB {
    int r, g, b;
};

struct ZombieStruk {
    float x;               // pozycja x na mapie
    float y;               // pozycja y na mapie
    StanZombie stan;       // stan animacji
    int klatka;            // klatka (0 lub 1)
    float dystans;         // odleg³oœæ od gracza
    int srodekX;           // Numer kolumny (promienia) na ekranie, gdzie wypada œrodek Zombie
    bool widoczny;         // Flaga okreœlaj¹ca, czy Zombie znajduje siê w FOV gracza
};

class ZombieRenderer {
public:


    std::string bufor;
    float odleglosc;
    StanZombie obecnyStan;
    int klatkaAnimacji;
    int licznikPetli;

    KolorRGB PobierzBazowyKolor(int idKoloru);
    float mapuj(float x, float in_min, float in_max, float out_min, float out_max);

    std::string PobierzKolorTlaANSI(int idKoloru, float jasnosc);
    std::string PobierzKolorCzcionkiANSI(int idKoloru, float jasnosc);

    void RenderujKlatke(const ZombieStruk& z);
    void ZombieBufor(std::vector<ZombieStruk>& listaZombie);
    void pozycjaZombie(ZombieStruk& z);

};


#endif // ZOMBIE_H_INCLUDED
