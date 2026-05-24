// 18.【2012统考真题】假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，可共享相同的后缀存储空间，例如，loading和being的存储映像共享相同的ing后缀存储空间。
// 设str1和str2分别指向两个单词所在单链表的头结点，链表结点结构为data-next，请设计一个时间上尽可能高效的算法，找出由str1和str2所指向两个链表共同后缀的起始位置（如图中字符i所在结点的位置p）。
// 要求：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
// (3)说明你所设计算法的时间复杂度。

// (1)算法的基本设计思想：
// ①分别求出str1和str2所指的两个链表的长度m和n。
// ②将两个链表以表尾对齐：令指针p、q分别指向str1和str2的头结点，若m≥n，则指针p先走，使p指向链表中的第m-n+1个结点；若m<n，则使q指向链表中的第n-m+1个结点，即使指针p和q所指的结点到表尾的长度相等。
// ③反复将指针p和q同步向后移动，并判断它们是否指向同一结点。当p、q指向同一结点，则该点即所求的共同后缀的起始地址。

// (2)本题代码如下：
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	char data;
	struct Node* next;
}SNode;
/*求链表长度的函数*/
int listlen(SNode* head) {
	int len = 0;
	while (head->next != NULL) {
		len++;
		head = head->next;
	}
	return len;
}
/*找出共同后缀的起始地址*/
SNode* find_list(SNode* str1, SNode* str2) {
	int m, n;
	SNode* p, * q;
	m = listlen(str1); // 求str1的长度，O(m)
	n = listlen(str2); // 求str2的长度，O(n)
	for (p = str1; m > n; m--) // 若m>n，使p指向链表中的第m-n+1个结点
		p = p->next;
	for (q = str2; m < n; n--) // 若m<n，使q指向链表中的第n-m+1个结点
		q = q->next;
	while (p->next != NULL && p->next != q->next) { // 查找共同后缀的起始地址
		p = p->next; // 两个指针同步向后移动
		q = q->next;
	}
	return p->next; // 返回共同后缀的起始地址
}

// 以下为辅助测试代码，可用于验证功能
SNode* createNode(char data) {
	SNode* node = (SNode*)malloc(sizeof(SNode));
	node->data = data;
	node->next = NULL;
	return node;
}

int main() {
	// 构造测试用例："loading"和"being"共享后缀"ing"
	SNode* common = createNode('i');
	common->next = createNode('n');
	common->next->next = createNode('g');

	SNode* str1 = createNode('h');
	str1->next = createNode('l');
	str1->next->next = createNode('o');
	str1->next->next->next = createNode('a');
	str1->next->next->next->next = common;

	SNode* str2 = createNode('b');
	str2->next = createNode('e');
	str2->next->next = common;

	SNode* result = find_list(str1, str2);
	if (result != NULL) {
		printf("共同后缀起始字符：%c\n", result->data); // 应输出'i'
	} else {
		printf("无共同后缀\n");
	}
	return 0;
}

// (3)时间复杂度为O(len1+len2)或O(max(len1,len2))，其中len1、len2分别为两个链表的长度。