#include <iostream>

#define MaxSize 100
typedef char ElemType;
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S) {
    S.top = -1;
}

bool StackEmpty(SqStack S) {
    if (S.top == -1)
        return true;
    else
        return false;
}

bool Push(SqStack &S, ElemType x) {
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, ElemType &x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

//01.假设一个算术表达式中包含圆括号、方括号和花括号3种类型的括号，编写一个算法来判别表达式中的括号是否配对，以字符“\0”作为算术表达式的结束符。
bool BracketCheck(char *str) {
    SqStack S;
    InitStack(S);
    int i = 0;
    ElemType e;
    while (str[i] != '\0') {
        switch (str[i]) {
            case '(':
                Push(S, '(');
                break;
            case '[':
                Push(S, '[');
                break;
            case '{':
                Push(S, '{');
                break;
            case ')':
                Pop(S, e);
                if (e != '(')
                    return false;
            case ']':
                Pop(S, e);
                if (e != '[')
                    return false;
            case '}':
                Pop(S, e);
                if (e != '{')
                    return false;
            default:
                break;
        }
        i++;
    }
    if (StackEmpty(S))
        return true;
    else
        return false;
}


//02.按下图所示铁道进行车厢调度（注意，两侧铁道均为单向行驶道，火车调度站有一个用于调度的“栈道”），火车调度站的入口处有n节硬座和软座车厢（分别用H和S表示）等待调度，试编写算法，输出对这n节车厢进行调度的操作（即入栈或出栈操作）序列，以使所有的软座车厢都被调整到硬座车厢之前。
void Train_Arrange(char *train) {
    SqStack S;
    InitStack(S);
    char *p = train, *q = train, c;
    while (*p != '\0') {
        switch (*p) {
            case 'H':
                Push(S, *p);
            case 'S':
                *(q++) = *p;
            default:
                break;
        }
        p++;
    }
    while (!StackEmpty(S)) {
        Pop(S, c);
        *(q++) = c;
    }
}


//03.利用一个栈实现以下递归函数的非递归计算：
//算法思想：设置一个栈用于保存n和对应的Pn(x)值，栈中相邻元素的Pn(x)有题中关系。然后边出栈边计算Pn(x)，栈空后该值就计算出来了。
struct stack {
    int no;//保存n
    double val;//保存Pn(x)的值
} stack[MaxSize];

double p(int n, double x) {
    double p1 = 1, p2 = 2 * x;
    if (n == 0)
        return p1;
    else if (n == 1)
        return p2;
    else {
        int top = -1;
        for (int i = n; i > 2; i--) {//入栈
            top++;
            stack[top].no = i;//栈底存放p(n)
        }
        while (top >= 0) {//出栈
            stack[top].val = 2 * x * p2 - 2 * (stack[top].no - 1) * p1;
            p1 = p2;
            p2 = stack[top].val;
            top--;
        }
        return stack[0].val;
    }
}


//04.某汽车轮渡口，过江渡船每次能载10辆车过江。过江车辆分为客车类和货车类，上渡船有如下规定：同类车先到先上船；客车先于货车上船，且每上4辆客车，才允许放上1辆货车；若等待客车不足4辆，则以货车代替；若无货车等待，允许客车都上船。试设计一个算法模拟渡口管理。
//算法思想：假设数组q的最大下标为10，恰好是每次载渡的最大量。假设客车的队列为qk，货车的队列为qh。若qk充足，则每取4个qk元素后再取一个qh元素，直到q的长度为10。若qk不充足，则直接用qh补齐。
typedef struct {
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;

bool QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q, ElemType x) {
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q, ElemType &x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

void manager(SqQueue &q, SqQueue &qk, SqQueue &qh) {//q渡船队列，qk客车队列，qh货车队列
    int i = 0, j = 0;//j表示渡船上的总车辆数
    ElemType x;
    while (j < 10) {//不足10辆时
        if (!QueueEmpty(qk) && i < 4) {//客车队列不空，且未上足4辆
            DeQueue(qk, x);//从客车队列出队
            EnQueue(q, x);//客车上渡船
            i++;//客车数加1
            j++;//渡船上的总车辆数加1
        } else if (i == 4 && !QueueEmpty(qh)) {//客车已上足4辆
            DeQueue(qh, x);//从货车队列出队
            EnQueue(q, x);//货车上渡船
            j++;//渡船上的总车辆数加1
            i = 0;//每上一辆货车，i重新计数
        } else {//其他情况（客车队列空或货车队列空）
            while (j < 10 && i < 4 && !QueueEmpty(qh)) {//客车队列空
                DeQueue(qh, x);//从货车队列出队
                EnQueue(q, x);//货车上渡船
                i++;//i计数，当i>4时，退出本循环
                j++;//渡船上的总车辆数加1
            }
            i = 0;
        }
        if (QueueEmpty(qk) && QueueEmpty(qh))//若货车和客车加起来不足10辆
            break;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
