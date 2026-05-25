#include "StatusBar.h"
#include "ZmienGlob.h"
#include <iostream>
#include <iomanip>


StatusBar::StatusBar(std::string name, float maxVal)
    : name(name), currentValue(maxVal), maxValue(maxVal) {
}

void StatusBar::setValue(float newValue) {
    if (newValue < 0) currentValue = 0;
    else if (newValue > maxValue) currentValue = maxValue;
    else currentValue = newValue;
}

float StatusBar::getValue() const {
    return currentValue;
}

void StatusBar::stats() const {
    std::cout << "\x1b[48;2;38;7;11m" << std::left << std::setw(7) << name << ": "
        << std::right << std::setw(2) << (int)currentValue << "/"
        << std::left << std::setw(3) << (int)maxValue << "\x1b[0m";
}

void StatusBar::draw() const {
    std::cout << "\x1b[48;2;38;7;11m" << "\xE2\x99\xA5  [";
    int full = (int)currentValue;
    int max = (int)maxValue;

    for (int i = 0; i < full; i++) std::cout << "\xE2\x96\x93";

    int shadows = 0;
    if (full > 0 && full < max) {
        shadows = (full == max - 1) ? 1 : 2;
        for (int i = 0; i < shadows; i++) std::cout << "\xE2\x96\x92";
    }

    int empty = max - full - shadows;
    for (int i = 0; i < empty; i++) std::cout << "\xE2\x96\x91";

    std::cout << "]" << "\x1b[0m";
}
