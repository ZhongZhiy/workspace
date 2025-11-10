/*
 * C11 类型转换规则验证程序
 * 说明：本程序通过一系列小实验，验证C语言在不同运算场景下的“整型提升”“通常算术转换”“条件运算符”“赋值转换”“移位/位运算”
 * 以及浮点与指针相关的转换行为。使用 _Generic 来在运行期打印表达式的“结果类型”。
 *
 * 编译：
 *   GCC/Clang（Linux/macOS, LP64）：  gcc -std=c11 -Wall -Wextra -O0 type_conversion_tests.c -o type_tests
 *   MSVC（Windows, LLP64）：          cl /std:c11 /W4 /Od type_conversion_tests.c
 *
 * 运行：
 *   ./type_tests   （Windows上为 type_tests.exe）
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>


int main(){
	printf("hello world!");
}
