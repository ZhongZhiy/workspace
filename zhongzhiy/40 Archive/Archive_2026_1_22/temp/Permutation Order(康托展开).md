## 题意
求$n$个数的第$k$个排列
求$n$个数的排列是第几的排列

## 题解
通过[[康托展开]]实现**排列与数字之间的转换**

## 参考代码
```cpp fold
#include <algorithm>
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

const int N = 20 + 5;


int fac[N];
void per_cal(){
    fac[0] = 1;
    for(int i = 1;i < N; ++i) {
        fac[i] = fac[i-1] * i;
    }
}

int rak[N];

void pre_rank(int n, int k) {
    // de2(n, k)
    memset(rak, 0, sizeof(rak));
    for(int i = n-1; i >= 0;i--) {
        rak[i] = k / fac[i];
        k %= fac[i];
        // de(i)
        // de2(rak[i], k)
    }
    // de2(n, k)
    // fi0(n) cout << rak[i] << ' ';
}

int ans_permutation[N];
void print_ans(int n) {
    for(int i = n-1;i >= 0; i--) cout << ans_permutation[i] << ' ';
    cout << endl;
}

void rank2permutation(int n, int k) {
    pre_rank(n,k);
    // return;
    vi num(n);
    for(int i = 1;i <= n; ++i) num[i-1] = i;

    // return;
    for(int i = n-1;i >= 0;i--) {
        ans_permutation[i] = num[rak[i]];
        num.erase(num.begin() + rak[i]);
    }
    print_ans(n);
}

int permutation[N];
void permutation2rank(int n) {
    for(int i = n-1;i >= 0; --i) {
        cin >> permutation[i];
    }
    vi num(n);
    fi0(n) num[i] = i+1;

    auto get_rank = [&](int x){
        return lower_bound(all(num), x) - num.begin();
    };

    int ans_rank = 0;
    for(int i = n-1; i >= 0;--i) {
        int rk = get_rank(permutation[i]);
        ans_rank += fac[i] * rk;
        // de2(i, rk)
        num.erase(num.begin() + rk);
    }
    cout << ans_rank + 1<< endl;
}

void solve(){
    int op; cin >> op;
    per_cal();
    if(op == 1){
        int n, k; cin >> n >> k;
        k--;
        // de(k)
        rank2permutation(n, k);
    }else {
        int n; cin >> n;
        permutation2rank(n);
    }
}

signed main() {
    hello;

    int t; cin >> t;
    while(t--) {
        solve();
    }
    world;
}


```