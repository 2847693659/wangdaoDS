#include <iostream>

#define MaxSize 100
typedef int ElemType;
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    BiTNode *data[MaxSize];
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

bool Push(SqStack &S, BiTNode *x) {
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, BiTNode *&x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

bool GetTop(SqStack S, BiTNode *&x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}

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

//03.��д��������������ķǵݹ��㷨
void PostOrder(BiTree T) {
    SqStack S;
    InitStack(S);
    BiTNode *p = T, *r = NULL;
    while (p || !StackEmpty(S)) {
        if (p) {//�ߵ������
            Push(S, p);
            p = p->lchild;
        } else {//����
            GetTop(S, p);//��ջ����㣨�ǳ�ջ��
            if (p->rchild && p->rchild != r)//�����������ڣ���δ�����ʹ�
                p = p->rchild;//ת����
            else {//���򣬵�����㲢����
                Pop(S, p);//����㵯��
                //visit(p->data);//���ʸý��
                r = p;//��¼������ʹ��Ľ��
                p = NULL;//�������������pָ��
            }
        }
    }
}
//ע�⣺ÿ�γ�ջ������һ�������൱�ڱ������Ըý��Ϊ�����������轫p��NULL


//04.�Ը��������������¶��ϡ����ҵ���Ĳ�α����㷨
//������������Ĳ�������෴�����Խ���������Ľ����ջ�ٳ�ջ����Ϊ������
void InvertLevel(BiTree T) {
    SqStack S;
    SqQueue Q;
    BiTNode *p;
    if (T != NULL) {
        InitStack(S);
        InitQueue(Q);
        EnQueue(Q, T);
        while (!QueueEmpty(Q)) {
            DeQueue(Q, p);
            Push(S, p);
            if (p->lchild)
                EnQueue(Q, p->lchild);
            if (p->rchild)
                EnQueue(Q, p->rchild);
        }
        while (!StackEmpty(S)) {
            Pop(S, p);
            //visit(p->data);
        }
    }
}


//05.������������ö�������洢�ṹ�����һ���ǵݹ��㷨��������ĸ߶�
//���ò�α������㷨�����ñ���level��¼��ǰ������ڵĲ��������ñ���lastָ��ǰ������ҽ�㣬ÿ�β�α�������ʱ��lastָ��Ƚϣ���������ȣ��������1������lastָ����һ������ҽ�㣬ֱ��������ɡ�level��ֵ��Ϊ�������ĸ߶ȡ�
int Btdepth(BiTree T) {
    if (T == NULL)//���գ��߶�Ϊ0
        return 0;
    int front = -1, rear = -1;
    int last = 0, level = 0;//lastָ��ǰ������ҽ��
    BiTNode *Q[MaxSize];//���ö���Q��Ԫ���Ƕ��������ָ���������㹻
    Q[++rear] = T;//����������
    BiTNode *p;
    while (front < rear) {//�Ӳ��գ���ѭ��
        p = Q[++front];//����Ԫ�س��ӣ������ڷ��ʵĽ��
        if (p->lchild)
            Q[++rear] = p->lchild;//�������
        if (p->rchild)
            Q[++rear] = p->rchild;//�Һ������
        if (front == last) {//����ò�����ҽ��
            level++;//������1
            last = rear;//lastָ���²�
        }
    }
    return level;
}

//��ĳ��Ľ�������ÿ��Ľ���������������ȵȣ���������������Ƶ�˼�롣��Ȼ������ɱ�д�ݹ��㷨����ʵ�����£�
int Btdepth2(BiTree T) {
    if (T == NULL)
        return 0;
    int ldepth, rdepth;
    ldepth = Btdepth2(T->lchild);
    rdepth = Btdepth2(T->rchild);
    if (ldepth > rdepth)
        return ldepth + 1;
    else
        return rdepth + 1;
}


//06.��һ�ö������и�����ֵ������ͬ��������������к�����������зֱ��������һά����A[1...n]��B[1...n]�У��Ա�д�㷨�����ö������Ķ�������
BiTree PreInCreate(ElemType A[], ElemType B[], int h1, int r1, int h2, int r2) {
    BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
    root->data = A[h1];
    int i;
    for (i = h2; B[i] != root->data; i++);
    int llen = i - h2, rlen = r2 - i;
    if (llen != 0)
        root->lchild = PreInCreate(A, B, h1 + 1, h1 + llen, h2, h2 + llen - 1);
    else
        root->lchild = NULL;
    if (rlen != 0)
        root->rchild = PreInCreate(A, B, r1 - rlen + 1, r1, r2 - rlen + 1, r2);
    else
        root->rchild = NULL;
    return root;
}


//07.������������������ʽ�洢��дһ���б�����������Ƿ�����ȫ���������㷨
//�㷨˼�룺���ò�α����㷨�������н�������У������ս�㣩�������ս��ʱ���鿴����Ƿ��зǿս�㡣���У��������������ȫ��������
bool IsComplete(BiTree T) {
    SqQueue Q;
    BiTNode *p;
    InitQueue(Q);
    if (T == NULL)
        return true;//����Ϊ��������
    EnQueue(Q, T);
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        if (p != NULL) {//���ǿգ������������������
            EnQueue(Q, p->lchild);
            EnQueue(Q, p->rchild);
        } else {//���Ϊ�գ��������Ƿ��зǿս��
            while (!QueueEmpty(Q)) {
                DeQueue(Q, p);
                if (p != NULL)//���ǿգ��������Ϊ����ȫ������
                    return false;
            }
        }
    }
    return true;
}


