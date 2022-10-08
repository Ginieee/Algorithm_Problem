/*
* 
* Algorithm HW : Saving Ink
* Author : Kang Eojin(kaj1226@gachon.ac.kr)
* 
* Summary of Problem :
*	Susan likes to make a line drawing with ink. There're several dots on drawing paper.
*	Your job is to tell Susan how to connect the dots so as to minimize the amount of ink used.
*	Susan connects the dots by drawing straight lines between pairs, possibly lifting the pen between lines.
*	When Susan is done there must be a sequence of connected lines from any dot to any other dot.
* 
* Info of INPUT : 
*	The input begins with a single positive integer on a line by itself indicating the number of dots(0<n<30) on drawing paper.
*	For each dots, a line follows; each following line contains two real numbers indicating the (x,y) coordinates of the dots.
* 
* Info of OUTPUT :
*	Your program must print a single real number to two decimal places:
*		the minimum total length of ink lines that can connect all the dots.
* 
*  Summary of Code :
*	I use the kruskal algorithm to solve this problem. Also use findParent() and unionParent() that Union-Find algorithm for kruskal.
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INPUT "input.txt"
#define INPUT2 "input2.txt"
#define INPUT3 "input3.txt"
#define MAXNUM 29

struct DOT {
	double x;
	double y;
};

struct EDGE {
	int u;
	int v;
	double w;
};

int dotNum = 0; //the number of dots
int edgeNum = 0; //the number of edges
struct DOT dot[MAXNUM];
int parent[MAXNUM]; //to use for union-find algorithm
struct EDGE* edgeStart = NULL; //to store the start of edges

//function prototype
void readFile();
void printInput();
void makeEdge();
void printEdge();
int compare(const void* a, const void* b);
void kruskal();
int findParent(int x);
void unionParent(int u, int v);


int main() {
	readFile();
	makeEdge();
	kruskal();
}

/*
* Function : readFile()
* 
* INPUT : nothing
* RETURN : nothing
* 
* Summary of function :
*	This function is to read input file.
*	It reads input file and store the number of dots, and each information of dots.
* 
*	printInput() is just for test.
*/
void readFile() {
	FILE* myFile = NULL;
	myFile = fopen(INPUT, "r");
	if (myFile == NULL) { //defensive coding
		printf("Input File Open is failed!\n");
		exit(1);
	}

	fscanf(myFile, "%d", &dotNum); //read and store the number of dots
	for (int i = 0; i < dotNum; i++) {
		fscanf(myFile, "%lf %lf", &dot[i].x, &dot[i].y); //read and store the information of each dots
		parent[i] = i; //set that dot's parent to itself. It will used for union-find algorithm
	}

	//printInput();

	fclose(myFile);
}


/*
* Function : printInput()
*
* INPUT : nothing
* RETURN : nothing
*
* Summary of function :
*	This function is to print the information of input file.
*	It is just used for test.
*/
void printInput() {
	printf("%d\n", dotNum); //print the number of dots
	for (int i = 0; i < dotNum; i++) {
		printf("%.1lf %.1lf \n", dot[i].x, dot[i].y); //print each information of dot
	}
}


/*
* Function : makeEdge()
*
* INPUT : nothing
* RETURN : nothing
*
* Summary of function :
*	This function is to make edge with every dots.
*	The number of edges is (number of dots * (number of dots - 1)) cause there is no edge with same node to same node.
*	It store each edge's start node, end node, weight(distance).
*	Also it uses linked array to store these edges.
* 
*	printEdge() is just for test.
*/
void makeEdge() {
	edgeNum = dotNum * (dotNum - 1); //the number of edges to be created
	struct EDGE* edge = (struct EDGE*)malloc(sizeof(struct EDGE) * edgeNum); //make linked array to store each edges.

	int k = 0;
	for (int u = 0; u < dotNum; u++) {
		for (int v = 0; v < dotNum; v++) {
			if (u == v) continue; //there is no edge with same node to same node.
			edge[k].u = u;
			edge[k].v = v;
			edge[k].w = sqrt(pow(dot[u].x - dot[v].x, 2) + pow(dot[u].y - dot[v].y, 2));
			k++;
		}
	}

	edgeStart = edge; //to use these edges in other functions, store the start address to edgeStart

	//printEdge();
}


