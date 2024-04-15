#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MaxSize 100

typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int length;
} SqList;

//01.从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删元素的值。空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行
//算法思想：搜索整个顺序表，查找最小值元素并记住其位置，搜索结束后用最后一个元素填补空出的原最小值元素的位置
bool Del_Min(SqList &L, ElemType &value) {
    if (L.length == 0)
        return false;//表空，中止操作返回
    value = L.data[0];
    int pos = 0;//假定0号元素的值最小
    for (int i = 1; i < L.length; i++) {//循环，寻找具有最小值的元素
        if (L.data[i] < value) {//让value记忆当前具有最小值的元素
            value = L.data[i];
            pos = i;
        }
    }
    L.data[pos] = L.data[L.length - 1];//空出的位置由最后一个元素填补
    L.length--;
    return true;//此时，value即为最小值
}


//02.设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)
//算法思想：扫描顺序表L的前半部分元素，对于元素L.data[i]（0<=i<L.length/2），将其与后半部分的对应元素L.data[L.length-1-i]进行交换
void Reverse(SqList &L) {
    ElemType temp;//辅助变量
    for (int i = 0; i < L.length / 2; i++) {
        temp = L.data[i];//交换L.data[i]与L.data[L.length - 1 - i]
        L.data[i] = L.data[L.length - 1 - i];
        L.data[L.length - 1 - i] = temp;
    }
}


//03.对长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，该算法删除线性表中所有值为x的数据元素
//解法一：用k记录顺序表L中不等于x的元素个数（即需要保存的元素个数)，扫描时将不等于x的元素移动到下标k的位置，并更新k值。扫描结束后修改L的长度
void Del_x_1(SqList &L, ElemType x) {
    int k = 0;//记录值不等于x的元素个数
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] != x) {
            L.data[k] = L.data[i];
            k++;//不等于x的元素增1
        }
    }
    L.length = k;//顺序表L的长度等于k
}

//解法二：用k记录顺序表L中等于x的元素个数，边扫描L边统计k，并将不等于x的元素前移k个位置。扫描结束后修改L的长度
void Del_x_2(SqList &L, ElemType x) {
    int k = 0;//k记录值等于x的元素个数
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == x)
            k++;
        else
            L.data[i - k] = L.data[i];//当前元素前移k个位置
    }
    L.length -= k;//顺序表L的长度递减
}


//04.从有序顺序表中删除其值在给定值s与t之间（要求s<t）的所有元素，若s或t不合理或顺序表为空，则显示出错信息并退出运行
//算法思想：先寻找值大于等于s的第一个元素（第一个删除的元素），然后寻找值大于t的第一个元素（最后一个删除的元素的下一个元素），要将这段元素删除，只需直接将后面的元素前移
bool Del_s_t2(SqList &L, ElemType s, ElemType t) {
    int i, j;
    if (s >= t || L.length == 0)
        return false;
    for (i = 0; i < L.length && L.data[i] < s; i++);//寻找值大于等于s的第一个元素
    if (i == L.length)
        return false;//所有元素值均小于s，返回
    for (j = i; j < L.length && L.data[j] <= t; j++);//寻找值大于t的第一个元素
    for (; j < L.length; i++, j++)
        L.data[i] = L.data[j];//前移，填补被删元素位置
    L.length = i;
    return true;
}


//05.从顺序表中删除其值在给定值s与t之间（包含s和t，要求s<t）的所有元素，若s或t不合理或顺序表为空，则显示出错信息并退出运行
//算法思想：从前向后扫描顺序表L，用k记录下元素值在s到t之间元素的个数（初始时k=0）。对于当前扫描的元素，若其值不在s到t之间，则前移k个位置；否则执行k++。由于这样每个不在s到t之间的元素仅移动一次，因此算法效率高
bool Del_s_t(SqList &L, ElemType s, ElemType t) {
    int k = 0;
    if (s >= t || L.length == 0)
        return false;//线性表为空或s、t不合法，返回
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] >= s && L.data[i] <= t)
            k++;
        else
            L.data[i - k] = L.data[i];//当前元素前移k个位置
    }
    L.length -= k;//长度减小
    return true;
}


