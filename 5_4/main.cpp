#include <iostream>

#define MaxSize 100

typedef int ElemType;
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

//04.������Ժ����ֵܱ�ʾ���洢��ɭ�ֵ�Ҷ�ӽ����
int Leaves(CSTree T) {
    if (T == NULL)
        return 0;
    if (T->firstchild == NULL)//������޺��ӣ���ý�����Ҷ��
        return 1 + Leaves(T->nextsibling);//����Ҷ�ӽ������ֵ������е�Ҷ�ӽ����
    else//�����������ֵ�������Ҷ����֮��
        return Leaves(T->firstchild) + Leaves(T->nextsibling);
}


//05.�Ժ����ֵ�����Ϊ�洢�ṹ������Ƶݹ��㷨���������
int Height(CSTree T) {
    int hc, hs;
    if (T == NULL)
        return 0;
    else {//���򣬸߶�ȡ��Ů�߶�+1���ֵ������߶ȵĴ���
        hc = Height(T->firstchild);//��һ��Ů����
        hs = Height(T->nextsibling);//�ֵ�����
        if (hc + 1 > hs)
            return hc + 1;
        else
            return hs;
    }
}


//06.��֪һ�����Ĳ�����м�ÿ�����Ķȣ���д�㷨��������ĺ���-�ֵ�����
void createCSTree_Degree(CSTree T, ElemType e[], int degree[], int n) {
    CSNode *pointer[MaxSize];
    for (int i = 0; i < n; i++) {//��ʼ��
        pointer[i]->data = e[i];
        pointer[i]->firstchild = pointer[i]->nextsibling = NULL;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        int d = degree[i];//���i�Ķ���
        if (d > 0) {
            k++;//kΪ��Ů������
            pointer[i]->firstchild = pointer[k];//����i����Ůk�������
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
