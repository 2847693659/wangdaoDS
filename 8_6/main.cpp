#include <iostream>

typedef int ElemType;

//02.设顺序表用数组A[]表示，表中元素存储在数组下标1~m+n的范围内，前m个元素递增有序，后n个元素递增有序，设计一个算法，使得整个顺序表有序。
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C/C++描述算法，关键之处给出注释。
//(3)说明你所设计算法的时间复杂度与空间复杂度。
void Insert_Sort(ElemType A[], int m, int n) {
    int i, j;
    for (i = m + 1; i < m + n; i++) {//依次将A[m+1...m+n]插入有序表
        A[0] = A[i];
        for (j = i - 1; A[j] > A[0]; j--) {
            A[j + 1] = A[j];
        }
        A[j + 1] = A[0];
    }
}


//03.有一种简单的排序算法，称为计数排序（count sorting）。这种排序算法对一个待排序的表（用数组表示）进行排序，并将排序结果存放到另一个新的表中。必须注意的是，表中所有待排序的关键码互不相同，计数排序算法针对表中的每个记录，扫描待排序的表一趟，统计表中有多少个记录的关键码比该记录的关键码小，假设针对某个记录统计出的计数值为c，则这个记录在新有序表中的合适存放位置即为c。
//(1)设计实现计数排序的算法。
//(2)对于有n个记录的表，关键码比较次数是多少？
//(3)与简单选择排序相比较，这种方法是否更好？为什么？
void CountSort(ElemType A[], ElemType B[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (A[i] > A[j])
                count++;
        }
        B[count] = A[i];
    }
}


//04.设有一个数组中存放了一个无序的关键序列K1,K2,...,Kn。现要求将Kn放在将元素排序后的正确位置上，试编写实现该功能的算法，要求比较关键字的次数不超过n。
int Partition(ElemType A[], int n) {
    int low = 1, high = n;
    ElemType pivot = A[n];
    while (low < high) {
        while (low < high && A[low] <= pivot)
            low++;
        A[high] = A[low];
        while (low < high && A[high] >= pivot)
            high--;
        A[low] = A[high];
    }
    A[low] = pivot;
    return low;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
