#include "fun.h"
#include "ZmienGlob.h"
#include "Mapa.h"
#include "HUD.h"
#include "Weapon.h"
#include "PozycjeZombie.h"
#include "zombie.h"
#include "grafika.h"
#include "ekrany.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>

bool gra = true;

std::string Bufor;
std::vector<ZombieStruk> listaZombie;
std::string napisInfo = "";

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    HUD myGameHud;
    Weapon stick("w");
    InicjujZombie(NumerMapy);
    ZombieRenderer z1;
    grafika g1;
    gracz gracz1;
    Silnik S1;
    Pocisk p1(20.0f);

    SetConsoleOutputCP(CP_UTF8);
    std::cout << "\x1b[?25l"; // ukrycie kursora

    //EKRAN STARTOWY
    int wybor = obslugaEkranuStartowego();
    if (wybor == 1) return 0; //EXIT

    system("cls");

    while (gra) {
        auto x = std::chrono::high_resolution_clock::now();
        klatka = ((x - startTime) / std::chrono::milliseconds(1000)) % 2 == 0;

        // Logika gracza i broni
        gracz1.akcjeGracza();
        gracz1.sterowanieGracza();
        bool attack = (GetAsyncKeyState(VK_SPACE) & 0x8000);
        stick.update(attack);
        p1.Strzal(stick, listaZombie);
        p1.Aktualizuj(listaZombie);

        myGameHud.update(HpGracz, ammo, pts);

        // Logika œmierci
        if (HpGracz <= 0.0f) {
            zycia -= 1;
            bool kontynuuj = obslugaEkranuSmierci(zycia, HpGracz, fGraczX, fGraczY, NumerMapy);

            if (kontynuuj) {
                // Jeœli gracz ¿yje, resetujemy pozycjê
                fGraczX = TabelaPozycjiPowrotu[NumerMapy].x;
                fGraczY = TabelaPozycjiPowrotu[NumerMapy].y;
            }
            else {
                return 0; // Game Over
            }
        }

        // Logika wygranej
        if (listaZombie.empty()) {
            obslugaEkranuWygranej(); 
            return 0;                // EXIT
        }

        // rysowanie klatek gry
        S1.RayCaster(mapa);
        S1.PrzejsciaPrzezPokoje(mapa);

        g1.BuforMapa();
        z1.ZombieBufor(listaZombie);
        stick.render();
        myGameHud.render();
        p1.Renderuj();

        g1.wypiszBufor();

        auto y = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::milliseconds>(y - x);
        if (czas_trwania < std::chrono::milliseconds(16)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16) - czas_trwania);
        }
    }

    return 0;
}