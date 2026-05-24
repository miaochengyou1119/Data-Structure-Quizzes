#include <stdio.h>
#include <string.h>

/**
 * 统计模式串在主串中完全匹配的子串数量
 * @param main_str 主串
 * @param pattern_str 模式串
 * @return 匹配的次数
 */
int countPatternMatches(const char* main_str, const char* pattern_str) {
    // 获取主串和模式串的长度
    int main_len = strlen(main_str);
    int pattern_len = strlen(pattern_str);

    // 匹配次数计数器
    int count = 0;

    // 边界条件：如果模式串为空，或者模式串比主串长，直接返回0
    if (pattern_len == 0 || pattern_len > main_len) {
        return 0;
    }

    // i为主串指针，j为模式串指针
    int i = 0, j = 0;
    while (i < main_len) {
        // 当前字符匹配，同时后移指针
        if (main_str[i] == pattern_str[j]) {
            i++;
            j++;
        }
        else {
            // 匹配失败，主串指针回退，模式串指针重置
            i = i - j + 1;
            j = 0;
        }

        // 模式串全部匹配完成，计数加1
        if (j == pattern_len) {
            count++;
            // 匹配成功后，主串指针回退（避免重叠匹配漏统计），模式串重置
            i = i - j + 1;
            j = 0;
        }
    }

    return count;
}

int main() {
    // 定义主串和模式串（你可以修改这两个字符串测试不同情况）
    char main_str[] = "ababcabcabx";
    char pattern_str[] = "abc";

    // 调用函数统计匹配次数
    int match_count = countPatternMatches(main_str, pattern_str);

    // 输出结果
    printf("主串: %s\n", main_str);
    printf("模式串: %s\n", pattern_str);
    printf("完全匹配的子串数量: %d\n", match_count);

    return 0;
}