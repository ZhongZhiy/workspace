#include <array>
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>
#define tii tuple<int, int, int>
#define tll tuple<ll, ll, ll>
#define sp << ' ' <<
#define inf 0x3f3f3f3f3f3f3f3f
#define N 100005
#define M 1000005
#define i128 __int128
#define lc p << 1
#define rc p << 1 | 1
#define v4 vector<vector<vector<vector<i128>>>>
#define ss (55, vector<vector<vector<i128>>>(55, vector<vector<i128>>(55, vector<i128>(4, 0))));
using namespace std;
using namespace __gnu_pbds;
int main() {
    // ios::sync_with_stdio(0); cout.tie(nullptr);

    auto solve = [&]() {
        ll n, d;
        cin >> n >> d;
        v4 dp ss;
        v4 dp_mid ss;
        dp[1][0][0][0] = 1, dp[0][1][0][1] = 1, dp[0][0][1][2] = 1;
        if (n == 2)
            dp_mid = dp;
        for (int i = 2; i <= n; i++) {

            v4 tmp ss;
            for (int a = 0; a < i; a++) {
                for (int b = 0; b + a < i; b++) {
                    int c = i - 1 - a - b;

                    for (int now = 0; now < 3; now++) {
                        for (int pre = 0; pre < 4; pre++) {
                            if (pre == now)
                                continue;
                            if (now == 1 && pre == 3)
                                continue;
                            if (now == 0) {
                                tmp[a + 1][b][c][now] += dp[a][b][c][pre];
                            } else if (now == 1) {
                                tmp[a][b + 1][c][now] += dp[a][b][c][pre];
                            } else if (now == 2) {
                                tmp[a][b][c + 1][now] += dp[a][b][c][pre];
                            }
                        }
                    }
                    tmp[a][b + 1][c][3] += dp[a][b][c][1];
                }
            }
            dp = tmp;
            if (i == n / 2)
                dp_mid = dp;
        }
        i128 ans = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j + i <= n; j++) {
                int k = n - i - j;
                for (int now = 0; now < 4; now++) {
                    if (max({abs(i - j), abs(j - k), abs(i - k)}) <= d)
                        ans += dp[i][j][k][now];
                }
            }
        }
        if (n % 2) {
            for (int i = 0; i <= n / 2; i++) {
                for (int j = 0; j + i <= n / 2; j++) {
                    int k = n / 2 - i - j;
                    for (int mid = 0; mid < 3; mid++) {
                        for (int now = 0; now < 4; now++) {
                            if (mid == now || (mid == 1 && now == 3))
                                continue;
                            int a = 2 * i, b = 2 * j, c = 2 * k;
                            switch (mid) {
                            case 0:
                                a++;
                                break;
                            case 1:
                                b++;
                                break;
                            case 2:
                                c++;
                                break;
                            }
                            if (max({abs(a - b), abs(b - c), abs(c - a)}) <= d)
                                ans -= dp_mid[i][j][k][now];
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i <= n / 2; i++) {
                for (int j = 0; j + i <= n / 2; j++) {
                    int k = n / 2 - i - j;
                    if (max({abs(i - j), abs(j - k), abs(k - i)}) * 2 <= d)
                        ans -= dp_mid[i][j][k][1];
                }
            }
        }
        auto write = [&](auto &&self, i128 x) -> void {
            if (x > 9)
                self(self, x / 10);
            cout << (ll)x % 10;
        };
        write(write, ans);
    };

    solve();
    return 0;
}
