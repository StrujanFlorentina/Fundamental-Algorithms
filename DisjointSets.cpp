/*Strujan Florentina, seria B, grupa 302210
Multimi disjuncte
*/

#include <stdlib.h>
#include <iostream>

typedef struct Nod{
	
	int key;
	int rank;
	Nod* parinte;
}Nod;
Nod* newNode(int val)
{
	Nod* a=(Nod*)malloc(sizeof(Nod));
	a->key = val;
	a->rank = 0;
	a->parinte = NULL;
	return a;
}
void makeSet(Nod* x)
{
	x->parinte = x;
	x->rank = 0;
}
void link(Nod* x, Nod* y)
{
	if (x->rank >= y->rank)
	{
		y->parinte = x;
		if (x->rank == y->rank)
			x->rank++;
	}
	else
		x->parinte = y;
}
Nod* findSet(Nod* x)
{
	if (x != x->parinte)
		x->parinte = findSet(x->parinte);
	return x->parinte;
}
void unionn(Nod* x, Nod* y)
{
	link(findSet(x), findSet(y));
}
void afisare(Nod** x,int n)
{
	for (int i = 1; i <= n; i++)
		printf("Elementul %d cu rank-ul %d\n", x[i]->key, x[i]->rank);
}
void demo()
{
	int n = 10;
	Nod** x = (Nod**)malloc(n*sizeof( Nod*));
	for (int i = 1; i <= n; i++)
	{
		x[i] = newNode(i);
		makeSet(x[i]);
	}
	afisare(x, n);
	unionn(x[4], x[5]);
	unionn(x[6], x[7]);
	unionn(x[5], x[6]);
	unionn(x[7], x[10]);
	afisare(x, n);
	printf("Find set pentru elementul %d : %d\n", x[6]->key, x[6]->parinte->key);
	printf("Find set pentru elementul %d : %d\n", x[10]->key, x[10]->parinte->key);
	printf("Find set pentru elementul %d : %d\n", x[1]->key, x[1]->parinte->key);
	printf("Find set pentru elementul %d : %d\n", x[4]->key, x[4]->parinte->key);
	printf("Find set pentru elementul %d : %d\n", x[7]->key, x[7]->parinte->key);
}
int main()
{
	demo();
	return 0;
}