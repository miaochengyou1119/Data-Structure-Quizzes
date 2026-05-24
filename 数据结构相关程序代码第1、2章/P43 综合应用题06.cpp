// 6.设C={a1,b1,a2,b2,...,an,bn}为线性表，采用带头结点的单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A={a1,a2,...,an},B={bn,...,b2,b1}。

#include<stdio.h>
#include<stdlib.h>

// 定义链表结点类型
typedef struct LNode {
	int data; // 数据域，这里以int为例，可根据需要修改
	struct LNode* next; // 指针域
}LNode,*LinkList;

LinkList DisCreat_2(LinkList& A) {
	LinkList B = (LinkList)malloc(sizeof(LNode)); // 创建B表表头
	B->next = NULL; // B表的初始化
	LNode* p = A->next, * q; // p为工作指针
	LNode* ra = A; // ra时钟指向A的尾结点
	while (p != NULL) {
		ra->next = p; ra = p; // 将*p链到A的表尾
		p = p->next;
		if (p != NULL) {
			q = p->next; // 头插后，*p将断链，因此用q记忆*p的后继
			p->next = B->next; // 将*p插入到B的前端
			B->next = p;
			p = q;
		}
	}
	ra->next = NULL; // A尾结点的next域置空
	return B;
}

// 辅助函数：创建带头结点的单链表（尾插法）
LinkList CreateList(int arr[], int n) {
	LinkList L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LNode* r = L; // 尾指针
	for (int i = 0; i < n; i++) {
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->data = arr[i];
		p->next = NULL;
		r->next = p;
		r = p;
	}
	return L;
}

// 辅助函数：打印链表
void PrintList(LinkList L, const char* name) {
	printf("%s：", name);
	LNode* p = L->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 主函数：测试拆分逻辑
int main() {
	// 测试用例：C={a1,b1,a2,b2,a3,b3,a4,b4}
	int testData[] = { 1,2,3,4,5,6,7,8 };
	int n = sizeof(testData) / sizeof(testData[0]);

	LinkList A = CreateList(testData, n);
	printf("原链表C：\n");
	PrintList(A, "C");

	LinkList B = DisCreat_2(A);
	printf("\n拆分后：\n");
	PrintList(A, "A"); // 应为{1,3,5,7}
	PrintList(B, "B"); // 应为{8,6,4,2}
	return 0;
}