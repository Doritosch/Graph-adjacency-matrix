#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//인접리스트 구조체
typedef struct Graphlist {
	int V;
	int E;
	struct GraphNode** Adj;
} Graphlist;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

//인접행렬 구조체
typedef struct Graph {
	int V;	//꼭짓점 개수
	int E;	//모서리 개수
	int** Adj;	//행렬
}Graph;

//행렬 초기화하는 함수
Graph * AdjMatrix(int v, int e)	{
	Graph * G = (Graph*)malloc(sizeof(Graph));

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

//행렬에 무방향 삽입하는 함수
Graph* insert_undirect(Graph * G, int u, int v) {
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

//인접행렬 출력하는 함수
void print_adj_mat(Graph * G) {
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

//인접리스트 초기화하는 함수
Graph* AdjList(int v, int e) {
	Graphlist* G = (Graphlist*)malloc(sizeof(Graphlist));
	if (!G) {
		printf("Memory Error!!");
		exit(0);
	}
	G->V = v;
	G->E = e;
	G->Adj = (GraphNode**)malloc(G->V * sizeof(GraphNode*));
	for (int i = 0; i < G->V; i++) {
		G->Adj[i] = (Graphlist*)malloc(sizeof(Graphlist));
		G->Adj[i]->vertex = i;
		G->Adj[i]->link = NULL;
	}
	return G;
}

//인접리스트에 무방향 인서트하는 함수
Graph* insert_Node(Graphlist* G,int u,int v) {
	GraphNode* temp1;
	GraphNode* temp2;
	GraphNode* temp3; //중복확인용 노드

	temp3 = (GraphNode*)malloc(sizeof(GraphNode));
	temp3 = G->Adj[u]->link;	//그래프 행의 링크를 받아옴
	while (temp3 != NULL) {		//노드가 NULL이 아닐때 까지 
		if (temp3->vertex == v) {	//중복이면 함수 호출
			insert_Node(G, (rand() % G->V), (rand() % G->V));
			return;
		}
		//다음 노드로 이동
		temp3 = temp3->link;
	}
	//free
	free(temp3);

		printf("\n Reading Edges(%d, %d) : ",u,v);

		//크기에 맞지않는 u,v 호출시 예외처리
		if (u >= G->V || v >= G->V) {
			printf(" No such vertex!!\n");
			exit(0);
		}
		else {		//아니면 Edge(u,v)
			temp1 = (GraphNode*)malloc(sizeof(GraphNode));
			temp1->vertex = v;
			temp1->link = G->Adj[u]->link;
			G->Adj[u]->link = temp1;
					//Edge(v,u)
			printf(" Insert Edges(%d, %d) ", u, v);
			temp2 = (GraphNode*)malloc(sizeof(GraphNode));
			temp2->vertex = u;
			temp2->link = G->Adj[v]->link;
			G->Adj[v]->link = temp2;
			printf(" Insert Edges(%d, %d)  \n", v, u);
		}
	return G;
}
//인접리스트 삭제하는 함수
void deleteList(Graphlist* G) {
	GraphNode* auxiliaryNode;
	GraphNode* iterator;
	for (int i = 0; i < G->V; i++) {
		//행의 처음 노드 받아오고
		iterator = G->Adj[i];
		//iterator가 NULL 일때까지
		while (iterator) {
			auxiliaryNode = iterator->link;		//iterator 다음노드를 auxiliaryNode에 저장
			free(iterator);	//iterator 지우기
			iterator = auxiliaryNode;	//auxiliaryNode를 iterator에 저장
		}
	}
	free(G->Adj);	//G->Adj 지운후 
	free(G);		//G 지움
	printf("Delete Graph");
	
}
//인접리스트 출력하는 함수
void print_adj_list(Graphlist* G)
{
	printf("\n Adjacency List of Graph\n");
	for (int i = 0; i < G->V; i++) {
		GraphNode* head = G->Adj[i];
		for (GraphNode* p = head; p != NULL; p = p->link)
			printf(" %d ->", p->vertex);
		printf(" NULL \n");
	}
	printf("\n");
}

int main() {
	srand((unsigned)time(NULL));
	//5~10사이 난수 
	int randomV = ((rand() % 6) + 5);
	int randomE = ((rand() % 6) + 5);

	printf("random V : %d\t", randomV);
	printf("random E : %d", randomE);
	//그래프 초기화
	Graphlist * G = AdjList(randomV, randomE);	
	
	for (int i = 0; i < randomE; i++) {	//0~ 난수까지 무방향 인서트함수에 삽입
		insert_Node(G, (rand() % randomV), (rand() % randomV));
	}
	//그래프 출력
	print_adj_list(G);
	//그래프 삭제
	deleteList(G);

	return 0;
}