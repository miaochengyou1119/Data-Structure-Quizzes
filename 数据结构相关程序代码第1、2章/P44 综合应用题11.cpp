// 11.设计一个算法用于判断带头结点的循环双链表是否对称。

#include<stdio.h>
#include<stdlib.h>

// 定义循环双链表结点类型（带头结点）
typedef struct DNode {
	int data; // 数据域
	struct DNode* prior; // 前驱指针
	struct DNode* next; // 后继指针
}DNode,*DLinkList;

// 初始化带头结点的循环双链表
bool InitDLinkList(DLinkList& L) {
	L=(DNode*)malloc(sizeof(DNode));
	if(L == NULL)return false; // 内存分配失败
	L->prior = L; // 头结点前驱指向自身
	L->next = L; // 头结点后继指向自身
	return true;
}

// 尾插法创建带头结点的循环双链表
void CreateDLinkList(DLinkList& L, int a[], int n) {
	if (!InitDLinkList(L))return;
	DNode* r = L; // 尾指针，初始指向头结点
	for (int i = 0; i < n; i++) {
		DNode* s = (DNode*)malloc(sizeof(DNode));
		s->data = a[i];
		// 双向链接
		s->prior = r;
		s->next = L; // 新结点后继指向头结点（循环）
		r->next = s;
		L->prior = s; // 头结点前驱指向新结点（循环）
		r = s; // 尾指针后移
	}
}

// 打印循环双链表（用于测试验证）
void PrintDLinkList(DLinkList L) {
	DNode* p = L->next; // 从第一个数据结点开始
	if (p == L) { // 空链表
		printf("链表为空\n");
		return;
	}
	while (p != L) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

int Symmetry(DLinkList L) {
	DNode* p = L->next, * q = L->prior; // 两头工作指针
	while (p != q && p->next != q) { // 循环跳出条件
		if (p->data == q->data) {
			p = p->next;
			q = q->prior;
		}
		else
			return 0; // 否则，返回0
	}
	return 1; // 比较结束后返回1
}

// 主函数：测试逻辑
int main() {
	// 测试用例1：对称的循环双链表
	int arr1[] = { 1,2,3,2,1 };
	int len1 = sizeof(arr1) / sizeof(arr1[0]);
	DLinkList L1;
	CreateDLinkList(L1, arr1, len1);
	printf("测试用例1（对称链表）：\n");
	printf("链表元素："); PrintDLinkList(L1);
	int res1 = Symmetry(L1);
	printf("链表是否对称：%s\n\n", res1 ? "是" : "否");

	// 测试用例2：不对称的循环双链表
	int arr2[] = { 1,2,3,4,5 };
	int len2 = sizeof(arr2) / sizeof(arr2[0]);
	DLinkList L2;
	CreateDLinkList(L2, arr2, len2);
	printf("测试用例2（不对称链表）：\n");
	printf("链表元素："); PrintDLinkList(L2);
	int res2 = Symmetry(L2);
	printf("链表是否对称：%s\n\n", res2 ? "是" : "否");
}