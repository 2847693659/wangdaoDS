#include <iostream>

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;//以邻接矩阵存储的图

typedef struct ArcNode {
    int adjvex;//该弧所指向的顶点的位置
    struct ArcNode *nextarc;//指向下一条弧的指针
} ArcNode;//边表结点
typedef struct VNode {
    VertexType data;//顶点信息
    ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
} VNode, AdjList[MaxVertexNum];//顶点表结点
typedef struct {
    AdjList vertices;//顶点表
    int vexnum, arcnum;//图的顶点数和弧数
} ALGraph;//以邻接表存储的图

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

//02.试设计一个算法，判断一个无向图G是否为一棵树。若是一棵树，则算法返回true，否则返回false
//一个无向图G是一棵树的条件是，G必须是无回路的连通图或有n-1条边的连通图。这里采用后者作为判断条件。对连通的判定，可用能否遍历全部顶点来实现。可以采用深度优先搜索算法在遍历图的过程中统计可能访问到的顶点个数和边的条数，若一次遍历就能访问到n个顶点和n-1条边，则可断定此图是一棵树。
void DFS(ALGraph &G, int v, int &Vnum, int &Enum, bool visited[]) {//深度优先遍历图G，统计访问过的顶点数和边数，通过Vnum和Enum返回
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
    int Vnum = 0, Enum = 0;//记录顶点数和边数
    DFS(G, 1, Vnum, Enum, visited);
    if (Vnum == G.vexnum && Enum == 2 * (G.vexnum - 1))//符合树的条件
        return true;
    else
        return false;
}


//03.写出图的深度优先搜索DFS算法的非递归算法（图采用邻接表形式）
void DFS_Non_RC(ALGraph &G, int v) {//从顶点v开始进行深度优先搜索，一次遍历一个连通分量的所有顶点
    bool visited[MaxVertexNum];
    int w;//顶点序号
    SqStack S;
    InitStack(S);
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    Push(S, v);
    visited[v] = true;
    while (!StackEmpty(S)) {
        int k;
        Pop(S, k);//栈中退出一个顶点
//      visit(k);//先访问，再将其子结点入栈
        for (w = FirstNeighbor(G, k); w >= 0; w = NextNeighbor(G, k, w)) {//k所有邻接点
            if (!visited[w]) {
                Push(S, w);
                visited[w] = true;
            }
        }
    }
}


//04.分别采用基于深度优先遍历和广度优先遍历算法判别以邻接表方式存储的有向图中是否存在由顶点vi到顶点vj的路径（i≠j）。注意，算法中涉及的图的基本操作必须在此存储结构上实现。
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


//05.假设图用邻接表表示，设计一个算法，输出从顶点Vi到顶点Vj的所有简单路径。
//循环vi的每一个边表结点，对每一个边表结点递归找到vj的简单路径，注意由于是简单路径，所以在每次递归一次就把visited[刚访问过的结点]置为1，防止出现回路，若在本次循环中找不到到vj的简单路径，则需将visited[刚访问过的结点]恢复为0，以便下次循环使用
int d = 0;
int visited2[MaxVertexNum] = {0};
int path[MaxVertexNum] = {0};

void FindPath(ALGraph G, int i, int j) {
    path[d] = i;//将当前顶点添加到路径中
    d++;//路径长度增1
    visited2[i] = 1;//置已访问标记
    if (i == j) {//找到一条路径则输出
        printf(path[]);//输出路径上的结点
        d = 0;
        for (int k = 0; k < MaxVertexNum; k++)
            path[k] = 0;
    }
    ArcNode *p = G.vertices[i].firstarc;//p指向i的第一个相邻点
    while (p != NULL) {
        int w = p->adjvex;
        if (visited2[w] == 0)//若顶点w未访问，递归访问它
            FindPath(G, w, j);
        p = p->nextarc;//p指向i的下一个相邻点
    }
    visited2[i] = 0;//恢复环境，使该顶点可重新使用
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
