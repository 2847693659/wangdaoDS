#include <iostream>

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;//���ڽӾ���洢��ͼ

typedef struct ArcNode {
    int adjvex;//�û���ָ��Ķ����λ��
    struct ArcNode *nextarc;//ָ����һ������ָ��
} ArcNode;//�߱���
typedef struct VNode {
    VertexType data;//������Ϣ
    ArcNode *firstarc;//ָ���һ�������ö���Ļ���ָ��
} VNode, AdjList[MaxVertexNum];//�������
typedef struct {
    AdjList vertices;//�����
    int vexnum, arcnum;//ͼ�Ķ������ͻ���
} ALGraph;//���ڽӱ�洢��ͼ

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

typedef struct {
    int data[MaxVertexNum];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue &Q) {
    Q.rear = Q.front = 0;
}

bool QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q, int x) {
    if ((Q.rear + 1) % MaxVertexNum == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxVertexNum;
    return true;
}

bool DeQueue(SqQueue &Q, int &x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxVertexNum;
    return true;
}


int FirstNeighbor(ALGraph G, int v) {

}

int NextNeighbor(ALGraph G, int v, int w) {

}

//02.�����һ���㷨���ж�һ������ͼG�Ƿ�Ϊһ����������һ���������㷨����true�����򷵻�false
//һ������ͼG��һ�����������ǣ�G�������޻�·����ͨͼ����n-1���ߵ���ͨͼ��������ú�����Ϊ�ж�����������ͨ���ж��������ܷ����ȫ��������ʵ�֡����Բ���������������㷨�ڱ���ͼ�Ĺ�����ͳ�ƿ��ܷ��ʵ��Ķ�������ͱߵ���������һ�α������ܷ��ʵ�n�������n-1���ߣ���ɶ϶���ͼ��һ������
void DFS(ALGraph &G, int v, int &Vnum, int &Enum, bool visited[]) {//������ȱ���ͼG��ͳ�Ʒ��ʹ��Ķ������ͱ�����ͨ��Vnum��Enum����
    visited[v] = true;
    Vnum++;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        Enum++;
        if (!visited[w])
            DFS(G, w, Vnum, Enum, visited);
    }
}

bool isTree(ALGraph &G) {
    bool visited[MaxVertexNum];
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    int Vnum = 0, Enum = 0;//��¼�������ͱ���
    DFS(G, 1, Vnum, Enum, visited);
    if (Vnum == G.vexnum && Enum == 2 * (G.vexnum - 1))//������������
        return true;
    else
        return false;
}


//03.д��ͼ�������������DFS�㷨�ķǵݹ��㷨��ͼ�����ڽӱ���ʽ��
void DFS_Non_RC(ALGraph &G, int v) {//�Ӷ���v��ʼ�����������������һ�α���һ����ͨ���������ж���
    bool visited[MaxVertexNum];
    int w;//�������
    SqStack S;
    InitStack(S);
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    Push(S, v);
    visited[v] = true;
    while (!StackEmpty(S)) {
        int k;
        Pop(S, k);//ջ���˳�һ������
//      visit(k);//�ȷ��ʣ��ٽ����ӽ����ջ
        for (w = FirstNeighbor(G, k); w >= 0; w = NextNeighbor(G, k, w)) {//k�����ڽӵ�
            if (!visited[w]) {
                Push(S, w);
                visited[w] = true;
            }
        }
    }
}


//04.�ֱ���û���������ȱ����͹�����ȱ����㷨�б����ڽӱ�ʽ�洢������ͼ���Ƿ�����ɶ���vi������vj��·����i��j����ע�⣬�㷨���漰��ͼ�Ļ������������ڴ˴洢�ṹ��ʵ�֡�
int visited1[MaxVertexNum] = {0};
bool can_reach = false;

void DFS1(ALGraph G, int i, int j) {
    if (i == j) {
        can_reach = true;
        return;
    }
    visited1[i] = 1;
    for (int p = FirstNeighbor(G, i); p >= 0; p = NextNeighbor(G, i, p)) {
        if (!visited1[p] && !can_reach)
            DFS1(G, p, j);
    }
}

void BFS1(ALGraph G, int i, int j) {
    if (i == j) {
        can_reach = true;
        return;
    }
    SqQueue Q;
    InitQueue(Q);
    visited1[i] = 1;
    EnQueue(Q, i);
    while (!QueueEmpty(Q)) {
        int k;
        DeQueue(Q, k);
        visited1[k] = 1;
        for (int p = FirstNeighbor(G, k); p >= 0; p = NextNeighbor(G, k, p)) {
            if (p == j) {
                can_reach = true;
                return;
            }
            if (!visited1[p]) {
                EnQueue(Q, p);
                visited1[p] = 1;
            }
        }
    }
}


//05.����ͼ���ڽӱ��ʾ�����һ���㷨������Ӷ���Vi������Vj�����м�·����
//ѭ��vi��ÿһ���߱��㣬��ÿһ���߱���ݹ��ҵ�vj�ļ�·����ע�������Ǽ�·����������ÿ�εݹ�һ�ξͰ�visited[�շ��ʹ��Ľ��]��Ϊ1����ֹ���ֻ�·�����ڱ���ѭ�����Ҳ�����vj�ļ�·�������轫visited[�շ��ʹ��Ľ��]�ָ�Ϊ0���Ա��´�ѭ��ʹ��
int d = 0;
int visited2[MaxVertexNum] = {0};
int path[MaxVertexNum] = {0};

void FindPath(ALGraph G, int i, int j) {
    path[d] = i;//����ǰ������ӵ�·����
    d++;//·��������1
    visited2[i] = 1;//���ѷ��ʱ��
    if (i == j) {//�ҵ�һ��·�������
        printf(path[]);//���·���ϵĽ��
        d = 0;
        for (int k = 0; k < MaxVertexNum; k++)
            path[k] = 0;
    }
    ArcNode *p = G.vertices[i].firstarc;//pָ��i�ĵ�һ�����ڵ�
    while (p != NULL) {
        int w = p->adjvex;
        if (visited2[w] == 0)//������wδ���ʣ��ݹ������
            FindPath(G, w, j);
        p = p->nextarc;//pָ��i����һ�����ڵ�
    }
    visited2[i] = 0;//�ָ�������ʹ�ö��������ʹ��
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
