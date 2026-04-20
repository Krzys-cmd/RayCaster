#include "fun.h"
#include "ZmienGlob.h"
#include "Mapa.h"

#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>
#include <windows.h>

void gracz::akcjeGracza(){
    if(_kbhit()){
      char key=_getch();

      if(key=='c'){
        system("cls");
      }

    }
}

void gracz::sterowanieGracza(){

     float fChodSzyb = 0.05f; //predksoc chodzenia
     float fObrSzyb = 0.03f; //predksoc obrotu


       if (GetAsyncKeyState('A') & 0x8000) {
            fGraczaKat -= fObrSzyb;
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            fGraczaKat += fObrSzyb;
        }

     fGraczaKat= fmodf(fGraczaKat, 2.0f * 3.14159f);
     if(fGraczaKat<0.0f) fGraczaKat += 2*PI;

        float fKierune = 0.0f;
        if (GetAsyncKeyState('W') & 0x8000) fKierune = 1.0f;  // Przód
        if (GetAsyncKeyState('S') & 0x8000) fKierune = -1.0f; // Tył

     if(fKierune!=0.0f){


        float fDeltaX = sinf(fGraczaKat)*fChodSzyb*fKierune;
        float fDeltaY = cosf(fGraczaKat)*fChodSzyb*fKierune;

        float fNoweX = fGraczX+fDeltaX;
        float fNoweY = fGraczY+fDeltaY;

       if(fNoweX >= 0 && fNoweX < SzerMapy){
            if(mapa[NumerMapy][(int)fGraczY][(int)(fGraczX+fDeltaX)]!=1){
            fGraczX+=fDeltaX;
        }
       }

        if(fNoweY >= 0 && fNoweY < WysMapy){
            if(mapa[NumerMapy][(int)(fGraczY+fDeltaY)][(int)fGraczX]!=1){
            fGraczY+=fDeltaY;
            }
        }



     }//przod tyl

}

void Silnik::RayCaster(int mapa[iloscMap][WysMapy][SzerMapy]){


    float fStartAngle=fGraczaKat-(fFOV / 2.0f);

  for(int i=0; i<iloscPromieni; i++){
    float fKatPromienia = fStartAngle+((float)i / iloscPromieni) * fFOV;

    bool bHitWall=false;
    bool bHitDoor=false;
    float fOdlegOdSciany=0.0f;

    float fOkoX=sinf(fKatPromienia);//kierunek x promeina
    float fOkoY=cosf(fKatPromienia); //kierunke y proemina

    while(!bHitWall && !bHitDoor && fOdlegOdSciany<16.0f){//petla dochdzaca do sciany
        fOdlegOdSciany+=0.002f;
        float fXuderzenia=(fOkoX*fOdlegOdSciany+fGraczX);
        float fYuderzenia=(fOkoY*fOdlegOdSciany+fGraczY);

        if(fabsf(fXuderzenia-roundf(fXuderzenia))>fabsf(fYuderzenia-roundf(fYuderzenia))){//sprwadzamy ktora wsprozedna jest blizej liczby calkowitej
            TabScianaPozioma[i]=true;
                }
        else{
            TabScianaPozioma[i]=false;
        }


        int TestX = (int)fXuderzenia;
        int TestY = (int)fYuderzenia;

        float fLokalneX = fXuderzenia - (float)(int)fXuderzenia;
        float fLokalneY = fYuderzenia - (float)(int)fYuderzenia;

       if(TestX<0 || TestY<0 || TestX>=SzerMapy || TestY>=WysMapy){
        bHitWall=true;
        fOdlegOdSciany=16.0f;
       }
       else if(mapa[NumerMapy][TestY][TestX]==1){
        bHitWall=true;
        TabDrzwi[i]=false;
       }
       else if(mapa[NumerMapy][TestY][TestX] == 2) {


        bool bTrafienie = (TestX==0 &&  fLokalneX < 0.5f) ||
                          (TestX==WysMapy-1 && fLokalneX > 0.5f)||
                          (TestY==0 && fLokalneY < 0.5f) ||
                          (TestY==SzerMapy-1 && fLokalneY > 0.5f);

            if(bTrafienie) {
                bHitDoor = true;
                TabDrzwi[i] = true;
            }
         }//else if dla 2
      }//petla while
     float fPrawdziwaOdl = fOdlegOdSciany * cosf(fKatPromienia - fGraczaKat);//tybie oko

     float nSufit = (float)(wysokEkranu / 2.0) - (wysokEkranu / fPrawdziwaOdl);
     float nPodloga = wysokEkranu - nSufit;

       TabSufit[i]=nSufit;
       TabPodloga[i]=nPodloga;
       TabDystans[i]=fPrawdziwaOdl;


  }


  for(int i=0; i<iloscPromieni-1; i++){
    if(TabScianaPozioma[i-1]==false&&TabScianaPozioma[i+1]==false) TabScianaPozioma[i]=false;
    if(TabScianaPozioma[i-1]==true&&TabScianaPozioma[i+1]==true) TabScianaPozioma[i]=true;

  }


}

