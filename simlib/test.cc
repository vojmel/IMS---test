#include <stdbool.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include "simlib.h"
#include <math.h>




typedef struct tPozadavek
{
	long tableSize;		// velikost tabulky
	int  presnost;		// presnost hledani 
} tPozadavek;



// Jeden pripad
//#ifdef TEST_OBECNY
#define RAM 1024  // 2048  4048

int pocetPozadavku = 5;

tPozadavek testovaciPozadavky[] = {
	{5000, 1},		// SELECT 1 FROM 5000
	{5000, 10},		// SELECT 10 FROM 5000
	{5000, 100},	// SELECT 100 FROM 5000
	{5000, 1000},	// SELECT 1000 FROM 5000
	{10000, 10},	// SELECT 10 FROM 100000
};

//#endif



//
// Doba cekani na vybrani vsech dat z urcite tabulky 
// po restartu databaze
double Proces_select_all_for_first_time(long tableSize) {

	printf("Proces_select_all_for_first_time\n");

	double x = (double) tableSize;

	double EX;

	if ((RAM == 1024) || (RAM == 2048) || (RAM == 4096)) {

		if (x <= 50000) {
			EX = -3.633160094*10^(-10)*(x^4.0) + 3.010655377*10^(-5)*(x^3) - 6.485170915*10^(-1)*x^2 + 5451.536758*x + 292221663.7;
		}
		else {
			EX = 6.522615822*10^(-12)*(x^4.0) - 3.40168904*10^(-6)*x^3 + 6.069266668*10^(-1)*x^2 - 37279.99271*x + 1167227804;
		}
	}

  
	double p = EX/5; // Kazda hodnota je 5x merena viz. dokumentace

	double rozptyl = 5*p*(1-p);

	double res = Normal(EX, rozptyl);


	printf("Size: %lu|  EX:%f, p:%f, rozptyl:%f, =%f\n", tableSize, EX, p, rozptyl, res);

	return res;
}

//
// Doba cekani na vybrani dat z urcite tabulky 
// po restartu databaze
double Proces_select_for_first_time(long tableSize, int presnost) {

	printf("Proces_select_for_first_time\n");
	return 2;
}

//
// Z tabulky jiz byla vybrana data
// vybara se z ni jiz po nekolikate
double Proces_select_N(long tableSize, int presnost) {

	printf("Proces_select_N\n");
	return 1;
}


//
// Vytvoreni objektu na zaklade dat z databaze
double Proces_create_objects(long objCnt) {

	printf("Proces_create_objects\n");
	return objCnt;
}


//
// Filtrace objektu v JAVA
double Proces_filter_objects(long objCnt, int presnost) {

	printf("Proces_filter_objects\n");
	return 1;
}


// 
// Urci kolik radku nam vrati tabulka pro urcitou presnost
long get_rows_cnt_for(long tableSize, int presnost) {

	// 0 all radky

	return 1;
}




Facility java("Java filtrace"); 

Facility db("Databaze");  


bool db_win = false;
bool java_win = false;
bool db_end = false;
bool java_end = false;


long cntPozJava = 0; // Pocet zpracovanych pozadavku JAVA


long lastTableJava = 0; // posledni tabulka
//
// Zpracovani pozadavku pomoci JAVA
class Java : public Process {


    void Behavior() {

    	double timeForProcess = 0;

 		Seize(java);
 		printf("\nJAVA - ");

 		// Uz je db hotova?
 		if (db_end) {
 			db_win = true;
 			printf("Db win");
 			Cancel();
 			return;
 		}

 		long tableSize = testovaciPozadavky[cntPozJava].tableSize;

 		// Je to jina tabulka nez predchozi?
 		if (lastTableJava != tableSize) {

 			lastTableJava = tableSize;

 			printf("\nJAVA - ");
 			// Vybrani vsech dat z tabulky
 			timeForProcess += Proces_select_all_for_first_time(lastTableJava);

 			printf("\nJAVA - ");
 			// Vytvoreni JAVA objektu
 			timeForProcess += Proces_create_objects(get_rows_cnt_for(lastTableJava, 0));

 		}
 		// Je to stejna tabulka jak predchozi
 		else {
 			// nic
 		}

 		int presnost = testovaciPozadavky[cntPozJava].presnost;

 		printf("\nJAVA - ");
 		// Filtrace v JAVA
 		timeForProcess += Proces_filter_objects(lastTableJava, presnost);

 		printf("wait: %f", timeForProcess);
 		Wait(timeForProcess);

 		cntPozJava++;
	    Release(java);

	    // ukonceni
	    if (cntPozJava == pocetPozadavku) {

	    	printf("Java end");

	    	// Db dokonceno
	    	java_end = true;

	    	if ( ! db_end) {
 				java_win = true;
	    	}
	    	else {
	    		printf("Java end DB end\n");
	    	}
	    }
    }
};



long cntPozDb = 0; // Pocet zpracovanych pozadavku databazi



long lastTableDb = 0; // posledni tabulka

//
// Zpracovani pozadavku pomoci Databaze
class Database : public Process {



    void Behavior() {

 		Seize(db);
 		printf("\nDB - ");

 		double timeForProcess = 0;

 		// Uz je db hotova?
 		if (java_end) {
 			java_win = true;
 			printf("Java win");
 			Cancel();
 			return;
 		}


 		int presnost = testovaciPozadavky[cntPozDb].presnost;

 		// Je to jina tabulka nez predchozi?
 		if (lastTableDb != testovaciPozadavky[cntPozDb].tableSize) {

 			lastTableDb = testovaciPozadavky[cntPozDb].tableSize;


 		printf("\nDB - ");
 			// Vybrani z databaze
 			timeForProcess += Proces_select_for_first_time(lastTableDb, presnost);

 		}
 		// Je to stejna tabulka jak predchozi
 		else {

 		printf("\nDB - ");
 			// Vybrani z databaze
 			timeForProcess += Proces_select_N(lastTableDb, presnost);
 		}


 		printf("\nDB - ");
 		// Vytvoreni JAVA objektu
 		timeForProcess += Proces_create_objects(get_rows_cnt_for(lastTableDb, presnost));


 		printf("wait: %f", timeForProcess);
 		Wait(timeForProcess);

 		cntPozDb++;
	    Release(db);

	    // ukonceni
	    if (cntPozDb == pocetPozadavku) {
	    	printf("DB end\n");

	    	// Db dokonceno
	    	db_end = true;

	    	if ( ! java_end) {
 				db_win = true;
	    	}
	    	else {
	    		printf("DB end Java end\n");
	    	}
	    }
    }
};




int main()
{
	
	Init(0, 10000000);

	// Nagenerovani pozadavku 
	for (int i = 0; i < pocetPozadavku; ++i)
	{
        (new Database)->Activate();
        (new Java)->Activate();
	}


	Run();


	if (java_win) {
		printf("Java win\n");
	}
	if (db_win) {
		printf("db win\n");
	}


	printf("Java\n");
	java.Output();

	printf("DB\n");
	db.Output();


	Proces_select_all_for_first_time(100);
	Proces_select_all_for_first_time(200);
	Proces_select_all_for_first_time(500);
	Proces_select_all_for_first_time(50000);
	Proces_select_all_for_first_time(200000);

	return 0;
}