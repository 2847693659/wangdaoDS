#include <iostream>

//05.写出折半查找的递归算法。初始调用时，low为1，high为ST.length
typedef int ElemType;
typedef struct {
    ElemType *data;
    int length;
} SSTable;

int BinSearchRec(SSTable ST, ElemType key, int low, int high) {
    if (low > high)
        return 0;
    int mid = (low + high) / 2;
    if (key > ST.data[mid])
        BinSearchRec(ST, key, mid + 1, high);
    else if (key < ST.data[mid])
        BinSearchRec(ST, key, low, high - 1);
    else
        return mid;
}


//06.线性表中各结点的检索概率不等时，可用如下策略提高顺序检索的效率：若找到指定的结点，则将该结点和其前驱结点（若存在）交换，使得经常被检索的结点尽量位于表的前端。试设计在顺序结构和链式结构的线性表上实现上述策略的顺序检索算法。
#define MaxSize 100
typedef struct {
    ElemType data[MaxSize];
    int length;
} SqList;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

int SqListSearch(SqList &L, ElemType key) {
    int i = 0;
    for (; L.data[i] != key && i < L.length; i++);
    if (i < L.length && i > 0) {
        int temp = L.data[i];
        L.data[i] = L.data[i - 1];
        L.data[i - 1] = temp;
        return --i;
    } else
        return -1;
}

LNode *LinkListSearch(LinkList &L, ElemType key) {//链表带头结点
    LNode *p = L->next, *q = L;
    while (p->data != key && p != NULL) {
        q = p;
        p = p->next;
    }
    if (p != NULL) {
        ElemType temp = p->data;
        p->data = q->data;
        q->data = temp;
        return q;
    } else
        return NULL;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
