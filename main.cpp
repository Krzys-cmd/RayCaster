#include "fun.h"
#include "ZmienGlob.h"
#include "Mapa.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>

//dupa

bool gra=true;

int main()
{
   grafika g1;

   gracz gracz1;

   Silnik S1;

   SetConsoleOutputCP(CP_UTF8);

   std::cout << "\x1b[?25l";

    while(gra){

        auto x = std::chrono::high_resolution_clock::now();//poczatek czasu

     gracz1.akcjeGracza();
     gracz1.sterowanieGracza();
     S1.RayCaster(mapa);
     g1.bufor();

     auto y = std::chrono::high_resolution_clock::now();//koniec czasu
     auto czas_trwania=y-x;//roznicA

         if(std::chrono::microseconds(16)<czas_trwania){  //WARUNek do spania
            std::this_thread::sleep_for(std::chrono::milliseconds(16) - czas_trwania); //spanie
         }

    }

    return 0;
}
