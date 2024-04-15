#include <iostream>

//01.��ϣ��ѭ�������е�Ԫ�ض��ܵõ����ã���������һ����־��tag������tag��ֵΪ0��1�����ֶ�ͷָ��front�Ͷ�βָ��rear��ͬʱ�Ķ���״̬�ǡ��ա����ǡ��������Ա�д��˽ṹ��Ӧ����Ӻͳ����㷨��
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


//02.Q��һ�����У�S��һ����ջ��ʵ�ֽ������е�Ԫ�����õ��㷨��
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


//03.��������ջS1��S2��ģ��һ�����У���֪ջ��4�����㶨�����£�
//Push(S,x);//Ԫ��x��ջS
//Pop(S,x);//s��ջ������ջ��ֵ����x
//StackEmpty(S);//�ж�ջ�Ƿ�Ϊ��
//StackOverflow(S);//�ж�ջ�Ƿ���
//�������ջ��������ʵ�ָö��е�3�����㣨�β��ɶ��߸���Ҫ���Լ���ƣ���
//Enqueue;//��Ԫ��x���
//Dequeue;//���ӣ���������Ԫ�ش洢��x��
//QueueEmpty;//�ж϶����Ƿ�Ϊ��
bool StackOverflow(SqStack S) {
    if (S.top > MaxSize - 1)
        return true;
    else
        return false;
}

bool EnQueue2(SqStack &S1, SqStack &S2, ElemType e) {
    if (!StackOverflow(S1)) {//S1����
        Push(S1, e);
        return true;
    } else if (!StackEmpty(S2))//S1����S2�ǿ�
        return false;
    else {//S1����S2��
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
    if (!StackEmpty(S2)) {//S2��Ϊ��
        Pop(S2, x);
        return true;
    } else if (StackEmpty(S1))//S1��S2��Ϊ��
        return false;
    else {//S2Ϊ����S1��Ϊ��
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
