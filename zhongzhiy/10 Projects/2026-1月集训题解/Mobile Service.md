---
title: Mobile Service
date: 2026-01-30
categories:
tags:
  - 线性DP
  - 算法
  - DP
status:
link: https://icpc.upc.edu.cn/problem.php?cid=1434&pid=1
---

# Mobile Service
## 题意

> [!abstract] 题目关键信息
有 $3$ 个服务员最初分别在 $1, 2, 3$ 位置上, 有 $n$ 个请求, 每个请求需要一个服务员去对应位置, 另外两个服务员不动, 每次移动有一定的花费且不对称 $co st[u][v] \neq co st[u][v]  , co st[u][u] = 0$, 求满足所有请求的最小费用

##  题解
最初, 可以定义`dp[i][a][b][c]`代表满足第`i`个请求时三个服务员分别在位置`a, b, c`上的时候的最小费用
但是时间, 和空间上都超过了

可以考虑每次移动后会有两个服务员不动, 一个服务员位于请求的位置, 那么就可以减少一个维度, 因为有一个永远是上一个请求的位置`dp[i][a][b]`就够了


##  参考代码
> [!example] 
```cpp
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
// #define int long long
typedef vector<int> vi;
#define F first
#define S second
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

const int N = 205;
int cost[N][N];
const int M = 1005;
//滚动数组
int dp[2][N][N], reg[M];

signed main() {
    hello;
    int l, n; cin >> l >> n;
    fi(l)fj(l) cin >> cost[i][j];

    fi(n) cin >> reg[i];
    reg[0] = 3;

    memset(dp, 0x3f, sizeof(dp));
    dp[0][1][2] = 0;

    for(int i = 1; i <= n; ++i) {
        //上一个请求的位置
        int c = reg[i-1];
        int cur = i % 2;
        //滚动数组初始化
        memset(dp[cur], 0x3f, sizeof(dp[cur]));
        for(int a = 1;a <= l; ++a){
            for(int b = 1; b <= l; ++b) {
                if(a == b || b == c || a == c) continue;
                if(a != reg[i] && b != reg[i]) dp[cur][a][b] = min(dp[cur][a][b], dp[1-cur][a][b] + cost[c][reg[i]]);
                if(b != reg[i] && c != reg[i]) dp[cur][c][b] = min(dp[cur][c][b], dp[1-cur][a][b] + cost[a][reg[i]]);
                if(c != reg[i] && a != reg[i]) dp[cur][a][c] = min(dp[cur][a][c] ,dp[1-cur][a][b] + cost[b][reg[i]]);
            }
        }
    }
    int ans = dp[0][0][0];
    for(int a = 1;a <= l; ++a)
        for(int b = 1;b <= l; ++b)
            ans = min(ans, dp[n%2][a][b]);
    cout << ans << endl;

    world;
}


```
