---
title: CSES Array Descrption
date: 2026-01-25
categories:
tags:
  - 算法
  - DP
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/task/1746/
---

# CSES Array Descrption


## 题意

> [!abstract] 题目关键信息
> 给定一个长度为$n$的数列, 其中一些值是未知的, 要求相邻两项之间的差不超过$1$, 问: 有多少给满足条件的数列

##  题解
这道题的约束要求记录当前的值和相邻的值, 因此使用二维DP:
**定义状态**`dp[i][j]`为第$i$个数字为$j$有多少种满足条件的子数列
**状态转移**: `dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1]` 满足条件的前三个相加
**初始化**: 如果第一个是给定的值, 则初始化`dp[1][v] = 1`, 否则对于$v \in m$, `dp[i][v] = 1`
**时间复杂度分析**, 如果是$n = 1 \times 10^5$, $m = 100$, 那么两层循环为$1\times 10^8$可以接受



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
const int M = 1e9 + 7;
int n, m;
int dp[N][105];


signed main() {
    hello;
    cin >> n >> m;
    vi a(n+1);
    fi(n) cin >> a[i];
    if(a[1]) {
        dp[1][a[1]] = 1;
    }else {
        fi(m) dp[1][i] = 1;
    }

    for(int i = 2;i <= n; ++i) {
        if(a[i]) dp[i][a[i]] = ((a[i] >= 1 ? dp[i-1][a[i]-1] : 0) + dp[i-1][a[i]] + (a[i]+1<=m ? dp[i-1][a[i]+1] : 0)) % M;
        else
        for(int j = 1; j <= m; ++j) {
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + (j+1 <= m ? dp[i-1][j+1] : 0)) % M;
        }
    }

    int sum = 0;
    fi(m) sum = (sum + dp[n][i] ) % M;
    // fi(m) cout << dp[2][i] << ' ';
    cout << sum << endl;


    world;
}


// 只需要记录最核心的代码块或模板
```
