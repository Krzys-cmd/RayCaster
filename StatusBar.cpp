#include "StatusBar.h"
#include "ZmienGlob.h"
#include <string>
#include <iostream>
#include <sstream>
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
    std::ostringstream oss;

    oss << "\x1b[48;2;38;7;11m" << std::left << std::setw(6) << name << ": "
        << std::right << std::setw(3) << (int)currentValue << "/"
        << std::left << std::setw(3) << (int)maxValue << "\x1b[0m";
    Bufor += oss.str();
}

void StatusBar::draw() const {
    Bufor += "\x1b[48;2;38;7;11m\xE2\x99\xA5  [";

    int maxBlocks = 12;

    if (maxValue <= 0) return;

    float ratio = currentValue / maxValue;
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    float scaledValue = ratio * maxBlocks;
    int full = (int)scaledValue;

    for (int i = 0; i < full; i++) {
        Bufor += "\xE2\x96\x93";
    }

    int shadows = 0;
    if (full > 0 && full < maxBlocks) {
        float reszta = scaledValue - full;
        if (reszta > 0.5f) {
            shadows = 1;
            Bufor += "\xE2\x96\x92";
        }
    }

    int empty = maxBlocks - full - shadows;
    for (int i = 0; i < empty; i++) {
        Bufor += "\xE2\x96\x91";
    }

    Bufor += "]\x1b[0m";
}
