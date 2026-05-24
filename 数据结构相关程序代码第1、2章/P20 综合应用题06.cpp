// 6.将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。

#include<stdio.h>
#include<stdbool.h>
#define MAXSIZE 100 // 可根据需要调整最大长度

typedef struct {
	int data[MAXSIZE]; // 存储元素的数组
	int length; // 当前长度
	int maxSize; // 最大容量
}SeqList;

bool Merge(SeqList A, SeqList B, SeqList& C) {
	// 将有序顺序表A与B合并为一个新的有序顺序表C
	if (A.length + B.length > C.maxSize) // 大于顺序表的最大长度
		return false;
	int i = 0, j = 0, k = 0;
	while (i < A.length && j < B.length) { // 循环，两两比较，小者存入结果表
		if (A.data[i] <= B.data[j])
			C.data[k++] = A.data[i++];
		else
			C.data[k++] = B.data[j++];
	}
	while (i < A.length) // 还剩一个没有比较完的顺序表
		C.data[k++] = A.data[i++];
	while (j < B.length)
		C.data[k++] = B.data[j++];
	C.length = k;
	return true;
}

// 辅助函数：打印顺序表
void PrintSeqList(SeqList L) {
	for (int i = 0; i < L.length; i++) {
		printf("%d",L.data[i]);
	}
	printf("\n");
}

int main() {
	// 初始化两个有序顺序表A和B
	SeqList A = { {1,3,5,7,9},5,MAXSIZE };
	SeqList B = { {2,4,6,8,10},5,MAXSIZE };
	SeqList C = { {0},0,MAXSIZE }; // 初始化空表C
	printf("顺序表A：");
	PrintSeqList(A);
	printf("顺序表B：");
	PrintSeqList(B);
	if (Merge(A, B, C)) {
		printf("合并后的顺序表C：");
		PrintSeqList(C);
	} else {
		printf("合并失败：顺序表C容量不足\n");
	}
	return 0;
}