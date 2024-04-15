#include <iostream>

//05.д���۰���ҵĵݹ��㷨����ʼ����ʱ��lowΪ1��highΪST.length
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


//06.���Ա��и����ļ������ʲ���ʱ���������²������˳�������Ч�ʣ����ҵ�ָ���Ľ�㣬�򽫸ý�����ǰ����㣨�����ڣ�������ʹ�þ����������Ľ�㾡��λ�ڱ��ǰ�ˡ��������˳��ṹ����ʽ�ṹ�����Ա���ʵ���������Ե�˳������㷨��
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

LNode *LinkListSearch(LinkList &L, ElemType key) {//�����ͷ���
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
