# Párhuzamos Algoritmusok
Neptunkód: IGRYHL
Név: Somody Máté

Féléves feladat leírása

Három eltérő módszerrel közelítem meg a prímszámkeresés/prímszámvizsgálat problémáját. A program a növekvő intervallumokban ellenőrzi az összes számot, hogy prím-e vagy sem. A célom a programmal bemutatni a párhuzamosítás hatékonyságát és előnyeit.

1, Készítek egy szekvenciális kódot (primszam_seq.c), mely nem használ párhuzamosított megoldásokat, illetve az algoritmusa is a legegyszerűbb, (általában) elsőnek megismert/megtanított opció. Ezen program bool primszam_e(int num) függvénye fog felelni a prímszám ellenőrzésért, és mindig a paraméterként kapott szám feléig ellenőrzi (2-től indulva), hogy létezik-e osztója. Ennek az algoritmusnak a számítási ideje lineáris arányban áll a talált prímszámok számával, tehát elég látványosan nő kellően nagy számosságnál iterációról iterációra.

2, A második megoldás egy posix szálakat megvalósító, párhuzamosított program (primszam_posix.c). Ez a program 2 dologban különbözik az elsőtől, annak érdekében, hogy kevesebb legyen a számítási idő:
- nem a felezős algoritmust tartalmazza a bool primszam_e(int num) függvény, hanem az alábbit:
ha a szám 2 vagy 3, akkor visszatér igazzal, ha a szám kisebbegyenlő mint egy vagy osztható kettővel vagy osztható hárommal, akkor hamissal tér vissza, ha eddig nem tért vissza a függvény, akkor for ciklusban i = 5-től indulva, iterációnként 6-ot léptetve megnézi, hogy a szám osztható-e i-vel vagy i+2-vel, ha igen, visszatér hamis értékkel, ha nincs visszatérés akkor a ciklus addig tart amíg az i kisebbegyenlő, mint a szám négyzetgyöke.
Ha még mindig nem volt visszatérése a függvénynek, akkor itt tér vissza igaz értékkel.
- a program 2,3,4 és 10 szálon ellenőrzi 0-tól az alábbi számokig (tehát újrakezdve, ezzel mérési intervallumokat létrehozva) az összes értéket:
10000, 50000, 100000, 200000, 350000, 1000000, 4000000, 10000000, 20000000.

3, A harmadik megoldás (primszam_omp.c) OpenMP API-t használ. Logikailag nem különbözik a 2. megoldástól, csak értelemszerűen a kód rendszerezése és a szintaktikája a posix köré van szervezve.
