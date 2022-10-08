#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define MAXNUM 29

struct DOT {
	double x;
	double y;
};

struct EDGE {
	int u;
	int v;
	double w;
};

int dotNum = 0;
struct DOT dot[MAXNUM];
struct EDGE edge[MAXNUM][MAXNUM];

void readFile();
void printInput();
void makeEdge();
void printEdge();
void initEdge();

int main() {
	readFile();
	makeEdge();
}

void readFile() {
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("Input File Open is failed!\n");
		exit(1);
	}

	fscanf(myFile, "%d", &dotNum);
	for (int i = 0; i < dotNum; i++) {
		fscanf(myFile, "%lf %lf", &dot[i].x, &dot[i].y);
		//printf(" %lf %lf \n", dot[i].x, dot[i].y);
	}

	printInput();

	fclose(myFile);
}

void printInput() {
	printf("%d\n", dotNum);
	for (int i = 0; i < dotNum; i++) {
		printf("%.1lf %.1lf \n", dot[i].x, dot[i].y);
	}
}

void makeEdge() {
	initEdge();

	for (int u = 0; u < dotNum; u++) {
		for (int v = 0; v < dotNum; v++) {
			if (u == v) continue;
			edge[u][v].u = u;
			edge[u][v].v = v;
			edge[u][v].w = sqrt(pow(dot[u].x - dot[v].x, 2) + pow(dot[u].y - dot[v].y, 2));
		}
	}

	printEdge();
}

void printEdge() {
	for (int u = 0; u < dotNum; u++) {
		for (int v = 0; v < dotNum; v++) {
			printf("\t(%d,%d)%.2lf", edge[u][v].u, edge[u][v].v, edge[u][v].w);
		}
		printf("\n");
	}
}

void initEdge() {
	for (int i = 0; i < MAXNUM; i++) {
		for (int j = 0; j < MAXNUM; j++) {
			edge[i][j].u = -1;
			edge[i][j].v = -1;
			edge[i][j].w = -1.0;

		}
	}
}