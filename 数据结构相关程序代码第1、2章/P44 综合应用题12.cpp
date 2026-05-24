// 12.有两个循环单链表，链表头指针分别为h1和h2，编写一个函数将链表h2链接到链表h1之后，要求链接后的链表仍保持循环链表形式。

#include<stdio.h>
#include<stdlib.h>

// 定义循环单链表结点类型
typedef struct LNode {
	int data; // 数据域
	struct LNode* next; // 后继指针
}LNode,*LinkList;

// 初始化循环单链表（无头结点，第一个结点就是表头）
bool InitCircleList(LinkList& L) {
	L = NULL; // 空循环链表初始化为NULL
	return true;
}

// 尾插法创建循环单链表（无头结点）
void CreateCircleList(LinkList& L, int a[], int n) {
	if (n == 0)return;
	// 创建第一个结点（表头）
	L = (LNode*)malloc(sizeof(LNode));
	L->data = a[0];
	LNode* r = L; // 尾指针

	// 插入后续结点
	for (int i = 1; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = L; // 尾结点指向表头，形成循环
}

// 打印循环单链表（用于测试验证）
void PrintCircleList(LinkList L) {
	if (L == NULL) { // 空链表
		printf("链表为空\n");
		return;
	}
	LNode* p = L;
	do {
		printf("%d", p->data);
		p = p->next;
	} while (p != L); // 循环到表头结束
	printf("\n");
}

LinkList Link(LinkList& h1, LinkList& h2) {
// 将循环链表h2链接到循环链表h1之后，使之仍保持循环链表的形式
	LNode* p, * q; // 分别指向两个链表的尾结点
	p = h1;
	while (p->next != h1) // 寻找h1的尾结点
		p = p->next;
	q = h2;
	while (q->next != h2) // 寻找h2的尾结点
		q = q->next;
	p->next = h2; // 将h2链接到h1之后
	q->next = h1; // 令h2的尾结点指向h1
	return h1;
}

int main() {
	// 测试用例：创建两个循环单链表
	int arr1[] = { 1,2,3 }; // h1的元素
	int arr2[] = { 4,5,6 }; // h2的元素
	int len1 = sizeof(arr1) / sizeof(arr1[0]);
	int len2 = sizeof(arr2) / sizeof(arr2[0]);

	LinkList h1, h2;
	InitCircleList(h1);
	InitCircleList(h2);
	CreateCircleList(h1, arr1, len1);
	CreateCircleList(h2, arr2, len2);

	// 打印链接前的链表
	printf("链接前-循环链表h1："); PrintCircleList(h1);
	printf("链接前-循环链表h2："); PrintCircleList(h2);

	// 调用链接函数
	LinkList h = Link(h1, h2);

	// 打印链接后的链表
	printf("链接后-新循环链表："); PrintCircleList(h);
	return 0;
}