#include "ekrany.h"
#include "ZmienGlob.h"
#include <string>
#include <vector>

void StartScreen::render(int selectedOption) {
    Bufor += "\x1b[48;2;0;0;0m\x1b[H";
    for (int y = 0; y < wysokEkranu; y++) {
        for (int x = 0; x < szerEkranu; x++) {
            Bufor += " ";
        }
        if (y < wysokEkranu - 1) Bufor += "\n";
    }

    // kody kolorow
    const char* T = "\x1b[0m  ";               
    const char* Z = "\x1b[48;2;50;205;50m  ";   
    const char* K = "\x1b[48;2;220;0;0m  "; 
    const char* B = "\x1b[48;2;80;0;0m  ";

    // tytul gry
    const char* titleArt[8][37] = {
        { Z,Z,Z,Z, T, Z,Z,Z,Z, T, Z,T,T,T,Z, T, Z,Z,Z,T, T, Z,T,T,T,Z, T, Z,Z,Z,T, T, Z,T,T,T,Z },
        { T,T,T,Z, T, Z,T,T,Z, T, Z,Z,T,Z,Z, T, Z,T,T,Z, T, Z,T,T,T,Z, T, Z,T,T,Z, T, Z,Z,T,T,Z },
        { T,T,Z,T, T, Z,T,T,Z, T, Z,K,Z,T,Z, T, Z,Z,Z,T, T, Z,T,T,T,Z, T, Z,Z,Z,T, T, Z,K,Z,T,Z },
        { T,Z,T,T, T, Z,T,T,Z, T, Z,K,T,T,Z, T, Z,T,T,Z, T, Z,T,T,T,Z, T, Z,K,T,Z, T, Z,K,K,Z,Z },
        { Z,Z,Z,Z, T, Z,Z,Z,Z, T, Z,K,T,T,Z, T, Z,Z,Z,K, T, Z,Z,Z,Z,K, T, Z,K,T,Z, T, Z,K,T,T,Z },
        { T,K,K,T, T, T,T,K,K, T, T,T,T,T,T, T, T,K,T,K, T, T,T,K,K,T, T, K,T,T,T, T, T,K,T,T,T },
        { T,K,T,T, T, T,T,K,T, T, T,T,K,T,T, T, T,K,T,T, T, T,T,T,K,T, T, K,T,T,T, T, T,T,T,T,K },
        { T,T,T,T, T, T,T,T,T, T, T,T,K,T,T, T, T,T,T,T, T, T,T,T,K,T, T, T,T,T,T, T, T,T,T,T,T }
    };

    int artW = 74;
    int artH = 8;
    int startX = (szerEkranu / 2) - (artW / 2);
    int startY = (wysokEkranu / 2) - 10;

 //rysowanie napisu + obwodka
    for (int y = -1; y <= artH; y++) {
        for (int x = -1; x <= 37; x++) {

            const char* rysowanyKolor = T; 

            if (y >= 0 && y < artH && x >= 0 && x < 37 && titleArt[y][x] != T) {
                rysowanyKolor = titleArt[y][x]; // Rysowanie litery/krwi
            }
            // gdy puste pole, sprawdzamy czy obok jest znak
            else {
                bool dotykaZnaku = false;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int sprawdzY = y + dy;
                        int sprawdzX = x + dx;

                        // sprawdzenie czy nie wychodzimy poza tablice
                        if (sprawdzY >= 0 && sprawdzY < artH && sprawdzX >= 0 && sprawdzX < 37) {
                            if (titleArt[sprawdzY][sprawdzX] != T) {
                                dotykaZnaku = true;
                            }
                        }
                    }
                }
                if (dotykaZnaku) {
                    //obwodka
                    rysowanyKolor = B;
                }
            }

            if (rysowanyKolor != T) {
                Bufor += "\x1b[" + std::to_string(startY + y + 1) + ";" + std::to_string(startX + (x * 2) + 1) + "H";
                Bufor += rysowanyKolor;
            }
        }
    }

    int menuY = startY + artH + 6;
    Bufor += "\x1b[0m"; 

    //START
    std::string startText = "S T A R T";
    int startMenuX = (szerEkranu / 2) - (startText.length() / 2);
    Bufor += "\x1b[" + std::to_string(menuY) + ";" + std::to_string(startMenuX + 1) + "H";

    if (selectedOption == 0) {
        Bufor += "\x1b[48;2;180;0;0m\x1b[38;2;255;255;255m";
        Bufor += "> " + startText + " <";
    }
    else {
        Bufor += "\x1b[48;2;0;0;0m\x1b[38;2;120;120;120m";
        Bufor += "  " + startText + "  ";
    }

    //EXIT
    std::string exitText = "E X I T";
    int exitMenuX = (szerEkranu / 2) - (exitText.length() / 2);
    Bufor += "\x1b[" + std::to_string(menuY + 3) + ";" + std::to_string(exitMenuX + 1) + "H";

    if (selectedOption == 1) {
        Bufor += "\x1b[48;2;180;0;0m\x1b[38;2;255;255;255m";
        Bufor += "> " + exitText + " <";
    }
    else {
        Bufor += "\x1b[48;2;0;0;0m\x1b[38;2;120;120;120m";
        Bufor += "  " + exitText + "  ";
    }

    Bufor += "\x1b[0m";
}

