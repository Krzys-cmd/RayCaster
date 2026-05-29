#ifndef FUN_H_INCLUDED
#define FUN_H_INCLUDED

#include "ZmienGlob.h"





class Silnik {
public:
    void RayCaster(int mapa[iloscMap][WysMapy][SzerMapy]);

    void PrzejsciaPrzezPokoje(int mapa[iloscMap][WysMapy][SzerMapy]);
};

class gracz {
public:
    inline static bool DrzwiOtworz = false;
    inline static float fPoziomZamknieciaDrzwi = 1.0;

    void sterowanieGracza();

    void akcjeGracza();

};


#endif
