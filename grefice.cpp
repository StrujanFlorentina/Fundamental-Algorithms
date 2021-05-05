/*Strujan Florentina, seria B, grupa 302210
Statistici dinamice de ordine*/
#include<stdio.h> 
#include<stdlib.h> 
#include "Profiler.h"
Profiler P("Tree");
//Nodul unui arbore
typedef struct node
{
	int key;
	int size;
	struct node* left;
	struct node* right;
}TNode;
//rank-ul unui nod
int size(TNode* A) {
	if (A != NULL)
		return A->size;
	else
		return 0;
}
//Functia de initializare a unui nou nod
TNode* new_node(int data, int size)
{
	TNode* nod = (TNode*)malloc(sizeof(TNode));
	nod->key = data;
	nod->size = size;
	nod->left = NULL;
	nod->right = NULL;
	return nod;
}
//Constructia unui arbore perfect echilibrat. Dintr-un sir dat se construieste un arbore. Se alege mijlocul sirului ( subsirului) ca radacina
// iar rangul ca fiind diferenta dintre prima pozitie a sirului(subsirului) - ultima +1. Se repeta pasii pentru subsirul din stanga mijlocului si cel din
//dreapta lui pana la folosirea fiecarul element.
TNode* BuildPBT(int* A, int low, int high)
{
	int mij;
	TNode* radacina;
	if (low > high)
		return NULL;
	else
	{
		mij = (low + high) / 2;
		radacina = new_node(A[mij], high - low + 1);
		radacina->left = BuildPBT(A, low, mij - 1);
		radacina->right = BuildPBT(A, mij + 1, high);
	}
	return radacina;
}
//Functia de afisare frumoasa
void afisare(TNode* nod, int nivel)
{
	if (nod == NULL)
	{
		for (int i = 0; i < nivel; i++)
			printf("\t ");
		puts("null ");
	}
	else
	{
		afisare(nod->right, nivel + 1);
		for (int i = 0; i < nivel; i++)
			printf("\t ");
		printf("(%d)- %d \n", nod->key, nod->size);
		afisare(nod->left, nivel + 1);
	}
}
//Functia de selectie al celui de i-lea cel mai mic termen. Daca suma nodurilor din subarborele stang este egal cu i-ul dat, se va returna nodul respectiv.
//Daca i-ul e mai mic decat suma, se va cauta in subarborele stang nodului. Daca e mai mare, in subarborele drept, actualizandu-se i-ul cu i-r pentru
//a cauta al i-r lea nod din subarborele drept 
TNode* OsSelect(TNode* A, int i, int n)
{
	Operation op1 = P.createOperation("TreeSel", n);
	op1.count();
	if (A != NULL) {
		int r = size(A->left) + 1;
		op1.count();
		if (i == r)
			return A;
		else
		{
			op1.count();
			if (i < r)
				return OsSelect(A->left, i, n);
			else
				return OsSelect(A->right, i - r, n);
		}
	}
}

TNode* parinteNod(TNode* radacina, TNode* nod,Operation op2)
{
	if (radacina == NULL || nod == NULL)
		return NULL;
	else
	{
		op2.count();
		if (radacina->left == nod && radacina->right == NULL)
		{
			op2.count();
			radacina->size = radacina->size - 1;
			return radacina;
		}
		else {
			op2.count(2);
			if (radacina->right == nod && radacina->left == NULL)
			{
				op2.count();
				radacina->size = radacina->size - 1;
				return radacina;
			}
			else
			{
				op2.count();
				if (size(radacina) < size(nod))
				{
					op2.count();

					radacina->size = radacina->size - 1;
					return parinteNod(radacina->right, nod,op2);
				}
				else
				{
					op2.count();
					radacina->size = radacina->size - 1;
					return parinteNod(radacina->left, nod,op2);
				}
			}
		}
		}
}
int rank(TNode* nod) {
	if (nod == NULL)
		return 0;
	else
		return 1 + rank(nod->left) + rank(nod->right);
}
void refacereRank(TNode* A) {
	if (A != NULL)
		A->size = rank(A);
	if (A->left != NULL)
		refacereRank(A->left);
	if (A->right != NULL)
		refacereRank(A->right);
}
void OsDelete(TNode* A, int i, int n)
{
	Operation op2= P.createOperation("TreeDel", n);
	TNode* a = OsSelect(A, i, n);
	TNode* p;
	if (a != NULL) {
		op2.count(2);
		if (a->left == NULL && a->right == NULL)
		{
			p = parinteNod(A, a,op2);
			op2.count();
			if (a == p->left)
			{
				op2.count();
				p->left = NULL;
			}
			else
			{
				op2.count();
				p->right = NULL;
			}
			free(a);
		}
		else {
			op2.count();
			if (a->left == NULL && a->right != NULL)
			{
				op2.count(2);
				a->key = a->right->key;
				a->right = NULL;
				free(a->right);
			}
			else {
				op2.count(2);
				if (a->left != NULL && a->right == NULL)
				{
					op2.count(2);
					a->key = a->left->key;
					a->left = NULL;
					free(a->left);
				}
				else
				{
					TNode* b = OsSelect(A, i - 1, n);
					op2.count();
					a->key = b->key;
					p = parinteNod(A, b,op2);
					if (p == NULL)
						return;
					else
					{
						op2.count();
						if (b == p->right)
						{
							op2.count();
							p->right = NULL;
						}
						else
						{
							p->left = NULL;
							op2.count();
						}
						free(b);
					}
				}
			}
		}
	}
}

void demo()
{
	TNode* a, * aa;
	printf("Demo pentru arborele creat din 11 elemente cu selectia si stergerea a 3 elemente random\n");
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int n = sizeof(A) / sizeof(A[0]);
	TNode* radacina = BuildPBT(A, 0, n - 1);
	afisare(radacina, 0);
	for (int i = 0; i < 3; i++)
	{
		int index = rand() % (n - 1);
		a = OsSelect(radacina, index, n);
		printf("al %d lea element--%d\n", index, a->key);
		OsDelete(radacina, index, n);
	}
	refacereRank(radacina);
	afisare(radacina, 0);


}
int main()
{
	demo();
	int n, index, size;
	int A[10000];
	node* radacina, * sel;
	for (n = 100; n <= 10000; n = n + 100)
	{
		for (int i = 0; i < 5; i++)
		{
			FillRandomArray(A, n, 0, 100000, 0, 1);
			radacina = BuildPBT(A, 0, n - 1);
			size = n;
			for (int j = 0; j < n; j++)
			{
				index = rand() % (size - 1);
				sel = OsSelect(radacina, index, n);
				OsDelete(radacina, sel->key, n);
			}
		}
	}
	P.divideValues("TreeSel", 5);
	P.divideValues("TreeDel", 5);
	P.addSeries("TreeDelFin", "TreeSel", "TreeDel");
	P.createGroup("Tree", "TreeSel", "TreeDelFin");
	P.showReport();
	return 0;
}
