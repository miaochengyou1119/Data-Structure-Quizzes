// 1.从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删元素的值。
// 空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行。

#include<stdio.h>
#include<stdbool.h>

// 假设顺序表最大长度
#define MAXSIZE 100

// 定义元素类型，这里以int为例
typedef int ElemType;

// 定义顺序表结构体
typedef struct {
	ElemType data[MAXSIZE];
	int length; // 当前长度
}SqList;

bool Del_Min(SqList& L, ElemType& value) {
// 删除顺序表L中最小值元素结点，并通过引用型参数value返回其值
// 若删除成功，则返回true;否则返回false
	if (L.length == 0)
		return false; // 表空，中止操作返回
	value = L.data[0];
	int pos = 0; // 假定0号元素的值最小
	for (int i = 1; i < L.length; i++) // 循环，寻找具有最小值的元素
		if (L.data[i] < value) { // 让value记忆当前具有最小值的元素
			value = L.data[i];
			pos = i;
		}
	L.data[pos] = L.data[L.length - 1]; // 空出的位置由最后一个元素填补
	L.length--;
	return true; // 此时，value为最小值
}

// 测试用例
int main() {
	SqList L = { {5,2,8,1,9},5 }; // 初始化一个顺序表
	ElemType min_val;
	if (Del_Min(L, min_val)) {
		printf("删除的最小值为：%d\n", min_val);
		printf("删除后的顺序表元素为：");
		for (int i = 0; i < L.length; i++) {
			printf("%d", L.data[i]);
		}
		printf("\n");
	}
	return 0;
}