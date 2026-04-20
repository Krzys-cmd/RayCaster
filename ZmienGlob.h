#ifndef ZMIENGLOB_H_INCLUDED
#define ZMIENGLOB_H_INCLUDED

inline const int SzerMapy = 16;
inline const int WysMapy = 16;
inline const int iloscMap = 1;
inline int NumerMapy = 0;

inline float fGraczX=7.0f; //pozycja x gracza
inline float fGraczY=6.0f; //pzoycja y gracza
inline float fGraczaKat = 3.14159f; //kat patrzenia gracza
inline float fFOV = 3.14159f / 3.0f; //pole widzenia gracza
inline float PI=3.14159f;

inline const int szerEkranu=150;
inline const int wysokEkranu=40;
inline const int iloscPromieni = szerEkranu;
inline const int WirtualnaWysokscEkranu = wysokEkranu*2;

inline float TabSufit[iloscPromieni];
inline float TabPodloga[iloscPromieni];
inline float TabDystans[iloscPromieni];
inline bool TabScianaPozioma[iloscPromieni];
inline bool TabDrzwi[iloscPromieni];



#endif // ZMIENGLOB_H_INCLUDED
