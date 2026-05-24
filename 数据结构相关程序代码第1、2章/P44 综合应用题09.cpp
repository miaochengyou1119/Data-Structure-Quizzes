// 9.已知两个链表A和B分别表示两个集合，其元素递增排列。编制函数，求A与B的交集，并存放于A链表中。

#include<stdio.h>
#include<stdlib.h>

// 定义链表结点类型
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;

// 打印链表（用于测试）
void PrintList(LinkList L) {
	LNode* p = L->next;
	while (p) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 尾插法创建递增有序链表
LinkList CreateList(int a[], int n) {
	LinkList L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	LNode* r = L;
	for (int i = 0; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = NULL;
		r->next = s;
		r = s;
	}
	return L;
}

LinkList Union(LinkList& la, LinkList& lb) {
	LNode* pa = la->next; // 设工作指针分别为pa和pb
	LNode* pb = lb->next;
	LNode* u, * pc = la; // 结果表中当前合并结点的前驱指针pc
	while (pa && pb) {
		if (pa->data == pb->data) { // 交集并入结果表中
			pc->next = pa; // A中结点链接到结果表
			pc = pa;
			pa = pa->next;
			u = pb; // B中结点释放
			pb = pb->next;
			free(u);
		}
		else if (pa->data < pb->data) { // 若A中当前结点值小于B中当前结点值
			u = pa;
			pa = pa->next; // 后移指针
			free(u); // 释放A中当前结点
		}
		else { // 若B中当前结点值小于A中当前结点值
			u = pb;
			pb = pb->next; // 后移指针
			free(u); // 释放B中当前结点
		}
	} // while结束
	while (pa) { // B已遍历完，A未完
		u = pa;
		pa = pa->next;
		free(u); // 释放A中剩余结点
	}
	while (pb) { // A已遍历完，B未完
		u = pb;
		pb = pb->next;
		free(u); // 释放B中剩余结点
	}
	pc->next = NULL; // 置结果链表尾指针为NULL
	free(lb); // 释放B表的头结点
	return la;
}

int main() {
	int a[] = { 1,3,5,7,9 };
	int b[] = { 3,5,8,10 };
	int n1 = sizeof(a) / sizeof(a[0]);
	int n2 = sizeof(b) / sizeof(b[0]);

	LinkList A = CreateList(a, n1);
	LinkList B = CreateList(b, n2);

	printf("原链表A："); PrintList(A);
	printf("原链表B："); PrintList(B);

	LinkList C = Union(A, B);
	printf("交集链表："); PrintList(C);
	return 0;
}