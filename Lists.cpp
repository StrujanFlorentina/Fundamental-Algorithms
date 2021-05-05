//Strujan Florentina, grupa 302210, seria B
//Generarea a k liste ordonate. Interclasarea a doua liste ordonate generate aleator
#include<iostream>
#include<stdlib.h>
#include "Profiler.h"

typedef struct node
{
	int key;
	struct node* next;
}NodeT;

void printList(NodeT* first)
{
	while (first != NULL)
	{
		printf("%d ", first->key);
		first = first->next;
	}
	printf("\n");
}

void insertLast(NodeT** first, NodeT** last, int value)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = value;
	p->next = NULL;
	if ((*first) == NULL)
	{
		(*first) = p;
		(*last) = p;
	}
	else
	{
		(*last)->next = p;
		(*last) = p;
	}
}

void generateKLists(NodeT** first, NodeT** last, int k, int n)
{

	int* a = (int*)calloc((n / k), sizeof(int));
	for (int i = 0; i < k; i++)
	{
		first[i] = NULL;
		last[i] = NULL;
		FillRandomArray(a, n / k, 1, 100, false, 1);
		for (int j = 0; j < n / k; j++)
		{
			insertLast(&first[i], &last[i], a[j]);
		}
	}
}

NodeT* mergeTwoLists(NodeT* a, NodeT* b)
{
	NodeT* first = NULL;
	NodeT* last = NULL;
	while (a != NULL && b != NULL) {
		if (a->key < b->key) {
			insertLast(&first, &last, a->key);
			a = a->next;
		}
		else {
			insertLast(&first, &last, b->key);
			b = b->next;
		}
	}
	while (a != NULL) {
		insertLast(&first, &last, a->key);
		a = a->next;
	}
	while (b != NULL) {
		insertLast(&first, &last, b->key);
		b = b->next;
	}
	return first;
}

int main()
{
	int n,k;
	NodeT** first = (NodeT**)calloc(2, sizeof(NodeT*));
	NodeT** last = (NodeT**)calloc(2, sizeof(NodeT*));
	printf("\nIntroduceti numarul total de elemente ce vor fi interclasate: ");
	scanf_s("%d", &n);
	printf("\nIntroduceti numarul de liste ce vreti sa fie generate: ");
	scanf_s("%d", &k);
	generateKLists(first, last, k, n);
	for (int i = 0; i < k; i++)
	{
		printf("Lista numarul %d este : ", i);
		printList(first[i]);
	}
	printf("Interclasarea primelor doua liste: ");
	printList(mergeTwoLists(first[0], first[1]));
}