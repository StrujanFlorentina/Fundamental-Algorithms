/*Strujan Florentina, seria B, grupa 302210
Căutarea în tabele de dispersie. Adresare deschisa, verificare pătratică*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Profiler.h"
//Am definit o structura pentru celulele tabelei
typedef struct cell
{
	int key;
	int status;
} Celula;
//Statusul tabelei 
enum { LIBER, OCUPAT };
// functia pentru mod N
int hPrim(int K, int N)
{
	return K % N;
}
//Verificarea polinomiala
int hFunction(int K, int N, int i)
{
	return (hPrim(K, N) + i + i * i) % N;
}
//Initializam fiecare celula a tabelei cu LIBER
void initializare(Celula* T, int N)
{
	for (int i = 0; i < N; i++)
	{
		T[i].status = LIBER;
	}
}
//Afisarea tabelei. Daca statusul este LIBER, se va afisa -- neexistand valori 
void afisare(Celula* T, int N)
{
	printf("\n\nTabela de dispersie: \n");
	for (int i = 0; i < N; i++)
	{
		if (T[i].status == OCUPAT)
			printf("T[%d]=%d\n", i, T[i]);
		else
			printf("T[%d]=--\n", i);
	}
}
//Functia insereaza elemente in tabela de dispersie. Daca statusul este LIBER, se va insera in celula respectiva elementul iar 
//statusul se va modifica la OCUPAT. Daca nu, se va incrementa i-ul si se va reapela hFunction pentru gasirea unui alt posibil loc liber
void inserare(int K, Celula* T, int N)
{
	int i = 0;
	int h;
	int gasit = 0;
	while (i < N && gasit == 0)
	{
		h = hFunction(K, N, i);
		if (T[h].status == LIBER)
		{
			T[h].status = OCUPAT;
			T[h].key = K;
			gasit = 1;
		}
		else
			i++;
	}
}
//Functia cauta elementul dorit in tabela de dispersie. Daca primul loc unde ar trebui sa fie valoarea are statusul LIBER sau se ajunge
//la i-ul mai mare decat numarul de elemente al tabelei, se va returna 0(fals) si se fa afisa mesajul corespunzator. In caz contrar
//se va verifica daca valoarea elementului cautat corespunde celui gasit.Daca da, se returneaza pozitia din tabela si se afiseaza 
//mesajul corespunzator. Daca nu, se trece la urmatoarea pozitie gasit cu hFunction
int cautare1(int K, Celula* T, int N)
{
	int i = 0;
	int h;
	int gasit = 0;
	while (i < N && gasit == 0)
	{
		h = hFunction(K, N, i);
		if (T[h].status == LIBER)
		{
			printf("Elementul %d nu exista in tabela.\n", K);
			return 0;
		}
		else
		{
			if (T[h].key == K)
			{
				printf("Elementul %d gasit la pozitia %d.\n", K, h);
				gasit = 1;
				return h;
			}
		}
		i++;
	}
}
//Functia de cautare fara mesaje, pentru functia de stergere
int cautare(int K, Celula* T, int N)
{
	int i = 0;
	int h;
	int gasit = 0;
	while (i < N && gasit == 0)
	{
		h = hFunction(K, N, i);
		if (T[h].status == LIBER)
		{
			return 0;
		}
		else
		{
			if (T[h].key == K)
			{
				gasit = 1;
				return h;
			}
		}
		i++;
	}
	if(gasit==0)
		return 0;
}
//Functia de cautare ce returneaza numarul operatiilor efectuate (numarul celulelor acesate)
int nrOperatii(int K, Celula* T, int N)
{
	int i = 0;
	int h;
	int gasit = 0;
	while (i < N && gasit == 0)
	{
		h = hFunction(K, N, i);
		if (T[h].status == LIBER)
		{
			return i;
		}
		else
		{
			if (T[h].key == K)
			{
				gasit = 1;
				return i;
			}
		}
		i++;
	}
	if (gasit == 0)
		return i;
}
//Functia sterge elementul dorit.Se cauta in tabela elementul. Daca este gasit, statusul lui din tabela se modifica la LIBER. Daca nu,
//se trece la urmatoarea pozitie posibila a elementului si se verifica. Daca se ajunge la i egal cu numarul de elemente al tabelei
//sau primul element la care ar trebui sa fie are statusul LIBER se va afisa mesajul corespunzator.
void stergere(int K, Celula* T, int N)
{
	int i = 0, h, gasit = 0, poz;
	while (i < N && gasit == 0)
	{
		h = hFunction(K, N, i);
		poz = cautare(K, T, N);
		if (T[h].key == T[poz].key)
		{
			T[h].status = LIBER;
			gasit = 1;
		}
		else
			i++;
	}
	if (gasit == 0)
		printf("Elementul nu exista in tabela.");
}
//In aceasta functie am verificat functiile de inserare, cautare si stergere cu o dimensiune a tabelei si elemente date.
void dummy()
{
	printf("\nDummy:");
	int N = 10,a,b,caut;
	Celula* T = (Celula*)malloc(N * sizeof(Celula));
	initializare(T, N);
	int v[] = { 19, 36, 5, 21, 4, 26, 14, 17 };
	for (int i = 0; i < sizeof(v) / sizeof(int); i++)
		inserare(v[i], T, N);
	afisare(T, N);
	printf("Dati valoarea elementului ce doriti sa fie cautat: ");
	scanf_s("%d", &a);
	caut=cautare1(a, T, N);
	printf("\nDati valoarea elementului ce doriti sa fie sters: ");
	scanf_s("%d", &b);
	stergere(b, T, N);
	afisare(T, N);
	printf("\n");
}
//Functia demo pentru factor de umplere 95%
void demo()
{
	printf("\nDemo pentru factor de umplere 0.95");
	float alfa = 0.95;
	int N = 101, n = alfa*N, v[100];
	Celula* T = (Celula*)malloc(N * sizeof(Celula));
	initializare(T, N);
	FillRandomArray(v, n, 0, 500, false, 0);
	for (int i = 0; i < n; i++)
	{
		inserare(v[i], T, N);
	}
	afisare(T, N);
	printf("\n");
}
//Functia afseaza tabelul de cautare cu valorile efortului maxim pentru gasirea unui element in cazul in care exista sau nu in tabela de dispersie
//si cu media efortului depus in fiecare caz. Am umplut vectorii cu FillRandomArray, elementele din primul punandu-le in tabela de dispersie
//pentru gasirea sigura a elementelor in timpul testarii, celalalt continand elemente din afara intervalului elementelot primului vector
void tabelCautare(float alfa)
{
	int N = 10007, v[11000], vfara[2000], n = alfa * N, maxFound=0, maxNFound=0;
	float avgFound=0, avgNFound=0;
	FillRandomArray(v, n, 1, 30000, 0, 0);
	Celula* T = (Celula*)malloc(N * sizeof(Celula));
	initializare(T, N);
	for (int i = 0; i < n; i++)
		inserare(v[i], T, N);
	FillRandomArray(vfara, 1500, 30001, 50000, 0, 0);
	for (int j = 0; j < 3000; j++)
	{
		if (j < 1500)
		{
			if (cautare(v[j+5000], T, N) > 0)
			{
				avgFound = avgFound + nrOperatii(v[j+5000], T, N);
				if (maxFound < nrOperatii(v[j+5000], T, N))
					maxFound = nrOperatii(v[j+5000], T, N);
			}
		}
		else
		{
			if (cautare(vfara[3000-j+1], T, N) == 0)
			{
				avgNFound = avgNFound + nrOperatii(vfara[3000-j], T, N);
				if (maxNFound < nrOperatii(vfara[3000-j], T, N))
					maxNFound = nrOperatii(vfara[3000-j], T, N);
			}
		}
	}
	avgFound = avgFound / 1500;
	avgNFound = avgNFound / 1500;
	printf("\nFactor de umplere %.2f \n%f | %d | %f | %d\n", alfa, avgFound, maxFound, avgNFound, maxNFound);
}
int main()
{
	dummy();
	demo();
	printf("Tbelul de cautare:\navg found | max found | avg not foud | max not found\n");
	tabelCautare(0.80);
	tabelCautare(0.85);
	tabelCautare(0.90);
	tabelCautare(0.95);
	tabelCautare(0.99);
	return 0;
}