void DeathScreen::render(int selectedOption, int lives) {
    Bufor += "\x1b[48;2;0;0;0m\x1b[H";
    for (int y = 0; y < wysokEkranu; y++) {
        for (int x = 0; x < szerEkranu; x++) {
            Bufor += " ";
        }
        if (y < wysokEkranu - 1) Bufor += "\n";
    }

    const char* T = "\x1b[0m  ";                
    const char* R = "\x1b[48;2;220;0;0m  ";     
    const char* G = "\x1b[48;2;50;205;50m  ";    
    const char* B = "\x1b[48;2;80;0;0m  ";     

    if (lives > 0) {
       
       //serce
        int heart[7][7] = {
            {0, 2, 2, 0, 2, 2, 0},
            {2, 1, 1, 2, 1, 1, 2},
            {2, 1, 1, 1, 1, 1, 2},
            {2, 1, 1, 1, 1, 1, 2},
            {0, 2, 1, 1, 1, 2, 0},
            {0, 0, 2, 1, 2, 0, 0},
            {0, 0, 0, 2, 0, 0, 0}
        };

        int hW = 7 * 2; // Szerokość serca w konsoli
        int odst = 6;   // Odstęp między sercami
        int startX = (szerEkranu / 2) - ((3 * hW + 2 * odst) / 2);
        int startY = (wysokEkranu / 2) - 8;

        // Rysowanie serc
        for (int h = 0; h < 3; h++) {
            // Jeśli h jest mniejsze od liczby żyć, środek jest czerwony, inaczej zielony
            const char* kolorSrodka = (h < lives) ? R : G;

            for (int y = 0; y < 7; y++) {
                for (int x = 0; x < 7; x++) {
                    if (heart[y][x] != 0) { 
                        int rX = startX + (h * (hW + odst)) + (x * 2);
                        Bufor += "\x1b[" + std::to_string(startY + y) + ";" + std::to_string(rX) + "H";

                        if (heart[y][x] == 1) {
                            Bufor += kolorSrodka; // Wypełnienie
                        }
                        else if (heart[y][x] == 2) {
                            Bufor += B;           // Obwodka
                        }
                    }
                }
            }
        }

        Bufor += "\x1b[0m"; 
        std::string info = "S T R A C I L E S  J E D N O  Z Y C I E";
        Bufor += "\x1b[" + std::to_string(startY + 9) + ";" + std::to_string((szerEkranu / 2) - (info.length() / 2)) + "H";
        Bufor += "\x1b[38;2;255;50;50m" + info; 

        std::string btn = "P O W R O T  D O  G R Y";
        Bufor += "\x1b[" + std::to_string(startY + 14) + ";" + std::to_string((szerEkranu / 2) - (btn.length() / 2) - 2) + "H";
        Bufor += "\x1b[48;2;180;0;0m\x1b[38;2;255;255;255m> " + btn + " <\x1b[0m";

    }
    else {
       //GAME OVER
        const char* gameOverArt[7][43] = {
    { T,G,G,G, T, T,G,G,T, T, G,T,T,T,G, T, G,G,G,G, T,T,T, T,G,G,T, T, G,T,T,T,G, T, G,G,G,G, T, G,G,G,T },
    { G,T,T,T, T, G,T,T,G, T, G,G,T,G,G, T, G,T,T,T, T,T,T, G,T,T,G, T, G,T,T,T,G, T, G,T,T,T, T, G,T,T,G },
    { G,T,T,T, T, G,T,T,G, T, G,T,G,T,G, T, G,G,G,T, T,T,T, G,T,T,G, T, G,T,T,T,G, T, G,G,G,T, T, G,T,T,G },
    { G,T,G,G, T, G,G,G,G, T, G,T,T,T,G, T, G,T,T,T, T,T,T, G,T,T,G, T, T,G,T,G,T, T, G,T,T,T, T, G,G,G,T },
    { G,T,T,G, T, G,T,T,G, T, G,T,T,T,G, T, G,T,T,T, T,T,T, G,T,T,G, T, T,G,T,G,T, T, G,T,T,T, T, G,T,G,T },
    { G,T,T,G, T, G,T,T,G, T, G,T,T,T,G, T, G,T,T,T, T,T,T, G,T,T,G, T, T,T,G,T,T, T, G,T,T,T, T, G,T,T,G },
    { T,G,G,T, T, G,T,T,G, T, G,T,T,T,G, T, G,G,G,G, T,T,T, T,G,G,T, T, T,T,G,T,T, T, G,G,G,G, T, G,T,T,G }
        };

        int artW = 43 * 2; 
        int artH = 7;
        int startX = (szerEkranu / 2) - (artW / 2);
        int startY = (wysokEkranu / 2) - 10;

        // Rysowanie napisu z obwódką
        for (int y = -1; y <= artH; y++) {
            for (int x = -1; x <= 43; x++) {
                const char* rysowanyKolor = T;

                if (y >= 0 && y < artH && x >= 0 && x < 43 && gameOverArt[y][x] != T) {
                    rysowanyKolor = gameOverArt[y][x];
                }
                else {
                    bool dotyka = false;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            int sy = y + dy;
                            int sx = x + dx;
                            if (sy >= 0 && sy < artH && sx >= 0 && sx < 43) {
                                if (gameOverArt[sy][sx] != T) dotyka = true;
                            }
                        }
                    }
                    if (dotyka) rysowanyKolor = B;
                }

                if (rysowanyKolor != T) {
                    Bufor += "\x1b[" + std::to_string(startY + y + 1) + ";" + std::to_string(startX + (x * 2) + 1) + "H";
                    Bufor += rysowanyKolor;
                }
            }
        }

        // Przyciski Menu
        Bufor += "\x1b[0m"; 
        int menuY = startY + artH + 6;

        std::string btn1 = "Z A G R A J  P O N O W N I E";
        int btn1X = (szerEkranu / 2) - (btn1.length() / 2);
        Bufor += "\x1b[" + std::to_string(menuY) + ";" + std::to_string(btn1X + 1) + "H";
        if (selectedOption == 0) Bufor += "\x1b[48;2;180;0;0m\x1b[38;2;255;255;255m> " + btn1 + " <\x1b[0m";
        else Bufor += "\x1b[48;2;0;0;0m\x1b[38;2;120;120;120m  " + btn1 + "  \x1b[0m";

        std::string btn2 = "E X I T";
        int btn2X = (szerEkranu / 2) - (btn2.length() / 2);
        Bufor += "\x1b[" + std::to_string(menuY + 3) + ";" + std::to_string(btn2X + 1) + "H";
        if (selectedOption == 1) Bufor += "\x1b[48;2;180;0;0m\x1b[38;2;255;255;255m> " + btn2 + " <\x1b[0m";
        else Bufor += "\x1b[48;2;0;0;0m\x1b[38;2;120;120;120m  " + btn2 + "  \x1b[0m";
    }
}

