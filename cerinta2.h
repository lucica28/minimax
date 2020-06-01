#ifndef _CERINTA2_H
#define _CERINTA2_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct  Tree
{
	int val;
	int depth;
	struct Tree *lastChild;
	struct Tree *child;
	struct Tree *sibling;
} Tree;

typedef struct Node
{
    Tree *value;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

void initQueue(Queue **q);
int isEmptyQueue(Queue *q);
void enqueue(Queue *q, Tree *x);
void dequeue(Queue *q);
void clear(Queue *q);
Tree *front(Queue *q);

Tree *createNode(int value, int depth);
void insert(Tree *parent, Tree *child);
void Display(FILE *outFile, Tree *tree);
int minEval(Tree *tree);
int maxEval(Tree *tree);
void destroy(Tree *tree);
int maxEvalPrune(Tree *tree, int alfa, int beta);
int minEvalPrune(Tree *tree, int alfa, int beta);

#endif