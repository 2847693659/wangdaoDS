#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

//01.设计一个递归算法，删除不带头结点的单链表L中所有值为x的结点
//算法需要借助一个递归工作栈，深度为O(n)，时间复杂度为O(n)。有读者认为直接去掉p结点会造成断链，实际上因为L为引用，是直接对原链表进行操作的，因此不会断链。
void Del_X_1(LinkList &L, ElemType x) {
    LNode *p;//p指向待删除结点
    if (L == NULL)//递归出口
        return;
    if (L->data == x) {//若L所指结点的值为x
        p = L;//删除*L，并让L指向下一结点
        L = L->next;
        free(p);
        Del_X_1(L, x);//递归调用
    } else {//若L所指结点的值不为x
        Del_X_1(L->next, x);//递归调用
    }
}


//02.在带头结点的单链表L中，删除所有值为x的结点，并释放其空间，假设值为×的结点不唯一，试编写算法以实现上述操作
//解法一：用p从头至尾扫描单链表，pre指向*p结点的前驱。若p所指结点的值为x，则删除，并让p移向下一个结点，否则让pre、p指针同步后移一个结点。
void Del_X_2(LinkList &L, ElemType x) {
    LNode *p = L->next, *pre = L, *q;
    while (p != NULL) {
        if (p->data == x) {
            q = p;//g指向该结点
            p = p->next;
            pre->next = p;//删除*q结点
            free(q);//释放*q结点的空间
        } else {//否则，pre和p同步后移
            pre = p;
            p = p->next;
        }
    }
}

//解法二：采用尾插法建立单链表。用p指针扫描L的所有结点，当其值不为x时，将其链接到L之后，否则将其释放。
void Del_X_3(LinkList &L, ElemType x) {
    LNode *p = L->next, *r = L, *q;//r指向尾结点，其初值为头结点
    while (p != NULL) {
        if (p->data != x) {//*p结点值不为x时将其链接到L尾部
            r->next = p;
            r = p;
            p = p->next;//继续扫描
        } else {//*p结点值为x时将其释放
            q = p;
            p = p->next;//继续扫描
            free(q);//释放空间
        }
    }
    r->next = NULL;//插入结束后置尾结点指针为NULL
}


//03.设L为带头结点的单链表，编写算法实现从尾到头反向输出每个结点的值
//
void R_Print(LinkList L) {
    if (L->next != NULL)
        R_Print(L->next);//递归
    if (L != NULL)//没有这个if判断也可以
        printf("%d", L->data);
}

void R_Ignore_Head(LinkList L) {
    if (L->next != NULL)
        R_Print(L->next);
}


//04.试编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设最小值结点是唯一的）
//算法思想：用p从头至尾扫描单链表，pre指向*p结点的前驱，用minp保存值最小的结点指针（初值为p），minpre指向*minp结点的前驱（初值为pre）。一边扫描，一边比较，若p->data小于minp->data,则将p、pre分别赋值给minp、minpre,如下图所示。当p扫描完毕时，minp指最小值结点，minpre指向最小值结点的前驱结点，再将minp所指结点删除即可。
void Delete_Min(LinkList &L) {
    LNode *pre = L, *p = L->next;//p为工作指针，pre指向其前驱
    LNode *minpre = pre, *minp = p;//保存最小值结点及其前驱
    while (p != NULL) {
        if (p->data < minp->data) {
            minp = p;//找到比之前找到的最小值结点更小的结点
            minpre = pre;
        }
        pre = p;//继续扫描下一个结点
        p = p->next;
    }
    minpre->next = minp->next;//删除最小值结点
    free(minp);
}
//算法需要从头至尾扫描链表，时间复杂度为O(n)，空间复杂度为O(1)。


//05.试编写算法将带头结点的单链表就地逆置，所谓"就地"是指辅助空间复杂度为O(1)
//解法一：将头结点摘下，然后从第一结点开始，依次插入到头结点的后面（头插法建立单链表），直到最后一个结点为止，这样就实现了链表的逆置。
void Reverse_1(LinkList &L) {
    LNode *p = L->next, *r;//p为工作指针，r为p的后继，以防断链
    L->next = NULL;//先将头结点L的next域置为NULL
    while (p != NULL) {//依次将元素结点摘下
        r = p->next;//暂存p的后继
        p->next = L->next;//将p结点插入到头结点之后
        L->next = p;
        p = r;
    }
}
//上述算法的时间复杂度为O(n)，空间复杂度为O(1)。

