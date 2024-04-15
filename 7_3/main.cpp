#include <iostream>

typedef int ElemType;
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
    int count;//count保存以该结点为根的子树上的结点个数
} BiTNode, *BiTree;

//06.试编写一个算法，判断给定的二叉树是否是二叉排序树
//对二叉排序树来说，其中序遍历序列为一个递增有序序列。因此，对给定的二叉树进行中序遍历，若始终能保持前一个值比后一个值小，则说明该二叉树是一棵二叉排序树
ElemType predt = INT_MIN;

int JudgeBst(BiTree T) {
    ElemType b1, b2;
    if (T == NULL)
        return 0;
    else {
        b1 = JudgeBst(T->lchild);//判断左子树是否是二叉排序树
        if (b1 == 0 || predt >= T->data)//若左子树返回值为0或前驱大于等于当前结点
            return 0;//则不是二叉排序树
        predt = T->data;//保存当前结点的关键字
        b2 = JudgeBst(T->rchild);//判断右子树
        return b2;//返回右子树的结果
    }
}

//也可以不用中序遍历
bool Judge(BiTree T, ElemType lower, ElemType upper) {
    if (T == NULL)
        return true;
    if (T->data <= lower || T->data >= upper)
        return false;
    return Judge(T->lchild, lower, T->data) && Judge(T->rchild, T->data, upper);
}

bool isBST(BiTree T) {
    return Judge(T, INT_MIN, INT_MAX);
}


//07.设计一个算法，求出指定结点在给定二叉排序树中的层次
int level(BiTree T, BiTNode *p) {
    int n = 0;
    if (T != NULL) {
        n++;
        while (T->data != p->data) {
            if (p->data < T->data)
                T = T->lchild;
            else
                T = T->rchild;
            n++;
        }
    }
    return n;
}


//08.利用二叉树遍历的思想编写一个判断二叉树是否是平衡二叉树的算法
void Judge_AVL(BiTree T, int &balance, int &h) {
    int bl = 0, br = 0, hl = 0, hr = 0;//左、右子树的平衡标记和高度
    if (T == NULL) {//空树，高度为0
        h = 0;
        balance = 1;
    } else if (T->lchild == NULL && T->rchild == NULL) {//仅有根结点，则高度为1
        h = 1;
        balance = 1;
    } else {
        Judge_AVL(T->lchild, bl, hl);//递归判断左子树
        Judge_AVL(T->rchild, br, hr);//递归判断右子树
        h = (hl > hr ? hl : hr) + 1;
        if (abs(hl - hr) < 2)//若子树高度差的绝对值<2，则看左、右子树是否都平衡
            balance = bl && br;//左、右子树都平衡时，二叉树平衡
        else
            balance = 0;
    }
}


//09.设计一个算法，求出给定二叉排序树中最小和最大的关键字
ElemType MinElem(BiTree T) {
    while (T->lchild != NULL)
        T = T->lchild;
    return T->data;
}

ElemType MaxElem(BiTree T) {
    while (T->rchild != NULL)
        T = T->rchild;
    return T->data;
}


//10.设计一个算法，从大到小输出二叉排序树中所有值不小于k的关键字
void OutPut(BiTree T, ElemType k) {
    if (T == NULL)
        return;
    if (T->rchild != NULL)
        OutPut(T->rchild, k);
    if (T->data >= k)
        printf("%d", T->data);
    if (T->lchild != NULL)
        OutPut(T->lchild, k);
}


//11.编写一个递归算法，在一棵有n个结点的、随机建立起来的二叉排序树上查找第k(1≤k≤n)小的元素，并返回指向该结点的指针。要求算法的平均时间复杂度为O(log2n)。二叉排序树的每个结点中除data,lchild,rchild等数据成员外，增加一个count成员，保存以该结点为根的子树上的结点个数。
BiTNode *Search_Small(BiTree T, int k) {
    if (k < 1 || k > T->count)
        return NULL;
    if (T->lchild == NULL) {
        if (k == 1)
            return T;
        else
            return Search_Small(T->rchild, k - 1);
    } else {
        if (T->lchild->count == k - 1)
            return T;
        else if (T->lchild->count > k - 1)
            return Search_Small(T->lchild, k);
        else
            return Search_Small(T->rchild, k - (T->lchild->count + 1));
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
