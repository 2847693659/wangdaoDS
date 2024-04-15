#include <iostream>

//01.若希望循环队列中的元素都能得到利用，则需设置一个标志域tag，并以tag的值为0或1来区分队头指针front和队尾指针rear相同时的队列状态是“空”还是“满”。试编写与此结构相应的入队和出队算法。
#define MaxSize 100
typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int front, rear, tag;
} SqQueue1;

bool EnQueue1(SqQueue1 &Q, ElemType x) {
    if (Q.front == Q.rear && Q.tag == 1)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    Q.tag = 1;
    return true;
}

bool DeQueue1(SqQueue1 &Q, ElemType &x) {
    if (Q.front == Q.rear && Q.tag == 0)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    Q.tag = 0;
    return true;
}


//02.Q是一个队列，S是一个空栈，实现将队列中的元素逆置的算法。
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

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

void Reverse(SqStack &S, SqQueue &Q) {
    ElemType x;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, x);
        Push(S, x);
    }
    while (!StackEmpty(S)) {
        Pop(S, x);
        EnQueue(Q, x);
    }
}


//03.利用两个栈S1，S2来模拟一个队列，已知栈的4个运算定义如下：
//Push(S,x);//元素x入栈S
//Pop(S,x);//s出栈并将出栈的值赋给x
//StackEmpty(S);//判断栈是否为空
//StackOverflow(S);//判断栈是否满
//如何利用栈的运算来实现该队列的3个运算（形参由读者根据要求自己设计）？
//Enqueue;//将元素x入队
//Dequeue;//出队，并将出队元素存储在x中
//QueueEmpty;//判断队列是否为空
bool StackOverflow(SqStack S) {
    if (S.top > MaxSize - 1)
        return true;
    else
        return false;
}

bool EnQueue2(SqStack &S1, SqStack &S2, ElemType e) {
    if (!StackOverflow(S1)) {//S1不满
        Push(S1, e);
        return true;
    } else if (!StackEmpty(S2))//S1满且S2非空
        return false;
    else {//S1满但S2空
        while (!StackEmpty(S1)) {
            ElemType x;
            Pop(S1, x);
            Push(S2, x);
        }
        Push(S1, e);
        return true;
    }
}

bool DeQueue2(SqStack &S1, SqStack &S2, ElemType &x) {
    if (!StackEmpty(S2)) {//S2不为空
        Pop(S2, x);
        return true;
    } else if (StackEmpty(S1))//S1、S2均为空
        return false;
    else {//S2为空且S1不为空
        while (!StackEmpty(S1)) {
            Pop(S1, x);
            Push(S2, x);
        }
        Pop(S2, x);
        return true;
    }
}

bool QueueEmpty1(SqStack S1, SqStack S2) {
    if (StackEmpty(S1) && StackEmpty(S2))
        return true;
    else
        return false;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
