#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

//01.���һ���ݹ��㷨��ɾ������ͷ���ĵ�����L������ֵΪx�Ľ��
//�㷨��Ҫ����һ���ݹ鹤��ջ�����ΪO(n)��ʱ�临�Ӷ�ΪO(n)���ж�����Ϊֱ��ȥ��p������ɶ�����ʵ������ΪLΪ���ã���ֱ�Ӷ�ԭ������в����ģ���˲��������
void Del_X_1(LinkList &L, ElemType x) {
    LNode *p;//pָ���ɾ�����
    if (L == NULL)//�ݹ����
        return;
    if (L->data == x) {//��L��ָ����ֵΪx
        p = L;//ɾ��*L������Lָ����һ���
        L = L->next;
        free(p);
        Del_X_1(L, x);//�ݹ����
    } else {//��L��ָ����ֵ��Ϊx
        Del_X_1(L->next, x);//�ݹ����
    }
}


//02.�ڴ�ͷ���ĵ�����L�У�ɾ������ֵΪx�Ľ�㣬���ͷ���ռ䣬����ֵΪ���Ľ�㲻Ψһ���Ա�д�㷨��ʵ����������
//�ⷨһ����p��ͷ��βɨ�赥����preָ��*p����ǰ������p��ָ����ֵΪx����ɾ��������p������һ����㣬������pre��pָ��ͬ������һ����㡣
void Del_X_2(LinkList &L, ElemType x) {
    LNode *p = L->next, *pre = L, *q;
    while (p != NULL) {
        if (p->data == x) {
            q = p;//gָ��ý��
            p = p->next;
            pre->next = p;//ɾ��*q���
            free(q);//�ͷ�*q���Ŀռ�
        } else {//����pre��pͬ������
            pre = p;
            p = p->next;
        }
    }
}

//�ⷨ��������β�巨������������pָ��ɨ��L�����н�㣬����ֵ��Ϊxʱ���������ӵ�L֮�󣬷������ͷš�
void Del_X_3(LinkList &L, ElemType x) {
    LNode *p = L->next, *r = L, *q;//rָ��β��㣬���ֵΪͷ���
    while (p != NULL) {
        if (p->data != x) {//*p���ֵ��Ϊxʱ�������ӵ�Lβ��
            r->next = p;
            r = p;
            p = p->next;//����ɨ��
        } else {//*p���ֵΪxʱ�����ͷ�
            q = p;
            p = p->next;//����ɨ��
            free(q);//�ͷſռ�
        }
    }
    r->next = NULL;//�����������β���ָ��ΪNULL
}


//03.��LΪ��ͷ���ĵ�������д�㷨ʵ�ִ�β��ͷ�������ÿ������ֵ
//
void R_Print(LinkList L) {
    if (L->next != NULL)
        R_Print(L->next);//�ݹ�
    if (L != NULL)//û�����if�ж�Ҳ����
        printf("%d", L->data);
}

void R_Ignore_Head(LinkList L) {
    if (L->next != NULL)
        R_Print(L->next);
}


//04.�Ա�д�ڴ�ͷ���ĵ�����L��ɾ��һ����Сֵ���ĸ�Ч�㷨��������Сֵ�����Ψһ�ģ�
//�㷨˼�룺��p��ͷ��βɨ�赥����preָ��*p����ǰ������minp����ֵ��С�Ľ��ָ�루��ֵΪp����minpreָ��*minp����ǰ������ֵΪpre����һ��ɨ�裬һ�߱Ƚϣ���p->dataС��minp->data,��p��pre�ֱ�ֵ��minp��minpre,����ͼ��ʾ����pɨ�����ʱ��minpָ��Сֵ��㣬minpreָ����Сֵ����ǰ����㣬�ٽ�minp��ָ���ɾ�����ɡ�
void Delete_Min(LinkList &L) {
    LNode *pre = L, *p = L->next;//pΪ����ָ�룬preָ����ǰ��
    LNode *minpre = pre, *minp = p;//������Сֵ��㼰��ǰ��
    while (p != NULL) {
        if (p->data < minp->data) {
            minp = p;//�ҵ���֮ǰ�ҵ�����Сֵ����С�Ľ��
            minpre = pre;
        }
        pre = p;//����ɨ����һ�����
        p = p->next;
    }
    minpre->next = minp->next;//ɾ����Сֵ���
    free(minp);
}
//�㷨��Ҫ��ͷ��βɨ������ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��


