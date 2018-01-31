#include "data.h"


//
// Tabulky v cache databaze
//

typedef struct tDbCache
{
	long tableName;
	tDbCache * next;
} tDbCache;

tDbCache * db_for_db;
tDbCache * db_for_java;

//
// Je v db uz nakeshovana?
bool DB_is_cached(tDbCache * db, long tableName) {

	tDbCache * ptr = db;

	while (ptr)  {
		if (ptr->tableName == tableName) return 1;
		ptr = ptr->next;
	}

	return 0;
}


void DB_insert(tDbCache ** db, long tableName) {

	if ( ! DB_is_cached((*db), tableName)) {

		// prvni prvek
		if ((*db) == NULL) { 
			tDbCache * newPr = (tDbCache *) malloc(sizeof(tDbCache));
			if (newPr == NULL) {
				if (DEBUG) printf("Error malloc.\n");
				exit(1);
			}
			(*db) = newPr;
			(*db)->tableName = tableName;
			(*db)->next = NULL;
			return;
		}

		// vice nez jeden prvek

		tDbCache * last = (*db);
		int cnt = 1;

		while (last->next != NULL)  {
			cnt++;
			last = last->next;
		}


		if (cnt >= DB_CACHE) {
			// zapomeneme prvni
			tDbCache * newFirst = (*db)->next;
			free((*db));
			(*db) = newFirst;
		}

		// insertujeme posledni
		tDbCache * newPr = (tDbCache *) malloc(sizeof(tDbCache));
		if (newPr == NULL) {
			if (DEBUG) printf("Error malloc.\n");
			exit(1);
		}

		newPr->tableName = tableName;
		newPr->next = NULL;

		last->next = newPr;
	}
}


//
// Vymazani cache
void DB_clear(tDbCache ** db) {

	if ((*db) != NULL) {
		
		tDbCache * next = (*db)->next;
		free((*db));
		(*db) = next;

		while ((*db) != NULL) {
			next = (*db);
			(*db) = (*db)->next;
			free(next);
		}
	}
}

//
// Obsah DB
void DB_content(tDbCache * db) {

	tDbCache * ptr = db;
	if (DEBUG) printf("============================\n");
	while (ptr)  {
		if (DEBUG) printf("%lu\n", ptr->tableName);
		ptr = ptr->next;
	}
	if (DEBUG) printf("============================\n");
}



//
// Jednotlive přechody
//


//
// Doba cekani na vybrani vsech dat z urcite tabulky 
// po restartu databaze
double Proces_select_all_for_first_time(long tableSize) {

	double x = (double) tableSize;
	double rozptyl = 0;
	double EX = 0;

	if (x <= 50000) { 

		rozptyl = 17783287.41;
		EX = -3.633160094*pow(10, (-10))*pow(x, 4.0)+3.010655377*pow(10, (-5))*pow(x, 3)-6.485170915*pow(10, (-1))*pow(x, 2)+5451.536758*x+292221663.7;
	}
	else {

		rozptyl = 52717087.64;
		EX = 6.522615822*pow(10,(-12))*pow(x, 4.0)-3.40168904*pow(10, (-6))*pow(x, 3)+6.069266668*pow(10, (-1))*pow(x, 2)-37279.99271*x+1167227804;
	}

	double res = Normal(EX, rozptyl);

	if (DEBUG) printf("DB select all rows> Size: %lu|  EX:%g, rozptyl:%g, =%g\n", tableSize, EX, rozptyl, res);
	return (res/1000000); // Prevod ns na ms
}

