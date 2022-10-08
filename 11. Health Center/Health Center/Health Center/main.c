#include <stdio.h>
#include <stdlib.h>
#define MAXINTER 500
#define MAXROAD 20
#define MAXHEALTH 100
#define INPUT "input.txt"
#define INF 99

struct INTER {
	int startInter;
	int endInter;
	int length;
};

int healthNum = 0, interNum = 0;

int* existInter = NULL;
struct INTER* lengthInter = NULL;
int** adjcMatrix = NULL;

void readFile();
void makeAdjacency();
void initMatrix(int**);
void printMatrix(int** matrix);

int main() {
	readFile();
	makeAdjacency();
}

void readFile() {
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) { //defensive coding
		printf("Input File Open is failed!\n");
		exit(1);
	}

	fscanf(myFile, "%d %d", &healthNum, &interNum);
	int* existArr = (int*)malloc(sizeof(int) * healthNum);
	for (int i = 0; i < healthNum; i++) {
		fscanf(myFile, "%d", &existArr[i]);
	}
	existInter = existArr;

	struct INTER* interArr = (struct INTER*)malloc(sizeof(struct INTER) * interNum);
	for (int i = 0; i < interNum; i++) {
		fscanf(myFile, "%d %d %d", &interArr[i].startInter, &interArr[i].endInter, &interArr[i].length);
	}
	lengthInter = interArr;

	fclose(myFile);
}

void makeAdjacency() {
	int** adjc;
	adjc = (int**)malloc(sizeof(int*) * interNum);
	for (int i = 0; i < interNum; i++) {
		adjc[i] = (int*)malloc(sizeof(int) * interNum);
	}
	initMatrix(adjc);
	adjcMatrix = adjc;

	for (int i = 0; i < interNum; i++) {
		for (int j = 0; j < interNum; j++) {
			for (int k = 0; k < interNum; k++) {
				if (lengthInter[k].startInter == i && lengthInter[k].endInter == j) {
					adjc[i][j] = lengthInter[k].length;
				}
			}
		}
	}

	printMatrix(adjc);
}

void initMatrix(int** matrix) {
	for (int i = 0; i < interNum; i++) {
		for (int j = 0; j < interNum; j++) {
			matrix[i][j] = INF;
		}
	}
}

void printMatrix(int** matrix) {
	for (int i = 0; i < interNum; i++) {
		for (int j = 0; j < interNum; j++) {
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void floyd() {
	int i = 0, j = 0, k = 0;
	for (i = 0; i < interNum; i++) {
		for (j = 0; j < interNum; j++) {

		}
	}
}