void YouWinScreen::render(int selectedOption) {
    // Czyszczenie ekranu (tak jak w StartScreen)
    Bufor += "\x1b[48;2;0;0;0m\x1b[H";
    for (int y = 0; y < wysokEkranu; y++) {
        for (int x = 0; x < szerEkranu; x++) {
            Bufor += " ";
        }
        if (y < wysokEkranu - 1) Bufor += "\n";
    }

    // Kody kolorów
    const char* T = "\x1b[0m  ";              // Przezroczysty / Tło
    const char* Z = "\x1b[48;2;255;220;0m  "; // Żółty (Wypełnienie)
    const char* B = "\x1b[48;2;80;0;0m  ";   // Bordowy (Obwódka i Podświetlenie)

    // Tytuł YOU WIN! (29 kolumn z wykrzyknikiem)
    const char* winGrid[5][29] = {
        { Z,T,Z, T, Z,Z,Z, T, Z,T,Z, T,T, Z,T,T,T,Z, T, Z,Z,Z, T, Z,T,T,Z, T, Z },
        { T,Z,T, T, Z,T,Z, T, Z,T,Z, T,T, Z,T,T,T,Z, T, T,Z,T, T, Z,Z,T,Z, T, Z },
        { T,Z,T, T, Z,T,Z, T, Z,T,Z, T,T, Z,T,Z,T,Z, T, T,Z,T, T, Z,T,Z,Z, T, Z },
        { T,Z,T, T, Z,T,Z, T, Z,T,Z, T,T, Z,Z,T,Z,Z, T, T,Z,T, T, Z,T,T,Z, T, T },
        { T,Z,T, T, Z,Z,Z, T, Z,Z,Z, T,T, Z,T,T,T,Z, T, Z,Z,Z, T, Z,T,T,Z, T, Z }
    };

    int artW = 58; // 29 kolumn * 2 znaki szerokości
    int artH = 5;
    int startX = (szerEkranu / 2) - (artW / 2);
    int startY = (wysokEkranu / 2) - 8;

    // Rysowanie napisu + automatyczna bordowa obwódka
    for (int y = -1; y <= artH; y++) {
        for (int x = -1; x <= 29; x++) {

            const char* rysowanyKolor = T;

            if (y >= 0 && y < artH && x >= 0 && x < 29 && winGrid[y][x] != T) {
                rysowanyKolor = winGrid[y][x];
            }
            else {
                bool dotykaZnaku = false;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int sprawdzY = y + dy;
                        int sprawdzX = x + dx;

                        if (sprawdzY >= 0 && sprawdzY < artH && sprawdzX >= 0 && sprawdzX < 29) {
                            if (winGrid[sprawdzY][sprawdzX] != T) {
                                dotykaZnaku = true;
                            }
                        }
                    }
                }
                if (dotykaZnaku) {
                    rysowanyKolor = B;
                }
            }

            if (rysowanyKolor != T) {
                Bufor += "\x1b[" + std::to_string(startY + y + 1) + ";" + std::to_string(startX + (x * 2) + 1) + "H";
                Bufor += rysowanyKolor;
            }
        }
    }

    int menuY = startY + artH + 6;
    Bufor += "\x1b[0m";

    // --- PRZYCISK: ZAGRAJ PONOWNIE ---
    std::string playText = "Z A G R A J   P O N O W N I E";
    int playMenuX = (szerEkranu / 2) - (playText.length() / 2);
    Bufor += "\x1b[" + std::to_string(menuY) + ";" + std::to_string(playMenuX + 1) + "H";

    if (selectedOption == 0) {
        // TERAZ: Bordowe tło i żółte litery dla aktywnej opcji
        Bufor += "\x1b[48;2;110;0;20m\x1b[38;2;255;220;0m";
        Bufor += "> " + playText + " <";
    }
    else {
        // Nieaktywny (Czarne tło, szare litery)
        Bufor += "\x1b[48;2;0;0;0m\x1b[38;2;120;120;120m";
        Bufor += "  " + playText + "  ";
    }

    // --- PRZYCISK: EXIT ---
    std::string exitText = "E X I T";
    int exitMenuX = (szerEkranu / 2) - (exitText.length() / 2);
    Bufor += "\x1b[" + std::to_string(menuY + 3) + ";" + std::to_string(exitMenuX + 1) + "H";

    if (selectedOption == 1) {
        // TERAZ: Bordowe tło i żółte litery dla aktywnej opcji
        Bufor += "\x1b[48;2;110;0;20m\x1b[38;2;255;220;0m";
        Bufor += "> " + exitText + " <";
    }
    else {
        // Nieaktywny (Czarne tło, szare litery)
        Bufor += "\x1b[48;2;0;0;0m\x1b[38;2;120;120;120m";
        Bufor += "  " + exitText + "  ";
    }

    Bufor += "\x1b[0m";
}
