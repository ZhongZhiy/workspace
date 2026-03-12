---
title: LCIS最长上升公共子序列
date: 2026-01-30
categories:
tags:
  - 线性DP
  - DP
  - 算法
status:
link:
---

# LCIS最长上升公共子序列
## 题意

> [!abstract] 题目关键信息
给定俩个长为 $n$ 的数列, 求他们的最长上升公共子序列

##  题解
定义状态: `dp[i][j]` 为序列`a`的前`i`个数和序列`b`的前`j`个数的最长公共上升序列长度, 固定`i`的时候, 如果当前`b[j] == a[i]`, 那么 
$$
dp[i][j] = max{dp[i-1][k]}
$$
其中 $k$ 是小于 $j$ 的数, 也就是找序列 $b$ 的`1~j`中和序列 $a[i-1]$ 匹配的最长公共上升子序列作为转移

其中当内层遍历`j`的时候, 对应的`i`是固定的, 那么可以用一个变量来不断记录前`j`个中的最大值
##  参考代码
> [!example] 
```cpp
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

const int N = 3005;
int a[N], b[N], dp[N][N];

signed main() {
    hello;
    int n; cin >> n;
    fi(n) cin >> a[i];
    fi(n) cin >> b[i];

    fi(n) dp[i][0] = dp[0][i] = 0;
    for(int i = 1;i <= n; ++i) {
	    //记录最大值
        int val = 0;
        for(int j = 1;j <= n; ++j){
            if(a[i] == b[j]) dp[i][j] = val + 1;
            else dp[i][j] = dp[i-1][j];
            //满足递增条件
            if(b[j] < a[i]) val = max(val, dp[i-1][j]);
        }
    }
    int ans = 0;
    fi(n) ans = max(ans, dp[n][i]);
    cout << ans << endl;

    world;
}


```