//05.�Ա�д�㷨����ͷ���ĵ�����͵����ã���ν"�͵�"��ָ�����ռ临�Ӷ�ΪO(1)
//�ⷨһ����ͷ���ժ�£�Ȼ��ӵ�һ��㿪ʼ�����β��뵽ͷ���ĺ��棨ͷ�巨������������ֱ�����һ�����Ϊֹ��������ʵ������������á�
void Reverse_1(LinkList &L) {
    LNode *p = L->next, *r;//pΪ����ָ�룬rΪp�ĺ�̣��Է�����
    L->next = NULL;//�Ƚ�ͷ���L��next����ΪNULL
    while (p != NULL) {//���ν�Ԫ�ؽ��ժ��
        r = p->next;//�ݴ�p�ĺ��
        p->next = L->next;//��p�����뵽ͷ���֮��
        L->next = p;
        p = r;
    }
}
//�����㷨��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��

//�ⷨ�������α������Ա�L���������ָ�뷴ת
void Reverse_2(LinkList &L) {
    LNode *pre, *p = L->next, *r = p->next;
    p->next = NULL;//�����һ�����
    while (r != NULL) {//rΪ�գ���˵��pΪ���һ�����
        pre = p;//���μ�������
        p = r;
        r = r->next;
        p->next = pre;//ָ�뷴ת
    }
    L->next = p;//�������һ�����
}
//�����㷨��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��


//06.��һ����ͷ���ĵ�����L�����һ���㷨ʹ��Ԫ�ص�������
//�㷨˼�룺����ֱ�Ӳ��������㷨��˼�룬�ȹ���ֻ��һ�����ݽ�����������Ȼ������ɨ�赥������ʣ�µĽ��*p��ֱ��p==NULLΪֹ�������������ͨ���Ƚϲ��Ҳ���*p��ǰ�����*pre��Ȼ��*p���뵽*pre֮��
void Sort(LinkList &L) {
    LNode *pre, *p = L->next, *r = p->next;//r����*p��̽��ָ�룬�Ա�֤������
    p->next = NULL;//����ֻ��һ�����ݽ��������
    p = r;
    while (p != NULL) {
        r = p->next;//����*p�ĺ�̽��ָ��
        pre = L;
        while (pre->next != NULL && pre->next->data < p->data)
            pre = pre->next;//��������в��Ҳ���*p��ǰ�����*pre
        p->next = pre->next;//��*p���뵽*pre֮��
        pre->next = p;
        p = r;//ɨ��ԭ��������ʣ�µĽ��
    }
}
//���㷨��ʱ�临�Ӷ�ΪO(n2)��Ϊ�ﵽ��ѵ�ʱ�����ܣ����Ƚ���������ݸ��Ƶ������У��ٲ���ʱ�临�Ӷ�ΪO(nlog2n)�������㷨��������Ȼ������Ԫ�����β��뵽�����У���ʱ��ʱ�临�Ӷ�ΪO(nlog2n)����Ȼ�����Կռ任ʱ��Ĳ��ԡ�


//07.����һ������ͷ���ĵ�����������Ԫ�ؽ�������ֵ�����Ա�дһ��������ɾ���������н��ڸ���������ֵ����Ϊ��������������֮���Ԫ�ص�Ԫ�أ������ڣ�
//��Ϊ����������ģ�����ֻ����������м�飬ִ��ɾ��
void RangeDelete(LinkList &L, ElemType from, ElemType to) {
    LNode *pre = L, *p = L->next;
    while (p != NULL) {
        if (p->data > from && p->data < to) {
            pre->next = p->next;
            free(p);
            p = pre->next;
        } else {
            pre = p;
            p = p->next;
        }
    }
}


