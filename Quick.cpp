/*Strujan Florentina, seria B, grupa 302210
Analiza și compararea metodelor avansate de sortare – HeapSort și QuickSort / QuickSelect
*/

#include<stdlib.h>
#include<iostream>
#include "Profiler.h"

Profiler P("QuickHeap"); 

//parintele
int parent(int nod)
{
	return nod / 2;
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

void MaxHeapify(int* H, int n, int nod,Operation& comp1, Operation& atrib1)
{
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
		MaxHeapify(H, n, max,comp1,atrib1);
	}
}
void BuildMaxHeapBottomUp(int* H, int n,Operation& comp1, Operation& atrib1)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MaxHeapify(H, n, i,comp1, atrib1);
}
void HeapSort(int* H, int n)
{
	Operation comp1 = P.createOperation("Heap_comp", n);
	Operation atrib1 = P.createOperation("Heap_atrib", n);
	int aux;
	BuildMaxHeapBottomUp(H, n,comp1,atrib1);
	for (int i = n - 1; i >= 0; i--)
	{
		atrib1.count(3);
		aux = H[0];
		H[0] = H[i];
		H[i] = aux;

		MaxHeapify(H, i, 0 , comp1 , atrib1);
	}
}
//Functia partitioneaza un sir dat. Se alege pivotul ca fiind ultimul element al sirului, apoi in restul sirului se interschimba elementele
//mai mari din stanga pozitiei aferente pivotului cu cele mai mici din dreapta acestuia. La final, se returneaza pozitia corespunzatoare pivotului
int partitie(int* A, int low, int high,int n)
{
	Operation comp3 = P.createOperation("Quick_comp", n);
	Operation atrib3 = P.createOperation("Quick_atrib", n);
	atrib3.count();
	int pivot = A[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) 
	{
		comp3.count();
		if (A[j] <= pivot) {

			i++;
			atrib3.count(3);
			int aux = A[i];
			A[i] = A[j];
			A[j] = aux;
		}
	}
	atrib3.count();
	int aux1 = A[i + 1];
	A[i + 1] = A[high];
	A[high] = aux1;
	return (i + 1);
}
//Functia partitioneaza sirul. Se ia ca pivot un element random dintre low si high, care se pozitioneaza la finalul sirului, apoi sirul se partitioneaza
int partitie_r(int* A, int low, int high,int n)
{
	Operation comp4 = P.createOperation("Quick1_comp", n);
	Operation atrib4 = P.createOperation("Quick1_atrib", n);
	srand(time(NULL));
	int random = low + rand() % (high - low);
	atrib4.count(3);
	int aux = A[random];
	A[random] = A[high];
	A[high] = aux;
	return partitie(A, low, high,n);
}
int partitie_mij(int* A, int low, int high, int n)
{
	Operation comp5 = P.createOperation("Quick2_comp", n);
	Operation atrib5 = P.createOperation("Quick2_atrib", n);
	int mij = (low + high) / 2;
	atrib5.count(3);
	int aux = A[mij];
	A[mij] = A[high];
	A[high] = aux;
	return partitie(A, low, high, n);
}
//Functia sorteaza recursiv un sir.Se partitionaza dupa un pivot random prin metoda descrisa mai sus, apoi se repeta procedura pentru
//subsirurile obtinute in stanga, respectiv dreapta pivotului.Pentru un set de n valori oarecare algoritmul efectuează O(nlogn) comparații,
//dar în cazul cel mai nefavorabil(sir ordonat crescator sau descrescator) se efectuează O(n^2) comparații.
void QuickSort_r(int* A, int low, int high,int n)
{
	if (low < high) {
		int pi = partitie_r(A, low, high,n);
		QuickSort_r(A, low, pi - 1,n);
		QuickSort_r(A, pi + 1, high,n);
	}
}
//QuickSort cu pivotul ales ultimul element
void QuickSort(int* A, int low, int high, int n)
{
	if (low < high) {
		int pi = partitie(A, low, high, n);
		QuickSort(A, low, pi - 1, n);
		QuickSort(A, pi + 1, high, n);
	}
}
//QuickSort cu pivotul ales elementul din mijloc
void QuickSort_mij(int* A, int low, int high, int n)
{
	if (low < high) {
		int pi = partitie_mij(A, low, high, n);
		QuickSort_mij(A, low, pi - 1, n);
		QuickSort_mij(A, pi + 1, high, n);
	}
}
//Functia returneaza al k-lea cel mai mic element al sirului. Daca k nu este cuprins intre low si high se va returna -1. In caz contrar, se
//va compara pivotul cu k.Daca sunt egale, se va retuna pivotul. Altfel, k-ul se va compara cu acesta. Daca este mai mic, se va relua
//cautarea in subsirul stang.Altfel, in subsitul drept. Datorita faptului ca se apeleaza recursiv doar un subsir, complexitatea  in mediul
//statistic se reduce de la O(nlogn) la O(n). Pentru worst case avem complexitatea O(n^2)
int QuickSelect(int* A, int low, int high, int k,int n)
{
	if (k > 0 && k <= high - low + 1) 
	{ 
		int index = partitie_r(A, low, high,n);
		if (index - low + 1 == k)
			return A[index];
		else
			if (index - low + 1 > k)
				return QuickSelect(A, low, index - 1, k,n); 
			else
		return QuickSelect(A, index + 1, high, k - index + low - 1,n);
	} 
	return -1;
}

