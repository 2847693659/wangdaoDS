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

//01.��˳�����ɾ��������Сֵ��Ԫ�أ�����Ψһ�����ɺ������ر�ɾԪ�ص�ֵ���ճ���λ�������һ��Ԫ�������˳���Ϊ�գ�����ʾ������Ϣ���˳�����
//�㷨˼�룺��������˳���������СֵԪ�ز���ס��λ�ã����������������һ��Ԫ����ճ���ԭ��СֵԪ�ص�λ��
bool Del_Min(SqList &L, ElemType &value) {
    if (L.length == 0)
        return false;//��գ���ֹ��������
    value = L.data[0];
    int pos = 0;//�ٶ�0��Ԫ�ص�ֵ��С
    for (int i = 1; i < L.length; i++) {//ѭ����Ѱ�Ҿ�����Сֵ��Ԫ��
        if (L.data[i] < value) {//��value���䵱ǰ������Сֵ��Ԫ��
            value = L.data[i];
            pos = i;
        }
    }
    L.data[pos] = L.data[L.length - 1];//�ճ���λ�������һ��Ԫ���
    L.length--;
    return true;//��ʱ��value��Ϊ��Сֵ
}


//02.���һ����Ч�㷨����˳���L������Ԫ�����ã�Ҫ���㷨�Ŀռ临�Ӷ�ΪO(1)
//�㷨˼�룺ɨ��˳���L��ǰ�벿��Ԫ�أ�����Ԫ��L.data[i]��0<=i<L.length/2�����������벿�ֵĶ�ӦԪ��L.data[L.length-1-i]���н���
void Reverse(SqList &L) {
    ElemType temp;//��������
    for (int i = 0; i < L.length / 2; i++) {
        temp = L.data[i];//����L.data[i]��L.data[L.length - 1 - i]
        L.data[i] = L.data[L.length - 1 - i];
        L.data[L.length - 1 - i] = temp;
    }
}


//03.�Գ���Ϊn��˳���L����дһ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)���㷨�����㷨ɾ�����Ա�������ֵΪx������Ԫ��
//�ⷨһ����k��¼˳���L�в�����x��Ԫ�ظ���������Ҫ�����Ԫ�ظ���)��ɨ��ʱ��������x��Ԫ���ƶ����±�k��λ�ã�������kֵ��ɨ��������޸�L�ĳ���
void Del_x_1(SqList &L, ElemType x) {
    int k = 0;//��¼ֵ������x��Ԫ�ظ���
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] != x) {
            L.data[k] = L.data[i];
            k++;//������x��Ԫ����1
        }
    }
    L.length = k;//˳���L�ĳ��ȵ���k
}

//�ⷨ������k��¼˳���L�е���x��Ԫ�ظ�������ɨ��L��ͳ��k������������x��Ԫ��ǰ��k��λ�á�ɨ��������޸�L�ĳ���
void Del_x_2(SqList &L, ElemType x) {
    int k = 0;//k��¼ֵ����x��Ԫ�ظ���
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == x)
            k++;
        else
            L.data[i - k] = L.data[i];//��ǰԪ��ǰ��k��λ��
    }
    L.length -= k;//˳���L�ĳ��ȵݼ�
}


//04.������˳�����ɾ����ֵ�ڸ���ֵs��t֮�䣨Ҫ��s<t��������Ԫ�أ���s��t�������˳���Ϊ�գ�����ʾ������Ϣ���˳�����
//�㷨˼�룺��Ѱ��ֵ���ڵ���s�ĵ�һ��Ԫ�أ���һ��ɾ����Ԫ�أ���Ȼ��Ѱ��ֵ����t�ĵ�һ��Ԫ�أ����һ��ɾ����Ԫ�ص���һ��Ԫ�أ���Ҫ�����Ԫ��ɾ����ֻ��ֱ�ӽ������Ԫ��ǰ��
bool Del_s_t2(SqList &L, ElemType s, ElemType t) {
    int i, j;
    if (s >= t || L.length == 0)
        return false;
    for (i = 0; i < L.length && L.data[i] < s; i++);//Ѱ��ֵ���ڵ���s�ĵ�һ��Ԫ��
    if (i == L.length)
        return false;//����Ԫ��ֵ��С��s������
    for (j = i; j < L.length && L.data[j] <= t; j++);//Ѱ��ֵ����t�ĵ�һ��Ԫ��
    for (; j < L.length; i++, j++)
        L.data[i] = L.data[j];//ǰ�ƣ����ɾԪ��λ��
    L.length = i;
    return true;
}


