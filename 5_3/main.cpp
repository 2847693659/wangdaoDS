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

//03.编写后序遍历二叉树的非递归算法
void PostOrder(BiTree T) {
    SqStack S;
    InitStack(S);
    BiTNode *p = T, *r = NULL;
    while (p || !StackEmpty(S)) {
        if (p) {//走到最左边
            Push(S, p);
            p = p->lchild;
        } else {//向右
            GetTop(S, p);//读栈顶结点（非出栈）
            if (p->rchild && p->rchild != r)//若右子树存在，且未被访问过
                p = p->rchild;//转向右
            else {//否则，弹出结点并访问
                Pop(S, p);//将结点弹出
                //visit(p->data);//访问该结点
                r = p;//记录最近访问过的结点
                p = NULL;//结点访问完后，重置p指针
            }
        }
    }
}
//注意：每次出栈访问完一个结点就相当于遍历完以该结点为根的子树，需将p置NULL


//04.试给出二叉树的自下而上、从右到左的层次遍历算法
//正好与二叉树的层序遍历相反，可以将层序遍历的结果入栈再出栈，即为所求结果
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


//05.假设二叉树采用二叉链表存储结构，设计一个非递归算法求二叉树的高度
//采用层次遍历的算法，设置变量level记录当前结点所在的层数，设置变量last指向当前层的最右结点，每次层次遍历出队时与last指针比较，若两者相等，则层数加1，并让last指向下一层的最右结点，直到遍历完成。level的值即为二叉树的高度。
int Btdepth(BiTree T) {
    if (T == NULL)//树空，高度为0
        return 0;
    int front = -1, rear = -1;
    int last = 0, level = 0;//last指向当前层的最右结点
    BiTNode *Q[MaxSize];//设置队列Q，元素是二叉树结点指针且容量足够
    Q[++rear] = T;//将根结点入队
    BiTNode *p;
    while (front < rear) {//队不空，则循环
        p = Q[++front];//队列元素出队，即正在访问的结点
        if (p->lchild)
            Q[++rear] = p->lchild;//左孩子入队
        if (p->rchild)
            Q[++rear] = p->rchild;//右孩子入队
        if (front == last) {//处理该层的最右结点
            level++;//层数增1
            last = rear;//last指向下层
        }
    }
    return level;
}

//求某层的结点个数、每层的结点个数、树的最大宽度等，都采用与此题类似的思想。当然，此题可编写递归算法，其实现如下：
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


//06.设一棵二叉树中各结点的值互不相同，其先序遍历序列和中序遍历序列分别存于两个一维数组A[1...n]和B[1...n]中，试编写算法建立该二叉树的二叉链表
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


//07.二叉树按二叉链表形式存储，写一个判别给定二叉树是否是完全二叉树的算法
//算法思想：采用层次遍历算法，将所有结点加入队列（包括空结点）。遇到空结点时，查看其后是否有非空结点。若有，则二叉树不是完全二叉树。
bool IsComplete(BiTree T) {
    SqQueue Q;
    BiTNode *p;
    InitQueue(Q);
    if (T == NULL)
        return true;//空树为满二叉树
    EnQueue(Q, T);
    while (!QueueEmpty(Q)) {
        DeQueue(Q, p);
        if (p != NULL) {//结点非空，将其左、右子树入队列
            EnQueue(Q, p->lchild);
            EnQueue(Q, p->rchild);
        } else {//结点为空，检查其后是否有非空结点
            while (!QueueEmpty(Q)) {
                DeQueue(Q, p);
                if (p != NULL)//结点非空，则二叉树为非完全二叉树
                    return false;
            }
        }
    }
    return true;
}


//08.假设二叉树采用二叉链表存储结构存储，试设计一个算法，计算一棵给定二叉树的所有双分支结点个数
int DsonNodes(BiTree T) {
    if (T == NULL)
        return 0;
    else if (T->lchild != NULL && T->rchild != NULL)//双分支结点
        return DsonNodes(T->lchild) + DsonNodes(T->rchild) + 1;
    else
        return DsonNodes(T->lchild) + DsonNodes(T->rchild);
}


//09.设树B是一棵采用链式结构存储的二叉树，编写一个把树B中所有结点的左、右子树进行交换的函数
void swap(BiTree T) {
    BiTNode *temp;
    if (T != NULL) {
        swap(T->lchild);//递归地交换左子树
        swap(T->rchild);//递归地交换右子树
        temp = T->lchild;//交换左、右孩子结点
        T->lchild = T->rchild;
        T->rchild = temp;
    }
}


