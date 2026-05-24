// 2.试编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设该结点唯一）。

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点类型
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;

LinkList Delete_Min(LinkList& L) {
	LNode* pre = L, * p = pre->next; // p为工作指针，pre指向其前驱
	LNode* minpre = pre, * minp = p; // 保存最小值结点及其前驱
	while (p != NULL) {
		if (p->data < minp->data) {
			minp = p; // 找到比之前找到的最小值结点更小的结点
			minpre = pre;
		}
		pre = p; // 继续扫描下一个结点
		p = p->next;
	}
	minpre->next = minp->next; // 删除最小值结点
	free(minp);
	return L;
}

// 尾插法创建带头结点的单链表
LinkList CreateList(int a[], int n) {
	LinkList L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	LNode* r = L; // 尾指针
	for (int i = 0; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = NULL;
		r->next = s;
		r = s;
	}
	return L;
}

// 打印单链表
void PrintList(LinkList L) {
	LNode* p = L->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

int main() {
	int arr[] = { 5,2,8,1,9,3 };
	int n = sizeof(arr) / sizeof(arr[0]);

	LinkList L = CreateList(arr, n);
	printf("原链表：");
	PrintList(L);

	L = Delete_Min(L);
	printf("删除最小值后：");
	PrintList(L);
	return 0;
}