//解法二：依次遍历线性表L，并将结点指针反转
void Reverse_2(LinkList &L) {
    LNode *pre, *p = L->next, *r = p->next;
    p->next = NULL;//处理第一个结点
    while (r != NULL) {//r为空，则说明p为最后一个结点
        pre = p;//依次继续遍历
        p = r;
        r = r->next;
        p->next = pre;//指针反转
    }
    L->next = p;//处理最后一个结点
}
//上述算法的时间复杂度为O(n)，空间复杂度为O(1)。


//06.有一个带头结点的单链表L，设计一个算法使其元素递增有序
//算法思想：采用直接插入排序算法的思想，先构成只含一个数据结点的有序单链表，然后依次扫描单链表中剩下的结点*p（直至p==NULL为止），在有序表中通过比较查找插入*p的前驱结点*pre，然后将*p插入到*pre之后。
void Sort(LinkList &L) {
    LNode *pre, *p = L->next, *r = p->next;//r保持*p后继结点指针，以保证不断链
    p->next = NULL;//构造只含一个数据结点的有序表
    p = r;
    while (p != NULL) {
        r = p->next;//保存*p的后继结点指针
        pre = L;
        while (pre->next != NULL && pre->next->data < p->data)
            pre = pre->next;//在有序表中查找插入*p的前驱结点*pre
        p->next = pre->next;//将*p插入到*pre之后
        pre->next = p;
        p = r;//扫描原单链表中剩下的结点
    }
}
//该算法的时间复杂度为O(n2)，为达到最佳的时间性能，可先将链表的数据复制到数组中，再采用时间复杂度为O(nlog2n)的排序算法进行排序，然后将数组元素依次插入到链表中，此时的时间复杂度为O(nlog2n)，显然这是以空间换时间的策略。


//07.设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于给定的两个值（作为函数参数给出）之间的元素的元素（若存在）
//因为链表是无序的，所以只能逐个结点进行检查，执行删除
void RangeDelete(LinkList &L, ElemType from, ElemType to) {
    LNode *pre = L, *p = L->next;
    while (p != NULL) {
        if (p->data > from && p->data < to) {
            pre->next = p->next;
            free(p);
            p = pre->next;
        } else {
            pre = p;
            p = p->next;
        }
    }
}


//08.给定两个单链表，编写算法找出两个链表的公共结点
//我们先要分别遍历两个链表得到它们的长度，并求出两个长度之差。在长的链表上先遍历长度之差个结点之后，再同步遍历两个链表，直到找到相同的结点，或者一直到链表结束。此时，该方法的时间复杂度为O(len1+len2)
int Length(LinkList L) {//默认带头结点
    int n = 0;
    L = L->next;
    while (L != NULL) {
        n++;
        L = L->next;
    }
    return n;
}

LNode *Search_lst_Common(LinkList L1, LinkList L2) {
    int len1 = Length(L1), len2 = Length(L2), dist;
    LinkList longList, shortList;
    if (len1 >= len2) {
        longList = L1->next;
        shortList = L2->next;
        dist = len1 - len2;
    } else {
        longList = L2->next;
        shortList = L1->next;
        dist = len2 - len1;
    }
    while (dist > 0) {
        longList = longList->next;
        dist--;
    }
    while (longList != NULL) {
        if (longList == shortList)
            return longList;
        else {
            longList = longList->next;
            shortList = shortList->next;
        }
    }
    return NULL;
}