//
// Doba cekani na vybrani dat z urcite tabulky 
// po restartu databaze
double Proces_select_for_first_time(long tableSize, int presnost) {

	double x = (double) tableSize;
	double rozptyl = 0;
	double EX = 0;

	if (presnost == 0) {
		return Proces_select_all_for_first_time(tableSize);
	}
	else if (presnost == 1)
	{
		if (x <= 30000) { 
			rozptyl = 22263113.77;
			EX = 8.413280178*pow(10, (-10))*pow(x, 4) - 5.305512854*pow(10, (-5))*pow(x, 3) + 9.584964437*pow(10, (-1))*pow(x, 2) - 2991.863661*x + 376904280.1;
		}
		else {
			rozptyl = 23823072.64;
			EX = 1.111638274*pow(10, (-12))*pow(x, 4) - 5.510163743*pow(10, (-7))*pow(x, 3) + 8.107319807*pow(10, (-2))*pow(x, 2) + 121.6715031*x + 339723127.2;
		}
	}
	else if (presnost == 10)
	{
		if (x <= 30000) { 
			rozptyl = 17698652.37;
			EX = 3.377060336*pow(10, (-10))*pow(x, 4) - 2.114107523*pow(10, (-5))*pow(x, 3) + 4.039350052*pow(10, (-1))*pow(x, 2) + 76.61222593*x + 347074150.9;
		}
		else {
			rozptyl = 22221616.21;
			EX = 2.543890049*pow(10, (-12))*pow(x, 4) - 1.376538139*pow(10, (-6))*pow(x, 3) + 0.242131595*pow(x, 2) - 12585.17677*x + 611318291.8;
		}
	}
	else if (presnost == 100)
	{
		if (x <= 30000) { 
			rozptyl = 19977605.55;
			EX = 5.169203418*pow(10, (-9))*pow(x, 4) - 3.042955354*pow(10, (-4))*pow(x, 3) + 5.492220533*pow(x, 2) - 30477.43456*x + 378982123.1;
		}
		else {
			rozptyl = 23464799.62;
			EX = 1.546782181*pow(10, (-12))*pow(x, 4) - 8.042593597*pow(10, (-7))*pow(x, 3) + 1.331242376*pow(10, (-1))*pow(x, 2) - 5033.085524*x + 435600300;
		}
	}
	else if (presnost == 1000)
	{
		if (x <= 30000) { 
			rozptyl = 17836242.56;
			EX = 2.603872633*pow(10, (-9))*pow(x, 4) - 1.593687428*pow(10, (-4))*pow(x, 3) + 2.975291953*pow(x, 2) - 15458.79867*x + 324348925.5;
		}
		else {
			rozptyl = 17518427.85;
			EX = 1.265445563*pow(10, (-12))*pow(x, 4) - 6.225847516*pow(10, (-7))*pow(x, 3) + 9.253313815*pow(10, (-2))*pow(x, 2) - 1668.344913*x + 326546804;
		}
	}


 
	double res = Normal(EX, rozptyl);

	if (DEBUG) printf("DB select first time> Size: %lu|  EX:%g, rozptyl:%g, =%g\n", tableSize, EX, rozptyl, res);
	return res/1000000; // Prevod ns na ms
}

