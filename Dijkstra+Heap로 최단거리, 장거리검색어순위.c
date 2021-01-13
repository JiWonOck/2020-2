#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ELEMENT 200
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 15 //������ ��
#define INF	1000000	/* ���Ѵ� (������ ���� ���) */

char *region_list[]={"��õ", "����", "����", "����", "õ��", "����", "����", "����", "����", "���", "�뱸", "����", "����", "����", "�λ�"};
int weight[MAX_VERTICES][MAX_VERTICES]={ //��Ʈ��ũ�� ���� ���
	{0, 26, INF, 124, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	{26, 0, 152, INF, 83, INF, 138, INF, INF, INF, INF, INF, INF, INF, INF},
	{INF, 152, 0, INF, INF, INF, INF, 85, INF, INF, INF, INF, INF, INF, INF},
	{124, INF, INF, 0, 66, INF, INF, INF, 37, INF, INF, INF, INF, INF, INF},
	{INF, 83, INF, 66, 0, 37, INF, INF, INF, INF, INF, INF, INF, INF, INF},
	{INF, INF	, INF, INF, 37, 0, 28, INF, INF, 25, INF, INF, INF, INF, INF},
	{INF, 138	, INF, INF, INF, 28, 0, 195, INF, INF, 120, INF, INF, INF, INF},
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

int distance[MAX_VERTICES];				//���� �������κ����� �ִ� ��� �Ÿ�
int found[MAX_VERTICES];				//�湮�� ���� ǥ��
int path[MAX_VERTICES][MAX_VERTICES];	//�ִܰŸ� �������� ��ġ�� ������ ����
int check[MAX_VERTICES];				//�� �������� ���� ������ ǥ��

void path_init(int path[][MAX_VERTICES]);		//path ������� �ʱ�ȭ
int find_index(char* s, char* list[]);			//������ �ε��� ��ȣ ��ȯ 
int choose(int distance[],int n,int found[]);	// �ִܰŸ��� �ִ� ������ ã�� �Լ�
void shortest_path(int start, int n);			//�ִ� ��� �˰���
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
	heap = create();		// ���� ����
	init(heap);				// �ʱ�ȭ
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
		printf("��Ÿ�%d�� �˻���: %s->%s\n", (i+1), start_copy, end_copy);
	}
	free(heap);
}

//path ������� �ʱ�ȭ
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

// �ִܰŸ��� �ִ� ������ ã�� �Լ�
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

//�ִ� ��� �˰���
void shortest_path(int start, int n) {
	int i,j,u,w;
	for(i=0; i<n; i++){//�ʱ�ȭ
		distance[i] = weight[start][i];
		found[i] = FALSE;
		check[i]=1;
		path[i][0] = start;
	}

	found[start] =TRUE;//���� ���� �湮 ǥ��
	distance[start] = 0;
	for(i=0; i<n-1; i++){
		u = choose(distance, n, found);
		found[u] = TRUE;
		for(w=0; w<n;w++){
			if(!found[w]){
				if(distance[u]+weight[u][w] < distance[w]){
					if(i==0){//ó������ ������ ������ ����
						path[w][check[w]] = u; //���ŵ� ��θ� ��� �迭�� ����
						check[w]++;
					}
					else{
						for(j=0; j<(check[u]+1); j++){//����� ��ŭ �ݺ�
							path[w][j] = path[u][j]; //��θ� ����
							path[w][j+1] = u; //���κп� �ڱ��ڽ��� ����
							check[w]++;
						}
					}
					distance[w] = distance[u] + weight[u][w];

				}
			}
		}
	}
}

// ���� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void init(HeapType* h) {
	h->heap_size = 0;
}

// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.distance > h->heap[i / 2].distance)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
element delete_max_heap(HeapType* h){
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].distance) < h->heap[child + 1].distance)
			child++;
		if (temp.distance >= h->heap[child].distance) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
