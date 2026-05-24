// 13.设有一个带头结点的非循环双链表L，其每个结点中除有pre、data和next域外，还有一个访问频度域freq，其值均初始化为零。
// 每当在链表中进行一次Locate(L,x)运算时，令值为x的结点中freq域的值增1，并使此链表中的结点保持按访问频度递减的顺序排列，且最近访问的结点排在频度相同的结点之前，以便使频繁访问的结点总是靠近表头。
// 试编写符合上述要求的Locate(L,x)函数，返回找到结点的地址，类型为指针型。

#include<stdio.h>
#include<stdlib.h>

// 定义ElemType类型（适配题目中的参数类型）
typedef int ElemType;

// 定义双链表结点类型（包含访问频度域freq）
typedef struct DNode {
	ElemType data; // 数据域
	int freq; // 访问频度域，初始为0
	struct DNode* pre; // 前驱指针
	struct DNode* next; // 后继指针
}DNode,*DLinkList;

// 初始化带头结点的非循环双链表
bool InitDLinkList(DLinkList& L) {
	L = (DNode*)malloc(sizeof(DNode));
	if (L == NULL)return false; // 内存分配失败
	L->pre = NULL; // 头结点前驱为NULL（非循环）
	L->next = NULL; // 头结点后继为NULL
	L->freq = 0; // 头结点freq无意义，初始化为0
	return true;
}

// 尾插法创建带头结点的非循环双链表（初始化freq为0）
void CreateDLinkList(DLinkList& L, ElemType a[], int n) {
	if (!InitDLinkList(L))return;
	DNode* r = L; // 尾指针，初始指向头结点
	for (int i = 0; i < n; i++) {
		DNode* s = (DNode*)malloc(sizeof(DNode));
		s->data = a[i];
		s->freq = 0; // 访问频度初始化为0
		s->pre = r; // 新结点前驱指向尾结点
		s->next = NULL; // 新结点后继为NULL（非循环）
		r->next = s; // 尾结点后继指向新结点
		r = s; // 尾指针后移
	}
}

// 打印双链表（包含freq值，用于验证排序效果）
void PrintDLinkList(DLinkList L) {
	DNode* p = L->next;
	if (p == NULL) {
		printf("链表为空\n");
		return;
	}
	while (p) {
		printf("data=%d,freq=%d", p->data, p->freq);
		p = p->next;
	}
	printf("\n");
}

DLinkList Locate(DLinkList& L, ElemType x) {
	DNode* p = L->next, * q; // p为工作指针，q为p的前驱，用于查找插入位置
	while (p && p->data != x)
		p = p->next; // 查找值为x的结点
	if (!p)
		exit(0); // 不存在值为x的结点
	else {
		p->freq++; // 令元素值为x的结点的freq值加1
		if (p->pre == L || p->pre->freq > p->freq)
			return p; // p是链表首结点，或freq值小于前驱
		if (p->next != NULL)p->next->pre = p->pre;
		p->pre->next = p->next; // 将p结点从链表上摘下
		q = p->pre; // 以下查找p结点的插入位置
		while (q != L && q->freq <= p->freq)
			q = q->pre;
		p->next = q->next;
		if (q->next != NULL)q->next->pre = p; // 将p结点排在同频率的第一个
		p->pre = q;
		q->next = p;
	}
	return p; // 返回值为x的结点的指针
}

// 主函数：测试逻辑
int main() {
	// 创建初始链表：1 2 3 4 5（所有结点freq初始为0）
	ElemType arr[] = { 1,2,3,4,5 };
	int len = sizeof(arr) / sizeof(arr[0]);
	DLinkList L;
	CreateDLinkList(L, arr, len);

	printf("初始链表：");
	PrintDLinkList(L);

	// 测试多次查找，验证频率排序效果
	printf("\n第1次查找值为3的结点：\n");
	Locate(L, 3);
	PrintDLinkList(L);

	printf("\n第1次查找值为2的结点：\n");
	Locate(L, 2);
	PrintDLinkList(L);

	printf("\n第2次查找值为3的结点（freq变为2）：\n");
	Locate(L, 3);
	PrintDLinkList(L);

	printf("\n第1次查找值为4的结点：\n");
	Locate(L, 4);
	PrintDLinkList(L);
	return 0;
}