//
// Z tabulky jiz byla vybrana data
// vybara se z ni jiz po nekolikate
double Proces_select_N(long tableSize, int presnost) {

	double x = (double) tableSize;
	double rozptyl = 0;
	double EX = 0;

	if (presnost == 1) { // SELECT 1
		if (x <= 100000) { 
			rozptyl = 12181740.935322901;
			EX =  8.7499183322292536e+007 * pow(x,0)
		        +  1.4306785198833036e+003 * pow(x,1)
		        + -1.2164796597581025e-002 * pow(x,2)
		        +  3.1897467136335933e-008 * pow(x,3);
		}
		else {
			rozptyl = 308751474.4975068;
			EX = 2.0101596166555294e+008 * pow(x,0)
	        + -4.3162399019284121e+003 * pow(x,1)
	        +  4.4605713119624614e-002 * pow(x,2)
	        + -6.2584904146892900e-008 * pow(x,3)
	        + -2.9269866088521469e-013 * pow(x,4)
	        +  1.8568374966457155e-018 * pow(x,5);
		}
	}
	else if ((presnost == 10) || (presnost == 100) || (presnost == 1000)) { // 10 100 1000
		rozptyl = 7773926.666;
		EX = -1.944093758*pow(10, (-13))*pow(x, 4)+8.979902382*pow(10, (-8))*pow(x, 3)-1.225073446*pow(10, (-2))*pow(x, 2)+874.8471046*x+91579897.79;
	}
	else {
		if((x>100) && (x<=500))
		{
			rozptyl = 4686004.707;
		}
		if((x>500) && (x<=1000))
		{
			rozptyl = 4987878.088;
		}
		if((x>1000) && (x<=2000))
		{
			rozptyl = 4619003.685;
		}
		if((x>2000) && (x<=5000))
		{
			rozptyl = 4486389.328;
		}
		if((x>5000) && (x<=7500))
		{
			rozptyl = 5014263.891;
		}
		if((x>7500) && (x<=10000))
		{
			rozptyl = 14060348.47;
		}
		if((x>10000) && (x<=20000))
		{
			rozptyl = 28521437.11;
		}
		if((x>20000) && (x<=30000))
		{
			rozptyl = 27011173.59;
		}
		if((x>30000) && (x<=50000))
		{
			rozptyl = 17945548.25;
		}
		if((x>50000) && (x<=75000))
		{
			rozptyl = 22618628.78;
		}
		if((x>75000) && (x<=100000))
		{
			rozptyl = 172245952.1;
		}
		if((x>100000) && (x<=200000))
		{
			rozptyl = 397341689.5;
		}
		if((x>200000) && (x<=250000))
		{
			rozptyl = 300896812.5;
		}

		if (x <= 75000) {
			EX = -1.650711644*pow(10, (-2))*pow(x, 2) + 2959.56312*x + 5594917.196;
		}
		else {
			EX = 1.224686075*pow(10, (-2))*pow(x, 2) + 9729.457018*x - 626953113.2;
		}
	}


 
	double res = Normal(EX, rozptyl);

	if (DEBUG) printf("DB select N> Size: %lu pres: %d|  EX:%g, rozptyl:%g, =%g\n", tableSize, presnost, EX, rozptyl, res);
	return res/1000000; // Prevod ns na ms
}


//
// Vytvoreni objektu na zaklade dat z databaze
double Proces_create_objects(long tableSize, int presnost) {

	double ret = 0;

	int exponent = 0;

	if (presnost == 0) {
		exponent = 0;
	}
	else if (presnost == 1) {
		exponent = 1;
	}
	else if (presnost == 10) {
		exponent = 2;
	}
	else if (presnost == 100) {
		exponent = 3;
	}
	else if (presnost == 1000) {
		exponent = 4;
	}

	double cntObj = tableSize/pow(10, exponent);

	if (cntObj < 1) { // Prilisna presnost nad tabulkou, jej jasne vybran jeden prvek
		cntObj = 1;
	}

	// Vytvoreni objektu
	for (int i = 0; i < cntObj; ++i) {
		ret += Normal(88093.24, 14514.355);
	}


	if (DEBUG) printf("Tvorba objektu> Size: %lu (obj: %f)| =%g \n", tableSize, cntObj, ret);
	return ret/1000000; // Prevod ns na ms
}


