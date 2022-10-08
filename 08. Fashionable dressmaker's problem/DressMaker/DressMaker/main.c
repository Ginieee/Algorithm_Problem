/*
* �ڵ� n���� Ŀ���� �Ƿ� ����
* �Ϸ翡 �� ���ۿ� �� �� -> ���� �� ���� ��ĥ �ҿ�
* i��° job�� ���ؼ�, Ti(1<=T<=1000) �� �ҿ�Ǵ� �� �� ��Ÿ��
* 
* �ٵ� ���⼭? ������ ����
* ���� ������ �����Ǵ� �� ����ŭ, �ڵ�� �Ϸ翡 Si ��Ʈ�� �����ؾ� ��
* 
* �ڵ� ������ ���� �� �� �ֵ��� ������ ã��
* 
* ��ǲ : 
* �ϳ��� ��� - number of test cases, followed by a blank line
* ���� �� ���̽��� ���̿��� blank line ����
* �� ���̽��� ù ��° �� - 1~1000�� ���� - number of jobs
* �׸��� �� job�� �����ϴ� �ٿ��� Ti�� Si�� ���
* 
* �ƿ�ǲ :
* For each test case, �ּ��� ������ �� �� �ִ� sequence ���
* �� job�� ������ input position���� ��Ÿ��
* sequence�� ��� �� �ٿ�, ���� ���̴� ����� ����
* ���̽��� �ƿ�ǲ ���̿��� �� ���� ����
* 
*/

#include <stdio.h>
#include <stdlib.h>
#define INPUT "input.txt"
#define MAXJOB 1000

struct JOB {
	int pos;
	int t;
	int s;
};

int main() {

	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) {
		printf("INPUT FILE COULD NOT OPENED!\n");
		exit(1);
	}

	int testNum = 0;
	int jobNum = 0;

	fscanf(myFile, "%d\n", &testNum);
	for (int i = 0; i < testNum; i++) {
		fscanf(myFile, "%d", &jobNum);

		struct JOB* jobs = (struct JOB*)malloc(sizeof(struct JOB) * jobNum);

		for (int j = 0; j < jobNum; j++) {
			fscanf(myFile, "%d %d", &jobs[j].t, &jobs[j].s);
			jobs[j].pos = j + 1;
		}

		//��� ��Ȳ ���鼭 �ٲ�ߵǴϱ� bubble sort?
		for (int m = 1; m < jobNum; m++) {
			for (int n = 0; n < jobNum - 1; n++) {
				if (jobs[n].t * jobs[n + 1].s > jobs[n + 1].t * jobs[n].s) {
					struct JOB temp = jobs[n];
					jobs[n] = jobs[n + 1];
					jobs[n + 1] = temp;
				}
			}
		}

		for (int j = 0; j < jobNum; j++) {
			printf("%d ", jobs[j].pos);
		}
		printf("\n\n");

		free(jobs);
	}

	fclose(myFile);
}