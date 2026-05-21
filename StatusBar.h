#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <string>

class StatusBar {
private:
    std::string name;
    float currentValue;
    float maxValue;

public:
    StatusBar(std::string name, float maxVal);

    void setValue(float newValue);
    float getValue() const;
    void stats() const;
    void draw() const;
};

#endif 