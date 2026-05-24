// 15.【2025统考真题】有两个长度均为n的一维整型数组A和res，对数组A中的每个元素A[i]，计算A[i]与A[j](0≤i≤j≤n-1)乘积的最大值，并将其保存到res[i]中。
// 例如，当A[]={1,4,-9,6}时，得到res[]={6,24,81,36}。
// 现给定数组A，设计一个时间和空间上尽可能高效的算法calMulMax,求res中各元素的值。
// 函数原型为void calMulMax(int A[],int res[],int n)。
// 要求如下：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想：
// 从后向前扫描一遍数组A，对每个A[i](0≤i≤n-1)，分别找到从A[n-1]到A[i]中的最大值Max和最小值Min，然后分以下情况进行处理：
// ①若A[i]≥0，则A[i]与Max相乘；
// ②若A[i]<0，则A[i]与Min相乘。
// 相乘的结果保存在res[i]中。

// (2)算法实现：
#include<stdio.h>

void calMulMax(int A[], int res[], int n) {
	int i, Max, Min;
	Max = Min = A[n - 1];
	for (i = n - 1; i >= 0; i--) { // 从后向前扫描一趟数组A
		if (A[i] > Max)Max = A[i];
		else if (A[i] < Min)Min = A[i];
		if (A[i] >= 0)res[i] = A[i] * Max; // 根据A[i]的正负性分别处理
		else res[i] = A[i] * Min;
	}
}

// 测试主函数
int main() {
	int A[] = { 1,4,-9,6 };
	int n = sizeof(A) / sizeof(A[0]);
	int res[4]; // 结果数组
	calMulMax(A, res, n);

	// 输出结果数组
	printf("res={");
	for (int i = 0; i < n; i++) {
		printf("%d", res[i]);
		if (i < n - 1)printf(",");
	}
	printf("}\n");

	return 0;
}

// (3)算法的时间复杂度为O(n)，空间复杂度为O(1)。