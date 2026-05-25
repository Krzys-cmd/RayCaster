#include "ZmienGlob.h"
#include "Weapon.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

Weapon::Weapon(std::string weaponName)
    : name(weaponName), attackFrame(0) {
    lastFrameTime = std::chrono::steady_clock::now();
}

void Weapon::render() const {
    int startY = wysokEkranu - 19;
    int startX = (szerEkranu / 2)+10 ;

    const char* T = "\x1b[0m  ";                     // Przezroczysty (brak t³a)
    const char* j = "\x1b[48;2;139;69;19m  ";        // Jasny br¹z
    const char* s = "\x1b[48;2;104;52;14m  ";        //sredni
    const char* c = "\x1b[48;2;70;35;10m  ";         // Ciemny br¹z

    const char* p = "\x1b[48;2;255;128;0m  ";      // Pomarañczowy (jasny i soczysty)
    const char* cp = "\x1b[48;2;200;80;0m  ";       // Ciemniejszy pomarañczowy (wpadaj¹cy w rdzawy)
    const char* cz = "\x1b[48;2;220;20;20m  ";      // Czerwony (krwisty, nie za jaskrawy)
    const char* cb = "\x1b[48;2;35;15;5m  ";        // Czarno-br¹zowy (bardzo ciemny, idealny na krawêdzie drewna)

    //bez ataku
    const char* attack_1[20][16] = {
{ T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T },
{ T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T },
{ T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T },
{ T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T },
{ T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T },
{ T, T, T, T, T, T, T, T, T, T, c, s, T, T, T, T },
{ T, T, T, T, T, T, T, T, T, T, c, s, T, T, T, T },
{ T, T, T, T, T, T, T, T, c, s, j, c, T, T, T, T },
{ T, T, T, T, T, T, T, T, s, j, s, T, T, T, T, T },
{ T, T, T, T, T, T, T, c, j, s, c, T, T, T, T, T },
{ T, T, T, T, T, T, T, c, j, s, T, T, T, T, T, T },
{ T, T, T, T, T, T, T, s, j, c, T, T, T, T, T, T },
{ T, T, T, T, T, T, s, j, s, T, T, T, T, T, T, T },
{ T, T, T, T, T, T, s, j, c, T, T, T, T, T, T, T },
{ T, T, T, T, T, s, j, s, T, T, T, T, T, T, T, T },
{ T, T, T, T, c, j, s, c, T, T, T, T, T, T, T, T },
{ T, T, T, T, s, j, c, T, T, T, T, T, T, T, T, T },
{ T, T, T, s, j, c, T, T, T, T, T, T, T, T, T, T },
{ T, T, c, j, j, c, T, T, T, T, T, T, T, T, T, T },
{ T, T, c, j, s, T, T, T, T, T, T, T, T, T, T, T },
    };

    const char* attack_2[20][16] = {
    { T, T, T, T, cb, cb, cz, cz, T, T, T, T, T, T, T, T },
    { T, T, T, cb, cp, p, p, cp, cb, T, p, T, T, T, T, T },
    { T, T, T, cz, p, cz, cp, p, cb, T, T, T, T, T, T, T },
    { T, p, T, cb, cz, p, cz, cp, cz, T, T, p, T, T, T, T },
    { T, T, T, cb, p, cp, p, p, cb, T, T, T, T, T, T, T },
    { T, T, T, T, cz, cz, cb, cb, T, T, c, s, T, T, T, T },
    { T, T, T, T, T, T, T, T, T, T, c, s, T, T, T, T },
    { T, T, T, T, p, T, T, T, c, s, j, c, T, T, T, T },
    { T, T, T, T, T, T, T, s, j, s, T, T, T, T, T, T },
    { T, T, T, T, T, T, T, c, j, s, c, T, T, T, T, T },
    { T, T, T, T, T, T, T, c, j, s, T, T, T, T, T, T },
    { T, T, T, T, T, T, T, s, j, c, T, T, T, T, T, T },
    { T, T, T, T, T, T, s, j, s, T, T, T, T, T, T, T },
    { T, T, T, T, T, T, s, j, c, T, T, T, T, T, T, T },
    { T, T, T, T, T, s, j, s, T, T, T, T, T, T, T, T },
    { T, T, T, T, c, j, s, c, T, T, T, T, T, T, T, T },
    { T, T, T, T, s, j, c, T, T, T, T, T, T, T, T, T },
    { T, T, T, s, j, c, T, T, T, T, T, T, T, T, T, T },
    { T, T, c, j, j, c, T, T, T, T, T, T, T, T, T, T },
    { T, T, c, j, s, T, T, T, T, T, T, T, T, T, T, T },
    };

    const char* attack_3[20][16] = {
    { T, T, T,  cb, cb, cz, cz,T, T, T, T, T, T, T, T, T },
    { T, T, cb, cp, p, p, cp, cb,T, T, T, T, T, T, T, T },
    { T, T,  cz, p, cz, cp, p, cb,T, p, T, T, T, T, T, T },
    { T,  T, cb, cz, p, cz, cp, cz,T, T, T,T, T, T, T, T },
    { T, p,  cb, p, cp, p, p, cb, T,T, T, T, T, T, T, T },
    { T, T, T, cz, cz, cb, cb, T, T, c, s, T,T, T, T, T },
    { T, T, p, T, T, T, T, T, T, c, s, T, T,T, T, T },
    { T, T, T, T, T, T, T, c, s, j, c, T,T, T, T, T },
    { T, T, T, T, T, T, T,  s, j, s, T,T, T, T, T, T },
    { T, T, T, T, T, T, T, s, j, s, T, T,T, T, T, T },
    { T, T, T, T, T, T, c, j, s, T,T, T, T, T, T, T },
    { T, T, T, T, T, T, s, j, c, T,T, T, T, T, T, T },
    { T, T, T, T, T, s, j, s, T,T, T, T, T, T, T, T },
    { T, T, T, T, T, s, j, c, T,T,T, T, T, T, T, T },
    { T, T, T, T, s, j, s, T,T, T, T, T, T, T, T, T },
    { T, T, T, c, j, s, c, T, T,T, T, T, T, T, T, T },
    { T, T, T, s, j, c, T, T,T, T, T, T, T, T, T, T },
    { T, T, s, j, c, T,T, T, T, T, T, T, T, T, T, T },
    { T, T, c, j, j, c, T, T, T, T, T, T, T, T, T, T },
    { T, T, c, j, s, T, T, T, T, T, T, T, T, T, T, T },
    };

    const char* attack_4[20][16] = {
    { T, T,  cb, cb, cz, cz,T, T, T, T, T, T, T, T, T, T },
    { T,  cb, cp, p, p, cp, cb, T, T,T, T, T, T, T, T, T },
    { T,  cz, p, cz, cp, p, cb, T,p, T, T, T, T, T, T, T },
    { T,  cb, cz, p, cz, cp, cz, T, T, T,T, p, T, T, T, T },
    { T,  cb, p, cp, p, p, cb, T, T,T, T, T, T, T, T, T },
    { T, T, cz, cz, cb, cb, T, T, c, s, T, T,T, T, T, T },
    { T, T, T, T, T, T, T,  c, s, T,T,T, p, T, T, T },
    { T, T, p, T,T, T, c, s, j, c, T, T,T, T, T, p },
    { T, T, T, T, T, T, s, j, s, T, T, T,T, p, T, T },
    { T, T, T, T, T,  c, j, s, c, T, T, T, T, T,T, T },
    { T, T, T, T, T,  c, j, s, T, T, T, T, T,T, T, T },
    { T, T, T, T,   s, j, c, T, T,T, T, T, T,T, T, T },
    { T, T, T,  s, j, s, T,T, T,T, T, T, T, T, T, T },
    { T, T, T,  s, j, c, T,T,T, T, T, T, T, T, T, T },
    { T, T, T,  s, j, s, T,T, T,T, T, T, T, T, T, T },
    { T, T, c, j, s, c, T,T, T, T, T, T, T, T, T, T },
    { T, T, s, j, c, T,T,T, T, T, T, T, T, T, T, T },
    { T, T, s, j, c, T,T, T, T, T, T, T, T, T, T, T },
    { T, T, c, j, j, c, T, T, T, T, T, T, T, T, T, T },
    { T, T, c, j, s, T, T, T, T, T, T, T, T, T, T, T },
    };


    if (attackFrame == 0) {
        // Spoczynek (attack_1)
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 16; x++) {
                if (attack_1[y][x] != T) {
                    Bufor += "\x1b[" + std::to_string(startY + y) + ";" + std::to_string(startX + (x * 2)) + "H" + attack_1[y][x];
                }
            }
        }
    }
    else if (attackFrame == 1) {
        // Klatka ataku 1
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 16; x++) {
                if (attack_2[y][x] != T) {
                    Bufor += "\x1b[" + std::to_string(startY + y) + ";" + std::to_string(startX + (x * 2)) + "H" + attack_2[y][x];
                }
            }
        }
    }
    else if (attackFrame == 2) {
        // Klatka ataku 2
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 16; x++) {
                if (attack_3[y][x] != T) {
                    Bufor += "\x1b[" + std::to_string(startY + y) + ";" + std::to_string(startX + (x * 2)) + "H" + attack_3[y][x];
                }
            }
        }
    }
    else if (attackFrame == 3) {
        // Klatka ataku 3
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 16; x++) {
                if (attack_4[y][x] != T) {
                    Bufor += "\x1b[" + std::to_string(startY + y) + ";" + std::to_string(startX + (x * 2)) + "H" + attack_4[y][x];
                }
            }
        }
    }
    Bufor += "\x1b[0m";
}


void Weapon::update(bool isAttacking) {
    // Pobierz aktualny czas
    auto currentTime = std::chrono::steady_clock::now();

    // Oblicz, ile milisekund minê³o od ostatniej zmiany klatki
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime).count();

    // Jeœli gracz klika atak i jeszcze nie zaczêliœmy animacji (jest 0), zacznij natychmiast
    if (isAttacking && attackFrame == 0) {
        attackFrame = 1;
        lastFrameTime = currentTime; // Zresetuj zegar
    }
    // Jeœli animacja ju¿ trwa (jest wiêksza od 0)
    else if (attackFrame > 0) {

        // Zmieñ klatkê TYLKO jeœli up³ynê³o np. 150 milisekund
        if (elapsedTime > 150) {
            attackFrame++;
            lastFrameTime = currentTime; // Zresetuj zegar dla nastêpnej klatki

            // Jeœli animacja dobieg³a koñca, wróæ do pozycji 0
            if (attackFrame > 3) {
                attackFrame = 0;
            }
        }
    }
}
