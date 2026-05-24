// 3.对长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，该算法删除顺序表中所有值为x的数据元素。

// 解法1：用k记录顺序表L中不等于x的元素个数（需要保存的元素个数），扫描时将不等于x的元素移动到下标k的位置，并更新k值。
// 扫描结束后修改L的长度。

#include<stdio.h>
#include<stdlib.h>

// 定义顺序表最大长度
#define MAXSIZE 100

// 定义元素类型
typedef int ElemType;

// 定义顺序表结构
typedef struct {
	ElemType data[MAXSIZE];
	int length;
}SqList;

void del_x_1(SqList& L, ElemType x) {
// 本算法实现删除顺序表L中所有值为x的数据元素
	int k = 0, i; // 记录值不等于x的元素个数
	for(int i=0;i<L.length;i++)
		if (L.data[i] != x) {
			L.data[k] = L.data[i];
			k++; // 不等于x的元素增1
		}
	L.length = k; // 顺序表L的长度等于k
}

// 以下为辅助函数，用于测试
// 初始化顺序表
void InitList(SqList& L) {
	L.length = 0;
}

// 插入元素
int ListInsert(SqList& L, int i, ElemType e) {
	if (i<1 || i>L.length + 1)return 0;
	if (L.length >= MAXSIZE)return 0;
	for (int j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[i - 1] = e;
	L.length++;
	return 1;
}

// 打印顺序表
void PrintList(SqList L) {
	for (int i = 0; i < L.length; i++)
		printf("%d", L.data[i]);
	printf("\n");
}

int main(){
	SqList L;
	InitList(L);
	// 插入测试数据
	ListInsert(L, 1, 2);
	ListInsert(L, 2, 3);
	ListInsert(L, 3, 2);
	ListInsert(L, 4, 4);
	ListInsert(L, 5, 2);
	ListInsert(L, 6, 5);
	printf("原顺序表：");
	PrintList(L);
	del_x_1(L, 2);
	printf("删除值为2的元素后：");
	PrintList(L);
	return 0;
}