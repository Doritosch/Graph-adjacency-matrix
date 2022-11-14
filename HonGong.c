#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//��������Ʈ ����ü
typedef struct Graphlist {
	int V;
	int E;
	struct GraphNode** Adj;
} Graphlist;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

//������� ����ü
typedef struct Graph {
	int V;	//������ ����
	int E;	//�𼭸� ����
	int** Adj;	//���
}Graph;

//��� �ʱ�ȭ�ϴ� �Լ�
Graph * AdjMatrix(int v, int e)	{
	Graph * G = (Graph*)malloc(sizeof(Graph));

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

//��Ŀ� ������ �����ϴ� �Լ�
Graph* insert_undirect(Graph * G, int u, int v) {
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

//������� ����ϴ� �Լ�
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

//��������Ʈ �ʱ�ȭ�ϴ� �Լ�
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

//��������Ʈ�� ������ �μ�Ʈ�ϴ� �Լ�
Graph* insert_Node(Graphlist* G,int u,int v) {
	GraphNode* temp1;
	GraphNode* temp2;
	GraphNode* temp3; //�ߺ�Ȯ�ο� ���

	temp3 = (GraphNode*)malloc(sizeof(GraphNode));
	temp3 = G->Adj[u]->link;	//�׷��� ���� ��ũ�� �޾ƿ�
	while (temp3 != NULL) {		//��尡 NULL�� �ƴҶ� ���� 
		if (temp3->vertex == v) {	//�ߺ��̸� �Լ� ȣ��
			insert_Node(G, (rand() % G->V), (rand() % G->V));
			return;
		}
		//���� ���� �̵�
		temp3 = temp3->link;
	}
	//free
	free(temp3);

		printf("\n Reading Edges(%d, %d) : ",u,v);

		//ũ�⿡ �����ʴ� u,v ȣ��� ����ó��
		if (u >= G->V || v >= G->V) {
			printf(" No such vertex!!\n");
			exit(0);
		}
		else {		//�ƴϸ� Edge(u,v)
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
//��������Ʈ �����ϴ� �Լ�
void deleteList(Graphlist* G) {
	GraphNode* auxiliaryNode;
	GraphNode* iterator;
	for (int i = 0; i < G->V; i++) {
		//���� ó�� ��� �޾ƿ���
		iterator = G->Adj[i];
		//iterator�� NULL �϶�����
		while (iterator) {
			auxiliaryNode = iterator->link;		//iterator ������带 auxiliaryNode�� ����
			free(iterator);	//iterator �����
			iterator = auxiliaryNode;	//auxiliaryNode�� iterator�� ����
		}
	}
	free(G->Adj);	//G->Adj ������ 
	free(G);		//G ����
	printf("Delete Graph");
	
}
//��������Ʈ ����ϴ� �Լ�
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
	//5~10���� ���� 
	int randomV = ((rand() % 6) + 5);
	int randomE = ((rand() % 6) + 5);

	printf("random V : %d\t", randomV);
	printf("random E : %d", randomE);
	//�׷��� �ʱ�ȭ
	Graphlist * G = AdjList(randomV, randomE);	
	
	for (int i = 0; i < randomE; i++) {	//0~ �������� ������ �μ�Ʈ�Լ��� ����
		insert_Node(G, (rand() % randomV), (rand() % randomV));
	}
	//�׷��� ���
	print_adj_list(G);
	//�׷��� ����
	deleteList(G);

	return 0;
}