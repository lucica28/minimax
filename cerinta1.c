#include "cerinta1.h"

gameTree *readTable(char *inFile, int *lines, int *rows)
{
	FILE *fin = fopen(inFile, "r");
	gameTree *newTree = malloc(sizeof(gameTree));
	newTree->depth = 0;
	fscanf(fin, "%d %d", &(*lines), &(*rows));
	fscanf(fin, " %c ", &newTree->playerToMove);
	if(newTree->playerToMove == 'R') newTree->playerToMove = 'B';
	else newTree->playerToMove = 'R';
	listNode *list = malloc(sizeof(listNode));
	list->table = (char**) malloc(*lines * sizeof(char*));
	for(int i = 0; i < *lines; i++)
		list->table[i] = malloc(*rows * sizeof(char));
	for(int i = 0; i < *lines; i++)
		for(int j = 0; j < *rows; j++)
			fscanf(fin, "%c ", &list->table[i][j]);
	newTree->head = list;
	list->child = NULL;
	list->next = NULL;
	fclose(fin);
	return newTree;
}

int isOver(char **table, int lines, int rows, char player)
{
	int i, j, auxI, auxJ, count;
	for(i = 0; i < lines; i++)
		for(j = 0; j < rows; j++)
		{
			if(table[i][j] == player)
			{
				count = 0; auxI = i; auxJ = j;
				while(auxI >= 0 && auxI < lines && auxJ >= 0 && auxJ < rows)
				{
					if(table[auxI++][auxJ] != player) break; 
					count++;
					if(count == 4) return 1;
				}
				count = 0; auxI = i; auxJ = j;
				while(auxI >= 0 && auxI < lines && auxJ >= 0 && auxJ < rows)
				{
					if(table[auxI][auxJ++] != player) break;
					count++;
					if(count == 4) return 1;
				}
				count = 0; auxI = i; auxJ = j;
				while(auxI >= 0 && auxI < lines && auxJ >= 0 && auxJ < rows)
				{
					if(table[auxI++][auxJ++] != player) break;
					count++;
					if(count == 4) return 1;
				}
				count = 0; auxI = i; auxJ = j;
				while(auxI >= 0 && auxI < lines && auxJ >= 0 && auxJ < rows)
				{
					if(table[auxI++][auxJ--] != player) break;
					count++;
					if(count == 4) return 1;
				}
			}
		}
	for(i = 0; i < lines; i++)
		for(j = 0; j < rows; j++)
			if(table[i][j] == '-') return 0;
	//DRAW
	return 1;
}

void generateNodes(gameTree *tree, listNode *list, int lines, int rows)
{
	if(isOver(list->table, lines, rows, 'R') || 
		isOver(list->table, lines, rows, 'B')) return;
	//New tree node
	gameTree *newTree = malloc(sizeof(gameTree));
	newTree->depth = tree->depth + 1;
	if(tree->playerToMove == 'B') newTree->playerToMove = 'R';
	else newTree->playerToMove = 'B';
	newTree->head = NULL;
	list->child = newTree;
	for(int j = rows - 1; j >= 0; j--)
		for(int i = lines - 1; i >= 0; i--)
		{
			if((i == lines - 1 && list->table[i][j] == '-') ||
				(list->table[i][j] == '-' && list->table[i + 1][j] != '-'))
			{	
				//New list element
				listNode *newList = malloc(sizeof(listNode));
				newList->table = (char**) malloc(lines * sizeof(char*));
				for(int it = 0; it < lines; it++)
					newList->table[it] = malloc(rows * sizeof(char));
				for(int it = 0; it < lines; it++)
					for(int jt = 0; jt < rows; jt++)
						newList->table[it][jt] = list->table[it][jt];
				newList->table[i][j] = newTree->playerToMove;
				newList->child = NULL;
				newList->next = newTree->head;
				newTree->head = newList;
				generateNodes(newTree, newList, lines, rows);
			}
		}
}

void display(FILE *outFile, gameTree *tree, int lines, int rows)
{
	if(!tree) return; 
	listNode *auxList = tree->head;
	while(auxList)
	{
		for(int i = 0; i < lines; i++)
		{
			//INDENT
			for(int i = 0; i < tree->depth; i++)
				fprintf(outFile, "\t");
			for(int j = 0; j < rows; j++)			
				{
					fprintf(outFile, "%c", auxList->table[i][j]);
					if(j != rows - 1) fprintf(outFile, " ");
				}
			fprintf(outFile, "\n");
		}
		fprintf(outFile, "\n");
		display(outFile, auxList->child, lines, rows);
		auxList = auxList->next;
	}
}

void destroyList(listNode *head, int lines)
{
	if(!head) return;
	listNode *aux;
	while(head)
	{
		destroyTree(head->child, lines);
		aux = head;
		head = head->next;
		for(int i = 0; i < lines; i++)
			free(aux->table[i]);
		free(aux->table);
		free(aux);
	}
}

void destroyTree(gameTree *tree, int lines)
{
	if(!tree) return;
	destroyList(tree->head, lines);
	free(tree);
}