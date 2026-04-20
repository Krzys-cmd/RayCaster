#ifndef FUN_H_INCLUDED
#define FUN_H_INCLUDED

#include "ZmienGlob.h"








class Silnik{
public:
    void RayCaster(int mapa[iloscMap][WysMapy][SzerMapy]);
};

class gracz{
public:
    void sterowanieGracza();

    void akcjeGracza();

};


class grafika{
public:

    float mapuj(float x, float in_min, float in_max, float out_min, float out_max);

    void bufor();
};
#endif
