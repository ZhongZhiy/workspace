#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

int main() {
    const int N = 1e7; // 数据规模，可以调整
    static int a[N + 5], b[N + 5], c[N + 5], head[N + 5];

    // 初始化
    for (int i = 1; i <= N; ++i) {
        b[i] = rand() % 100;
        c[i] = rand() % 100;
    }

    // -----------------------------
    // 第一种：分开两层循环
    // -----------------------------
    auto start1 = high_resolution_clock::now();

    for (int i = 1; i <= N; ++i) {
        a[i] = b[i] + c[i];
    }
    for (int i = 1; i <= N; ++i) {
        head[i] = head[i - 1] + a[i];
    }

    auto end1 = high_resolution_clock::now();
    auto t1 = duration_cast<milliseconds>(end1 - start1).count();

    // -----------------------------
    // 第二种：合并成一层循环
    // -----------------------------
    auto start2 = high_resolution_clock::now();

    for (int i = 1; i <= N; ++i) {
        a[i] = b[i] + c[i];
        head[i] = head[i - 1] + a[i];
    }

    auto end2 = high_resolution_clock::now();
    auto t2 = duration_cast<milliseconds>(end2 - start2).count();

    // 输出结果
    cout << "分开循环耗时: " << t1 << " ms\n";
    cout << "合并循环耗时: " << t2 << " ms\n";
    cout << "性能提升: " << fixed << setprecision(2)
         << 100.0 * (t1 - t2) / t1 << "%\n";

    return 0;
}

