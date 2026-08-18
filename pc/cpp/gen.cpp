// gen.cpp
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    // 使用当前时间戳作为随机数种子
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // 生成题目要求的变量，假设 N 的范围是 1 到 1000
    int t = 1;
    cout << t << "\n";

    // 生成数组中的 N 个元素，假设范围是 1 到 100000
    while(t--){
        int n = rng()% 100+1;
        int x = rng() % 200 + 1;
        cout << n << ' ' << x << "\n";
        for (int i = 0; i <n ; ++i) {
            cout << (rng() % 100 + 1) << " ";
        }
        cout << "\n";
    }

    return 0;
}
