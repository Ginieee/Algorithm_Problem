#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT "input.txt"
#define XMAX 10000
#define ZMAX 100

int** dpRoot = NULL;
int lengthX = 0, lengthZ = 0;
char x[XMAX];
char z[ZMAX];

void initMalloc();
void setMalloc();
void findSequence();
void freeMalloc(); 
void initGlobal();


int main() {

	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("Input File Could Not Opened!\n");
		exit(1);
	}

	int caseNum = 0;
	int result = 0;

	fscanf(myFile, "%d", &caseNum);
	for (int k = 0; k < caseNum; k++) {
		fscanf(myFile, "%s\n%s", x, z);
		lengthX = strlen(x);
		lengthZ = strlen(z);
		/*printf("%s %d\n%s %d\n", x, lengthX, z, lengthZ);
		printf("IN X : \n");
		for (int j = 0; j < lengthX; j++) {
			printf("%c\n", x[j]);
		}
		printf("IN Z : \n");
		for (int j = 0; j < lengthZ; j++) {
			printf("%c\n", z[j]);
		}*/

		int** dp = (int**)malloc(sizeof(int*) * (lengthZ + 1));
		for (int i = 0; i < lengthZ + 1; i++) {
			dp[i] = (int*)malloc(sizeof(int) * (lengthX + 1));
		}

		dpRoot = dp;

		initMalloc();
		setMalloc();
		findSequence();

		result = dp[lengthZ][lengthX];
		printf("%d\n", result);

		freeMalloc();
		initGlobal();
	}

	fclose(myFile);
}

void initMalloc() {
	for (int i = 0; i < lengthZ + 1; i++) {
		for (int j = 0; j < lengthX + 1; j++) {
			dpRoot[i][j] = 0;
			//printf(" %d ", dpRoot[i][j]);
		}
		//printf("\n");
	}
	//printf("\ninit malloc finish\n");
}

void setMalloc() {
	for (int i = 0; i < lengthX + 1; i++) {
		dpRoot[0][i] = 1;
	}
}

void findSequence() {
	for (int i = 1; i <= lengthZ; i++) {
		for (int j = 1; j <= lengthX; j++) {
			if (z[i - 1] == x[j - 1]) {
				dpRoot[i][j] = dpRoot[i - 1][j - 1] + dpRoot[i][j - 1];
			}
			else {
				dpRoot[i][j] = dpRoot[i][j - 1];
			}
		}
	}
}

void freeMalloc() {
	int** temp = dpRoot;
	dpRoot = NULL;
	for (int i = 0; i < lengthZ + 1; i++) {
		free(temp[i]);
	}
	free(temp);
}

void initGlobal() {
	dpRoot = NULL;
	lengthX = 0; 
	lengthZ = 0;
	x[0] = "\0";
	z[0] = "\0";
}