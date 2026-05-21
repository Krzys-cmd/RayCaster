#include "HUD.h"
#include <iostream>

HUD::HUD() : health("HP  ", 12), ammo("AMMO", 30), points("POINTS", 50), width(19) {}

void HUD::drawGradientLine(bool top) {
    for (int i = 0; i < width; i++) {
        int r = top ? (80 + (i * 175 / (width - 1))) : (255 - (i * 175 / (width - 1)));
        int b = top ? (30 - (i * 30 / (width - 1))) : (0 + (i * 30 / (width - 1)));

        std::cout << "\x1b[48;2;" << r << ";0;" << b << "m";
        if (i == 0) std::cout << (top ? "\xE2\x95\x94" : "\xE2\x95\x9A");
        else if (i == width - 1) std::cout << (top ? "\xE2\x95\x97" : "\xE2\x95\x9D");
        else std::cout << "\xE2\x95\x90";
        std::cout << "\x1b[0m";
    }
    std::cout << std::endl;
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
    std::cout << "\x1b[H";
    std::cout << "\x1b[" + std::to_string(wysokEkranu - 5) + "H";

    drawGradientLine(true);

    std::cout << "\x1b[48;2;115;0;24m\xE2\x95\x91\x1b[0m";

    float currentHP = health.getValue();
    if (currentHP > 8) std::cout << "\x1b[38;2;0;255;0m";
    else if (currentHP < 5) std::cout << "\x1b[38;2;255;0;0m";
    else std::cout << "\x1b[38;2;255;170;0m";

    health.draw();
    std::cout << "\x1b[0m";

    std::cout << "\x1b[48;2;220;0;6m\xE2\x95\x91\x1b[0m\n";

    // HP
    std::cout << "\x1b[48;2;150;0;18m\xE2\x95\x91\x1b[0m";
    health.stats();
    std::cout << "\x1b[48;2;38;7;11m  \x1b[48;2;185;0;12m\xE2\x95\x91\x1b[0m\n";

    // AMMO
    std::cout << "\x1b[48;2;185;0;12m\xE2\x95\x91\x1b[0m";
    ammo.stats();
    std::cout << "\x1b[48;2;38;7;11m  \x1b[48;2;150;0;18m\xE2\x95\x91\x1b[0m\n";

    // POINTS
    std::cout << "\x1b[48;2;220;0;6m\xE2\x95\x91\x1b[0m";
    points.stats();
    std::cout << "\x1b[48;2;38;7;11m  \x1b[48;2;115;0;24m\xE2\x95\x91\x1b[0m\n";

    drawGradientLine(false);
}