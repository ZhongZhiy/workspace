---
title: CSES Book Shop
date: 2026-01-25
categories:
tags:
  - 背包DP
  - 算法
  - DP
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/task/1158
---

# CSES Book Shop
## 题意

> [!abstract] 题目关键信息
> - **核心考点**： #背包DP
> 背包有$n$个容纳, 每本书价值$w_{i}$, 费用$c_{i}$求可以买的最大价值

##  题解
定义状态`dp[i]`为容量`i`可以买到的最大价值的书
那么状态转移`dp[i] = max(dp[i], dp[i-c[j]] + w[i])`
值得注意的是每本书只能买一次, 这是一个**0/1背包问题**, 
怎么处理只能买一次呢, 外层遍历书, 内层逆序遍历容量$n$, 这样每次转换使用的较小的状态`dp[i-c[j]]`就不会包含当前当前这本书, 当前这本书就不会被多次取


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

const int N = 1e5 + 10;
int cost[N], page[N];
int dp[N];

signed main() {
    hello;
    int n, x; cin >> n >> x;
    fi(n) cin >> cost[i];
    fi(n) cin >> page[i];

    for(int i = 1;i <= n; ++i) {
        for(int j = x; j >= 0; j --) {
            if(j >= cost[i])
            dp[j] = max(dp[j], dp[j-cost[i]]+page[i]);
        }
    }
    cout << dp[x];

    world;
}


// 只需要记录最核心的代码块或模板
```