/*
* Function : printEdge()
*
* INPUT : nothing
* RETURN : nothing
*
* Summary of function :
*	This function is to print edges.
*	It is used just for test.
*/
void printEdge() {
	struct EDGE* n;
	n = edgeStart;
	for (int k = 0; k < edgeNum; k++) {
		printf("(%d,%d)%.2lf\n", n[k].u, n[k].v, n[k].w);
	}
}


/*
* Function : compare(const void* a, const void* b)
*
* INPUT : 
*	const void* a : the first value to compare and sort
*	const void* b : the second value to compare and sort
* RETURN : 
*	int = it is used for qsort() to sorting values. It means used for quick sort.
*
* Summary of function :
*	This function is to compare values to used for qsort().
*	It is used for sorting nondecreasing order of w(distance) values in each nodes.
*/
int compare(const void* a, const void* b) {
	struct EDGE edge1 = *(struct EDGE*)a;
	struct EDGE edge2 = *(struct EDGE*)b;

	if (edge1.w < edge2.w) {
		return -1;
	}

	if (edge1.w > edge2.w) {
		return 1;
	}

	return 0;
}


/*
* Function : kruskal()
*
* INPUT : nothing
* RETURN : nothing
*
* Summary of function :
*	This function is for Kruskal's algorithm.
*	First, It made empty MST set.
*	Second, it sorting the edges by nondecreasing order of w values in each nodes using qsort().
*	And with that sorted edges, start with first edge, if that edge's start and end node's parents are not same(it they are not same set), add it to MST and union that set.
*	With this, add that added edge's cost(distance) to the total(total length) value.
*	Repeat upper step while there are dotNum-1 number of edges in MST.
*	Finally, print that total value.
*	
*	printEdge() is just for test.
*/
void kruskal() {
	int* mst = (int*)malloc(sizeof(int) * dotNum - 1); //create empty MST
	int mstNum = 0;
	double total = 0.0;

	qsort(edgeStart, edgeNum, sizeof(edgeStart[0]), compare); //sorting edges by nondecreasing order with each edge's weight(distance)

	//printEdge();

	int i = 0;
	while (mstNum < dotNum - 1) {
		int u = edgeStart[i].u;
		int v = edgeStart[i].v;
		if (findParent(u) != findParent(v)) { //If they are not same set, add to MST and union them.
			mst[mstNum++] = i;
			total += edgeStart[i].w;
			unionParent(u, v);
		}
		i++;
	}
	printf("%.2lf\n", total); //print a single real number to two decimal places

	free(mst);
	free(edgeStart);
}


/*
* Function : findParent(int x)
*
* INPUT :
*	int x : The index of dot that used for find parent.
* RETURN : 
*	int : The index of parent of dot x.
*
* Summary of function :
*	This function is to find the parent of dot x.
*	If that parent is itself, just return it.
*	But if the parent is not itself, find its real parent through recursive execution.
*/
int findParent(int x) {
	if (parent[x] == x) {
		return x;
	}
	else {
		parent[x] = findParent(parent[x]);
	}
}


/*
* Function : unionParent(int u, int v)
*
* INPUT :
*	int u : The first node(set) that will union
*	int v : The second node(set) that will union
* RETURN : nothing
*
* Summary of function :
*	This function is for union two sets to one.
*	It find parent of each dots, and union that with the smaller parent.
*/
void unionParent(int u, int v) {
	int parentU = findParent(u);
	int parentV = findParent(v);
	if (parentU < parentV) {
		parent[v] = parent[u];
	}
	else {
		parent[u] = parent[v];
	}
}