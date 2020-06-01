#include "cerinta2.h"

void initQueue(Queue **q)
{
	(*q) = (Queue*) malloc(sizeof(Queue));
	(*q)->front = NULL;
	(*q)->rear = NULL;
}

int isEmptyQueue(Queue *q)
{
    if(q->front) return 1;
    return 0;
}

void enqueue(Queue *q, Tree *x)
{
	if(!x) return;
	Node *new = malloc(sizeof(Node));
	new->value = x;
	new->next = NULL;
	if(!isEmptyQueue(q))
	{
		q->front = new;
		q->rear = new;
		return;	
	}
	q->rear->next = new;
	q->rear = new;
}

void dequeue(Queue *q)
{
	Node *aux = q->front;
	if(!isEmptyQueue(q)) return;
	if(q->front == q->rear)
	{
		q->front = NULL;
		q->rear = NULL;
		free(aux);
		return;
	}
	q->front = q->front->next;
	free(aux);
}

Tree *front(Queue *q)
{
	if(!q) return NULL;
    return q->front->value;
}

void clear(Queue *q)
{
	if(!isEmptyQueue(q)) return;
	while(isEmptyQueue(q))
	{
		dequeue(q);
	}
}


int len(Tree *tree)
{
	if(!tree) return 0;
	int len = 0;
	while(tree)
	{
		len++;
		tree = tree->sibling;
	}
	return len;
}

Tree *createNode(int value, int depth)
{
	Tree *newTree;
	newTree = malloc(sizeof(Tree));
	newTree->val = value;
	newTree->depth = depth;
	newTree->child = NULL;
	newTree->sibling = NULL;
	newTree->lastChild = NULL;
	return newTree;
}

void insert(Tree *parent, Tree *child)
{
	Tree *head = parent->child;
	if(!head)
	{
		parent->child = child;
		parent->lastChild = child;
		return;
	}
	parent->lastChild->sibling = child;
	parent->lastChild = child;
}

int minEval(Tree *tree)
{
	int min = 999999;
	while(tree)
	{
		if(tree->val == 0 && tree->child != NULL) tree->val = maxEval(tree->child);
		if(min > tree->val) min = tree->val;
		tree = tree->sibling;
	}
	return min;
}

int maxEval(Tree *tree)
{
	int max = -999999;
	while(tree)
	{
		if(tree->val == 0 && tree->child != NULL) tree->val = minEval(tree->child);
		if(max < tree->val) max = tree->val;
		tree = tree->sibling;
	}
	return max;
}

int minEvalPrune(Tree *tree, int alfa, int beta)
{
	int min = 999999;
	while(tree)
	{
		if(tree->val == 0 && tree->child != NULL) 
			tree->val = maxEvalPrune(tree->child, alfa, beta);
		if(min > tree->val) min = tree->val;
		if(tree->val <= alfa) 
		{
			destroy(tree->sibling);
			tree->sibling = NULL; 
			return min;
		}
		if(tree->val < beta) beta = tree->val;
		tree = tree->sibling;
	}
	return min;
}

int maxEvalPrune(Tree *tree, int alfa, int beta)
{
	int max = -999999;
	while(tree)
	{
		if(tree->val == 0 && tree->child != NULL) 
			tree->val = minEvalPrune(tree->child, alfa, beta);
		if(max < tree->val) max = tree->val;
		if(tree->val >= beta) 
		{
			destroy(tree->sibling);
			tree->sibling = NULL; 
			return max;
		}
		if(tree->val > alfa) alfa = tree->val;
		tree = tree->sibling;
	}
	return max;
}

void Display(FILE *outFile, Tree *tree)
{
	if(!tree) return;
	while(tree)
	{
		//INDENT
		for(int i = 1; i < tree->depth; i++)
			fprintf(outFile, "\t");
		fprintf(outFile, "%d\n", tree->val);
		Display(outFile, tree->child);
		tree = tree->sibling;
	}
}

void destroy(Tree *tree)
{
	if(!tree) return;
	Tree *aux = tree;
	while(tree)
	{
		destroy(tree->child);
		aux = tree;
		tree = tree->sibling;
		free(aux);
	}
}
