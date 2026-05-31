#ifndef POZYCJEZOMBIE_H_INCLUDED
#define POZYCJEZOMBIE_H_INCLUDED

#include <vector>
#include "zombie.h"
#include "ZmienGlob.h"

inline bool ZombieZainicjowane[iloscMap] = {false};

inline void InicjujZombie(int pietro) {
    if (ZombieZainicjowane[pietro]) {
        return;
    }

    listaZombie.clear();

    if (pietro == 0) {
        // Mapa 0: Gracz pojawia się na (8.5, 1.5).
        // Zombie rozstawione w czystych rzędach na samym dole (y=11 i y=14)
        listaZombie.push_back({ 1.5f,  14.5f, IDLE, 0, true });
        listaZombie.push_back({ 14.5f, 14.5f, IDLE, 0, true });
        listaZombie.push_back({ 1.5f,  11.5f, WALK, 0, true });
        listaZombie.push_back({ 14.5f, 11.5f, WALK, 0, true });
        listaZombie.push_back({ 8.5f,  11.5f, IDLE, 0, true });
    }
    else if (pietro == 1) {
        // Mapa 1: Gracz pojawia się na (8.5, 14.5).
        // Zombie rozstawione w czystych rzędach na samej górze (y=1, y=3, y=4)
        listaZombie.push_back({ 1.5f,  1.5f,  IDLE, 0, true });
        listaZombie.push_back({ 14.5f, 1.5f,  IDLE, 0, true });
        listaZombie.push_back({ 3.5f,  4.5f,  WALK, 0, true });
        listaZombie.push_back({ 12.5f, 4.5f,  WALK, 0, true });
        listaZombie.push_back({ 8.5f,  3.5f,  IDLE, 0, true });
    }
    else if (pietro == 2) {
        // Mapa 2: Gracz pojawia się po lewej stronie (1.5, 8.5).
        // Zombie bezpiecznie rozstawione w pionowych korytarzach po prawej stronie (x=10 i x=14)
        listaZombie.push_back({ 14.5f, 1.5f,  IDLE, 0, true });
        listaZombie.push_back({ 14.5f, 14.5f, IDLE, 0, true });
        listaZombie.push_back({ 14.5f, 8.5f,  WALK, 0, true });
        listaZombie.push_back({ 10.5f, 4.5f,  IDLE, 0, true });
        listaZombie.push_back({ 10.5f, 12.5f, WALK, 0, true });
    }

    ZombieZainicjowane[pietro] = true;
}
#endif
