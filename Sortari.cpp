/*Strujan Florentina, seria B, grupa 302210
Sortarile BubbleSort, InserionSort si SelectionSort
*/

#include <stdlib.h>
#include <iostream>
#include "Profiler.h"
using namespace std;

Profiler P("Sortari");

void citire_sir(int* sir,int n)
{
	int i;
	printf("Dati elementele:");
	for (i = 0; i < n; i++)
		scanf_s("%d", &sir[i]);
}
void afisare_sir(int* sir, int n)
{
	int i;
	for (i = 0; i< n; i++)
		printf("%d ", sir[i]);
}
/*Metoda BubbleSort sorteaza sirul dat comparand intotdeauna elementele adiacente(vecinii) si interschimbandu-i in cazul in care primul este mai mare decat al doilea.
Se fac n-1 treceri pentru a ne asigura ca sirul este sortat.Dupa fiecare parcurgere, cel mai mare element ajunge pe ultima pozitie a sirului.
Pentru cazul favorabil avem sirul crescator, pentru care nu se face nicio atribuire( O(c) ) si n-1 comparatii ( O(n) ), iar pentru cazul nefavorabil avem 
sirul descrescator pentru care se fac 3*(n-1) atribuiri (O(n)) si n-1 comparatii (O(n)).
Este stabil si adaptiv. Am creat operatiile comp1 si atrib1 pentru a numara comparatiile, respectiv artibuirile facute.
*/
void BubbleSort(int* sir, int n)
{
	int sortat = 0, counter = 0, i, aux;
	Operation comp1 = P.createOperation("BubbleSort_comp", n);
	Operation atrib1 = P.createOperation("BubbleSort_atrib", n);
	while (sortat == 0)
	{
		sortat = 1;
		for (i = 0; i < n - 1 - counter; i++)
		{
			comp1.count();
			if (sir[i] > sir[i + 1])
			{
				atrib1.count(3);
				aux = sir[i];
				sir[i] = sir[i + 1];
				sir[i + 1] = aux;
				sortat = 0;
			}
		}
		counter++;
	}
}

/*Metoda InsertionSort presupune inserarea primului element din partea nesorata a sirului in partea sortata, in functie de pozitia la care se potriveste
(parcurge de la dreapta spre stanga partea sortata, oprindu-se la primul element mai mic decat el, mutand restul elementelor cu o pozitie spre dreapta).
Pentru cazul favorabil avem sirul crescator, pentru care se fac 2*(n-1) atribuiri (O(n)) si n - 1 comparatii(O(n)), iar pentru cazul nefavorabil avem
sirul descrescator pentru care se fac 2*(n-1)+n*(n-1)/2 atribuiri (O(n^2)) si n-1+n*(n-1)/2 comparatii(O(n^2)).
Nu este stabil,dar este adaptiv, mai adaptiv decat SelectionSort .Am creat operatiile comp1 si atrib1 pentru a numara comparatiile, respectiv artibuirile facute.
*/
void InsertionSort(int* sir, int n)
{
	int i, j, key;
	Operation comp2 = P.createOperation("InsertionSort_comp", n);
	Operation atrib2 = P.createOperation("InsertionSort_atrib", n);
	for (i = 1; i < n; i++)
	{
		atrib2.count();
		key = sir[i];
		j = i - 1;
		while ((j >= 0) && (sir[j] > key))
		{
			comp2.count();
			atrib2.count();
			sir[j + 1] = sir[j];
			j--;
		}
		if (j >= 0)
			comp2.count();
		atrib2.count();
		sir[j + 1] = key;
	}
}

/*Metoda SelectionSort se axeaza pe gasirea si selectia minimului din sirul nesortat si punerea lui la finalul partii sortate, prin interschimbare.
Pentru cazul favorabil avem sirul crescator, pentru care nu se face nicio atribuire( O(c) ) si n*(n-1)/2 comparatii ( O(n^2) ), iar pentru cazul nefavorabil avem 
sirul crescator cu ultimul element inaintea primului pentru care se fac 3*(n-1) atribuiri (O(n)) si n*(n-1)/2 comparatii (O(n^2)).
Nu este stabil si nici foarte adaptiv. Am creat operatiile comp1 si atrib1 pentru a numara comparatiile, respectiv artibuirile facute.*/

