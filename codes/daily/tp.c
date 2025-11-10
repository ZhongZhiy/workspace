#include <stdio.h>

int main(void) {
    printf("=== 2.5 位运算与移位测试 ===\n\n");

    unsigned int m = 0xFFFF0000u;
    int n = -1;
    unsigned int u = 1u;
    int s = 8;

    // 位运算：与、或、异或、取反
    printf("1. 按位与（&）:\n");
    printf("   m = 0x%X, n = 0x%X, m & n = 0x%X\n", m, n, m & n);

    printf("\n2. 按位或（|）:\n");
    printf("   m = 0x%X, u = 0x%X, m | u = 0x%X\n", m, u, m | u);

    printf("\n3. 按位异或（^）:\n");
    printf("   m = 0x%X, u = 0x%X, m ^ u = 0x%X\n", m, u, m ^ u);

    printf("\n4. 取反（~）:\n");
    printf("   u = 0x%X, ~u = 0x%X\n", u, ~u);

    // 移位运算：左移和右移
    printf("\n5. 左移（<<）:\n");
    printf("   u = 0x%X, u << s = 0x%X\n", u, u << s);

    printf("\n6. 右移（>>）无符号数:\n");
    printf("   m = 0x%X, m >> 1 = 0x%X\n", m, m >> 1);

    printf("\n7. 右移（>>）有符号数:\n");
    printf("   n = 0x%X, n >> 1 = 0x%X\n", n, n >> 1);

    printf("\n8. 混合位运算（有符号与无符号）:\n");
    printf("   n & u = 0x%X\n", n & u);

    return 0;
}
