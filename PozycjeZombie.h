#ifndef POZYCJEZOMBIE_H_INCLUDED
#define POZYCJEZOMBIE_H_INCLUDED

#include <vector>
#include "zombie.h"
#include "ZmienGlob.h"

inline void InicjujZombie(int pietro) {
    listaZombie.clear();
    if (pietro == 0) {
        listaZombie.push_back({ 8.5f,  6.0f,  IDLE, 0, true });
        listaZombie.push_back({ 12.2f, 8.4f,  IDLE, 0, true });
    }
    else if (pietro == 1) {
        listaZombie.push_back({ 3.0f,  14.1f, IDLE, 0, true });
        listaZombie.push_back({ 7.0f,  2.5f,  IDLE, 0, true });
    }
    else if (pietro == 2) {
        listaZombie.push_back({ 1.5f,  1.5f,  WALK, 0, true });
    }
}

#endif