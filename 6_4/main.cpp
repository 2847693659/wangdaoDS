#include <iostream>

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

typedef struct ArcNode1 {
    int adjvex;
    struct ArcNode1 *nextarc;
} ArcNode1;
typedef struct VNode {
    VertexType data;
    ArcNode1 *firstarc;
} VNode, AdjList[MaxVertexNum];
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

typedef struct {
    int data[MaxVertexNum];
    int top;
} SqStack;

void InitStack(SqStack &S) {
    S.top = -1;
}

bool StackEmpty(SqStack S) {
    if (S.top == -1)
        return true;
    else
        return false;
}

bool Push(SqStack &S, int x) {
    if (S.top == MaxVertexNum - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, int &x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

int FirstNeighbor(ALGraph G, int v) {

}

int NextNeighbor(ALGraph G, int v, int w) {

}

//06.��˵������DFS���ʵ�������޻�ͼ��������
bool visited[MaxVertexNum];
int time1;
int finishTime[MaxVertexNum];

void DFS(ALGraph G, int v) {
    visited[v] = true;
//    visit(v);
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w])
            DFS(G, w);
    }
    time1 = time1 + 1;
    finishTime[v] = time1;
}

void DFSTraverse(ALGraph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    time1 = 0;
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i])
            DFS(G, i);
    }
}

//��⣺ÿ���˳��ݹ�ʱ��ջ��������DFS�㷨�����������У��ڶ����˳��ݹ�ջǰ�����
void DFS1(ALGraph G, int v, SqStack &S) {
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w])
            DFS1(G, w, S);
    }
    Push(S, v);
}

void DFSTraverse1(ALGraph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    SqStack S;
    InitStack(S);
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i])
            DFS1(G, i, S);
    }
    int k;
    while (!StackEmpty(S)) {
        Pop(S, k);
        printf("%d", k);
    }
}


//10.(2)��Ա��е����ݣ���ƺ������ʽ�洢�ṹ���Ա�����е���·״̬��Ϣ��LSI����Ҫ�������ʽ�洢�ṹ���������Ͷ��壬��������Ӧ�����ʽ�洢�ṹʾ��ͼ��ʾ��ͼ�пɽ���ID��ʶ��㣩��
typedef struct {
    unsigned int ID, IP;
} LinkNode;//Link�Ľṹ
typedef struct {
    unsigned int Prefix, Mask;
} NetNode;//Net�Ľṹ
typedef struct ArcNode {
    int Flag;//Flag=1ΪLink,Flag=2ΪNet
    union {
        LinkNode LNode;
        NetNode NNode;
    } LinkORNet;
    unsigned int Metric;
    struct ArcNode *next;
} ArcNode;//�����
typedef struct HNode {
    unsigned int RouterID;
    ArcNode *LN_link;
    struct HNode *next;
} HNode;//��ͷ���


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
