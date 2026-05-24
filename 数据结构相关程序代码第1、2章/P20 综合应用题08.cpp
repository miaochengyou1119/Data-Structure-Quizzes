// 8.线性表(a1,a2,...,an)中的元素递增有序且按顺序存储于计算机内。
// 要求设计一个算法，完成用最少时间在表中查找数值为x的元素，若找到，则将其与后继元素位置相交换，若找不到，则将其插入表中并使表中元素仍然递增有序。

#include<stdio.h>

// 定义元素类型，这里用int作为示例
typedef int ElemType;

void SearchExchangeInsert(ElemType A[], ElemType x,int *n) {
	int low = 0, high = *n - 1, mid; // low和high指向顺序表下界和上界的下标
	while (low <= high) {
		mid = (low + high) / 2; // 找中间位置
		if (A[mid] == x) break; // 找到x，退出while循环
		else if (A[mid] < x) low = mid + 1; // 到中点mid的右半部去查
		else high = mid - 1; // 到中点mid的左半部去查
	} // 下面两个if语句只会执行一个
	if (A[mid] == x && mid != *n - 1) { // 若最后一个元素与x相等，则不存在与其后继交换的操作
		ElemType t = A[mid];
		A[mid] = A[mid + 1];
		A[mid + 1] = t;
	}
	if (low > high) { // 查找失败，插入数据元素x
		int i;
		for (i = *n - 1; i > high; i--)A[i + 1] = A[i]; // 后移元素
		A[i + 1] = x; // 插入x
		(*n)++; // 表长+1
	} // 结束插入
}

// 辅助函数：打印顺序表
void PrintList(ElemType A[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", A[i]);
	}
	printf("\n");
}

int main() {
	// 初始化一个递增有序的顺序表
	ElemType A[100] = { 1,3,5,7,9 };
	int n = 5; // 当前表长
	printf("初始顺序表：");
	PrintList(A, n);

	// 测试1：查找并交换存在的元素（非最后一个）
	int x1 = 5;
	printf("\n查找并交换元素 %d:\n",x1);
	SearchExchangeInsert(A, x1, &n);
	printf("操作后：");
	PrintList(A, n);

	// 测试2：查找并插入不存在的元素
	int x2 = 4;
	printf("\n插入元素 %d:\n", x2);
	SearchExchangeInsert(A, x2, &n);
	printf("操作后：");
	PrintList(A, n);

	// 测试3：查找最后一个元素（不交换）
	int x3 = 9;
	printf("\n查找最后一个元素 %d:\n", x3);
	SearchExchangeInsert(A, x3, &n);
	printf("操作后：");
	PrintList(A, n);

	return 0;
}