//09.给定一个带表头结点的单链表，设head为头指针，结点结构为(data,next)，data为整型元素，next为指针，试写出算法：按递增次序输出单链表中各结点的数据元素，并释放结点所占的存储空间（要求：不允许使用数组作为辅助空间）
//类似06题直接插入排序的思想
void Min_Delete(LinkList &L) {
    while (L->next != NULL) {
        LNode *pre = L, *p = L->next;
        while (p->next != NULL) {
            if (p->next->data < pre->next->data)
                pre = p;
            p = p->next;
        }
        printf("%d", pre->next->data);
        LNode *u = pre->next;
        pre->next = u->next;
        free(u);
    }
    free(L);
}


//10.将一个带头结点的单链表A分解为两个带头结点的单链表A和B,使得A表中含有原表中序号为奇数的元素，而B表中含有原表中序号为偶数的元素，且保持其相对顺序不变
//
LinkList DisCreat_1(LinkList &A) {
    int i = 0;
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *ra = A, *rb = B, *p = A->next;
    A->next = NULL;
    while (p != NULL) {
        i++;
        if (i % 2 == 0) {
            rb->next = p;
            rb = p;
        } else {
            ra->next = p;
            ra = p;
        }
        p = p->next;
    }
    ra->next = NULL;
    rb->next = NULL;
    return B;
}


//11.设C={a1,b1,a2,b2,…，an,bn}为线性表，采用带头结点的单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A={a1,a2,…,an}，B={bn,…,b2,b1}
//
LinkList DisCreat_2(LinkList &A) {
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *ra = A, *p = A->next, *q;
    while (p != NULL) {
        ra->next = p;
        ra = p;
        p = p->next;
        if (p != NULL) {
            q = p->next;
            p->next = B->next;
            B->next = p;
            p = q;
        }
    }
    ra->next = NULL;
    return B;
}


//12.在一个递增有序的线性表中，有数值相同的元素存在。若存储方式为单链表，设计算法去掉数值相同的元素，使表中不再有重复的元素，例如(7,10,10,21,30,42,42,42,51,70)将变为(7,10,21,30,42,51,70)
//算法思想：由于是有序表，所有相同值域的结点都是相邻的。用p扫描递增单链表L，若*p结点的值域等于其后继结点的值域，则删除后者，否则p移向下一个结点。
void Del_Same(LinkList &L) {
    LNode *p = L->next, *q;
    while (p != NULL) {
        q = p->next;
        if (q->data == p->data) {
            p->next = q->next;
            free(q);
        } else
            p = p->next;
    }
}
//本算法的时间复杂度为O(n)，空间复杂度为O(1)。
//本题也可采用尾插法，将头结点摘下，然后从第一结点开始，依次与已经插入结点的链表的最后一个结点比较，若不等则直接插入，否则将当前遍历的结点删除并处理下一个结点，直到最后一个结点为止。


//13.假设有两个按元素值递增次序排列的线性表，均以单链表形式存储。请编写算法将这两个单链表归并为一个按元素值递减次序排列的单链表，并要求利用原来两个单链表的结点存放归并后的单链表
//
void MergeList(LinkList &L1, LinkList &L2) {
    LNode *p1 = L1->next, *p2 = L2->next, *q;
    L1->next = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->data <= p2->data) {
            q = p1->next;
            p1->next = L1->next;
            L1->next = p1;
            p1 = q;
        } else {
            q = p2->next;
            p2->next = L1->next;
            L1->next = p2;
            p2 = q;
        }
    }
    while (p1 != NULL) {
        q = p1->next;
        p1->next = L1->next;
        L1->next = p1;
        p1 = q;
    }
    while (p2 != NULL) {
        q = p2->next;
        p2->next = L1->next;
        L1->next = p2;
        p2 = q;
    }
    free(L2);
}


//14.设A和B是两个单链表（带头结点），其中元素递增有序。设计一个算法从A和B中的公共元素产生单链表C，要求不破坏A、B的结点
//
void Get_Common(LinkList A, LinkList B) {
    LNode *pa = A->next, *pb = B->next, *r;
    LinkList C = (LinkList) malloc(sizeof(LNode));
    r = C;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data)
            pa = pa->next;
        else if (pa->data > pb->data)
            pb = pb->next;
        else {
            LNode *s = (LNode *) malloc(sizeof(LNode));
            s->data = pa->data;
            r->next = s;
            r = s;
            pa = pa->next;
            pb = pb->next;
        }
    }
    r->next = NULL;
}


