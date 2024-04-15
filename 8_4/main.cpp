#include <iostream>

typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//04.��дһ���㷨���ڻ��ڵ������ʾ�Ĵ�����ؼ��������Ͻ��м�ѡ������
//ÿ��������Ԫ�أ�Ȼ��ͷ�巨
void selectSort(LinkList &L) {
    LNode *h = L, *p, *pfront, *max, *maxfront;
    L = NULL;
    while (h != NULL) {//����ɨ��ԭ���������ĺ��
        p = max = h;
        pfront = maxfront = NULL;
        while (p != NULL) {//ɨ��ԭ����Ѱ�������max
            if (p->data > max->data) {//�ҵ�����ģ�������������ǰ��
                max = p;
                maxfront = pfront;
            }
            pfront = p;
            p = p->next;//����Ѱ��
        }
        //ע��������������������
        if (max == h)//�������ԭ���������ĺ�ε���ǰ��
            h = h->next;
        else//�������ԭ���������ĺ�εĲ�����ǰ�˵�λ��
            maxfront->next = max->next;//��ʱ�Ѷ���
        //�����������ԭ�����ʲôλ�ã������������ó�����ͷ�巨���뵽L��
        max->next = L;//���max��������ǰ��
        L = max;
    }
}


//05.�����һ���㷨���ж�һ�����������Ƿ񹹳�һ��С���ѡ�
bool IsMinHeap(ElemType A[], int n) {
    if (n % 2 == 0) {//lenΪż������һ������֧���
        if (A[n / 2] > A[n])//�жϵ���֧���
            return false;
        for (int i = n / 2 - 1; i >= 1; i--) {//�ж�����˫��֧���
            if (A[i] > A[2 * i] || A[i] > A[2 * i + 1])
                return false;
        }
    } else {//lenΪ����ʱ��û�е���֧���
        for (int i = n / 2; i >= 1; i--) {//�ж�����˫��֧���
            if (A[i] > A[2 * i] || A[i] > A[2 * i + 1])
                return false;
        }
    }
    return true;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
