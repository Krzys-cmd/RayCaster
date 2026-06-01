#ifndef ekrany_H
#define ekrany_H

class StartScreen {
public:
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

int obslugaEkranuStartowego();

// Zwraca true jeœli gracz kontynuuje, false jeœli Game Over 
bool obslugaEkranuSmierci(int& lives, float& hp, float& x, float& y, int mapa);

bool obslugaEkranuWygranej();

#endif 