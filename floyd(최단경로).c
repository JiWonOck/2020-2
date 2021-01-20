
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType *g)
{
	int i, j;
	printf("===============================\n");
	for (i = 0; i<g->n; i++) {
		for (j = 0; j<g->n; j++) {
			if (A[i][j] == INF)
				printf("  * ");
			else printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("===============================\n");
}

void floyd(GraphType* g)
{

	int i, j, k;
	for (i = 0; i<g->n; i++)
		for (j = 0; j<g->n; j++)
			A[i][j] = g->weight[i][j];
	printA(g);

	for (k = 0; k<g->n; k++) {
		for (i = 0; i<g->n; i++)
			for (j = 0; j<g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
		printA(g);
	}
}

int main(void)
{
	GraphType g = { 15,
	{{0, 26 , INF, INF, INF, 83, INF, INF, INF, 152, 138, INF, INF, INF, INF},
	 {26, 0, 124, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	 {INF, 124, 0, 37, INF, 66, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	 {INF, INF, 37, 0, 128, INF, INF, 34, INF, INF, INF, INF, INF, INF, INF},
	 {INF, INF, INF, 128, 0, INF, INF, INF, 56, INF, INF, INF, INF, INF, INF},
	 {83, INF, 66, INF, INF, 0, 37, INF, INF, INF, INF, INF, INF, INF, INF},
	 {INF, INF, INF, INF, INF, 37, 0, 25, INF, INF, 28, INF, INF, INF, INF},
	 {INF, INF, INF, 34, INF, INF, 25, 0, 113, INF, INF, 137, INF, INF, INF},
	 {INF, INF, INF, INF, 56, INF, INF, 113, 0, INF, INF, 170, INF, INF, 197},
	 {152, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, 85, INF, INF},
	 {138, INF, INF, INF, INF, INF, 28, INF, INF, INF, 0, 120, 195, INF, INF},
	 {INF, INF, INF, INF, INF, INF, INF, 137, 170, INF, 120, 0, INF, INF, 88},
	 {INF, INF, INF, INF, INF, INF, INF, INF, INF, 85, 195, INF, 0, 164, INF},
	 {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 164, 0, 93},
	 {INF, INF, INF, INF, INF, INF, INF, INF, 197, INF, INF, 88, INF, 93, 0}	}
	};
	floyd(&g);
	return 0;
}
