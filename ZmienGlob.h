#ifndef ZMIENGLOB_H_INCLUDED
#define ZMIENGLOB_H_INCLUDED

#include <string>
#include <vector>
#include "zombie.h"

inline const int SzerMapy = 16;
inline const int WysMapy = 16;
inline const int iloscMap = 3;
inline int NumerMapy = 0;
inline int AkutalnyProgresMapy = 0;


inline float HpGracz = 100.0f;
inline float ammo = 8.0f;
inline float pts = 0.0f;

inline float fGraczX = 8.5f; //pozycja x gracza
inline float fGraczY = 1.5f; //pzoycja y gracza
inline float fGraczaKat = 2 * 3.14159f; //kat patrzenia gracza
inline float fFOV = 3.14159f / 3.0f; //pole widzenia gracza

inline float PI = 3.14159f;

inline const int szerEkranu = 150;
inline const int wysokEkranu = 40;
inline const int iloscPromieni = szerEkranu;
inline const int WirtualnaWysokscEkranu = wysokEkranu * 2;

inline float TabSufit[iloscPromieni];
inline float TabPodloga[iloscPromieni];
inline float TabDystans[iloscPromieni];
inline bool TabScianaPozioma[iloscPromieni];
inline bool TabDrzwi[iloscPromieni];

inline bool attack = false;
inline int zycia = 3;

extern std::string Bufor;
extern std::vector<ZombieStruk> listaZombie;
extern std::string napisInfo;

inline int napisInfoKlatki = 0;
inline bool klatka = 0;
#endif // ZMIENGLOB_H_INCLUDED
