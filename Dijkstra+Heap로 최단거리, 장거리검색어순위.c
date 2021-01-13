#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ELEMENT 200
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 15 //정점의 수
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

char *region_list[]={"인천", "서울", "속초", "보령", "천안", "공주", "대전", "동해", "군산", "논산", "대구", "포항", "목포", "광주", "부산"};
int weight[MAX_VERTICES][MAX_VERTICES]={ //네트워크의 인접 행렬
	{0, 26, INF, 124, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	{26, 0, 152, INF, 83, INF, 138, INF, INF, INF, INF, INF, INF, INF, INF},
	{INF, 152, 0, INF, INF, INF, INF, 85, INF, INF, INF, INF, INF, INF, INF},
	{124, INF, INF, 0, 66, INF, INF, INF, 37, INF, INF, INF, INF, INF, INF},
	{INF, 83, INF, 66, 0, 37, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	{INF, INF, INF, INF, 37, 0, 28, INF, INF, 25, INF, INF, INF, INF, INF},
	{INF, 138, INF, INF, INF, 28, 0, 195, INF, INF, 120, INF, INF, INF, INF},
	{INF, INF, 85, INF, INF, INF, 195, 0, INF, INF, INF, 164, INF, INF, INF},
	{INF, INF, INF, 37, INF, INF, INF, INF, 0, 34, INF, INF, 128, INF, INF},
	{INF, INF, INF, INF, INF, 25, INF, INF, 34, 0, 137, INF, INF, 113, INF},
	{INF, INF, INF, INF, INF, INF, 120, INF, INF, 137, 0, INF, INF, 170, 88},
	{INF, INF, INF, INF, INF, INF, INF, 164, INF, INF, INF, 0, INF, INF, 93},
	{INF, INF, INF, INF, INF, INF, INF, INF, 128, INF, INF, INF, 0, 56, INF},
	{INF, INF, INF, INF, INF, INF, INF, INF, INF, 113, 170, INF, 56, 0, 197},
	{INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 88, 93, INF, 197, 0}};

typedef struct {
	char route[100];
	int distance;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

int distance[MAX_VERTICES];				//시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES];				//방문한 정점 표시
int path[MAX_VERTICES][MAX_VERTICES];	//최단거리 정점까지 거치는 노드들을 저장
int check[MAX_VERTICES];				//한 정점으로 가는 정점을 표시

void path_init(int path[][MAX_VERTICES]);		//path 인접행렬 초기화
int find_index(char* s, char* list[]);			//지역의 인덱스 번호 반환 
int choose(int distance[],int n,int found[]);	// 최단거리에 있는 정점을 찾는 함수
void shortest_path(int start, int n);			//최단 경로 알고리즘
HeapType* create();
void init(HeapType* h);
void insert_max_heap(HeapType* h, element item);
element delete_max_heap(HeapType* h);

void main(){
	int i, index_start, index_end;
	char str[100];
	char *start, *end, *start_copy, *end_copy;
	path_init(path);
	HeapType* heap;
	heap = create();		// 히프 생성
	init(heap);				// 초기화
	element e;
	element e_copy;
	
	while(gets(str)!=NULL){
		strcpy(e.route, str);
		start=strtok(str, "-");
		end=strtok(NULL, "-");
		
		index_start=find_index(start, region_list);
		index_end=find_index(end, region_list);
		shortest_path(index_start, MAX_VERTICES);
		printf("%d KM \n", distance[index_end]);
		
		e.distance = distance[index_end];
		insert_max_heap(heap, e);
	}

	for(i=0;i<3;i++){
		e_copy=delete_max_heap(heap);
		start_copy=strtok(e_copy.route, "-");
		end_copy=strtok(NULL, "-");
		printf("장거리%d위 검색어: %s->%s\n", (i+1), start_copy, end_copy);
	}
	free(heap);
}

//path 인접행렬 초기화
void path_init(int path[][MAX_VERTICES]){
	int i,j;
	for(i=0;i<MAX_VERTICES;i++)
	for(j=0;j<MAX_VERTICES;j++)
	path[i][j] = INF;
}

int find_index(char* s, char* list[]){
	int i, index=0;
	for(i=0; i<15;i++){
		if(strcmp(list[i], s)==0){
			index=i;
		}
	}
	return index;
}

// 최단거리에 있는 정점을 찾는 함수
int choose(int distance[],int n,int found[]){
	int i,min,minpos;
	min = INT_MAX;
	minpos = -1;

	for(i=0;i<n;i++)

	if(distance[i]<min && !found[i]){
		min = distance[i];
		minpos = i;
	}
	return minpos;
}

//최단 경로 알고리즘
void shortest_path(int start, int n) {
	int i,j,u,w;
	for(i=0; i<n; i++){//초기화
		distance[i] = weight[start][i];
		found[i] = FALSE;
		check[i]=1;
		path[i][0] = start;
	}

	found[start] =TRUE;//시작 정점 방문 표시
	distance[start] = 0;
	for(i=0; i<n-1; i++){
		u = choose(distance, n, found);
		found[u] = TRUE;
		for(w=0; w<n;w++){
			if(!found[w]){
				if(distance[u]+weight[u][w] < distance[w]){
					if(i==0){//처음에는 인접한 정점에 연결
						path[w][check[w]] = u; //갱신된 경로를 경로 배열에 저장
						check[w]++;
					}
					else{
						for(j=0; j<(check[u]+1); j++){//저장된 만큼 반복
							path[w][j] = path[u][j]; //경로를 갱신
							path[w][j+1] = u; //끝부분에 자기자신을 저장
							check[w]++;
						}
					}
					distance[w] = distance[u] + weight[u][w];

				}
			}
		}
	}
}

// 생성 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.distance > h->heap[i / 2].distance)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
element delete_max_heap(HeapType* h){
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].distance) < h->heap[child + 1].distance)
			child++;
		if (temp.distance >= h->heap[child].distance) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