//15.已知两个链表A和B分别表示两个集合，其元素递增排列。编制函数，求A与B的交集，并存放于A链表中
//
LinkList Union(LinkList &A, LinkList &B) {
    LNode *pa = A->next, *pb = B->next, *r = A, *q;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            q = pa;
            pa = pa->next;
            free(q);
        } else if (pa->data > pb->data) {
            q = pb;
            pb = pb->next;
            free(q);
        } else {
            r->next = pa;
            r = pa;
            pa = pa->next;
            q = pb;
            pb = pb->next;
            free(q);
        }
    }
    while (pa != NULL) {
        q = pa;
        pa = pa->next;
        free(q);
    }
    while (pb != NULL) {
        q = pb;
        pb = pb->next;
        free(q);
    }
    r->next = NULL;
    free(B);
    return A;
}
//该算法的时间复杂度为O(len1+len2)，空间复杂度为O(1)


//16.两个整数序列A=a1,a2,a3,…,am和B=b1,b2,b3,…,bn已经存入两个单链表中，设计一个算法，判断序列B是否是序列A的连续子序列
//
int Pattern(LinkList A, LinkList B) {
    LNode *pa = A, *pb = B, *pre = pa;
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {
            pa = pa->next;
            pb = pb->next;
        } else {
            pa = pre->next;
            pre = pa;
            pb = B;
        }
    }
    if (pb == NULL)
        return 1;
    else
        return 0;
}


//17.设计一个算法用于判断带头结点的循环双链表是否对称
//
int Symmetry(DLinkList L) {
    DNode *p = L->next, *q = L->prior;
    while (p != q && q->next != p) {//前半句为元素总数是奇数时的情况，后半句为元素总数是偶数时的情况。注意这里的q->next != p，这种情况是L中元素的个数为偶数，当比较完中点左右的元素后，p会再向后移动，q会再向前移动，此时q在p前面，所以判断条件为q->next != p
        if (p->data == q->data) {
            p = p->next;
            q = q->prior;
        } else
            return 0;
    }
    return 1;
}


//18.有两个循环单链表，链表头指针分别为h1和h2，编写一个函数将链表h2链接到链表h1之后，要求链接后的链表仍保持循环链表形式
//
LinkList Link(LinkList &h1, LinkList &h2) {
    LNode *p1 = h1, *p2 = h2;
    while (p1->next != h1)
        p1 = p1->next;
    while (p2->next != h2)
        p2 = p2->next;
    p1->next = h2;
    p2->next = h1;
    return h1;
}


//19.设有一个带头结点的循环单链表，其结点值均为正整数。设计一个算法，反复找出单链表中结点值最小的结点并输出，然后将该结点从中删除，直到单链表空为止，再删除表头结点
//
void Del_All(LinkList &L) {
    LNode *p, *pre, *minp, *minpre;
    while (L->next != L) {
        p = L->next;
        pre = L;
        minp = p;
        minpre = pre;
        while (p != L) {
            if (p->data < minp->data) {
                minp = p;
                minpre = pre;
            }
            pre = p;
            p = p->next;
        }
        printf("%d", minp->data);
        minpre->next = minp->next;
        free(minp);
    }
    free(L);
}


//20.设头指针为L的带有表头结点的非循环双向链表，其每个结点中除有pred（前驱指针）、data（数据）和next（后继指针）域外，还有一个访问频度域freq。在链表被启用前，其值均初始化为零。每当在链表中进行一次Locate(L,x)运算时，令元素值为x的结点中freq域的值增1，并使此链表中结点保持按访问频度非增（递减）的顺序排列，同时最近访问的结点排在频度相同的结点前面，以使使频繁访问的结点总是靠近表头。试编写符合上述要求的Locate(L,x)运算的算法，该运算为函数过程，返回找到结点的地址，类型为指针型
//算法思想：首先在双向链表中查找数据值为x的结点，查到后，将结点从链表上摘下，然后顺着结点的前驱链查找该结点的插入位置（频度递减，且排在同频度的第一个，即向前找到第一个比它的频度大的结点，插入位置为该结点之后），并插入到该位置。
typedef struct DFNode {
    ElemType data;
    struct DFNode *prior, *next;
    int freq;
} DFNode, *DFLinkList;

