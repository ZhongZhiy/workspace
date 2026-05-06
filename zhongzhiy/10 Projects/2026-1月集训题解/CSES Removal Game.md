---
title: CSES Removal Game
date: 2026-01-26
categories:
tags:
  - 区间DP
  - 算法
  - DP
  - finished
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/result/16054550/
---

# CSES Removal Game
## 题意

> [!abstract] 题目关键信息
> - **核心考点**： #区间DP 
> 一个数列, 两个人轮流取数, 每个人只能取当前数列中的两端的值, 问第一个人可以取到的最大总和

##  题解
**定义状态**: `dp[i][j]`为区间`i~j`能取到的最大值
**状态转移**: `sum[i][j]`为`i~j`的总和, 由于是0和游戏, 用总和减去剩下区间的最大取值就是当前区间可以取到的最大数值和
`dp[i][j] = max(sum[i][j] - dp[i+1][j], sum[i][j] - dp[i][j-1]`
**状态初始**: `dp[i][i] = a[i]`
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
#define F first
#define S second
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;


const int N = 5005;
int dp[N][N], sum[N];

signed main() {
    hello;
    int n; cin >> n;
    fi(n){
        cin >> dp[i][i];
        sum[i] = sum[i-1] + dp[i][i];
    }

    for(int len = 2; len <= n; ++len) {
        for(int i = 1;i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            dp[i][j] = sum[j] - sum[i-1] + max(-dp[i+1][j], -dp[i][j-1]);
        }
    }
    cout << dp[1][n] << endl;

    world;
}


```
