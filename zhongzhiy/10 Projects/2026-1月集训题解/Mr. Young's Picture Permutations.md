---
title: Mr. Young's Picture Permutations
date: 2026-01-29
categories:
tags:
  - 算法
  - DP
  - 记忆化搜索
  - 线性DP
status:
link: https://icpc.upc.edu.cn/problem.php?cid=1434&pid=6 算法提高DP
---

# Mr. Young's Picture Permutations
## 题意

> [!abstract] 题目关键信息
要求对 $N$个人排队满足以下要求, 最多 $5$ 排: 
>1. 每排靠左最齐, 且每第 $i$ 排人数为 $N_{i}$
>2. 每排从左到右递减
>3. 每列从后到前递减
>求满足这样排列的方案数

##  题解
#线性DP
考虑从高到第的学生 $i$ 可以怎么排, 
1. 首先由于约束 $2$ , 所以一定是在左侧有人的情况下才能排在某排
2. 其次, 由于约束 $3$ , 所以后排一定有人, 否则自己就会比之后放入后排的人高, 违反了约束 $3$ 
3. 由于约束 $1$ 每排不能超过 $N_{i}$

那么定义 $dp[a][b][c][d][e]$ 为每排分别是 $a, b, c, d, e$ 个人的时候的方案数, 那么 $$dp[a][b][c][d][e] += dp[a-1][b][c][d][e] + dp[a][b-1][c][d][e] + dp[a][b][c-1][d][e] + dp[a][b][e][d-1][e] + dp[a][b][c][d][e-1]$$
但是由于不知道 $k$ , 有几排, 所以不能走递推, 反之, 应该递归, 每个到底 状态$dp[a][b][c][d][e]$ 的就是一个方案, 通过记忆化剪枝, 最好算得从 $dp[0][0][0][0][0]$ 到目标状态有多少种方案

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
// #define int long long
typedef vector<int> vi;
#define F first
#define S second
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

unsigned dp[31][31][31][31][31];

int cl[6];
ll dfs(int a, int b, int c, int d, int e) {
    if(dp[a][b][c][d][e] != -1) return dp[a][b][c][d][e];
    if(a == cl[1] && b == cl[2] && c == cl[3] && d == cl[4] && e == cl[5]) {
        return 1;
    }

    ll res = 0;
    if(a < cl[1]) res += dfs(a+1, b, c, d, e);
    if(b < a && b < cl[2]) res += dfs(a, b+1, c, d, e);
    if(c < b && c < cl[3]) res += dfs(a, b, c+1, d, e);
    if(d < c && d < cl[4]) res += dfs(a, b, c, d+1, e);
    if(e < d && e < cl[5]) res += dfs(a, b, c, d, e + 1);
    return dp[a][b][c][d][e] = res;
}

signed main() {
    // hello;
    int n;
    while(cin >> n && n) {
        memset(dp, -1, sizeof(dp));
        memset(cl, 0, sizeof(cl));
        fi(n) cin >> cl[i];
        cout << dfs(0, 0, 0, 0, 0) << endl;
    }

    world;
}


```
