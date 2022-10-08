/*
* 코디가 n개의 커스텀 의뢰 받음
* 하루에 한 개밖에 못 함 -> 보통 한 개에 며칠 소요
* i번째 job에 대해서, Ti(1<=T<=1000) 는 소요되는 일 수 나타냄
* 
* 근데 여기서? 지각비가 있음
* 일의 시작이 지연되는 일 수만큼, 코디는 하루에 Si 센트를 지불해야 함
* 
* 코디가 지각비를 적게 낼 수 있도록 시퀀스 찾기
* 
* 인풋 : 
* 하나의 양수 - number of test cases, followed by a blank line
* 또한 각 케이스들 사이에도 blank line 있음
* 각 케이스의 첫 번째 줄 - 1~1000의 정수 - number of jobs
* 그리고 각 job을 설명하는 줄에는 Ti와 Si가 담김
* 
* 아웃풋 :
* For each test case, 최소의 지각비를 낼 수 있는 sequence 출력
* 각 job은 각각의 input position으로 나타냄
* sequence는 모두 한 줄에, 정수 사이는 띄어쓰기로 구분
* 케이스별 아웃풋 사이에는 빈 줄이 있음
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

		//계속 상황 보면서 바꿔야되니까 bubble sort?
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