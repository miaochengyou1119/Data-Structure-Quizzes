// 17.【2009统考真题】已知一个带有表头结点的单链表，结点结构为data-link。
// 假设该链表只给出了头指针list。
// 在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的结点（k为正整数）。
// 若查找成功，算法输出该结点的data域的值，并返回1；否则，只返回0。
// 要求：
// (1)描述算法的基本设计思想。
// (2)描述算法的详细实现步骤。
// (3)根据设计思想和实现步骤，采用程序设计语言描述算法（使用C、C++或Java语言实现），关键之处请给出简要注释。

// (1)算法的基本设计思想：
// 问题的关键是设计一个尽可能高效的算法，通过链表的一次遍历，找到倒数第k个结点的位置。
// 定义两个指针变量p和q，初始时均指向头结点的下一个结点（链表的第一个结点），p指针沿链表移动；当p指针移动到第k个结点时，q指针开始与p指针同步移动；当p指针移动到最后一个结点时，q指针所指示结点为倒数第k个结点。
// 以上过程对链表仅进行一遍扫描。

// (2)算法的详细实现步骤如下：
// ①count=0，p和q指向链表表头结点的下一个结点。
// ②若p为空，转⑤。
// ③若count等于k，则q转向下一个结点；否则，count=count+1。
// ④p指向下一个结点，转②。
// ⑤若count等于k，则查找成功，输出该结点的data域的值，返回1；否则，说明k值超过了线性表的长度，查找失败，返回0.
// ⑥算法结束。

// (3)算法实现如下：

#include<stdio.h>
#include<stdlib.h>

// 你代码中涉及的类型定义（补全基础结构）
typedef int ElemType; // 链表数据的类型定义
typedef struct LNode { // 链表结点的结构定义
	ElemType data; // 结点数据
	struct LNode* link; // 结点连接指针（与你代码中的link字段一致）
}LNode,*LinkList;

// 初始化带头结点的单链表
bool InitLinkList(LinkList& list) {
	list = (LNode*)malloc(sizeof(LNode));
	if (list == NULL)return false;
	list->link = NULL; // 头结点的link初始化为NULL
	return true;
}

// 尾插法创建带头结点的单链表（用于测试）
void CreateLinkList(LinkList& list, ElemType a[], int n) {
	if (!InitLinkList(list))return;
	LNode* r = list; // 尾指针，初始指向头结点
	for (int i = 0; i < n; i++) {
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->link = NULL;
		r->link = s; // 尾结点的link指向新结点
		r = s; // 尾指针后移
	}
}

// 打印带头结点的单链表（用于测试验证）
void PrintLinkList(LinkList list) {
	LNode* p = list->link; // 跳过表头结点
	if (p == NULL) {
		printf("链表为空\n");
		return;
	}
	while (p) {
		printf("%d", p->data);
		p = p->link;
	}
	printf("\n");
}

int Search_k(LinkList list, int k) {
	LNode* p = list->link, * q = list->link; // 指针p、q指示第一个结点
	int count = 0;
	while (p != NULL) { // 遍历链表直到最后一个结点
		if (count < k)count++; // 计数，若count<k只移动p
		else q = q->link;
		p = p->link; // 之后让p、q同步移动
	} // while
	if (count < k)
		return 0; // 查找失败返回0
	else { // 否则打印并返回1
		printf("%d", q->data);
		return 1;
	}
}

// 主函数：测试逻辑
int main() {
	// 测试用例1：查找倒数第2个结点（链表：1,2,3,4,5，倒数第2个是4）
	ElemType arr[] = { 1, 2, 3, 4, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	LinkList list;
	CreateLinkList(list, arr, n);

	printf("原链表：");
	PrintLinkList(list);

	printf("测试1-查找倒数第2个结点：");
	int res1 = Search_k(list, 2);
	printf("，返回值：%d\n", res1); // 输出4，返回1

	// 测试用例2：查找倒数第6个结点（超出链表长度，返回0）
	printf("测试2-查找倒数第6个结点：");
	int res2 = Search_k(list, 6);
	printf("，返回值：%d\n", res2); // 无输出，返回0
	return 0;
}