#include <iostream>

//1.已知一个整数序列A=(a0,a1,…,an-1),其中0≤ai<n(0≤i<n)。从数组中选择一些数，要求选择的数中任意两数差的绝对值小于等于k。设计一个在时间上尽可能高效的算法输出最多可能选择的元素个数。
//法1：暴力枚举
//两层循环，对每一个ai，对数组进行遍历，找值介于ai-k和ai+k的所有元素，记录选取出来的元素个数，求其最大值。
//时间复杂度为O(n2)，空间复杂度为O(1)
int getMaxCount1(int A[], int n, int k) {
    int count = 0, max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            if (abs(A[i] - A[j]) <= k)
                count++;
        }
        if (count > max)
            max = count;
        count = 0;
    }
    return max;
}

//法2：先快排，再从第每个元素往后找比它大了不超过k的所有元素，记录选取出来的元素个数，求其最大值。
//快排的时间复杂度为O(nlogn)，但查找数组的时间仍为O(n2)，所以时间复杂度仍为O(n2)，空间复杂度为O(logn)
void QuickSort(int A[], int low, int high) {
    if (low < high) {
        int i = low, j = high;
        int pivot = A[i];
        while (i < j) {
            while (i < j && A[j] >= pivot)
                j--;
            A[i] = A[j];
            while (i < j && A[i] <= pivot)
                i++;
            A[j] = A[i];
        }
        A[i] = pivot;
        QuickSort(A, low, i - 1);
        QuickSort(A, i + 1, high);
    }
}

int getMaxCount2(int A[], int n, int k) {
    int count = 0, max = 0;
    QuickSort(A, 0, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n && abs(A[i] - A[j]) <= k; j++)//从i往左找
            count++;
        for (int m = i - 1; m >= 0 && abs(A[i] - A[m]) <= k; m--)//从i往右找
            count++;
        if (count > max)
            max = count;
        count = 0;
    }
    return max;
}

//法3：快排+数组指针优化，因为数组有序，j指针可以不用每次都重新从i开始移动，j可以直接在之前的位置上往右移
//快排的时间复杂度为O(nlogn)，但查找数组的时间变为O(n)，所以时间复杂度仍为O(nlogn)，空间复杂度为O(logn)
int getMaxCount3(int A[], int n, int k) {
    int count, max = 0;
    QuickSort(A, 0, n - 1);
    int i = 0, j = 0, m = 0;
    for (; i < n; i++) {
        for (; j < n && abs(A[i] - A[j]) <= k; j++);//A[j]是A[i]右边能保证A[j]-A[i]<=k的最大的元素
        for (; m < n && abs(A[i] - A[m]) > k; m++);//A[m]是A[i]左边能保证A[i]-A[m]<=k的最小的元素的左边挨着的元素
        count = j - m;
        if (count > max)
            max = count;
    }
    return max;
}


//2.在数组中，某个数字减去它右边的数字得到一个数对之差。求所有数对之差的最大值。例如，在数组{2, 4, 1, 16, 7, 5, 11, 9}中，数对之差的最大值是11，是16减去5的结果。设计一个在时间上尽可能高效的算法输出所有数对之差的最大值。
//法1：暴力解
//首先，遍历数组，找到所有的差值，然后，从所有差值中找出最大值。具体实现方法为：针对数组a中的每一个元素a[i], 求所有a[i]-a[j](i<j<n)的值中的最大值
//时间复杂度为O(n2)，空间复杂度为O(1)
int getMax1(int a[], int n) {
    int max = INT_MIN;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] - a[j] > max)
                max = a[i] - a[j];
        }
    }
    return max;
}

//法2：动态规划
//给定数组a，申请额外的数组diff和max，其中diff[i]是以数组第i+1个数字为减数的所有数对之差的最大值（前i+1个数字组成的子数组中最大的差值），max[i]为前i+1个数的最大值。假设已经求得了diff[i]，diff[i+1]的值有两种可能性
//(1)等于diff[i]
//(2)等于max[i]-a[i]
//可以得到：diff[i+1] = max(diff[i],max[i-1]-a[i])，max[i+1] = max(max[i], a[i+1])
//数组最大的差值为diff[n-1] (n为数组的长度)
//对数组进行了一次遍历，时间复杂度为O(n)，由于引入了两个额外的数组，因此这个算法的空间复杂度为O(n)
int getMax2(int a[], int n) {
    int diff[n], max[n];
    diff[0] = INT_MIN;
    max[0] = a[0];
    for (int i = 1; i < n; i++) {
        diff[i] = std::max(diff[i - 1], max[i - 1] - a[i]);
        max[i] = std::max(max[i - 1], a[i]);
    }
    return diff[n - 1];
}

//动态规划优化：
//在求解 diff[i+1]时，只用到了diff[i]与max[i]，而与数组diff和max中其他数字无关，因此可以通过两个变量而不是数组来记录diff[i]与max[i]的值，从而降低了算法的空间复杂度
//时间复杂度为O(n)，空间复杂度为O(1)
int getMax3(int a[], int n) {
    int diff, max;
    diff = INT_MIN;
    max = a[0];
    for (int i = 1; i < n; i++) {
        diff = std::max(diff, max - a[i]);
        max = std::max(max, a[i]);
    }
    return diff;
}

//3.有一个数组A由2n+1个互不相同的正整数组成，该序列中的数先减后增，第n+1个数是最小值，输入一个整数key。请设计一个时间和空间上尽可能高效的算法，判断key是否在该数组中，是的话返回数组下标，否则返回-1。例如对应A={10, 7, 5, 2, 6, 13, 15}，key=5时返回true，若key=8则返回false。
//法1：暴力遍历
//时间复杂度为O(n)，空间复杂度为O(1)
bool find1(int A[], int key, int n) {
    for (int i = 0; i < n; i++) {
        if (A[i] == key) {
            return true;
        }
    }
    return false;
}

//法2：在第n+1位数的左右两边分别折半查找
//时间复杂度为O(logn)，空间复杂度为O(1)
bool find2(int A[], int key, int n) {
    if (A[n / 2] == key) {
        return true;
    }
    //左边为降序
    int low1 = 0, high1 = n / 2 - 1, mid1;
    while (low1 <= high1) {
        mid1 = (low1 + high1) / 2;
        if (A[mid1] == key) {
            return true;
        } else if (A[mid1] > key)
            low1 = mid1 + 1;
        else
            high1 = mid1 - 1;
    }
    //右边为升序
    int low2 = n / 2 + 1, high2 = n - 1, mid2;
    while (low2 <= high2) {
        mid2 = (low2 + high2) / 2;
        if (A[mid2] == key) {
            return true;
        } else if (A[mid2] > key)
            high2 = mid2 - 1;
        else
            low2 = mid2 + 1;
    }
    return false;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
