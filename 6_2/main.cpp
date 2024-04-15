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

//04.д����ͼ���ڽӱ��ʾת�����ڽӾ����ʾ���㷨
void Convert(ALGraph &G, int arcs[MaxVertexNum][MaxVertexNum]) {
    for (int i = 0; i < G.vexnum; i++) {//���α������������Ϊͷ�ı�����
        ArcNode *p = G.vertices[i].firstarc;//ȡ������i�ĵ�һ������
        while (p != NULL) {//����������
            arcs[i][p->adjvex] = 1;
            p = p->nextarc;//ȡ��һ������
        }
    }
}



//06.��2021ͳ�����⡿��֪������ͨͼG�ɶ��㼯V�ͱ߼�E��ɣ�|E|>0����G�ж�Ϊ�����Ķ������Ϊ������2��ż��ʱ��G���ڰ������б��ҳ���Ϊ|E|��·������ΪEL·��������ͼG�����ڽӾ���洢�����Ͷ������£�
#define MAXV 100
typedef struct {//ͼ�Ķ���
    int numVertices, numEdges;//ͼ��ʵ�ʵĶ������ͱ���
    char VerticesList[MAXV];//�����MAXVΪ�Ѷ��峣��
    int Edge[MAXV][MAXV];//�ڽӾ���
} MGraph;

//������㷨int IsExistEL(MGraph G)���ж�G�Ƿ����EL·���������ڣ��򷵻�1�����򷵻�0��Ҫ��
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�
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
