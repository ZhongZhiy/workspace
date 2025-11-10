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

/* 将表达式的类型映射为字符串 */
#define TYPENAME(x) _Generic((x), \
    signed char: "signed char", \
    unsigned char: "unsigned char", \
    short: "short", \
    unsigned short: "unsigned short", \
    int: "int", \
    unsigned int: "unsigned int", \
    long: "long", \
    unsigned long: "unsigned long", \
    long long: "long long", \
    unsigned long long: "unsigned long long", \
    float: "float", \
    double: "double", \
    long double: "long double", \
    bool: "bool", \
    char*: "char*", \
    const char*: "const char*", \
    void*: "void*", \
    const void*: "const void*", \
    default: "other")

/* 自动选择printf格式，打印值（仅覆盖本实验中涉及的类型） */
#define PRINT_VAL(x) do { \
    printf("%-26s -> %-22s = ", #x, TYPENAME((x))); \
    _Generic((x), \
        signed char:            printf("%d", (int)(x)), \
        unsigned char:          printf("%u", (unsigned)(x)), \
        short:                  printf("%d", (int)(x)), \
        unsigned short:         printf("%u", (unsigned)(x)), \
        int:                    printf("%d", (x)), \
        unsigned int:           printf("%u", (x)), \
        long:                   printf("%ld", (x)), \
        unsigned long:          printf("%lu", (x)), \
        long long:              printf("%lld", (x)), \
        unsigned long long:     printf("%llu", (x)), \
        float:                  printf("%.9g", (double)(x)), \
        double:                 printf("%.17g", (x)), \
        long double:            printf("%.21Lg", (x)), \
        bool:                   printf("%s", (x) ? "true" : "false"), \
        char*:                  printf("\"%s\"", (x)), \
        const char*:            printf("\"%s\"", (x)), \
        void*:                  printf("%p", (x)), \
        const void*:            printf("%p", (x)), \
        default:                printf("<unprintable-type>") \
    ); \
    puts(""); \
} while(0)

/* 分隔标题 */
static void section(const char* title) {
    puts("");
    printf("==== %s ====\n", title);
}

int main(void) {
    printf("平台字长与范围：\n");
    printf("CHAR_BIT=%d, sizeof(char)=%zu, sizeof(short)=%zu, sizeof(int)=%zu, sizeof(long)=%zu, sizeof(long long)=%zu\n",
           CHAR_BIT, sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(long long));
    printf("浮点：FLT_EVAL_METHOD=%d, sizeof(float)=%zu, sizeof(double)=%zu, sizeof(long double)=%zu\n",
           FLT_EVAL_METHOD, sizeof(float), sizeof(double), sizeof(long double));

    section("一、整型提升（integer promotions）与一元+/-/~/! 运算");
    signed char sc = -10;
    unsigned char uc = 250;
    short s = -20000;
    unsigned short us = 50000;
    PRINT_VAL(+sc);       // 一元+触发整型提升
    PRINT_VAL(~sc);       // 位反操作数经提升
    PRINT_VAL(+s);
    PRINT_VAL(+uc);
    PRINT_VAL(+us);

    section("二、通常算术转换（usual arithmetic conversions）- 混合算术");
    int i = -42;
    unsigned int ui = 42u;
    long l = -100000L;
    unsigned long ul = 100000UL;
    long long ll = -1;
    unsigned long long ull = 1ULL;
    float f = 3.5f;
    double d = 2.25;
    long double ld = 1.0L;

    PRINT_VAL(i + ui);       // 有符号与无符号同rank
    PRINT_VAL(l + ul);       // long 与 unsigned long
    PRINT_VAL(ll + ull);     // long long 与 unsigned long long
    PRINT_VAL(i + l);        // 提升到 long
    PRINT_VAL(ui + ul);      // 提升到 unsigned long
    PRINT_VAL(f + i);        // int => float（后再提升到更高精度）
    PRINT_VAL(f + d);        // float => double
    PRINT_VAL(d + ld);       // double => long double

    section("三、赋值转换（assignment）与截断/溢出");
    double dx = 123.75;
    int ix = (int)dx;      // 显式强转：截断
    PRINT_VAL(ix);
    unsigned char u8 = (unsigned char)300; // 模2^8截断
    PRINT_VAL(u8);
    long long big = 9223372036854775807LL; // LLONG_MAX
    double bigd = (double)big;             // 可能丢精
    PRINT_VAL(bigd);

    section("四、条件运算符(?:) 的类型合并");
    PRINT_VAL( (true ? i : ui) );   // 有符/无符合并
    PRINT_VAL( (false ? f : d) );   // float 与 double
    PRINT_VAL( (i ? d : ld) );      // double 与 long double

    section("五、位运算与移位");
    unsigned int m = 0xFFFF0000u;
    int n = -1;
    PRINT_VAL(m & n);     // 操作数经整型提升/算术转换
    PRINT_VAL(n >> 1);    // 算术右移或逻辑右移（实现定义）
    PRINT_VAL(m >> 1);    // 逻辑右移（无符号）

    section("六、指针与空指针常量转换");
    int a = 0;
    int *pi = &a;
    void *pv = pi;            // 任意T* 可隐式转 void*
    PRINT_VAL(pv);
    const void *pcv = pv;     // 添加限定符
    PRINT_VAL(pcv);
    int *pnull = 0;           // 0 / NULL 为空指针常量
    PRINT_VAL(pnull);
    char *pc = (char*)pv;     // 通过 void* 再转回（需显式）
    PRINT_VAL(pc);

    section("七、函数参数（原型存在时）");
    /* 带原型时，按参数类型进行转换；无原型（旧式C）会先发生默认实参提升，现代C已不建议使用无原型。 */
    printf("printf示例：%%d 接收int，%%f 接收double（float实参会提升为double）\n");
    float farg = 1.25f;
    printf("传入 float 给 %%f -> "); printf("%f\n", farg); // 实际按double传递

    section("八、边界示例：有符号与无符号比较/运算的陷阱");
    int neg1 = -1;
    unsigned int one = 1u;
    PRINT_VAL(neg1 < one);       // 有符号提升到无符号后比较
    PRINT_VAL(neg1 + one);       // 可能产生大的无符号值

    puts("\n(完)\n");
    return 0;
}