DFNode *Locate(DFLinkList &L, ElemType x) {
    DFNode *p = L->next, *pre;//p为工作指针，pre为p的前驱，用于查找插入位置
    while (p != NULL && p->data != x)
        p = p->next;//查找值为x的结点
    if (p == NULL)
        exit(0);//不存在值为x的结点
    else {
        p->freq++;//令元素值为x的结点的freq域加1
        if (p->prior == L || p->prior->freq > p->freq)
            return p;//p是链表首结点，或freq值小于前驱
        if (p->next != NULL)
            p->next->prior = p->prior;
        p->prior->next = p->next;//将p结点从链表上摘下
        pre = p->prior;//以下查找p结点的插入位置
        while (pre != L && pre->freq <= p->freq)
            pre = pre->prior;
        p->next = pre->next;//将p结点排在同频率的第一个
        if (pre->next != NULL)
            pre->next->prior = p;
        p->prior = pre;
        pre->next = p;
    }
    return p;//返回值为x的结点的指针
}


//21.单链表有环，是指单链表的最后一个结点的指针指向了链表中的某个结点（通常单链表的最后一个结点的指针域是空的）。试编写算法判断单链表是否存在环。
//(1)给出算法的基本设计思想。
//设置快慢两个指针分别为fast和slow,初始时都指向链表头head。slow每次走一步，即slow=slow->next，fast每次走两步，即fast=fast->next->next。由于fast比slow走得快，如果有环，那么fast一定会先进入环，而slow后进入环。当两个指针都进入环后，经过若干操作后两个指针定能在环上相遇。这样就可以判断一个链表是否有环。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
LNode *FindLoopStart(LinkList L) {
    LNode *fast = L, *slow = L;//设置快慢两个指针
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;//每次走一步
        fast = fast->next->next;//每次走两步
        if (slow == fast)//相遇
            break;
    }
    if (slow == NULL || fast->next == NULL)//没有环，返回NULL
        return NULL;
    LNode *p1 = L, *p2 = slow;//分别指向开始点、相遇点
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;//返回入口点
}
//(3)说明你所设计算法的时间复杂度和空间复杂度。
//当fast与slow相遇时，slow肯定没有遍历完链表，故算法的时间复杂度为O(n)，空间复杂度为O(1)。


//剑指 Offer 22 https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
//22.【2009统考真题】已知一个带有表头结点的单链表，结点结构为data link，假设该链表只给出了头指针list。在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的结点（k为正整数）。若查找成功，算法输出该结点的data域的值，并返回1；否则，只返回0。要求：
//(1)描述算法的基本设计思想。
//定义两个指针变量p和q，初始时均指向头结点的下一个结点（链表的第一个结点），p指针沿链表移动；当p指针移动到第k个结点时，q指针开始与p指针同步移动；当P指针移动到最后一个结点时，q指针所指示结点为倒数第k个结点。以上过程对链表仅进行一遍扫描。
//(2)描述算法的详细实现步骤。
//(3)根据设计思想和实现步骤，采用程序设计语言描述算法（使用C或C++语言实现），关键之处请给出简要注释。
int Search_k(LinkList L, int k) {
    LNode *p = L->next, *q = L->next;
    int count = 0;
    while (p != NULL) {
        if (count < k)
            count++;
        else
            q = q->next;
        p = p->next;
    }
    if (count < k)
        return 0;
    else {
        printf("%d", q->data);
        return 1;
    }
}


//力扣160 https://leetcode.cn/problems/intersection-of-two-linked-lists/
//23.【2012统考真题】假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，可共享相同的后缀存储空间，例如，“loading”和“being”的存储映像如下图所示。设str1和str2分别指向两个单词所在单链表的头结点，链表结点结构为data next，请设计一个时间上尽可能高效的算法，找出由str1和str2所指向两个链表共同后缀的起始位置（如图中字符i所在结点的位置P）。要求：
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
int Listlen(LinkList L) {//默认带头结点
    int n = 0;
    L = L->next;
    while (L != NULL) {
        n++;
        L = L->next;
    }
    return n;
}