//08.����������������д�㷨�ҳ���������Ĺ������
//������Ҫ�ֱ������������õ����ǵĳ��ȣ��������������֮��ڳ����������ȱ�������֮������֮����ͬ��������������ֱ���ҵ���ͬ�Ľ�㣬����һֱ�������������ʱ���÷�����ʱ�临�Ӷ�ΪO(len1+len2)
int Length(LinkList L) {//Ĭ�ϴ�ͷ���
    int n = 0;
    L = L->next;
    while (L != NULL) {
        n++;
        L = L->next;
    }
    return n;
}

LNode *Search_lst_Common(LinkList L1, LinkList L2) {
    int len1 = Length(L1), len2 = Length(L2), dist;
    LinkList longList, shortList;
    if (len1 >= len2) {
        longList = L1->next;
        shortList = L2->next;
        dist = len1 - len2;
    } else {
        longList = L2->next;
        shortList = L1->next;
        dist = len2 - len1;
    }
    while (dist > 0) {
        longList = longList->next;
        dist--;
    }
    while (longList != NULL) {
        if (longList == shortList)
            return longList;
        else {
            longList = longList->next;
            shortList = shortList->next;
        }
    }
    return NULL;
}


//09.����һ������ͷ���ĵ�������headΪͷָ�룬���ṹΪ(data,next)��dataΪ����Ԫ�أ�nextΪָ�룬��д���㷨����������������������и���������Ԫ�أ����ͷŽ����ռ�Ĵ洢�ռ䣨Ҫ�󣺲�����ʹ��������Ϊ�����ռ䣩
//����06��ֱ�Ӳ��������˼��
void Min_Delete(LinkList &L) {
    while (L->next != NULL) {
        LNode *pre = L, *p = L->next;
        while (p->next != NULL) {
            if (p->next->data < pre->next->data)
                pre = p;
            p = p->next;
        }
        printf("%d", pre->next->data);
        LNode *u = pre->next;
        pre->next = u->next;
        free(u);
    }
    free(L);
}


//10.��һ����ͷ���ĵ�����A�ֽ�Ϊ������ͷ���ĵ�����A��B,ʹ��A���к���ԭ�������Ϊ������Ԫ�أ���B���к���ԭ�������Ϊż����Ԫ�أ��ұ��������˳�򲻱�
//
LinkList DisCreat_1(LinkList &A) {
    int i = 0;
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *ra = A, *rb = B, *p = A->next;
    A->next = NULL;
    while (p != NULL) {
        i++;
        if (i % 2 == 0) {
            rb->next = p;
            rb = p;
        } else {
            ra->next = p;
            ra = p;
        }
        p = p->next;
    }
    ra->next = NULL;
    rb->next = NULL;
    return B;
}


//11.��C={a1,b1,a2,b2,����an,bn}Ϊ���Ա����ô�ͷ���ĵ������ţ����һ���͵��㷨��������Ϊ�������Ա�ʹ��A={a1,a2,��,an}��B={bn,��,b2,b1}
//
LinkList DisCreat_2(LinkList &A) {
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *ra = A, *p = A->next, *q;
    while (p != NULL) {
        ra->next = p;
        ra = p;
        p = p->next;
        if (p != NULL) {
            q = p->next;
            p->next = B->next;
            B->next = p;
            p = q;
        }
    }
    ra->next = NULL;
    return B;
}


//12.��һ��������������Ա��У�����ֵ��ͬ��Ԫ�ش��ڡ����洢��ʽΪ����������㷨ȥ����ֵ��ͬ��Ԫ�أ�ʹ���в������ظ���Ԫ�أ�����(7,10,10,21,30,42,42,42,51,70)����Ϊ(7,10,21,30,42,51,70)
//�㷨˼�룺�����������������ֵͬ��Ľ�㶼�����ڵġ���pɨ�����������L����*p����ֵ��������̽���ֵ����ɾ�����ߣ�����p������һ����㡣
void Del_Same(LinkList &L) {
    LNode *p = L->next, *q;
    while (p != NULL) {
        q = p->next;
        if (q->data == p->data) {
            p->next = q->next;
            free(q);
        } else
            p = p->next;
    }
}
//���㷨��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��
//����Ҳ�ɲ���β�巨����ͷ���ժ�£�Ȼ��ӵ�һ��㿪ʼ���������Ѿ����������������һ�����Ƚϣ���������ֱ�Ӳ��룬���򽫵�ǰ�����Ľ��ɾ����������һ����㣬ֱ�����һ�����Ϊֹ��


