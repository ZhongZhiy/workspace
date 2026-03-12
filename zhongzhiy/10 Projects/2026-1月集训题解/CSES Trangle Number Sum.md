---
title: CSES Trangle Number Sum
date: 2026-01-23
categories:
tags:
  - 算法
  - 数论
status:
difficulty: 🟡 中等
link:
---

# CSES Trangle Number Sum
## 题意

> [!abstract] 题目关键信息
>求一个数最少能被多少个三角形数表示

##  题解
#费马多边形定理: 一个数最多被m个m边形数表示
所以最多被3个3边形数表示, 只要枚举1, 2, 3个就可以了

##  参考代码
> [!example] 
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
typedef vector<vector<int>> vvi;
typedef long long ll;

bool istrangle(int n) {
    if(n < 0) return false;
    int val = 8 * n + 1;
    int r = sqrt(val);
    return r * r == val;
}
void solve() {
    int n; cin >> n;
    if(istrangle(n)) cout << 1 << endl;
    else {
        for(int i = 1;i * (i + 1) / 2 < n; ++i) {
            if(istrangle(n - i * (i + 1)/2)) {
                cout << 2 << endl;
                return;
            }
        }
        cout << 3 << endl;
    }
}

signed main() {
    hello;
    int t; cin >> t;
    while(t--) solve();

    world;
}


```
