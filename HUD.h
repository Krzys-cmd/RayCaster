#ifndef HUD_H
#define HUD_H

#include "StatusBar.h"
#include <vector>
#include <string>

class HUD {
private:
    StatusBar health;
    StatusBar ammo;
    StatusBar points;
    int width;

    void drawGradientLine(bool top);

public:
    HUD();

    void update(float hp, float am, float pts);
    bool isAlive() const;
    void render();
};

#endif