
// 3.1 Mein erstes Programm

#include <stdio.h>

int main()
{
printf("my first program");
return(0);
}

// Compiliere
// cc -o first first.c -Wall
// Starte
// ./first

//3.2 Variablen, Befehle, Ausdrücke

// Wichtige Typen:
// int, double, char, Arrays=Zeiger, Funktionen, Strukturen, Selbst-definierte Datentypen, beliebige Kombinationen

// Mehrere Variablen auf einmal deklarieren:
double number1, average, sum;

// Zuweisug, arithmetische Ausdrücke

a = b + c;
value = 3.0*sin(angle);
hours = minutes/60;
mod = x % y;
value += delta;
counter++;
number--;
code = input & mask; /* bitwise AND */
code2 = input | mask2; /* bitwise OR */
rest = sequence << n; /* bit shift left by n bits */

// for-Schleife
for(<initial>; <condition>; <command>)
	<command>;

// while-Schleife
while(<condition>)
	<command>;

// if-Befehl
if(<condition>)
	<command1>;
else
	<command2>;

//Mögliche conditions
a==b, a!=b, a<b, a<=b, a>b, a>=b;

if( (money>100) || ((price < 10) && (money>20)) )
	printf("Buy it!!\n");

// Blöcke anstatt eines einzelnen Befehls
{
<command1>;
<command2>;
...
}

// Casts übersetzen Datentypen

int z;
z = (int) 3.2;
printf("%d\n", z); // ergibt 3

// 3.3 Arrays

// Arrays = Vektoren oder “Listen” von Variablen. Deklaration: <type> <name>[<size>]. Arrays starten mit Index 0, laufen bis <size>-1.

int main()
{
int counter;
double value[10];
for(counter=0; counter<10; counter++)
value[counter]=counter*counter + 0.1;
return(0);
}

// Matrix = Array von Arrays:
double matrix[10][10];
for(row=0; row<10; row++)
	for(column=0; column<10; column++)
		result[row][column] = matrix1[row][column] + matrix2[row][column];	

// 3.4 Unterprogramme, Funktionen

#include <stdio.h>
#include <math.h>

int main()
{
	double argument;
	argument = 0.0;
	while (argument < 2*M_PI)
	{
		printf("sin(%f)=%f\n", argument, sin(argument));
		argument += 0.1;
	}
	return(0);
}

// Linke Bibliothek beim Compilieren: -l<lib-name>
// cc -o first first.c -Wall -lm

// Zufallszahlen
#include <stdlib.h>
value = drand48(); // Zufallszahl in [0,1]

// Eigene Funktionen definieren

double calc_average(int number, double value[])
{
	int counter; /* local variable, not visible e.g. in main() */
	double sum; /* the same */
	sum = 0.0;
	for(counter=0; counter<number; counter++)
		sum += value[counter];
	return(sum/number);
}

int main()
{
	int counter;
	double value[10];
	double average;
	for(counter=0; counter<10; counter++)
		value[counter]=counter*counter;
	average = calc_average(10, value);
	printf("avg=%f\n", average);
	return(0);
}

// Unterprogramme = Funktionen ohne Rückgabewert

void print_value_and_flowers(int x)
{
	printf("flowers\n, value=%d, flowers\n", x);
}

// Mehr als ein Rückgabewert: Strukturen oder Zeiger

// 3.5 Geltungsbereich von Variablen
// Variablen sind lokal, bis auf (SEHR BÖSE!!) globale

// 3.6 Strings

char name[100]; // up to 99 characters
strpy(name, "Robert Smith");
printf("length(%s)=%d\n", name, strlen(name));
sprintf(string, <format string>, ...);
// valgrind findet Speicherfehler

// 3.7 Strukturen, selbst-definierte Datentypen

struct particle
{
double mass;
int charge;
double position[3];
}

struct particle particle1; // Variablen-Deklaration

particle1.mass = 9.109e-31;
particle1.charge = 1;
particle1.position[0] = -2.3e-3;

typedef double vector_t[3]; // eigener Datentyp
typedef struct particle particle_t;

vector_t velocity; // Variablen-Deklaration
particle_t electron;

