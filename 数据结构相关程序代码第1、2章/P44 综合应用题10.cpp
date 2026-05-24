// 10.两个整数序列A=a1,a2,...,am和B=b1,b2,...,bn已经存入两个单链表中，设计一个算法，判断序列B是否是序列A的连续子序列。

#include<stdio.h>
#include<stdlib.h>

// 定义链表结点类型（题目假定A和B均无头结点）
typedef struct LNode {
	int data; // 结点数据域
	struct LNode* next; // 结点指针域
}LNode,*LinkList;

// 尾插法创建无头结点的链表（适配题目要求）
LinkList CreateListWithoutHead(int a[], int n) {
	if (n == 0)return NULL; // 空序列返回NULL

	// 创建第一个结点（无头结点，第一个结点就是数据结点）
	LinkList head = (LNode*)malloc(sizeof(LNode));
	head->data = a[0];
	head->next = NULL;
	LNode* r = head; // 尾指针

	// 依次插入后续结点
	for (int i = 1; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = NULL;
		r->next = s;
		r = s;
	}
	return head;
}

// 打印无头结点的链表（用于测试验证）
void PrintListWithoutHead(LinkList L) {
	LNode* p = L;
	if (p == NULL) {
		printf("链表为空\n");
		return;
	}
	while (p) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

int Pattern(LinkList A, LinkList B) {
	LNode* p = A; // p为A链表的工作指针，本题假定A和B均无头结点
	LNode* pre = p; // pre记住每趟比较中A链表的开始结点
	LNode* q = B; // q是B链表的工作指针
	while (p && q)
		if (p->data == q->data) { // 结点值相同
			p = p->next;
			q = q->next;
		}
		else {
			pre = pre->next;
			p = pre; // A链表新的开始比较结点
			q = B; // q从B链表第一个结点开始
		}
	if (q == NULL) // B已经比较结束
		return 1; // 说明B是A的子序列
	else
		return 0; // B不是A的子序列
}

// 主函数：测试逻辑
int main() {
	// 测试用例1：B是A的连续子序列
	int arrA1[] = { 1,2,3,4,5,6 };
	int arrB1[] = { 3,4,5 };
	int lenA1 = sizeof(arrA1) / sizeof(arrA1[0]);
	int lenB1 = sizeof(arrB1) / sizeof(arrB1[0]);
	LinkList A1 = CreateListWithoutHead(arrA1, lenA1);
	LinkList B1 = CreateListWithoutHead(arrB1, lenB1);

	printf("测试用例1：\n");
	printf("链表A："); PrintListWithoutHead(A1);
	printf("链表B："); PrintListWithoutHead(B1);
	int res1 = Pattern(A1, B1);
	printf("B是否是A的连续子序列：%s\n\n", res1 ? "是" : "否");

	// 测试用例2：B不是A的连续子序列
	int arrA2[] = { 1,2,3,4,5,6 };
	int arrB2[] = { 3,5 };
	int lenA2 = sizeof(arrA2) / sizeof(arrA2[0]);
	int lenB2 = sizeof(arrB2) / sizeof(arrB2[0]);
	LinkList A2 = CreateListWithoutHead(arrA2, lenA2);
	LinkList B2 = CreateListWithoutHead(arrB2, lenB2);

	printf("测试用例2：\n");
	printf("链表A："); PrintListWithoutHead(A2);
	printf("链表B："); PrintListWithoutHead(B2);
	int res2 = Pattern(A2, B2);
	printf("B是否是A的连续子序列：%s\n\n", res2 ? "是" : "否");

	return 0;
}