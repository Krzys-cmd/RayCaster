

<h3 align="center">Terminal Raycaster 3D FPS</h3>

<p align="center">
  Lekki, retro silnik FPS 3D działający w oparciu o technikę Raycastingu, stworzony od zera w <b>C++17</b>. Renderuje grafikę pseudo 3D bezpośrednio w konsoli Windows wykorzystując znaki ASCII/ANSI i bloki Unicode.
</p>

##  Główne funkcje

| Funkcja | Opis |
|---|---|
| **Silnik Raycasting** | Renderowanie perspektywy 2.5D, wykrywanie ścian, korekcja efektu "rybiego oka" i cieniowanie w terminalu. |
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

Silnik generuje dwuipółwymiarowe środowisko na podstawie dwuwymiarowej siatki mapy.

### Logika Raycastera
Dla każdej kolumny pikseli na ekranie rzucany jest promień. Silnik wykorzystuje zoptymalizowany algorytm **DDA (Digital Differential Analyzer)** do szybkiego przeskakiwania między komórkami siatki mapy i wykrywania kolizji ze ścianami.
* **Kąta promienia:** Kąt promienia jest wyznaczany na podstawie kąta patrzenia gracza, pola widzenia oraz aktualnej kolumny ekranu: `fKatPromienia = fStartAngle + ((float)i / iloscPromieni) * fFOV`.
* **Korekcja "Fisheye":** Aby uniknąć sferycznego zniekształcenia obrazu (efekt rybiego oka), silnik nie używa prostej odległości euklidesowej. Zamiast tego oblicza **odległość prostopadłą** do płaszczyzny kamery:
  `fPrawdziwaOdl = fOdlegOdSciany * cosf(fKatPromienia - fGraczaKat);`
* **Cieniowanie:** Wysokość ściany rysowanej na ekranie jest odwrotnie proporcjonalna do odległości . Im większa odległość, tym ciemniejszy odcień ANSI jest przypisywany znakom 


### Logika i Pozycjonowanie Przeciwników (Zombie)

Pozycja i renderowanie zombie na ekranie opierają się na połączeniu trygonometrii, detekcji kolizji oraz skalowania perspektywicznego:

* **Ruch i Śledzenie Gracza:** 
  Ścieżka poruszania się zombie jest wyznaczana na podstawie kąta do gracza (`fKatDoGracza` obliczonego za pomocą `std::atan2`). Jeśli zombie widzi gracza i znajduje się w zasięgu $2.0 \le \text{dystans} < 10.0$, przesuwa się w jego stronę z krokami wyliczanymi przez `sinf` oraz `cosf`.

* **Detekcja Kolizji ze Ścianami:** 
  Przed wykonaniem ruchu silnik sprawdza kolizję promienia fizycznego zombie (`promien = 0.3f`) w 4 punktach wokół przeciwnika. Zapewnia to, że zombie nie przenika przez ściany mapy podczas pościgu.

* **Projekcja na Ekran (`z.srodekX`):** 
  Pozycja pozioma sprite'a w konsoli jest ustalana poprzez obliczenie różnicy kąta patrzenia gracza i kąta do zombie (`fRoznicaKata`), a następnie przeliczenie tej wartości na konkretną kolumnę ekranu w ramach pola widzenia (`fFOV`):
 ` z.srodekX = (fRoznicaKata + fFOV / 2.0f) / fFOV * szerEkranu;`
