# Párhuzamos Algoritmusok
Neptunkód: IGRYHL
Név: Somody Máté

Féléves feladat leírása

A prímszámkeresés/prímszámvizsgálat problémát közelítem meg három különböző tanult módszerrel. A program egyre növekvő méretű intervallumokban az összes számról eldönteni, hogy prím-e vagy sem. A program célja, hogy bemutassa a párhuzamosítás erejét és hasznosságát.
1) Készítettem két szekvenciális kódot (primszam_seq.c illetve primszam_csharp.cs), melyek nem használ párhuzamosított megoldásokat, illetve az algoritmusa is a legegyszerűbb, (általában) elsőnek megismert/megtanított opció. Ezen C program bool primszam_e(int num) függvénye felel a prímszám ellenőrzésért, a cshapr-ban pedig a static bool IsPrime(int num) függvény, és mindig a paraméterként kapott szám feléig ellenőrzi (2-től indulva), hogy létezik-e osztója. Ennek az algoritmusnak a számítási ideje lineáris arányban áll a talált prímszámok számával, tehát elég látványosan nő kellően nagy számosságnál iterációról iterációra. 

2) A második megoldás egy posix szálakat megvalósító, párhuzamosított program (primszam_posix.c). Ez a program 2 dologban különbözik az elsőtől, annak érdekében, hogy kevesebb legyen a számítási idő:
- nem a felezős algoritmust tartalmazza a bool primszam_e(int num) függvény, hanem az alábbit:
ha a szám 2 vagy 3, akkor visszatér igazzal, ha a szám kisebbegyenlő mint egy vagy osztható kettővel vagy osztható hárommal, akkor hamissal tér vissza, ha eddig nem tért vissza a függvény, akkor for ciklusban i = 5-től indulva, iterációnként 6-ot léptetve megnézi, hogy a szám osztható-e i-vel vagy i+2-vel, ha igen, visszatér hamis értékkel, ha nincs visszatérés akkor a ciklus addig tart amíg az i kisebbegyenlő, mint a szám négyzetgyöke. 
Ha még mindig nem volt visszatérése a függvénynek, akkor itt tér vissza igaz értékkel.
- a program 2,3,4 és 10 szálon ellenőrzi 0-tól az alábbi számokig (tehát újrakezdve, ezzel mérési intervallumokat létrehozva) az összes értéket: 
10000, 50000, 100000, 200000, 350000, 1000000, 4000000, 10000000, 20000000. 

3) A harmadik megoldás (primszam_omp.c) OpenMP API-t használ. Logikailag nem különbözik a 2. megoldástól, csak értelemszerűen a kód rendszerezése és a szintaktikája a posix köré van szervezve.

A mérési adatok könnyű rögzítése érdeképen csv fájlokba mentik a programok az eredményeket, amit könnyű felhasználni utána például táblázatkészítéshez.
A futási időben semmilyen felhasználói interakcióra nincs szükség, a program elvégzi az összes intervallumon a számításokat az első szál mennyiségen, majd ezt megismétli a többi számosságú szál esetén is.

# Mérések/Tapasztalatok
A méréseket az alábbi specifikáción végeztem:
- Processzor:	Intel(R) Core(TM) i5-1038NG7 2.00GHz
- Memória:	16.0 GB, DDR4, 3733MHz
- OS: Windows 10 Professional
- Rendszer típusa:	64 bites operációs rendszer, x64-alapú processzor

A mérések során táblázatba rögzítettem az összes adatot, majd ábrázoltam grafikonon azokat. A repository feladat mappájában található xlsx dokumentum tartalmazza a:
- mért adatokat
- az egyes megoldások elkülönített grafikonját
- minden megoldás összes mért adatát egy közös grafikonon ábrázolva.

A grafikonokról leolvasva, teljesen egyértelmű, hogy a szekvenciális módszer a leglassabb, ráadásul nem is lineárisan nő a számítási ideje, hiszen a húszezredik prímszám megtalálásához nem pontosan kétszer annyi számot kell ellenőrizni, amennyit a tízezredik megtalálásához. 
Az összesített ábráról könnyen leolvashatjuk, hogy nagyjából 1.000.000 és 4.000.000 között kezd kijönni a teljesítménybeli különbség.
Megállapíthatjuk, hogy (legalábbis az én számítógépemen) az open mp általánosságban gyorsabb, mint a posix, és optimális szál szám a 10.