//
// Filtrace objektu v JAVA
double Proces_filter_objects(long tableSize, int presnost) {

	double x = (double) tableSize;
	double rozptyl = 0;
	double EX = 0;

	// RAM nezalezi
	if (presnost == 0) {
		return 0; // filtrace vsech netrva nic
	}

	if (presnost == 1) {

		if (x <= 500) {
			rozptyl = 93047.18049;
			EX = 1052.28*x + 500682;
		}
		else if (x <= 2000) {
			rozptyl = 1089802.987;
			EX = -2.848496933*pow(x, 2) + 8403.3634*x - 2462735.067;
		}
		else if (x <= 20000) {
			rozptyl = 664370.3361;
			EX = 1.288513437*pow(10, (-9))*pow(x, 4) - 4.794834544*pow(10, (-5))*pow(x, 3) + 5.560013426*pow(10, (-1))*pow(x, 2) - 1964.93922*x + 5018847.618;
		}
		else {
			rozptyl = 1362728.391;
			EX = -6.726539099*pow(10, (-15))*pow(x, 4) + 7.008578903*pow(10, (-9))*pow(x, 3) - 2.139562281*pow(10, (-3))*pow(x, 2) + 509.1881486*x + 1200288.689;	
		}
	}
	else { // 10 100 1000

		if (x <= 5000) {
			rozptyl = 298763.312;
			EX = -5.637501865*pow(10, (-2))*pow(x,2) + 917.2501529*x + 420823.9099;
		}
		else if (x <= 20000) {
			rozptyl = 770391.34;
			EX = 1.092857643*pow(10, (-5))*pow(x, 3) - 3.993301536*pow(10, (-1))*pow(x, 2)+ 4728.083749*x - 11414432.16;
		}
		else {
			rozptyl = 2074518.806;
			EX = -2.804699165*pow(10, (-14))*pow(x, 4) + 1.831345456*pow(10, (-8))*pow(x, 3) - 4.039533162*pow(10, (-3))*pow(x, 2)+ 631.0639661*x - 761899.8207;
		}
	}
	

	double res = Normal(EX, rozptyl);

	if (DEBUG) printf("Filtrace objekctu> Size: %lu|  EX:%g, rozptyl:%g, =%g\n", tableSize, EX, rozptyl, res);
	return res/1000000; // Prevod ns na ms // z ms
}


// 
Facility java("Java filtrace"); 
Facility db("Databaze");  

// Kdo vyhral
bool db_win = false;
bool java_win = false;
bool db_end = false;
bool java_end = false;

// Celkove casy
double java_time = 0;
double db_time = 0;


long cntPozJava = 0; // Pocet zpracovanych pozadavku JAVA
long lastTableJava = 0; // posledni tabulka
//
// Zpracovani pozadavku pomoci JAVA
class Java : public Process {


    void Behavior() {

    	double timeForProcess = 0;

 		Seize(java); 

 		// Uz je db hotova?
 		if (db_end) {
 			db_win = true;
 			if (SHOW_TIME_END) { // pokud chceme zjistit cas, tak nechame
 				Cancel();
 				return;
 			}
 		}

 		long tableSize = testovaciSelecty[cntPozJava].tableSize;
 		int presnost = testovaciSelecty[cntPozJava].presnost;

 		if (DEBUG) printf("\nJava> Tab.: %lu, pres.: %d\n", tableSize, presnost );

		// Vymazani cache db
 		if (tableSize == 0) {
 			if (presnost == 1) {
	 			if (DEBUG) printf("Clear - java memory\n");
 			}
 			else {
	 			if (DEBUG) printf("Clear\n");
	 			DB_clear(&db_for_java);
 			}
	 		cntPozJava++;
 			Release(java); 
	 		lastTableJava = 0;
	 		Cancel();
	 		return;
 		}
 		else {

 			// Je kes v DB a je v JAVA
 			if (lastTableJava == tableSize) {
 				// nedelam nic
 			}
 			// Je kes v DB
 			else if (DB_is_cached(db_for_java, tableSize)) {

	 			timeForProcess += Proces_select_N(tableSize, 0);
	 			// Vytvoreni JAVA objektu
	 			timeForProcess += Proces_create_objects(tableSize, 0);
 			}
 			// Neni nikde
 			else {
 				// Prvni select vsech
	 			timeForProcess += Proces_select_all_for_first_time(tableSize);
	 			// Vytvoreni JAVA objektu
	 			timeForProcess += Proces_create_objects(tableSize, 0);

	 			// Cache db
	 			DB_insert(&db_for_java, tableSize);
 			}

	 		lastTableJava = tableSize;

	 		// Filtrace v JAVA
	 		timeForProcess += Proces_filter_objects(lastTableJava, presnost);

	 		if (DEBUG) printf("Java> doba zpracovani: %f\n", timeForProcess);
	 		if (SHOW_TIME_PART) printf("JAVA;%s;%lu;%d;%f;\n", EXPERIMENT_NAME, tableSize, presnost, timeForProcess);

	 		java_time += timeForProcess;

	 		Wait(timeForProcess);

	 		cntPozJava++;
		    Release(java);

		    // ukonceni
		    if (cntPozJava == pocetPozadavku) {

		    	// Db dokonceno
		    	java_end = true;

		    	if ( ! db_end) {
	 				java_win = true;
		    	}
		    }
		}
    }
};



