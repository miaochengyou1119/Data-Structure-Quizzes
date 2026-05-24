// 3.利用两个栈S1和S2来模拟一个队列，已知栈的4个运算定义如下：
// Push(S, x); // 元素x入栈S
// Pop(S, x); // S出栈并将出栈的值赋给x
// StackEmpty(S); // 判断栈是否为空
// StackOverflow(S); // 判断栈是否为满
// 如何利用栈的运算来实现该队列的3个运算（形参由读者根据要求自己设计）？
// Enqueue; // 将元素x入队
// Dequeue; // 出队，并将出队元素存储在x中
// QueueEmpty; // 判断队列是否为空

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// 定义元素类型
typedef int ElemType;

#define MAXSIZE 100 // 栈的最大容量
typedef struct {
	ElemType data[MAXSIZE];
	int top; // 栈顶指针
}Stack;

// 初始化栈
void InitStack(Stack* S) {
	S->top = -1;
}

// 判断栈是否为空
bool StackEmpty(Stack* S) {
	return S->top == -1;
}

// 判断栈是否满
bool StackOverflow(Stack* S) {
	return S->top == MAXSIZE - 1;
}

// 入栈操作
void Push(Stack* S, ElemType x) {
	if (StackOverflow(S)) {
		printf("栈满，无法入栈！\n");
		return;
	}
	S->data[++S->top] = x;
}

// 出栈操作
void Pop(Stack* S, ElemType* x) {
	if (StackEmpty(S)) {
		printf("栈空，无法出栈！\n");
		*x = -1; // 用-1标识出栈失败
		return;
	}
	*x = S->data[S->top--];
}

int Enqueue(Stack* S1, Stack* S2, ElemType e) {
	if (!StackOverflow(S1)) {
		Push(S1, e);
		return 1;
	}
	if (StackOverflow(S1) && !StackEmpty(S2)) {
		printf("队列为满");
		return 0;
	}
	if (StackOverflow(S1) && StackEmpty(S2)) {
		while (!StackEmpty(S1)) {
			ElemType x;
			Pop(S1, &x);
			Push(S2, x);
		}
	}
	Push(S1, e);
	return 1;
}

void Dequeue(Stack* S1, Stack* S2, ElemType* x) {
	if (!StackEmpty(S2)) {
		Pop(S2, x);
	}
	else if (StackEmpty(S1)) {
		printf("队列为空");
	}
	else {
		while (!StackEmpty(S1)) {
			ElemType x1;
			Pop(S1, &x1);
			Push(S2, x1);
		}
		Pop(S2, x);
	}
}

int QueueEmpty(Stack* S1, Stack* S2) {
	if (StackEmpty(S1) && StackEmpty(S2))
		return 1;
	else
		return 0;
}

// 遍历输出队列（模拟，通过出队+暂存实现）
void TraverseQueue(Stack* S1, Stack* S2) {
	if (QueueEmpty(S1, S2)) {
		printf("队列为空！\n");
		return;
	}
	Stack temp; // 临时栈存储出队元素，遍历后恢复
	InitStack(&temp);
	ElemType x;
	printf("队列元素：");
	while (!QueueEmpty(S1, S2)) {
		Dequeue(S1, S2, &x);
		printf("%d", x);
		Push(&temp, x);
	}
	// 将临时栈元素放回队列
	while (!StackEmpty(&temp)) {
		Pop(&temp, &x);
		Enqueue(S1, S2, x);
	}
	printf("\n");
}

int main() {
	Stack S1, S2;
	InitStack(&S1);
	InitStack(&S2);
	ElemType x;

	// 测试入队：1 2 3 4 5
	printf("入队元素：1 2 3 4 5\n");
	Enqueue(&S1, &S2, 1);
	Enqueue(&S1, &S2, 2);
	Enqueue(&S1, &S2, 3);
	Enqueue(&S1, &S2, 4);
	Enqueue(&S1, &S2, 5);

	// 遍历队列
	TraverseQueue(&S1, &S2);

	// 测试出队
	printf("出队一个元素：");
	Dequeue(&S1, &S2, &x);
	printf("%d\n", x);

	// 遍历出队后的队列
	TraverseQueue(&S1, &S2);

	// 测试队列判空
	printf("队列是否为空：%s\n", QueueEmpty(&S1, &S2) ? "是" : "否");

	return 0;
}