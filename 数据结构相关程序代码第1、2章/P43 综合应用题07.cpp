// 7.在一个递增有序的单链表中，存在重复的元素，设计算法删除重复的元素，例如(7,10,10,21,30,42,42,42,51,70)将变为(7,10,21,30,42,51,70)。

#include<stdio.h>
#include<stdlib.h>

// 补充链表结点类型定义（与你的函数适配）
typedef struct LNode {
	int data; // 数据域（题目示例为整数）
	struct LNode* next; // 指针域
}LNode,*LinkList;

void Del_Same(LinkList& L) {
	LNode* p = L->next, * q; // p为扫描工作指针
	if (p == NULL)
		return;
	while (p->next != NULL) {
		q = p->next; // q指向*p的后继结点
		if (p->data == q->data) { // 找到重复值的结点
			p->next = q->next; // 释放*q结点
			free(q); // 释放相同元素值的结点
		}
		else
			p = p->next;
	}
}

// 辅助函数：创建带头结点的递增有序单链表（尾插法）
LinkList CreateList(int arr[], int n) {
	LinkList L = (LinkList)malloc(sizeof(LNode)); // 创建头结点
	L->next = NULL;
	LNode* r = L; // 尾指针，始终指向链表最后一个结点
	for (int i = 0; i < n; i++) {
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->data = arr[i];
		p->next = NULL;
		r->next = p;
		r = p; // 尾指针后移
	}
	return L;
}

// 辅助函数：打印链表内容（便于验证结果）
void PrintList(LinkList L, const char* name) {
	printf("%s：", name);
	LNode* p = L->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 主函数：测试删除重复元素的逻辑
int main() {
	// 题目示例测试用例：包含重复元素的递增有序数组
	int testData[] = { 7,10,10,21,30,42,42,42,51,70 };
	int n = sizeof(testData) / sizeof(testData[0]);

	// 创建链表并打印原始数据
	LinkList L = CreateList(testData, n);
	PrintList(L, "删除前的链表");

	// 调用你的删除重复元素函数
	Del_Same(L);

	// 打印删除后的结果（验证是否符合题目要求）
	PrintList(L, "删除后的链表");
	return 0;
}