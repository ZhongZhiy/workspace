---
title: CSES Longest Common Subsequent
date: 2026-01-25
categories:
tags:
  - 算法
  - DP
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/result/16045666/
---

# CSES Longest Common Subsequent
## 题意

> #最长公共子序列

两个序列的最长公共子序列
##  题解
**定义状态**: `dp[i][j]`为序列1中前`i`个和序列2中前`j`个数的最长公共子序列
**状态转移** : `if (a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 1`
`else if(a[i] != b[j]) dp[i][j] = max(dp[i-1][j], dp[i][j-1])`
**初始化**: 全为0



##  参考代码
> [!example] 
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
// #define int long long
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

const int N = 1005;
int a[N], b[N];
int dp[N][N], pre[N][N];

signed main() {
    int n, m; cin >> n >> m;
    fi(n) cin >> a[i];
    fi(m) cin >> b[i];
    fi(n)fj(m){
        if(a[i] == b[j]) dp[i][j] = dp[i-1][j-1]+1;
        else dp[i][j] = max({dp[i-1][j], dp[i][j-1]});
    }
    cout << dp[n][m] << endl;

    int i = n, j = m;
    vi ans;
    while(i >= 1 && j >= 1) {
        if(a[i] == b[j]) {
            ans.push_back(a[i]);
            i--; j--;
        }else if(dp[i][j-1] >= dp[i-1][j]) {
            j--;
        }else {
            i--;
        }
    }
    reverse(all(ans));
    for(auto c : ans) cout << c << ' ';


}


// 只需要记录最核心的代码块或模板
```
