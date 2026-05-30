#include "ZmienGlob.h"
#include "Weapon.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <cmath>

Weapon::Weapon(std::string weaponName)
    : name(weaponName), attackFrame(0) {
    lastFrameTime = std::chrono::steady_clock::now();
}

void Weapon::render() const {
    int startY = wysokEkranu - 19;
    int startX = (szerEkranu / 2) + 10;

    const char* T = "\x1b[0m  ";                     // Przezroczysty
    const char* j = "\x1b[48;2;139;69;19m  ";        // Jasny br¹z
    const char* s = "\x1b[48;2;104;52;14m  ";        //sredni
    const char* c = "\x1b[48;2;70;35;10m  ";         // Ciemny br¹z

    const char* p = "\x1b[48;2;255;128;0m  ";      // Pomarañczowy
    const char* cp = "\x1b[48;2;200;80;0m  ";       // Ciemniejszy pomarañczowy
    const char* cz = "\x1b[48;2;220;20;20m  ";      // Czerwony
    const char* cb = "\x1b[48;2;35;15;5m  ";        // Czarno-br¹zowy

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
    if (isAttacking && attackFrame == 0 && ammo > 0) {
        ammo--;
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

Pocisk::Pocisk(float obrazenia) : obra(obrazenia) {}

void Pocisk::RysujKule(const DanePocisku& k) {

        int rozmiar = std::max(1, (int)(6.0f / (k.dystans + 0.5f)));
        int ekranX = (int)(k.x * szerEkranu);
        int ekranY = wysokEkranu / 2;

               for (int i = -rozmiar/2; i <= rozmiar/2; i++) {
                    int y = ekranY + i;
                    if (y < 0 || y >= wysokEkranu) continue;

                    Bufor += "\033[" + std::to_string(y + 1) + ";" +
                             std::to_string(ekranX + 1) + "H";

                    int jasnosc = std::min(255, (int)(255.0f / (k.dystans + 0.5f) * 3.0f));
                    Bufor += "\x1b[48;2;" + std::to_string(jasnosc) + ";" +
                             std::to_string(jasnosc/2) + ";0m";

                    for (int j = -rozmiar/2; j <= rozmiar/2; j++) {
                        int x = ekranX + j;
                        if (x >= 0 && x < szerEkranu) Bufor += " ";
                    }
                    Bufor += "\x1b[0m";
                }
}

void Pocisk::RysujWybuch(const DanePocisku& k) {
    int ekranX  = (int)(k.x * szerEkranu);
    int ekranY  = wysokEkranu / 2;
    int maxRozmiar = std::max(2, (int)(8.0f / (k.dystans + 0.5f) * 2.0f));

    int rozmiar;
    if (k.klatkaWybuchu <= 2)
        rozmiar = (k.klatkaWybuchu + 1) * maxRozmiar / 3;
    else
        rozmiar = (6 - k.klatkaWybuchu) * maxRozmiar / 3;

    if (rozmiar < 1) rozmiar = 1;

    int r, g, b;
    if      (k.klatkaWybuchu <= 1) { r=255; g=200; b=0; }
    else if (k.klatkaWybuchu <= 3) { r=255; g=80;  b=0; }
    else                           { r=150; g=30;  b=0; }

    for (int j = -rozmiar; j <= rozmiar; j++) {
        int y = ekranY + j;
        if (y < 0 || y >= wysokEkranu) continue;

        Bufor += "\033[" + std::to_string(y + 1) + ";" +
                 std::to_string(ekranX - rozmiar + 1) + "H";
        Bufor += "\x1b[48;2;" + std::to_string(r) + ";" +
                 std::to_string(g) + ";" + std::to_string(b) + "m";

        for (int i = -rozmiar; i <= rozmiar; i++) {
            int x = ekranX + i;
            if (x >= 0 && x < szerEkranu) Bufor += " ";
        }
        Bufor += "\x1b[0m";
    }
}

void Pocisk::Strzal(const Weapon& bron, std::vector<ZombieStruk>& listaZombie) {
    static bool moznaStrzelic = true;

    // Reset gdy animacja wraca do 0
    if (bron.attackFrame == 0) {
        moznaStrzelic = true;
        return;
    }

    // Strzelaj tylko w klatce 3 i tylko raz na animację
    if (bron.attackFrame != 3) return;
    if (!moznaStrzelic) return;

    moznaStrzelic = false;

    DanePocisku nowa;
    nowa.x             = 0.5f;
    nowa.dystans       = 0.5f;
    nowa.maxDystans    = 16.0f;
    nowa.klatkaWybuchu = -1;
    nowa.aktywna       = true;

    int srodek = szerEkranu / 2;
    for (auto& z : listaZombie) {
        if (!z.widoczny) continue;
        int pol = (int)(32.0f * (3.2f / z.dystans)) / 2;

        if (z.srodekX - pol <= srodek &&
            z.srodekX + pol >= srodek &&
            TabDystans[srodek] >= z.dystans) {

            z.hp -= obra;
            nowa.maxDystans = z.dystans;
        }
    }

    if (TabDystans[srodek] < nowa.maxDystans)
        nowa.maxDystans = TabDystans[srodek];

    kule.push_back(nowa);
}

void Pocisk::Aktualizuj(std::vector<ZombieStruk>& listaZombie) {
    for (auto& k : kule) {
        if (!k.aktywna) continue;

        if (k.klatkaWybuchu >= 0) {
            k.klatkaWybuchu++;
            if (k.klatkaWybuchu >= 6) k.aktywna = false;
        } else {
            k.dystans += 0.4f;
            if (k.dystans >= k.maxDystans) {
                k.klatkaWybuchu = 0; // zacznij wybuch
            }
        }

    }
       kule.erase(
        std::remove_if(kule.begin(), kule.end(),
            [](const DanePocisku& k){ return !k.aktywna; }),
        kule.end()
    );
}

void Pocisk::Renderuj() {
    for (const auto& k : kule) {
        if (!k.aktywna) continue;
        if (k.klatkaWybuchu < 0)
            RysujKule(k);
        else
            RysujWybuch(k);
    }
    Bufor += "\x1b[0m";
}
