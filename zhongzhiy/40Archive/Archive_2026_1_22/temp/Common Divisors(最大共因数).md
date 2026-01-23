## 题意
求数列中任意两个数的最大共因数尽可能大

## 题解
逆向思维, 枚举因数, 然后枚举因数的倍数, 只要有两个及以上的数被包含就可以了

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

const int N = 1e6 + 10;
int vis[N];

signed main() {
    hello;
    int n; cin >> n;
    int mx = 0;
    fi(n){
        int t; cin >> t;
        mx = max(mx, t);
        vis[t]++;
    }

    for(int i = mx; i >= 1; --i) {
        int cnt = 0;
        for(int j = 1;j <= mx && j*i <= mx; j++) {
            cnt += vis[j*i];
        }
        if(cnt >= 2) {
            cout << i << endl;
            return 0;
        }
    }
}


```