// Alle Datentypen in extra Header (.h) File sammeln
// mit Strukturen kann man leicht Funktionen implementieren, die mehrere Daten zurückgeben

particle_t initialise_atom()
{
particle_t atom;
atom.mass = 1;
...
return(atom);
}

// 3.8 Pointer

// Pointer (Zeiger) = Adresse einer Variable im Speicher.
// Deklaration: <type> *ptr erzeugt ptr als Adresse einer Variablen des Typs <type>.
// &-Operator gibt Adresse der Variablen: & <variable>.
// *ptr = Inhalt der Variablen auf die ptr zeigt, d.h. man kann den Inhalt setzen durch *prt= <expression>.

int number, *address;
number = 50;
address = & number;
*address = 100;
printf("%d\n", number); // ergibt 100

// Arrays = Pointer, int value[10] 
// -> value = Adresse des Anfangs des Arrays, d.h. von value[0]. 
// Beides int value[10] und int *value2 = Pointer auf int, aber für value wird Array der Länge 10 reserviert und value zeigt auf den Array Anfang. value2 erhält anfangs KEINEN Wert.
// Zugriff: value[5] ist äquivalent zu *(value+5).

struct particle *atom;
...
atom->mass = 2.0; // Zugriff auf Elemente
//(äquivalent (*atom).mass=2.0)

// Pointer: verwendbar um komplexe Beziehungen zwischen Variablen herzustellen
// Pointer: verwendbar um aus Funktion Daten ohne return zurückzugeben

void add_numbers(int n1, int n2, int *result_p)
{
*result_p = n1+n2;
}

// Pointer result_p kann in add_numbers(), nur den Inhalt des Speichers ändern, auf den result_p zeigt, nicht aber den (externen) Wert von result_p.

// 3.9 Dynamische Speicher Allozierung

// Arrays dynamisch mit malloc(<number of bytes>) (definiert in stdlib.h) allozieren. Benutze sizeof(<data type>) um Array-Größe festzulegen.

struct particle *atom2;
int num_atoms;
...
atom2 = (struct particle *) malloc(num_atoms*sizeof(struct particle));

free(atom2); // Freigabe

// Allozierung von Matrizen variabler Größe in 2 Schritten.
// Grunprinzip n×m Matrix: Erst Array von n Pointern allozieren, 
// dann n mal Array von m double allozieren.

int num_rows, num_columns, row;
double **matrix;
...
matrix = (double **) malloc(num_rows*sizeof(double *));
for(row=0; row<num_rows; row++)
	matrix[row] = (double *) malloc(num_columns*sizeof(double));

// Freigabe

for(row=0; row<num_rows; row++)
	free(matrix[row]);
free(matrix);

// 4.2 Debugger

// gdb 

int main(int argc, char *argv[])
{
int t, *array, sum = 0;
array = (int *) malloc (100*sizeof(int));
for(t=0; t<100; t++)
	array[t] = t;
for(t=0; t<100; t++)
	sum += array[t];
printf("sum= %d\n", sum);
free(array);
return(0);
}

// Compilieren:
// cc -o gdbtest -g gdbtest.c

// Starten des Debuggers
// gdb gdbtest

// Kommandos durch Texteingabe
// list -> Source code an aktueller Stelle ansehen
// help line -> mehr Infos

// Setzen von Breakpoints: break (kurz b) + Zeilennumer oder Funktionsname
// Breakpoints löschen: delete
// Programm starten: run (kurz r)
// Variablen anehen: print (kurz p) + Variablenname
// Dauerhafte Anzeige: display
// Wert ändern: set var (kurz set var) + Variablenname
// Programm schrittweise fortsetzen: next (kurz n)
// In Funktionen reinschauen: step (kurz s)
// Ausführung bis zum nächsten Brealpoint/Ende: continue (kurz c)
// Breakpoints mit Bedingung: condition + NumberBreakpoint + (condition)
// Ausgeben eigener Datenstrukturen: Funktionen implementieren und jederzeit mit call aufrufen
// Weitere Infos: info

// 4.3 Memory Checker

// Fehler:
// - Zugiff hinter Array Grenzen
// - Zugriff auf bereits freigegebenen Speicher
// - Vergessen mit malloc allozierten Speicher freizugeben








