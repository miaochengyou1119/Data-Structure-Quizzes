// 5.设有两个栈S1、S2都采用顺序栈方式，并共享一个存储区[0,...,maxsize-1]，为了尽量利用空间，减少溢出的可能，可采用栈顶相向、迎面增长的存储方式。
// 试设计S1、S2有关入栈和出栈的操作算法。

#include<stdio.h>
#include<stdlib.h>

#define maxsize 100 // 定义栈的最大容量

// 定义共享栈的结构体
typedef struct {
	int stack[maxsize]; // 共享的栈空间
	int top[2]; // top[0]是S1栈顶，top[1]是S2栈顶
}SharedStack;

// 全局声明共享栈
SharedStack s;

int Push(int i, int elem) {
// 入栈操作。i为栈号，=0表示左边的S1栈，i=1表示右边的S2栈，x是入栈元素
// 入栈成功返回i，否则返回0
	if (i < 0 || i>1) {
		printf("栈号输入不对");
		exit(0);
	}
	if (s.top[1] - s.top[0] == 1) {
		printf("栈已满\n");
		return 0;
	}
	switch (i) {
	case 0:s.stack[++s.top[0]] = elem; return 1; break;
	case 1:s.stack[--s.top[1]] = elem; return 1;
	}
}

int Pop(int i) {
// 出栈算法。i代表栈号，i=0时为S1栈，i=1时为S2栈
// 出栈成功返回出栈元素，否则返回-1
	if (i < 0 || i>1) {
		printf("栈号输入错误\n");
		exit(0);
	}
	switch (i) {
	case 0:
		if (s.top[0] == -1) {
			printf("栈空\n");
			return -1;
		}
		else
			return s.stack[s.top[0]--];
		break;
	case 1:
		if (s.top[1] == maxsize) {
			printf("栈空\n");
			return -1;
		}
		else
			return s.stack[s.top[1]++];
		break;
	} // switch

}

// 主函数：测试共享栈的入栈和出栈操作
int main() {
	// 初始化共享栈
	s.top[0] = -1; // S1栈顶初始化为-1（空栈）
	s.top[1] = maxsize; // S2栈顶初始化为maxsize（空栈）

	// 测试入栈
	Push(0, 10);
	Push(0, 20);
	Push(1, 30);
	Push(1, 40);

	// 测试出栈
	printf("S1出栈：%d\n", Pop(0)); // 应输出20
	printf("S1出栈：%d\n", Pop(0)); // 应输出10
	printf("S2出栈：%d\n", Pop(1)); // 应输出40
	printf("S2出栈：%d\n", Pop(1)); // 应输出30

	// 测试栈空情况
	printf("S1再次出栈：%d\n", Pop(0)); // 应提示栈空并返回-1
	printf("S2再次出栈：%d\n", Pop(1)); // 应提示栈空并返回-1
	return 0;
}