void SelectionSort(int* sir, int n)
{
	int i, j, min, aux;
	Operation comp3 = P.createOperation("SelectionSort_comp", n);
	Operation atrib3 = P.createOperation("SelectionSort_atrib", n);
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			comp3.count();
			if (sir[min] > sir[j])
				min = j;
		}
		if (i != min)
		{
			atrib3.count(3);
			aux = sir[i];
			sir[i] = sir[min];
			sir[min] = aux;
		}
	}
}
//verificarea corectitudinii metodei BubbleSort
void verificareB()
{
	int n,sir[10];
	printf("Dati numarul de elemente");
	scanf_s("%d", &n);
	citire_sir(sir,n);
	afisare_sir(sir, n);
	BubbleSort(sir, n);
	printf("\n");
	afisare_sir(sir, n);
	printf("\n");
}
//verificarea corectitudinii metodei InsertionSort
void verificareI()
{
	int n, sir[10];
	printf("Dati numarul de elemente: ");
	scanf_s("%d", &n);
	citire_sir(sir,n);
	afisare_sir(sir, n);
	InsertionSort(sir, n);
	printf("\n");
	afisare_sir(sir, n);
	printf("\n");
}
//verificarea corectitudinii metodei SelectionSort
void verificareS()
{
	int n, sir[10];
	printf("Dati numarul de elemente: ");
	scanf_s("%d", &n);
	citire_sir(sir,n);
	afisare_sir(sir, n);
	SelectionSort(sir, n);
	printf("\n");
	afisare_sir(sir, n);
	printf("\n");
}

void BestCase()
{
	int sirI[10000],sir[10000],n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("%d", n);
		FillRandomArray(sirI, n, 10, 50000, false, 1);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		BubbleSort(sir, n);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		InsertionSort(sir, n);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		SelectionSort(sir, n);
	}
	P.addSeries("BubbleSortOp", "BubbleSort_comp", "BubbleSort_atrib");
	P.addSeries("InsertionSortOp", "InsertionSort_comp", "InsertionSort_atrib");
	P.addSeries("SelectionSortOp", "SelectionSort_comp", "SelectionSort_atrib");
	P.createGroup("BubbleSortBestCase", "BubbleSort_comp", "BubbleSort_atrib","BubbleSortOp");
	P.createGroup("InsertionSortBestCase", "InsertionSort_comp", "InsertionSort_atrib","InsertionSortOp");
	P.createGroup("SelectionSortBestCase", "SelectionSort_comp", "SelectionSort_atrib","SelectionSortOp");

	P.showReport();
}

void WorstCase()
{
	int sirI[10000], sir[10000], n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("%d", n);
		FillRandomArray(sirI, n, 10, 50000, false, 2);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		BubbleSort(sir, n);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		InsertionSort(sir, n);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		for (int i = n; i >0; i--)
			sir[i ] = sir[i-1];
		sir[0] = sir[n];
		SelectionSort(sir, n);
	}
	P.addSeries("BubbleSortOp", "BubbleSort_comp", "BubbleSort_atrib");
	P.addSeries("InsertionSortOp", "InsertionSort_comp", "InsertionSort_atrib");
	P.addSeries("SelectionSortOp", "SelectionSort_comp", "SelectionSort_atrib");
	P.createGroup("BubbleSortWorstCase", "BubbleSort_comp", "BubbleSort_atrib", "BubbleSortOp");
	P.createGroup("InsertionWorstCase", "InsertionSort_comp", "InsertionSort_atrib", "InsertionSortOp");
	P.createGroup("SelectionWorstCase", "SelectionSort_comp", "SelectionSort_atrib", "SelectionSortOp");

	P.showReport();
}

void MediuStatistic()
{
	int sirI[10000], sir[10000], n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("%d", n);
		FillRandomArray(sirI, n, 10, 50000, false, 0);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		BubbleSort(sir, n);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		InsertionSort(sir, n);
		memcpy(sir, sirI, n * sizeof(sirI[0]));
		SelectionSort(sir, n);
	}
	P.divideValues("BubbleSort_comp", 5);
	P.divideValues("BubbleSort_asign", 5);
	P.addSeries("BubbleSortOp", "BubbleSort_comp", "BubbleSort_atrib");
	P.divideValues("InsertionSort_comp", 5);
	P.divideValues("InsertionSort_atrib", 5);
	P.addSeries("InsertionSortOp", "InsertionSort_comp", "InsertionSort_atrib");
	P.divideValues("SelectionSort_comp", 5);
	P.divideValues("SelectionSort_atrib", 5);
	P.addSeries("SelectionSortOp", "SelectionSort_comp", "SelectionSort_atrib");
	P.createGroup("BubbleSortMediuStatistic", "BubbleSort_comp", "BubbleSort_atrib", "BubbleSortOp");
	P.createGroup("InsertionMediuStatistic", "InsertionSort_comp", "InsertionSort_atrib", "InsertionSortOp");
	P.createGroup("SelectionMediuStatistic", "SelectionSort_comp", "SelectionSort_atrib", "SelectionSortOp");

	P.showReport();
}

int main()
{
	/*BestCase();
	P.reset();
	WorstCase();
	P.reset();
	MediuStatistic();*/
	verificareB();
	verificareI();
	verificareS();
	return 0;
}