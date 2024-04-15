#include <iostream>

#define MaxSize 100
typedef int ElemType;
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    BiTNode *data[MaxSize];
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

bool EnQueue(SqQueue &Q, BiTNode *x) {
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q, BiTNode *&x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}


//1.��֪һ�÷ǿն�����T�߶�Ϊh���������Ϊn�����ö�������洢�ṹ�������һ���㷨������T�Ŀ�ȣ������н����������һ��Ľ���������Ҫ��
//(1)�����㷨�Ļ������˼�롣
//���������ɨ��ͳ��ÿһ��Ľ�����������ֵ
//(2)ʹ��C��C++���ԣ����������������������Ͷ��塣
//(3)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
int BTWidth(BiTree T) {
    BiTNode *p, *lastNode = T, *newLastNode = NULL;//lastNode������¼��ǰ������һ����㣬lastNode��ʼ��Ϊ����㣬newlastNode������¼��һ������һ����㣬newlastNode��ʼ��Ϊ��
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    int width = 0, maxWidth = 0;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        if (p->lchild != NULL) {//�������
            EnQueue(Q, p->lchild);
            newLastNode = p->lchild;//�����ý���������Ϊ��һ������һ�����
            width++;
        }
        if (p->rchild != NULL) {//�ҽ�����
            EnQueue(Q, p->rchild);
            newLastNode = p->rchild;//�����ý����ҽ����Ϊ��һ������һ�����
            width++;
        }
        if (p == lastNode) {//���ý��Ϊ�������һ����㣬�����lastNode�����Ƚ�width��ֵ
            lastNode = newLastNode;
            if (maxWidth < width)
                maxWidth = width;
        }
    }
    return maxWidth;
}


//2.��������ͷ�ڵ�Ľ�������L1��L2���ϳ�������Ԫ�ظ���Ϊn�������㶨��������ʾ�������һ��ʱ���Ͼ����ܸ�Ч�㷨�������������������������Ԫ�ص�Ȩֵ��
//(1)�����㷨�Ļ������˼�롣
//ָ����ƹ鲢������ͷ�巨����
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
//(3)˵�����㷨��ʱ�临�Ӷȡ��ռ临�Ӷȡ��ȶ��ԡ�
//ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(1)���ȶ�
typedef struct LinkNode {
    double data;
    struct LinkNode *next;
} LinkNode, *LinkList;

void Print_Ascend(LinkList L1, LinkList L2) {
    LinkNode *p = L1->next, *q = L2->next;
    LinkNode *x, *y;
    while (p != NULL && q != NULL) {//ͷ�巨�ϲ���������L1��
        if (p->data >= q->data) {
            x = p->next;
            p->next = L1->next;
            L1->next = p;
            p = x;
        } else {
            y = q->next;
            q->next = L1->next;
            L1->next = q;
            q = y;
        }
    }
    while (p != NULL) {
        x = p->next;
        p->next = L1->next;
        L1->next = p;
        p = x;
    }
    while (q != NULL) {
        y = q->next;
        q->next = L1->next;
        L1->next = q;
        q = y;
    }
    p = L1->next;
    while (p != NULL) {
        printf("%f", p->data);
        p = p->next;
    }
}


//3.��֪һ����������A=(a0,a1��,an-1)������0��ai<n(0��i<n)����������ѡ�����ɸ�����Ҫ��ѡ���������������֮��ľ���ֵ<=k(0<k<n)�������һ����ʱ���Ͼ����ܸ�Ч���㷨���������ѡ���Ԫ�ظ�����Ҫ��
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�
//ʱ�临�Ӷ�O(n2)���ռ临�Ӷ�O(n)
int MaxCount(int A[], int n, int k) {
    int B[n];
    for (int i = 0; i < n; i++) {
        B[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        B[A[i]]++;
    }
    int count, MaxCount = 0;
    for (int i = k; i < n - 1 - k; i++) {
        count = 0;
        for (int j = i - k; j <= i + k; j++) {
            count += B[j];
        }
        if (count > MaxCount)
            MaxCount = count;
    }
    return MaxCount;
}


//�Ż���
//ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(n)
int MaxCount1(int A[], int n, int k) {
    int B[n];
    for (int i = 0; i < n; i++) {
        B[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        B[A[i]]++;
    }
    int count = 0;
    for (int i = 0; i <= 2 * k && i < n; i++) {
        count += B[i];
    }
    int MaxCount = count;//��ʼʱMaxCount����ֵ��0~2k֮������ĸ���
    for (int i = k + 1; i < n - 1 - k; i++) {
        count += (B[i + k] - B[i - k - 1]);//���ƻ������ڣ���ȥ����֮ǰ��һ�������ϴ����ڵ����һ��
        if (count > MaxCount)
            MaxCount = count;
    }
    return MaxCount;
}


//4.һ������Ϊn��������������S�У�ֻ�г���K��K��ֵ��֪�����������ɴΣ���������඼ֻ����һ�Ρ������һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨���ҳ�K���ֵĴ�����
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�
//����1��������ͳ�ƣ�ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(1)����������������δʹ��
int Count(int S[], int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (S[i] == k) {
            count++;
        }
    }
    return count;
}

//����2���۰���ң��ҵ��Ļ�����ǰ����ҵ���k��ֵ��ʱ�临�Ӷ�O(log2n)���ռ临�Ӷ�O(1)
int Binary_Search_K(int S[], int n, int k) {
    int low = 0, high = n - 1, mid;
    int count = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        if (S[mid] == k) {
            for (int i = mid; i > 0; i--) {
                if (S[i] == k)
                    count++;
            }
            for (int i = mid + 1; i < n; i++) {
                if (S[i] == k)
                    count++;
            }
            break;
        } else if (S[mid] > k)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return count;
}

//����3���۰����k-1��k+1��λ�ã����±�����ټ�1��Ϊ����ʱ�临�Ӷ�O(log2n)���ռ临�Ӷ�O(1)������һ������ֵΪk-1��k+1����
int Binary_Search(int S[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (S[mid] == key) {
            return mid;
        } else if (S[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
}

int Count_K(int S[], int n, int k) {
    int pos1 = Binary_Search(S, n, k - 1), pos2 = Binary_Search(S, n, k + 1);
    return pos2 - pos1 - 1;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
