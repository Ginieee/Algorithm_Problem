#include <stdio.h>
#include <stdlib.h>

#define INPUT "input.txt"

FILE* myFile = NULL;

struct TRIP {
	int num;
	int cnt;
	int student[100];
	int money[100];
}trip;

void readInput();
void printTrip();
void initTrip();
int divMoney();
void calMoney();
void swap(int front, int back);
void sortingStudent();
void printResult();


int main() {

	trip.cnt = 0;
	trip.num = 0;
	for (int i = 0; i < 100; i++) {
		trip.student[i] = 0;
		trip.money[i] = 0;
	}
	readInput();
}

void readInput() {
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("File Open Failed!\n");
		exit(1);
	}

	int readNum = 0;

	while (fscanf(myFile, "%d", &readNum) == 1) {
		//printf("%d\n", readNum);
		if (readNum > 0 && readNum <= 100) {
			if (trip.cnt != 0) {
				printTrip();
			}
			trip.num = readNum;
		}
		else if (readNum > 100 && readNum <= 100000) { //이거 100보다 크다라고 해도 되나?
			trip.student[trip.cnt++] = readNum;
		}
		else if (readNum == 0) {
			if (trip.cnt != 0) {
				printTrip();
			}
			printf("No more Trip Information.\n");
		}
	}
}

int divMoney() {
	int sum = 0;
	for (int i = 0; i < trip.num; i++) {
		sum += trip.student[i];
	}
	int div = sum / trip.num;
	return div;
}

void printTrip() {
	printf("************************************\n");
	printf("\n\nTRIP STUDENT NUMBER : %d\n\n", trip.num);
	for (int i = 0; i < trip.num; i++) {
		printf("%dth student : %d\n", i + 1, trip.student[i]);
	}

	calMoney();

	printf("\n\n************************************\n");
	initTrip();
}

void initTrip() {
	for (int i = 0; i < trip.num; i++) {
		trip.student[i] = 0;
	}

	trip.cnt = 0;
}

void calMoney() {
	int eachMoney = divMoney();
	//printf("EACH MONEY : %d\n", eachMoney);
	for (int i = 0; i < trip.num; i++) {
		trip.money[i] = eachMoney;
	}

	if (eachMoney % 10 <= 9 && eachMoney % 10 >= 1) {
		int move = eachMoney % 10;
		int totalMove = move * trip.num;
		int getMore = totalMove / 10;
		eachMoney -= move;
		for (int i = 0; i < trip.num; i++) {
			trip.money[i] = eachMoney;
		}
		for (int i = 0; i < getMore; i++) {
			trip.money[i] += 10;
		}
		for (int i = 0; i < trip.num; i++) {
			printf("%d student money : %d\n", i + 1, trip.money[i]);
		}
	}

	sortingStudent();

	printResult();

}

void sortingStudent() {
	for (int i = 0; i < trip.num; i++) {
		for (int j = 0; j < trip.num-1; j++) {
			if (trip.student[j] < trip.student[j + 1]) {
				swap(j, j + 1);
			}
		}
	}
}

void swap(int front, int back) {
	int i = trip.student[front];
	trip.student[front] = trip.student[back];
	trip.student[back] = i;
}

void printResult() {
	int total = 0;
	printf("----------Result-----------\n");
	for (int i = 0; i < trip.num; i++) {
		printf(" %d student money : %d\n", trip.student[i], trip.money[i]);
		if (trip.student[i] < trip.money[i]) {
			total += trip.money[i] - trip.student[i];
		}
	}
	printf("\tOUTPUT : %d\n", total);
	printf("---------------------------\n");
}