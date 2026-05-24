// 16.设有一个长度n（n为偶数）的不带头结点的单链表，且结点值都大于0，设计算法求这个单链表的最大孪生和。
// 孪生和定义为一个结点值与其孪生结点值之和，对于第i个结点（从0开始），其孪生结点为第n-i-1个结点。
// 要求：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
// (3)说明你的算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想：
// 设置快、慢两个指针分别为fast和slow，初始时slow指向L（第一个结点），fast指向L->next（第二个结点），之后slow每次走一步，fast每次走两步。
// 当fast指向表尾（第n个结点）时，slow正好指向链表的中间点（第n/2个结点），即slow正好指向链表前半部分的最后一个结点。
// 将链表的后半部分逆置，然后设置两个指针分别指向链表前半部分和后半部分的首结点，在遍历过程中计算两个指针所指结点的元素之和，并维护最大值。

// (2)本题代码如下：

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点类型（无头结点）
typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;

// 尾插法创建无头结点单链表
LinkList CreateList(int a[], int n) {
	if (n == 0)return NULL;
	LinkList head = (LNode*)malloc(sizeof(LNode));
	head->data = a[0];
	head->next = NULL;
	LNode* r = head;
	for (int i = 1; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = NULL;
		r->next = s;
		r = s;
	}
	return head;
}

// 打印无头结点单链表（用于测试）
void PrintList(LinkList L) {
	LNode* p = L;
	while (p) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

int PairSum(LinkList L) {
	LNode* fast = L->next, * slow = L; // 利用快慢双指针找到链表的中间点
	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next; // 快指针每次走两步
		slow = slow->next; // 慢指针每次走一步
	}
	LNode* newHead = NULL, * p = slow->next, * tmp;
	while (p != NULL) { // 反转链表后一半部分的元素，采用头插法
		tmp = p->next; // p指向当前待插入结点，令tmp指向其下一结点
		p->next = newHead; // 将p所指结点插入到新链表的首结点之前
		newHead = p; // newHead指向刚才新插入的结点，作为新的首结点
		p = tmp; // 当前待处理结点变为下一结点
	}
	int mx = 0; p = L;
	LNode* q = newHead;
	while (q != NULL) { // 用p和q分别遍历两个链表
		if (p->data + q->data > mx) // 用mx记录最大值
			mx = p->data + q->data;
		p = p->next;
		q = q->next;
	}
	return mx;
}

// 主函数：测试逻辑
int main() {
	// 测试用例：链表长度为偶数，结点值都大于0
	int arr[] = { 5,4,3,2,1,6 }; // 孪生和为5+6=11,4+1=5,3+2=5，最大孪生和为11
	int n = sizeof(arr) / sizeof(arr[0]);
	LinkList L = CreateList(arr, n);

	printf("原链表：");
	PrintList(L);

	int maxSum = PairSum(L);
	printf("最大孪生和为：%d\n", maxSum);
	return 0;
}

// (3)本算法的时间复杂度为O(n)，空间复杂度为O(1)。