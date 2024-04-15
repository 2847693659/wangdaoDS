#include <iostream>

typedef int ElemType;

void swap(ElemType &a, ElemType &b) {
    ElemType temp = a;
    a = b;
    b = temp;
}

//02.��д˫��ð�������㷨���������������������ɨ�裬����һ�˰ѹؼ�������Ԫ�ط������е�����棬�ڶ��˰ѹؼ�����С��Ԫ�ط������е���ǰ�棬��˷������С�
void BubbleSort(ElemType A[], int n) {
    int low = 0, high = n - 1;
    bool flag = true;//һ��ð�ݺ��¼Ԫ���Ƿ񽻻���־
    while (low < high && flag) {//ѭ��������������flagΪfalse˵����û������
        flag = false;//ÿ�˳�ʼ��flagΪfalse
        for (int i = low; i < high; i++) {//��ǰ�������
            if (A[i] > A[i + 1]) {//��������
                swap(A[i], A[i + 1]);//����
                flag = true;//��flag
            }
        }
        high--;//�����Ͻ�
        for (int i = high; i > low; i--) {//�Ӻ���ǰ����
            if (A[i] < A[i - 1]) {//��������
                swap(A[i], A[i - 1]);//����
                flag = true;//��flag
            }
        }
        low++;//�޸��½�
    }
}


//03.��֪���Ա�˳��洢����ÿ��Ԫ�ض��ǲ���ͬ��������Ԫ�أ���ư����������ƶ�������ż��ǰ�ߵ��㷨��Ҫ��ʱ�����٣������ռ����٣���
//����ɲ��û��ڿ�������Ļ���˼��������㷨��ֻ�����һ�μ��ɣ���ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)�������ΪL[1...n]������˼���ǣ��ȴ�ǰ����ҵ�һ��ż��Ԫ��L(i)���ٴӺ���ǰ�ҵ�һ������Ԫ��L(j)�������߽������ظ���������ֱ��i����j��
void move(ElemType A[], int n) {
    int i = 0, j = n - 1;//i��ʾ���ż��Ԫ�ص��±ꣻj��ʾ�Ҷ�����Ԫ�ص��±�
    while (i < j) {
        while (i < j && A[i] % 2 != 0)//��ǰ����ҵ�һ��ż��Ԫ��
            i++;
        while (i < j && A[j] % 2 != 1)//�Ӻ���ǰ�ҵ�һ������Ԫ��
            j--;
        if (i < j) {
            swap(A[i], A[j]);//����������Ԫ��
            i++;
            j--;
        }
    }
}


//04.�����±�д���㾫���еĿ�������Ļ����㷨��ʹ֮ÿ��ѡȡ������ֵ��������شӵ�ǰ�ӱ���ѡ��ġ�
int Partition2(ElemType A[], int low, int high) {
    int rand_Index = low + rand() % (high - low + 1);
    swap(A[rand_Index], A[low]);//������ֵ��������һ��Ԫ��
    ElemType pivot = A[low];//�õ�ǰ���еĵ�һ��Ԫ��Ϊ����ֵ
    int i = low;//ʹ�ñ�A[low��i]�е�����Ԫ��С��pivot����ʼΪ�ձ�
    for (int j = low + 1; j <= high; j++) {//�ӵڶ���Ԫ�ؿ�ʼѰ��С�ڻ�׼��Ԫ��
        if (A[j] < pivot)//�ҵ��󣬽�����ǰ��
            swap(A[++i], A[j]);
    }
    swap(A[i], A[low]);//����׼Ԫ�ز�������λ��
    return i;//���ػ�׼Ԫ�ص�λ��
}


//05.�Ա�дһ���㷨��ʹ֮�ܹ�������L[1...n]���ҳ���kС��Ԫ�أ�����С����������ڵ�k��λ�õ�Ԫ�أ���
int kth_elem(ElemType a[], int low, int high, int k) {
    ElemType pivot = a[low];
    int low_temp = low, high_temp = high;//����������޸�1ow��high���ڵݹ�ʱ��Ҫ�õ�����
    while (low < high) {
        while (low < high && a[high] >= pivot)
            high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivot)
            low++;
        a[high] = a[low];
    }
    a[low] = pivot;
    if (low == k)//������k��ͬ��ֱ�ӷ���pivotԪ��
        return a[low];
    else if (low > k)//��ǰһ���ֱ��еݹ�Ѱ��
        return kth_elem(a, low_temp, low - 1, k);
    else//�ں�һ���ֱ��еݹ�Ѱ��
        return kth_elem(a, low + 1, high_temp, k - (low - low_temp + 1));
}


//06.�����������⣺����һ�����ɺ졢�ס���������ɫ��������ɵ��������У����дһ��ʱ�临�Ӷ�ΪO(n)���㷨��ʹ����Щ���鰴�졢�ס�����˳���źã����ųɺ�������ͼ����
typedef enum {
    RED, WHITE, BLUE
} color;//����ö������

void swap_color(color &a, color &b) {
    color temp = a;
    a = b;
    b = temp;
}

void Flag_Arrange(color a[], int n) {
    int i = 0, j = 0, k = n - 1;
    while (j <= k) {
        switch (a[j]) {//�ж��������ɫ
            case RED://��ɫ�����i����
                swap_color(a[i], a[j]);
                i++;
                j++;
                break;//switch��䲻����ִ���ж�Ϊ�������֮������ѭ�������Ǽ���ִ�к�������case��䣬���Ҫ��break
            case WHITE:
                j++;
                break;
            case BLUE://��ɫ�����k����
                swap_color(a[j], a[k]);
                k--;//����û��j++����Է�ֹ������a[j]��Ϊ��ɫ�����
        }
    }
}


//07.��2016ͳ�����⡿��֪��n��n��2�������������ɵļ���A={ak|0��k<n}�����仮��Ϊ�������ཻ���Ӽ�A1��A2��Ԫ�ظ����ֱ���n1��n2��A1��A2�е�Ԫ��֮�ͷֱ�ΪS1��S2�����һ�������ܸ�Ч�Ļ����㷨������|n1-n2|��С��|S1-S2|���Ҫ��
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
//(3)˵����������㷨��ƽ��ʱ�临�ӶȺͿռ临�Ӷȡ�
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
