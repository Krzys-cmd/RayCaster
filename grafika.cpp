#include "ZmienGlob.h"
#include "grafika.h"
#include "Mapa.h"
#include "fun.h"
#include "PozycjeZombie.h"

#include <windows.h>


void grafika::BuforMapa() {


    for (int i = 0; i < wysokEkranu; i++) {
        for (int j = 0; j < iloscPromieni; j++) {

            if (i < (int)TabSufit[j]) {//sufit

                Bufor += " ";
            }

            else if (i == (int)TabSufit[j]) { //gorne krawedz
                if (TabSufit[j] - (float)(int)(TabSufit[j]) < 0.5) {

                    float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);
                    int r = (int)(255 * fCien);
                    if (TabScianaPozioma[j]) r *= 0.7;

                    if (TabDrzwi[j] == 1) {
                        Bufor += "\x1b[48;2;20;60;\x1b[38;2;20;60;0m";
                    }
                    else Bufor += "\x1b[38;2;" + std::to_string(r) + ";0;0m"; // Kolor ściany (tekst)

                    Bufor += "\xE2\x96\x84"; // Znak ▄
                    Bufor += "\x1b[0m";

                }
                else Bufor += " ";

            }
            else if (i > (int)TabSufit[j] && i < (int)TabPodloga[j]) { //srodek sciany

                //int r = (int)mapuj(TabDystans[j], 0.0f, 16.0f, 255.0f, 50.0f); //mapowanie koloru

                float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);//mapowanie cienia
                int r = (int)(255 * fCien);
                if (TabScianaPozioma[j] == true)  r *= 0.7;



                if (TabDrzwi[j] == 1) {
                    Bufor += "\x1b[48;2;20;60;0m \x1b[0m";
                }
                else Bufor += "\x1b[48;2;" + std::to_string(r) + ";0;0m \x1b[0m";

            }
            else if (i == (int)TabPodloga[j]) { //dolna krawedz
                if (TabPodloga[j] - (float)(int)(TabPodloga[j]) < 0.5) {

                    float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);
                    int r = (int)(255 * fCien);
                    if (TabScianaPozioma[j]) r *= 0.7;
                    int szary = (int)mapuj(i, wysokEkranu / 2, wysokEkranu, 10.0f, 100.0f);

                    if (TabDrzwi[j] == 1) {
                        Bufor += "\x1b[38;2;20;60;0m";
                    }
                    else {
                        Bufor += "\x1b[38;2;" + std::to_string(r) + ";0;0m"; // góra (ściana)

                    }


                    Bufor += "\x1b[48;2;" + std::to_string(szary) + ";" + std::to_string(szary) + ";" + std::to_string(szary) + "m"; // dół (podłoga)
                    Bufor += "\xE2\x96\x80"; // ▀
                    Bufor += "\x1b[0m";



                }
                else {
                    float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);//mapowanie cienia
                    int r = (int)(255 * fCien);
                    if (TabScianaPozioma[j] == true)  r *= 0.7;

                    if (TabDrzwi[j] == 1) {
                        Bufor += "\x1b[48;2;20;60;0m \x1b[38;2;20;60;0m";
                    }
                    else Bufor += "\x1b[48;2;" + std::to_string(r) + ";0;0m \x1b[0m";
                };

            }
            else if (i > (int)TabPodloga[j]) {//podloga
                int szary = (int)mapuj(i, wysokEkranu / 2, wysokEkranu, 10.0f, 100.0f);
                Bufor += "\x1b[48;2;" + std::to_string(szary) + ";" + std::to_string(szary) + ";" + std::to_string(szary) + "m \x1b[0m";
            }


        }
        Bufor += "\n";
    }

        if (napisInfoKlatki > 0) {
            Bufor += "\x1b[0m";
            Bufor += "\x1b[" + std::to_string((wysokEkranu / 2)+9) + ";" +
            std::to_string((szerEkranu / 2) - (int)(napisInfo.length() / 2)) + "H";
            Bufor += "\x1b[38;2;255;50;50m" + napisInfo + "\x1b[0m";
            napisInfoKlatki--;
            }

}

