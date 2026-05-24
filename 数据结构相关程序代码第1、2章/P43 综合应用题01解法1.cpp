// 1.在带头结点的单链表L中，删除所有值为x的结点，并释放其空间，假设值为x的结点不唯一，试编写算法以实现以上操作。

// 解法1：用p从头至尾扫描单链表，pre指向*p结点的前驱，若p所指结点的值为x，则删除，并让p移向下一个结点，否则让pre、p指针同步后移一个结点。

#include<stdio.h>
#include<stdlib.h>

// 定义链表结点类型
typedef int ElemType; // 假设链表存储的是整型数据
typedef struct LNode {
	ElemType data; // 数据域
	struct LNode* next; // 指针域
}LNode,*LinkList;

void Del_x_1(LinkList& L, ElemType x) {
	LNode* p = L->next, * pre = L, * q; // 置p和pre的初始值
	while (p != NULL) {
		if (p->data == x) {
			q = p;
			p = p->next;
			pre->next = p;
			free(q);
		}
		else {
			pre = p;
			p = p->next;
		} // else
	} // while
}

// 尾插法创建带头结点的单链表（用于测试）
void CreateList_Tail(LinkList& L, ElemType a[], int n) {
	L = (LinkList)malloc(sizeof(LNode)); // 创建头结点
	L->next = NULL;
	LNode* r = L; // r指向尾结点，初始时指向头结点
	for (int i = 0; i < n; i++) {
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->data = a[i];
		p->next = NULL;
		r->next = p; // 将新结点插入到尾结点之后
		r = p; // 更新尾结点
	}
}

// 打印链表中的所有元素（用于测试）
void PrintList(LinkList L) {
	LNode* p = L->next; // 跳过头结点，从第一个数据结点开始
	if (p == NULL) {
		printf("链表为空！\n");
		return;
	}
	printf("链表元素：");
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 主函数（测试删除功能）
int main() {
	LinkList L;
	// 测试用例：创建包含多个重复值的链表[1,2,3,2,4,2,5]
	ElemType arr[] = { 1,2,3,2,4,2,5 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// 创建链表并打印初始状态
	CreateList_Tail(L, arr, n);
	printf("删除前：");
	PrintList(L);

	// 删除所有值为2的结点
	ElemType x = 2;
	Del_x_1(L, x);
	printf("删除所有值为%d的结点后：", x);
	PrintList(L);
	return 0;
}