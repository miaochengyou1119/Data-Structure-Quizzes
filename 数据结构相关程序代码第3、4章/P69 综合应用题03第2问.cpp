// 3.栈的始态和终态均为空，以I和O分别表示入栈和出栈，则出入栈的操作序列可表示为由I和O组成的序列，可以操作的序列称为合法序列，否则称为非法序列。
// (2)通过对(1)的分析，写出一个算法，判定所给的操作序列是否合法。
// 若合法，返回true，否则返回false（假定被判定的操作序列已存入一维数组中）。

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool Judge(char A[]) {
	int i = 0;
	int j = 0, k = 0; // i为下标，j和k分别为字母I和O的个数
	while (A[i] != '\0') { // 未到字符数组尾
		switch (A[i]) {
		case 'I':j++; break; // 入栈次数增1
		case 'O':k++;
			if (k > j) { printf("序列非法\n"); return false; }
		}
		i++; // 不论A[i]是I还是O，指针i均后移
	}
	if (j != k) {
		printf("序列非法\n");
		return false;
	}
	else {
		printf("序列合法\n");
		return true;
	}
}

int main() {
	char seq1[] = "IIOOIIOO"; // 合法序列
	char seq2[] = "IOIO"; // 合法序列
	char seq3[] = "IOOI"; // 非法序列(O>I)
	char seq4[] = "IIO"; // 非法序列(I!=O)

	Judge(seq1);
	Judge(seq2);
	Judge(seq3);
	Judge(seq4);
	return 0;
}