LNode *find_addr_1(LinkList str1, LinkList str2) {
    int str1len = Listlen(str1), str2len = Listlen(str2);
    LNode *p = str1->next, *q = str2->next;
    for (; str1len > str2len; str1len--)
        p = p->next;
    for (; str1len < str2len; str2len--)
        q = q->next;
    while (p != NULL && p != q) {
        p = p->next;
        q = q->next;
    }
    return p;
}

//解法2：力扣160 https://leetcode.cn/problems/intersection-of-two-linked-lists/solution/xiang-jiao-lian-biao-by-leetcode-solutio-a8jn/
LNode *find_addr_2(LinkList str1, LinkList str2) {
    if (str1 == NULL || str2 == NULL)
        return NULL;
    LNode *p = str1->next, *q = str2->next;
    while (p != q) {
        p = p == NULL ? str2->next : p->next;//先判断p是否为NULL，再进行三目运算符的运算，最后给p赋值
        q = q == NULL ? str1->next : q->next;
    }
    return p;
}
//(3)说明你所设计算法的时间复杂度。
//时间复杂度为O(len1+len2)或O(max(len1,len2))，其中len1、len2分别为两个链表的长度。


//力扣83 https://leetcode.cn/problems/remove-duplicates-from-sorted-list/
//24.【2015统考真题】用单链表保存m个整数，结点的结构为[data][link]，且|data|≤n（n为正整数）。现要求设计一个时间复杂度尽可能高效的算法，对于链表中data的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。要求：
//(1)给出算法的基本设计思想。
//(2)使用C或C++语言，给出单链表结点的数据类型定义。
//(3)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
void func(LinkList L, int n) {
    LNode *p = L, *r;
    int *q = (int *) malloc(sizeof(int) * (n + 1));
//    int q[n + 1] = {0};//报错，使用变量定义长度时，不可在定义时同时进行初始化赋值，需要在之后进行赋值
//    int q[n + 1];//这两句为正确的写法
//    q[n + 1] = {0};
//    for (int i = 0; i < n + 1; i++)//辅助空间初值置0
//        q[i] = 0;
    memset(q, 0, sizeof(int) * (n + 1));//上面辅助空间初值置0也可以用memset
    while (p->next != NULL) {
        if (q[abs(p->next->data)] == 0) {
            q[abs(p->next->data)] = 1;
            p = p->next;
        } else {
            r = p->next;
            p->next = r->next;
            free(r);
        }
    }
    free(q);
}
//(4)说明你所设计算法的时间复杂度和空间复杂度。
//参考答案所给算法的时间复杂度为O(m)，空间复杂度为O(n)。


//力扣143 https://leetcode.cn/problems/reorder-list/
//https://leetcode.cn/problems/reorder-list/solution/zhong-pai-lian-biao-by-leetcode-solution/
//25.【2019统考真题】设线性表L=(a1,a2,a3,…,an-2,an-1,an)采用带头结点的单链表保存，链表中的结点定义如下：
typedef struct node {
    int data;
    struct node *next;
} NODE;

//请设计一个空间复杂度为O(1)且时间上尽可能高效的算法，重新排列L中的各结点，得到线性表L'=(a1,an,a2,an-1,a3,an-2,…)。 要求：
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
void change_list(NODE *h) {
    NODE *p = h, *q = h, *r, *s;
    while (q->next != NULL) {
        p = p->next;
        q = q->next;
        if (q->next != NULL)
            q = q->next;
    }
    q = p->next;
    p->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }
    s = h->next;
    q = p->next;
    p->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = s->next;
        s->next = q;
        s = q->next;
        q = r;
    }
}
//(3)说明你所设计的算法的时间复杂度。
//第1步找中间结点的时间复杂度为O(n)，第2步逆置的时间复杂度为O(n)，第3步合并链表的时间复杂度为O(n)，所以该算法的时间复杂度为O(n)。


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
