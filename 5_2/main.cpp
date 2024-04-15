#include <iostream>

typedef int ElemType;

//05.已知一棵二叉树按顺序存储结构进行存储，设计一个算法，求编号分别为i和j的两个结点的最近的公共祖先结点的值
ElemType Comm_Ancestor(ElemType T[], int i, int j) {
    while (i != j) {
        if (i > j)
            i = i / 2;
        else
            j = j / 2;
    }
    return T[i];
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