//08.������������ö�������洢�ṹ�洢�������һ���㷨������һ�ø���������������˫��֧������
int DsonNodes(BiTree T) {
    if (T == NULL)
        return 0;
    else if (T->lchild != NULL && T->rchild != NULL)//˫��֧���
        return DsonNodes(T->lchild) + DsonNodes(T->rchild) + 1;
    else
        return DsonNodes(T->lchild) + DsonNodes(T->rchild);
}


//09.����B��һ�ò�����ʽ�ṹ�洢�Ķ���������дһ������B�����н��������������н����ĺ���
void swap(BiTree T) {
    BiTNode *temp;
    if (T != NULL) {
        swap(T->lchild);//�ݹ�ؽ���������
        swap(T->rchild);//�ݹ�ؽ���������
        temp = T->lchild;//�������Һ��ӽ��
        T->lchild = T->rchild;
        T->rchild = temp;
    }
}


//10.������������ö������洢�ṹ�洢�����һ���㷨����������������е�k��1 �� k �� �������н�������������ֵ
int num = 1;//������ŵ�ȫ�ֱ���

ElemType PreNode(BiTree T, int k) {
    if (T == NULL)//�ս�㣬�򷵻������ַ�
        return '#';
    if (num == k)//��ȣ���ǰ��㼴Ϊ��k�����
        return T->data;
    num++;//��һ�����
    ElemType e;
    e = PreNode(T->lchild, k);//�������еݹ�Ѱ��
    if (e != '#')//���������У��򷵻ظ�ֵ
        return e;
    e = PreNode(T->rchild, k);//���������еݹ�Ѱ��
    return e;
}


//11.��֪�������Զ�������洢����д�㷨��ɣ���������ÿ��Ԫ��ֵΪx�Ľ�㣬ɾȥ����Ϊ�������������ͷ���Ӧ�Ŀռ�
//ɾ����Ԫ��ֵxΪ����������ֻҪ��ɾ���������������Ϳ����ͷ�ֵΪx�ĸ���㣬����˲��ú���������㷨˼�룺ɾ��ֵΪx�Ľ�㣬��ζ��Ӧ���丸�������ң���Ůָ���ÿգ��ò�α��������ҵ�ĳ���ĸ���㡣����Ҫ��ɾ������ÿ��Ԫ��ֵΪx�Ľ������������Ҫ���������ö�������
void DeleteXTree(BiTree &T) {//ɾ����TΪ��������
    if (T != NULL) {
        DeleteXTree(T->lchild);
        DeleteXTree(T->rchild);
        free(T);
    }
}

void Search1(BiTree T, ElemType x) {
    SqQueue Q;
    if (T != NULL) {
        if (T->data == x) {
            DeleteXTree(T);
            exit(0);
        }
        BiTNode *p;
        InitQueue(Q);
        EnQueue(Q, T);
        while (!QueueEmpty(Q)) {
            DeQueue(Q, p);
            if (p->lchild != NULL) {
                if (p->lchild->data == x) {
                    DeleteXTree(p->lchild);
                    p->lchild = NULL;
                } else
                    EnQueue(Q, p->lchild);
            }
            if (p->rchild != NULL) {
                if (p->rchild->data == x) {
                    DeleteXTree(p->rchild);
                    p->rchild = NULL;
                } else
                    EnQueue(Q, p->rchild);
            }
        }
    }
}


