
/*
*
* Algorithm HW : The Cheapest Way
* Author : Kang Eojin (kaj1226@gachon.ac.kr)
*
* Summary of file :
*   Given an m*n matrix of integers, your are to write a program that computes a path of minimal weight from left to right across the matrix.
*   A path starts anywhere in column 1 and consists of a sequence of steps termination in column n.
*   Each step consists of traveling from column i to column i+1 in an adjacent(horizontal and diagonal) row.
*   The first and last rows(rows 1 and m) of a matrix are considered adjacent;
*   i.e, the matrix "wraps" so that it represents a horizontal cylinder. Legal steps are illustrated below.
*   The weight of a path is the sum of the integers in each of the n cells of the matrix that are visited.
* 
*
* Information of Input :
*   The input consists of a sequence of matrix specifications. Each matrix consists of the row and column dimensions on a line, denoted m and n, respectively.
*   This is followed by m*n integers, appearing in row major order; i.e, the first n integers constitute the first row of the matrix, the second n integers constitute the second row, and so on. The integers on a line will be separated from other integers by one or more spaces.
*   There will be one or more matrix specification in an input file. Input is terminated by EOF.
*   For each specification the number of rows will be between 1 and 10 inclusive; the number of columns will be between 1 and 100 inclusive.
*
* Information of Output :
*   Two lines should be output for each matrix specification. The first line represents a minimal-weight path, and the second line is the cost of this minimal path.
*   If there is more than one path of minimal weight, the lexicographically smallest path should be output.
*
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 99999
#define INPUT "input.txt"
#define OUTPUT "output.txt"

#define MAX_ROW 10
#define MAX_COL 100

struct matrix { //store information of original matrix
    int row;
    int col;
    int mat[MAX_ROW][MAX_COL];
} inputMatrix;

struct dp { //store information for dynamic programming
    int own;
    int sum;
    int parentRow;
};

struct dp dp[MAX_ROW][MAX_COL];

//function prototype
void readFileAndOthers();
void calCost();
struct dp findCheap(int leftTop, int left, int leftBottom);
int getCheapRow(int col);
void printCheapPath(int startRow, int col);

void checkMatrix();
void printDp();

FILE* outFile = NULL;

int main() {
    readFileAndOthers();
}


/*
*
* Function Name : readFileAndOthers()
* Return value : nothing
* Summary of Function :
*   This function is for read input file and set outputFile for other functions.
*   It read the information of file and call the other functions to use them.
*
*/
void readFileAndOthers() {
    FILE* myFile = NULL;
    myFile = fopen(INPUT, "r");
    if (myFile == NULL) {
        printf("Input File could not open!\n");
        exit(1);
    }

    outFile = fopen(OUTPUT, "w"); //prepare output file to use it later
    if (outFile == NULL) {
        printf("Output File could not open!\n");
        exit(1);
    };

    //checkMatrix() is just for test
    while (fscanf(myFile, "%d %d", &inputMatrix.row, &inputMatrix.col) != EOF) {
        for (int i = 0; i < inputMatrix.row; i++) {
            for (int j = 0; j < inputMatrix.col; j++) {
                fscanf(myFile, "%d", &inputMatrix.mat[i][j]); //store each integer to each cell
            }
        }
        //checkMatrix();
        calCost(); //to get each cost of cell
    }

    fclose(myFile);
    fclose(outFile);
}


/*
*
* Function Name : checkMatrix()
* Return value : nothing
* Summary of Function :
*   This function is to check the numbers in matrix.
*   It prints each integer in cells, but used for just test.
*
*/
void checkMatrix() {
    printf("\nCheck Matrix\n");
    for (int i = 0; i < inputMatrix.row; i++) {
        for (int j = 0; j < inputMatrix.col; j++) {
            printf(" %d ", inputMatrix.mat[i][j]);
        }
        printf("\n");
    }
}


