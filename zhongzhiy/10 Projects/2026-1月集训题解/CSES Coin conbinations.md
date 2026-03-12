---
title: CSES Coin conbinations
date: 2026-01-24
categories:
tags:
  - 算法
  - 排列组合
  - DP
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/task/1637
---

# CSES Coin conbinations
## 题意

> [!abstract] 题目关键信息
> - **核心考点**： #DP #排列组合
>求用给定金额的硬币, 求凑成$n$的排列和组合

##  题解
如果是算凑$n$的排列, 那么$\{1, 2\} , \{2, 1\}$是不同的状态, 

如果是凑$n$的组合, 那么就必须剔除顺序, 可以令小的硬币在前,

|**循环顺序**|**结果类型**|**逻辑直观理解**|
|---|---|---|
|**外层金额 $i$，内层硬币 $j$**|**排列 (Ordered)**|到达每个金额时，所有的硬币都可以作为“最后一跳”，所以顺序不同也算。|
|**外层硬币 $j$，内层金额 $i$**|**组合 (Unordered)**|硬币被一个一个加入系统。一旦开始考虑硬币 $B$，就再也不会回头去考虑硬币 $A$。|
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


const int M = 1e9 + 7;
signed main() {
    hello;
    int k, n; cin >> k >> n;
    vi mon(k);
    fi0(k) cin >> mon[i];
    sort(all(mon));

    vi dp(n+1);
    // fi(n) dp[i] = M;
    dp[0] = 1;
    // return 0;

    for(int j = 0;j < k; ++j) {
        for(int i = 1;i <= n; ++i) {
            if(i >= mon[j])
                dp[i] = (dp[i] + dp[i-mon[j]]) % M;
        }
    }
    cout << dp[n];
}


```
