#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10

typedef struct Graph {
	int V;	//꼭짓점 개수
	int E;	//모서리 개수
	int** Adj;	//행렬
}Graph;


Graph* AdjMatrix(int v, int e)
{
	Graph* G = (Graph*)malloc(sizeof(Graph));

	if (!G) {
		printf("Memory NULL");
		return;
	}

	G->V = v;	//꼭짓점 개수 저장
	G->E = e;	//모서리 개수 저장
	G->Adj = (int**)malloc(sizeof(int*) * G->V);	//행렬 크기 할당

	for (int i = 0; i < G->V; i++) {
		G->Adj[i] = malloc(sizeof(int) * G->V);		//행렬 만들기
	}
	for (int i = 0; i < G->V; i++) {
		for (int j = 0; j < G->V; j++) {
			G->Adj[i][j] = 0;			//행렬 초기화 
		}
	}

	return G;
}
Graph* insert_undirect(Graph* G,int u, int v)
{
	//u = 행 v = 열
	
	
		
		if (u >= G->V || v >= G->V) {	//넣을 값들이 행 열 보다 값이 크면 종료
			printf(" No such vertex!!");
			exit(0);
		}
		if (G->Adj[u][v] == 1) {
			insert_undirect(G, (rand() % G->V), (rand() % G->V));	//중복이면 반복
		}
		else {		//아니면 출력, 값 삽입
			printf("\n Reading Edge  (u,v) : (%d,%d)", u, v);
			G->Adj[u][v] = 1;
			G->Adj[v][u] = 1;
		}
	return G;
}
//행렬 출력하는 함수
void print_adj_mat(Graph* G) {
	if (G->Adj == NULL) {
		printf("No Matrix exist!\n");
			return;
	}
	printf("\n Adjacency Matrix of Direct Graph\n");
		for (int u = 0; u < G->V; u++) {
			for (int v = 0; v < G->V; v++) {
				printf("%2d ", G->Adj[u][v]);
			}
			printf("\n");
		}
}

int visited[SIZE];

int DFS(Graph* G, int u) {
	visited[u] = 1;
	for (int i = 0; i < G->V; i++) {
		if (!visited[i] && G->Adj[u][i]) {
			printf("[%d] -> [%d]\n", u+1, i+1);
			DFS(G, i);
		}
	}
}
int main() {
	srand((unsigned)time(NULL));
	//5~10사이 난수 
	int randomV= ((rand() % 6) + 5);
	int randomE = ((rand() % 6) + 5);
	int v, e;
	int first;
	Graph* G = AdjMatrix(randomV,randomE);

	printf("random V : %d\t", randomV);
	printf("random E : %d", randomE);
	for (int i = 0; i < randomE; i++) {	//0~ 난수까지 무방향 인서트함수에 삽입
		v = rand() % randomV;
		e = rand() % randomV;
		insert_undirect(G, v, e);
		if (i == 0) {
			first = v;
		}
	}

	int visited[SIZE];
	//행렬 출력
	print_adj_mat(G);
	DFS(G, first);
	return 0;
}