#include <iostream>

typedef int ElemType;

//02.��˳���������A[]��ʾ������Ԫ�ش洢�������±�1~m+n�ķ�Χ�ڣ�ǰm��Ԫ�ص������򣬺�n��Ԫ�ص����������һ���㷨��ʹ������˳�������
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C/C++�����㷨���ؼ�֮������ע�͡�
//(3)˵����������㷨��ʱ�临�Ӷ���ռ临�Ӷȡ�
void Insert_Sort(ElemType A[], int m, int n) {
    int i, j;
    for (i = m + 1; i < m + n; i++) {//���ν�A[m+1...m+n]���������
        A[0] = A[i];
        for (j = i - 1; A[j] > A[0]; j--) {
            A[j + 1] = A[j];
        }
        A[j + 1] = A[0];
    }
}


//03.��һ�ּ򵥵������㷨����Ϊ��������count sorting�������������㷨��һ��������ı��������ʾ���������򣬲�����������ŵ���һ���µı��С�����ע����ǣ��������д�����Ĺؼ��뻥����ͬ�����������㷨��Ա��е�ÿ����¼��ɨ�������ı�һ�ˣ�ͳ�Ʊ����ж��ٸ���¼�Ĺؼ���ȸü�¼�Ĺؼ���С���������ĳ����¼ͳ�Ƴ��ļ���ֵΪc���������¼����������еĺ��ʴ��λ�ü�Ϊc��
//(1)���ʵ�ּ���������㷨��
//(2)������n����¼�ı��ؼ���Ƚϴ����Ƕ��٣�
//(3)���ѡ��������Ƚϣ����ַ����Ƿ���ã�Ϊʲô��
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


//04.����һ�������д����һ������Ĺؼ�����K1,K2,...,Kn����Ҫ��Kn���ڽ�Ԫ����������ȷλ���ϣ��Ա�дʵ�ָù��ܵ��㷨��Ҫ��ȽϹؼ��ֵĴ���������n��
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