//13.������������Ԫ��ֵ�����������е����Ա����Ե�������ʽ�洢�����д�㷨��������������鲢Ϊһ����Ԫ��ֵ�ݼ��������еĵ�������Ҫ������ԭ������������Ľ���Ź鲢��ĵ�����
//
void MergeList(LinkList &L1, LinkList &L2) {
    LNode *p1 = L1->next, *p2 = L2->next, *q;
    L1->next = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->data <= p2->data) {
            q = p1->next;
            p1->next = L1->next;
            L1->next = p1;
            p1 = q;
        } else {
            q = p2->next;
            p2->next = L1->next;
            L1->next = p2;
            p2 = q;
        }
    }
    while (p1 != NULL) {
        q = p1->next;
        p1->next = L1->next;
        L1->next = p1;
        p1 = q;
    }
    while (p2 != NULL) {
        q = p2->next;
        p2->next = L1->next;
        L1->next = p2;
        p2 = q;
    }
    free(L2);
}


//14.��A��B��������������ͷ��㣩������Ԫ�ص����������һ���㷨��A��B�еĹ���Ԫ�ز���������C��Ҫ���ƻ�A��B�Ľ��
//
void Get_Common(LinkList A, LinkList B) {
    LNode *pa = A->next, *pb = B->next, *r;
    LinkList C = (LinkList) malloc(sizeof(LNode));
    r = C;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data)
            pa = pa->next;
        else if (pa->data > pb->data)
            pb = pb->next;
        else {
            LNode *s = (LNode *) malloc(sizeof(LNode));
            s->data = pa->data;
            r->next = s;
            r = s;
            pa = pa->next;
            pb = pb->next;
        }
    }
    r->next = NULL;
}


//15.��֪��������A��B�ֱ��ʾ�������ϣ���Ԫ�ص������С����ƺ�������A��B�Ľ������������A������
//
LinkList Union(LinkList &A, LinkList &B) {
    LNode *pa = A->next, *pb = B->next, *r = A, *q;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            q = pa;
            pa = pa->next;
            free(q);
        } else if (pa->data > pb->data) {
            q = pb;
            pb = pb->next;
            free(q);
        } else {
            r->next = pa;
            r = pa;
            pa = pa->next;
            q = pb;
            pb = pb->next;
            free(q);
        }
    }
    while (pa != NULL) {
        q = pa;
        pa = pa->next;
        free(q);
    }
    while (pb != NULL) {
        q = pb;
        pb = pb->next;
        free(q);
    }
    r->next = NULL;
    free(B);
    return A;
}
//���㷨��ʱ�临�Ӷ�ΪO(len1+len2)���ռ临�Ӷ�ΪO(1)


//16.������������A=a1,a2,a3,��,am��B=b1,b2,b3,��,bn�Ѿ����������������У����һ���㷨���ж�����B�Ƿ�������A������������
//
int Pattern(LinkList A, LinkList B) {
    LNode *pa = A, *pb = B, *pre = pa;
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {
            pa = pa->next;
            pb = pb->next;
        } else {
            pa = pre->next;
            pre = pa;
            pb = B;
        }
    }
    if (pb == NULL)
        return 1;
    else
        return 0;
}


//17.���һ���㷨�����жϴ�ͷ����ѭ��˫�����Ƿ�Գ�
//
int Symmetry(DLinkList L) {
    DNode *p = L->next, *q = L->prior;
    while (p != q && q->next != p) {//ǰ���ΪԪ������������ʱ�����������ΪԪ��������ż��ʱ�������ע�������q->next != p�����������L��Ԫ�صĸ���Ϊż�������Ƚ����е����ҵ�Ԫ�غ�p��������ƶ���q������ǰ�ƶ�����ʱq��pǰ�棬�����ж�����Ϊq->next != p
        if (p->data == q->data) {
            p = p->next;
            q = q->prior;
        } else
            return 0;
    }
    return 1;
}


