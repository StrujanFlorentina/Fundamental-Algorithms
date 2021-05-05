#include<stdlib.h>
#include<iostream>
#include "Profiler.h"

Profiler P("Heap");

//parintele
int parent(int nod)
{
	return nod/2;
}

//fiul stang
int left(int nod)
{
	return 2 * nod + 1;
}

//fiul drept
int right(int nod)
{
	return 2 * nod + 2;
}

//citirea sirului
void citire(int* H, int n)
{
	int i;
	printf("Dati elementele: ");
	for (i = 0; i < n; i++)
		scanf_s("%d", &H[i]);
}

//afisarea sirului
void afisare(int* H, int n)
{
	int i;
	printf("\n");
	for (i = 0; i < n; i++)
		printf("%d ", H[i]);
	printf("\n");
}

//Procedura presupune ca subarborii nodului nod au structura de heap corecta
//Procedura asigura pozitionarea nodului nod la locul potrivit, interschimbandu-l mereu cu cel mai mare fiu al sau, pana cand nu mai are fii
//sau pana cand acestia sunt mai mici decat el
void MaxHeapify(int* H, int n, int nod)
{
	Operation comp1 = P.createOperation("BottomUp_comp", n);
	Operation atrib1 = P.createOperation("BottomUp_atrib", n);
	int max = nod, aux;
	int l = left(nod);
	int r = right(nod);
	comp1.count();
	if ((l < n) && (H[l] > H[max]))
		max = l;
	comp1.count();
	if ((r < n) && (H[r] > H[max]))
		max = r;
	if (max != nod)
	{
		atrib1.count(3);
		aux = H[nod];
		H[nod] = H[max];
		H[max] = aux;
		MaxHeapify(H, n, max);
	}
}

//Procedura construieste un heap
//Construirea se incepe de la ultimul nivel, nivelul frunzelor(arbori cu un singur fiu, deci heap-uri corecte) si se continua pana la radacina,
//folosind functia MaxHeapify
void BuildMaxHeapBottomUp(int* H, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapify(H, n, i);
}


//Procedura asigura sortarea unui vector.Se incepe cu construirea unui heap, apoi extragerea maximului(varful heap-ului) si punerea lui 
//pe ultima pozitie si refacerea heap-ului.Complexitate O(n)
void HeapSortBottomUp(int* H, int n)
{
	int aux;
	BuildMaxHeapBottomUp(H, n);
	for (int i = n - 1; i >= 0; i--)
	{
		aux = H[0];
		H[0] = H[i];
		H[i] = aux;

		MaxHeapify(H, i, 0);
	}
}

//Procedura va asigura pozitionarea nodului nod la locul potrivit, in cazul in care acesta are o valoare mai mare decat cea a tatalui sau
//Nodul se va "urca" pana la intalnirea unui tata mai mare decat el.Dupa interschimbare fiul devenit tata va fi mai mare decat ambii fii
void increaseKey(int* H, int nod, int key,int n)
{
	Operation comp2 = P.createOperation("TopDown_comp", n);
	Operation atrib2 = P.createOperation("TopDown_atrib", n);
	int aux;
	atrib2.count();
	H[nod] = key;
	if (nod > 0)
		comp2.count();
	while ((nod > 0) && (H[nod] > H[parent(nod)]))
	{
		comp2.count();
		atrib2.count(3);
		aux = H[nod];
		H[nod] = H[parent(nod)];
		H[parent(nod)] = aux;
		nod = parent(nod);
	}
}
//Procedura insereaza un nou element in heap, asezandu-l pe ultima pozitie, apoi "promovandu-l" pana la pozitia potrivita cu ajutorul increaseKey
//Complexitatea O(log n)
void push_heap(int* H, int n)
{
	for (int i = 0; i < n; i++)
	{
		increaseKey(H, i, H[i],n);
	}
}

void BuildHeapTopDown(int* H)
{
	int n;
	printf("Dati numarul de noduri ce vreti sa fie adaugate: \n");
	scanf_s("%d", &n);
	printf("Dati elementele ce vreti sa fie adaugate: ");
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &H[i]);
	}
	push_heap(H, n);
	printf("TopDown: ");
	afisare(H, n);
}

void MediuStatisticc()
{
	int sirI[10000], sir[10000], n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		for (int i = 0; i < 5; i++)
		{
			printf("%d", n);
			FillRandomArray(sirI, n, 10, 50000, false, 0);
			memcpy(sir, sirI, n * sizeof(sirI[0]));
			BuildMaxHeapBottomUp(sir, n);
			//memcpy(sir, sirI, n * sizeof(sirI[0]));
			push_heap(sirI, n);
		}
	}
	P.divideValues("BottomUp_comp", 5);
	P.divideValues("BottomUp_asign", 5);
	P.addSeries("BottomUp", "BottomUp_comp", "BottomUp_atrib");
	P.divideValues("TopDown_comp", 5);
	P.divideValues("TopDown_atrib", 5);
	P.addSeries("TopDown", "TopDown_comp", "TopDown_atrib");
	P.createGroup("BottomUpMediuStatistic", "BottomUp_comp", "BottomUp_atrib", "BottomUp");
	P.createGroup("TopDownMediuStatistic", "TopDown_comp", "TopDown_atrib", "TopDown");
	P.showReport();
}

int main()
{
	int n, H[11],A[11];
	printf("Dati numarul de elemente pentru BottomUp: ");
	scanf_s("%d", &n);
	citire(H, n);
	BuildMaxHeapBottomUp(H, n);
	printf("BottomUp: ");
	afisare(H, n);
	HeapSortBottomUp(H, n);
	printf("HeapSort: ");
	afisare(H, n);
	BuildHeapTopDown(A);
	MediuStatisticc();
	return 0;
}