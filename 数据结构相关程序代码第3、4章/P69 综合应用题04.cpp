// 4.设单链表的表头指针为L，结点结构由data和next两个域构成，其中data域为字符型。
// 设计算法判断该链表的全部n个字符是否中心对称。
// 例如，xyx、xyyx都是中心对称的。

#include<stdio.h>
#include<stdlib.h>

// 定义单链表结点结构
typedef struct LNode {
	char data;
	struct LNode* next;
}LNode,*LinkList;

// 初始化单链表（带头结点）
LinkList InitList() {
	LinkList L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	return L;
}

// 尾插法创建单链表
void CreateList(LinkList L, char str[], int n) {
	LNode* r = L;
	for (int i = 0; i < n; i++) {
		LNode* p = (LNode*)malloc(sizeof(LNode));
		p->data = str[i];
		p->next = NULL;
		r->next = p;
		r = p;
	}
}

int dc(LinkList L, int n) {
	int i;
	char* s = (char*)malloc((n / 2) * sizeof(char));
	if (s == NULL) {
		printf("内存分配失败！\n");
		return 0;
	}
	LNode* p = L->next; // 工作指针p，指向待处理的当前元素
	for (i = 0; i < n / 2; i++) { // 链表前一半元素入栈
		s[i] = p->data;
		p = p->next;
	}
	i--; // 恢复最后的i值
	if (n % 2 == 1) // 若n为奇数，后移过中心结点
		p = p->next;
	while (p != NULL && s[i] == p->data) { // 检测是否中心对称
		i--; // i充当栈顶指针
		p = p->next;
	}
	if (i == -1) // 栈为空栈
		return 1; // 链表中心对称
	else
		return 0; // 链表中心不对称
}

// 测试主函数
int main() {
	LinkList L = InitList();

	// 测试用例1：中心对称（偶数长度）
	char str1[] = "xyyx";
	int n1 = 4;
	CreateList(L, str1, n1);
	printf("字符串\"%s\"是否中心对称：%s\n", str1, dc(L, n1) ? "是" : "否");

	// 清空链表，准备下一个测试
	LNode* p, * q;
	p = L->next;
	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}
	L->next = NULL;

	// 测试用例2：中心对称（奇数长度）
	char str2[] = "xyx";
	int n2 = 3;
	CreateList(L, str2, n2);
	printf("字符串\"%s\"是否中心对称：%s\n", str2, dc(L, n2) ? "是" : "否");
	
	// 清空链表
	p = L->next;
	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}
	L->next = NULL;

	// 测试用例3：非中心对称
	char str3[] = "abcd";
	int n3 = 4;
	CreateList(L, str3, n3);
	printf("字符串\"%s\"是否中心对称：%s\n", str3, dc(L, n3) ? "是" : "否");
	free(L);

	return 0;
}