//18.������ѭ������������ͷָ��ֱ�Ϊh1��h2����дһ������������h2���ӵ�����h1֮��Ҫ�����Ӻ�������Ա���ѭ��������ʽ
//
LinkList Link(LinkList &h1, LinkList &h2) {
    LNode *p1 = h1, *p2 = h2;
    while (p1->next != h1)
        p1 = p1->next;
    while (p2->next != h2)
        p2 = p2->next;
    p1->next = h2;
    p2->next = h1;
    return h1;
}


//19.����һ����ͷ����ѭ������������ֵ��Ϊ�����������һ���㷨�������ҳ��������н��ֵ��С�Ľ�㲢�����Ȼ�󽫸ý�����ɾ����ֱ���������Ϊֹ����ɾ����ͷ���
//
void Del_All(LinkList &L) {
    LNode *p, *pre, *minp, *minpre;
    while (L->next != L) {
        p = L->next;
        pre = L;
        minp = p;
        minpre = pre;
        while (p != L) {
            if (p->data < minp->data) {
                minp = p;
                minpre = pre;
            }
            pre = p;
            p = p->next;
        }
        printf("%d", minp->data);
        minpre->next = minp->next;
        free(minp);
    }
    free(L);
}


//20.��ͷָ��ΪL�Ĵ��б�ͷ���ķ�ѭ��˫��������ÿ������г���pred��ǰ��ָ�룩��data�����ݣ���next�����ָ�룩���⣬����һ������Ƶ����freq������������ǰ����ֵ����ʼ��Ϊ�㡣ÿ���������н���һ��Locate(L,x)����ʱ����Ԫ��ֵΪx�Ľ����freq���ֵ��1����ʹ�������н�㱣�ְ�����Ƶ�ȷ������ݼ�����˳�����У�ͬʱ������ʵĽ������Ƶ����ͬ�Ľ��ǰ�棬��ʹʹƵ�����ʵĽ�����ǿ�����ͷ���Ա�д��������Ҫ���Locate(L,x)������㷨��������Ϊ�������̣������ҵ����ĵ�ַ������Ϊָ����
//�㷨˼�룺������˫�������в�������ֵΪx�Ľ�㣬�鵽�󣬽�����������ժ�£�Ȼ��˳�Ž���ǰ�������Ҹý��Ĳ���λ�ã�Ƶ�ȵݼ���������ͬƵ�ȵĵ�һ��������ǰ�ҵ���һ��������Ƶ�ȴ�Ľ�㣬����λ��Ϊ�ý��֮�󣩣������뵽��λ�á�
typedef struct DFNode {
    ElemType data;
    struct DFNode *prior, *next;
    int freq;
} DFNode, *DFLinkList;

DFNode *Locate(DFLinkList &L, ElemType x) {
    DFNode *p = L->next, *pre;//pΪ����ָ�룬preΪp��ǰ�������ڲ��Ҳ���λ��
    while (p != NULL && p->data != x)
        p = p->next;//����ֵΪx�Ľ��
    if (p == NULL)
        exit(0);//������ֵΪx�Ľ��
    else {
        p->freq++;//��Ԫ��ֵΪx�Ľ���freq���1
        if (p->prior == L || p->prior->freq > p->freq)
            return p;//p�������׽�㣬��freqֵС��ǰ��
        if (p->next != NULL)
            p->next->prior = p->prior;
        p->prior->next = p->next;//��p����������ժ��
        pre = p->prior;//���²���p���Ĳ���λ��
        while (pre != L && pre->freq <= p->freq)
            pre = pre->prior;
        p->next = pre->next;//��p�������ͬƵ�ʵĵ�һ��
        if (pre->next != NULL)
            pre->next->prior = p;
        p->prior = pre;
        pre->next = p;
    }
    return p;//����ֵΪx�Ľ���ָ��
}


