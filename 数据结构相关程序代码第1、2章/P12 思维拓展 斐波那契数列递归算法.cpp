#include<iostream>
#include<stdexcept>

// 递归求解斐波那契数列第n项 时间复杂度O（2^n）
long long fib_recursive(int n) {
	// 边界条件校验
	if (n < 0) {
		throw std::invalid_argument("n 必须是非负整数");
	}
	// 递归终止条件
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	}
	// 递归核心逻辑
	return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
	try {
		std::cout << "=== 递归算法 ===" << std::endl;
		std::cout << "第5项：" << fib_recursive(5) << std::endl; // 输出5
		std::cout << "第10项：" << fib_recursive(10) << std::endl; // 输出55
		// 注意：n超过40后递归会明显变慢，甚至栈溢出
		// std::cout<<"第50项： "<<fib_recursive(50)<<std::endl; // 不推荐执行
	} catch (const std::invalid_argument& e) {
		std::cerr << "错误： " << e.what() << std::endl;
	}
	return 0;
}
