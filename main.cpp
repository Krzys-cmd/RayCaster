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

int main()
{

    auto startTime = std::chrono::high_resolution_clock::now(); //zegar pomocniczy

    HUD myGameHud;

    Weapon stick("w");

    InicjujZombie(NumerMapy);//wektor z zombie

    ZombieRenderer z1;
    grafika g1;
    gracz gracz1;
    Silnik S1;
    Pocisk p1(20.0f);//dmg kuli (ataku gracza)

    SetConsoleOutputCP(CP_UTF8);
    std::cout << "\x1b[?25l";//ukrycie kursora

    StartScreen menuStartowe;
    int wyborMenu = 0;
    bool wMenu = true;

    while (wMenu) {
        if (GetAsyncKeyState('W') & 0x8000) wyborMenu = 0;
        if (GetAsyncKeyState('S') & 0x8000) wyborMenu = 1;

        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (wyborMenu == 0) wMenu = false;
            else if (wyborMenu == 1) return 0;
        }

        Bufor.clear();
        menuStartowe.render(wyborMenu);
        g1.wypiszBufor();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    system("cls");
//g:
    while (gra) {
        auto x = std::chrono::high_resolution_clock::now();

        // Wyliczanie klatki dla animacji broni/zombie
        klatka = ((x - startTime) / std::chrono::milliseconds(1000)) % 2 == 0;

        gracz1.akcjeGracza();
        gracz1.sterowanieGracza();


        bool attack = (GetAsyncKeyState(VK_SPACE) & 0x8000);
        stick.update(attack);
        p1.Strzal(stick, listaZombie);  // logika strza³u
        p1.Aktualizuj(listaZombie);     // ruch kuli

        //test
        //ammo -= 0.05f;
       // pts += 0.05f;
       // HpGracz -= 0.1f;

        myGameHud.update(HpGracz, ammo, pts);

         std::cout << NumerMapy;
        if (HpGracz <= 0.0f) {
            zycia -= 1;

            DeathScreen deathScreen;
            int wyborMenu = 0;
            bool wEkranie = true;

            std::this_thread::sleep_for(std::chrono::milliseconds(400));

            while (wEkranie) {
                if (zycia <= 0) {
                    if (GetAsyncKeyState('W') & 0x8000) wyborMenu = 0;
                    if (GetAsyncKeyState('S') & 0x8000) wyborMenu = 1;
                }
                else {
                    wyborMenu = 0;
                }

                if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                    if (zycia > 0) {

                        HpGracz = 100.0f;
                        fGraczX = TabelaPozycjiPowrotu[NumerMapy].x;//nowy spawn
                        fGraczY = TabelaPozycjiPowrotu[NumerMapy].y;
                        wEkranie = false;
                    }
                    else {
                        if (wyborMenu == 0) {
                            zycia = 3;
                            HpGracz = 100.0f;
                            ammo = 8.0f;
                            pts = 0.0f;
                            NumerMapy = 0;
                             fGraczX = 2.5f;
                             fGraczY = 1.5f;
                            wEkranie = false;
                        }
                        else if (wyborMenu == 1) {
                            return 0;
                        }

                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(400));
                }

                Bufor.clear();
                deathScreen.render(wyborMenu, zycia);
                g1.wypiszBufor();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            }
        //test-ekran wygrana

        if (listaZombie.empty()) {
            YouWinScreen youWinScreen;
            int wyborWinMenu = 0;
            bool wWinEkranie = true;

            // Krótka pauza zabezpieczaj¹ca przed natychmiastowym zatwierdzeniem
            std::this_thread::sleep_for(std::chrono::milliseconds(400));

            while (wWinEkranie) {
                if (GetAsyncKeyState('W') & 0x8000) wyborWinMenu = 0;
                if (GetAsyncKeyState('S') & 0x8000) wyborWinMenu = 1;

                if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                    if (wyborWinMenu == 0) {
                        // Reset gry, aby graæ od nowa (ZAGRAJ PONOWNIE)
                        zycia = 3;
                        HpGracz = 100.0f;
                        ammo = 8.0f;
                        pts = 0.0f;
                        NumerMapy = 0;
                        fGraczX = 2.5f;
                        fGraczY = 1.5f;
                        InicjujZombie(NumerMapy); // Odrodzenie zombie
                        wWinEkranie = false;
                        //goto g;
                    }
                    else if (wyborWinMenu == 1) {
                        // Wyjœcie z gry (EXIT)
                        return 0;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(400));
                }

                Bufor.clear();
                youWinScreen.render(wyborWinMenu);
                g1.wypiszBufor();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }


        S1.RayCaster(mapa);//logika tla
        S1.PrzejsciaPrzezPokoje(mapa);

        //aktualzicja bufora
        g1.BuforMapa();
        z1.ZombieBufor(listaZombie);
        stick.render();
        myGameHud.render();
        p1.Renderuj();

        g1.wypiszBufor();//wypiasanie na ekran wszytskiego

        auto y = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::milliseconds>(y - x);

        if (czas_trwania < std::chrono::milliseconds(16)) { //kontorla fps
            std::this_thread::sleep_for(std::chrono::milliseconds(16) - czas_trwania);
        }
    }//petla gry

    return 0;
}
