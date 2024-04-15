#include <iostream>

//03.假设以I和O分别表示入栈和出栈操作。栈的初态和终态均为空，入栈和出栈的操作序列可表示为仅由I和O组成的序列，可以操作的序列称为合法序列，否则称为非法序列。
//(2)通过对(1)的分析，写出一个算法，判定所给的操作序列是否合法。若合法，返回true，否则返回false（假定被判定的操作序列已存入一维数组中）。
//设被判定的操作序列已存入一维数组A中。算法的基本设计思想：依次逐一扫描入栈出栈序列（即由“I”和“O”组成的字符串），每扫描至任一位置均需检查出栈次数（即“O”的个数）是否小于入栈次数（“I”的个数），若大于则为非法序列。扫描结束后，再判断入栈和出栈次数是否相等，若不相等则不合题意，为非法序列。
bool Judge(char A[]) {
    int i = 0;
    int j = 0, k = 0;//i为下标，j和k分别为字母I和O的个数
    while (A[i] != '\0') {//未到字符数组尾
        switch (A[i]) {
            case 'I':
                j++;//入栈次数增1
                break;
            case 'O':
                k++;
        }
        if (k > j)
            exit(0);
        i++;//不论A[i]是“I”或“O”，指针i均后移
    }
    if (j == k)
        return true;
    else
        return false;
}


//04.设单链表的表头指针为L，结点结构由data和next两个域构成，其中data域为字符型。试设计算法判断该链表的全部n个字符是否中心对称。例如xyx、xyyx都是中心对称。
//算法思想：使用栈来判断链表中的数据是否中心对称。让链表的前一半元素依次进栈。在处理链表的后一半元素时，当访问到链表的一个元素后，就从栈中弹出一个元素，两个元素比较，若相等，则将链表中的下一个元素与栈中再弹出的元素比较，直至链表到尾。这时若栈是空栈，则得出链表中心对称的结论；否则，当链表中的一个元素与栈中弹出元素不等时，结论为链表非中心对称，结束算法的执行。
typedef struct LNode {
    char data;
    struct LNode *next;
} LNode, *LinkList;

bool dc(LinkList L, int n) {//L带头结点
    int i;
    char s[n / 2];//s字符栈
    LNode *p = L->next;//p是链表的工作指针，指向待处理的当前元素
    for (i = 0; i < n / 2; i++) {//链表前一半元素进栈
        s[i] = p->data;
        p = p->next;
    }
    i--;//恢复最后的i值
    if (n % 2 == 1)//若n是奇数，后移过中心结点
        p = p->next;
    while (p != NULL && s[i] == p->data) {//检测是否中心对称
        i--;//i充当栈顶指针
        p = p->next;
    }
    if (i == -1)//栈为空栈
        return true;//链表中心对称
    else
        return false;//链表不中心对称
}


//05.设有两个栈s1、s2都采用顺序栈方式，并共享一个存储区[0,…,maxsize-1]，为了尽量利用空间，减少溢出的可能，可采用栈顶相向、迎面增长的存储方式。试设计s1、s2有关入栈和出栈的操作算法。
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
