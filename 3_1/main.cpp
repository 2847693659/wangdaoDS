#include <iostream>

//03.������I��O�ֱ��ʾ��ջ�ͳ�ջ������ջ�ĳ�̬����̬��Ϊ�գ���ջ�ͳ�ջ�Ĳ������пɱ�ʾΪ����I��O��ɵ����У����Բ��������г�Ϊ�Ϸ����У������Ϊ�Ƿ����С�
//(2)ͨ����(1)�ķ�����д��һ���㷨���ж������Ĳ��������Ƿ�Ϸ������Ϸ�������true�����򷵻�false���ٶ����ж��Ĳ��������Ѵ���һά�����У���
//�豻�ж��Ĳ��������Ѵ���һά����A�С��㷨�Ļ������˼�룺������һɨ����ջ��ջ���У����ɡ�I���͡�O����ɵ��ַ�������ÿɨ������һλ�þ������ջ����������O���ĸ������Ƿ�С����ջ��������I���ĸ���������������Ϊ�Ƿ����С�ɨ����������ж���ջ�ͳ�ջ�����Ƿ���ȣ���������򲻺����⣬Ϊ�Ƿ����С�
bool Judge(char A[]) {
    int i = 0;
    int j = 0, k = 0;//iΪ�±꣬j��k�ֱ�Ϊ��ĸI��O�ĸ���
    while (A[i] != '\0') {//δ���ַ�����β
        switch (A[i]) {
            case 'I':
                j++;//��ջ������1
                break;
            case 'O':
                k++;
        }
        if (k > j)
            exit(0);
        i++;//����A[i]�ǡ�I����O����ָ��i������
    }
    if (j == k)
        return true;
    else
        return false;
}


//04.�赥����ı�ͷָ��ΪL�����ṹ��data��next�����򹹳ɣ�����data��Ϊ�ַ��͡�������㷨�жϸ������ȫ��n���ַ��Ƿ����ĶԳơ�����xyx��xyyx�������ĶԳơ�
//�㷨˼�룺ʹ��ջ���ж������е������Ƿ����ĶԳơ��������ǰһ��Ԫ�����ν�ջ���ڴ�������ĺ�һ��Ԫ��ʱ�������ʵ������һ��Ԫ�غ󣬾ʹ�ջ�е���һ��Ԫ�أ�����Ԫ�رȽϣ�����ȣ��������е���һ��Ԫ����ջ���ٵ�����Ԫ�رȽϣ�ֱ������β����ʱ��ջ�ǿ�ջ����ó��������ĶԳƵĽ��ۣ����򣬵������е�һ��Ԫ����ջ�е���Ԫ�ز���ʱ������Ϊ��������ĶԳƣ������㷨��ִ�С�
typedef struct LNode {
    char data;
    struct LNode *next;
} LNode, *LinkList;

bool dc(LinkList L, int n) {//L��ͷ���
    int i;
    char s[n / 2];//s�ַ�ջ
    LNode *p = L->next;//p������Ĺ���ָ�룬ָ�������ĵ�ǰԪ��
    for (i = 0; i < n / 2; i++) {//����ǰһ��Ԫ�ؽ�ջ
        s[i] = p->data;
        p = p->next;
    }
    i--;//�ָ�����iֵ
    if (n % 2 == 1)//��n�����������ƹ����Ľ��
        p = p->next;
    while (p != NULL && s[i] == p->data) {//����Ƿ����ĶԳ�
        i--;//i�䵱ջ��ָ��
        p = p->next;
    }
    if (i == -1)//ջΪ��ջ
        return true;//�������ĶԳ�
    else
        return false;//�������ĶԳ�
}


//05.��������ջs1��s2������˳��ջ��ʽ��������һ���洢��[0,��,maxsize-1]��Ϊ�˾������ÿռ䣬��������Ŀ��ܣ��ɲ���ջ������ӭ�������Ĵ洢��ʽ�������s1��s2�й���ջ�ͳ�ջ�Ĳ����㷨��
#define MaxSize 100
typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int top1, top2;
} SqStack;

bool Push(SqStack &S, ElemType x, int i) {
    if (S.top2 - S.top1 == 1)
        return false;
    switch (i) {
        default:
            return false;
        case 1:
            S.data[++S.top1] = x;
            return true;
        case 2:
            S.data[--S.top2] = x;
            return true;
    }
}

bool Pop(SqStack &S, ElemType &x, int i) {
    switch (i) {
        default:
            return false;
        case 1:
            if (S.top1 == -1)
                return false;
            else {
                x = S.data[S.top1--];
                return true;
            }
        case 2:
            if (S.top2 == MaxSize)
                return false;
            else {
                x = S.data[S.top2++];
                return true;
            }
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
