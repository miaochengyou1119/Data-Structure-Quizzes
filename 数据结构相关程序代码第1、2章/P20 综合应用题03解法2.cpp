// 3.对长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，该算法删除顺序表中所有值为x的数据元素。

// 解法2：用k记录顺序表L中等于x的元素个数，一边扫描L，一边统计k，并将不等于x的元素前移k个位置。
// 扫描结束后修改L的长度。

#include<stdio.h>
#include<stdlib.h>

// 定义顺序表最大长度
#define MAXSIZE 100

// 定义顺序表元素类型
typedef int ElemType;

// 定义顺序表结构体
typedef struct {
	ElemType data[MAXSIZE];
	int length;
}SqList;

void del_x_2(SqList& L, ElemType x) {
	int k = 0, i = 0; // k记录值等于x的元素个数
	while (i < L.length) {
		if (L.data[i] == x)
			k++;
		else
			L.data[i - k] = L.data[i]; // 当前元素前移k个位置
		i++;
	}
	L.length = L.length - k; // 顺序表L的长度递减
}

// 辅助函数：打印顺序表
void PrintList(SqList L) {
	for (int i = 0; i < L.length; i++) {
		printf("%d", L.data[i]);
	}
	printf("\n");
}

int main() {
	SqList L;
	L.length = 0;
	// 初始化顺序表
	int arr[] = { 1,2,3,2,4,2,5 };
	for (int i = 0; i < 7; i++) {
		L.data[i] = arr[i];
		L.length++;
	}
	printf("原顺序表：");
	PrintList(L);
	ElemType x = 2;
	del_x_2(L, x);
	printf("删除值为%d 后的顺序表：", x);
	PrintList(L);
	return 0;
}