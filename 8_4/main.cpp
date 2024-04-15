#include <iostream>

typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//04.编写一个算法，在基于单链表表示的待排序关键字序列上进行简单选择排序。
//每次找最大的元素，然后头插法
void selectSort(LinkList &L) {
    LNode *h = L, *p, *pfront, *max, *maxfront;
    L = NULL;
    while (h != NULL) {//持续扫描原链表断链后的后段
        p = max = h;
        pfront = maxfront = NULL;
        while (p != NULL) {//扫描原链表寻找最大结点max
            if (p->data > max->data) {//找到更大的，记忆它和它的前驱
                max = p;
                maxfront = pfront;
            }
            pfront = p;
            p = p->next;//继续寻找
        }
        //注意这里的两种情况！！！
        if (max == h)//最大结点在原链表断链后的后段的最前端
            h = h->next;
        else//最大结点在原链表断链后的后段的不是最前端的位置
            maxfront->next = max->next;//此时已断链
        //无论最大结点在原链表的什么位置，都需把最大结点拿出来用头插法插入到L中
        max->next = L;//结点max插入结果链前端
        L = max;
    }
}


//05.试设计一个算法，判断一个数据序列是否构成一个小根堆。
bool IsMinHeap(ElemType A[], int n) {
    if (n % 2 == 0) {//len为偶数，有一个单分支结点
        if (A[n / 2] > A[n])//判断单分支结点
            return false;
        for (int i = n / 2 - 1; i >= 1; i--) {//判断所有双分支结点
            if (A[i] > A[2 * i] || A[i] > A[2 * i + 1])
                return false;
        }
    } else {//len为奇数时，没有单分支结点
        for (int i = n / 2; i >= 1; i--) {//判断所有双分支结点
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
