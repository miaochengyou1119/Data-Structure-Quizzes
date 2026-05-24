#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

// 定义栈结构
typedef struct {
    char data[MAXSIZE];
    int top; // 栈顶指针
} SqStack;

// 初始化栈
void InitStack(SqStack* S) {
    S->top = -1;
}

// 判断栈是否为空
bool StackEmpty(SqStack S) {
    return S.top == -1;
}

// 入栈操作
bool Push(SqStack* S, char e) {
    if (S->top == MAXSIZE - 1) {
        printf("栈满，无法入栈\n");
        fflush(stdout);
        return false;
    }
    S->data[++(S->top)] = e;
    return true;
}

// 出栈操作（增加空栈判断的友好提示）
bool Pop(SqStack* S, char* e) {
    if (StackEmpty(*S)) {
        printf("栈空，无法出栈（存在多余的右括号）\n");
        fflush(stdout);
        return false;
    }
    *e = S->data[(S->top)--];
    return true;
}

// 修复核心逻辑：确保所有分支都有输出
bool BracketsCheck(char* str) {
    SqStack S;
    InitStack(&S);
    int i = 0;
    bool isMatch = true; // 标记是否匹配
    char e;

    while (str[i] != '\0' && isMatch) {
        switch (str[i]) {
            // 左括号入栈
        case '(': Push(&S, '('); break;
        case '[': Push(&S, '['); break;
        case '{': Push(&S, '{'); break;

            // 右括号匹配检查（核心修复：增加输出）
        case ')':
            if (!Pop(&S, &e) || e != '(') {
                isMatch = false;
            }
            break;
        case ']':
            if (!Pop(&S, &e) || e != '[') {
                isMatch = false;
            }
            break;
        case '}':
            if (!Pop(&S, &e) || e != '{') {
                isMatch = false;
            }
            break;

        default: // 忽略非括号字符
            break;
        }
        i++;
    }

    // 统一输出结果（所有情况都能覆盖）
    if (!isMatch || !StackEmpty(S)) {
        printf("括号不匹配\n");
    }
    else {
        printf("括号匹配\n");
    }
    fflush(stdout); // 强制刷新输出
    return isMatch && StackEmpty(S);
}

// 主函数：保持测试逻辑，增加暂停
int main() {
    char test1[] = "({[()]})"; // 匹配
    char test2[] = "({[([)]})"; // 中间不匹配
    char test3[] = "(()";      // 左括号多余
    char test4[] = "())";      // 右括号多余（新增测试用例）

    // 测试用例1
    printf("测试用例1: %s\n", test1);
    BracketsCheck(test1);

    // 测试用例2
    printf("测试用例2: %s\n", test2);
    BracketsCheck(test2);

    // 测试用例3
    printf("测试用例3: %s\n", test3);
    BracketsCheck(test3);

    // 测试用例4（验证多余右括号）
    printf("测试用例4: %s\n", test4);
    BracketsCheck(test4);

    // 暂停窗口，方便查看结果
    printf("\n按任意键退出...\n");
    system("pause");
    return 0;
}