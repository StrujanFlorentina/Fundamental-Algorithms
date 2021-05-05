#include<stdlib.h>
#include<stdio.h>


int time = 0;
typedef struct nodetype
{
	int key;
	struct nodetype* next;
}nod;

enum { white = 1, grey = 2, black = 3 }color;


typedef struct g
{
	int noduri;
	int* parinte;
	int* descoperire;
	int* finalizare;
	int* color;
	nod** liste;

}graf;

nod* newNode(int givenkey)
{
	nod* p = (nod*)malloc(sizeof(nod));
	p->key = givenkey;
	p->next = NULL;
	return p;
}

graf* newGraph(int nr_noduri)
{
	graf* g = (graf*)malloc(sizeof(graf));
	g->noduri = nr_noduri;
	g->parinte = (int*)calloc(nr_noduri, sizeof(int));
	g->color = (int*)calloc(nr_noduri, sizeof(int));
	g->liste = (nod**)malloc(nr_noduri * sizeof(nod*));
	g->descoperire = (int*)calloc(nr_noduri, sizeof(int));
	g->finalizare = (int*)calloc(nr_noduri, sizeof(int));

	return g;
}

void push(nod** first, int givenkey)
{
	nod* p = newNode(givenkey);
	if ((*first) == NULL)
	{
		(*first) = p;
	}
	else
	{
		p->next = (*first);
		(*first) = p;
	}
}

int pop(nod** first)
{
	nod* aux = (nod*)malloc(sizeof(nod));
	int k;
	if ((*first) != NULL)
	{
		aux = (*first);
		(*first) = (*first)->next;
		k = aux->key;
		free(aux);
	}
	return k;
}


void printStack(nod* first)
{
	while (first != NULL)
	{
		printf("%d ", first->key);
		first = first->next;
	}
	printf("\n");
}
void citesteGraf(graf* G, int nr_noduri, int nr_muchii)
{
	G->noduri = nr_noduri;
	G->liste = (nod**)calloc(G->noduri, sizeof(nod*));

	for (int i = 0; i < nr_muchii; i++)
	{
		G->liste[i] = NULL;
		int x, y;
		printf("\nx=");
		scanf_s("%d", &x);
		printf("y=");
		scanf_s("%d", &y);
		push(&G->liste[x], y);
		push(&G->liste[y], x);
	}

	for (int i = 0; i < G->noduri; i++)
	{
		G->parinte[i] = -1;
		G->descoperire[i] = 0;
		G->finalizare[i] = 0;
		G->color[i] = white;
	}

}

void dfs_visit(graf* G, int nodSursa, int time)
{
	time = time + 1;
	G->color[nodSursa] = grey;
	G->descoperire[nodSursa] = time;
	nod* p = G->liste[nodSursa];
	printf("%d ", nodSursa);
	while (p != NULL)
	{
		if (G->color[p->key] == white)
		{
			G->parinte[p->key] = nodSursa;
			dfs_visit(G, p->key, time);
		}
		p = p->next;
	}
	G->color[nodSursa] = black;
	time = time + 1;
	G->finalizare[nodSursa] = time;

}

void dfs(graf* G, int time)
{
	time = 0;
	for (int i = 0; i < G->noduri; i++)
	{
		if (G->color[i] == white)

		{
			dfs_visit(G, i, time);
		}
	}
}


void demo()
{
	int n;
	int	time = 0;
	printf("\nIntroduceti numarul nodurilor:\n");
	scanf_s("%d", &n);
	int m;
	printf("\nIntroduceti numarul muchiilor:\n");
	scanf_s("%d", &m);
	graf* G = newGraph(n);
	citesteGraf(G, n, m);
	int nodSursa;
	printf("\nIntroduceti nodul de la care pornim:\n");
	scanf_s("%d", &nodSursa);
	dfs_visit(G, nodSursa, time);
	dfs(G, time);
	
}

int main()
{
	demo();
	return 0;
}