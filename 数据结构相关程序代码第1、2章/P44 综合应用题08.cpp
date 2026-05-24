// 8.设A和B是两个单链表（带头结点），其中元素递增有序。
// 设计一个算法从A和B中的公共元素产生单链表C，要求不破坏A、B的结点。

#include<stdio.h>
#include<stdlib.h>

// 补充链表结点类型定义（与你的函数适配）
typedef struct LNode {
	int data; // 数据域（题目中为递增有序整数）
	struct LNode* next; // 指针域
}LNode,*LinkList;

void Get_Common(LinkList A, LinkList B,LinkList &C) {
	LNode* p = A->next, * q = B->next, * r, * s;
	C = (LinkList)malloc(sizeof(LNode)); // 建立表C
	r = C; // r始终指向C的尾结点
	while (p != NULL && q != NULL) { // 循环跳出条件
		if (p->data < q->data)
			p = p->next; // 若A的当前元素较小，后移指针
		else if (p->data > q->data)
			q = q->next; // 若B的当前元素较小，后移指针
		else { // 找到公共结点
			s = (LNode*)malloc(sizeof(LNode));
			s->data = p->data; // 复制产生结点*s
			r->next = s; // 将*s链接到C上（尾插法）
			r = s;
			p = p->next; // 表A和B继续向后扫描
			q = q->next;
		}
	}
	r->next = NULL; // 置C尾结点指针为空
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

// 辅助函数：打印链表内容（独立的打印逻辑，不侵入核心算法）
void PrintList(LinkList L, const char* name) {
	printf("%s：", name);
	LNode* p = L->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 主函数：测试提取公共元素的逻辑
int main() {
	// 测试用例：两个递增有序链表
	int dataA[] = { 2,5,7,10,15,20 }; // 链表A的元素
	int dataB[] = { 5,8,10,15,25 }; // 链表B的元素
	int nA = sizeof(dataA) / sizeof(dataA[0]);
	int nB = sizeof(dataB) / sizeof(dataB[0]);

	// 创建链表A和B
	LinkList A = CreateList(dataA, nA);
	LinkList B = CreateList(dataB, nB);
	LinkList C; // 用于接收公共元素链表

	// 打印原始链表
	PrintList(A, "链表A：");
	PrintList(B, "链表B：");

	// 调用你的提取公共元素函数
	Get_Common(A, B, C);

	// 外部打印链表C（打印逻辑完全独立）
	PrintList(C, "公共元素链表C：");
	return 0;
}