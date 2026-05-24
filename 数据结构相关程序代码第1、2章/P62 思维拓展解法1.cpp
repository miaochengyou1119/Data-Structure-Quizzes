#include<stdio.h>
#include<stdlib.h>

// 用于qsort的比较函数
int cmp(const void* a, const void* b) {
	return*(int*)a - *(int*)b;
}

void twoPointer(int A[], int n, int x) {
	qsort(A, n, sizeof(int), cmp); // 排序0(nlogn)
	int i = 0, j = n - 1;
	while (i < j) {
		int sum = A[i] + A[j];
		if(sum<x){
			i++;
		} else if (sum > x) {
			j--;
		} else {
			printf("(%d,%d)\n", A[i], A[j]);
			i++;
			j--;
			// 跳过重复元素（可选）
			while (i < j && A[i] == A[i - 1])i++;
			while (i < j && A[j] == A[j + 1])j--;
		}
	}
}

int main() {
	int A[] = { 1,4,5,3,2 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 5;
	twoPointer(A, n, x);
	return 0;
}