//21.�������л�����ָ����������һ������ָ��ָ���������е�ĳ����㣨ͨ������������һ������ָ�����ǿյģ����Ա�д�㷨�жϵ������Ƿ���ڻ���
//(1)�����㷨�Ļ������˼�롣
//���ÿ�������ָ��ֱ�Ϊfast��slow,��ʼʱ��ָ������ͷhead��slowÿ����һ������slow=slow->next��fastÿ������������fast=fast->next->next������fast��slow�ߵÿ죬����л�����ôfastһ�����Ƚ��뻷����slow����뻷��������ָ�붼���뻷�󣬾������ɲ���������ָ�붨���ڻ��������������Ϳ����ж�һ�������Ƿ��л���
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
LNode *FindLoopStart(LinkList L) {
    LNode *fast = L, *slow = L;//���ÿ�������ָ��
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;//ÿ����һ��
        fast = fast->next->next;//ÿ��������
        if (slow == fast)//����
            break;
    }
    if (slow == NULL || fast->next == NULL)//û�л�������NULL
        return NULL;
    LNode *p1 = L, *p2 = slow;//�ֱ�ָ��ʼ�㡢������
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;//������ڵ�
}
//(3)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�
//��fast��slow����ʱ��slow�϶�û�б������������㷨��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)��


//��ָ Offer 22 https://leetcode.cn/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
//22.��2009ͳ�����⡿��֪һ�����б�ͷ���ĵ��������ṹΪdata link�����������ֻ������ͷָ��list���ڲ��ı������ǰ���£������һ�������ܸ�Ч���㷨�����������е�����k��λ���ϵĽ�㣨kΪ���������������ҳɹ����㷨����ý���data���ֵ��������1������ֻ����0��Ҫ��
//(1)�����㷨�Ļ������˼�롣
//��������ָ�����p��q����ʼʱ��ָ��ͷ������һ����㣨����ĵ�һ����㣩��pָ���������ƶ�����pָ���ƶ�����k�����ʱ��qָ�뿪ʼ��pָ��ͬ���ƶ�����Pָ���ƶ������һ�����ʱ��qָ����ָʾ���Ϊ������k����㡣���Ϲ��̶����������һ��ɨ�衣
//(2)�����㷨����ϸʵ�ֲ��衣
//(3)�������˼���ʵ�ֲ��裬���ó���������������㷨��ʹ��C��C++����ʵ�֣����ؼ�֮���������Ҫע�͡�
int Search_k(LinkList L, int k) {
    LNode *p = L->next, *q = L->next;
    int count = 0;
    while (p != NULL) {
        if (count < k)
            count++;
        else
            q = q->next;
        p = p->next;
    }
    if (count < k)
        return 0;
    else {
        printf("%d", q->data);
        return 1;
    }
}


//����160 https://leetcode.cn/problems/intersection-of-two-linked-lists/
//23.��2012ͳ�����⡿�ٶ����ô�ͷ���ĵ������浥�ʣ���������������ͬ�ĺ�׺ʱ���ɹ�����ͬ�ĺ�׺�洢�ռ䣬���磬��loading���͡�being���Ĵ洢ӳ������ͼ��ʾ����str1��str2�ֱ�ָ�������������ڵ������ͷ��㣬������ṹΪdata next�������һ��ʱ���Ͼ����ܸ�Ч���㷨���ҳ���str1��str2��ָ����������ͬ��׺����ʼλ�ã���ͼ���ַ�i���ڽ���λ��P����Ҫ��
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
int Listlen(LinkList L) {//Ĭ�ϴ�ͷ���
    int n = 0;
    L = L->next;
    while (L != NULL) {
        n++;
        L = L->next;
    }
    return n;
}

LNode *find_addr_1(LinkList str1, LinkList str2) {
    int str1len = Listlen(str1), str2len = Listlen(str2);
    LNode *p = str1->next, *q = str2->next;
    for (; str1len > str2len; str1len--)
        p = p->next;
    for (; str1len < str2len; str2len--)
        q = q->next;
    while (p != NULL && p != q) {
        p = p->next;
        q = q->next;
    }
    return p;
}

