#include <stdio.h>
#include <stdlib.h>
#define INPUT "input.txt"

/*
* �켱 ����� ���ϴµ�
* ��� % 10�� 0�� �ƴ϶�� 10���� �������� �ʴ´ٴ� �Ҹ��ϱ�
* �л��� x 10���� ���� ������ = ��ŭ�� ���� ���ΰ�
* �װ� 10���� ���� ��ŭ�� �л�(n��)�� ���ؾ� ��
* �л����� �� ���� �� ������ �����ؼ� ���� n���� �л���(���� ���� �� �л���) �� ���� �δ��ϵ���
* -> ���� �� ����� ���� ���� ���� �̵��� �����ϱ�
* �׸��� �����ϴ� �� - �� �� �� ����ؼ� �� ���� ��
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