void grafika::bufor(){
 std::string bufor = "\x1b[H";

    for (int i=0; i < wysokEkranu; i++) {
        for (int j = 0; j < iloscPromieni; j++) {

            if (i < (int)TabSufit[j]){//sufit

                bufor+=" ";
            }

            else if (i == (int)TabSufit[j]) { //gorne krawedz
                if(TabSufit[j]-(float)(int)(TabSufit[j])<0.5){

                float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);
                int r = (int)(255 * fCien);
                if (TabScianaPozioma[j]) r *= 0.7;

                    if(TabDrzwi[j]==1){
                      bufor += "\x1b[48;2;20;60;\x1b[38;2;20;60;0m";
                    }
                    else bufor += "\x1b[38;2;" + std::to_string(r) + ";0;0m"; // Kolor ściany (tekst)

                bufor += "\xE2\x96\x84"; // Znak ▄
                bufor += "\x1b[0m";

                }
                else bufor+=" ";

            }
            else if (i > (int)TabSufit[j] && i < (int)TabPodloga[j]) { //srodek sciany

                //int r = (int)mapuj(TabDystans[j], 0.0f, 16.0f, 255.0f, 50.0f); //mapowanie koloru

                float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);//mapowanie cienia
                int r = (int)(255 * fCien);
                if(TabScianaPozioma[j]==true)  r*=0.7;



                if(TabDrzwi[j]==1){
                  bufor += "\x1b[48;2;20;60;0m \x1b[0m";
                }
                else bufor += "\x1b[48;2;" + std::to_string(r) + ";0;0m \x1b[0m";

            }
            else if (i == (int)TabPodloga[j]) { //dolna krawedz
                if(TabPodloga[j]-(float)(int)(TabPodloga[j])<0.5){

                float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);
                int r = (int)(255 * fCien);
                if (TabScianaPozioma[j]) r *= 0.7;
                int szary = (int)mapuj(i, wysokEkranu / 2, wysokEkranu, 10.0f, 100.0f);

                    if(TabDrzwi[j]==1){
                      bufor += "\x1b[38;2;20;60;0m";
                    }
                    else{
                      bufor += "\x1b[38;2;" + std::to_string(r) + ";0;0m"; // góra (ściana)

                    }


                 bufor += "\x1b[48;2;" + std::to_string(szary) + ";" + std::to_string(szary) + ";" + std::to_string(szary) + "m"; // dół (podłoga)
                bufor += "\xE2\x96\x80"; // ▀
                bufor += "\x1b[0m";



                }
                else {
                    float fCien = mapuj(TabDystans[j], 0, 16, 1.0f, 0.2f);//mapowanie cienia
                    int r = (int)(255 * fCien);
                    if(TabScianaPozioma[j]==true)  r*=0.7;

                        if(TabDrzwi[j]==1){
                          bufor += "\x1b[48;2;20;60;0m \x1b[38;2;20;60;0m";
                        }
                        else bufor += "\x1b[48;2;" + std::to_string(r) + ";0;0m \x1b[0m";
                    };

            }
            else if(i > (int)TabPodloga[j]) {//podloga
                int szary = (int)mapuj(i, wysokEkranu / 2, wysokEkranu, 10.0f, 100.0f);
                bufor += "\x1b[48;2;" + std::to_string(szary) + ";" + std::to_string(szary) + ";" + std::to_string(szary) + "m \x1b[0m";
            }


        }
        bufor += "\n";
    }

    std::cout << bufor;
}

float grafika::mapuj(float x, float in_min, float in_max, float out_min, float out_max) {
    if (x < in_min) x = in_min;
    if (x > in_max) x = in_max;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
