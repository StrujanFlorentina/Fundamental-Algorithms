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
 TNode* new_node(int data,int size)
{
	TNode* nod =(TNode*)malloc(sizeof(TNode));
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
void afisare( TNode* nod,int nivel)
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
TNode* OsSelect(TNode* A, int i)
{
	if (A != NULL) {
		int r = size(A->left) + 1;
		if (i == r)
			return A;
		else
		{
			if (i < r)
				return OsSelect(A->left, i);
			else
				return OsSelect(A->right, i - r);
		}
	}
}
//Functia returneaza parintele nodului pentru a reface legaturile dupa stergere
TNode* parinteNod(TNode* radacina, TNode* nod)
{
	if (radacina == NULL||nod==NULL)
		return NULL;
	else
	{
		if (radacina->left == nod && radacina->right == NULL) 
		{
			radacina->size=radacina->size-1;
			return radacina;
		}
		else
			if (radacina->right == nod && radacina->left == NULL)
			{
				radacina->size = radacina->size - 1;
				return radacina;
			}
		else
			if (size(radacina) < size(nod))
			{
				radacina->size = radacina->size - 1;
				return parinteNod(radacina->right, nod);
			}
			else
			{
				radacina->size = radacina->size - 1;
				return parinteNod(radacina->left, nod);
			}
	}
}
int rank(TNode* nod) {
	if (nod == NULL)
		return 0;
	else
		return 1 + rank(nod->left) + rank(nod->right);
}
//Functia reface rank urile nodurilor afectate de stergere
void refacereRank(TNode* A) {
	if (A != NULL)
		A->size = rank(A);
	if (A->left != NULL)
		refacereRank(A->left);
	if (A->right != NULL)
		refacereRank(A -> right);
}
//Stergerea nodului in functie de pozitie.Daca e frunza, se face stergerea simpla, daca are doar un fiu, cheia fiului va fi copiata in nodul de sters si
//se va sterge nodul fiu. Altfel, cheia nodului care ar trebui sa fie in mod normal inaintea nodului de sters se va copia in acesta si se va sterge, 
//refacandu-se legaturile
void OsDelete(TNode* A, int i)
{
	TNode* a = OsSelect(A, i);
	TNode* p;
	if (a != NULL) {
		if (a->left == NULL && a->right == NULL)
		{
			p = parinteNod(A, a);
			if (a == p->left)
				p->left = NULL;
			else
				p->right = NULL;
			free(a);
		}
		else
			if (a->left == NULL && a->right != NULL)
			{
				a->key = a->right->key;
				a->right = NULL;
				free(a->right);
			}
			else
				if (a->left != NULL && a->right == NULL)
				{
					a->key = a->left->key;
					a->left = NULL;
					free(a->left);
				}
				else
				{
					TNode* b = OsSelect(A, i - 1);
					a->key = b->key;
					p = parinteNod(A, b);
					if (p == NULL)
						return;
					else
					{
						if (b == p->right)
							p->right = NULL;
						else
							p->left = NULL;
						free(b);
					}
				}
	}
}

void demo()
{
	TNode* a,*aa;
	printf("Demo pentru arborele creat din 11 elemente cu selectia si stergerea a 3 elemente random\n");
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int n = sizeof(A) / sizeof(A[0]);
	TNode* radacina = BuildPBT(A, 0, n - 1);
	afisare(radacina,0);
	for (int i = 1; i <= 3; i++)
	{
		int index = rand() % (n-1);
		a = OsSelect(radacina, index);
		printf("al %d lea element--%d\n", index, a->key);
		OsDelete(radacina, index);
	}
	refacereRank(radacina);
	afisare(radacina, 0);


}
int main()
{
	demo();
	return 0;
}