//12.�ڶ������в���ֵΪx�Ľ�㣬�Ա�д�㷨��ӡֵΪx�Ľ����������ȣ�����ֵΪx�Ľ�㲻����һ��
//�㷨˼�룺���÷ǵݹ��������������ʸ���㣬���ʵ�ֵΪx�Ľ��ʱ��ջ������Ԫ�ؾ�Ϊ�ý������ȣ����γ�ջ��ӡ���ɡ�
typedef struct {
    BiTNode *t;
    int tag;//tag=0��ʾ����Ů�����ʣ�tag=1��ʾ����Ů������
} stack;

void Search2(BiTree T, ElemType x) {
    BiTNode *p = T;
    stack s[MaxSize];
    int top = 0;
    while (p != NULL || top > 0) {
        while (p != NULL && p->data != x) {//�����ջ
            s[++top].t = p;
            s[top].tag = 0;
            p = p->lchild;//�����֧����
        }
        if (p != NULL && p->data == x) {//�ҵ�x
            for (int i = 1; i <= top; i++)
                printf("%d", s[i].t->data);
            exit(1);//�������ֵ�����
        }
        while (top != 0 && s[top].tag == 1)//��ջ���ձ�����
            top--;
        if (top != 0) {
            s[top].tag = 1;
            p = s[top].t->rchild;//���ҷ�֧���±���
        }
    }
}


//13.��һ�ö������Ľ��ṹΪ��LLINK��INFO��RLINK����ROOTΪָ��ö�����������ָ�룬p��q�ֱ�Ϊָ��ö�������������������ָ�룬�Ա�д�㷨ANCESTOR(ROOT,p,q,r)���ҵ�p��q������������Ƚ��r
//������������ʸ���㣬���ڵݹ��㷨�У�����ѹ��ջ�׵ġ�����Ҫ��p��q������������Ƚ��x����ʧһ���ԣ���p��q����ߡ��㷨˼�룺���ú���ǵݹ��㷨��ջ�д�Ŷ���������ָ�룬�����ʵ�ĳ���ʱ��ջ������Ԫ�ؾ�Ϊ�ý������ȡ����������Ȼ�ȱ��������p��ջ��Ԫ�ؾ�Ϊp�����ȡ��Ƚ�ջ���Ƶ���һ����ջ�С��������������qʱ����ջ��Ԫ�ش�ջ����ʼ���������ջ��ȥƥ�䣬��һ��ƥ�䣨����ȣ���Ԫ�ؾ��ǽ��p��q������������ȡ�
stack s[MaxSize], s1[MaxSize];//�����stack�ṹ��
BiTNode *Ancestor(BiTree ROOT, BiTNode *p, BiTNode *q) {
    BiTNode *bt = ROOT;
    int top = 0, top1;
    while (bt != NULL || top > 0) {
        while (bt != NULL) {
            s[++top].t = bt;
            s[top].tag = 0;
            bt = bt->lchild;//�����֧����
        }
        while (top != 0 && s[top].tag == 1) {//�ٶ�p��q����࣬����pʱ��ջ��Ԫ�ؾ�Ϊp������
            if (s[top].t == p) {
                for (int i = 1; i <= top; i++) {//��ջs��Ԫ��ת�븨��ջs1����
                    s1[i] = s[i];
                }
                top1 = top;
            }
            if (s[top].t == q) {//�ҵ�q���
                for (int i = top; i > 0; i--) {//��ջ��Ԫ�ص�����㵽s1��ȥƥ��
                    for (int j = top1; j > 0; j--) {
                        if (s1[j].t == s[i].t)
                            return s[i].t;//p��q����������������ҵ�
                    }
                }
            }
            top--;//��ջ
        }
        if (top != 0) {
            s[top].tag = 1;
            bt = s[top].t->rchild;//���ҷ�֧���±���
        }
    }
    return NULL;//p��q�޹�������
}


//14.������������ö�������洢�ṹ�����һ���㷨����ǿն�����b�Ŀ�ȣ������н����������һ��Ľ�������
typedef struct {
    BiTNode *data[MaxSize];//��������еĽ��ָ��
    int level[MaxSize];//����data����ͬ�±���Ĳ��
    int front, rear;
} Queue;

