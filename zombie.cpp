#include "zombie.h"
#include "ZombieKlatki.h"
#include "cmath"
#include "algorithm"
#include "ZmienGlob.h"

KolorRGB ZombieRenderer::PobierzBazowyKolor(int idKoloru) {
    switch (idKoloru) {
        case 1:  return { 55, 145,  55 }; // Zielony (Skóra)
        case 2:  return { 190,  15,  15 }; // Czerwony (Krew)
        case 3:  return { 110,  75,  35 }; // Br¹zowy (Tunika)
        case 4:  return { 150, 150, 150 }; // Szary (Koœci)
        //case 4:  return  { 190,  15,  15};
        default: return {   0,   0,   0 }; // Czarny
    }
}

float ZombieRenderer::mapuj(float x, float in_min, float in_max, float out_min, float out_max) {
    if (x < in_min) x = in_min;
    if (x > in_max) x = in_max;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

std::string ZombieRenderer::PobierzKolorTlaANSI(int idKoloru, float jasnosc) {
    KolorRGB baza = PobierzBazowyKolor(idKoloru);
    float Njasnosc = std::clamp(jasnosc * 0.8f, 0.05f, 1.0f);
    int r = static_cast<int>(baza.r * Njasnosc);
    int g = static_cast<int>(baza.g * Njasnosc);
    int b = static_cast<int>(baza.b * Njasnosc);

    return "48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
}

std::string ZombieRenderer::PobierzKolorCzcionkiANSI(int idKoloru, float jasnosc) {
    KolorRGB baza = PobierzBazowyKolor(idKoloru);
    float Njasnosc = std::clamp(jasnosc * 0.8f, 0.05f, 1.0f);
    int r = static_cast<int>(baza.r * Njasnosc);
    int g = static_cast<int>(baza.g * Njasnosc);
    int b = static_cast<int>(baza.b * Njasnosc);

    return "38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
}

void ZombieRenderer::pozycjaZombie(ZombieStruk& z) {
    float fWektorX = z.x - fGraczX;
    float fWektorY = z.y - fGraczY;

    z.dystans = std::sqrt(fWektorX * fWektorX + fWektorY * fWektorY);
    if (z.dystans < 0.1f) z.dystans = 0.1f;

    float fKatDoZombie = std::atan2(fWektorX, fWektorY);

    float fRoznicaKata = fKatDoZombie - fGraczaKat;
    while (fRoznicaKata < -3.14159f) fRoznicaKata += 2.0f * 3.14159f;
    while (fRoznicaKata >  3.14159f) fRoznicaKata -= 2.0f * 3.14159f;


    float skala = 8.0f / z.dystans;
    int polszerokoscZombie = static_cast<int>(32.0f * skala) / 2;

    z.srodekX = static_cast<int>(
        (fRoznicaKata + fFOV / 2.0f) / fFOV * (float)szerEkranu
    );

    // Widoczny tylko jeśli choć jeden piksel zombie jest na ekranie
    if (z.srodekX + polszerokoscZombie < 0 ||
        z.srodekX - polszerokoscZombie >= szerEkranu) {
        z.widoczny = false;
        return;
    }

    z.widoczny = true;
}

void ZombieRenderer::RenderujKlatke(const ZombieStruk& z) {
    int RozmairZombie = 32;
    if (!z.widoczny) return;
    const char* polBlok = "\xE2\x96\x84";

    float skalaX = 3.2f / z.dystans;
    float skalaY = 2.0f / z.dystans;



    int nowyRozmiarX = static_cast<int>(std::round((float)RozmairZombie * skalaX));
    int nowyRozmiarY = static_cast<int>(std::round((float)RozmairZombie * skalaY));

    if (nowyRozmiarY > 64) nowyRozmiarY = 64;

    int StartPromien = z.srodekX - (nowyRozmiarX / 2);
    int StartY = (wysokEkranu /2 ) - (nowyRozmiarY / 2);


    if (StartY < 0) StartY = 0;

     int test = std::min(nowyRozmiarY, wysokEkranu - StartY);

    for (int i = 0; i < test; i ++) {

        int aktualnyY = StartY + i;
        if (aktualnyY >= wysokEkranu) break;

        int poczatkowyX = (StartPromien < 0) ? 0 : StartPromien;
        Bufor += "\033[" + std::to_string(aktualnyY + 1) + ";" + std::to_string(poczatkowyX + 1) + "H";

        for (int j = 0; j < nowyRozmiarX; j++) {
            int obecnyPromien = StartPromien + j;

            if (obecnyPromien < 0 || obecnyPromien >= szerEkranu) {
                continue;
            }

            if (TabDystans[obecnyPromien] < z.dystans) {
                Bufor += "\033[1C";
                continue;
            }

            int noweI  = static_cast<int>(i / skalaY);
            int noweI2 = static_cast<int>((i + 1)/ skalaY);
            int noweJ  = static_cast<int>(j / skalaX);

            if (noweI  >= RozmairZombie) noweI  = RozmairZombie - 1;
            if (noweI2 >= RozmairZombie) noweI2 = RozmairZombie - 1;
            if (noweJ  >= RozmairZombie) noweJ  = RozmairZombie - 1;

            int kolorGora = KlatkiZombie[0][0][noweI][noweJ];
            int kolorDol = KlatkiZombie[0][0][noweI2][noweJ];

            if (kolorDol == 0 && kolorGora == 0) {
                Bufor += "\033[0m";
                Bufor += "\033[1C"; //przeskok na nastepna kratke
                continue;
            }

            std::string bg = PobierzKolorTlaANSI(kolorGora, skalaX);
            std::string fg = PobierzKolorCzcionkiANSI(kolorDol, skalaX);

            Bufor += ("\033[" + fg + ";" + bg + "m" + polBlok);
        }

    }

}

void ZombieRenderer::ZombieBufor(std::vector<ZombieStruk>& listaZombie) {

    for (auto& z : listaZombie) {
        pozycjaZombie(z);
    }
    std::sort(listaZombie.begin(), listaZombie.end(), [](const ZombieStruk& a, const ZombieStruk& b) {
        return a.dystans > b.dystans;
    });

    for (const auto& z : listaZombie) {
        if (z.widoczny) {
            RenderujKlatke(z);
        }
    }
}