//Din grafice reiese ca metoda Quick Sort este mai rapida si mai eficienta decat Heap Sort in mediul statistic.
void MediuStatistic()
{
	int sirI[10000], sir[10000], n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		for (int i = 0; i < 5; i++)
		{
			printf("%d", n);
			FillRandomArray(sirI, n, 10, 5000, false, 0);
			memcpy(sir, sirI, n * sizeof(sirI[0]));
			HeapSort(sirI, n);
			QuickSort_r(sir,0,n-1, n);
			
		}
	}
	P.divideValues("Heap_atrib", 5);
	P.divideValues("Heap_comp", 5);
	P.addSeries("HeapSortMediuStatistic", "Heap_atrib", "Heap_comp");

	P.divideValues("Quick_comp", 5);
	P.divideValues("Quick_atrib", 5);
	P.divideValues("Quick1_comp", 5);
	P.divideValues("Quick1_atrib", 5);
	P.addSeries("QuickAtrib", "Quick_atrib", "Quick1_atrib");
	P.addSeries("QuickComp", "Quick_comp", "Quick1_comp");
	P.addSeries("QuickSortMediuStatistic", "QuickAtrib", "QuickComp");

	P.createGroup("Quick&Heap.MediuStatistic", "QuickSortMediuStatistic", "HeapSortMediuStatistic");

	P.showReport();
}
//Pentru best case ar trebui sa se genereze un sir,iar ca pivot sa se ia mereu mijlocul sirului, apoi mijlocul subsirului obtinut dupa partitionare
//si tot asa pana sirul este complet sortat, complexitatea apropiindu-se de cea average O(n log n)
void BestCase()
{
	int sir[10000], n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("%d", n);
		FillRandomArray(sir, n, 10, 50000, false, 0);
		QuickSort_mij(sir, 0, n - 1, n);
	}
	P.addSeries("QuickAtribb", "Quick_atrib", "Quick2_atrib");
	P.addSeries("QuickCompp", "Quick_comp", "Quick2_comp");
	P.createGroup("QuickSortBestCase", "QuickAtribb", "QuickCompp");

	P.showReport();
}
//Pentru worst case avem sirul crescator sau descrescator, cand se efectuează O(n^2) comparații, alegandu-se mereu cel mai mare sau cel mai mic element
//(metoda alegerii ultimului element ca pivot)
void WorstCase()
{
	int sir[10000], n;
	for (n = 100; n <= 10000; n = n + 100)
	{
		printf("%d", n);
		FillRandomArray(sir, n, 10, 50000, false, 2);
		QuickSort(sir, 0, n - 1, n);
	}
	P.createGroup("QuickSortWorstCase", "Quick_atrib", "Quick_comp");

	P.showReport();
}

int main()
{
	int n, A[11],H[11],a,k;
	printf("Dati numarul de elemente pentru sortari: ");
	scanf_s("%d", &n);
	citire(H, n);
	HeapSort(H, n);
	printf("HeapSort: ");
	afisare(H, n);
	citire(A, n);
	QuickSort_r(A, 0, n - 1,n);
	printf("QuickSort: ");
	afisare(A, n);
	printf("\nDati al catelea cel mai mic numar il doriti: ");
	scanf_s("%d", &k);
	a=QuickSelect(A,0,n-1,k,n);
	printf("Al %d-lea cel mai mic numar este %d.",k, a);
	/*MediuStatistic();
	BestCase();
	WorstCase();*/
	return 0;
}
