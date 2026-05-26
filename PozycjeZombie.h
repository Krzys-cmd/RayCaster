#ifndef POZYCJEZOMBIE_H_INCLUDED
#define POZYCJEZOMBIE_H_INCLUDED

#include <vector>
#include "zombie.h"

inline std::vector<ZombieStruk> ListaZombieDlaMapy(int pietro) {
    std::vector<ZombieStruk> tymczasowyWektor;

    if (pietro == 0) { // Parter
        tymczasowyWektor.push_back({ 8.5f,  5.5f,  IDLE,  0 });
        tymczasowyWektor.push_back({ 12.2f, 8.4f,  IDLE,  0 });
    }
    else if (pietro == 1) { // Pierwsze piêtro
        tymczasowyWektor.push_back({ 3.0f,  14.1f, IDLE, 0 });
        tymczasowyWektor.push_back({ 7.0f,  2.5f,  IDLE,   0 });
    }
    else if (pietro == 2) { // Piwnica
        tymczasowyWektor.push_back({ 1.5f,  1.5f,  WALK,  0 });
    }

    return tymczasowyWektor;
}

#endif // POZYCJEZOMBIE_H_INCLUDED