long cntPozDb = 0; // Pocet zpracovanych pozadavku databazi


//
// Zpracovani pozadavku pomoci Databaze
class Database : public Process {



    void Behavior() {

 		Seize(db);
 		 

 		double timeForProcess = 0;

 		// Uz je db hotova?
 		if (java_end) {
 			java_win = true;
 			if (SHOW_TIME_END) { // pokud chceme zjistit cas, tak nechame
 				Cancel();
 				return;
 			}
 		}

 		int presnost = testovaciSelecty[cntPozDb].presnost;
 		long tableSize = testovaciSelecty[cntPozDb].tableSize;

		if (DEBUG) printf("\nDB> Tab.: %lu, pres.: %d\n", testovaciSelecty[cntPozDb].tableSize, presnost );

 		// Vymazani cache db
 		if (tableSize == 0) {
 			if (presnost == 1) {
	 			// clear JAVA mem
 			}
 			else {
	 			if (DEBUG) printf("clear\n");
	 			DB_clear(&db_for_db);
 			}
		    Release(db);
	 		cntPozDb++;
	 		Cancel();
	 		return;
 		}
 		else {

	 		// Je to jina tabulka nez predchozi?
	 		if ( ! DB_is_cached(db_for_db, tableSize)) {
	 			 
	 			DB_insert(&db_for_db, tableSize);

	 			// Vybrani z databaze poprve
	 			timeForProcess += Proces_select_for_first_time(tableSize, presnost);
	 		}
	 		// Je to stejna tabulka jak predchozi
	 		else {
	 			// Vybrani z databaze
	 			timeForProcess += Proces_select_N(tableSize, presnost);
	 		}

	 		// Vytvoreni JAVA objektu
	 		timeForProcess += Proces_create_objects(tableSize, presnost);


	 		if (DEBUG) printf("Db> doba zpracovani: %f\n", timeForProcess);
	 		if (SHOW_TIME_PART) printf("DB;%s;%lu;%d;%f;\n", EXPERIMENT_NAME, tableSize, presnost, timeForProcess);


	 		db_time += timeForProcess;
	 		Wait(timeForProcess);

	 		
	 		cntPozDb++;
		    Release(db);

		    // ukonceni
		    if (cntPozDb == pocetPozadavku) {
		    	// Db dokonceno
		    	db_end = true;

		    	if ( ! java_end) {
	 				db_win = true;
		    	}
		    }
	    }
    }
};

class GeneratorPozadavku: public Event {
  	void Behavior() {

  		// Nagenerovani pozadavku 
		for (int i = 0; i < pocetPozadavku; ++i)
		{
	        (new Database)->Activate();
	        (new Java)->Activate();
		}
	}
};


int main()
{
	Init(0, dobaSimulace);

  	(new GeneratorPozadavku)->Activate();

	Run();

	if ((java_win) && (db_win)) {
		if (SHOW_WINER) printf("\nNerozhodne.\n");
	}
	else if (java_win) {
		if (SHOW_WINER) printf("\nJava: vyhrala\n");
	}
	else if (db_win) {
		if (SHOW_WINER) printf("\nDatabaze: vyhrala\n");
	}

	printf("\n");

	if (SHOW_TIME_END) {
		printf("JAVA;%s;%f\n", EXPERIMENT_NAME, java_time);
		printf("DB;%s;%f\n", EXPERIMENT_NAME, db_time);
	}

	return 0;
}