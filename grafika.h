#ifndef GRAFIKA_H_INCLUDED
#define GRAFIKA_H_INCLUDED


class grafika {
std::string poprzedniaBufor;
public:
   // grafika();
    void BuforMapa();
    void wypiszBufor();
    float mapuj(float x, float in_min, float in_max, float out_min, float out_max);
};



#endif // GRAFIKA_H_INCLUDED
