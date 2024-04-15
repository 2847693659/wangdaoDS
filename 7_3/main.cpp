#include <iostream>

typedef int ElemType;
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
    int count;//count�����Ըý��Ϊ���������ϵĽ�����
} BiTNode, *BiTree;

//06.�Ա�дһ���㷨���жϸ����Ķ������Ƿ��Ƕ���������
//�Զ�����������˵���������������Ϊһ�������������С���ˣ��Ը����Ķ��������������������ʼ���ܱ���ǰһ��ֵ�Ⱥ�һ��ֵС����˵���ö�������һ�ö���������
ElemType predt = INT_MIN;

int JudgeBst(BiTree T) {
    ElemType b1, b2;
    if (T == NULL)
        return 0;
    else {
        b1 = JudgeBst(T->lchild);//�ж��������Ƿ��Ƕ���������
        if (b1 == 0 || predt >= T->data)//������������ֵΪ0��ǰ�����ڵ��ڵ�ǰ���
            return 0;//���Ƕ���������
        predt = T->data;//���浱ǰ���Ĺؼ���
        b2 = JudgeBst(T->rchild);//�ж�������
        return b2;//�����������Ľ��
    }
}

//Ҳ���Բ����������
bool Judge(BiTree T, ElemType lower, ElemType upper) {
    if (T == NULL)
        return true;
    if (T->data <= lower || T->data >= upper)
        return false;
    return Judge(T->lchild, lower, T->data) && Judge(T->rchild, T->data, upper);
}

bool isBST(BiTree T) {
    return Judge(T, INT_MIN, INT_MAX);
}


//07.���һ���㷨�����ָ������ڸ��������������еĲ��
int level(BiTree T, BiTNode *p) {
    int n = 0;
    if (T != NULL) {
        n++;
        while (T->data != p->data) {
            if (p->data < T->data)
                T = T->lchild;
            else
                T = T->rchild;
            n++;
        }
    }
    return n;
}


//08.���ö�����������˼���дһ���ж϶������Ƿ���ƽ����������㷨
void Judge_AVL(BiTree T, int &balance, int &h) {
    int bl = 0, br = 0, hl = 0, hr = 0;//����������ƽ���Ǻ͸߶�
    if (T == NULL) {//�������߶�Ϊ0
        h = 0;
        balance = 1;
    } else if (T->lchild == NULL && T->rchild == NULL) {//���и���㣬��߶�Ϊ1
        h = 1;
        balance = 1;
    } else {
        Judge_AVL(T->lchild, bl, hl);//�ݹ��ж�������
        Judge_AVL(T->rchild, br, hr);//�ݹ��ж�������
        h = (hl > hr ? hl : hr) + 1;
        if (abs(hl - hr) < 2)//�������߶Ȳ�ľ���ֵ<2�������������Ƿ�ƽ��
            balance = bl && br;//����������ƽ��ʱ��������ƽ��
        else
            balance = 0;
    }
}


//09.���һ���㷨�����������������������С�����Ĺؼ���
ElemType MinElem(BiTree T) {
    while (T->lchild != NULL)
        T = T->lchild;
    return T->data;
}

ElemType MaxElem(BiTree T) {
    while (T->rchild != NULL)
        T = T->rchild;
    return T->data;
}


//10.���һ���㷨���Ӵ�С�������������������ֵ��С��k�Ĺؼ���
void OutPut(BiTree T, ElemType k) {
    if (T == NULL)
        return;
    if (T->rchild != NULL)
        OutPut(T->rchild, k);
    if (T->data >= k)
        printf("%d", T->data);
    if (T->lchild != NULL)
        OutPut(T->lchild, k);
}


//11.��дһ���ݹ��㷨����һ����n�����ġ�������������Ķ����������ϲ��ҵ�k(1��k��n)С��Ԫ�أ�������ָ��ý���ָ�롣Ҫ���㷨��ƽ��ʱ�临�Ӷ�ΪO(log2n)��������������ÿ������г�data,lchild,rchild�����ݳ�Ա�⣬����һ��count��Ա�������Ըý��Ϊ���������ϵĽ�������
BiTNode *Search_Small(BiTree T, int k) {
    if (k < 1 || k > T->count)
        return NULL;
    if (T->lchild == NULL) {
        if (k == 1)
            return T;
        else
            return Search_Small(T->rchild, k - 1);
    } else {
        if (T->lchild->count == k - 1)
            return T;
        else if (T->lchild->count > k - 1)
            return Search_Small(T->lchild, k);
        else
            return Search_Small(T->rchild, k - (T->lchild->count + 1));
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