//06.从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同
//算法思想：注意是有序顺序表，值相同的元素一定在连续的位置上，用类似于直接插入排序的思想，初始时将第一个元素视为非重复的有序表。之后依次判断后面的元素是否与前面非重复有序表的最后一个元素相同，若相同，则继续向后判断，若不同，则插入前面的非重复有序表的最后，直至判断到表尾为止
bool Delete_Same(SqList &L) {
    if (L.length == 0)
        return false;
    int i, j;//i存储第一个不相同的元素，j为工作指针
    for (i = 0, j = 1; j < L.length; j++) {
        if (L.data[j] != L.data[i])//查找下一个与上个元素值不同的元素
            L.data[++i] = L.data[j];//找到后，将元素前移
    }
    L.length = i + 1;
    return true;
}


//07.将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。
//算法思想：首先，按顺序不断取下两个顺序表表头较小的结点存入新的顺序表中。然后，看哪个表还有剩余，将剩下的部分加到新的顺序表后面
bool Merge(SqList A, SqList B, SqList &C) {
    if (A.length + B.length > MaxSize)//大于顺序表的最大长度
        return false;
    int i = 0, j = 0, k = 0;
    while (i < A.length && j < B.length) {//循环，两两比较，小者存入结果表
        if (A.data[i] <= B.data[j])
            C.data[k++] = A.data[i++];
        else
            C.data[k++] = B.data[j++];
    }
    while (i < A.length)//还剩一个没有比较完的顺序表
        C.data[k++] = A.data[i++];
    while (j < B.length)
        C.data[k++] = B.data[j++];
    C.length = k;
    return true;
}


//08.已知在一维数组A[m+n]中依次存放两个线性表（a1,a2,a3,…,am)和（b1,b2,b3,…,bn)。编写一个函数，将数组中两个顺序表的位置互换，即将（b1,b2,b3,…,bn)放在（a1,a2,a3,…,am)的前面
//算法思想：先将数组A[m+n]中的全部元素（a1,a2,a3,…，am,b1,b2,b3,…，bn)原地逆置为（bn,bn-1,bn-2,…，b1,am,am-1,am-2,…,a1),再对前n个元素和后m个元素分别使用逆置算法，即可得到（b1,b2,b3,…,bn,a1,a2,a3,…,am)，从而实现顺序表的位置互换
void Reverse1(ElemType A[], int left, int right, int arraySize) {//left、right为数组下标
    if (left >= right || right >= arraySize)
        return;
    int mid = (left + right) / 2;
    for (int i = 0; i <= mid - left; i++) {
        ElemType temp = A[left + i];
        A[left + i] = A[right - i];
        A[right - i] = temp;
    }
}

void Exchange(ElemType A[], int m, int n, int arraySize) {
    Reverse1(A, 0, m + n - 1, arraySize);
    Reverse1(A, 0, n - 1, arraySize);
    Reverse1(A, n, m + n - 1, arraySize);
}


//09.线性表（a1,a2,a3,…，an)中的元素递增有序且按顺序存储于计算机内。要求设计一个算法，完成用最少时间在表中查找数值为x的元素，若找到，则将其与后继元素位置相交换，若找不到，则将其插入表中并使表中元素仍递增有序
//算法思想：顺序存储的线性表递增有序，可以顺序查找，也可以折半查找。题目要求“用最少的时间在表中查找数值为x的元素”，这里应使用折半查找法
void SearchExchangeInsert(SqList &L, ElemType x) {
    int low = 0, high = L.length - 1, mid, i;//1ow和high指向顺序表下界和上界的下标
    while (low <= high) {
        mid = (low + high) / 2;//找中间位置
        if (L.data[mid] == x)
            break;//找到x,退出while循环
        else if (L.data[mid] < x)
            low = mid + 1;//到中点mid的右半部去查
        else
            high = mid - 1;//到中点mid的左半部去查
    }
    //下面两个if语句只会执行一个
    if (L.data[mid] == x && mid != L.length - 1) {//若最后一个元素与x相等，则不存在与其后继交换的操作
        ElemType temp = L.data[mid];
        L.data[mid] = L.data[mid + 1];
        L.data[mid + 1] = temp;
    }
    if (low > high) {//查找失败，插入数据元素x，此时low=high+1，x应放入low的位置
        for (i = L.length - 1; i > high; i--)
            L.data[i + 1] = L.data[i];//后移元素
        L.data[i + 1] = x;//插入x
        L.length++;
    }//结束插入
}


