// 2.设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)。

#include<stdio.h>
#include<stdlib.h>

// 定义顺序表元素类型
typedef int ElemType;

// 定义顺序表结构
#define MAXSIZE 100
typedef struct {
	ElemType data[MAXSIZE];
	int length;
}SqList;

void Reverse(SqList& L) {
	ElemType temp; // 辅助变量
	for (int i = 0; i < L.length / 2;i++){
		temp = L.data[i]; // 交换L.data[i]与L.data[L.length-i-1]
		L.data[i] = L.data[L.length - i - 1];
		L.data[L.length - i - 1] = temp;
	}
}

// 辅助函数：打印顺序表
void PrintList(SqList L) {
	for (int i = 0; i < L.length; i++) {
		printf("%d", L.data[i]);
	}
	printf("\n");
}

int main() {
	// 初始化一个顺序表；
	SqList L;
	L.length = 5;
	L.data[0] = 1;
	L.data[1] = 2;
	L.data[2] = 3;
	L.data[3] = 4;
	L.data[4] = 5;
	printf("原顺序表：");
	PrintList(L);
	// 调用逆序函数
	Reverse(L);
	printf("逆序后顺序表：");
	PrintList(L);
	return 0;
}