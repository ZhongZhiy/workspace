## 题意
对$1-n$的每个数的所有因子求和

## 题解
分块处理

## 参考代码
```cpp fold
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

#define DEBUG
#ifdef DEBUG
#define de(x) cout << (#x) << "=" << (x) << endl;
#define de2(x, y) cout << (#x) << " " << (#y) << " = " << (x) << " " << (y) << endl;
#else
#define de(x)
#define de2(x, y)
#endif
#define endl '\n'
#define fi(n) for(int i = 1;i <= n; ++i)
#define fi0(n) for(int i = 0;i < n; ++i)
#define fj(n) for(int j = 1;j <= n; ++j)
#define all(x) (x).begin(), (x).end()
#define hello ios::sync_with_stdio(0); cin.tie(0);cout.tie(0);
#define world return 0;
#define int long long
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

const int M = 1e9 + 7;

int qpow(int base, int pow) {
    int ans = 1;
    while(pow) {
        if(pow&1) ans = (ans * base) % M;
        base = (base * base) % M;
        pow >>= 1;
    }
    return ans;
}

signed main() {
    hello;
    int n; cin >> n;
    int cnt = 0;
    int r = 0;
    int inv = qpow(2, M-2);
    for(int l = 1;r <= n; l = r + 1) {
        int k = n / l;
        if(k < 1) break;
        r = n / k;
        if(r > n) break;
        //防止爆longlong
        int lsum = (l + r) % M;
        int len = (r - l + 1) % M;
        k %= M;
        int sum = (lsum * len) % M * inv % M;
        cnt = (cnt + sum * k % M) % M;

    }
    cout << cnt << endl;
}


```