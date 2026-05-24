// 5.从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同。

#include<stdio.h>
#include<stdbool.h>
#define MaxSize 50 // 定义顺序表的最大容量

typedef struct {
	int data[MaxSize]; // 存储元素的数组
	int length; // 当前顺序表的长度
}SeqList;

bool Delete_Same(SeqList& L) {
	if (L.length == 0)
		return false;
	int i, j; // i存储第一个不相同的元素，j为工作指针
	for (i = 0, j = 1; j < L.length; j++)
		if (L.data[i] != L.data[j]) // 查找下一个与上一个元素值不同的元素
			L.data[++i] = L.data[j]; // 找到后，将元素前移
	L.length = i + 1;
	return true;
}

// 辅助函数：打印顺序表
void PrintList(SeqList L) {
	for (int k = 0; k < L.length; k++) {
		printf("%d", L.data[k]);
	}
	printf("\n");
}

int main() {
	// 测试用例
	SeqList L = { {1,2,2,2,2,3,3,3,4,4,5},11 };
	printf("原顺序表：");
	PrintList(L);
	if (Delete_Same(L)) {
		printf("去重后顺序表：");
		PrintList(L);
		printf("去重成功！\n");
	} else {
		printf("顺序表为空，无需去重。 \n");
	}
	return 0;
}