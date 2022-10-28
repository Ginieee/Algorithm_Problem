#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SCHEDULE {
	int st_h;
	int st_m;
	int end_h;
	int end_m;
	char name[255];
};

struct NAP {
	int st_h;
	int st_min;
	int nap_h;
	int nap_m;
};

int main() {
	FILE* myFile = NULL;
	myFile = fopen("SweetNap.txt", "r");
	if (myFile == NULL) {
		printf("INPUT FILE COULE NOT OPENED!\n");
		exit(1);
	}

	int scheduleCnt = 0;
	char start[6], end[6], title[255];
	int st_h, st_m, end_h, end_m;
	fscanf(myFile, "%d", &scheduleCnt);

	struct SCHEDULE* sch = (struct SCHEDULE*)malloc(sizeof(struct SCHEDULE));
	struct NAP napTime;

	for (int i = 0; i < scheduleCnt; i++) {
		fscanf(myFile, "%s %s %[^\n]", start, end, sch[i].name);

		st_h = atoi(strtok(start, ":"));
		st_m = atoi(strtok(NULL, ":"));
		end_h = atoi(strtok(end, ":"));
		end_m = atoi(strtok(NULL, ":"));

		sch[i].st_h = st_h;
		sch[i].st_m = st_m;
		sch[i].end_h = end_h;
		sch[i].end_m = end_m;

		printf("%d:%d %d:%d %s\n", sch[i].st_h, sch[i].st_m, sch[i].end_h, sch[i].end_m, sch[i].name);
	}

	free(sch);

	fclose(myFile);

}