#include<iostream>
#include<stdexcept>

// 非递归（迭代）求解斐波那契数列第n项 时间复杂度O（1）
long long fib_iterative(int n) {
	// 边界条件校验
	if (n < 0) {
		throw std::invalid_argument("n 必须是非负整数");
	}
	// 基础项直接返回
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	}

	// 迭代计算核心逻辑
	long long a = 0; // F(n-2)
	long long b = 1; // F(n-1)
	long long result = 0;
	for (int i = 2; i <= n; ++i) {
		result = a + b; // F(i) = F(i-1) + F(i-2)
		a = b; // 更新F(n-2)为原F(n-1)
		b = result; // 更新F(n-1)为当前F(i)
	}
	return result;
}

int main() {
	try {
		std::cout << "=== 非递归算法 ===" << std::endl;
		std::cout << "第5项： " << fib_iterative(5) << std::endl; // 输出5
		std::cout << "第10项： " << fib_iterative(10) << std::endl; // 输出55
		std::cout << "第100项： " << fib_iterative(100) << std::endl; // 可快速计算
	} catch(const std::invalid_argument&e){
		std::cerr << "错误： " << e.what() << std::endl;
	}
	return 0;
}
