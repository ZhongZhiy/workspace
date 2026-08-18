#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 998244353;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    auto solve = []() {
        int n, x, sum = 0;
        cin >> n >> x;

        vector<int>a(n);

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            cin >> a[i];
            cnt += a[i] / x;
            a[i] %= x;
        }
        sort(a.rbegin(), a.rend());

        if (x == 1) {
            cout << sum << '\n';
            return;
        }

        int ans = 0;
        for (int& t : a) {
            if (t + cnt + 1 >= x) {
                if (t == 0) {
                    break;
                }
                cnt -= x - t - 1;
                t = 0;
            } else {
                t += cnt;
                cnt = 0;
                break;
            }
        }

        for (int t : a) {
            // cout << t << ' ';
            ans += t;
            ans %= MOD;
        }

        if (cnt != 0) {
            ans += (cnt + 1) % x;
        }
        ans %= MOD;

        cout << ans << '\n';

    };

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
/*
3
3 3
1 1 1
1 4
3
4 10
30 8 7 6
*/
