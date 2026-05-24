// 1.在带头结点的单链表L中，删除所有值为x的结点，并释放其空间，假设值为x的结点不唯一，试编写算法以实现以上操作。

// 解法2：采用尾插法建立单链表。用p指针扫描L的所有结点，当其值不为x时，将其链接到L之后，否则将其释放。

#include<stdio.h>
#include<stdlib.h>

// 定义链表结点类型（统一数据类型和结构体）
typedef int ElemType; // 链表存储整型数据，可按需修改
typedef struct LNode {
	ElemType data; // 数据域
	struct LNode* next; // 指针域
}LNode,*LinkList;

void Del_x_2(LinkList& L, ElemType x) {
	LNode* p = L->next, * r = L, * q; // r指向尾结点，其初值为头结点
	while (p != NULL) {
		if (p->data != x) { // *p结点值不为x时将其链接到L尾部
			r->next = p;
			r = p;
			p = p->next; // 继续扫描
		}
		else { // *p结点值为x时将其释放
			q = p;
			p = p->next; // 继续扫描
			free(q); //释放空间
		}
	} // while
	r->next = NULL; // 插入结束后置尾结点指针为NULL
}

// 尾插法创建带头结点的单链表（用于生成测试链表）
void CreateList_Tail(LinkList& L, ElemType a[], int n) {
	L = (LinkList)malloc(sizeof(LNode)); // 创建头结点
	L->next = NULL;
	LNode* r = L; // r指向尾结点，初始指向头结点
	for (int i = 0; i < n; i++) {
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->data = a[i];
		p->next = NULL;
		r->next = p; // 新结点插入到尾结点后
		r = p; // 更新尾结点
	}
}

// 打印链表元素（直观查看删除前后效果）
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

// 主函数：测试解法2的删除功能
int main() {
	LinkList L;
	// 测试用例：创建包含重复值的链表[1,5,3,5,4,5,6]
	ElemType arr[] = { 1,5,3,5,4,5,6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// 创建链表并打印删除前状态
	CreateList_Tail(L, arr, n);
	printf("删除前：");
	PrintList(L);

	// 调用解法2，删除所有值为5的结点
	ElemType x = 5;
	Del_x_2(L, x);
	printf("删除所有值为%d的结点后：", x);
	PrintList(L);
	return 0;
}