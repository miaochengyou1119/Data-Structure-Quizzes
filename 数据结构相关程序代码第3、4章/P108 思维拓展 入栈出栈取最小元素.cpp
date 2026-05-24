#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// 定义栈的最大容量（可根据需求调整）
#define MAX_SIZE 100

// 定义最小栈结构：包含数据栈、最小值栈、各自的栈顶指针
typedef struct {
	int data_stack[MAX_SIZE]; // 数据栈：存储所有元素
	int min_stack[MAX_SIZE]; // 辅助栈：存储当前最小值
	int data_top; // 数据栈顶指针（初始为-1表示空栈）
	int min_top; // 最小值栈顶指针
}MinStack;

// 初始化最小栈
// @param stack：指向MinStack结构体的指针
void MinStackInit(MinStack* stack) {
	stack->data_top = -1;
	stack->min_top = -1;
}

// 入栈操作(Push)：时间复杂度O(1)
// @param stack：最小栈指针
// @param val：要入栈的数值
// @return：成功返回1，失败（栈满）返回0
int MinStackPush(MinStack* stack, int val) {
	// 检查栈是否已满
	if (stack->data_top >= MAX_SIZE - 1) {
		printf("栈已满，无法入栈！\n");
		return 0;
	}
	// 1.数据栈入栈
	stack->data_stack[++stack->data_top] = val;

	// 2.最小值栈入栈规则：空栈或新值≤当前最小值时入栈
	if (stack->min_top == -1 || val <= stack->min_stack[stack->min_top]) {
		stack->min_stack[++stack->min_top] = val;
	}
	return 1;
}

// 出栈操作(Pop)：时间复杂度O(1)
// @param stack：最小栈指针
// @return：成功返回1，失败（栈空）返回0
int MinStackPop(MinStack* stack) {
	// 检查栈是否为空
	if (stack->data_top == -1) {
		printf("栈为空，无法出栈！\n");
		return 0;
	}
	// 1.获取要弹出的元素
	int popped_val = stack->data_stack[stack->data_top--];

	// 2.若弹出的是当前最小值，最小值栈也出栈
	if (popped_val == stack->min_stack[stack->min_top]) {
		stack->min_top--;
	}
	return 1;
}

// 获取栈顶元素：时间复杂度O(1)
// @param stack：最小栈指针
// @return：栈顶元素（栈空返回INT_MAX）
int MinStackTop(MinStack* stack) {
	if (stack->data_top == -1) {
		printf("栈为空，无栈顶元素！\n");
		return INT_MAX;
	}
	return stack->data_stack[stack->data_top];
}

// 获取栈中最小值（min操作）：时间复杂度O(1)
// @param stack：最小栈指针
// @return：最小值（栈空返回INT_MAX）
int MinStackGetMin(MinStack* stack) {
	if (stack->min_top == -1) {
		printf("栈为空，无最小值！\n");
		return INT_MAX;
	}
	return stack->min_stack[stack->min_top];
}

// 测试程序
int main() {
	MinStack stack;
	MinStackInit(&stack); // 初始化栈

	// 入栈操作
	MinStackPush(&stack, -2);
	MinStackPush(&stack, 0);
	MinStackPush(&stack, -3);

	// 获取最小值（预期：-3）
	printf("当前栈最小值：%d\n", MinStackGetMin(&stack));

	// 出栈操作（弹出-3）
	MinStackPop(&stack);

	// 获取栈顶元素（预期：0）
	printf("当前栈顶元素：%d\n", MinStackTop(&stack));

	// 再次获取最小值（预期：-2）
	printf("当前栈最小值：%d\n", MinStackGetMin(&stack));

	return 0;
}