//10.假设二叉树采用二叉链存储结构存储，设计一个算法，求先序遍历序列中第k（1 ≤ k ≤ 二叉树中结点个数）个结点的值
int num = 1;//遍历序号的全局变量

ElemType PreNode(BiTree T, int k) {
    if (T == NULL)//空结点，则返回特殊字符
        return '#';
    if (num == k)//相等，则当前结点即为第k个结点
        return T->data;
    num++;//下一个结点
    ElemType e;
    e = PreNode(T->lchild, k);//左子树中递归寻找
    if (e != '#')//在左子树中，则返回该值
        return e;
    e = PreNode(T->rchild, k);//在右子树中递归寻找
    return e;
}


//11.已知二叉树以二叉链表存储，编写算法完成：对于树中每个元素值为x的结点，删去以它为根的子树，并释放相应的空间
//删除以元素值x为根的子树，只要能删除其左、右子树，就可以释放值为x的根结点，因此宜采用后序遍历。算法思想：删除值为x的结点，意味着应将其父结点的左（右）子女指针置空，用层次遍历易于找到某结点的父结点。本题要求删除树中每个元素值为x的结点的子树，因此要遍历完整棵二叉树。
void DeleteXTree(BiTree &T) {//删除以T为根的子树
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


//12.在二叉树中查找值为x的结点，试编写算法打印值为x的结点的所有祖先，假设值为x的结点不多于一个
//算法思想：采用非递归后序遍历，最后访问根结点，访问到值为x的结点时，栈中所有元素均为该结点的祖先，依次出栈打印即可。
typedef struct {
    BiTNode *t;
    int tag;//tag=0表示左子女被访问，tag=1表示右子女被访问
} stack;

void Search2(BiTree T, ElemType x) {
    BiTNode *p = T;
    stack s[MaxSize];
    int top = 0;
    while (p != NULL || top > 0) {
        while (p != NULL && p->data != x) {//结点入栈
            s[++top].t = p;
            s[top].tag = 0;
            p = p->lchild;//沿左分支向下
        }
        if (p != NULL && p->data == x) {//找到x
            for (int i = 1; i <= top; i++)
                printf("%d", s[i].t->data);
            exit(1);//输出祖先值后结束
        }
        while (top != 0 && s[top].tag == 1)//退栈（空遍历）
            top--;
        if (top != 0) {
            s[top].tag = 1;
            p = s[top].t->rchild;//沿右分支向下遍历
        }
    }
}


//13.设一棵二叉树的结点结构为（LLINK，INFO，RLINK），ROOT为指向该二叉树根结点的指针，p和q分别为指向该二叉树中任意两个结点的指针，试编写算法ANCESTOR(ROOT,p,q,r)，找到p和q的最近公共祖先结点r
//后序遍历最后访问根结点，即在递归算法中，根是压在栈底的。本题要找p和q的最近公共祖先结点x，不失一般性，设p在q的左边。算法思想：采用后序非递归算法，栈中存放二叉树结点的指针，当访问到某结点时，栈中所有元素均为该结点的祖先。后序遍历必然先遍历到结点p，栈中元素均为p的祖先。先将栈复制到另一辅助栈中。继续遍历到结点q时，将栈中元素从栈顶开始逐个到辅助栈中去匹配，第一个匹配（即相等）的元素就是结点p和q的最近公共祖先。
stack s[MaxSize], s1[MaxSize];//上题的stack结构体
BiTNode *Ancestor(BiTree ROOT, BiTNode *p, BiTNode *q) {
    BiTNode *bt = ROOT;
    int top = 0, top1;
    while (bt != NULL || top > 0) {
        while (bt != NULL) {
            s[++top].t = bt;
            s[top].tag = 0;
            bt = bt->lchild;//沿左分支向下
        }
        while (top != 0 && s[top].tag == 1) {//假定p在q的左侧，遇到p时，栈中元素均为p的祖先
            if (s[top].t == p) {
                for (int i = 1; i <= top; i++) {//将栈s的元素转入辅助栈s1保存
                    s1[i] = s[i];
                }
                top1 = top;
            }
            if (s[top].t == q) {//找到q结点
                for (int i = top; i > 0; i--) {//将栈中元素的树结点到s1中去匹配
                    for (int j = top1; j > 0; j--) {
                        if (s1[j].t == s[i].t)
                            return s[i].t;//p和q的最近公共祖先已找到
                    }
                }
            }
            top--;//退栈
        }
        if (top != 0) {
            s[top].tag = 1;
            bt = s[top].t->rchild;//沿右分支向下遍历
        }
    }
    return NULL;//p和q无公共祖先
}


//14.假设二叉树采用二叉链表存储结构，设计一个算法，求非空二叉树b的宽度（即具有结点数最多的那一层的结点个数）
typedef struct {
    BiTNode *data[MaxSize];//保存队列中的结点指针
    int level[MaxSize];//保存data中相同下标结点的层次
    int front, rear;
} Queue;

int BTWidth(BiTree T) {
    BiTNode *p;
    Queue Q;
    int k;
    Q.front = Q.rear = -1;//队列为空
    Q.rear++;
    Q.data[Q.rear] = T;//根结点指针入队
    Q.level[Q.rear] = 1;//根结点层次为1
    while (Q.front < Q.rear) {
        Q.front++;//出队
        p = Q.data[Q.front];//出队结点
        k = Q.level[Q.front];//出队结点的层次
        if (p->lchild != NULL) {//左孩子进队列
            Q.rear++;
            Q.data[Q.rear] = p->lchild;
            Q.level[Q.rear] = k + 1;
        }
        if (p->rchild != NULL) {//右孩子进队列
            Q.rear++;
            Q.data[Q.rear] = p->rchild;
            Q.level[Q.rear] = k + 1;
        }
    }
    int max = 0, i = 0;//max保存同一层最多的结点个数
    k = 1;//k表示从第一层开始查找
    while (i <= Q.rear) {//i扫描队中所有元素
        int n = 0;//n统计第k层的结点个数
        while (i <= Q.rear && Q.level[i] == k) {
            n++;
            i++;
        }
        k = Q.level[i];
        if (n > max)//保存最大的n
            max = n;
    }
    return max;
}


//15.设有一棵满二叉树（所有结点值均不同），已知其先序序列为pre，设计一个算法求其后序序列post
void PreToPost(ElemType pre[], int h1, int r1, ElemType post[], int h2, int r2) {
    int half;
    if (r1 >= h1) {
        post[r2] = pre[h1];
        half = (r1 - h1) / 2;
        PreToPost(pre, h1 + 1, h1 + half, post, h2, h2 + half - 1);//转换左子树
        PreToPost(pre, h1 + half + 1, r1, post, h2 + half, r2 - 1);//转换右子树
    }
}


//16.设计一个算法将二叉树的叶结点按从左到右的顺序连成一个单链表，表头指针为head。二叉树按二叉链表方式存储，链接时用叶结点的右指针域来存放单链表指针。
BiTNode *head, *pre = NULL;//全局变量

BiTree InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->lchild);//中序遍历左子树
        if (T->lchild == NULL && T->rchild == NULL) {//叶结点
            if (pre == NULL) {//处理第一个叶结点
                head = T;
                pre = T;
            } else {//将叶结点链入链表
                pre->rchild = T;
                pre = T;
            }
        }
        InOrder(T->rchild);//中序遍历右子树
        pre->rchild = NULL;//设置链表尾
    }
    return head;
}


