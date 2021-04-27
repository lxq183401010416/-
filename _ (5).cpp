#include<stdio.h>
#include<stdlib.h>
#define Max 100
#define True 1
#define False 0
int visited[Max];
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode
{
	char data;
	ArcNode* firstarc;
}VNode, AdjList[Max];
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;
typedef struct node
{
	int data;
	struct node* next;
}QueuePtr;
typedef struct
{
	QueuePtr* rear;
	QueuePtr* front;
}Queue;
void InitQueue(Queue& Q)
{
	Q.front = (QueuePtr*)malloc(sizeof(QueuePtr));
	Q.rear = Q.front;
}
void EnQueue(Queue& Q, int a)
{
	QueuePtr* p;
	p = (QueuePtr*)malloc(sizeof(QueuePtr));
	p->data = a;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}
int DeQueue(Queue& Q)
{
	int result;
	QueuePtr* p;
	p = Q.front->next;
	result = p->data;
	Q.front->next = p->next;
	if (p == Q.rear) Q.front = Q.rear;
	return result;
}
int Empty(Queue& Q)
{
	if (Q.front == Q.rear)
		return 1;
	else return 0;
}
int weizhi(ALGraph& G, char a)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == a)
			break;
	}
	return i;
}
void create(ALGraph& G)
{
	ArcNode* p;
	int i, weizhi1, weizhi2;
	char a, b, c, d;
	scanf("%d\n", &G.vexnum);
	for (i = 0; i < G.vexnum; i++)
	{
		scanf("%c%c", &G.vertices[i].data, &b);
	}
	for (i = 0; i < G.vexnum; i++)
		G.vertices[i].firstarc = NULL;
	scanf("%d\n", &G.arcnum);
	for (i = 0; i < G.arcnum; i++)
	{
		scanf("%c%c%c%c", &a, &b, &c, &d);
		weizhi1 = weizhi(G, a);
		weizhi2 = weizhi(G, c);
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = weizhi2;
		p->nextarc = G.vertices[weizhi1].firstarc;
		G.vertices[weizhi1].firstarc = p;
	}
}
int FirstAdjvex(ALGraph G, int v)
{
	int result;
	if (G.vertices[v].firstarc == NULL) result = -1;
	else
		result = G.vertices[v].firstarc->adjvex;
	return result;
}
int NextAdjvex(ALGraph G, int v, int w)
{
	int result;
	ArcNode* p;
	if (v == w)
	{
		if (G.vertices[v].firstarc = NULL) result = -1;
		else result = G.vertices[v].firstarc->adjvex;
	}
	else
	{
		for (p = G.vertices[v].firstarc; p != NULL; p = p->nextarc)
		{
			if (p->adjvex == w)
			{
				if (p->nextarc == NULL) result = -1;
				else result = p->nextarc->adjvex;
			}
		}
	}
	return result;
}
void DFS(ALGraph G, int v)
{
	int w;
	visited[v] = True;
	printf("%c  ", G.vertices[v].data);
	for (w = FirstAdjvex(G, v); w >= 0; w = NextAdjvex(G, v, w))
	{
		if (visited[w] == 0) DFS(G, w);
	}
}
void shengduPrint(ALGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; v++) visited[v] = False;
	for (v = 0; v < G.vexnum; v++)
		if (visited[v] == False) DFS(G, v);
}
void guangduPrint(ALGraph G)
{
	int v, u, w;
	Queue Q;
	InitQueue(Q);
	for (v = 0; v < G.vexnum; v++)
		visited[v] = False;
	for (v = 0; v < G.vexnum; v++)
	{
		if (visited[v] == False)
		{
			visited[v] = True;
			printf("%c  ", G.vertices[v].data);
			EnQueue(Q, v);
			while (Empty(Q) == 0)
			{
				u = DeQueue(Q);
				for (w = FirstAdjvex(G, u); w >= 0; w = NextAdjvex(G, u, w))
				{
					if (visited[w] == False)
					{
						visited[w] = True;
						printf("%c  ", G.vertices[w].data);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}
int main()
{
	ALGraph G;
	create(G);
	shengduPrint(G);
	printf("\n");
	guangduPrint(G);
}







