#ifndef DATA_H
#define DATA_H

// Jedna tabulka
typedef struct tTable
{
    int rowsCnt;			// pocet radku
    double pravPristupu; 	// pravdepodobnost pristupu do tab
    double dobaPristupu[4];	// doba jak dlouho trva pristupy pro jednotlive
} tTable;

// Defunice databaze
typedef struct tExperimentData
{
    int ram;
    struct tTable tables [2];
} tExperimentData;

typedef struct tData
{
	struct tExperimentData db;
	struct tExperimentData java;
} tData;


struct tData dataDbJava;


#endif //DATA_H