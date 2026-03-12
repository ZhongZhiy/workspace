---
title: CF Pizza Devi
date: 2026-01-26
categories:
tags:
  - DP
  - 算法
status:
difficulty: 🟡 中等
link: https://codeforces.com/contest/2193/problem/F
---

# CF Pizza Delibery
## 题意

> [!abstract] 题目关键信息
> - 在二维平面中, 给定起始和终点坐标, 你需要从起点坐标经过所有外卖坐标到达终点坐标, 在$(x, y)$只可以移动到$(x+1)$或$(y-1)$ 或$(y+1)$, 每次移动需要$1$秒, 求需要的最少时间

##  题解
可以看到$x$只会增长, 不减小, 那么$x_{i-1} < x_{i}$的话, 从$x_{i-1}$到$x_{i}$只会从$x_{i-1}$的最高点或者最低点移动过来
**定义状态**: `dp[i][0]`为从第$i$点最低点离开, `dp[i][1]`为从最高点离开
**状态转移**: 从上一个点的最高/最低处到达这个点的最高/最低处
`dp[i][0] = min(dp[i-1][0] + abs(mn[i] - mx[i-1], dp[i-1][1] + abs(mx[i] - mx[i-1])) + need`
`dp[i][1] = min(dp[i-1][0] + abs(mn[i] - mn[i-1], dp[i-1][1] + abs(mx[i-1] - mn[i]) + need`
其中`need`是`need = x[i] - x[i-1] + mx[i] - mn[i]`

**初始状态**: 从第一个点出发, 起始点`dp[0][0] = dp[0][1] = 0`


##  参考代码
> [!example] 
```cpp fold
#include <algorithm>
#include <climits>
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
#define F first
#define S second
typedef vector<vector<int>> vvi;
typedef long long ll;

void solve() {
    int n, ax, ay, bx, by; cin >> n >> ax >> ay >> bx >> by;
    vvi dp(n+5, vi(2, 0));
    vi dx(n + 10), dy(n + 10);
    fi(n) cin >> dx[i];
    fi(n) cin >> dy[i];
    map<int, int> mx, mn;
    mx[ax] = mn[ax] = ay;
    mx[bx] = mn[bx] = by;

    fi(n) {
        mx[dx[i]] = max(mx[dx[i]], dy[i]);
        if(mn.count(dx[i])) mn[dx[i]] = min(mn[dx[i]], dy[i]);
        else mn[dx[i]] = dy[i];
    }

    int lst = ax, cnt = 0;
    for(auto [x, y] : mx) {
        if(x == ax) {
            dp[0][0] = dp[1][0] = 0;
            cnt++;
            continue;
        }

        int dis = x - lst + mx[x] - mn[x];
        dp[cnt][0] = min(dp[cnt-1][0] + abs(mn[lst]-mx[x]), dp[cnt-1][1] + abs(mx[lst]-mx[x])) + dis;
        dp[cnt][1] = min(dp[cnt-1][0] + abs(mn[lst] - mn[x]), dp[cnt-1][1] + abs(mx[lst]-mn[x])) + dis;
        lst = x;
        cnt++;
    }
    cnt --;
    cout << min(dp[cnt][0], dp[cnt][1]) << endl;

}

signed main() {
    hello;
    int t; cin >> t;
    while(t--) solve();

    world;
}


```