int BTWidth(BiTree T) {
    BiTNode *p;
    Queue Q;
    int k;
    Q.front = Q.rear = -1;//����Ϊ��
    Q.rear++;
    Q.data[Q.rear] = T;//�����ָ�����
    Q.level[Q.rear] = 1;//�������Ϊ1
    while (Q.front < Q.rear) {
        Q.front++;//����
        p = Q.data[Q.front];//���ӽ��
        k = Q.level[Q.front];//���ӽ��Ĳ��
        if (p->lchild != NULL) {//���ӽ�����
            Q.rear++;
            Q.data[Q.rear] = p->lchild;
            Q.level[Q.rear] = k + 1;
        }
        if (p->rchild != NULL) {//�Һ��ӽ�����
            Q.rear++;
            Q.data[Q.rear] = p->rchild;
            Q.level[Q.rear] = k + 1;
        }
    }
    int max = 0, i = 0;//max����ͬһ�����Ľ�����
    k = 1;//k��ʾ�ӵ�һ�㿪ʼ����
    while (i <= Q.rear) {//iɨ���������Ԫ��
        int n = 0;//nͳ�Ƶ�k��Ľ�����
        while (i <= Q.rear && Q.level[i] == k) {
            n++;
            i++;
        }
        k = Q.level[i];
        if (n > max)//��������n
            max = n;
    }
    return max;
}


//15.����һ���������������н��ֵ����ͬ������֪����������Ϊpre�����һ���㷨�����������post
void PreToPost(ElemType pre[], int h1, int r1, ElemType post[], int h2, int r2) {
    int half;
    if (r1 >= h1) {
        post[r2] = pre[h1];
        half = (r1 - h1) / 2;
        PreToPost(pre, h1 + 1, h1 + half, post, h2, h2 + half - 1);//ת��������
        PreToPost(pre, h1 + half + 1, r1, post, h2 + half, r2 - 1);//ת��������
    }
}


//16.���һ���㷨����������Ҷ��㰴�����ҵ�˳������һ����������ͷָ��Ϊhead������������������ʽ�洢������ʱ��Ҷ������ָ��������ŵ�����ָ�롣
BiTNode *head, *pre = NULL;//ȫ�ֱ���

BiTree InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->lchild);//�������������
        if (T->lchild == NULL && T->rchild == NULL) {//Ҷ���
            if (pre == NULL) {//�����һ��Ҷ���
                head = T;
                pre = T;
            } else {//��Ҷ�����������
                pre->rchild = T;
                pre = T;
            }
        }
        InOrder(T->rchild);//�������������
        pre->rchild = NULL;//��������β
    }
    return head;
}


//17.������ж����ö������Ƿ����Ƶ��㷨����ν������T1��T2���ƣ�ָ����T1��T2���ǿյĶ�������ֻ��һ������㣻��T����������T2�������������Ƶģ���T����������T2�������������Ƶ�
bool similar(BiTree T1, BiTree T2) {
    bool leftS, rightS;
    if (T1 == NULL && T2 == NULL)//�����Կ�
        return true;
    else if (T1 == NULL || T2 == NULL)//ֻ��һ��Ϊ��
        return false;
    else {//�ݹ��ж�
        leftS = similar(T1->lchild, T2->lchild);
        rightS = similar(T1->rchild, T2->rchild);
        return leftS && rightS;
    }
}


//18.д�����������������������ָ������ں����ǰ�������㷨
typedef struct BiThreadNode {
    ElemType data;
    struct BiThreadNode *lchild, *rchild;
    int ltag, rtag;
} BiThreadNode, *BiThreadTree;

BiThreadNode *InPostPre(BiThreadTree T, BiThreadNode *p) {
    BiThreadNode *q;
    if (p->rtag == 0)//��p������Ů��������Ů�������ǰ��
        q = p->rchild;
    else if (p->ltag == 0)//��pֻ������Ů��������Ů�������ǰ��
        q = p->lchild;
    else if (p->lchild == NULL)//p���������е�һ��㣬�޺���ǰ��
        q = NULL;
    else {//˳������������p�����ȣ������ڣ��������ȵ�����Ů
        while (p->ltag == 1 && p->lchild != NULL)//�����p������Ů���ޣ���������������ָ��ĳ���Ƚ��f��p��f�������а���������ĵ�һ����㣩����f������Ů����˳��ǰ����˫�׵�˫�ף�һֱ�ҵ�˫��������Ů����ʱ����Ů��p��ǰ����
            p = p->lchild;
        if (p->ltag == 0)//��f������Ů����������Ů�ǽ��p�ں����µ�ǰ��,��p�������ȵ�����Ů�������ǰ��
            q = p->lchild;
        else
            q = NULL;//���е�֧����p��Ҷ�ӣ����ѵ�����㣬p�޺���ǰ��
    }
    return q;
}

