//Strujan Florentina, grupa 302210
//BFS

#include <stdlib.h>
#include <stdio.h>
enum { nevizitat, vizitat };

struct nod
{
	int key;
	struct nod* next;
};
struct graf {
	int noduri;
	int muchii;
	nod* v[999];
	nod* first = NULL;
	nod* last = NULL;
};

void inserare( nod**first, int key)
{
	nod* p = (nod*)malloc(sizeof(struct nod));
	p->key = key;
	p->next = NULL;
	nod* q = *first;
	if (*first == NULL)
		*first = p;
	else
	{
		while (q->next != NULL)
		{
			q = q->next;

		}
		q->next = p;
	}
}

void enqueue(nod** first, nod** last, int key)
{
	nod* p = (nod*)malloc(sizeof(struct nod));
	p->key = key;
	p->next = NULL;
	if (*first == NULL)
	{
		*first = p;
		*last = p;
	}
	else
	{
		(*last)->next = p;
		*last = p;
	}
}

int dequeue(nod** first)
{
	int x;
	if (*first != NULL)
	{
		nod* p = *first;
		*first = (*first)->next;
		p->next = NULL;
		x = p->key;
		free(p);
	}
	return x;
}

void afis_adiacenta1(graf* G)
{
	int i = 0;
	printf("Lista de adiacenta:\n");
	while (i < G->noduri)
	{
		printf("%d:", i);
		while (G->v[i] != NULL)
		{
			printf("%d ", G->v[i]->key);
			G->v[i] = G->v[i]->next;
		}
		printf("\n");
		i++;
	}
}

void bfs(int nodSursa, graf* G,int*b)
{
	int*viz = (int*)malloc(G->noduri*sizeof(int));
	for (int i = 0; i < G->noduri; i++)
		viz[i] = nevizitat;
	enqueue(&G->first, &G->last, nodSursa);
	viz[nodSursa] = vizitat;
	printf("\nBFS: %d ", nodSursa);
	b[nodSursa] = -1;
	while (G->first != NULL)
	{
		int a = dequeue(&G->first);
		while (G->v[a] != NULL)
		{
			if (viz[G->v[a]->key] == nevizitat)
			{
				b[G->v[a]->key] = a;
				viz[G->v[a]->key] = vizitat;
				printf("%d ", G->v[a]->key);
				enqueue(&G->first, &G->last, G->v[a]->key);
			}
			G->v[a] =G->v[a]->next;
		}
	}
}
void prettyprint(graf* G, int start, int nivel)
{
	for (int i = 0; i < nivel; i++)
		printf("\t");
	printf("%d", start);
	printf("\n");
	for(int j=0;j<G->noduri;j++)
		if (G->v[j]->key == start)
			prettyprint(G, j, nivel+1);
}

int main()
{
	int noduri = 4, muchii = 6;
	int *a = (int*)malloc(noduri*sizeof(int));
	graf* G = (graf*)malloc(sizeof(graf));
	G->noduri = noduri;
	G->muchii = muchii;

	inserare(&G->v[0], 2);
	inserare(&G->v[2], 0);
	inserare(&G->v[0], 1);
	inserare(&G->v[2], 3);
	inserare(&G->v[1], 2);
	inserare(&G->v[3], 3);

	afis_adiacenta1(G);

	bfs(2, G, a);

	int start = 0;
	for (int i = 0; i <= noduri; i++)
	{
		if (a[i] == -1)
		{
			start = i;
		}
	}
	printf( "\n\nPretty print:\n");
	prettyprint(G, start, 0);
}
