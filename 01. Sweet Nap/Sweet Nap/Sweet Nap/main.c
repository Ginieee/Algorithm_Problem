/*
* Copy from https://github.com/KimRina-ai/SweetNap/blob/main/SweetNap.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"


typedef struct SCHEDULE {
	int st_h;
	int st_m;
	int end_h;
	int end_m;
	char title[255];
}schedule;

typedef struct NAP {
	int napst_h;
	int napst_m;
	int nap_time;
}nap;

schedule* sch;
nap* s_nap;

void time_token(char* start_time, char* end_time, int i);
int check(int num_schedule);
void sort(int num_schedule);
void naptime(int num_schedule);


int main() {
	int num_schedule;
	char start_time[6];
	char end_time[6];
	char sch_ex[255];
	int i = 0;

	FILE* inFile;
	FILE* outFile;

	inFile = fopen(INPUT, "r");
	if (inFile == NULL) {
		printf("\nInput File Could Not Be Opened!\n");
		exit(1);
	}

	fscanf(inFile, "%d", &num_schedule);
	sch = (schedule*)malloc(sizeof(schedule) * num_schedule);
	s_nap = (nap*)malloc(sizeof(nap));

	//%[^\n] = ���๮�ڸ� ������ ��� ���ڸ� ���� -> ���� ����!
	while (fscanf(inFile, "%s %s %[^\n]", start_time, end_time, sch_ex) != EOF) {
		time_token(start_time, end_time, i);
		i++;
	}
	if (check(num_schedule) == -1) {
		printf("Input Error");
		exit(1);
	}
	sort(num_schedule);
	naptime(num_schedule);

	outFile = fopen(OUTPUT, "w");	//Open Output File (write)
	if (outFile == NULL) {
		printf("Output File Couldn't Be Opened.");
		exit(1);
	}
	else
	{
		int h, m;

		h = s_nap->nap_time / 60;
		m = s_nap->nap_time % 60;

		if (num_schedule == 0)	//When number of schedule : 0
		{
			fprintf(outFile, "10:00\n08:00\n");
			return 0;
		}

		//Prints nap start time
		if (s_nap->napst_m < 10)
			fprintf(outFile, "%d:0%d\n", s_nap->napst_h, s_nap->napst_m);
		else
			fprintf(outFile, "%d:%d\n", s_nap->napst_h, s_nap->napst_m);

		//Prints total time to take a nap
		if (h > 0)			//The case when h > 0
		{
			if (h < 10)		//The case when h < 10
			{
				if (m < 10)	//The case when m < 10
					fprintf(outFile, "0%d:0%d\n", h, m);
				else
					fprintf(outFile, "0%d:%d\n", h, m);
			}
			else			//The case when h >= 10
			{
				if (m < 10)	//The case when m < 10
					fprintf(outFile, "%d:0%d\n", h, m);
				else
					fprintf(outFile, "%d:%d\n", h, m);
			}
		}
		else				//The case when h = 0
		{
			if (m < 10)
				fprintf(outFile, "00:0%d\n", m);
			else
				fprintf(outFile, "00:%d\n", m);
		}
	}

	fclose(inFile);
	fclose(outFile);

	return 0;

}

/*
* char* strtok(char* str, char* delimiters)
* str�� delimiters�� �������� �߶� �����͸� �ϳ��� ��ȯ�ϴ� �Լ�
* string.h�� ���� : ���ڿ��� �Է��� �����ڸ� �������� �߶� ���ڿ��� �����͸� �ϳ��� �ϳ��� ��ȯ�� -> �ڸ� ���ڿ��� ����Ű�� char* ��ȯ
* �����ڸ� ã�� �Ǹ� �ش� �����ڸ� ������ ���� �˸��� \0���� �ٲ�
* strtok�� ù ���� ��ȯ���� ù �����ڰ� ��Ÿ���� �������� ��. �� ���¿��� strtok(NULL,������)�� �ϰ� �Ǹ� ������ ã�� ������ �ڿ������� �ٽ� �����ڸ� ã�� ��
* �̷��� ��� �ϴٰ� ���������� �� ���Դµ� �� strtok(NULL,"") ȣ���ϸ� NULL ��ȯ��
* => strtok �Լ��� ó�� �ҷ��ٶ��� ���ϴ� ���ڿ��� ����ְ� �� �������ʹ� ù ��° ���ڿ� NULL�� ���� -> strtok���� "������ �ʰ� �����ڸ� ã�Ҵ� �� ���ڿ� �ּҿ������� �ٽ� ã�ƶ�"�� ��
* => �ѹ��� ���ڿ��� �Ĺ� �����ִ� �� �ƴϰ� strtok �Լ��� NULL�� ��ȯ�� ������ ����ؼ� �ҷ���� ��
*/
void time_token(char* start_time, char* end_time, int i) {
	char* token;

	token = strtok(start_time, ":");
	(sch + i)->st_h = atoi(token); // start h -> 10
	token = strtok(NULL, ":");
	(sch + i)->st_m = atoi(token); //start m -> 0

	token = strtok(end_time, ":");
	(sch + i)->end_h = atoi(token); //end h->11
	token = strtok(NULL, ":");
	(sch + i)->end_m = atoi(token); //end m->30
}