//05.��˳�����ɾ����ֵ�ڸ���ֵs��t֮�䣨����s��t��Ҫ��s<t��������Ԫ�أ���s��t�������˳���Ϊ�գ�����ʾ������Ϣ���˳�����
//�㷨˼�룺��ǰ���ɨ��˳���L����k��¼��Ԫ��ֵ��s��t֮��Ԫ�صĸ�������ʼʱk=0�������ڵ�ǰɨ���Ԫ�أ�����ֵ����s��t֮�䣬��ǰ��k��λ�ã�����ִ��k++����������ÿ������s��t֮���Ԫ�ؽ��ƶ�һ�Σ�����㷨Ч�ʸ�
bool Del_s_t(SqList &L, ElemType s, ElemType t) {
    int k = 0;
    if (s >= t || L.length == 0)
        return false;//���Ա�Ϊ�ջ�s��t���Ϸ�������
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] >= s && L.data[i] <= t)
            k++;
        else
            L.data[i - k] = L.data[i];//��ǰԪ��ǰ��k��λ��
    }
    L.length -= k;//���ȼ�С
    return true;
}


//06.������˳�����ɾ��������ֵ�ظ���Ԫ�أ�ʹ��������Ԫ�ص�ֵ����ͬ
//�㷨˼�룺ע��������˳���ֵ��ͬ��Ԫ��һ����������λ���ϣ���������ֱ�Ӳ��������˼�룬��ʼʱ����һ��Ԫ����Ϊ���ظ��������֮�������жϺ����Ԫ���Ƿ���ǰ����ظ����������һ��Ԫ����ͬ������ͬ�����������жϣ�����ͬ�������ǰ��ķ��ظ����������ֱ���жϵ���βΪֹ
bool Delete_Same(SqList &L) {
    if (L.length == 0)
        return false;
    int i, j;//i�洢��һ������ͬ��Ԫ�أ�jΪ����ָ��
    for (i = 0, j = 1; j < L.length; j++) {
        if (L.data[j] != L.data[i])//������һ�����ϸ�Ԫ��ֵ��ͬ��Ԫ��
            L.data[++i] = L.data[j];//�ҵ��󣬽�Ԫ��ǰ��
    }
    L.length = i + 1;
    return true;
}


//07.����������˳���ϲ�Ϊһ���µ�����˳������ɺ������ؽ��˳���
//�㷨˼�룺���ȣ���˳�򲻶�ȡ������˳����ͷ��С�Ľ������µ�˳����С�Ȼ�󣬿��ĸ�����ʣ�࣬��ʣ�µĲ��ּӵ��µ�˳������
bool Merge(SqList A, SqList B, SqList &C) {
    if (A.length + B.length > MaxSize)//����˳������󳤶�
        return false;
    int i = 0, j = 0, k = 0;
    while (i < A.length && j < B.length) {//ѭ���������Ƚϣ�С�ߴ�������
        if (A.data[i] <= B.data[j])
            C.data[k++] = A.data[i++];
        else
            C.data[k++] = B.data[j++];
    }
    while (i < A.length)//��ʣһ��û�бȽ����˳���
        C.data[k++] = A.data[i++];
    while (j < B.length)
        C.data[k++] = B.data[j++];
    C.length = k;
    return true;
}


