#include<stdio.h>
#include<stdbool.h>

void hashTable(int A[], int n, int x) {
	// 假设数组元素范围在[-10000,10000]，可根据实际情况调整
#define MAX_VAL 10000
#define MIN_VAL -10000
#define OFFSET 10000 // 用于将负数转为非负数索引
#define HASH_SIZE (MAX_VAL - MIN_VAL + 1)

	static bool hash[HASH_SIZE] = { false };
	static bool used[HASH_SIZE] = { false }; // 标记艺术处的

	for (int i = 0; i < n; i++) {
		int target = x - A[i];
		if (target >= MIN_VAL && target <= MAX_VAL && hash[target + OFFSET] && !used[A[i] + OFFSET] && !used[target + OFFSET]) {
			printf("(%d,%d)\n", target, A[i]);
			used[A[i] + OFFSET] = true;
			used[target + OFFSET] = true;
		}
		if (A[i] >= MIN_VAL && A[i] <= MAX_VAL) {
			hash[A[i] + OFFSET] = true;
		}
	}
}

int main() {
	int A[] = { 1,4,5,3,2 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 5;
	hashTable(A, n, x);
	return 0;
}