//力扣189 https://leetcode.cn/problems/rotate-array/
//10.【2010统考真题】设将n（n>1）个整数存放到一维数组R中。设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p（0<p<n）个位置，即将R中的数据由（X0,X1,…,Xn-1)变换为（Xp,Xp+1,…,Xn-1,X0,X1,…,Xp-1)。要求：
//(1)给出算法的基本设计思想
//算法的基本设计思想：可将这个问题视为把数组ab转换成数组ba（a代表数组的前p个元素，b代表数组中余下的n-p个元素），先将a逆置得到a-1b，再将b逆置得到a-1b-1，最后将整个a-1b-1逆置得到(a-1b-1）-1=ba。设Reverse函数执行将数组元素逆置的操作，对abcdefgh向左循环移动3（p=3）个位置的过程如下：
//Reverse(0,p-1)得到cbadefgh;
//Reverse(p,n-1)得到cbahgfed;
//Reverse(0,n-1)得到defghabc；
//注：Reverse中，两个参数分别表示数组中待转换元素的始末位置
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释
void Reverse2(int R[], int from, int to) {
    for (int i = 0; i < (to - from + 1) / 2; i++) {
        int temp = R[from + i];
        R[from + i] = R[to - i];
        R[to - i] = temp;
    }
}

void Converse(int R[], int n, int p) {
    Reverse2(R, 0, p - 1);
    Reverse2(R, p, n - 1);
    Reverse2(R, 0, n - 1);
}
//(3)说明你所设计算法的时间复杂度和空间复杂度
//上述算法中三个Reverse函数的时间复杂度分别为O(p/2)、O((n-p)/2)和O(n/2)，故所设计的算法的时间复杂度为O（n)，空间复杂度为O（1）


//力扣4 https://leetcode.cn/problems/median-of-two-sorted-arrays/
//11.【2011统考真题】一个长度为L（L≥1）的升序序列S，处在第L/2（向上取整）个位置的数称为S的中位数。例如，若序列S1=（11,13,15,17,19），则S1的中位数是15，两个序列的中位数是含它们所有元素的升序序列的中位数。例如，若S2=（2,4,6,8,20），则S1和S2的中位数是11。现在有两个等长升序序列A和B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数。要求：
//(1)给出算法的基本设计思想
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释
int M_Search(int A[], int B[], int n) {
    int s1 = 0, d1 = n - 1, m1, s2 = 0, d2 = n - 1, m2;//分别表示序列A和B的首位数、末位数和中位数
    while (s1 != d1 || s2 != d2) {
        m1 = (s1 + d1) / 2;
        m2 = (s2 + d2) / 2;
        if (A[m1] == B[m2]) {
            return A[m1];
        } else if (A[m1] < B[m2]) {
            if ((s1 + d1) % 2 == 0) {//元素个数为奇数
                s1 = m1;
                d2 = m2;
            } else {//元素个数为偶数
                s1 = m1 + 1;
                d2 = m2;
            }
        } else {
            if ((s2 + d2) % 2 == 0) {//元素个数为奇数
                s2 = m2;
                d1 = m1;
            } else {//元素个数为偶数
                s2 = m2 + 1;
                d1 = m1;
            }
        }
    }
    return A[s1] < B[s2] ? A[s1] : B[s2];
}

//次优解：数组指针后移
int M_Search2(int A[], int B[], int n) {
    int i = 0, j = 0;
    int m;
    for (int k = 0; k < n; k++) {
        if (A[i] <= B[j])
            m = A[i++];
        else
            m = B[j++];
    }
    return m;
}
//(3)说明你所设计算法的时间复杂度和空间复杂度
//算法的时间复杂度为O(log2n)，空间复杂度为O(1)
//次优解的时间复杂度为O(n)，空间复杂度为O(1)


