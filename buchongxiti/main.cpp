#include <iostream>

//1.��֪һ����������A=(a0,a1,��,an-1),����0��ai<n(0��i<n)����������ѡ��һЩ����Ҫ��ѡ�����������������ľ���ֵС�ڵ���k�����һ����ʱ���Ͼ����ܸ�Ч���㷨���������ѡ���Ԫ�ظ�����
//��1������ö��
//����ѭ������ÿһ��ai����������б�������ֵ����ai-k��ai+k������Ԫ�أ���¼ѡȡ������Ԫ�ظ������������ֵ��
//ʱ�临�Ӷ�ΪO(n2)���ռ临�Ӷ�ΪO(1)
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

//��2���ȿ��ţ��ٴӵ�ÿ��Ԫ�������ұ������˲�����k������Ԫ�أ���¼ѡȡ������Ԫ�ظ������������ֵ��
//���ŵ�ʱ�临�Ӷ�ΪO(nlogn)�������������ʱ����ΪO(n2)������ʱ�临�Ӷ���ΪO(n2)���ռ临�Ӷ�ΪO(logn)
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
        for (int j = i; j < n && abs(A[i] - A[j]) <= k; j++)//��i������
            count++;
        for (int m = i - 1; m >= 0 && abs(A[i] - A[m]) <= k; m--)//��i������
            count++;
        if (count > max)
            max = count;
        count = 0;
    }
    return max;
}

//��3������+����ָ���Ż�����Ϊ��������jָ����Բ���ÿ�ζ����´�i��ʼ�ƶ���j����ֱ����֮ǰ��λ����������
//���ŵ�ʱ�临�Ӷ�ΪO(nlogn)�������������ʱ���ΪO(n)������ʱ�临�Ӷ���ΪO(nlogn)���ռ临�Ӷ�ΪO(logn)
int getMaxCount3(int A[], int n, int k) {
    int count, max = 0;
    QuickSort(A, 0, n - 1);
    int i = 0, j = 0, m = 0;
    for (; i < n; i++) {
        for (; j < n && abs(A[i] - A[j]) <= k; j++);//A[j]��A[i]�ұ��ܱ�֤A[j]-A[i]<=k������Ԫ��
        for (; m < n && abs(A[i] - A[m]) > k; m++);//A[m]��A[i]����ܱ�֤A[i]-A[m]<=k����С��Ԫ�ص���߰��ŵ�Ԫ��
        count = j - m;
        if (count > max)
            max = count;
    }
    return max;
}


//2.�������У�ĳ�����ּ�ȥ���ұߵ����ֵõ�һ������֮�����������֮������ֵ�����磬������{2, 4, 1, 16, 7, 5, 11, 9}�У�����֮������ֵ��11����16��ȥ5�Ľ�������һ����ʱ���Ͼ����ܸ�Ч���㷨�����������֮������ֵ��
//��1��������
//���ȣ��������飬�ҵ����еĲ�ֵ��Ȼ�󣬴����в�ֵ���ҳ����ֵ������ʵ�ַ���Ϊ���������a�е�ÿһ��Ԫ��a[i], ������a[i]-a[j](i<j<n)��ֵ�е����ֵ
//ʱ�临�Ӷ�ΪO(n2)���ռ临�Ӷ�ΪO(1)
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

//��2����̬�滮
//��������a��������������diff��max������diff[i]���������i+1������Ϊ��������������֮������ֵ��ǰi+1��������ɵ������������Ĳ�ֵ����max[i]Ϊǰi+1���������ֵ�������Ѿ������diff[i]��diff[i+1]��ֵ�����ֿ�����
//(1)����diff[i]
//(2)����max[i]-a[i]
//���Եõ���diff[i+1] = max(diff[i],max[i-1]-a[i])��max[i+1] = max(max[i], a[i+1])
//�������Ĳ�ֵΪdiff[n-1] (nΪ����ĳ���)
//�����������һ�α�����ʱ�临�Ӷ�ΪO(n)������������������������飬�������㷨�Ŀռ临�Ӷ�ΪO(n)
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

//��̬�滮�Ż���
//����� diff[i+1]ʱ��ֻ�õ���diff[i]��max[i]����������diff��max�����������޹أ���˿���ͨ������������������������¼diff[i]��max[i]��ֵ���Ӷ��������㷨�Ŀռ临�Ӷ�
//ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)
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

//3.��һ������A��2n+1��������ͬ����������ɣ��������е����ȼ���������n+1��������Сֵ������һ������key�������һ��ʱ��Ϳռ��Ͼ����ܸ�Ч���㷨���ж�key�Ƿ��ڸ������У��ǵĻ����������±꣬���򷵻�-1�������ӦA={10, 7, 5, 2, 6, 13, 15}��key=5ʱ����true����key=8�򷵻�false��
//��1����������
//ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)
bool find1(int A[], int key, int n) {
    for (int i = 0; i < n; i++) {
        if (A[i] == key) {
            return true;
        }
    }
    return false;
}

//��2���ڵ�n+1λ�����������߷ֱ��۰����
//ʱ�临�Ӷ�ΪO(logn)���ռ临�Ӷ�ΪO(1)
bool find2(int A[], int key, int n) {
    if (A[n / 2] == key) {
        return true;
    }
    //���Ϊ����
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
    //�ұ�Ϊ����
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