/*
*
* Function Name : calCost()
* Return value : nothing
* Summary of Function :
*   This function is for calculate the cost of visit each cell.
*   We can traveling only horizontal or diagonal, so cell[i][j] 's cost is depends on cell[i-1][j-1], cell[i][j-1], cell[i+1][j-1], choose the minimum cost of these cells and add cell[i][j]'s own cost.
*   And the first and last rows are considered adjacent, so if i is first row, then i-1 is last row, and if i is last row, then i+1 is first row.
*   Also, the first column of every row, it doesn't have last column, so their cost is only themselves.
*
*/
void calCost() {

    int row = inputMatrix.row;
    int col = inputMatrix.col;

    for (int i = 0; i < row; i++) { //init first column to themselves
        dp[i][0].own = inputMatrix.mat[i][0];
        dp[i][0].sum = inputMatrix.mat[i][0];
        dp[i][0].parentRow = -1;
    }

    //printDp() is just for test
    struct dp result;
    for (int c = 1; c < col; c++) {
        for (int r = 0; r < row; r++) {
            dp[r][c].own = inputMatrix.mat[r][c];
            if (r == 0) { // if it is first row
                result = findCheap(dp[row - 1][c - 1].sum, dp[r][c - 1].sum, dp[r + 1][c - 1].sum);

            }
            else if (r == row - 1) { // if it is last row
                result = findCheap(dp[r - 1][c - 1].sum, dp[r][c - 1].sum, dp[0][c - 1].sum);
            }
            else { 
                result = findCheap(dp[r - 1][c - 1].sum, dp[r][c - 1].sum, dp[r + 1][c - 1].sum);
            }
            dp[r][c].sum = result.sum + dp[r][c].own;
            dp[r][c].parentRow = r + result.parentRow;

            if (dp[r][c].parentRow == row) { //if it was last row and parentRow is it's lower row, go to first row 
                dp[r][c].parentRow = 0;
            }
            else if (dp[r][c].parentRow == -1) { //if it was first row and parentRow is it's upper row, go to last row 
                dp[r][c].parentRow = row - 1;
            }
        }
    }
    //printDp();

    int cheapRow = getCheapRow(col - 1);
    printCheapPath(cheapRow, col);
    printf("\n");
    fprintf(outFile, "\n");
}


/*
* Function Name : findCheap(int leftTop, int left, int leftBottom)
* Return value : struct dp
* Summary of Function :
*   This function is for find Cheap cell(choose parent row).
*   if,
*       leftTop < left, leftTop < leftBottom : leftTop
*       leftBottom <= leftTop < left : leftBottom
*       left <= leftTop, left < leftBottom : left
*       leftBottom <= left <= leftTop : leftBottom
* 
*/
struct dp findCheap(int leftTop, int left, int leftBottom) {
    struct dp temp;
    if (leftTop < left) {
        if (leftTop < leftBottom) {
            temp.sum = leftTop;
            temp.parentRow = -1;
        }
        else {
            temp.sum = leftBottom;
            temp.parentRow = 1; // It returns leftBottom when leftTop==leftBottom too.
        }
    }
    else {
        if (left < leftBottom) {
            temp.sum = left;
            temp.parentRow = 0;
        }
        else {
            temp.sum = leftBottom;
            temp.parentRow = 1;
        }
    }

    return temp;
}


/*
* 
* Function Name : getCheapRow(int col)
* Return value : int
* Summary of Function :
*   This function is to get the row that its last column is the cheapest.
*
*/
int getCheapRow(int col) {
    int min = INF;
    int minIdx = -1;
    for (int i = 0; i < inputMatrix.row; i++) {
        if (dp[i][col].sum < min) {
            min = dp[i][col].sum;
            minIdx = i;
        }
    }
    
    return minIdx;
}


/*
*
* Function Name : printCheapPath(int startRow, int col)
* Return value : nothing
* Summary of Function :
*   This function is to get cheapest way path and print it.
*   Start with startRow that getCheapRow()'s result.
*   And store each cell's parent row's own cost in each cell.
*   So, when the store is finish, print the path and total cost(cheapest cost).
*
*/
void printCheapPath(int startRow, int col) {
    int cost[MAX_COL] = { 0, };
    int row = startRow;
    cost[col - 1] = dp[startRow][col - 1].own;
    for (int i = col - 2; i >= 0; i--) {
        //printf("%dth : ", i);
        int parentRow = dp[row][i + 1].parentRow;
        //printf(" %d ", parentRow);
        cost[i] = dp[parentRow][i].own;
        //printf(" %d \n", dp[parentRow][i].own);
        row = parentRow;

    }

    for (int i = 0; i < col; i++) {
        printf("%d ", cost[i]);
        fprintf(outFile, "%d ", cost[i]);
    }
    printf("\n%d", dp[startRow][col - 1].sum);
    fprintf(outFile, "\n%d", dp[startRow][col - 1].sum);
}


/*
*
* Function Name : printDp()
* Return value : nothing
* Summary of Function :
*   This function is to check the dynamic programming table.
*   It prints each integer in cells, but used for just test.
*
*/
void printDp() {
    printf("\nprint DP\n");
    for (int i = 0; i < inputMatrix.row; i++) {
        for (int j = 0; j < inputMatrix.col; j++) {
            printf("\t%d", dp[i][j].parentRow);
        }
        printf("\n");
    }
    printf("-----------------\n");
}