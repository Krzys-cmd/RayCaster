#include <windows.h>
#include <thread>
#include "HUD.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    HUD myGameHud;
    float hp = 12, ammo = 30, pts = 0;

    while (myGameHud.isAlive()) {
        myGameHud.render();

        //zmiany w hp itd...........
        hp -= 0.5f;
        ammo -= 1.0f;
        pts += 2.0f;

        myGameHud.update(hp, ammo, pts);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}