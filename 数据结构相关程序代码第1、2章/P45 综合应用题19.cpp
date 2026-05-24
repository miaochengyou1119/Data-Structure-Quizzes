// 19.【2015统考真题】用单链表保存m个整数，结点的结构为[data][link] ，且|data|≤n（n为正整数）。
// 现要求设计一个时间上尽可能高效的算法，对于链表中data的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。
// 例如，若给定的单链表head如下：head->21->-15->-15->-7->15^。
// 则删除结点后的head为head->21->-15->-7。
// 要求：
// (1)给出算法的基本设计思想。
// (2)使用C或C++语言，给出单链表结点的数据类型定义。
// (3)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
// (4)说明你所设计算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想：
// ·算法的核心思想是用空间换时间。使用辅助数组记录链表中已出现的数值，从而只需对链表进行一趟扫描。
// ·因为|data|≤n，故辅助数组q的大小n+1，各元素的初值均为0.
// 依次扫描链表中的各结点，同时检查q[|data|]的值，若为0则保留该结点，并令q[|data|]=1；否则将该结点从链表中删除。

// (2)使用C语言描述的单链表结点的数据类型定义：

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node* link;
}NODE;
typedef NODE* PNODE;

// (3)算法实现如下：

void func(PNODE h, int n) {
	PNODE p = h, r;
	int* q, m;
	q = (int*)malloc(sizeof(int) * (n + 1)); // 申请n+1个位置的辅助空间
	for (int i = 0; i < n+1; i++) // 数组元素初值置0
		*(q + i) = 0;
	while (p->link != NULL) {
		m = p->link->data > 0 ? p->link->data : -p->link->data;
		if (*(q + m) == 0) { // 判断该结点的data是否已出现过
			*(q + m) = 1; // 首次出现
			p = p->link; // 保留
		}
		else { // 重复出现
			r = p->link; // 删除
			p->link = r->link;
			free(r);
		}
	}
	free(q);
}

// 以下为辅助函数，用于创建链表、打印链表等，方便测试
PNODE createList(int arr[], int len) {
	PNODE head = (PNODE)malloc(sizeof(NODE));
	head->link = NULL;
	PNODE tail = head;
	for (int i = 0; i < len; i++) {
		PNODE newNode = (PNODE)malloc(sizeof(NODE));
		newNode->data = arr[i];
		newNode->link = NULL;
		tail->link = newNode;
		tail = newNode;
	}
	return head;
}

void printList(PNODE head) {
	PNODE p = head->link;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("NULL\n");
}

int main() {
	int arr[] = { 21,-15,-15,-7,15 };
	int n = 21; // 题目中|data|<=n
	PNODE head = createList(arr, 5);

	printf("原链表：");
	printList(head);

	func(head, n);

	printf("处理后链表：");
	printList(head);
	return 0;
}

// (4)算法的时间复杂度为O(m)，空间复杂度为O(n)。