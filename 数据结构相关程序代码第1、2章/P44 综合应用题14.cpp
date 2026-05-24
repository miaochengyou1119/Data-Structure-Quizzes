// 14.设将n(n>1)个整数存放到不带头结点的单链表L中，设计算法将L中保存的序列循环右移k(0<k<n)个位置。
// 例如，若k=1，则将链表{0,1,2,3}变为{3,0,1,2}。
// 要求：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想：
// 首先，遍历链表计算表长n，并找到链表的尾结点，将其与首结点相连，得到一个循环单链表。
// 然后，找到新链表的尾结点，它为原链表的第n-k个结点，令L指向新链表尾结点的下一个结点，并将环断开，得到新链表。

// (2)本题代码如下：

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点类型（无头结点）
typedef struct LNode {
	int data; // 数据域
	struct LNode* next; // 后继指针
}LNode;

// 尾插法创建无头结点的单链表
LNode* CreateList(int a[], int n) {
	if (n == 0)return NULL; // 空链表返回NULL

	// 创建第一个结点（无头结点，直接作为表头）
	LNode* head = (LNode*)malloc(sizeof(LNode));
	head->data = a[0];
	head->next = NULL;
	LNode* r = head; // 尾指针

	// 插入后续结点
	for (int i = 1; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = NULL;
		r->next = s;
		r = s;
	}
	return head;
}

// 打印无头结点的单链表（用于测试验证）
void PrintList(LNode* L) {
	if (L == NULL) {
		printf("链表为空\n");
		return;
	}
	LNode* p = L;
	while (p) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

LNode* Converse(LNode* L, int k) {
	int n = 1; // n用来保存链表的长度
	LNode* p = L; // p为工作指针
	while (p->next != NULL) { // 计算链表的长度
		p = p->next;
		n++;
	} // 循环执行后，p指向链表尾结点
	p->next = L; // 将链表连成一个环
	for (int i = 1; i <= n - k; i++)// 寻找链表的第n-k个结点
		p = p->next;
	L = p->next; // 令L指向新链表尾结点的下一个结点
	p->next = NULL; // 将环断开
	return L;
}

// 主函数：测试逻辑
int main() {
	// 测试用例：原链表[0,1,2,3]，右移k=1个位置
	int arr[] = { 0,1,2,3 };
	int len = sizeof(arr) / sizeof(arr[0]);
	int k = 1; // 右移1个位置

	// 创建原链表并打印
	LNode* L = CreateList(arr, len);
	printf("原链表：");
	PrintList(L);

	// 调用右移函数
	LNode* newL = Converse(L, k);

	// 打印右移后的链表
	printf("右移%d个位置后：", k);
	PrintList(newL);

	// 额外测试：右移k=2个位置（基于原链表[0,1,2,3]）
	L = CreateList(arr, len); // 重新创建原链表
	k = 2;
	newL = Converse(L, k);
	printf("右移%d个位置后：", k);
	PrintList(newL);
	return 0;
}

// (3)本算法的时间复杂度为0(n)，空间复杂度为O(1)。