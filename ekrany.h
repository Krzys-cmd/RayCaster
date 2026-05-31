#ifndef ekrany_H
#define ekrany_H

class StartScreen {
public:
    // 0 podœwietla START, 1 podœwietla EXIT
    void render(int selectedOption);
};

class DeathScreen {
public:
    void render(int selectedOption, int lives);
};

class YouWinScreen {
public:
    void render(int selectedOption);
};


#endif 