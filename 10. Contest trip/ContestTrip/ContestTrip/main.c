#include <stdio.h>
#include <stdlib.h>
#define MAXCITY 100
#define DAY 100
#define MAXSTOP 100
#define CITY 25
#define INPUT "input.txt"

struct TRAIN {
	int cityNum;
	char cities[MAXCITY][CITY];
}train;

struct RUN {
	char time[5];
	char city[CITY];
}run[DAY][MAXSTOP];

struct USER {
	char startTime[5];
	char startCity[CITY];
	char destinationCity[CITY];
}user;



int main() {
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("INPUT FILE COULD NOT BE OPENED!\n");
		exit(1);
	}

	fscanf(myFile, "%d", &train.cityNum);
	//printf("city num : %d\n", train.cityNum);
	for (int i = 0; i < train.cityNum; i++) {
		fscanf(myFile, "%s", train.cities[i]);
		//printf("In train City : %s\n", train.cities[i]);
	}

	int caseNum = 0;
	int stopNum = 0;
	fscanf(myFile, "%d", &caseNum);
	//printf("case num : %d\n", caseNum);
	for (int i = 0; i < caseNum; i++) {
		fscanf(myFile, "%d", &stopNum);
		//printf("stopNum : %d\n", stopNum);
		for (int j = 0; j < stopNum; j++) {
			fscanf(myFile, "%s %s", run[i][j].time, run[i][j].city);
			//printf("TIME : %s , CITY : %s\n", run[i][j].time, run[i][j].city);
		}
	}

	fscanf(myFile, "%s %s %s", user.startTime, user.startCity, user.destinationCity);
	//printf("%s\n%s\n%s\n", user.startTime, user.startCity, user.destinationCity);
	


}