// 20.【2019统考真题】设线性表L=(a1,a2,a3,...,an-2,an-1,an)采用带头结点的单链表保存，链表中的结点定义如下：
typedef struct node
{
	int data;
	struct node* next;
}NODE;
// 请设计一个空间复杂度为O(1)且时间上尽可能高效的算法，重新排列L中的各结点，得到线性表L'=(a1,an,a2,an-1,a3,an-2,...)。
// 要求：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
// (3)说明你所设计的算法的时间复杂度。

// (1)算法的基本设计思想：
// 先观察L=(a1,a2,a3,...,an-2,an-1,an)和L'=(a1,an,a2,an-1,a3,an-2,...)，发现L'是由L摘取第一个元素，再摘取倒数第一个元素......依次合并而成的。
// 为了方便链表后半段取元素，需要现将L后半段原地逆置[题目要求空间复杂度为O(1)，不能借助栈]，否则每取最后一个结点都需要遍历一次链表。
// ①先找出链表L的中间结点，为此设置两个指针p和q，指针p每次走一步，指针q每次走两步，当指针q到达链尾时，指针p正好在链表的中间结点；
// ②然后将L的后半段结点原地逆置。
// ③从单链表前后两段中依次各取一个结点，按要求重排。

// (2)算法实现如下：
#include<stdio.h>
#include<stdlib.h>

void change_list(NODE* h) {
	NODE* p, * q, * r, * s;
	p = q = h;
	while (q->next != NULL) { // 寻找中间结点
		p = p->next; // p走一步
		q = q->next;
		if(q->next != NULL)q = q->next; // q走两步
	}
	q = p->next; // p所指结点为中间结点，q为后半段链表的首结点
	p->next = NULL;
	while (q != NULL) { // 将链表后半段逆置
		r = q->next;
		q->next = p->next;
		p->next = q;
		q = r;
	}
	s = h->next; // s指向前半段的第一个数据结点，即插入点
	q = p->next; // q指向后半段的第一个数据结点
	p->next = NULL;
	while (q != NULL) { // 将链表后半段的结点插入到指定位置
		r = q->next; // r指向后半段的下一个结点
		q->next = s->next; // 将q所指结点插入到s所指结点之后
		s->next = q;
		s = q->next; // s指向前半段的下一个插入点
		q = r;
	}
}

// 辅助函数：创建链表（头插法，方便测试）
NODE* create_list(int arr[], int n) {
	NODE* head = (NODE*)malloc(sizeof(NODE));
	head->next = NULL; // 初始化头结点
	for (int i = n - 1; i >= 0; i--) {
		NODE* new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = arr[i];
		new_node->next = head->next;
		head->next = new_node;
	}
	return head;
}

// 辅助函数：打印链表
void print_list(NODE* h) {
	NODE* p = h->next;
	while (p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 辅助函数：释放链表内存
void free_list(NODE* h) {
	NODE* p = h, * q;
	while (p != NULL) {
		q = p->next;
		free(p);
		p = q;
	}
}

// 主函数：测试程序
int main() {
	// 测试用例：链表数据[1,2,3,4,5]（奇数个结点）
	int test_arr1[] = { 1,2,3,4,5 };
	int n1 = sizeof(test_arr1) / sizeof(test_arr1[0]);
	NODE* head1 = create_list(test_arr1, n1);

	printf("原链表1：");
	print_list(head1);
	change_list(head1);
	printf("重排后链表1：");
	print_list(head1);
	free_list(head1);

	// 测试用例：链表数据[1,2,3,4]（偶数个结点）
	int test_arr2[] = { 1,2,3,4 };
	int n2 = sizeof(test_arr2) / sizeof(test_arr2[0]);
	NODE* head2 = create_list(test_arr2, n2);

	printf("\n原链表2：");
	print_list(head2);
	change_list(head2);
	printf("重排后链表2：");
	print_list(head2);
	free_list(head2);
	return 0;
}

// (3)第一步找中间结点的时间复杂度为O(n)，第二步逆置的时间复杂度为O(n)，第三步合并链表的时间复杂度为O(n)，所以该算法的时间复杂度为O(n)。