float grafika::mapuj(float x, float in_min, float in_max, float out_min, float out_max) {
    if (x < in_min) x = in_min;
    if (x > in_max) x = in_max;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void grafika::wypiszBufor() {
    Bufor += "\x1b[H";


    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteFile(hOut, Bufor.c_str(), (DWORD)Bufor.size(), &written, nullptr);

    //std::cout<<Bufor;
    Bufor.clear();
}

void Silnik::RayCaster(int mapa[iloscMap][WysMapy][SzerMapy]) {

    float fStartAngle = fGraczaKat - (fFOV / 2.0f);

    if (gracz::fPoziomZamknieciaDrzwi > 0 && gracz::DrzwiOtworz) {
        gracz::fPoziomZamknieciaDrzwi -= 0.011;
    }


    for (int i = 0; i < iloscPromieni; i++) {
        TabDrzwi[i] = false;
        TabScianaPozioma[i] = false;
        TabSufit[i] = 0.0;
        TabPodloga[i] = 0.0;
        TabDystans[i] = 0.0;

    }

    for (int i = 0; i < iloscPromieni; i++) {
        float fKatPromienia = fStartAngle + ((float)i / iloscPromieni) * fFOV;

        bool bHitWall = false;
        bool bHitDoor = false;
        float fOdlegOdSciany = 0.0f;

        float fOkoX = sinf(fKatPromienia);//kierunek x promeina
        float fOkoY = cosf(fKatPromienia); //kierunke y proemina

        while (!bHitWall && !bHitDoor && fOdlegOdSciany < 16.0f) {//petla dochdzaca do sciany
            fOdlegOdSciany += 0.002f;
            float fXuderzenia = (fOkoX * fOdlegOdSciany + fGraczX);
            float fYuderzenia = (fOkoY * fOdlegOdSciany + fGraczY);

            if (fabsf(fXuderzenia - roundf(fXuderzenia)) > fabsf(fYuderzenia - roundf(fYuderzenia))) {//sprwadzamy ktora wsprozedna jest blizej liczby calkowitej
                TabScianaPozioma[i] = true;
            }
            else {
                TabScianaPozioma[i] = false;
            }


            int TestX = (int)fXuderzenia;  //generalna pozycja uderzniea na mapie
            int TestY = (int)fYuderzenia;

            float fLokalneX = fXuderzenia - (float)(int)fXuderzenia; //pzoycja uderznia w bloku
            float fLokalneY = fYuderzenia - (float)(int)fYuderzenia;

            if (TestX < 0 || TestY < 0 || TestX >= SzerMapy || TestY >= WysMapy) {
                bHitWall = true;
                fOdlegOdSciany = 16.0f;
            }
            else if (mapa[NumerMapy][TestY][TestX] == 1) {
                bHitWall = true;
                TabDrzwi[i] = false;
            }
            else if (mapa[NumerMapy][TestY][TestX] == 2) {


                bool bTrafienie = (TestX == 0 && fLokalneX < 0.5f && fLokalneY < gracz::fPoziomZamknieciaDrzwi) ||       // najepirw decyzja ktora to sciana i w zalwensoci od sciany konkretna wsporzedna musi spelnaic konekrty warunek zeby bylo wglebienie w drzwiach
                    (TestX == WysMapy - 1 && fLokalneX > 0.5f && fLokalneY < gracz::fPoziomZamknieciaDrzwi) ||
                    (TestY == 0 && fLokalneY < 0.5f && fLokalneX < gracz::fPoziomZamknieciaDrzwi) ||
                    (TestY == SzerMapy - 1 && fLokalneY > 0.5f && fLokalneX < gracz::fPoziomZamknieciaDrzwi);

                if (bTrafienie) {
                    bHitDoor = true;
                    TabDrzwi[i] = true;
                }
            }//else if dla 2
        }//petla while
        float fPrawdziwaOdl = fOdlegOdSciany * cosf(fKatPromienia - fGraczaKat);//tybie oko

        float nSufit = (float)(wysokEkranu / 2.0) - (wysokEkranu / fPrawdziwaOdl);
        float nPodloga = wysokEkranu - nSufit;

        TabSufit[i] = nSufit;
        TabPodloga[i] = nPodloga;
        TabDystans[i] = fPrawdziwaOdl;


    }


    for (int i = 0; i < iloscPromieni - 1; i++) {
        if (TabScianaPozioma[i - 1] == false && TabScianaPozioma[i + 1] == false) TabScianaPozioma[i] = false;
        if (TabScianaPozioma[i - 1] == true && TabScianaPozioma[i + 1] == true) TabScianaPozioma[i] = true;

    }


}

void Silnik::PrzejsciaPrzezPokoje(int mapa[iloscMap][WysMapy][SzerMapy]) {

    if (gracz::fPoziomZamknieciaDrzwi < 0) {
        for (int i = 0; i < WysMapy; i++) {
            for (int j = 0; j < SzerMapy; j++) {
                if (mapa[NumerMapy][i][j] == 2) {
                    mapa[NumerMapy][i][j] = 3;
                }

            } // j
        }// i
    }//if < 0

    if (mapa[NumerMapy][(int)fGraczY][(int)fGraczX] == 3) {
        gracz::fPoziomZamknieciaDrzwi = 1.0;
        gracz::DrzwiOtworz = false;
        NumerMapy++;
        fGraczX = TabelaPozycjiNowegoPokoju[NumerMapy].x; //pozycje na przenosznie sie do pokoju dalej
        fGraczY = TabelaPozycjiNowegoPokoju[NumerMapy].y;
        InicjujZombie(NumerMapy);

    }
    else if (mapa[NumerMapy][(int)fGraczY][(int)fGraczX] == 4) {
        gracz::fPoziomZamknieciaDrzwi = 1.0;
        gracz::DrzwiOtworz = false;
        NumerMapy--;
        fGraczX = TabelaPozycjiPowrotu[NumerMapy].x; // pozycje powrotu
        fGraczY = TabelaPozycjiPowrotu[NumerMapy].y;
        InicjujZombie(NumerMapy);

    }
    //std::cout << NumerMapy;
}
