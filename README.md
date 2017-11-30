Test rychlosti filtrace JAVA/Postgres


Generování dat:
Je tam založení ukázkové tabulky rows100 a její naplnění.
Použití:
Parametry jdou za sebou stejně.

Najde to tabulku: rows100
filtruje podle sloupce:  "id"
operace filtrace: LIKE   (bere kdekoliv v hodnotě)  (ještě máme LIKES LIKEE EQEUALS)
Vsechny sloupce tabulky: "id, name"
Bude fltrovat pomoci: JAVA  (ještě máme DB)

Adresa serveru: 192.168.0.51
Databaze název: postgres
Uživatel: postgres
Heslo: postgres

TestApp 100 "id" LIKE 1 "id, name" JAVA 192.168.0.51 postgres postgres postgres


Výstup:
JAVA;100;id;LIKE;1;20;992142;89075

JAVA;                         Filtrovano pomoci JAVA  (ještě máme DB)
100;                           Celkový počet řádků v tabulce
id;                              Filtrovaný sloupec
LIKE;                          Operace filtrace (ještě máme LIKES LIKEE EQEUALS)
1;                               Hodnota kterou jsme hledali
20;                             Počet nalezených záznamů
992142;                     Doba první filtrace
89075                        Průměrná doba filtrace po 15 pokusech
