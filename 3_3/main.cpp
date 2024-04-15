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

//01.����һ���������ʽ�а���Բ���š������źͻ�����3�����͵����ţ���дһ���㷨���б���ʽ�е������Ƿ���ԣ����ַ���\0����Ϊ�������ʽ�Ľ�������
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


//02.����ͼ��ʾ�������г�����ȣ�ע�⣬����������Ϊ������ʻ�����𳵵���վ��һ�����ڵ��ȵġ�ջ���������𳵵���վ����ڴ���n��Ӳ�����������ᣨ�ֱ���H��S��ʾ���ȴ����ȣ��Ա�д�㷨���������n�ڳ�����е��ȵĲ���������ջ���ջ���������У���ʹ���е��������ᶼ��������Ӳ������֮ǰ��
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


//03.����һ��ջʵ�����µݹ麯���ķǵݹ���㣺
//�㷨˼�룺����һ��ջ���ڱ���n�Ͷ�Ӧ��Pn(x)ֵ��ջ������Ԫ�ص�Pn(x)�����й�ϵ��Ȼ��߳�ջ�߼���Pn(x)��ջ�պ��ֵ�ͼ�������ˡ�
struct stack {
    int no;//����n
    double val;//����Pn(x)��ֵ
} stack[MaxSize];

double p(int n, double x) {
    double p1 = 1, p2 = 2 * x;
    if (n == 0)
        return p1;
    else if (n == 1)
        return p2;
    else {
        int top = -1;
        for (int i = n; i > 2; i--) {//��ջ
            top++;
            stack[top].no = i;//ջ�״��p(n)
        }
        while (top >= 0) {//��ջ
            stack[top].val = 2 * x * p2 - 2 * (stack[top].no - 1) * p1;
            p1 = p2;
            p2 = stack[top].val;
            top--;
        }
        return stack[0].val;
    }
}


//04.ĳ�����ֶɿڣ������ɴ�ÿ������10��������������������Ϊ�ͳ���ͻ����࣬�϶ɴ������¹涨��ͬ�೵�ȵ����ϴ����ͳ����ڻ����ϴ�����ÿ��4���ͳ������������1�����������ȴ��ͳ�����4�������Ի������棻���޻����ȴ�������ͳ����ϴ��������һ���㷨ģ��ɿڹ���
//�㷨˼�룺��������q������±�Ϊ10��ǡ����ÿ���ضɵ������������ͳ��Ķ���Ϊqk�������Ķ���Ϊqh����qk���㣬��ÿȡ4��qkԪ�غ���ȡһ��qhԪ�أ�ֱ��q�ĳ���Ϊ10����qk�����㣬��ֱ����qh���롣
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

void manager(SqQueue &q, SqQueue &qk, SqQueue &qh) {//q�ɴ����У�qk�ͳ����У�qh��������
    int i = 0, j = 0;//j��ʾ�ɴ��ϵ��ܳ�����
    ElemType x;
    while (j < 10) {//����10��ʱ
        if (!QueueEmpty(qk) && i < 4) {//�ͳ����в��գ���δ����4��
            DeQueue(qk, x);//�ӿͳ����г���
            EnQueue(q, x);//�ͳ��϶ɴ�
            i++;//�ͳ�����1
            j++;//�ɴ��ϵ��ܳ�������1
        } else if (i == 4 && !QueueEmpty(qh)) {//�ͳ�������4��
            DeQueue(qh, x);//�ӻ������г���
            EnQueue(q, x);//�����϶ɴ�
            j++;//�ɴ��ϵ��ܳ�������1
            i = 0;//ÿ��һ��������i���¼���
        } else {//����������ͳ����пջ�������пգ�
            while (j < 10 && i < 4 && !QueueEmpty(qh)) {//�ͳ����п�
                DeQueue(qh, x);//�ӻ������г���
                EnQueue(q, x);//�����϶ɴ�
                i++;//i��������i>4ʱ���˳���ѭ��
                j++;//�ɴ��ϵ��ܳ�������1
            }
            i = 0;
        }
        if (QueueEmpty(qk) && QueueEmpty(qh))//�������Ϳͳ�����������10��
            break;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
