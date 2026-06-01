#include "fun.h"
#include "ZmienGlob.h"
#include "Mapa.h"

#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>
#include <windows.h>

void gracz::akcjeGracza() {
    if (_kbhit()) {
        char key = _getch();

        if (key == 'c') {
            system("cls");
            //pts += 10;
        }
        if (key == 'e' && pts >= 50) {
            DrzwiOtworz = true;
            pts = 0;
        }
        else if(key == 'e' && pts < 50){
            napisInfo = " ZA  MALO  PKT ";
            napisInfoKlatki = 90; // 2 sekundy przy 60fps
        }
       // if (key == 'r') {
        //    ammo = 8;
        //}
    }
}

void gracz::sterowanieGracza() {

    float fChodSzyb = 0.075f; //predksoc chodzenia
    float fObrSzyb = 0.05f; //predksoc obrotu


    if (GetAsyncKeyState('A') & 0x8000) {
        fGraczaKat -= fObrSzyb;
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        fGraczaKat += fObrSzyb;
    }

    fGraczaKat = fmodf(fGraczaKat, 2.0f * 3.14159f);
    if (fGraczaKat < 0.0f) fGraczaKat += 2 * PI;

    float fKierune = 0.0f;
    if (GetAsyncKeyState('W') & 0x8000) fKierune = 1.0f;  // Przód
    if (GetAsyncKeyState('S') & 0x8000) fKierune = -1.0f; // Tył

    if (fKierune != 0.0f) {


        float fDeltaX = sinf(fGraczaKat) * fChodSzyb * fKierune;
        float fDeltaY = cosf(fGraczaKat) * fChodSzyb * fKierune;

        float fNoweX = fGraczX + fDeltaX;
        float fNoweY = fGraczY + fDeltaY;

        if (fNoweX >= 0 && fNoweX < SzerMapy) {
            if (mapa[NumerMapy][(int)fGraczY][(int)(fGraczX + fDeltaX)] != 1) {
                fGraczX += fDeltaX;
            }
        }

        if (fNoweY >= 0 && fNoweY < WysMapy) {
            if (mapa[NumerMapy][(int)(fGraczY + fDeltaY)][(int)fGraczX] != 1) {
                fGraczY += fDeltaY;
            }
        }



    }//przod tyl

}
