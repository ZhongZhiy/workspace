---
title: Making the Grade
date: 2026-01-30
categories:
tags:
  - 算法
  - DP
  - 线性DP
status:
link: https://icpc.upc.edu.cn/problem.php?cid=1434&pid=5
---

# Making the Grade
## 题意

> [!abstract] 题目关键信息
给定长度为 $N$ 的序列 $A$ , 构造一个长度为 $N$ 的序列 $B$ , 满足: 
>1. $B$ 非严格单调递减或递增
>2. 最小化 $S = \sum_{i = 1}^N |A_{i} - B_{i}$
>求最小值 $S$ . $1 \leq N \leq 2000, 1 \leq |A_{i}| \leq 10^9$




##  题解
有个引理:
>[!note]
>在满足 $S$ 最小化的前提下, 一定存在一种构造序列 $B$ 的方案, 使得 $B$ 中的所有数字的在 $A$ 中出现过

也就是现在只需要在 $A$ 中出现的数选择组成 $B$ , 
定义状态: $dp[i][j] = |A_{i} - S_{j}| + min\{dp[i-1][k]\}$ 其中 $dp[i][j]$  的含义是 $B$ 第 $i$ 个数取离散化后的 $A$ 的第 $j$ 个数取得的最小的值


##  参考代码
> [!example] 
```cpp
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
#define F first
#define S second
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

const int N = 2005;
int orig[N], uni[N], dp[N][N];

signed main() {
    hello;
    int n; cin >> n;
    fi(n) {
        cin >> orig[i];
        uni[i] = orig[i];
    }
    //离散化
    sort(uni+1, uni + 1 + n);
    int sz = unique(uni+1, uni+1+n) - (uni + 1);


    //递增情况
    for(int i = 1;i <= n; ++i) {
        int min_prev = -1;
        for(int j = 1;j <= sz; ++j) {
            if(min_prev < 0 || dp[i-1][j] < min_prev) min_prev = dp[i-1][j];
            dp[i][j] = abs(orig[i] - uni[j]) + min_prev;
        }
    }

    int ans = INT_MAX;
    fi(sz) ans = min(ans, dp[n][i]);

    //递减情况
    memset(dp, 0, sizeof(dp));
    for(int i = 1;i <= n; ++i) {
        int min_prev = -1;
        for(int j = sz;j >= 1 ; --j) {
            if(min_prev < 0 || dp[i-1][j] < min_prev) min_prev = dp[i-1][j];
            dp[i][j] = abs(orig[i] - uni[j]) + min_prev;
        }
    }
    fi(sz) ans = min(ans, dp[n][i]);
    cout << ans << endl;

    world;
}


```
