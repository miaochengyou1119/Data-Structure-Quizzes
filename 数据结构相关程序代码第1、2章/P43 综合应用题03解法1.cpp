// 3.试编写算法将带头结点的单链表就地逆置，所谓“就地”是指辅助空间复杂度为O(1)。

// 解法1：将头结点摘下，然后从第一结点开始，依次插入到头结点的后面（头插法建立单链表），直到最后一个节点为止，实现链表逆置。

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点类型
typedef struct LNode {
	int data; // 数据域
	struct LNode* next; // 指针域
}LNode,*LinkList;

LinkList Reverse_1(LinkList L) {
	LNode* p, * r; // p为工作指针，r为p的后继，以防断链
	p = L->next; // 从第一个元素结点开始
	L->next = NULL; // 先将头结点L的next域置为NULL
	while (p != NULL) { // 依次将元素结点摘下
		r = p->next; // 暂存p的后继
		p->next = L->next; // 将p结点插入到头结点之后
		L->next = p;
		p = r;
	}
	return L;
}

// 辅助函数：创建一个带头结点的单链表
LinkList CreateList() {
	LinkList L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	LNode* p, * tail = L;
	int x;
	printf("请输入链表元素（以-1结束）：");
	while (scanf_s("%d", &x) && x != -1) {
		p = (LNode*)malloc(sizeof(LNode));
		p->data = x;
		p->next = NULL;
		tail->next = p;
		tail = p;
	}
	return L;
}

// 辅助函数：遍历打印单链表
void PrintList(LinkList L) {
	LNode* p = L->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 主函数：测试逆置功能
int main() {
	LinkList L = CreateList();
	printf("原链表：");
	PrintList(L);

	L = Reverse_1(L);
	printf("逆置后链表：");
	PrintList(L);
	return 0;
}