//力扣169 https://leetcode.cn/problems/majority-element/
//12.【2013统考真题】已知一个整数序列A=（a0,a1,…,an-1），其中0≤ai<n（0≤i<n)。若存在ap1=ap2=…=apm=x且m>n/2（0≤pk<n,1≤k≤m）,则称x为A的主元素。例如A=（0,5,5,3,5,7,5,5）,则5为主元素；又如A=（0,5,5,3,5,1,5,7）,则A中没有主元素。假设A中的n个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。若存在主元素，则输出该元素；否则输出-1。要求：
//(1)给出算法的基本设计思想
//算法的基本设计思想：算法的策略是从前向后扫描数组元素，标记出一个可能成为主元素的元素Num。然后重新计数，确认Num是否是主元素。
//算法可分为以下两步：
//①选取候选的主元素。依次扫描所给数组中的每个整数，将第一个遇到的整数Num保存到c中，记录Num的出现次数为1；若遇到的下一个整数仍等于Num，则计数加1，否则计数减1；当计数减到0时，将遇到的下一个整数保存到c中，计数重新记为1，开始新一轮计数，即从当前位置开始重复上述过程，直到扫描完全部数组元素。
//②判断c中元素是否是真正的主元素。再次扫描该数组，统计c中元素出现的次数，若大于n/2，则为主元素；否则，序列中不存在主元素。
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释
int Majority(int A[], int n) {
    int c = A[0], count = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] == c)
            count++;
        else {
            if (count > 0)
                count--;
            else {
                c = A[i];
                count = 1;
            }
        }
    }
    if (count > 0) {//这个判断加不加都可，但下面循环一定要有
        count = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] == c)
                count++;
        }
    }
    if (count > n / 2)
        return c;
    else
        return -1;
}
//(3)说明你所设计算法的时间复杂度和空间复杂度
//实现的程序的时间复杂度为O(n)，空间复杂度为O(1)


//力扣41 https://leetcode.cn/problems/first-missing-positive/
//13.【2018统考真题】给定一个含n（n≥1）个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。例如，数组{-5,3,2,3}中未出现的最小正整数是1；数组{1，2,3}中未出现的最小正整数是4。要求：
//(1)给出算法的基本设计思想
//(2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释
int findMissMin(int A[], int n) {
    int i;
    int *B = (int *) malloc(sizeof(int) * n);
    memset(B, 0, sizeof(int) * n);
    for (i = 0; i < n; i++) {
        if (A[i] > 0 && A[i] <= n)
            B[A[i] - 1] = 1;
    }
    for (i = 0; i < n; i++) {
        if (B[i] == 0)
            break;
    }
    return i + 1;
}
//(3)说明你所设计算法的时间复杂度和空间复杂度
//时间复杂度：遍历A一次，遍历B一次，两次循环内操作步骤为O(1)量级，因此时间复杂度为O(n)。空间复杂度：额外分配了B[n]，空间复杂度为O(n)。



//14.【2020统考真题】定义三元组(a,b,c)(a、b、c均为正数）的距离D=|a-b|+|b-c|+|c-a|。给定3个非空整数集合S1、S2和S3，按升序分别存储在3个数组中。请设计一个尽可能高效的算法，计算并输出所有可能的三元组（a,b,c)（aES1，bES2，cES3）中的最小距离。例如S1={-1,0,9},S2={-25,-10,10,11},S3={2,9,17,30,41},则最小距离为2，相应的三元组为（9,10,9）。要求：
//(1)给出算法的基本设计思想
//(2)根据设计思想，采用C语言或C++语言描述算法，关键之处给出注释

//#define INT_MAX 0x7fffffff

//int abs_(int a) {
//    if (a < 0)
//        return -a;
//    else
//        return a;
//}

bool xls_min(int a, int b, int c) {
    if (a <= b && a <= c)
        return true;
    return false;
}

int findMinofTrip(int A[], int n1, int B[], int n2, int C[], int n3) {
    int i = 0, j = 0, k = 0, D_min = INT_MAX, D;
    while (i < n1 && j < n2 && k < n3 && D_min > 0) {
        D = abs(A[i] - B[j]) + abs(B[j] - C[k]) + abs(A[i] - C[k]);
        if (D < D_min)
            D_min = D;
        if (xls_min(A[i], B[j], C[k]))
            i++;
        else if (xls_min(B[j], A[i], C[k]))
            j++;
        else
            k++;
    }
    return D_min;
}
//(3)说明你所设计算法的时间复杂度和空间复杂度
//设n=(|S1|+|S2|+|S3|)，时间复杂度为O(n)，空间复杂度为O(1)


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
