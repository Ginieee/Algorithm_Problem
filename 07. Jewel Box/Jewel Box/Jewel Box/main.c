#include <stdio.h>
#include <stdlib.h>

#define INPUT "input.txt"
#define OUTPUT "output.txt"

typedef struct BOX {
	int cost;
	int hold;
	double holdPerdollar;
}box;


int main() {
	
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("\nInput file could not open!\n");
		exit(1);
	}

	int pearlNum = 0;
	box box1;
	box box2;
	int box1Num = 0, box2Num = 0;
	int leftPearl = 0;
	int check = 0;

	fscanf(myFile, "%d", &pearlNum);
	while (pearlNum != 0) {
		fscanf(myFile, "%d %d", &box1.cost, &box1.hold);
		fscanf(myFile, "%d %d", &box2.cost, &box2.hold);

		box1.holdPerdollar = (double)box1.hold / (double)box1.cost;
		box2.holdPerdollar = (double)box2.hold / (double)box2.cost;

		//printf("%lf \t%lf\n", box1.holdPerdollar, box2.holdPerdollar);
		//printf("peartNum 나누기 box1.hold = %d\n", pearlNum % box1.hold);
		//printf("peartNum 나누기 box2.hold = %d\n", pearlNum % box2.hold);

		if (box1.holdPerdollar >= box2.holdPerdollar) {
			box1Num = pearlNum / box1.hold;
			leftPearl = pearlNum % box1.hold;
			if (leftPearl != 0) {
				check = 0;
				for (int i = 0; i <= box1Num; i++) {
					if (leftPearl + (box1.hold * i) == box2.hold) {
						check = 1;
						box2Num = i;
						box1Num -= box2Num;
						printf("%d 1\n", box1Num);
						break;
					}
				}
				if (check == 0) {
					printf("failed\n");
				}
			}
			else {
				printf("%d 1\n", box1Num);
			}
		}
		else {
			box2Num = pearlNum / box2.hold;
			leftPearl = pearlNum % box2.hold;
			if (leftPearl != 0) {
				check = 0;
				for (int i = 0; i <= box2Num; i++) {
					if (leftPearl + (box2.hold * i) == box1.hold) {
						check = 1;
						box1Num = i;
						box2Num -= box1Num;
						printf("%d 2\n", box2Num);
						break;
					}
				}
				if (check == 0) {
					printf("failed\n");
				}
			}
			else {
				printf("%d 2\n", box2Num);
			}
		}
		fscanf(myFile, "%d", &pearlNum);
	}

	fclose(myFile);
}