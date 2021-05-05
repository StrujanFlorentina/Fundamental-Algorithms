#include<stdio.h>
#include<stdlib.h>
typedef struct parinte
{
	int key;
	int nrFii;
	int Fii[10];
}Parinte;
void citireSirParinti(int* A,int n)
{
	for (int i = 1; i <= n; i++)
	{
		scanf_s("%d", &A[i]);
	}
}
void afisareSirParinti(int* A,int n)
{
	printf("\nVectorul: ");
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}
/*int nivel(int* A, int n, int i)
{
	int count=0,gasit=0 ;
	i--;
	while (gasit==0)
	{
		if (A[i] == -1)
			gasit = 1;
		else
		{
			count++;
			i = A[i]-1;
		}
	}
	return count;
}*/
void PrettyPrint1(int* A, int n, int parinte, int nivel)
{
	for (int i = 1; i <= nivel; i++)
	{
		printf("    ");
	}
	printf("%d", parinte);
	printf("\n");
	for (int i = 1; i <= n; i++)
	{
		if (A[i] == parinte)
			PrettyPrint1(A, n, i, nivel + 1);
	}

}
void R1()
{
	int A[10];
	int n;
	printf("Dati nr de noduri: ");
	scanf_s("%d", &n);
	printf("\nDati parintii nodurilor si -1 pentru radacina: \n");
	citireSirParinti(A, n);
	afisareSirParinti(A, n);
	int radacina;
	for (int i = 0; i < n; i++)
	{
		if (A[i] == -1)
			radacina = i;
	}
	printf("\nPretty print: \n");
	PrettyPrint1(A, n, radacina, 0);
}
void initializare(Parinte* P, int n)
{
	for (int i = 0; i < n; i++)
	{
		P[i].nrFii = 0;
		P[i].key = 0;
	}
}
void afisare(Parinte* P, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nParintele %d cu cei %d fii: ", P[i].key, P[i].nrFii+1);
		for (int j = 0; j <= P[i].nrFii; j++)
			printf("%d ", P[i].Fii[j]);
	}
}
int inserareParinte(int* A, Parinte* P, int n)
{
	int poz = 0,N=0,i=1;
	while (i < n)
	{
		int gasit = 0;
		for (poz = 0; poz <= n; poz++)
		{
			if (gasit == 0)
			{
				if (P[poz].key == A[i])
				{
					P[poz].nrFii = P[poz].nrFii + 1;
					P[poz].Fii[P[poz].nrFii] = i;
					gasit = 1;
				}
				else
					if (P[poz].key == 0)
					{
						gasit = 1;
						N++;
						P[poz].key = A[i];
						P[poz].Fii[P[poz].nrFii] = i;
					}
			}
		}
		i++;
	}
	return N;
}
void PrettyPrint2(Parinte* P, int N, int index, int nivel)
{
	int a;
	for (int i = 1; i <= nivel; i++)
	{
		printf("    ");
	}
	for (int i = 0; i < P[index].nrFii; i++)
	{
		printf("%d", P[index].Fii[i]);
		printf("\n");
		for (int j = 0; j < N; j++)
		{
			if (P[j].key == P[index].Fii[i])
			{
				a = j;
				PrettyPrint2(P, N, a, nivel + 1);
			}
		}

		/*for (int j = 0; j < N; j++)
		{
			if (P[j].key == P[index].Fii[0])
				a = j;
		}
		if (P[index].Fii[0] == NULL)
			printf("%d\n", P[index].key);
		else
			PrettyPrint2(P, N, a, nivel + 1);*/

	}
}
void T1()
{
	int A[] = { 0,2,7,5,2,7,7,-1,5,2 };
	int n = sizeof(A) / sizeof(int), index;
	Parinte* P = (Parinte*)malloc(n * sizeof(Parinte));
	initializare(P, n);
	int N = inserareParinte(A, P, n); // Se insereaza parintii, dar se si returneaza numarul de parinti adaugati
	printf("\nS-au adaugat %d parinti", N);
	afisare(P, N);
	for (int i = 0; i <= N; i++)
	{
		if (P[i].key = -1)
		{
			index = i-1;
		}
	}
	printf("\nPretty print: \n");
	PrettyPrint2(P, N, index , 0);
}
int main()
{
	R1();
	T1();
	return 0;
}
