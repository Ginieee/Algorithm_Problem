/*
* Lab1 - Algorithm Class
* Author : Kang Eojin(kaj1226@gachon.ac.kr)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INPUT "input.txt"
#define INPUT2 "input2.txt"
#define INPUT3 "input3.txt"
#define MAXINTER 100
#define MAXROAD 10
#define MAXFIRE 100
#define INF 9999

int** lengthRoot;
int dis[MAXINTER]; //the distance from nearest fire station to each intersection

void initDisToFire(int interCnt); 
void initLength(int interCnt);
void getLength(int interCnt);
int getPoorResidents(int interCnt);

int main() {

	//file open
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("INPUT COULD NOT OPENED!\n");
		exit(1);
	}


	int fireCnt = 0, interCnt = 0;
	int fire = 0; //fire station's location
	int u, v, l; //each roads start intersection, end intersection, length


	fscanf(myFile, "%d %d", &fireCnt, &interCnt);
	initDisToFire(interCnt);
	

	//to store each length between intersections
	int** length = (int**)malloc(sizeof(int*) * (interCnt + 1));
	for (int i = 0; i < interCnt + 1; i++) {
		length[i] = (int*)malloc(sizeof(int) * (interCnt + 1));
	}
	lengthRoot = length;

	initLength(interCnt);

	for (int i = 0; i < fireCnt; i++) {
		fscanf(myFile, "%d", &fire);
		dis[fire] = 0; //the distance from firestation to itself is 0
	}

	//store each length between intersection
	//Since it is two way segments, store two way too.
	for (int i = 0; i < interCnt; i++) {
		fscanf(myFile, "%d %d %d", &u, &v, &l);
		length[u][v] = l;
		length[v][u] = l;
	}

	getLength(interCnt);

	int min = getPoorResidents(interCnt);

	printf("%d\n", min);

	//free malloc and close file
	for (int i = 0; i < interCnt + 1; i++) {
		free(length[i]);
	}
	free(length);

	fclose(myFile);
}

void initDisToFire(int interCnt) {
	//init every distance to INF cause we don't know where is fire station yet
	for (int i = 1; i <= interCnt; i++) {
		dis[i] = INF;
	}
}

void initLength(int interCnt) {
	//init that length
	//If i and j are same, it means the road segment to itself, so store 0
	//But if they are different, we don't know length yet so store INF
	for (int i = 0; i < interCnt + 1; i++) {
		for (int j = 0; j < interCnt + 1; j++) {
			if (i == j) {
				lengthRoot[i][j] = 0;
			}
			else {
				lengthRoot[i][j] = INF;
			}
		}
	}
}

void getLength(int interCnt) {
	//get the length between each intersection to nearest fire station.
	for (int k = 1; k <= interCnt; k++) {
		for (int i = 1; i <= interCnt; i++) {
			for (int j = 1; j <= interCnt; j++) {
				lengthRoot[i][j] = min(lengthRoot[i][j], lengthRoot[i][k] + lengthRoot[k][j]);
			}
		}
	}
}

int getPoorResidents(int interCnt) {
	int n = 0;
	int temp = 0;
	int tempPos = 0;

	int result[MAXINTER] = { 0, };

	for (int i = 1; i <= interCnt; i++) {
		if (dis[i] == 0) { //if there is fire station, check each maximum distance
			for (int j = 1; j <= interCnt; j++) {
				if (lengthRoot[i][j] > temp) {
					temp = lengthRoot[i][j];
					tempPos = j;
				}
			}
			result[n] = tempPos; //store that poorest-served resident's intersection
			n++;
		}
	}

	int min = 0;
	//to output the lowest intersection number
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			min = result[0];
		}
		else {
			if (min > result[i]) {
				min = result[i];
			}
		}
	}

	return min;
}