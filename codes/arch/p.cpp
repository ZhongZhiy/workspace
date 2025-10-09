#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007LL;

long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long inv(long long x) { return mod_pow(x, MOD - 2); }

long long Pnk(long long n, int k) {
    long long r = 1;
    for (int i = 0; i < k; ++i) r = r * (n - i) % MOD;
    return r;
}

long long Cnk(long long n, int k) {
    if (k < 0 || k > n) return 0;
    long long num = 1, den = 1;
    for (int i = 1; i <= k; ++i) {
        num = num * (n - k + i) % MOD;
        den = den * i % MOD;
    }
    return num * inv(den) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 常数因子：与输入无关，预先算一次
    const long long CONST_FACTOR =
        Pnk(95, 5) * Cnk(90, 5) % MOD * Cnk(85, 5) % MOD;

    vector<string> S(5);
    while (true) {
        // 读 5 行；兼容空行和 EOF
        int got = 0;
        for (int i = 0; i < 5; ) {
            string line;
            if (!getline(cin, line)) { got = -1; break; }
            if (line.empty()) continue; // 跳过空行
            S[i++] = line;
            ++got;
        }
        if (got == -1) break; // EOF


        // 位压 DP 计算 F
        const int FULL = (1<<5) - 1;
        vector<long long> dp(1<<5, 0), ndp(1<<5, 0);

        dp[0] = 1;

        for (int j = 0; j < 100; ++j) {
            ndp = dp; // 选项：不使用该英雄
            for (int mask = 0; mask <= FULL; ++mask) {
                long long ways = dp[mask];
                if (!ways) continue;
                for (int i = 0; i < 5; ++i) {
                    if (((mask >> i) & 1) == 0 && S[i][j] == '1') {
                        int nmask = mask | (1<<i);
                        ndp[nmask] += ways;
                        if (ndp[nmask] >= MOD) ndp[nmask] -= MOD;
                    }
                }
            }
            dp.swap(ndp);
        }
        long long F = dp[FULL];

        long long ans = F * CONST_FACTOR % MOD;
        cout << ans << "\n";
    }
    return 0;
}

