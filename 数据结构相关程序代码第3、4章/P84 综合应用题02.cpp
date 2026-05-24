// 2.Q是一个队列，S是一个空栈，实现将队列中的元素逆置的算法。

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// 定义元素类型
typedef int ElemType;

#define STACK_INIT_SIZE 100 // 栈初始容量
#define STACKINCREMENT 10 // 栈扩容增量

// 顺序栈结构体
typedef struct {
	ElemType* base; // 栈底指针
	ElemType* top; // 栈顶指针
	int stacksize; // 当前栈容量
}Stack;

// 初始化栈
bool InitStack(Stack& S) {
	S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base) {
		printf("栈内存分配失败！\n");
		return false;
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return true;
}

// 判断栈是否为空
bool StackEmpty(Stack& S) {
	return S.top == S.base;
}

// 入栈操作
bool Push(Stack& S, ElemType x) {
	// 检查栈是否满，满则扩容
	if (S.top - S.base >= S.stacksize) {
		S.base = (ElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (!S.base) {
			printf("栈扩容失败！\n");
			return false;
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = x; // 元素入栈，栈顶指针上移
	return true;
}

// 出栈操作
bool Pop(Stack& S, ElemType& x) {
	if (StackEmpty(S)) {
		printf("栈为空，无法出栈！\n");
		return false;
	}
	x = *--S.top; // 栈顶指针下移，取出元素
	return true;
}

// 销毁栈
void DestroyStack(Stack& S) {
	if (S.base) {
		free(S.base);
		S.base = NULL;
		S.top = NULL;
		S.stacksize = 0;
	}
}

// 链式队列结点结构
typedef struct QNode {
	ElemType data;
	struct QNode* next;
}QNode,*QueuePtr;

// 队列的头、尾指针结构
typedef struct {
	QueuePtr front; // 队头指针
	QueuePtr rear; // 队尾指针
}Queue;

// 初始化队列
bool InitQueue(Queue& Q) {
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) {
		printf("队列内存分配失败！\n");
		return false;
	}
	Q.front->next = NULL; // 队头结点后继为空
	return true;
}

bool QueueEmpty(Queue& Q) {
	return Q.front == Q.rear;
}

// 入队操作
bool EnQueue(Queue& Q, ElemType x) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) {
		printf("结点内存分配失败！\n");
		return false;
	}
	p->data = x;
	p->next = NULL;
	Q.rear->next = p; // 新结点链入队尾
	Q.rear = p; // 队尾指针后移
	return true;
}

// 出队操作
ElemType DeQueue(Queue& Q) {
	if (QueueEmpty(Q)) {
		printf("队列为空，无法出队！\n");
		exit(1); // 空队列出队直接退出，也可返回特定值
	}
	QueuePtr p = Q.front->next; // 指向队头元素结点
	ElemType x = p->data; // 取出队头元素
	Q.front->next = p->next; // 队头指针后继后移
	if(Q.rear==p){
		Q.rear = Q.front;
	}
	free(p); // 释放出队结点
	return x;
}

// 遍历输出队列
void TraverseQueue(Queue& Q) {
	if (QueueEmpty(Q)) {
		printf("队列为空！\n");
		return;
	}
	QueuePtr p = Q.front->next;
	printf("队列元素：");
	while (p) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 销毁队列
void DestroyQueue(Queue& Q) {
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

void Inverse(Stack& S, Queue& Q) {
// 本算法实现将队列中的元素逆置
	ElemType x; // 定义元素变量，用于存储出队/出栈的元素
	while (!QueueEmpty(Q)) {
		x = DeQueue(Q); // 队列中全部元素依次出队
		Push(S, x); // 元素依次
	}
	while (!StackEmpty(S)) {
		Pop(S, x); // 栈中全部元素依次出栈
		EnQueue(Q, x); // 再入队
	}
}

// 主函数：测试功能
int main() {
	Stack S;
	Queue Q;

	// 初始化栈和队列
	InitStack(S);
	InitQueue(Q);

	// 向队列中添加测试元素：1 2 3 4 5
	for (int i = 1; i <= 5; i++) {
		EnQueue(Q, i);
	}
	printf("逆置前：");
	TraverseQueue(Q);

	// 调用逆置函数
	Inverse(S, Q);

	printf("逆置后：");
	TraverseQueue(Q);

	// 释放资源
	DestroyStack(S);
	DestroyQueue(Q);
	return 0;
}