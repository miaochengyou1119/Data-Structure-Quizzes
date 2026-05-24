// 10.【2010统考真题】设将n(n>1)个整数存放到一维数组R中。
// 设计一个在时间和空间两方面都尽可能高效的算法。
// 将R中保存的序列循环左移p(0<p<n)个位置，即将R中的数据由(X0,X1,...,Xn-1)变换为(Xp,Xp+1,...,Xn-1,X0,X1,...,Xp-1)。
// 要求：
// (1)给出算法的基本设计思想。
// (2)根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
// (3)说明你所设计算法的时间复杂度和空间复杂度。

// (1)算法的基本设计思想:
// 可将问题视为把数组ab转换成数组ba（a代表数组的前p个元素，b代表数组中余下的n-p个元素），先将a逆置得到a^-1b，再将b逆置得到a^-1b^-1，最后将整个a^-1b^-1逆置得到(a^-1b^-1)^-1=ba。
// 设Reverse函数执行将数组逆置的操作，对abcdefgh向左循环移动3(p=3)个位置的过程如下：
// Reverse(0,p-1)得到cbadefgh;
// Reverse(p,n-1)得到cbahgfed;
// Reverse(0,n-1)得到defghabc。
// 注：在Reverse中，两个参数分别表示数组中待转换元素的始末位置。

// (2)使用C语言描述算法如下：

#include<stdio.h>

void Reverse(int R[], int from, int to) {
	for (int i = 0; i < (to - from + 1) / 2; i++) {
		int temp = R[from + i];
		R[from + i] = R[to - i];
		R[to - i] = temp;
	}
}

void Converse(int R[], int n, int p) {
	Reverse(R, 0, p - 1);
	Reverse(R, p, n - 1);
	Reverse(R, 0, n - 1);
}

// 辅助函数：打印数组，方便查看运行结果
void printArray(int R[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", R[i]);
	}
	printf("\n");
}

// 主函数：测试循环左移算法的完整逻辑
int main() {
	// 测试用例1：对应你注释中的示例(abcdefgh→defghabc)，数值版）
	int R1[] = { 1,2,3,4,5,6,7,8 };
	int n1 = 8; // 数组长度
	int p1 = 3; // 左移3个位置
	printf("原数组：");
	printArray(R1, n1);
	Converse(R1, n1, p1);
	printf("左移%d个位置后：", p1);
	printArray(R1, n1); // 输出：4 5 6 7 8 1 2 3
	
	// 测试用例2：自定义测试（验证不同n和p）
	int R2[] = { 10,20,30,40,50 };
	int n2 = 5;
	int p2 = 2;
	printf("\n原数组：");
	printArray(R2, n2);
	Converse(R2, n2, p2);
	printf("左移%d个位置后：", p2);
	printArray(R2, n2); // 输出：30 40 50 10 20

	return 0;
}

// (3)上述算法中三个Reverse函数的时间复杂度分别为O(p/2)、O((n-p)/2)和O(n/2)，故所设计的算法的时间复杂度为O(n)，空间复杂度为O(1)。

// 【另解】借助辅助数组来实现。算法思想：创建大小为p的辅助数组S，将R中前p个整数依次暂存在S中。
// 同时将R中后n-p个整数左移，然后将S中暂存的p个数依次放回到R中的后续单元。
// 时间复杂度为O(n)，空间复杂度为O(p)。