#include <iostream>

typedef int ElemType;

void swap(ElemType &a, ElemType &b) {
    ElemType temp = a;
    a = b;
    b = temp;
}

//02.编写双向冒泡排序算法，在正反两个方向交替进行扫描，即第一趟把关键字最大的元素放在序列的最后面，第二趟把关键字最小的元素放在序列的最前面，如此反复进行。
void BubbleSort(ElemType A[], int n) {
    int low = 0, high = n - 1;
    bool flag = true;//一趟冒泡后记录元素是否交换标志
    while (low < high && flag) {//循环跳出条件，当flag为false说明已没有逆序
        flag = false;//每趟初始置flag为false
        for (int i = low; i < high; i++) {//从前向后起泡
            if (A[i] > A[i + 1]) {//发生逆序
                swap(A[i], A[i + 1]);//交换
                flag = true;//置flag
            }
        }
        high--;//更新上界
        for (int i = high; i > low; i--) {//从后往前起泡
            if (A[i] < A[i - 1]) {//发生逆序
                swap(A[i], A[i - 1]);//交换
                flag = true;//置flag
            }
        }
        low++;//修改下界
    }
}


//03.已知线性表按顺序存储，且每个元素都是不相同的整数型元素，设计把所有奇数移动到所有偶数前边的算法（要求时间最少，辅助空间最少）。
//本题可采用基于快速排序的划分思想来设计算法，只需遍历一次即可，其时间复杂度为O(n)，空间复杂度为O(1)。假设表为L[1...n]，基本思想是：先从前向后找到一个偶数元素L(i)，再从后向前找到一个奇数元素L(j)，将二者交换；重复上述过程直到i大于j。
void move(ElemType A[], int n) {
    int i = 0, j = n - 1;//i表示左端偶数元素的下标；j表示右端奇数元素的下标
    while (i < j) {
        while (i < j && A[i] % 2 != 0)//从前向后找到一个偶数元素
            i++;
        while (i < j && A[j] % 2 != 1)//从后向前找到一个奇数元素
            j--;
        if (i < j) {
            swap(A[i], A[j]);//交换这两个元素
            i++;
            j--;
        }
    }
}


//04.试重新编写考点精析中的快速排序的划分算法，使之每次选取的枢轴值都是随机地从当前子表中选择的。
int Partition2(ElemType A[], int low, int high) {
    int rand_Index = low + rand() % (high - low + 1);
    swap(A[rand_Index], A[low]);//将枢轴值交换到第一个元素
    ElemType pivot = A[low];//置当前表中的第一个元素为枢轴值
    int i = low;//使得表A[low…i]中的所有元素小于pivot，初始为空表
    for (int j = low + 1; j <= high; j++) {//从第二个元素开始寻找小于基准的元素
        if (A[j] < pivot)//找到后，交换到前面
            swap(A[++i], A[j]);
    }
    swap(A[i], A[low]);//将基准元素插入最终位置
    return i;//返回基准元素的位置
}


//05.试编写一个算法，使之能够在数组L[1...n]中找出第k小的元素（即从小到大排序后处于第k个位置的元素）。
int kth_elem(ElemType a[], int low, int high, int k) {
    ElemType pivot = a[low];
    int low_temp = low, high_temp = high;//由于下面会修改1ow与high，在递归时又要用到它们
    while (low < high) {
        while (low < high && a[high] >= pivot)
            high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivot)
            low++;
        a[high] = a[low];
    }
    a[low] = pivot;
    if (low == k)//由于与k相同，直接返回pivot元素
        return a[low];
    else if (low > k)//在前一部分表中递归寻找
        return kth_elem(a, low_temp, low - 1, k);
    else//在后一部分表中递归寻找
        return kth_elem(a, low + 1, high_temp, k - (low - low_temp + 1));
}


//06.荷兰国旗问题：设有一个仅由红、白、蓝三种颜色的条块组成的条块序列，请编写一个时间复杂度为O(n)的算法，使得这些条块按红、白、蓝的顺序排好，即排成荷兰国旗图案。
typedef enum {
    RED, WHITE, BLUE
} color;//设置枚举数组

void swap_color(color &a, color &b) {
    color temp = a;
    a = b;
    b = temp;
}

void Flag_Arrange(color a[], int n) {
    int i = 0, j = 0, k = n - 1;
    while (j <= k) {
        switch (a[j]) {//判断条块的颜色
            case RED://红色，则和i交换
                swap_color(a[i], a[j]);
                i++;
                j++;
                break;//switch语句不会在执行判断为真后的语句之后跳出循环，而是继续执行后面所有case语句，因此要加break
            case WHITE:
                j++;
                break;
            case BLUE://蓝色，则和k交换
                swap_color(a[j], a[k]);
                k--;//这里没有j++语句以防止交换后a[j]仍为蓝色的情况
        }
    }
}


//07.【2016统考真题】已知由n（n≥2）个正整数构成的集合A={ak|0≤k<n}，将其划分为两个不相交的子集A1和A2，元素个数分别是n1和n2，A1和A2中的元素之和分别为S1和S2。设计一个尽可能高效的划分算法，满足|n1-n2|最小且|S1-S2|最大。要求：
//(1)给出算法的基本设计思想。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
//(3)说明你所设计算法的平均时间复杂度和空间复杂度。
int setPartition(ElemType a[], int n) {
    ElemType pivot;
    int low = 0, low_temp = 0, high = n - 1, high_temp = n - 1, k = n / 2;
    bool flag = false;
    while (!flag) {
        pivot = a[low];
        while (low < high) {
            while (low < high && a[high] >= pivot)
                high--;
            a[low] = a[high];
            while (low < high && a[low] <= pivot)
                low++;
            a[high] = a[low];
        }
        a[low] = pivot;
        if (low == k - 1)
            flag = true;
        else if (low < k - 1) {
            low_temp = ++low;
            high = high_temp;
        } else {
            high_temp = --high;
            low = low_temp;
        }
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
