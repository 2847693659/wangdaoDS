#include <iostream>

typedef int ElemType;

//05.��֪һ�ö�������˳��洢�ṹ���д洢�����һ���㷨�����ŷֱ�Ϊi��j��������������Ĺ������Ƚ���ֵ
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
