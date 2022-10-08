
/*
*
* Algorithm HW : Smart elephant
* Author : Kang Eojin (kaj1226@gachon.ac.kr)
* 
* Summary of file :
*   Some people think that the bigger an elephant is, the smarter it is.
*   To disprove this, you want to analyze a collection of elephants and place as large a subset of elephants as possible into a sequence whose weights are increasing but IQ's are decreasing.
*  
* Information of Input : 
*   The input will consist of data for a bunch of elephants, at on elephant per line terminated by the EOF.
*   The data for each particular elephant will consist of a pair of integers : the first representing its size in kilograms and the second representing its IQ in the hundredths of IQ points.
*   Both integers are between 1 and 10,000.
*   Two elephants may have the same weight, the same IQ, or even the same weight and IQ.
* 
* Information of Output :
*   The first output line should contain an integer n, the length of elephant sequence found.
*   The remaining n lines should each contain a single positive integer representing an elephant.
*   Denote the numbers on the ith data line as W[i] and S[i]
*   If these sequence of n elephants are a[1],a[2],...,a[n] then it must be the case that
*       W[a[1]] < W[a[2]] < ... < W[a[n]] and S[a[1]] > S[a[2]] > ... > S[a[n]]
* 
* In order for the answer to be correct, n must be as large as possible.
* All inequalities are strict : weights must be strictly increasing, and IQs must be strictly decreasing.
* Your program can report any correct answer for a given input.
* 
* 
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1001 //for use in LCS array, it must have default value in 0th index. So 1000+1.
#define INPUT "input.txt" 
#define OUTPUT "output.txt"

#define INPUT2 "input2.txt"  //just for test
#define INPUT3 "input3.txt"

struct ELEPHANT { //struct of elephant. It has weight, IQ, and own idx(index).
    int weight;
    int IQ;
    int idx;
};

struct LCS { //struct of LCS. It has prev for store prev path's idx, length for count length of sequence.
    int prev;
    int length;
};

struct ELEPHANT elephant[MAX]; //To store information of elephants.
int size = 0; //To store input's size(number of input elephants).
int max = 0; //To store the max length.
int start = 0; //To get start idx of final(longest) sequence's path.

struct LCS lcs[MAX]; //To calculate and store each sequence's length
int result[MAX]; //To store each index of LCS.

//function prototype
void initArr();
void readFile();
int compare(const void* a, const void* b);
void printElephant();
void getLCS();
void printLCS();
void findMaxLCS();
void getPath();
void printOutput();

//printElephant() and printLCS() are just for test
int main() {
    initArr();
    readFile();
    //printElephant();
    qsort(elephant, size, sizeof(elephant[0]), compare); //using qsort to sort elephants.
    //printElephant();
    getLCS();
    //printLCS();
    findMaxLCS();
    getPath();
    printOutput();
}


/*
* 
* Function Name : initArr()
* Return value : nothing
* Summary of Function :
*   This function is for initialize each array.
*       elephant array : init all objects to 0 for default velue.
*       lcs array : init prev to -1, means there are no prev path(index) yet.
*                   init length to 1, means only that index is in the LCS path.
*       result array : init to 0 for default value.
* 
*/
void initArr() {
    for (int i = 0; i < MAX; i++) {
        elephant[i].weight = 0;
        elephant[i].IQ = 0;
        elephant[i].idx = 0;

        lcs[i].prev = -1;
        lcs[i].length = 1;

        result[i] = 0;
    }
}


/*
*
* Function Name : readFile()
* Return value : nothing
* Summary of Function :
*   This function is for read input file.
*   It reads input file and store each elephant's information to elephant[i].
*   And store the number of elephants in size.
*
*/
void readFile() {
    FILE* myFile = NULL;
    myFile = fopen(INPUT, "r");
    if (myFile == NULL) {
        printf("File could not open!\n");
        exit(1);
    }

    int i = 0;
    while (fscanf(myFile, "%d %d", &elephant[i].weight, &elephant[i].IQ) != EOF) {
        elephant[i].idx = i + 1;
        i++;
    }
    size = i;

    fclose(myFile);
}