int check(int num_schedule) {
	int i;
	int count;

	for (i = 0; i < num_schedule; i++)
	{
		count = 0;
		//Time Limit 10:00 -18:00
		if ((sch + i)->st_h >= 10 && (sch + i)->st_h <= 18
			&& (sch + i)->st_m >= 0 && (sch + i)->st_m < 60
			&& (sch + i)->end_h >= 10 && (sch + i)->end_h <= 18
			&& (sch + i)->end_m >= 0 && (sch + i)->end_m < 60)
			count++;
		//Prevent same time
		if ((sch + i)->st_h != (sch + i)->end_h || (sch + i)->st_m != (sch + i)->end_m)
			count++;
		//Avoid situations where the start time is greater than the end time
		if ((sch + i)->st_h <= (sch + i)->end_h || (sch + i)->st_m < (sch + i)->end_m)
			count++;
		if (count != 3)
			return -1;
		return 0;
	}
}

void sort(int num_schedule)
{
	schedule sort;
	int i, j;

	for (i = 0; i < num_schedule; i++)
	{
		for (j = 0; j < num_schedule - 1; j++)
		{
			//Sort by hour
			if ((sch + j)->st_h > (sch + j + 1)->st_h)
			{
				sort = *(sch + j);
				*(sch + j) = *(sch + j + 1);
				*(sch + j + 1) = sort;
			}
			//Sort minutes if the times are the same
			else if ((sch + j)->st_h == (sch + j + 1)->st_h)
			{
				if ((sch + j)->st_m > (sch + j + 1)->st_m)
				{
					sort = *(sch + j);
					*(sch + j) = *(sch + j + 1);
					*(sch + j + 1) = sort;
				}
			}
		}
	}
}


void naptime(int num_schedule)
{
	int i;
	int total1;
	int total2;
	int front;
	int behind;

	front = ((sch->st_h) * 60 + (sch->st_m)) - 600;
	behind = 1080 - (((sch + num_schedule - 1)->end_h * 60) + (sch + num_schedule - 1)->end_m);

	if (front < behind)
	{
		s_nap->napst_h = (sch + num_schedule - 1)->end_h;
		s_nap->napst_m = (sch + num_schedule - 1)->end_m;
		s_nap->nap_time = behind;
	}

	else
	{
		s_nap->napst_h = 10;
		s_nap->napst_m = 0;
		s_nap->nap_time = front;
	}

	//Compare nap_time
	for (i = 0; i < num_schedule - 1; i++)
	{
		total1 = (sch + i + 1)->st_h * 60 + (sch + i + 1)->st_m;
		total2 = (sch + i)->end_h * 60 + (sch + i)->end_m;
		if ((total1 - total2) > s_nap->nap_time)
		{
			s_nap->napst_h = (sch + i)->end_h;
			s_nap->napst_m = (sch + i)->end_m;
			s_nap->nap_time = total1 - total2;
		}
	}
}