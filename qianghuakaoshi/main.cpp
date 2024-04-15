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


//1.已知一棵非空二叉树T高度为h，结点总数为n，采用二叉链表存储结构。请设计一个算法，求树T的宽度（即具有结点数最多的那一层的结点个数），要求：
//(1)给出算法的基本设计思想。
//层序遍历，扫描统计每一层的结点数并求最大值
//(2)使用C或C++语言，给出二叉树结点的数据类型定义。
//(3)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
int BTWidth(BiTree T) {
    BiTNode *p, *lastNode = T, *newLastNode = NULL;//lastNode用来记录当前层的最后一个结点，lastNode初始化为根结点，newlastNode用来记录下一层的最后一个结点，newlastNode初始化为空
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    int width = 0, maxWidth = 0;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        if (p->lchild != NULL) {//左结点入队
            EnQueue(Q, p->lchild);
            newLastNode = p->lchild;//并将该结点的左结点设为下一层的最后一个结点
            width++;
        }
        if (p->rchild != NULL) {//右结点入队
            EnQueue(Q, p->rchild);
            newLastNode = p->rchild;//并将该结点的右结点设为下一层的最后一个结点
            width++;
        }
        if (p == lastNode) {//若该结点为本层最后一个结点，则更新lastNode，并比较width的值
            lastNode = newLastNode;
            if (maxWidth < width)
                maxWidth = width;
        }
    }
    return maxWidth;
}


//2.有两个带头节点的降序单链表L1、L2，较长的链表元素个数为n。链表结点定义如下所示。请设计一个时间上尽可能高效算法，按升序输出两个链表中所有元素的权值。
//(1)给出算法的基本设计思想。
//指针后移归并，链表头插法逆置
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
//(3)说明该算法的时间复杂度、空间复杂度、稳定性。
//时间复杂度O(n)，空间复杂度O(1)，稳定
typedef struct LinkNode {
    double data;
    struct LinkNode *next;
} LinkNode, *LinkList;

void Print_Ascend(LinkList L1, LinkList L2) {
    LinkNode *p = L1->next, *q = L2->next;
    LinkNode *x, *y;
    while (p != NULL && q != NULL) {//头插法合并两个链表到L1中
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


//3.已知一个整数序列A=(a0,a1…,an-1)，其中0≤ai<n(0≤i<n)。从数组中选择若干个数，要求选择的数中任意两数之差的绝对值<=k(0<k<n)。请设计一个在时间上尽可能高效的算法输出最多可能选择的元素个数。要求：
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
//(3)说明你所设计算法的时间复杂度和空间复杂度。
//时间复杂度O(n2)，空间复杂度O(n)
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


//优化：
//时间复杂度O(n)，空间复杂度O(n)
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
    int MaxCount = count;//初始时MaxCount保存值在0~2k之间的数的个数
    for (int i = k + 1; i < n - 1 - k; i++) {
        count += (B[i + k] - B[i - k - 1]);//类似滑动窗口，减去窗口之前的一个，加上窗口内的最后一个
        if (count > MaxCount)
            MaxCount = count;
    }
    return MaxCount;
}


//4.一个长度为n的升序整数序列S中，只有常数K（K的值已知）出现了若干次，其他数最多都只出现一次。试设计一个在时间和空间两方面都尽可能高效的算法，找出K出现的次数。
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
//(3)说明你所设计算法的时间复杂度和空间复杂度。
//方法1：遍历并统计，时间复杂度O(n)，空间复杂度O(1)，但题中升序条件未使用
int Count(int S[], int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (S[i] == k) {
            count++;
        }
    }
    return count;
}

//方法2：折半查找，找到的话就向前向后找等于k的值，时间复杂度O(log2n)，空间复杂度O(1)
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

//方法3：折半查找k-1和k+1的位置，两下标相减再减1即为所求，时间复杂度O(log2n)，空间复杂度O(1)，但不一定存在值为k-1和k+1的数
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
