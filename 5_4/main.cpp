#include <iostream>

#define MaxSize 100

typedef int ElemType;
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

//04.编程求以孩子兄弟表示法存储的森林的叶子结点数
int Leaves(CSTree T) {
    if (T == NULL)
        return 0;
    if (T->firstchild == NULL)//若结点无孩子，则该结点必是叶子
        return 1 + Leaves(T->nextsibling);//返回叶子结点和其兄弟子树中的叶子结点数
    else//孩子子树和兄弟子树中叶子数之和
        return Leaves(T->firstchild) + Leaves(T->nextsibling);
}


//05.以孩子兄弟链表为存储结构，请设计递归算法求树的深度
int Height(CSTree T) {
    int hc, hs;
    if (T == NULL)
        return 0;
    else {//否则，高度取子女高度+1和兄弟子树高度的大者
        hc = Height(T->firstchild);//第一子女树高
        hs = Height(T->nextsibling);//兄弟树高
        if (hc + 1 > hs)
            return hc + 1;
        else
            return hs;
    }
}


//06.已知一棵树的层次序列及每个结点的度，编写算法构造此树的孩子-兄弟链表
void createCSTree_Degree(CSTree T, ElemType e[], int degree[], int n) {
    CSNode *pointer[MaxSize];
    for (int i = 0; i < n; i++) {//初始化
        pointer[i]->data = e[i];
        pointer[i]->firstchild = pointer[i]->nextsibling = NULL;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        int d = degree[i];//结点i的度数
        if (d > 0) {
            k++;//k为子女结点序号
            pointer[i]->firstchild = pointer[k];//建立i与子女k间的链接
            for (int j = 2; j <= d; j++) {
                k++;
                pointer[k - 1]->nextsibling = pointer[k];
            }
        }
    }
    T = pointer[0];
    free(*pointer);
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