//19.��2014ͳ�����⡿�������Ĵ�Ȩ·�����ȣ�WPL���Ƕ�����������Ҷ���Ĵ�Ȩ·������֮�͡�����һ�ö�����T�����ö�������洢�����ṹΪleft weight right������Ҷ����weight�򱣴�ý��ķǸ�Ȩֵ����rootΪָ��T�ĸ�����ָ�룬�������T��WPL���㷨��Ҫ��
//(1)�����㷨�Ļ������˼��
//(2)ʹ��C��C++���ԣ����������������������Ͷ���
//(3)�������˼�룬����C��C++���������㷨���ؼ�֮������ע��
typedef struct BiWeightTNode {
    int weight;
    struct BiWeightTNode *lchild, *rchild;
} BiWeightTNode, *BiWeightTree;

//��������������㷨��
int wpl_PreOrder(BiWeightTree root, int depth) {
    static int wpl = 0;//���徲̬�ֲ������洢wpl
    if (root->lchild == NULL && root->rchild == NULL)//��ΪҶ��㣬���ۻ�wpl
        wpl += depth * root->weight;
    if (root->lchild != NULL)//�����������գ�����������ݹ����
        wpl_PreOrder(root->lchild, depth + 1);
    if (root->rchild != NULL)//�����������գ�����������ݹ����
        wpl_PreOrder(root->rchild, depth + 1);
    return wpl;
}

int WPL(BiWeightTree root) {
    return wpl_PreOrder(root, 0);
}

//���ڲ�α������㷨��
int wpl_LevelOrder(BiWeightTree root) {
    BiWeightTNode *Q[MaxSize];//��������
    int front = 0, rear = 0;//frontΪͷָ�룬rearΪβָ�룬ͷָ��ָ���ͷԪ�أ�βָ��ָ���β�ĺ�һ��Ԫ��
    int wpl = 0, depth = 0;//��ʼ��wpl�����
    BiWeightTNode *lastNode = root, *newlastNode = NULL;//lastNode������¼��ǰ������һ����㣬lastNode��ʼ��Ϊ����㣬newlastNode������¼��һ������һ����㣬newlastNode��ʼ��Ϊ��
    Q[rear++] = root;//��������
    while (front < rear) {//��α����������в�����ѭ��
        BiWeightTNode *p = Q[front++];//�ó������е�ͷԪ��
        if (p->lchild == NULL && p->rchild == NULL)//��ΪҶ��㣬��ͳ��wpl
            wpl += depth * p->weight;
        if (p->lchild != NULL) {//����Ҷ��㣬�����������
            Q[rear++] = p->lchild;
            newlastNode = p->lchild;//������һ������һ�����Ϊ�ý�������
        }
        if (p->rchild != NULL) {//�����Ҷ��㣬���ҽ�����
            Q[rear++] = p->rchild;
            newlastNode = p->rchild;
        }
        if (p == lastNode) {//���ý��Ϊ�������һ����㣬�����lastNode
            lastNode = newlastNode;
            depth++;//������1
        }
    }
    return wpl;//����wpl
}


//20.��2017ͳ�����⡿�����һ���㷨���������ı��ʽ������������ת��Ϊ�ȼ۵���׺���ʽ��ͨ�����ŷ�ӳ�������ļ�����򣩲���������磬���������ñ��ʽ����Ϊ�㷨������ʱ������ĵȼ���׺���ʽ�ֱ�Ϊ(a+b)*(c*(-d))��(a*b)+(-(c-d))��
//��������㶨�����£�
typedef struct node {
    char data[10];//�洢�������������
    struct node *left, *right;
} BTree;
//Ҫ��
//(1)�����㷨�Ļ������˼��
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע��

void BTreeToExp(BTree *root, int depth) {
    if (root == NULL)//�ս�㷵��
        return;
    else if (root->left == NULL && root->right == NULL)//��ΪҶ���
        printf("%s", root->data);//�������������������
    else {//Ϊ��֧���
        if (depth > 1)//�����ӱ��ʽ���1������
            printf("(");
        BTreeToExp(root->left, depth + 1);
        printf("%s", root->data);//���������
        BTreeToExp(root->right, depth + 1);
        if (depth > 1)//�����ӱ��ʽ���1������
            printf(")");
    }
}

void BTreeToE(BTree *root) {
    BTreeToExp(root, 1);//���ĸ߶�Ϊ1
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
