// 15.单链表有环，是指单链表的最后一个结点的指针指向了链表中的某个结点（通常单链表的最后一个结点的指针域是空的）。
// 试编写算法判断单链表是否存在环。
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或者C++语言描述算法，关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想：
// 设置快慢两个指针分别为fast和slow最初都指向链表头head。slow每次走一步，即slow=slow->next；fast每次走两步，即fast=fast->next->next。
// fast比slow走得快，若有环，则fast一定先进入环，而slow后进入环。两个指针都进入环后，经过若干操作后两个指针定能在环上相遇。
// 这样就可以判断一个链表是否有环。
// 当slow刚进入环时，fast早已进入环。因为fast每次比slow多走一步且fast与slow的距离小于环的长度，所以fast与slow相遇时，slow所走的距离不超过环的长度。
// 设头结点到环的入口点的距离为a，环的入口点沿着环的方向到相遇点的距离为x，环长为r，相遇时fast绕过了n圈。
// 则有2(a+x)=a+n*r+x，即a=nr-x。
// 显然从头结点到环的入口点的距离等于n倍的环长减去环的入口点到相遇点的距离。
// 因此可设置两个指针，一个指向head，另一个指向相遇点，两个指针同步移动（均为一次走一步），相遇点即环的入口点。

// (2)本题代码如下：

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点类型
typedef struct LNode {
	int data; // 数据域
	struct LNode* next; // 后继指针
}LNode;

// 创建单环单链表（用于测试）
// 参数说明：arr为结点数据，n为总结点数，loopPos为环入口点的位置（从0开始计数）
LNode* CreateLoopList(int arr[], int n, int loopPos) {
	if (n <= 0 || loopPos >= n)return NULL;

	// 创建头结点（链表第一个结点）
	LNode* head = (LNode*)malloc(sizeof(LNode));
	head->data = arr[0];
	LNode* p = head;
	LNode* loopNode = NULL; // 保存环入口结点

	// 创建后续结点
	for (int i = 1; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = arr[i];
		p->next = s;
		p = s;
		// 标记环入口结点
		if (i == loopPos)loopNode = s;
	}

	// 若loopPos为0，环入口是头结点
	if (loopPos == 0)loopNode = head;

	// 将尾结点指向环入口结点，形成环
	p->next = loopNode;

	return head;
}

// 创建无环单链表（用于测试）
LNode* CreateNormalList(int arr[], int n) {
	if (n <= 0)return NULL;

	LNode* head = (LNode*)malloc(sizeof(LNode));
	head->data = arr[0];
	LNode* p = head;

	for (int i = 1; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = arr[i];
		p->next = s;
		p = s;
	}
	p->next = NULL; // 尾结点next为NULL，无环

	return head;
}

LNode* FindLoopStart(LNode* head) {
	LNode* fast = head, * slow = head; // 设置快慢两个指针
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next; // 每次走一步
		fast = fast->next->next; // 每次走两步
		if (slow == fast)break; // 相遇
	}
	if (fast == NULL || fast->next == NULL)
		return NULL; // 没有环，返回NULL
	LNode* p1 = head, * p2 = slow; // 分别指向开始点、相遇点
	while (p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1; // 返回入口点
}

// 主函数：测试逻辑
int main() {
	// 测试用例1：带环链表（数据：1,2,3,4,5；环入口为第3个结点，数据为4）
	int arr1[] = { 1,2,3,4,5 };
	int n1 = sizeof(arr1) / sizeof(arr1[0]);
	LNode* loopHead = CreateLoopList(arr1, n1, 3); // loopPos=3（索引从0开始）
	LNode* loopStart = FindLoopStart(loopHead);
	if (loopStart) {
		printf("带环链表测试：找到环入口点，数据为%d\n", loopStart->data);
	} else {
		printf("带环链表测试：未找到环（错误）\n");
	}

	// 测试用例2：无环链表（数据：1,2,3,4,5）
	int arr2[] = { 1,2,3,4,5 };
	int n2 = sizeof(arr2) / sizeof(arr2[0]);
	LNode* normalHead = CreateNormalList(arr2, n2);
	LNode* normalStart = FindLoopStart(normalHead);
	if (normalStart) {
		printf("无环链表测试：错误识别出环，入口点数据为%d\n", normalStart->data);
	} else {
		printf("无环链表测试：未找到环（正确）\n");
	}
	return 0;
}

// (3)当fast与slow相遇时，slow肯定没有遍历完链表，故算法的时间复杂度为O(n)，空间复杂度为O(1)。