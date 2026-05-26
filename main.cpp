#include "fun.h"
#include "ZmienGlob.h"
#include "Mapa.h"
#include "HUD.h"
#include "Weapon.h"
#include "PozycjeZombie.h"
#include "zombie.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>


bool gra = true;

int main()
{

    HUD myGameHud;
    float hp = 12, ammo = 30, pts = 0;

    Weapon stick("w");




    ZombieRenderer z1;
    grafika g1;
    gracz gracz1;
    Silnik S1;

    SetConsoleOutputCP(CP_UTF8);// //utf 8

    std::cout << "\x1b[?25l";//ukrycie kursora

    while (gra) {

        auto x = std::chrono::high_resolution_clock::now();//poczatek czasu

        std::vector<ZombieStruk> ListaZombie = ListaZombieDlaMapy(NumerMapy);//vectro z pozcyajmi zombie

        gracz1.akcjeGracza();
        gracz1.sterowanieGracza();
        S1.RayCaster(mapa);
        S1.PrzejsciaPrzezPokoje(mapa);
        g1.BuforMapa();
        z1.ZombieBufor(ListaZombie);

        //zmiany w hp itd..........
                                            myGameHud.render();

                                                        stick.render();

                                                        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                                                            attack = true;
                                                        }
                                                        else {
                                                            attack = false;
                                                        }

                                                           stick.update(attack);

                                                            stick.render();

                                            hp -= 0.5f;
                                            ammo -= 1.0f;
                                            pts += 2.0f;

                                            myGameHud.update(hp, ammo, pts);

        g1.wypiszBufor();



        auto y = std::chrono::high_resolution_clock::now();//koniec czasu
        auto czas_trwania = y - x;//roznicA

        if (std::chrono::microseconds(16) < czas_trwania) {  //WARUNek do spania
            std::this_thread::sleep_for(std::chrono::milliseconds(16) - czas_trwania); //spanie
        }

    }

    return 0;
}
