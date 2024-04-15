#include <iostream>

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;
typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph1;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;
typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

//04.写出从图的邻接表表示转换成邻接矩阵表示的算法
void Convert(ALGraph &G, int arcs[MaxVertexNum][MaxVertexNum]) {
    for (int i = 0; i < G.vexnum; i++) {//依次遍历各顶点表结点为头的边链表
        ArcNode *p = G.vertices[i].firstarc;//取出顶点i的第一条出边
        while (p != NULL) {//遍历边链表
            arcs[i][p->adjvex] = 1;
            p = p->nextarc;//取下一条出边
        }
    }
}



//06.【2021统考真题】已知无向连通图G由顶点集V和边集E组成，|E|>0，当G中度为奇数的顶点个数为不大于2的偶数时，G存在包含所有边且长度为|E|的路径（称为EL路径）。设图G采用邻接矩阵存储，类型定义如下：
#define MAXV 100
typedef struct {//图的定义
    int numVertices, numEdges;//图中实际的顶点数和边数
    char VerticesList[MAXV];//顶点表。MAXV为已定义常量
    int Edge[MAXV][MAXV];//邻接矩阵
} MGraph;

//请设计算法int IsExistEL(MGraph G)，判断G是否存在EL路径，若存在，则返回1，否则返回0。要求：
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
//(3)说明你所设计算法的时间复杂度和空间复杂度。
int IsExistEL(MGraph G) {
    int degree, count = 0;
    for (int i = 0; i < G.numVertices; i++) {
        degree = 0;
        for (int j = 0; j < G.numVertices; j++) {
            if (G.Edge[i][j] == 1)
                degree++;
        }
        if (degree % 2 == 1)
            count++;
    }
    if (count == 0 || count == 2)
        return 1;
    else
        return 0;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
