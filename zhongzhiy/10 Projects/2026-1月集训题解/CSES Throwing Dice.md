---
title: CSES Throwing Dice
date: 2026-01-22
categories:
tags:
  - 算法
  - 矩阵快速幂
  - 组合数学
status:
difficulty: finished
link: https://cses.fi/problemset/task/1096
---

# CSES Throwing Dice
## 题意
>[!info] 题意
>求点数$n$可以又哪些骰子情况组成
>

##  题解
用DP可以, 但会超时
题目可以转换求: `dp[i] = dp[i-1]+dp[i-2]+dp[i-3]+dp[i-4]+dp[i-5]+dp[i-6]`
显然这是线性加法, 可以使用[[10 Projects/2026-1月集训题解/矩阵快速幂]]加速计算
构造矩阵:
```markdown
start = [1,2,3,6,12,24]
		
		0 0 0 0 0 1
		1 0 0 0 0 1
trans = 0 1 0 0 0 1
		0 0 1 0 0 1
		0 0 0 1 0 1
		0 0 0 0 1 1
```


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
typedef long long ll;

const int N = 1e9 + 7;
struct mat{
    int v[6][6];
    int r, c;
    mat(int r, int c):r(r), c(c){memset(v, 0, sizeof(v));}
};

mat mutiply(mat a, mat b){
    mat c{a.r,b.c};
    for(int i = 0;i < a.r; ++i)
        for(int j = 0;j < b.c; ++j)
            for(int k = 0;k < a.c; ++k) {
                if(a.v[i][k] == 0) continue;
                c.v[i][j] = (c.v[i][j] + a.v[i][k] * b.v[k][j] % N ) % N;
            }
    return c;
}

mat qpow(mat base, int pow) {
    mat ans(6,6);
    for(int i = 0;i < 6; ++i) ans.v[i][i] = 1;
    while(pow) {
        if(pow&1) {ans = mutiply(ans, base);}
        base = mutiply(base, base);
        pow>>=1;
    }
    return ans;
}

int cal(int n) {
    mat start(1, 6);
    start.v[0][0] = 1; start.v[0][1] = 2; start.v[0][2] = 3;
    start.v[0][3] = 6; start.v[0][4] = 12; start.v[0][5] = 24;

    mat base(6,6);
    base.v[0][0] = 0; base.v[0][1] = 0; base.v[0][2] = 0; base.v[0][3] = 0; base.v[0][4] = 0; base.v[0][5] = 1;
    base.v[1][0] = 1; base.v[1][1] = 0; base.v[1][2] = 0; base.v[1][3] = 0; base.v[1][4] = 0; base.v[1][5] = 1;
    base.v[2][0] = 0; base.v[2][1] = 1; base.v[2][2] = 0; base.v[2][3] = 0; base.v[2][4] = 0; base.v[2][5] = 1;
    base.v[3][0] = 0; base.v[3][1] = 0; base.v[3][2] = 1; base.v[3][3] = 0; base.v[3][4] = 0; base.v[3][5] = 1;
    base.v[4][0] = 0; base.v[4][1] = 0; base.v[4][2] = 0; base.v[4][3] = 1; base.v[4][4] = 0; base.v[4][5] = 1;
    base.v[5][0] = 0; base.v[5][1] = 0; base.v[5][2] = 0; base.v[5][3] = 0; base.v[5][4] = 1; base.v[5][5] = 1;

    mat ans = qpow(base, n+1);
    return ans.v[0][5];
}


signed main() {
    hello;
    int n; cin >> n;
    cout << cal(n) << endl;


    world;
}


```