/*
*
* Function Name : compare(const void *a, const void *b)
* Return value : int value
* Summary of Function :
*   This function is used for qsort function.
*   It is used to sort elephants in ascending order of weight, but if the weights are the same, it is used to sort IQ in descending order.
*   If it returns positive number, it means it needs to sort, but if it returns negative number, it means it doesn't need to sort.
*
*/
int compare(const void *a, const void *b) {
    struct ELEPHANT e1 = *(struct ELEPHANT*)a;
    struct ELEPHANT e2 = *(struct ELEPHANT*)b;

    if (e1.weight != e2.weight) {
        return (e1.weight - e2.weight);
    }
    else {
        return (e2.IQ - e1.IQ);
    }
}


/*
*
* Function Name : printElephant()
* Return value : nothing
* Summary of Function :
*   This function is for print elephant array.
*   It prints each elephant's weight and IQ, but used for just test.
*
*/
void printElephant() {
    printf("\n\n----------print Elephant----------\n");
    for (int i = 0; i < size; i++) {
        printf("%dth : \tweight %d\tIQ %d\tindex : %d\n", i, elephant[i].weight, elephant[i].IQ, elephant[i].idx);
    }
    printf("\n----------------------------------\n\n");
}


/*
*
* Function Name : getLCS()()
* Return value : nothing
* Summary of Function :
*   This function is for calculate LCS.
*   It start with second(index 1) elephant because first elephant can calculate nothing.
*   So, compared to the elephants in front of this elephant, if this elephant's weight is bigger and IQ is smaller than front one, that LCS can be updated.
*   For efficiency, check this lcs length is less than the value to be increaed. So, if it is smaller than the value to be increase, increase that and store path that passed to lcs's prev value.
*
*/
void getLCS() {
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (elephant[i].weight > elephant[j].weight && elephant[i].IQ < elephant[j].IQ) { // check it can be update or not
                if (lcs[i].length < lcs[j].length + 1) { //check for efficiency
                    lcs[i].length = lcs[j].length + 1;
                    lcs[i].prev = j; //save path(index) that passed
                }
            }
        }
    }
}


/*
*
* Function Name : printLCS()
* Return value : nothing
* Summary of Function :
*   This function is for print lcs array.
*   It prints each lcs's length and prev value, but used for just test.
*
*/
void printLCS() {
    printf("\n\n----------print LCS----------\n");
    printf("length : ");
    for (int i = 0; i < size; i++) {
        printf(" %d ", lcs[i].length);
    }
    printf("\nprev : ");
    for (int i = 0; i < size; i++) {
        printf(" %d ", lcs[i].prev);
    }
    printf("\n----------------------------------\n\n");
}


/*
*
* Function Name : findMaxLCS()
* Return value : nothing
* Summary of Function :
*   This function is for find Longest pass in LCS(real LCS).
*   If this lcs's length is bigger than max value, store it and store that index to start value to used for get path that passed.
*
*/
void findMaxLCS() {
    for (int i = 0; i < size; i++) {
        if (lcs[i].length > max) {
            max = lcs[i].length;
            start = i;
        }
    }
}


/*
*
* Function Name : getPath()
* Return value : nothing
* Summary of Function :
*   This function is for get path that passed before.
*   Start with idx = max-1 because it will go to 0.
*   While idx is bigger or same as 0, it store each path's idx to result array.
*   And store next prev idx to start value.
*
*/
void getPath() {
    int idx = max - 1;
    while (idx >= 0) {
        result[idx] = elephant[start].idx;  //store each path's idx
        start = lcs[start].prev; //store next prev idx
        idx--;
    }
}


/*
*
* Function Name : printOutput()
* Return value : nothing
* Summary of Function :
*   This function is for print final output.
*   It follows with upper OUTPUT rules.
*   It print to colsole with file.
*
*/
void printOutput() {
    //printf("\n\n**********OUTPUT*********\n");
    FILE* myFile = NULL;
    myFile = fopen(OUTPUT, "w");
    if (myFile == NULL) {
        printf("Output File could not open!\n");
        exit(1);
    }

    printf("%d\n", max); //print max length
    fprintf(myFile, "%d\n", max);

    for (int i = 0; i < max; i++) { //print each path's idx
        printf("%d\n", result[i]);
        fprintf(myFile, "%d\n", result[i]);
    }

    fclose(myFile);
}