//17.试设计判断两棵二叉树是否相似的算法。所谓二叉树T1和T2相似，指的是T1和T2都是空的二叉树或都只有一个根结点；或T的左子树和T2的左子树是相似的，且T的右子树和T2的右子树是相似的
bool similar(BiTree T1, BiTree T2) {
    bool leftS, rightS;
    if (T1 == NULL && T2 == NULL)//两树皆空
        return true;
    else if (T1 == NULL || T2 == NULL)//只有一树为空
        return false;
    else {//递归判断
        leftS = similar(T1->lchild, T2->lchild);
        rightS = similar(T1->rchild, T2->rchild);
        return leftS && rightS;
    }
}


//18.写出在中序线索二叉树里查找指定结点在后序的前驱结点的算法
typedef struct BiThreadNode {
    ElemType data;
    struct BiThreadNode *lchild, *rchild;
    int ltag, rtag;
} BiThreadNode, *BiThreadTree;

BiThreadNode *InPostPre(BiThreadTree T, BiThreadNode *p) {
    BiThreadNode *q;
    if (p->rtag == 0)//若p有右子女，则右子女是其后序前驱
        q = p->rchild;
    else if (p->ltag == 0)//若p只有左子女，则左子女是其后序前驱
        q = p->lchild;
    else if (p->lchild == NULL)//p是中序序列第一结点，无后序前驱
        q = NULL;
    else {//顺左线索向上找p的祖先，若存在，再找祖先的左子女
        while (p->ltag == 1 && p->lchild != NULL)//若结点p左、右子女均无，设其中序左线索指向某祖先结点f（p是f右子树中按中序遍历的第一个结点），若f无左子女，则顺其前驱找双亲的双亲，一直找到双亲有左子女（这时左子女是p的前驱）
            p = p->lchild;
        if (p->ltag == 0)//若f有左子女，则其左子女是结点p在后序下的前驱,即p结点的祖先的左子女是其后序前驱
            q = p->lchild;
        else
            q = NULL;//仅有单支树（p是叶子），已到根结点，p无后序前驱
    }
    return q;
}

