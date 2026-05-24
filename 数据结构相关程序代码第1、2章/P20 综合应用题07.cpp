// 7.已知在一维数组A[m+n]中依次存放两个线性表(a1,a2,a3,...,am)和(b1,b2,b3,...,bn)。
// 编写一个函数，将数组中两个顺序表的位置互换，即将(b1,b2,b3,...,bn)放在(a1,a2,a3,...,am)的前面。

#include<stdio.h>

typedef int DataType;
void Reverse(DataType A[], int left, int right, int arraySize) {
// 逆转(aleft,aleft+1,aleft+2,...,aright)为(aright,aright-1,...,aleft)
	if (left >= right || right >= arraySize)
		return;
	int mid = (left + right) / 2;
	for (int i = 0; i <= mid - left; i++) {
		DataType temp = A[left + i];
		A[left + i] = A[right - i];
		A[right - i] = temp;
	}
}
void Exchange(DataType A[], int m, int n, int arraySize) {
/*数组A[m+n]中，从0到m-1存放顺序表(a1,a2,a3,...,am)，从m到m+n-1存放顺序表
(b1,b2,b3,...,bn)，算法将这两个表的位置互换*/
	Reverse(A, 0, m + n - 1, arraySize);
	Reverse(A, 0, n - 1, arraySize);
	Reverse(A, n, m + n - 1, arraySize);
}

// 测试函数
int main() {
	int A[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int m = 5, n = 5;
	int arraySize = sizeof(A) / sizeof(A[0]);
	printf("原数组：");
	for (int i = 0; i < arraySize; i++) {
		printf("%d", A[i]);
	}
	printf("\n");
	Exchange(A, m, n, arraySize);
	printf("交换后：");
	for (int i = 0; i < arraySize; i++) {
		printf("%d", A[i]);
	}
	printf("\n");
	return 0;
}