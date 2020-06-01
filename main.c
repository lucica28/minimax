#include "cerinta1.h"
#include "cerinta2.h"
#include "bonus.h"

void solveCerinta1(char *inFile, char *outFile)
{
	int lines, rows;
	gameTree *tree = readTable(inFile, &lines, &rows);
	generateNodes(tree, tree->head, lines, rows);
	FILE *fout = fopen(outFile, "w");
	display(fout, tree, lines, rows);
	fclose(fout);
	destroyTree(tree, lines);	
}

void solveCerinta2(char *inFile, char *outFile)
{
	FILE *fin = fopen(inFile, "r");
	FILE *fout = fopen(outFile, "w");
	char lin[500000], **buffer;
	int maxDepth;
	Queue *q;
	initQueue(&q);
	fscanf(fin, "%d\n", &maxDepth);
	buffer = malloc(maxDepth * sizeof(char*));
	for(int i = 0; i < maxDepth; i++)
	{
		fgets(lin, 500000, fin);
		lin[strlen(lin) - 1] = 0;
		buffer[i] = malloc((strlen(lin) + 1) * sizeof(char));
		strcpy(buffer[i], lin);
	}
	for(int i = maxDepth - 1; i >= 0; i--)
	{
		char *p = strtok(buffer[i], " ");
		while(p)
		{
			p[strlen(p) - 1] = 0;
			if(p[0] == '(') 
			{	
				Tree *newNode = createNode(0, i + 1);
				for(int j = 0; j < atoi(p + 1); j++)
				{
					insert(newNode, front(q));
					dequeue(q);
				}
				enqueue(q, newNode);
			}
			else 
			{
				Tree *newNode = createNode(atoi(p + 1), i + 1);
				enqueue(q, newNode);
			}
			p = strtok(NULL, " ");
		}
	}
	for(int i = 0; i < maxDepth; i++)
		free(buffer[i]);
	free(buffer);
	minEval(front(q));
	Display(fout, front(q));
	fclose(fin);
	fclose(fout);
	destroy(front(q));
	clear(q);
	free(q);
}

void solveCerinta3(char *inFile, char *outFile)
{
	FILE *fin = fopen(inFile, "r");
	FILE *fout = fopen(outFile, "w");
	char lin[500000], **buffer;
	int maxDepth;
	Queue *q;
	initQueue(&q);
	fscanf(fin, "%d\n", &maxDepth);
	buffer = malloc(maxDepth * sizeof(char*));
	for(int i = 0; i < maxDepth; i++)
	{
		fgets(lin, 500000, fin);
		lin[strlen(lin) - 1] = 0;
		buffer[i] = malloc((strlen(lin) + 1) * sizeof(char));
		strcpy(buffer[i], lin);
	}
	for(int i = maxDepth - 1; i >= 0; i--)
	{
		char *p = strtok(buffer[i], " ");
		while(p)
		{
			p[strlen(p) - 1] = 0;
			if(p[0] == '(') 
			{	
				Tree *newNode = createNode(0, i + 1);
				for(int j = 0; j < atoi(p + 1); j++)
				{
					insert(newNode, front(q));
					dequeue(q);
				}
				enqueue(q, newNode);
			}
			else 
			{
				Tree *newNode = createNode(atoi(p + 1), i + 1);
				enqueue(q, newNode);
			}
			p = strtok(NULL, " ");
		}
	}
	for(int i = 0; i < maxDepth; i++)
		free(buffer[i]);
	free(buffer);
	minEvalPrune(front(q), -999999, 999999);
	Display(fout, front(q));
	fclose(fin);
	fclose(fout);
	destroy(front(q));
	clear(q);
	free(q);
}


int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("Eroare la introducerea argumentelor\n");
		return 0;
	}
	
	if(!strcmp(argv[1], "-c1")) solveCerinta1(argv[2], argv[3]);
	if(!strcmp(argv[1], "-c2")) solveCerinta2(argv[2], argv[3]);
	if(!strcmp(argv[1], "-c3")) solveCerinta3(argv[2], argv[3]);

	return 0;
}