//19.【2014统考真题】二叉树的带权路径长度（WPL）是二叉树中所有叶结点的带权路径长度之和。给定一棵二叉树T，采用二叉链表存储，结点结构为left weight right，其中叶结点的weight域保存该结点的非负权值。设root为指向T的根结点的指针，请设计求T的WPL的算法，要求：
//(1)给出算法的基本设计思想
//(2)使用C或C++语言，给出二叉树结点的数据类型定义
//(3)根据设计思想，采用C或C++语言描述算法，关键之处给出注释
typedef struct BiWeightTNode {
    int weight;
    struct BiWeightTNode *lchild, *rchild;
} BiWeightTNode, *BiWeightTree;

//基于先序遍历的算法：
int wpl_PreOrder(BiWeightTree root, int depth) {
    static int wpl = 0;//定义静态局部变量存储wpl
    if (root->lchild == NULL && root->rchild == NULL)//若为叶结点，则累积wpl
        wpl += depth * root->weight;
    if (root->lchild != NULL)//若左子树不空，则对左子树递归遍历
        wpl_PreOrder(root->lchild, depth + 1);
    if (root->rchild != NULL)//若右子树不空，则对右子树递归遍历
        wpl_PreOrder(root->rchild, depth + 1);
    return wpl;
}

int WPL(BiWeightTree root) {
    return wpl_PreOrder(root, 0);
}

//基于层次遍历的算法：
int wpl_LevelOrder(BiWeightTree root) {
    BiWeightTNode *Q[MaxSize];//声明队列
    int front = 0, rear = 0;//front为头指针，rear为尾指针，头指针指向队头元素，尾指针指向队尾的后一个元素
    int wpl = 0, depth = 0;//初始化wpl和深度
    BiWeightTNode *lastNode = root, *newlastNode = NULL;//lastNode用来记录当前层的最后一个结点，lastNode初始化为根结点，newlastNode用来记录下一层的最后一个结点，newlastNode初始化为空
    Q[rear++] = root;//根结点入队
    while (front < rear) {//层次遍历，若队列不空则循环
        BiWeightTNode *p = Q[front++];//拿出队列中的头元素
        if (p->lchild == NULL && p->rchild == NULL)//若为叶结点，则统计wpl
            wpl += depth * p->weight;
        if (p->lchild != NULL) {//若非叶结点，则让左结点入队
            Q[rear++] = p->lchild;
            newlastNode = p->lchild;//并设下一层的最后一个结点为该结点的左结点
        }
        if (p->rchild != NULL) {//处理非叶结点，让右结点入队
            Q[rear++] = p->rchild;
            newlastNode = p->rchild;
        }
        if (p == lastNode) {//若该结点为本层最后一个结点，则更新lastNode
            lastNode = newlastNode;
            depth++;//层数加1
        }
    }
    return wpl;//返回wpl
}


//20.【2017统考真题】请设计一个算法，将给定的表达式树（二叉树）转换为等价的中缀表达式（通过括号反映操作符的计算次序）并输出。例如，当下列两棵表达式树作为算法的输入时：输出的等价中缀表达式分别为(a+b)*(c*(-d))和(a*b)+(-(c-d))。
//二叉树结点定义如下：
typedef struct node {
    char data[10];//存储操作数或操作符
    struct node *left, *right;
} BTree;
//要求：
//(1)给出算法的基本设计思想
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释

void BTreeToExp(BTree *root, int depth) {
    if (root == NULL)//空结点返回
        return;
    else if (root->left == NULL && root->right == NULL)//若为叶结点
        printf("%s", root->data);//输出操作数，不加括号
    else {//为分支结点
        if (depth > 1)//若有子表达式则加1层括号
            printf("(");
        BTreeToExp(root->left, depth + 1);
        printf("%s", root->data);//输出操作符
        BTreeToExp(root->right, depth + 1);
        if (depth > 1)//若有子表达式则加1层括号
            printf(")");
    }
}

void BTreeToE(BTree *root) {
    BTreeToExp(root, 1);//根的高度为1
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