//�ⷨ2������160 https://leetcode.cn/problems/intersection-of-two-linked-lists/solution/xiang-jiao-lian-biao-by-leetcode-solutio-a8jn/
LNode *find_addr_2(LinkList str1, LinkList str2) {
    if (str1 == NULL || str2 == NULL)
        return NULL;
    LNode *p = str1->next, *q = str2->next;
    while (p != q) {
        p = p == NULL ? str2->next : p->next;//���ж�p�Ƿ�ΪNULL���ٽ�����Ŀ����������㣬����p��ֵ
        q = q == NULL ? str1->next : q->next;
    }
    return p;
}
//(3)˵����������㷨��ʱ�临�Ӷȡ�
//ʱ�临�Ӷ�ΪO(len1+len2)��O(max(len1,len2))������len1��len2�ֱ�Ϊ��������ĳ��ȡ�


//����83 https://leetcode.cn/problems/remove-duplicates-from-sorted-list/
//24.��2015ͳ�����⡿�õ�������m�����������ĽṹΪ[data][link]����|data|��n��nΪ������������Ҫ�����һ��ʱ�临�ӶȾ����ܸ�Ч���㷨������������data�ľ���ֵ��ȵĽ�㣬��������һ�γ��ֵĽ���ɾ���������ֵ��ȵĽ�㡣Ҫ��
//(1)�����㷨�Ļ������˼�롣
//(2)ʹ��C��C++���ԣ���������������������Ͷ��塣
//(3)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
void func(LinkList L, int n) {
    LNode *p = L, *r;
    int *q = (int *) malloc(sizeof(int) * (n + 1));
//    int q[n + 1] = {0};//����ʹ�ñ������峤��ʱ�������ڶ���ʱͬʱ���г�ʼ����ֵ����Ҫ��֮����и�ֵ
//    int q[n + 1];//������Ϊ��ȷ��д��
//    q[n + 1] = {0};
//    for (int i = 0; i < n + 1; i++)//�����ռ��ֵ��0
//        q[i] = 0;
    memset(q, 0, sizeof(int) * (n + 1));//���渨���ռ��ֵ��0Ҳ������memset
    while (p->next != NULL) {
        if (q[abs(p->next->data)] == 0) {
            q[abs(p->next->data)] = 1;
            p = p->next;
        } else {
            r = p->next;
            p->next = r->next;
            free(r);
        }
    }
    free(q);
}
//(4)˵����������㷨��ʱ�临�ӶȺͿռ临�Ӷȡ�
//�ο��������㷨��ʱ�临�Ӷ�ΪO(m)���ռ临�Ӷ�ΪO(n)��


//����143 https://leetcode.cn/problems/reorder-list/
//https://leetcode.cn/problems/reorder-list/solution/zhong-pai-lian-biao-by-leetcode-solution/
//25.��2019ͳ�����⡿�����Ա�L=(a1,a2,a3,��,an-2,an-1,an)���ô�ͷ���ĵ������棬�����еĽ�㶨�����£�
typedef struct node {
    int data;
    struct node *next;
} NODE;

//�����һ���ռ临�Ӷ�ΪO(1)��ʱ���Ͼ����ܸ�Ч���㷨����������L�еĸ���㣬�õ����Ա�L'=(a1,an,a2,an-1,a3,an-2,��)�� Ҫ��
//(1)�����㷨�Ļ������˼�롣
//(2)�������˼�룬����C��C++���������㷨���ؼ�֮������ע�͡�
void change_list(NODE *h) {
    NODE *p = h, *q = h, *r, *s;
    while (q->next != NULL) {
        p = p->next;
        q = q->next;
        if (q->next != NULL)
            q = q->next;
    }
    q = p->next;
    p->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }
    s = h->next;
    q = p->next;
    p->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = s->next;
        s->next = q;
        s = q->next;
        q = r;
    }
}
//(3)˵��������Ƶ��㷨��ʱ�临�Ӷȡ�
//��1�����м����ʱ�临�Ӷ�ΪO(n)����2�����õ�ʱ�临�Ӷ�ΪO(n)����3���ϲ������ʱ�临�Ӷ�ΪO(n)�����Ը��㷨��ʱ�临�Ӷ�ΪO(n)��


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
