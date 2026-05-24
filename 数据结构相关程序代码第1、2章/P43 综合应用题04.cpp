// 4.设在一个带表头结点的单链表中，所有结点的元素值无序，试编写一个函数，删除表中所有处于给定的两个值（作为函数参数给出）之间的元素（若存在）。

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点类型
typedef struct LNode {
	int data;
	struct LNode* link;
}LNode,*LinkList;

void RangeDelete(LinkList& L, int min, int max) {
	LNode* pr = L, * p = L->link; // p是检测指针，pr是其前驱
	while(p!=NULL)
		if (p->data > min && p->data < max) { // 寻找到被删结点，删除
			pr->link = p->link;
			free(p);
			p = pr->link;
		}
		else { // 否则继续寻找被删结点
			pr = p;
			p = p->link;
		}
}

// 辅助函数：创建带头结点的单链表
LinkList CreateList(int arr[], int n) {
	LinkList L = (LNode*)malloc(sizeof(LNode));
	L->link = NULL;
	LNode* tail = L;
	for (int i = 0; i < n; i++) {
		LNode* newNode = (LNode*)malloc(sizeof(LNode));
		newNode->data = arr[i];
		newNode->link = NULL;
		tail->link = newNode;
		tail = newNode;
	}
	return L;
}

// 辅助函数：打印单链表
void PrintList(LinkList L) {
	LNode* p = L->link;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->link;
	}
	printf("\n");
}

// 主函数：测试
int main() {
	int arr[] = { 1,5,3,8,2,7,4 };
	int n = sizeof(arr) / sizeof(arr[0]);
	LinkList L = CreateList(arr, n);

	printf("原链表：");
	PrintList(L);

	int min = 2, max = 7;
	RangeDelete(L, min, max);

	printf("删除区间（%d，%d）内元素后的链表：", min, max);
	PrintList(L);
	return 0;
}