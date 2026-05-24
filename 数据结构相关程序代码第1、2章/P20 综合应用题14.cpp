// 14.【2020统考真题】定义三元组(a,b,c)（a，b，c均为整数）的距离D=|a-b|+|b-c|+|c-a|。
// 给定3个非空整数集合S1、S2和S3，按升序分别存储在3个数组中。
// 请设计一个尽可能高效的算法，计算并输出所有可能得三元组(a,b,c)(a∈S1,b∈S2,c∈S3)中的最小距离。
// 例如S1={-1,0,9}，S2={-25,-10,10,11}，S3={2,9,17,30,41}，则最小距离为2，相应的三元组为(9,10,9)。
// 要求：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C语言或C++语言描述算法，关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想：
// ①使用Dmin记录所有已处理的三元组的最小距离，初值为一个足够大的整数。
// ②集合S1、S2和S3分别保存在数组A、B、C中。
// 数组的下标变量i=j=k=0，当i<|S1|、j<|S2|且k<|S3|时（|S|表示集合S中的元素个数），循环执行下面的步骤a)~c)。
// a)计算（A[i],B[j],C[k]）的距离D；（计算D）
// b)若D<Dmin，则Dmin=D；（更新D）
// c)将A[i]、B[j]、C[k]中的最小值的下标+1；（对照分析：最小值为a，最大值为c，这里c不变而更新a，试图寻找更小的距离D）
// ③输出Dmin，结束。

// (2)算法实现：
#include<stdio.h>
#include<limits.h>

#define INT_MAX 0x7fffffff
int abs_(int a) { // 计算绝对值
	if (a < 0)return -a;
	else return a;
}
bool xls_min(int a,int b,int c){ // a是否是三个数中的最小值
	if (a <= b && a <= c)return true;
	return false;
}
int findMinofTrip(int A[], int n, int B[], int m, int C[], int p) {
	// D_min用于记录三元组的最小距离，初值赋为INT_MAX
	int i = 0, j = 0, k = 0, D_min = INT_MAX, D;
	while (i < n && j < m && k < p && D_min>0) {
		D = abs_(A[i] - B[j]) + abs_(B[j] - C[k]) + abs_(C[k] - A[i]); // 计算D
		if (D < D_min)D_min = D;
		if (xls_min(A[i], B[j], C[k]))i++; // 更新a
		else if (xls_min(B[j], C[k], A[i]))j++;
		else k++;
	}
	return D_min;
}

// 主函数测试
int main() {
	int S1[] = { -1,0,9 };
	int S2[] = { -25,-10,10,11 };
	int S3[] = { 2,9,17,30,41 };
	int n = sizeof(S1) / sizeof(S1[0]);
	int m = sizeof(S2) / sizeof(S2[0]);
	int p = sizeof(S3) / sizeof(S3[0]);
	int min_distance = findMinofTrip(S1, n, S2, m, S3, p);
	printf("最小距离为：%d\n", min_distance);
	return 0;
}

// (3)设n=(|S1|+|S2|+|S3|)，时间复杂度为O(n)，空间复杂度为O(1)。