#include "HUD.h"
#include "ZmienGlob.h"

#include <iostream>
#include <string>

HUD::HUD() : health("HP  ", 100.0f), ammo("AMMO", 30.0f), points("POINTS", 50.0f), width(19) {}

void HUD::drawGradientLine(bool top) {
    for (int i = 0; i < width; i++) {
        int r = top ? (80 + (i * 175 / (width - 1))) : (255 - (i * 175 / (width - 1)));
        int b = top ? (30 - (i * 30 / (width - 1))) : (0 + (i * 30 / (width - 1)));
        Bufor += ("\x1b[48;2;" + std::to_string(r) + ";0;" + std::to_string(b) + "m");
        if (i == 0) Bufor += (top ? "\xE2\x95\x94" : "\xE2\x95\x9A");
        else if (i == width - 1) Bufor += (top ? "\xE2\x95\x97" : "\xE2\x95\x9D");
        else Bufor += "\xE2\x95\x90";
        Bufor += "\x1b[0m";
    }
    Bufor += "\x1b[0m\n";
}

void HUD::update(float hp, float am, float pts) {
    health.setValue(hp);
    ammo.setValue(am);
    points.setValue(pts);
}

bool HUD::isAlive() const {
    return health.getValue() > 0;
}

void HUD::render() {
    Bufor += "\x1b[H";
    Bufor += "\x1b[" + std::to_string(wysokEkranu - 5) + "H";

    drawGradientLine(true);

    Bufor += "\x1b[48;2;115;0;24m\xE2\x95\x91\x1b[0m";

    float currentHP = health.getValue();

    if (currentHP > 50.0f) Bufor += "\x1b[38;2;0;255;0m";
    else if (currentHP < 25.0f) Bufor += "\x1b[38;2;255;0;0m";
    else Bufor += "\x1b[38;2;255;170;0m";

    health.draw();
    Bufor += "\x1b[0m";

    Bufor += "\x1b[48;2;220;0;6m\xE2\x95\x91\x1b[0m\n";

    // HP
    Bufor += "\x1b[48;2;150;0;18m\xE2\x95\x91\x1b[0m";
    health.stats();
    Bufor += "\x1b[48;2;38;7;11m  \x1b[48;2;185;0;12m\xE2\x95\x91\x1b[0m\n";

    // AMMO
    Bufor += "\x1b[48;2;185;0;12m\xE2\x95\x91\x1b[0m";
    ammo.stats();
    Bufor += "\x1b[48;2;38;7;11m  \x1b[48;2;150;0;18m\xE2\x95\x91\x1b[0m\n";

    // POINTS
    Bufor += "\x1b[48;2;220;0;6m\xE2\x95\x91\x1b[0m";
    points.stats();
    Bufor += "\x1b[48;2;38;7;11m  \x1b[48;2;115;0;24m\xE2\x95\x91\x1b[0m\n";

    drawGradientLine(false);
}