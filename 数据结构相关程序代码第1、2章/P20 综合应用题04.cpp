// 4.从顺序表中删除其值在给定值s和t之间（包含s和t，要求s<t）的所有元素，若s或t不合理或顺序表为空，则显示出错信息并退出运行。

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100 // 顺序表最大长度

typedef int ElemType; // 元素类型定义为int，可根据需要

// 顺序表结构定义
typedef struct {
	ElemType data[MAXSIZE];
	int length; // 当前长度
}SqList;

// 初始化顺序表
void InitList(SqList& L) {
	L.length = 0;
}

// 尾插法添加元素
bool ListAdd(SqList& L, ElemType e) {
	if (L.length >= MAXSIZE) {
		printf("顺序表已满，无法插入\n");
		return false;
	}
	L.data[L.length++] = e;
	return true;
}

// 打印顺序表
void PrintList(SqList& L) {
	printf("顺序表元素：");
	for (int i = 0; i < L.length; i++) {
		printf("%d", L.data[i]);
	}
	printf("\n");
}

bool Del_s_t(SqList& L, ElemType s, ElemType t) {
// 删除顺序表L中值在给定值s和t（要求s<t）之间的所有元素
	int i, k = 0;
	if (L.length == 0 || s >= t)
		return false; // 线性表为空或s、t不合法，返回
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] >= s && L.data[i] <= t)
			k++;
		else
			L.data[i - k] = L.data[i]; // 当前元素前移k个位置
	} // for // 长度减小
	L.length -= k;
	return true;
}

// 主函数：测试
int main() {
	SqList L;
	InitList(L);
	// 构造测试数据
	ElemType testData[] = { 1,3,5,2,4,6,8,7,9 };
	int n = sizeof(testData) / sizeof(testData[0]);
	for (int i = 0; i < n; i++) {
		ListAdd(L, testData[i]);
	}
	printf("原顺序表：\n");
	PrintList(L);
	ElemType s = 3, t = 7;
	if (Del_s_t(L, s, t)) {
		printf("删除 [%d,%d]之间元素后： \n", s, t);
		PrintList(L);
	} else {
		printf("删除失败：顺序表为空或s>=t \n");
	}
	return 0;
}