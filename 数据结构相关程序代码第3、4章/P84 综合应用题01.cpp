// 1.若希望循环队列中的元素都能得到利用，则需设置一个标志域tag，并以tag的值为0或1来区分队首指针front和队尾指针rear相同时的队列状态是“空”还是“满”。
// 试编写与此结构相应的入队和出队算法。

#include<stdio.h>
#include<stdlib.h>

#define MaxSize 100 // 定义队列的最大容量
typedef int ElemType; // 定义队列元素类型为int

// 定义循环队列的结构体
typedef struct {
	ElemType data[MaxSize]; // 存储队列元素的数组
	int front; // 队头指针
	int rear; // 队尾指针
	int tag; // 标志位，0表示空，1表示可能满
}SqQueue;

// 初始化队列
void InitQueue(SqQueue& Q) {
	Q.front = Q.rear = 0;
	Q.tag = 0; // 初始时队列为空，tag设为0
}

int EnQueue1(SqQueue& Q, ElemType x) {
	if (Q.front == Q.rear && Q.tag == 1)
		return 0; // 两个条件都满足时则队满
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % MaxSize;
	Q.tag = 1; // 可能队满
	return 1;
}

int DeQueue1(SqQueue& Q, ElemType& x) {
	if (Q.front == Q.rear && Q.tag == 0)
		return 0; // 两个条件都满足时则队空
	x = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	Q.tag = 0;
	return 1;
}

// 主函数：测试入队和出队操作
int main() {
	SqQueue Q;
	InitQueue(Q); // 初始化队列

	ElemType x;
	// 测试入队
	if (EnQueue1(Q, 10))printf("入队10成功\n");
	if (EnQueue1(Q, 20))printf("入队20成功\n");
	if (EnQueue1(Q, 30))printf("入队30成功\n");

	// 测试出队
	if (DeQueue1(Q, x))printf("出队元素：%d\n", x);
	if (DeQueue1(Q, x))printf("出队元素：%d\n", x);
	if (DeQueue1(Q, x))printf("出队元素：%d\n", x);

	// 测试队空时出队
	if(!DeQueue1(Q, x))printf("队空，出队失败\n");
	return 0;
}