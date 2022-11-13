#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10

typedef struct Graph {
	int V;	//������ ����
	int E;	//�𼭸� ����
	int** Adj;	//���
}Graph;


Graph* AdjMatrix(int v, int e)
{
	Graph* G = (Graph*)malloc(sizeof(Graph));

	if (!G) {
		printf("Memory NULL");
		return;
	}

	G->V = v;	//������ ���� ����
	G->E = e;	//�𼭸� ���� ����
	G->Adj = (int**)malloc(sizeof(int*) * G->V);	//��� ũ�� �Ҵ�

	for (int i = 0; i < G->V; i++) {
		G->Adj[i] = malloc(sizeof(int) * G->V);		//��� �����
	}
	for (int i = 0; i < G->V; i++) {
		for (int j = 0; j < G->V; j++) {
			G->Adj[i][j] = 0;			//��� �ʱ�ȭ 
		}
	}

	return G;
}
Graph* insert_undirect(Graph* G,int u, int v)
{
	//u = �� v = ��
	
	
		
		if (u >= G->V || v >= G->V) {	//���� ������ �� �� ���� ���� ũ�� ����
			printf(" No such vertex!!");
			exit(0);
		}
		if (G->Adj[u][v] == 1) {
			insert_undirect(G, (rand() % G->V), (rand() % G->V));	//�ߺ��̸� �ݺ�
		}
		else {		//�ƴϸ� ���, �� ����
			printf("\n Reading Edge  (u,v) : (%d,%d)", u, v);
			G->Adj[u][v] = 1;
			G->Adj[v][u] = 1;
		}
	return G;
}
//��� ����ϴ� �Լ�
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
	//5~10���� ���� 
	int randomV= ((rand() % 6) + 5);
	int randomE = ((rand() % 6) + 5);
	int v, e;
	int first;
	Graph* G = AdjMatrix(randomV,randomE);

	printf("random V : %d\t", randomV);
	printf("random E : %d", randomE);
	for (int i = 0; i < randomE; i++) {	//0~ �������� ������ �μ�Ʈ�Լ��� ����
		v = rand() % randomV;
		e = rand() % randomV;
		insert_undirect(G, v, e);
		if (i == 0) {
			first = v;
		}
	}

	int visited[SIZE];
	//��� ���
	print_adj_mat(G);
	DFS(G, first);
	return 0;
}