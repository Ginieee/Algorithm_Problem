#include <stdio.h>
#include <stdlib.h>
#define INPUT "input.txt"

/*
* 우선 평균을 구하는데
* 평균 % 10이 0이 아니라면 10으로 떨어지지 않는다는 소리니까
* 학생수 x 10으로 나눈 나머지 = 만큼을 따로 빼두고
* 그걸 10으로 나눈 몫만큼의 학생(n명)을 정해야 함
* 학생들을 돈 많이 낸 순으로 정렬해서 위의 n명의 학생들(돈을 많이 낸 학생들) 저 몫을 부담하도록
* -> 많이 낸 사람이 많이 내야 돈의 이동이 적으니까
* 그리고 내야하는 돈 - 낸 돈 을 계산해서 다 합해 줌
*/

struct STUDENT {
	int pastPay;
	int totalPay;
};

int compare(const void* a, const void* b);

int main() {
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("INPUT FILE COULD NOT OPENED!\n");
		exit(1);
	}

	int studentNum = 0;
	int total = 0, avg = 0;
	int rest = 0, eachRest = 0, restStudent = 0;
	int moveMoney = 0;

	fscanf(myFile, "%d", &studentNum);
	while (studentNum != 0) {

		struct STUDENT* students = (struct STUDENT*)malloc(sizeof(struct STUDENT) * studentNum);
		for (int i = 0; i < studentNum; i++) {
			fscanf(myFile, "%d", &students[i].pastPay);
			total += students[i].pastPay;
		}
		avg = total / studentNum;

		if (avg % 10 == 0) {
			for (int i = 0; i < studentNum; i++) {
				students[i].totalPay = avg;
				if (students[i].totalPay > students[i].pastPay) {
					moveMoney += students[i].totalPay - students[i].pastPay;
				}
			}
		}
		else {
			rest = (avg % 10) * studentNum;
			restStudent = rest / 10;
			eachRest = rest / restStudent;
			avg = avg - (avg % 10);
			qsort(students, studentNum, sizeof(struct STUDENT), compare);

			for (int i = 0; i < restStudent; i++) {
				students[i].totalPay = avg + eachRest;
				if (students[i].totalPay > students[i].pastPay) {
					moveMoney += students[i].totalPay - students[i].pastPay;
				}
			}
			for (int i = restStudent; i < studentNum; i++) {
				students[i].totalPay = avg;
				if (students[i].totalPay > students[i].pastPay) {
					moveMoney += students[i].totalPay - students[i].pastPay;
				}
			}
		}

		printf("\\%d\n", moveMoney);

		total = 0;
		avg = 0;
		rest = 0;
		eachRest = 0;
		restStudent = 0;
		moveMoney = 0;

		free(students);

		fscanf(myFile, "%d", &studentNum);
	}


	fclose(myFile);
}

int compare(const void* a, const void* b) {
	struct STUDENT* s1 = (struct STUDENT*)a;
	struct STUDENT* s2 = (struct STUDENT*)b;

	if (s1->pastPay < s2->pastPay) {
		return 1;
	}
	else if (s1->pastPay > s2->pastPay) {
		return -1;
	}
	else return 0;
}