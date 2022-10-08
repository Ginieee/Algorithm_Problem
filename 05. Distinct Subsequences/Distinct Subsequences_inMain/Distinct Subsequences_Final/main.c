#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT "input.txt"
#define XMAX 10000
#define ZMAX 100



int main() {

	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("Input File Could Not Opened!\n");
		exit(1);
	}

	int caseNum = 0;
	int lengthX = 0, lengthZ = 0;
	char x[XMAX];
	char z[ZMAX];


	fscanf(myFile, "%d", &caseNum);
	for (int i = 0; i < caseNum; i++) {
		fscanf(myFile, "%s\n", x);
		fscanf(myFile, "%s\n", z);
		lengthX = strlen(x);
		lengthZ = strlen(z);
		printf("%s %d\n%s %d\n", x, lengthX, z, lengthZ);
		printf("IN X : \n");
		for (int j = 0; j < lengthX; j++) {
			printf("%c\n", x[j]);
		}
		printf("IN Z : \n");
		for (int j = 0; j < lengthZ; j++) {
			printf("%c\n", z[j]);
		}

		//create malloc
		int** dp = (int**)malloc(sizeof(int*) * (lengthZ + 1));
		for (int j = 0; j < lengthZ + 1; j++) {
			dp[j] = (int*)malloc(sizeof(int) * (lengthX + 1));
		}

		//init malloc
		for (int m = 0; m < lengthZ+ 1; m++) {
			for (int n = 0; n < lengthX + 1; n++) {
				dp[m][n] = 0;
				printf(" %d ", dp[m][n]);
			}
			printf("\n");
		}
		printf("\init malloc finish\n");

		//set malloc
		for (int j = 0; j < lengthX + 1; j++) {
			dp[0][j] = 1;
		}
		/*for (int m = 0; m < lengthZ + 1; m++) {
			for (int n = 0; n < lengthX + 1; n++) {
				printf(" %d ", dp[m][n]);
			}
			printf("\n");
		}*/
		for (int m = 1; m <= lengthZ; m++) {
			for (int n = 1; n <= lengthX; n++) {
				if (z[m - 1] == x[n - 1]) {
					dp[m][n] = dp[m - 1][n - 1] + dp[m][n - 1];
				}
				else {
					dp[m][n] = dp[m][n - 1];
				}
			}
		}

		for (int m = 0; m < lengthZ + 1; m++) {
			for (int n = 0; n < lengthX + 1; n++) {
				printf(" %d ", dp[m][n]);
			}
			printf("\n");
		}



		//malloc free
		for (int j = 0; j < lengthZ + 1; j++) {
			free(dp[j]);
		}
		free(dp);

		printf("\n\n finish once \n");
	}

	fclose(myFile);
}