//08.��֪��һά����A[m+n]�����δ���������Ա�a1,a2,a3,��,am)�ͣ�b1,b2,b3,��,bn)����дһ��������������������˳����λ�û�����������b1,b2,b3,��,bn)���ڣ�a1,a2,a3,��,am)��ǰ��
//�㷨˼�룺�Ƚ�����A[m+n]�е�ȫ��Ԫ�أ�a1,a2,a3,����am,b1,b2,b3,����bn)ԭ������Ϊ��bn,bn-1,bn-2,����b1,am,am-1,am-2,��,a1),�ٶ�ǰn��Ԫ�غͺ�m��Ԫ�طֱ�ʹ�������㷨�����ɵõ���b1,b2,b3,��,bn,a1,a2,a3,��,am)���Ӷ�ʵ��˳����λ�û���
void Reverse1(ElemType A[], int left, int right, int arraySize) {//left��rightΪ�����±�
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


//09.���Ա�a1,a2,a3,����an)�е�Ԫ�ص��������Ұ�˳��洢�ڼ�����ڡ�Ҫ�����һ���㷨�����������ʱ���ڱ��в�����ֵΪx��Ԫ�أ����ҵ�����������Ԫ��λ���ཻ�������Ҳ��������������в�ʹ����Ԫ���Ե�������
//�㷨˼�룺˳��洢�����Ա�������򣬿���˳����ң�Ҳ�����۰���ҡ���ĿҪ�������ٵ�ʱ���ڱ��в�����ֵΪx��Ԫ�ء�������Ӧʹ���۰���ҷ�
void SearchExchangeInsert(SqList &L, ElemType x) {
    int low = 0, high = L.length - 1, mid, i;//1ow��highָ��˳����½���Ͻ���±�
    while (low <= high) {
        mid = (low + high) / 2;//���м�λ��
        if (L.data[mid] == x)
            break;//�ҵ�x,�˳�whileѭ��
        else if (L.data[mid] < x)
            low = mid + 1;//���е�mid���Ұ벿ȥ��
        else
            high = mid - 1;//���е�mid����벿ȥ��
    }
    //��������if���ֻ��ִ��һ��
    if (L.data[mid] == x && mid != L.length - 1) {//�����һ��Ԫ����x��ȣ��򲻴��������̽����Ĳ���
        ElemType temp = L.data[mid];
        L.data[mid] = L.data[mid + 1];
        L.data[mid + 1] = temp;
    }
    if (low > high) {//����ʧ�ܣ���������Ԫ��x����ʱlow=high+1��xӦ����low��λ��
        for (i = L.length - 1; i > high; i--)
            L.data[i + 1] = L.data[i];//����Ԫ��
        L.data[i + 1] = x;//����x
        L.length++;
    }//��������
}


//����189 https://leetcode.cn/problems/rotate-array/
//10.��2010ͳ�����⡿�轫n��n>1����������ŵ�һά����R�С����һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨����R�б��������ѭ������p��0<p<n����λ�ã�����R�е������ɣ�X0,X1,��,Xn-1)�任Ϊ��Xp,Xp+1,��,Xn-1,X0,X1,��,Xp-1)��Ҫ��
//(1)�����㷨�Ļ������˼��
//�㷨�Ļ������˼�룺�ɽ����������Ϊ������abת��������ba��a���������ǰp��Ԫ�أ�b�������������µ�n-p��Ԫ�أ����Ƚ�a���õõ�a-1b���ٽ�b���õõ�a-1b-1���������a-1b-1���õõ�(a-1b-1��-1=ba����Reverse����ִ�н�����Ԫ�����õĲ�������abcdefgh����ѭ���ƶ�3��p=3����λ�õĹ������£�
//Reverse(0,p-1)�õ�cbadefgh;
//Reverse(p,n-1)�õ�cbahgfed;
//Reverse(0,n-1)�õ�defghabc��
//ע��Reverse�У����������ֱ��ʾ�����д�ת��Ԫ�ص�ʼĩλ��
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע��
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
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷ�
//�����㷨������Reverse������ʱ�临�Ӷȷֱ�ΪO(p/2)��O((n-p)/2)��O(n/2)��������Ƶ��㷨��ʱ�临�Ӷ�ΪO��n)���ռ临�Ӷ�ΪO��1��


//����4 https://leetcode.cn/problems/median-of-two-sorted-arrays/
//11.��2011ͳ�����⡿һ������ΪL��L��1������������S�����ڵ�L/2������ȡ������λ�õ�����ΪS����λ�������磬������S1=��11,13,15,17,19������S1����λ����15���������е���λ���Ǻ���������Ԫ�ص��������е���λ�������磬��S2=��2,4,6,8,20������S1��S2����λ����11�������������ȳ���������A��B�������һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨���ҳ���������A��B����λ����Ҫ��
//(1)�����㷨�Ļ������˼��
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע��
int M_Search(int A[], int B[], int n) {
    int s1 = 0, d1 = n - 1, m1, s2 = 0, d2 = n - 1, m2;//�ֱ��ʾ����A��B����λ����ĩλ������λ��
    while (s1 != d1 || s2 != d2) {
        m1 = (s1 + d1) / 2;
        m2 = (s2 + d2) / 2;
        if (A[m1] == B[m2]) {
            return A[m1];
        } else if (A[m1] < B[m2]) {
            if ((s1 + d1) % 2 == 0) {//Ԫ�ظ���Ϊ����
                s1 = m1;
                d2 = m2;
            } else {//Ԫ�ظ���Ϊż��
                s1 = m1 + 1;
                d2 = m2;
            }
        } else {
            if ((s2 + d2) % 2 == 0) {//Ԫ�ظ���Ϊ����
                s2 = m2;
                d1 = m1;
            } else {//Ԫ�ظ���Ϊż��
                s2 = m2 + 1;
                d1 = m1;
            }
        }
    }
    return A[s1] < B[s2] ? A[s1] : B[s2];
}

//���Ž⣺����ָ�����
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
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷ�
//�㷨��ʱ�临�Ӷ�ΪO(log2n)���ռ临�Ӷ�ΪO(1)
//���Ž��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)


//����169 https://leetcode.cn/problems/majority-element/
//12.��2013ͳ�����⡿��֪һ����������A=��a0,a1,��,an-1��������0��ai<n��0��i<n)��������ap1=ap2=��=apm=x��m>n/2��0��pk<n,1��k��m��,���xΪA����Ԫ�ء�����A=��0,5,5,3,5,7,5,5��,��5Ϊ��Ԫ�أ�����A=��0,5,5,3,5,1,5,7��,��A��û����Ԫ�ء�����A�е�n��Ԫ�ر�����һ��һά�����У������һ�������ܸ�Ч���㷨���ҳ�A����Ԫ�ء���������Ԫ�أ��������Ԫ�أ��������-1��Ҫ��
//(1)�����㷨�Ļ������˼��
//�㷨�Ļ������˼�룺�㷨�Ĳ����Ǵ�ǰ���ɨ������Ԫ�أ���ǳ�һ�����ܳ�Ϊ��Ԫ�ص�Ԫ��Num��Ȼ�����¼�����ȷ��Num�Ƿ�����Ԫ�ء�
//�㷨�ɷ�Ϊ����������
//��ѡȡ��ѡ����Ԫ�ء�����ɨ�����������е�ÿ������������һ������������Num���浽c�У���¼Num�ĳ��ִ���Ϊ1������������һ�������Ե���Num���������1�����������1������������0ʱ������������һ���������浽c�У��������¼�Ϊ1����ʼ��һ�ּ��������ӵ�ǰλ�ÿ�ʼ�ظ��������̣�ֱ��ɨ����ȫ������Ԫ�ء�
//���ж�c��Ԫ���Ƿ�����������Ԫ�ء��ٴ�ɨ������飬ͳ��c��Ԫ�س��ֵĴ�����������n/2����Ϊ��Ԫ�أ����������в�������Ԫ�ء�
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע��
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
    if (count > 0) {//����жϼӲ��Ӷ��ɣ�������ѭ��һ��Ҫ��
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
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷ�
//ʵ�ֵĳ����ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)


//����41 https://leetcode.cn/problems/first-missing-positive/
//13.��2018ͳ�����⡿����һ����n��n��1�������������飬�����һ����ʱ���Ͼ����ܸ�Ч���㷨���ҳ�������δ���ֵ���С�����������磬����{-5,3,2,3}��δ���ֵ���С��������1������{1��2,3}��δ���ֵ���С��������4��Ҫ��
//(1)�����㷨�Ļ������˼��
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע��
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
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷ�
//ʱ�临�Ӷȣ�����Aһ�Σ�����Bһ�Σ�����ѭ���ڲ�������ΪO(1)���������ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷȣ����������B[n]���ռ临�Ӷ�ΪO(n)��



//14.��2020ͳ�����⡿������Ԫ��(a,b,c)(a��b��c��Ϊ�������ľ���D=|a-b|+|b-c|+|c-a|������3���ǿ���������S1��S2��S3��������ֱ�洢��3�������С������һ�������ܸ�Ч���㷨�����㲢������п��ܵ���Ԫ�飨a,b,c)��aES1��bES2��cES3���е���С���롣����S1={-1,0,9},S2={-25,-10,10,11},S3={2,9,17,30,41},����С����Ϊ2����Ӧ����Ԫ��Ϊ��9,10,9����Ҫ��
//(1)�����㷨�Ļ������˼��
//(2)�������˼�룬����C���Ի�C++���������㷨���ؼ�֮������ע��

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
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷ�
//��n=(|S1|+|S2|+|S3|)��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
