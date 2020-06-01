#ifndef _CERINTA1_H
#define _CERINTA1_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listNode
{
	char **table;
	struct gameTree *child;
	struct listNode *next;
} listNode;

typedef struct gameTree
{
	int depth;
	char playerToMove;
	struct listNode *head;
} gameTree;

gameTree *readTable(char *inFile, int *lines, int *rows);
void generateNodes(gameTree *tree, listNode *list, int lines, int rows);
void display(FILE *outFile, gameTree *tree, int n, int m);
int isOver(char **table, int lines, int rows, char player);
void destroyList(listNode *head, int lines);
void destroyTree(gameTree *tree, int lines);

#endif