

<h3 align="center">Terminal Raycaster 3D FPS</h3>

<p align="center">
  Lekki, retro silnik FPS 3D działający w oparciu o technikę Raycastingu, stworzony od zera w <b>C++17</b>. Renderuje grafikę pseudo 3D bezpośrednio w konsoli Windows wykorzystując znaki ASCII/ANSI i bloki Unicode.
</p>

##  Główne funkcje

| Funkcja | Opis |
|---|---|
| **Silnik Raycasting 3D** | Renderowanie perspektywy 3D, wykrywanie ścian, korekcja efektu "rybiego oka" i cieniowanie w terminalu. |
| **Progresja map** | Obsługa wielu poziomów z różnymi układami pomieszczeń, interaktywnymi drzwiami i punktami odrodzenia. |
| **Sztuczna Inteligencja (Zombie)** | Przeciwnicy ze śledzeniem gracza (Line-of-Sight), dynamicznym pozycjonowaniem (`PozycjeZombie.h`) i animacjami. |
| **System Walki** | Strzelanie w czasie rzeczywistym, detekcja trafień, zarządzanie amunicją i animacje broni. |
| **Własny Interfejs (UI)** | Interaktywne ekrany Start/Śmierć/Wygrana oraz HUD w czasie rzeczywistym wyświetlający zdrowie, amunicję i punkty. |


##  Sterowanie

| Klawisz | Akcja |
| :---: | :--- |
| **W / S** | Ruch do przodu / do tyłu |
| **A / D** | Obrót w lewo / w prawo |
| **Spacja** | Strzał |
| **E** | Otwieranie drzwi (koszt: 50 punktów) |
| **Enter** | Wybór opcji w menu |

##  Architektura i Matematyka Silnika

Silnik generuje w pełni trójwymiarowe środowisko na podstawie dwuwymiarowej siatki mapy.

### Logika Raycastera
Dla każdej kolumny pikseli na ekranie rzucany jest promień. Silnik wykorzystuje zoptymalizowany algorytm **DDA (Digital Differential Analyzer)** do szybkiego przeskakiwania między komórkami siatki mapy i wykrywania kolizji ze ścianami.
* **Wektor promienia:** Obliczany jako suma wektora kierunku gracza i płaszczyzny kamery: `rayDir = dir + plane * cameraX`.
* **Korekcja "Fisheye":** Aby uniknąć sferycznego zniekształcenia obrazu (efekt rybiego oka), silnik nie używa prostej odległości euklidesowej. Zamiast tego oblicza **odległość prostopadłą** do płaszczyzny kamery:
  `perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX`
* **Cieniowanie:** Wysokość ściany rysowanej na ekranie jest odwrotnie proporcjonalna do odległości (`lineHeight = screenHeight / perpWallDist`). Im większa odległość, tym ciemniejszy odcień ANSI jest przypisywany znakom 

### Skalowanie i renderowanie Sprite'ów (Zombies)
Pozycje przeciwników (definiowane w `PozycjeZombie.h`) są renderowane z użyciem algebry wektorowej.
1. **Transformacja macierzowa:** Pozycja sprite'a jest obliczana względem gracza, a następnie mnożona przez macierz odwrotną płaszczyzny kamery, aby uzyskać głębię (`transformY`).
2. **Skalowanie perspektywiczne:** Wysokość i szerokość sprite'a (pixel artu z bloków znaków) są skalowane proporcjonalnie do rozdzielczości konsoli i odwrotnie proporcjonalnie do odległości: `spriteHeight = abs(screenHeight / transformY)`.
3. **1D Z-Buffer:** Aby poprawnie rysować zombie wychodzące zza ścian, silnik zapisuje odległość ścian do jednowymiarowego Z-Bufora (`ZBuffer[x]`). Sprite jest rysowany w danej kolumnie tylko wtedy, gdy jego głębia (`transformY`) jest mniejsza niż głębia ściany w tym samym punkcie.

