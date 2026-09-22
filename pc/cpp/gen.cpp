#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// 全局高质量随机数生成器
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 1. 生成 [l, r] 范围内的随机整数
long long rnd(long long l, long long r) {
    if (l > r) swap(l, r);
    return uniform_int_distribution<long long>(l, r)(rng);
}

// 2. 生成随机数组，长度为n，范围是 [min_val, max_val]
vector<long long> gen_array(int n, long long min_val, long long max_val) {
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rnd(min_val, max_val);
    }
    return a;
}

// 3. 生成一棵 N 个节点的随机树 (输出边对)
void print_random_tree(int n) {
    // 经典的建树方法：节点 2 到 N 分别向其前面的某个点连边
    for (int i = 2; i <= n; i++) {
        int u = i;
        int v = rnd(1, i - 1);
        cout << u << " " << v << "\n";
    }
}

int main() {
    // 关闭同步流提升大量数据的输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cout << t << "\n"; // 如果有多组测试数据取消注释

    while (t--) {

    }

    return 0;
}
